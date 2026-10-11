"""Focused scratch briefs, hypothesis-led probes, and a persistent manual-attempt cap."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys

import build_dra as B
from source_inventory import ROOT, UNITS, manifest, source_functions, sdk_symbols, mask

ATTEMPT_CAP = 10


def file_sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def complete_assembly(path, function, address):
    """Require one labeled, contiguous retail body of the declared size."""
    text = path.read_text()
    declared = re.search(r"(?m)^nonmatching\s+" + re.escape(function) + r",\s*(0x[0-9a-fA-F]+|\d+)\s*$", text)
    addresses = [int(value, 16) for value in re.findall(
        r"/\*\s*[0-9a-fA-F]+\s+([0-9a-fA-F]{8})\s+[0-9a-fA-F]{8}\s*\*/", text)]
    if (not declared or not re.search(r"(?m)^glabel\s+" + re.escape(function) + r"\s*$", text)
            or not re.search(r"(?m)^endlabel\s+" + re.escape(function) + r"\s*$", text)):
        raise ValueError("A complete retail assembly reference with matching labels is required")
    size = int(declared[1], 0)
    if (not addresses or addresses[0] != address or len(addresses) * 4 != size
            or any(value != address + index * 4 for index, value in enumerate(addresses))):
        raise ValueError("Retail assembly reference has a gap, stale address, or incomplete declared body")
    return size


def parse_target(value):
    match = re.fullmatch(r"(main|game|title|movie|st0[0-9]):(func_[0-9A-Fa-f]{8})", value)
    if not match:
        raise ValueError("Use unit:func_XXXXXXXX, for example main:func_80027214")
    return match[1], "func_" + match[2][5:].upper()


def target_info(unit, function, calibration=False, *, recovery=False, assembly_hint=None):
    if (unit, function) in sdk_symbols():
        raise ValueError("SDK routines remain symbolized assembly; they are not session targets")
    row = next((r for r in manifest(unit) if r["name"] == function), None)
    if not row or row["kind"] != "func":
        raise ValueError("Review this boundary first; the target is not a game function")
    definitions, stubs, _ = source_functions(unit)
    entry = definitions.get(function)
    if calibration and (not entry or entry["category"] == "cxx_alias"):
        raise ValueError("Calibration requires an existing C body")
    if entry and not calibration and not recovery:
        raise ValueError("Target already has source; use --calibration for diagnostic setup")
    if not entry and function not in stubs:
        raise ValueError("Target has no active source slot")
    source = ROOT / (entry["source"] if entry else stubs[function])
    text = source.read_text()
    directories = [directory for directory, name in re.findall(
        r'INCLUDE_ASM\("([^\"]+)",\s*(func_[0-9A-Fa-f]{8})\)', text) if name == function]
    candidates = list((ROOT / "asm/us" / unit).rglob(function + ".s"))
    active = [p for p in candidates if p.parent.relative_to(ROOT).as_posix() in directories]
    same_slot = [p for p in candidates if p.parent.name == source.stem]
    if recovery and entry and assembly_hint:
        # A recorded recovery session starts with an ASM stub, then writes C.
        # Its retained retail reference may live in an older sector directory.
        # Preserve that explicit reference rather than guessing after the stub
        # disappears. The caller still compares all metadata and the ASM SHA.
        selected = [path for path in candidates if path.relative_to(ROOT).as_posix() == assembly_hint]
    else:
        selected = active if directories else same_slot if len(same_slot) == 1 else candidates
    if len(selected) != 1:
        raise ValueError("A unique complete retail assembly reference is required")
    complete_assembly(selected[0], function, row["address"])
    cc1, flags, maspsx, as_flags = B.unit_toolchain(unit, source.name)
    return dict(unit=unit, function=function, source=source.relative_to(ROOT).as_posix(),
                assembly=selected[0].relative_to(ROOT).as_posix(), address=hex(row["address"]),
                assembly_sha256=file_sha256(selected[0]),
                compiler=str(cc1), cc1_flags=flags, maspsx_flags=maspsx, as_flags=as_flags,
                calibration=calibration, provenance="Original-object grouping/settings require separate review")


def body_excerpt(text, function):
    clean = mask(text)
    found = re.search(r"(?m)^[^\n;={}]*\b" + re.escape(function) + r"\([^;{}]*\)\s*\{", clean)
    if not found:
        return None
    start, pos, depth = found.start(), found.end(), 1
    while pos < len(clean) and depth:
        depth += (clean[pos] == "{") - (clean[pos] == "}")
        pos += 1
    return text[start:pos] if depth == 0 else None


def session_dir(unit, function):
    return ROOT / "analysis/scratch" / unit / function


def attempts_this_cycle(state):
    return sum(entry["cycle"] == state.get("cycle", 0) for entry in state["probes"])


def require_attempt_available(state):
    if attempts_this_cycle(state) >= ATTEMPT_CAP:
        raise ValueError("Ten manual probes reached. Preserve the seed and use a calibrated CPU search; requeue only with new learning evidence.")


def brief(unit, function, seed=None, calibration=False, m2c=False):
    info = target_info(unit, function, calibration)
    directory = session_dir(unit, function)
    directory.mkdir(parents=True, exist_ok=True)
    state_path = directory / "session.json"
    if state_path.exists():
        state = json.loads(state_path.read_text())
        if state["target"] != info:
            raise ValueError("Target/profile changed; preserve this session and explicitly review its baseline before restarting")
    else:
        state = dict(target=info, cycle=0, probes=[], requeues=[])
    source = ROOT / info["source"]
    assembly = ROOT / info["assembly"]
    target = directory / "target.s"
    if target.exists() and file_sha256(target) != info["assembly_sha256"]:
        raise ValueError("Scratch retail assembly changed; preserve and review it before continuing")
    if not target.exists():
        target.write_bytes(assembly.read_bytes())
    definitions, _, _ = source_functions(unit)
    neighbors = sorted((name for name, entry in definitions.items()
                        if entry["source"] == info["source"] and entry["category"] not in ("assisted_c", "source_hack_c") and name != function),
                       key=lambda name: abs(int(name[5:], 16) - int(function[5:], 16)))[:3]
    headings = re.findall(r'^#include "([^"]+)"', source.read_text(), re.M)
    lines = ["# " + unit + ":" + function, "", "## Current task", "", "Recover a natural source body with the real ABI and defined target arithmetic. SDK stays assembly.",
             "A scratch score is diagnostic. Parent acceptance requires whole-unit bytes, data/relocations and source placement.", "",
             "## Fixed baseline", "", "```json", json.dumps(info, indent=2), "```", "",
             "Manual probes in this cycle: " + str(attempts_this_cycle(state)) + "/10. Change one hypothesis at a time.", "",
             "Read docs/CODEGEN_MODEL.md first; query tools/learning_search.py for the observed diff class.", "",
             "Headers: " + ", ".join("include/" + name for name in headings), "",
             "Retail assembly: target.s (complete copied reference).", "",
             "## Matched neighbors", ""]
    for neighbor in neighbors:
        snippet = body_excerpt(source.read_text(), neighbor)
        if snippet:
            lines.extend(["### " + neighbor, "", "```c", snippet[:1600], "```", ""])
    if seed:
        candidate = Path(seed).resolve()
        candidate.relative_to(ROOT.resolve())
        (directory / "seed.c").write_bytes(candidate.read_bytes())
        state["seed"] = candidate.relative_to(ROOT).as_posix()
        lines.extend(["Seed: seed.c. Logic/type/lifetime review is required before permutation.", ""])
    if m2c:
        command = [sys.executable, str(ROOT / ".tools/m2c/m2c.py"), "-t", "mipsel-gcc-c", str(directory / "target.s")]
        result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True)
        (directory / "m2c.c").write_text(result.stdout)
        (directory / "m2c.log").write_text(result.stderr)
        state["m2c_exit"] = result.returncode
        lines.extend(["m2c baseline: m2c.c; exit " + str(result.returncode) + ". Declarations/semantics remain unverified.", ""])
    lines.extend(["## Last result", "", "See RESULT.md and session.json; preserve both after every probe.", ""])
    (directory / "BRIEF.md").write_text("\n".join(lines))
    state_path.write_text(json.dumps(state, indent=2) + "\n")
    return directory


def probe(unit, function, hypothesis):
    directory = session_dir(unit, function)
    state = json.loads((directory / "session.json").read_text())
    require_attempt_available(state)
    if not hypothesis.strip():
        raise ValueError("State one concrete hypothesis before compiling")
    info = state["target"]
    if info != target_info(unit, function, info["calibration"], recovery=True,
                           assembly_hint=info["assembly"]):
        raise ValueError("The session's compiler/target metadata changed")
    if file_sha256(directory / "target.s") != info["assembly_sha256"]:
        raise ValueError("Scratch retail assembly differs from the active reference")
    definitions, stubs, _ = source_functions(unit)
    if function in stubs or function not in definitions:
        raise ValueError("Target still uses INCLUDE_ASM; write a source candidate before probing")
    number = len(state["probes"]) + 1
    report = directory / f"probe-{number:03d}.json"
    source_hash = file_sha256(ROOT / info["source"])
    entry = dict(cycle=state["cycle"], hypothesis=hypothesis, report=report.relative_to(ROOT).as_posix(),
                 source_sha256=source_hash, source_candidate_valid=True,
                 exit_code=None, at=datetime.now(timezone.utc).isoformat())
    # Reserve the attempt before spawning the compiler so an interrupted run
    # cannot silently reset the cap or lose its hypothesis.
    state["probes"].append(entry)
    (directory / "session.json").write_text(json.dumps(state, indent=2) + "\n")
    (directory / "RESULT.md").write_text("# Diagnostic running or interrupted\n\n" + json.dumps(entry, indent=2) + "\n")
    with report.open("w") as output:
        result = subprocess.run([sys.executable, str(ROOT / "tools/probe_slot.py"), unit,
                                 Path(info["source"]).name, "--function", function], cwd=ROOT, stdout=output, stderr=subprocess.STDOUT)
    entry["exit_code"] = result.returncode
    (directory / "session.json").write_text(json.dumps(state, indent=2) + "\n")
    (directory / "RESULT.md").write_text("# Latest diagnostic\n\n" + json.dumps(entry, indent=2) + "\n\nPrivate only; no linked-source credit.\n")
    return result.returncode


def requeue(unit, function, evidence, reason, refresh_profile=False):
    path, _, anchor = evidence.partition("#")
    resolved = (ROOT / path).resolve()
    resolved.relative_to(ROOT.resolve())
    if not resolved.is_file() or not reason.strip():
        raise ValueError("Requeue needs an existing new-learning file and a concrete reason")
    state_path = session_dir(unit, function) / "session.json"
    state = json.loads(state_path.read_text())
    if any(entry["evidence"] == evidence for entry in state["requeues"]):
        raise ValueError("This learning already reopened the function; supply new evidence")
    reopening = dict(evidence=evidence, evidence_sha256=file_sha256(resolved),
                     reason=reason, previous_cycle=state["cycle"])
    if refresh_profile:
        previous = state["target"]
        current = target_info(unit, function, previous["calibration"], recovery=True,
                              assembly_hint=previous["assembly"])
        profile_fields = {"compiler", "cc1_flags", "maspsx_flags", "as_flags"}
        if ({key: value for key, value in previous.items() if key not in profile_fields}
                != {key: value for key, value in current.items() if key not in profile_fields}):
            raise ValueError("Profile refresh cannot change the target, source slot or retail reference; review that boundary separately")
        if file_sha256(state_path.parent / "target.s") != previous["assembly_sha256"]:
            raise ValueError("Scratch retail assembly changed; preserve and review it before reopening")
        reopening["previous_target"] = previous
        reopening["current_target"] = current
        state["target"] = current
    state["requeues"].append(reopening)
    state["cycle"] += 1
    state_path.write_text(json.dumps(state, indent=2) + "\n")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    for name in ("brief", "probe", "requeue"):
        command = commands.add_parser(name)
        command.add_argument("target")
        if name == "brief":
            command.add_argument("--seed")
            command.add_argument("--calibration", action="store_true")
            command.add_argument("--m2c", action="store_true")
        elif name == "probe":
            command.add_argument("--hypothesis", required=True)
        else:
            command.add_argument("--evidence", required=True)
            command.add_argument("--reason", required=True)
            command.add_argument("--refresh-profile", action="store_true",
                                 help="explicitly adopt reviewed current compiler flags while preserving the retail target and prior probes")
    args = parser.parse_args()
    try:
        unit, function = parse_target(args.target)
        if args.command == "brief":
            print(brief(unit, function, args.seed, args.calibration, args.m2c).relative_to(ROOT))
        elif args.command == "probe":
            return probe(unit, function, args.hypothesis)
        else:
            requeue(unit, function, args.evidence, args.reason, args.refresh_profile)
    except (ValueError, KeyError, FileNotFoundError) as error:
        parser.exit(2, str(error) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
