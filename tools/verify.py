"""Build canonical units and record fresh input hashes plus complete byte comparisons."""
from project_layout import source_dir
import argparse
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

import build_dra
from source_inventory import ROOT, UNITS, manifest, source_functions

RECORDS = ROOT / "build/us/verification"


def digest(path):
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()


def input_manifest(unit):
    paths = {ROOT / "tools/build_dra.py", ROOT / "tools/verify.py", ROOT / "tools/check_source_order.py", ROOT / "tools/source_inventory.py", ROOT / "tools/project_layout.py"}
    for tree in ("include", "external/maspsx", "bin/windows", "assets", "bin/cc1_revisions"):
        paths.update(p for p in (ROOT / tree).rglob("*") if p.is_file()
                     and "__pycache__" not in p.parts and ".git" not in p.parts)
    for tree in (source_dir(unit), f"asm/us/{unit}"):
        paths.update(p for p in (ROOT / tree).rglob("*") if p.is_file()
                     and not (unit == "game" and "stages" in p.relative_to(ROOT).parts))
    paths.update(p for p in (ROOT / "config/us/linkers").glob("*") if p.is_file()
                 and (p.name == f"{unit}.ld" or f".{unit}." in p.name))
    for name in (f"{unit}.yaml", "SLUS_014.04.yaml" if unit == "main" else f"{unit}.yaml",
                 f"sym.{unit}.txt", f"rel.{unit}.txt", f"functions/{unit}.txt"):
        path = ROOT / "config/us" / name
        if path.exists():
            paths.add(path)
    required_manifest = ROOT / "config/us/functions" / f"{unit}.txt"
    if not required_manifest.is_file() or not manifest(unit):
        raise ValueError(f"Missing or empty function manifest: {unit}")
    sdk_metadata = ROOT / "config/us/psyq_funcs.txt"
    if not sdk_metadata.is_file():
        raise ValueError("Missing SDK assembly classification metadata")
    paths.add(sdk_metadata)
    boundary_metadata = ROOT / "config/us/boundary_overrides.json"
    if boundary_metadata.is_file():
        paths.add(boundary_metadata)
    paths.add(ROOT / build_dra.CONFIG[unit]["target"])
    return {p.relative_to(ROOT).as_posix(): digest(p) for p in sorted(paths)}


def require_placement(unit):
    symbols = {}
    for name, address, obj in build_dra.parse_map_symbols(unit):
        symbols.setdefault(name, []).append((address, obj.replace("\\", "/")))
    definitions, _, duplicates = source_functions(unit)
    if duplicates:
        raise ValueError(f"Duplicate source definitions: {unit}: {duplicates}")
    for row in manifest(unit):
        resolved = symbols.get(row["name"], [])
        if not resolved:
            raise ValueError(f"Manifest symbol is not defined in linked map: {unit}:{row['name']}")
        if any(address != row["address"] for address, _ in resolved):
            raise ValueError(f"Manifest placement differs: {unit}:{row['name']}")
        if row["name"] in definitions:
            expected_object = "build/us/" + definitions[row["name"]]["source"] + ".o"
            if not any(obj == expected_object for _, obj in resolved):
                raise ValueError(f"Source symbol resolved from wrong object: {unit}:{row['name']}")


def fingerprint(inputs):
    return hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest()


def current_verification(unit):
    path = RECORDS / f"{unit}.json"
    if not path.exists():
        return dict(unit=unit, current_verified_build=False, reason="canonical build verification required")
    try:
        record = json.loads(path.read_text())
        cfg = build_dra.CONFIG[unit]
        output = ROOT / cfg["out"]
        target = ROOT / cfg["target"]
        current = fingerprint(input_manifest(unit)) == record.get("inputs_sha256")
        valid = output.exists() and digest(output) == record.get("output_sha256")
        valid = valid and hashlib.sha1(target.read_bytes()).hexdigest() == cfg["sha1"]
        valid = valid and output.read_bytes() == target.read_bytes()
        valid = valid and digest(ROOT / "build/us" / f"{unit}.map") == record.get("map_sha256")
        valid = valid and digest(ROOT / cfg["elf"]) == record.get("elf_sha256")
    except (OSError, ValueError) as error:
        return dict(unit=unit, current_verified_build=False, reason=f"verification unavailable: {error}")
    return dict(unit=unit, current_verified_build=current and valid,
                reason="verified" if current and valid else "inputs or outputs changed", record=record)


def build(units):
    RECORDS.mkdir(parents=True, exist_ok=True)
    before = {u: input_manifest(u) for u in units}
    for unit in units:
        (RECORDS / f"{unit}.json").unlink(missing_ok=True)
        cfg = build_dra.CONFIG[unit]
        if hashlib.sha1((ROOT / cfg["target"]).read_bytes()).hexdigest() != cfg["sha1"]:
            raise ValueError(f"Retail input hash changed: {unit}")
    subprocess.run([sys.executable, str(ROOT / "tools/check_source_order.py"), "--check"], cwd=ROOT, check=True)
    command = [sys.executable, str(ROOT / "tools/build_dra.py")]
    if len(units) == 1:
        command += ["--unit", units[0]]
    # Reproduce the recorded local toolchain; external overrides need their own audit.
    environment = {k: v for k, v in os.environ.items() if not k.startswith("DRA_")}
    subprocess.run(command, cwd=ROOT, env=environment, check=True)
    after = {u: input_manifest(u) for u in units}
    records = []
    for unit in units:
        if before[unit] != after[unit]:
            raise ValueError(f"Inputs changed during build: {unit}; rebuild after edits stop")
        cfg = build_dra.CONFIG[unit]
        actual, expected = (ROOT / cfg["out"]).read_bytes(), (ROOT / cfg["target"]).read_bytes()
        if actual != expected:
            raise ValueError(f"Whole output differs: {unit}")
        require_placement(unit)
        record = dict(unit=unit, verified_at=datetime.now(timezone.utc).isoformat(),
                      byte_identical=True, sha1=cfg["sha1"], size=len(actual),
                      output_sha256=hashlib.sha256(actual).hexdigest(),
                      map_sha256=digest(ROOT / "build/us" / f"{unit}.map"), elf_sha256=digest(ROOT / cfg["elf"]),
                      inputs_sha256=fingerprint(before[unit]), inputs=before[unit])
        records.append(record)
    for record in records:
        (RECORDS / f"{record['unit']}.json").write_text(json.dumps(record, indent=2) + "\n")
    print(f"Fresh canonical verification: {len(records)}/{len(units)} complete units")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--unit", choices=UNITS)
    parser.add_argument("--check", action="store_true", help="check saved evidence without building")
    args = parser.parse_args()
    units = [args.unit] if args.unit else UNITS
    if args.check:
        states = [current_verification(u) for u in units]
        for state in states:
            print(f"{state['unit']}: {state['reason']}")
        return 0 if all(s["current_verified_build"] for s in states) else 1
    build(units)
    return 0


if __name__ == "__main__":
    sys.exit(main())
