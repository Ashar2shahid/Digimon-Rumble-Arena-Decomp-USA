#!/usr/bin/env python3
"""Check that each src/<unit>/<slot>.c defines functions in retail vram order.

cc1psx emits a translation unit's functions in source order and the linker
places that object's .text at the slot start, so a slot's definitions MUST
appear in ascending vram order (the order splat generated).  A reordered file
shifts every following symbol in the unit; per-symbol check_unit verdicts
cannot see that (each symbol is compared against its own retail bytes), and the
whole-image sha1 only says "mismatch".

For every src/<unit>/<slot>.c this extracts the sequence of definers
(INCLUDE_ASM stubs and top-level C function definitions), maps each to its vram
in config/us/functions/<unit>.txt, and reports the first out-of-order pair
plus how many definitions are misplaced (len - LIS).  Definitions absent from
the manifest are skipped (static helpers / aliases).

Usage:
    python tools/check_source_order.py            # report + summary
    python tools/check_source_order.py --check    # CI: exit 1 on violation, no summary
"""
from project_layout import source_dir
import argparse
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
UNITS = ["main", "game", "title", "movie"] + ["st%02d" % i for i in range(10)]

INCLUDE_ASM_RE = re.compile(r'INCLUDE_ASM\("[^"]*",\s*(\w+)\)')
# Top-level function definition: return type / qualifiers then the name, then
# an opening paren.  The name is taken as the last identifier before the paren.
DEF_RE = re.compile(r"^\s*(?:\w+\s+|\*\s*)+(\w+)\s*\(")


def manifest_vrams(unit):
    """{name: vram} for a unit, from config/us/functions/<unit>.txt."""
    path = os.path.join(ROOT, "config", "us", "functions", "%s.txt" % unit)
    out = {}
    if not os.path.exists(path):
        return out
    with open(path, errors="ignore") as f:
        for line in f:
            line = line.split("#", 1)[0].strip()
            if not line:
                continue
            m = re.match(r"(\S+)\s+([0-9A-Fa-f]+)", line)
            if m:
                out.setdefault(m.group(1), int(m.group(2), 16))
    return out


def name_before_paren(text):
    head = text[:text.index("(")].rstrip()
    parts = head.split()
    if not parts:
        return None
    return parts[-1].lstrip("*") or None


def definers(path):
    """[(name, line_no)] of a C file's definers, in source order.

    INCLUDE_ASM stubs and top-level function definitions; prototypes
    (`extern ...;`), typedefs and data definitions are ignored."""
    out = []
    with open(path, errors="ignore") as f:
        lines = f.read().splitlines()
    depth = 0
    for i, raw in enumerate(lines, 1):
        line = raw.rstrip()
        if depth == 0:
            s = line.strip()
            if s and not s.startswith(("#", "/*", "*", "//", "}")):
                m = INCLUDE_ASM_RE.search(s)
                if m:
                    out.append((m.group(1), i))
                elif not s.startswith(("extern", "typedef")) \
                        and "(" in s and not s.endswith(";") \
                        and DEF_RE.match(line):
                    nm = name_before_paren(s)
                    if nm:
                        out.append((nm, i))
        depth += line.count("{") - line.count("}")
    return out


def lis_length(seq):
    """Longest strictly increasing subsequence length (O(n^2))."""
    best = [1] * len(seq)
    for i in range(len(seq)):
        for j in range(i):
            if seq[j] < seq[i] and best[j] + 1 > best[i]:
                best[i] = best[j] + 1
    return max(best) if best else 0


def check_file(path, unit, vrams):
    """(first_pair, misplaced, considered) or None when in order."""
    seq = [(nm, vrams[nm]) for nm, _ln in definers(path) if nm in vrams]
    inv = None
    for i in range(1, len(seq)):
        if seq[i][1] < seq[i - 1][1]:
            inv = (seq[i - 1], seq[i])
            break
    if inv is None:
        return None
    misplaced = len(seq) - lis_length([vr for _nm, vr in seq])
    return inv, misplaced, len(seq)


def main():
    ap = argparse.ArgumentParser(description="Check src function ordering vs retail vram.")
    ap.add_argument("--check", action="store_true",
                    help="CI mode: no summary, exit non-zero on any violation")
    args = ap.parse_args()

    checked = 0
    violations = 0
    for unit in UNITS:
        src = os.path.join(ROOT, source_dir(unit))
        if not os.path.isdir(src):
            continue
        vrams = manifest_vrams(unit)
        for name in sorted(os.listdir(src)):
            if not name.endswith(".c"):
                continue
            path = os.path.join(src, name)
            checked += 1
            res = check_file(path, unit, vrams)
            if res is None:
                continue
            violations += 1
            (pa, va), (pb, vb) = res[0]
            print("%s: %s (0x%08X) defined before %s (0x%08X); %d of %d misplaced"
                  % (os.path.relpath(path, ROOT), pa, va, pb, vb, res[1], res[2]))
    if not args.check:
        print("checked %d files, %d with out-of-order definitions" % (checked, violations))
    return 1 if violations else 0


if __name__ == "__main__":
    sys.exit(main())
