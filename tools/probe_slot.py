"""Compile one source slot into private objects for diagnostic byte comparisons.

Relocations are masked only for iteration. This never grants source credit;
tools/verify.py must pass the complete linked unit afterward.
"""
from project_layout import source_dir
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
from unittest.mock import patch

import build_dra as B
from check_unit import object_symbols
from source_inventory import ROOT, UNITS, source_functions, manifest


def parse_relocation_metadata(symbol_text, relocation_text):
    """Read objdump's ELF symbol/relocation tables, including local section values.

    A relocation against a defined symbol in the same section can be resolved
    relative to a function. An undefined or differently-sectioned symbol cannot
    be checked until linking. This parser deliberately does not guess addends
    from decorated VALUE expressions.
    """
    symbols = {}
    for line in symbol_text.splitlines():
        fields = line.split()
        if len(fields) >= 5 and re.fullmatch(r"[0-9a-fA-F]{8}", fields[0]) \
                and re.fullmatch(r"[0-9a-fA-F]{8}", fields[-2]):
            symbols[fields[-1]] = (fields[-3], int(fields[0], 16))
    relocations = {}
    section = None
    for line in relocation_text.splitlines():
        heading = re.match(r"RELOCATION RECORDS FOR \[(\S+)\]", line)
        if heading:
            section = heading.group(1)
            continue
        match = re.match(r"^([0-9a-fA-F]{8})\s+(R_MIPS_\w+)\s+(\S+)\s*$", line)
        if section is None or match is None:
            continue
        offset = int(match.group(1), 16)
        kind, symbol = match.group(2), match.group(3)
        symbol_section, symbol_value = symbols.get(symbol, (None, None))
        if offset in relocations.setdefault(section, {}):
            raise ValueError(f"Multiple relocations at {section}+{offset:#x}")
        relocations[section][offset] = dict(kind=kind, symbol=symbol,
                                             symbol_section=symbol_section,
                                             symbol_value=symbol_value)
    return relocations


def object_relocations(obj):
    """Return relocation metadata from this object's ELF tables via objdump."""
    def dump(flag):
        return subprocess.run([B.tool("objdump"), flag, obj], cwd=ROOT,
                              check=True, capture_output=True, text=True).stdout
    return parse_relocation_metadata(dump("-t"), dump("-r"))


def relocation_mask(kind, expected_word):
    if kind == "R_MIPS_26":
        return 0xFC000000
    if kind in ("R_MIPS_HI16", "R_MIPS_LO16", "R_MIPS_GPREL16"):
        return 0xFFFF0000
    if kind == "R_MIPS_32":
        return 0  # A relocated whole-word address, not an instruction field.
    if kind is None:
        # Legacy callers supply only offsets. Keep their low-level masked-word
        # API unchanged; probe_slot itself supplies typed relocation metadata.
        return 0xFC000000 if expected_word >> 26 in (2, 3) else 0xFFFF0000
    return 0xFFFFFFFF  # Unknown relocation: compare conservatively.


def compare_words(actual, expected, relocated, *, function_vram=None,
                  function_offset=None, section=None):
    """Compare code fields and, when metadata permits, local R_MIPS_26 targets.

    `relocated` may be an offset set for legacy masked diagnostics or an
    offset-to-ELF-metadata map. A local jump target is checked only with the
    latter plus retail and object function locations. External relocations
    still require the linked gate.
    """
    differences = []
    for offset in range(0, min(len(actual), len(expected)), 4):
        got = int.from_bytes(actual[offset:offset + 4], "little")
        want = int.from_bytes(expected[offset:offset + 4], "little")
        mask = 0xFFFFFFFF
        if offset in relocated:
            entry = relocated[offset] if isinstance(relocated, dict) else None
            kind = entry["kind"] if entry is not None else None
            mask = relocation_mask(kind, want)
        if (got & mask) != (want & mask):
            differences.append(dict(offset=hex(offset), actual=f"{got:08x}", expected=f"{want:08x}", mask=f"{mask:08x}"))
            continue
        if offset not in relocated or not isinstance(relocated, dict):
            continue
        entry = relocated[offset]
        if entry["kind"] != "R_MIPS_26" or function_vram is None \
                or function_offset is None or section is None \
                or entry["symbol_section"] != section \
                or entry["symbol_value"] is None:
            continue
        # ELF32/MIPS REL stores the addend in the instruction's low 26 bits.
        # For a defined same-section symbol, S + A gives the object target.
        object_target = entry["symbol_value"] + ((got & 0x03FFFFFF) << 2)
        retail_pc = function_vram + offset
        retail_target = ((retail_pc + 4) & 0xF0000000) | ((want & 0x03FFFFFF) << 2)
        actual_relative = object_target - function_offset
        retail_relative = retail_target - function_vram
        if actual_relative != retail_relative:
            differences.append(dict(offset=hex(offset), actual=f"{got:08x}", expected=f"{want:08x}",
                                    mask=f"{mask:08x}", reason="local_jump_target",
                                    actual_relative_target=hex(actual_relative),
                                    retail_relative_target=hex(retail_relative),
                                    relocation_symbol=entry["symbol"]))
    return differences


def original_size(unit, name, source=None):
    candidates = list((ROOT / "asm/us" / unit).rglob(f"{name}.s"))
    if len(candidates) > 1 and source is not None:
        # Old sector splits may remain as historical assembly beside the
        # current complete function. Prefer the assembly directories referenced
        # by this source slot, then its own basename, before estimating a span.
        directories = re.findall(r'INCLUDE_ASM\("([^\"]+)"', source.read_text())
        active = [path for path in candidates if path.parent.relative_to(ROOT).as_posix() in directories]
        if len(active) == 1:
            candidates = active
        else:
            same_slot = [path for path in candidates if path.parent.name == source.stem]
            if len(same_slot) == 1:
                candidates = same_slot
    if len(candidates) != 1:
        rows = manifest(unit)
        current = next((row["address"] for row in rows if row["name"] == name), None)
        following = min((row["address"] for row in rows if current is not None and row["address"] > current), default=None)
        # This can include padding or a false split. It is only a diagnostic
        # region estimate when the original individual assembly is unavailable.
        return following - current if following is not None else None
    text = candidates[0].read_text()
    declared = re.search(r"nonmatching\s+" + re.escape(name) + r",\s*(0x[0-9a-fA-F]+|\d+)", text)
    if declared:
        return int(declared[1], 0)
    addresses = [int(a, 16) for a in re.findall(r"/\*\s*[0-9a-fA-F]+\s+([0-9a-fA-F]{8})", text)]
    return max(addresses) - min(addresses) + 4 if addresses else None


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("unit", choices=UNITS)
    parser.add_argument("slot", help="source basename, e.g. 1E800.c")
    parser.add_argument("--function", action="append", help="restrict diagnostics to an address-named function")
    parser.add_argument("--compiler", choices=("shipped", "psyq40", "esa45", "psyq46", "gcc272"),
                        help="private compiler candidate; does not change canonical settings")
    parser.add_argument("--g", type=int, choices=(0, 8),
                        help="private small-data threshold candidate")
    args = parser.parse_args()
    if Path(args.slot).name != args.slot or not args.slot.endswith(".c"):
        parser.error("slot must be a .c basename")
    source = ROOT / source_dir(args.unit) / args.slot
    if not source.is_file():
        parser.error("source slot does not exist")
    key = f"{args.unit}/{args.slot}"
    if args.compiler and B.UNIT_CXX.get(key):
        parser.error("compiler-profile override is not supported for C++ slots; use the existing C++ compiler")
    compiler_candidates = {
        "shipped": B.cc1_bin(),
        "psyq40": "bin/cc1_revisions/psyq4.0/CC1PSX.EXE",
        "esa45": "bin/cc1_revisions/esa4.5/psyq4.5/CC1PSX.EXE",
        "psyq46": "bin/cc1_revisions/psyq46/CC1PSX.EXE",
        "gcc272": "bin/windows/gcc-2.7.2-win/CC1PSX.EXE",
    }
    if args.compiler:
        compiler = compiler_candidates[args.compiler]
        if not (ROOT / compiler).is_file():
            parser.error(f"compiler candidate is unavailable: {compiler}")
        B.UNIT_CC1_EXE[key] = compiler
    if args.g is not None:
        B.UNIT_G[key] = args.g
    os.chdir(ROOT)
    before = hashlib.sha256(source.read_bytes()).hexdigest()
    directory = f"build/us/probes/{args.unit}/{source.stem}-{os.getpid()}"
    B.BUILD = directory
    real_walk = os.walk

    def one_slot(root):
        for path, directories, files in real_walk(root):
            yield path, directories, [name for name in files if Path(path) / name == source]

    with patch.object(B.os, "walk", one_slot):
        count = B.compile_c(B.cpp_bin(), B.cc1_bin(), str(Path(B.tool("as")).absolute()), [args.unit])
    if count != 1:
        raise ValueError(f"Single-slot compilation failed: {count}")
    if hashlib.sha256(source.read_bytes()).hexdigest() != before:
        raise ValueError("Source changed while probing; retry after edits stop")
    obj = B.obj_for(str(source))
    symbols, _ = object_symbols([obj])
    relocations = object_relocations(obj)
    definitions, _, _ = source_functions(args.unit)
    addresses = {row["name"]: row["address"] for row in manifest(args.unit)}
    cfg = B.CONFIG[args.unit]
    retail = (ROOT / cfg["target"]).read_bytes()
    if hashlib.sha1(retail).hexdigest() != cfg["sha1"]:
        raise ValueError("Retail revision hash differs")
    sections, results = {}, []
    requested = set(args.function or [name for name, entry in definitions.items() if entry["source"] == source.relative_to(ROOT).as_posix()])
    if not requested:
        raise ValueError("No source definitions selected")
    for name in sorted(requested):
        symbol = symbols.get(name)
        size = original_size(args.unit, name, source)
        if symbol is None or name not in addresses or size is None:
            results.append(dict(function=name, diagnostic_match=False, reason="symbol, retail size or manifest entry unavailable"))
            continue
        path, section, offset, built_size = symbol
        if section not in sections:
            output = ROOT / directory / (section.lstrip(".") + ".bin")
            subprocess.run([B.tool("objcopy"), "-O", "binary", "-j", section, obj, str(output)], cwd=ROOT, check=True)
            sections[section] = output.read_bytes()
        actual = sections[section][offset:offset + built_size]
        retail_offset = addresses[name] - cfg["vram"] + cfg["file_base"]
        expected = retail[retail_offset:retail_offset + size]
        relative_relocations = {r - offset: entry for r, entry in relocations.get(section, {}).items()
                                if offset <= r < offset + built_size}
        differences = compare_words(actual, expected, relative_relocations,
                                    function_vram=addresses[name], function_offset=offset,
                                    section=section)
        matched = built_size == size and len(actual) == size and not differences
        unresolved_jumps = sum(entry["kind"] == "R_MIPS_26" and
                               entry["symbol_section"] != section
                               for entry in relative_relocations.values())
        results.append(dict(function=name, diagnostic_match=matched, built_size=built_size, retail_size=size,
                            relocated_words=len(relative_relocations),
                            unresolved_jump_relocations=unresolved_jumps,
                            differing_words=len(differences), differences=differences[:32]))
    report = dict(unit=args.unit, source=source.relative_to(ROOT).as_posix(), source_sha256=before, results=results,
                  compiler=B.cxx_cc1_bin() if B.UNIT_CXX.get(key) else B.UNIT_CC1_EXE.get(key, B.cc1_bin()),
                  g=B.UNIT_G.get(key, 0),
                  extra_cc1_flags=B.UNIT_CC1.get(key, []),
                  acceptance="diagnostic only; requires a fresh complete linked-unit verify.py gate")
    (ROOT / directory / "probe.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
    return 0 if all(row["diagnostic_match"] for row in results) else 1


if __name__ == "__main__":
    sys.exit(main())
