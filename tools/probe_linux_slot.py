"""Private GCC 2.95.2 diagnostics; run with the existing WSL Python environment.

Only recovered C is compiled. Original INCLUDE_ASM bodies are omitted, and
relocation fields are masked for iteration. This never changes canonical
objects or grants source credit; complete linked-unit verification is required.
"""
import argparse
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import platform
import re
import shutil
import subprocess
import sys
import tempfile

from elftools.elf.elffile import ELFFile

import build_dra as B
from project_layout import source_dir
from probe_slot import compare_words, original_size
from source_inventory import ROOT, UNITS, manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("unit", choices=UNITS)
    parser.add_argument("slot", help="canonical .c basename")
    parser.add_argument("--source", help="optional separate draft under the workspace")
    parser.add_argument("--function", action="append")
    parser.add_argument("--g", type=int, choices=(0, 8), default=0)
    parser.add_argument("--char-signedness", choices=("signed", "unsigned"), default="signed")
    parser.add_argument("--aspsx", choices=("2.77", "2.79", "2.80", "2.86"), default="2.86")
    parser.add_argument("--opt", choices=("2", "3"), default="2")
    parser.add_argument("--sdata", action="append", default=[], metavar="SYMBOL:SIZE")
    args = parser.parse_args()
    if platform.system() != "Linux":
        parser.error("run in WSL with .venv-wsl/bin/python")
    if Path(args.slot).name != args.slot or not args.slot.endswith(".c"):
        parser.error("slot must be a .c basename")
    key = f"{args.unit}/{args.slot}"
    if B.UNIT_CXX.get(key):
        parser.error("this is a C compiler probe; C++ slots retain their separate compiler")
    source = (ROOT / (args.source or f"{source_dir(args.unit)}/{args.slot}")).resolve()
    if not source.is_relative_to(ROOT) or not source.is_file():
        parser.error("source must be an existing workspace file")
    compiler = ROOT / ".tools/gcc-2.95.2/cc1"
    if not compiler.is_file():
        parser.error("fetch the hash-pinned compiler with tools/fetch_compiler.py 2.95.2")
    before = hashlib.sha256(source.read_bytes()).hexdigest()
    stamp = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S%f")
    output = ROOT / f"build/us/linux-probes/{args.unit}/{source.stem}-{stamp}-{os.getpid()}"
    output.mkdir(parents=True, exist_ok=False)
    metadata = dict(B.UNIT_SDATA.get(key, {})) if args.g else {}
    for entry in args.sdata:
        symbol, separator, size = entry.partition(":")
        if not separator or not re.fullmatch(r"[A-Za-z_]\w*", symbol):
            parser.error("small-data metadata must be SYMBOL:SIZE")
        metadata[symbol] = int(size, 0)
    flags = ["-quiet", f"-O{args.opt}", f"-G{args.g}", "-mips1", "-mcpu=3000",
             "-mgas", "-msoft-float", "-fgnu-linker", f"-f{args.char_signedness}-char"]
    preprocessor = shutil.which("mipsel-linux-gnu-cpp") or shutil.which("cpp")
    if preprocessor is None:
        parser.error("a C preprocessor is required in WSL")
    with tempfile.TemporaryDirectory(prefix="dra-gcc295-") as directory:
        work = Path(directory)
        preprocessed, assembly = work / "draft.i", work / "draft.s"
        subprocess.run([preprocessor, "-P", "-undef", "-nostdinc",
                        "-D_LANGUAGE_C", "-DVER_USA", "-DSKIP_ASM",
                        "-D__GNUC__=2", "-D__GNUC_MINOR__=95", "-Dmips", "-D_MIPSEL",
                        "-I", str(ROOT / "include"), str(source), "-o", str(preprocessed)],
                       cwd=ROOT, check=True)
        # Old cc1's stat() overflows on some Windows-mounted paths; its source
        # and output stay in WSL's temporary filesystem during compilation.
        subprocess.run([str(compiler), *flags, "-o", str(assembly), str(preprocessed)],
                       cwd=work, env=dict(os.environ, TMPDIR=str(work)), check=True)
        text = assembly.read_text()
        if metadata:
            text = B.append_external_sdata_metadata(text, metadata, args.g)
        (output / "draft.cc1.s").write_text(text)
        shutil.copy2(preprocessed, output / "draft.i")
    maspsx = [sys.executable, str(ROOT / "external/maspsx/maspsx.py"),
              f"--aspsx-version={args.aspsx}"]
    extras = B.UNIT_MASPSX.get(key, B.CONFIG[args.unit].get("maspsx_extra", []))
    converted = subprocess.run([*maspsx, *extras], input=text, cwd=ROOT,
                               text=True, capture_output=True, check=True)
    translated = output / "draft.gnu.s"
    translated.write_text(converted.stdout)
    obj = output / "draft.o"
    subprocess.run(["mipsel-linux-gnu-as", "-EL", "-march=mips2", "-mtune=mips2",
                    "-no-pad-sections", "-O1", f"-G{args.g}", "-I", str(ROOT / "include"),
                    "-o", str(obj), str(translated)], cwd=ROOT, check=True)
    if hashlib.sha256(source.read_bytes()).hexdigest() != before:
        raise ValueError("source changed while probing; retry after the writer freezes")
    cfg = B.CONFIG[args.unit]
    retail = (ROOT / cfg["target"]).read_bytes()
    if hashlib.sha1(retail).hexdigest() != cfg["sha1"]:
        raise ValueError("retail revision hash differs")
    addresses = {row["name"]: row["address"] for row in manifest(args.unit)}
    with obj.open("rb") as stream:
        elf = ELFFile(stream)
        symbols = {s.name: s for s in elf.get_section_by_name(".symtab").iter_symbols()
                   if s["st_shndx"] != "SHN_UNDEF" and re.fullmatch(r"func_[0-9A-Fa-f]{8}", s.name)}
        relocations = {}
        for section in elf.iter_sections():
            if section["sh_type"] == "SHT_REL":
                relocations.setdefault(section["sh_info"], set()).update(
                    entry["r_offset"] for entry in section.iter_relocations())
        results = []
        for name in sorted(args.function or symbols):
            symbol, size = symbols.get(name), original_size(args.unit, name)
            if symbol is None or name not in addresses or size is None:
                results.append(dict(function=name, diagnostic_match=False,
                                    reason="defined symbol, manifest row or retail size unavailable"))
                continue
            section_index = symbol["st_shndx"]
            if not isinstance(section_index, int):
                continue
            offset, built_size = symbol["st_value"], symbol["st_size"]
            actual = elf.get_section(section_index).data()[offset:offset + built_size]
            retail_offset = addresses[name] - cfg["vram"] + cfg["file_base"]
            expected = retail[retail_offset:retail_offset + size]
            relocated = {r - offset for r in relocations.get(section_index, ())
                         if offset <= r < offset + built_size}
            differences = compare_words(actual, expected, relocated)
            results.append(dict(function=name, diagnostic_match=built_size == size and
                                len(actual) == size and not differences,
                                built_size=built_size, retail_size=size,
                                relocated_words=len(relocated), differences=differences))
    report = dict(unit=args.unit, source=source.relative_to(ROOT).as_posix(),
                  source_sha256=before, compiler=compiler.relative_to(ROOT).as_posix(),
                  compiler_sha256=hashlib.sha256(compiler.read_bytes()).hexdigest(),
                  compiler_flags=flags, aspsx=args.aspsx, maspsx_extra=extras,
                  preprocessor=preprocessor,
                  external_small_data=metadata, object=obj.relative_to(ROOT).as_posix(),
                  results=results, acceptance="diagnostic only; requires fresh complete linked-unit verification")
    (output / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
