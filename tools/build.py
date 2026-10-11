"""Rebuild modules from recovered C, assembly, and original data; require exact matches."""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import subprocess

from compile_c import compile_c


def run(*command):
    subprocess.run(command, check=True)


def inputs_fingerprint(module, config, assembly_only=False):
    digest = hashlib.sha256()
    digest.update(json.dumps(dict(module=module, compiler=config["compiler"], aspsx=config["aspsx"],
                                 assembly_only=assembly_only), sort_keys=True).encode())
    paths = [Path("tools/build.py"), Path("tools/compile_c.py")]
    paths += sorted(Path("include").glob("*.h"))
    paths += sorted((Path("src") / module["name"]).glob("*.c"))
    paths += sorted((Path("asm/us") / module["name"]).glob("*.s"))
    paths += sorted((Path("analysis/us") / module["name"]).glob("*.csv"))
    for path in paths:
        digest.update(path.as_posix().encode())
        digest.update(path.read_bytes())
    return digest.hexdigest()


def function_asm(path: Path) -> str:
    """Keep instructions unchanged. GTE words use .word for GNU as compatibility."""
    result = []
    for line in path.read_text().splitlines():
        if line.startswith(("nonmatching ", "endlabel ", "enddlabel ")):
            continue
        if line.lstrip().startswith(("alabel ", "dlabel ", "jlabel ")):
            line = "glabel " + line.strip().split(" ", 1)[1]
        match = re.search(r"/\* [0-9A-F]+ [0-9A-F]+ ([0-9A-F]{8}) \*/", line)
        if match:
            word = int.from_bytes(bytes.fromhex(match[1]), "little")
            if word >> 26 == 0x12:
                line = f"    .word 0x{word:08X} # original COP2/GTE instruction"
        result.append(line)
    return "\n".join(result) + "\n"


def build_module(module, config, assembly_only):
    name = module["name"]
    original = Path(module["path"])
    data = original.read_bytes()
    if hashlib.sha1(data).hexdigest() != module["sha1"]:
        raise ValueError(f"Input hash mismatch: {original}")
    base, start, end = (int(module[k], 0) for k in ("file_base", "text_start", "text_end"))
    directory = Path("build/us") / name
    directory.mkdir(parents=True, exist_ok=True)
    (directory / "verification.json").unlink(missing_ok=True)
    functions = list(csv.DictReader((Path("analysis/us") / name / "functions.csv").open()))
    recovered = {}
    objects = []
    if not assembly_only:
        for source in sorted((Path("src") / name).glob("*.c")):
            obj = compile_c(source, directory / (source.stem + ".s"), config["compiler"], config["aspsx"])
            objects.append(obj)
            symbols = subprocess.check_output(["mipsel-linux-gnu-nm", "--defined-only", str(obj)], text=True)
            for symbol in re.findall(r"(?m)\b[Tt]\s+(func_[0-9A-F]{8})$", symbols):
                if symbol in recovered:
                    raise ValueError(f"Duplicate recovered function: {symbol}")
                recovered[symbol] = obj
    asm = [".set noreorder", ".set noat", ".macro glabel label", ".globl \\label", "\\label:", ".endm"]
    asm += [".section .prefix,\"a\"", f'.incbin "{original}", 0, {start}']
    linker = ["OUTPUT_ARCH(mips)", "SECTIONS {", f".prefix 0x{base:X} : {{ fallback.o(.prefix) }}"]
    position = start
    matched = []
    names = set()
    for function in functions:
        offset = int(function["vrom"], 0)
        size = int(function["length"], 0)
        address = int(function["address"], 0)
        symbol = function["name"]
        names.add(symbol)
        if offset != position or address != base + offset:
            raise ValueError(f"Non-contiguous function split at {symbol}")
        if symbol in recovered:
            obj = recovered[symbol]
            section = f"{obj.resolve()}(.{symbol})"
            matched.append(dict(name=symbol, address=hex(address), size=size))
        else:
            asm.extend([f".section .{symbol},\"ax\"", function_asm(Path("asm/us") / name / (symbol + ".s"))])
            section = f"fallback.o(.{symbol})"
        # Padding between functions must also match the original; final comparison checks it.
        linker.append(f".{symbol} 0x{address:X} : {{ {section} }}")
        linker.append(f"ASSERT(SIZEOF(.{symbol}) <= 0x{size:X}, \"{symbol} grew\")")
        position += size
    if position != end or set(recovered) - names:
        raise ValueError("Function inventory does not cover the configured text span")
    asm += [".section .suffix,\"a\""]
    if len(data) > end:
        asm += [f'.incbin "{original}", {end}, {len(data) - end}']
    linker += [f".suffix 0x{base + end:X} : {{ fallback.o(.suffix) }}",
               "/DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.gnu.attributes) }"]
    for context in (Path("analysis/us") / name).glob("context*.csv*"):
        for row in csv.DictReader(context.open()):
            if row.get("category") == "symbol" and row["isDefined"] == "False":
                symbol = row["getName"]
                if symbol not in names and not symbol.startswith(".L"):
                    linker.append(f"PROVIDE({symbol} = {row['address']});")
    linker += [f"_gp = {module['gp']};", "}"]
    (directory / "fallback.s").write_text("\n".join(asm) + "\n")
    (directory / "module.ld").write_text("\n".join(linker) + "\n")
    fallback = directory / "fallback.o"
    run("mipsel-linux-gnu-as", "-EL", "-mips1", "-G0", "-o", str(fallback), str(directory / "fallback.s"))
    # Use absolute input paths in the generated linker script, except its fallback alias.
    script = (directory / "module.ld").read_text().replace("fallback.o(", f"{fallback.resolve()}(")
    (directory / "module.ld").write_text(script)
    elf = directory / "module.elf"
    run("mipsel-linux-gnu-ld", "-EL", "-T", str(directory / "module.ld"), "-Map", str(directory / "module.map"),
        "-o", str(elf), str(fallback.resolve()), *(str(obj.resolve()) for obj in objects))
    rebuilt = directory / original.name
    run("mipsel-linux-gnu-objcopy", "-O", "binary", str(elf), str(rebuilt))
    actual = rebuilt.read_bytes()
    if actual != data:
        errors = [i for i, (a, b) in enumerate(zip(actual, data)) if a != b]
        first = errors[0] if errors else min(len(actual), len(data))
        for function in matched:
            offset = int(function["address"], 0) - base
            function["matching"] = actual[offset:offset + function["size"]] == data[offset:offset + function["size"]]
        (directory / "mismatch.json").write_text(json.dumps(matched, indent=2) + "\n")
        raise ValueError(f"{name}: {len(errors)} differing bytes; first at file {first:#x}, RAM {base + first:#x}; sizes {len(actual)}/{len(data)}")
    code_bytes = end - start
    matched_bytes = sum(f["size"] for f in matched)
    result = dict(module=name, sha1=hashlib.sha1(actual).hexdigest(), identical=True,
                  compiler=config["compiler"] if matched else None, aspsx=config["aspsx"] if matched else None,
                  assembly_only=assembly_only, inputs_sha256=inputs_fingerprint(module, config, assembly_only),
                  provisional_functions=len(functions), recovered_c_functions=len(matched),
                  configured_text_bytes=code_bytes, recovered_c_bytes=matched_bytes,
                  c_percent_of_configured_text=round(100 * matched_bytes / code_bytes, 4), functions=matched)
    (directory / "verification.json").write_text(json.dumps(result, indent=2) + "\n")
    (directory / "mismatch.json").unlink(missing_ok=True)
    print(f"{name}: byte-identical; {len(matched)}/{len(functions)} C functions, {matched_bytes}/{code_bytes} configured text bytes", flush=True)
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--assembly-only", action="store_true", help="validate original disassembly without C replacements")
    parser.add_argument("--compiler", choices=("2.7.2", "2.8.1"), help="test a compiler candidate")
    parser.add_argument("--module", help="build only one configured module")
    args = parser.parse_args()
    config = json.loads(Path("config/us/project.json").read_text())
    if args.compiler:
        config["compiler"] = args.compiler
    modules = [m for m in config["modules"] if args.module is None or m["name"] == args.module]
    if not modules:
        parser.error("Unknown module")
    Path("build/us/verification.json").unlink(missing_ok=True)
    results = [build_module(m, config, args.assembly_only) for m in modules]
    if not args.module:
        Path("build/us/verification.json").write_text(json.dumps(results, indent=2) + "\n")


if __name__ == "__main__":
    main()
