"""Calibrate decomp-permuter scoring against complete retail DRA functions.

Read canonical objects and raw images, assemble retail functions privately, and
write only analysis/us/workflow/permuter_calibration/. A zero score is diagnostic;
byte equality and linked placement remain separate acceptance gates.
"""

import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys

import build_dra as build
from project_layout import source_dir


ROOT = Path(__file__).resolve().parent.parent
OUTPUT = ROOT / "analysis/us/workflow/permuter_calibration"
sys.path.insert(0, str(ROOT / ".tools/decomp-permuter"))
from src.scorer import Scorer  # noqa: E402


CASES = (
    ("leaf", "main", "17804", "func_80027588", ROOT / "asm/us/main/func_80027588.s", 16),
    ("branch", "main", "17804", "func_800275FC", ROOT / "asm/us/main/nonmatchings/17804/func_800275FC.s", 604),
    ("table", "game", "12398", "func_80079680", ROOT / "asm/us/game/nonmatchings/12398/func_80079680.s", 172),
)


def run(command):
    return subprocess.run([str(part) for part in command], cwd=ROOT, check=True,
                          capture_output=True, text=True).stdout


def assemble(name, text, directory):
    source = directory / f"{name}.s"
    output = directory / f"{name}.o"
    # Retail jlabel metadata makes local branch targets global and induces
    # R_MIPS_PC16 relocations that this scorer cannot parse. Keep instruction
    # text untouched while making those intra-function labels local again.
    text = re.sub(r"(?m)^\s*jlabel\s+(\.L\w+)\s*$", r"\1:", text)
    source.write_text('.include "macro.inc"\n.set noreorder\n.set noat\n.text\n' + text,
                      encoding="utf-8")
    run([ROOT / build.tool("as"), *build.AS_FLAGS, "-I", ROOT / "include",
         "-o", output, source])
    return output


def scorer(target, function):
    objdump = ROOT / build.tool("objdump")
    command = f'"{objdump}" -drz --disassemble={function}'
    return Scorer(str(target), stack_differences=True, algorithm="difflib",
                  debug_mode=False, ign_branch_targets=False,
                  objdump_command=command)


def function_offset(obj, function):
    symbols = run([ROOT / build.tool("objdump"), "-t", obj])
    for line in symbols.splitlines():
        fields = line.split()
        if fields and fields[-1] == function and ".text" in fields:
            return int(fields[0], 16)
    raise ValueError(f"missing .text symbol {function} in {obj}")


def shift_text_vma(obj, offset):
    shifted = obj.with_name(obj.stem + "_shifted.o")
    # Section VMA changes objdump address metadata only; the assembled retail
    # instructions and relocations remain untouched.
    run([ROOT / build.tool("objcopy"), "--change-section-vma",
         f".text={hex(offset)}", obj, shifted])
    return shifted


def linked_code_check(unit, function, size):
    config = build.CONFIG[unit]
    offset = int(function.removeprefix("func_"), 16) - config["vram"] + config["file_base"]
    actual_file = (ROOT / config["out"]).read_bytes()
    retail_file = (ROOT / config["target"]).read_bytes()
    actual = actual_file[offset:offset + size]
    expected = retail_file[offset:offset + size]
    return dict(file_offset=hex(offset), bytes_equal=len(actual) == size and actual == expected,
                built_sha256=hashlib.sha256(actual).hexdigest(),
                retail_sha256=hashlib.sha256(expected).hexdigest(),
                full_image_sha1_matches=hashlib.sha1(actual_file).hexdigest() == config["sha1"])


def negative_sources(asm):
    register = re.sub(r"(\bsw\s+)\$a1, 0x54\(\$a0\)",
                      r"\g<1>$a2, 0x54($a0)", asm, count=1)
    opcode = re.sub(r"\bsubu(\s+\$a1, \$a1, \$a2)",
                    r"addu\1", asm, count=1)
    if register == asm or opcode == asm:
        raise ValueError("leaf mutation anchor changed")
    return register, opcode


def branch_mutation(asm):
    branch = re.search(r"(\bbeqz\s+\$v0,\s*)(\.L[0-9A-Fa-f]+)", asm)
    if branch is None:
        raise ValueError("branch mutation anchor changed")
    labels = re.findall(r"(?m)^\s*\.L[0-9A-Fa-f]+(?=:)", asm)
    replacement = next((label.strip() for label in labels if label.strip() != branch.group(2)), None)
    if replacement is None:
        raise ValueError("branch mutation anchor changed")
    return asm[:branch.start(2)] + replacement + asm[branch.end(2):]


def table_check():
    """Check code-independent retail table bytes, object relocations and placement."""
    address, count = 0x8006520C, 21
    offset = address - build.CONFIG["game"]["vram"] + build.CONFIG["game"]["file_base"]
    size = count * 4
    built = (ROOT / build.CONFIG["game"]["out"]).read_bytes()
    retail = (ROOT / build.CONFIG["game"]["target"]).read_bytes()
    actual, expected = built[offset:offset + size], retail[offset:offset + size]
    if len(actual) != size or len(expected) != size:
        raise ValueError("table range missing from linked game image")
    corrupted = bytearray(actual)
    corrupted[0] ^= 1
    obj = ROOT / "build/us/src/battle/12398.c.o"
    reloc_text = run([ROOT / build.tool("objdump"), "-r", "-j", ".rodata.79680", obj])
    reloc_count = len(re.findall(r"\bR_MIPS_32\b", reloc_text))
    linker = (ROOT / "config/us/linkers/game.ld").read_text(encoding="utf-8")
    placement = ".rodata_79680 0x8006520C : AT(0xE4C)" in linker
    section = "build/us/src/battle/12398.c.o(.rodata.79680);" in linker
    return dict(vram=hex(address), file_offset=hex(offset), size=size,
                built_sha256=hashlib.sha256(actual).hexdigest(),
                retail_sha256=hashlib.sha256(expected).hexdigest(),
                bytes_equal=actual == expected,
                original_first_word=hex(int.from_bytes(actual[:4], "little")),
                corrupted_first_word=hex(int.from_bytes(corrupted[:4], "little")),
                corrupted_word_rejected=bytes(corrupted) != expected,
                r_mips_32_relocations=reloc_count,
                relocation_count_expected=count,
                linker_address_matches=placement,
                linker_section_matches=section)


def main():
    OUTPUT.mkdir(parents=True, exist_ok=True)
    rows = []
    for label, unit, slot, function, original, retail_size in CASES:
        asm = original.read_text(encoding="utf-8")
        directory = OUTPUT / label
        directory.mkdir(exist_ok=True)
        target = assemble("retail", asm, directory)
        candidate = ROOT / f"build/us/{source_dir(unit)}/{slot}.c.o"
        if not candidate.is_file():
            raise FileNotFoundError(candidate)
        offset = function_offset(candidate, function)
        shifted_target = shift_text_vma(target, offset)
        score = scorer(shifted_target, function)
        positive, _ = score.score(str(candidate))
        row = dict(case=label, function=function, retail_size=retail_size,
                   candidate=str(candidate.relative_to(ROOT)), target=str(shifted_target.relative_to(ROOT)),
                   candidate_text_offset=hex(offset), code_score=positive,
                   target_instructions=len(score.target_seq),
                   linked_code=linked_code_check(unit, function, retail_size))
        if label == "leaf":
            register, opcode = negative_sources(asm)
            mutated = shift_text_vma(assemble("register_changed", register, directory), offset)
            row["register_mutation_score"] = score.score(str(mutated))[0]
            mutated = shift_text_vma(assemble("opcode_changed", opcode, directory), offset)
            row["opcode_mutation_score"] = score.score(str(mutated))[0]
        if label == "branch":
            changed = branch_mutation(asm)
            mutated = shift_text_vma(assemble("branch_changed", changed, directory), offset)
            row["branch_target_mutation_score"] = score.score(str(mutated))[0]
        rows.append(row)
    table = table_check()
    table["code_score_with_table_copy_corrupted"] = next(row["code_score"] for row in rows if row["case"] == "table")
    report = dict(scorer="decomp-permuter Scorer, explicit native objdump -drz --disassemble=<function>",
                  target_metadata="Private retail .text VMA set to canonical function offset; instruction bytes unchanged",
                  stack_differences=True, ignore_branch_targets=False,
                  cases=rows, table_check=table,
                  calibrated=all(row["code_score"] == 0 and row["linked_code"]["bytes_equal"]
                                 and row["linked_code"]["full_image_sha1_matches"] for row in rows)
                  and rows[0]["register_mutation_score"] > 0
                  and rows[0]["opcode_mutation_score"] > 0
                  and rows[1]["branch_target_mutation_score"] > 0
                  and table["bytes_equal"] and table["corrupted_word_rejected"]
                  and table["r_mips_32_relocations"] == 21
                  and table["linker_address_matches"] and table["linker_section_matches"],
                  acceptance="diagnostic calibration only; retain strict source-byte and full linked-unit gates")
    (OUTPUT / "report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report, indent=2))
    return 0 if report["calibrated"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
