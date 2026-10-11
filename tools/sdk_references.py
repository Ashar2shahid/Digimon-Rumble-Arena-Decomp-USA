"""Inspect SDK assembly references; flag literal RAM pointers for relocation review."""
import argparse
from collections import Counter
import json
import re

from source_inventory import ROOT, sdk_symbols, manifest, mask


def audit():
    files = set()
    missing = []
    for unit, name in sorted(sdk_symbols()):
        candidates = list((ROOT / "asm/us" / unit).rglob(f"{name}.s"))
        if candidates:
            files.update(candidates)
        else:
            # Labels may share a larger data/assembly fragment, so report this
            # for review rather than concluding the SDK entry has no assembly.
            missing.append(dict(unit=unit, name=name))
    counts, review = Counter(), []
    for path in sorted(files):
        text = mask(path.read_text(), strings=False)
        for number, line in enumerate(text.splitlines(), 1):
            code = line.split("#", 1)[0].strip()
            if not code:
                continue
            if "%hi(" in code or "%lo(" in code:
                counts["symbolic_hi_lo_operands"] += 1
            if re.match(r"(?:j|jal)\s+", code):
                operand = code.split(None, 1)[1].strip()
                if re.fullmatch(r"(?:0x)?[0-9a-fA-F]{8}", operand):
                    review.append(dict(file=path.relative_to(ROOT).as_posix(), line=number,
                                       kind="literal_control_target", expression=code))
                else:
                    counts["symbolic_direct_transfers"] += 1
            if code.startswith(".word"):
                for operand in code[5:].split(","):
                    operand = operand.strip()
                    if re.fullmatch(r"(?:0x)?[0-9a-fA-F]{8}", operand):
                        value = int(operand, 16)
                        if 0x80000000 <= value < 0x80200000:
                            review.append(dict(file=path.relative_to(ROOT).as_posix(), line=number,
                                               kind="possible_literal_ram_pointer", expression=operand))
                    elif re.search(r"\b(?:D|func|jtbl)_[0-9a-fA-F]{8}\b|\.L[0-9a-fA-F]+", operand):
                        counts["symbolic_data_words"] += 1
            if re.match(r"lui\s+\$\w+,\s*0x800[0-9a-fA-F]\b", code):
                review.append(dict(file=path.relative_to(ROOT).as_posix(), line=number,
                                   kind="possible_literal_ram_high_half", expression=code))
    result = dict(sdk_manifest_entries=len(sdk_symbols()), assembly_files_inspected=len(files),
                  reference_counts=dict(counts), review=review, entries_without_individual_assembly=missing,
                  limitations=["literal RAM values can be intentional constants; inspect before changing",
                               "entries may share fragments; missing individual files are not proof of missing code",
                               "opaque data, external fixed-address symbols and linker layout also need relocation review",
                               "this static audit does not establish that the complete game is shiftable"])
    print(f"SDK: {len(files)} assembly files inspected; {sum(counts.values())} symbolic references; {len(review)} literal-RAM cases for review")
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--save", action="store_true")
    args = parser.parse_args()
    result = audit()
    if args.save:
        (ROOT / "config/us/sdk_references.json").write_text(json.dumps(result, indent=2) + "\n")


if __name__ == "__main__":
    main()
