"""Copy a prior project into a fresh local directory and verify its actual build.

The source project is read only. Stored objects/outputs and SDK archive images
are deliberately not copied. Each run gets a new directory and input manifest.
Run with Windows Python because the reference uses native PSY-Q executables.
"""
from __future__ import annotations

import argparse
import ast
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys


ROOT = Path(os.path.abspath(__file__)).parent.parent
COPIED_TREES = ("src", "include", "asm", "assets", "configs", "linkers",
                "external/maspsx", "bin/windows/binutils", "bin/windows/gcc-win")


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def copy_inputs(source, target):
    paths = set()
    for folder in COPIED_TREES:
        for path in (source / folder).rglob("*"):
            if path.is_file() and not any(part in (".git", "__pycache__") for part in path.parts):
                paths.add(path.relative_to(source))
    for path in ("README.md", "LICENSE", "tools/build_dra.py",
                 "tools/check_source_order.py", "tools/progress.py", "tools/check_unit.py",
                 "bin/windows/gcc-psx/CC1PSX.EXE",
                 "bin/windows/gcc-psx/CPPPSX.EXE",
                 "bin/cc1_revisions/CPPPSX.EXE", "bin/cc1_revisions/CC1PLPSX.EXE",
                 "disks/us/SLUS_014.04"):
        paths.add(Path(path))
    for name in ("game", "title", "movie", *(f"st{i:02}" for i in range(10))):
        paths.add(Path(f"assets/us/bin/{name}.bin"))
    # Read override data as literals rather than importing reference code.
    tree = ast.parse((source / "tools/build_dra.py").read_text())
    for node in tree.body:
        if isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id == "UNIT_CC1_EXE" for t in node.targets):
            for path in ast.literal_eval(node.value).values():
                paths.add(Path(path))
    manifest = []
    for relative in sorted(paths):
        original = source / relative
        destination = target / relative
        if not original.is_file():
            raise FileNotFoundError(original)
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(original, destination)
        if sha256(original) != sha256(destination):
            raise ValueError(f"Copy mismatch: {relative}")
        manifest.append(dict(path=relative.as_posix(), size=destination.stat().st_size,
                             sha256=sha256(destination)))
    return manifest


def run_logged(command, directory, path):
    env = dict(os.environ)
    for name in ("DRA_CPP", "DRA_CC1", "DRA_BINUTILS", "TMPDIR"):
        env.pop(name, None)
    with path.open("w", encoding="utf-8") as log:
        result = subprocess.run(command, cwd=directory, env=env, stdout=log,
                                stderr=subprocess.STDOUT)
    return result.returncode


def check_latest():
    latest = ROOT / "analysis/legacy-audit/latest.json"
    if not latest.is_file():
        raise FileNotFoundError("No isolated legacy build yet; supply the reference project path.")
    report = json.loads(latest.read_text())
    target = Path(report["isolated_project"])
    inputs = json.loads((target.parent / "inputs.json").read_text())["copied"]
    changed = [p["path"] for p in inputs if not (target / p["path"]).is_file()
               or sha256(target / p["path"]) != p["sha256"]]
    recorded = {p["path"] for p in inputs}
    added = [path.relative_to(target).as_posix() for folder in COPIED_TREES
             for path in (target / folder).rglob("*")
             if path.is_file() and not any(part in (".git", "__pycache__") for part in path.parts)
             and path.relative_to(target).as_posix() not in recorded]
    outputs_changed = []
    for row in report["units"]:
        filename = "SLUS_014.04" if row["unit"] == "main" else row["unit"] + ".bin"
        output = target / "build/us/out" / filename
        if not output.is_file() or hashlib.sha1(output.read_bytes()).hexdigest() != row["expected_sha1"]:
            outputs_changed.append(row["unit"])
    valid = (report["build_exit"] == 0 and report["source_order_exit"] == 0
             and all(row["identical"] for row in report["units"])
             and not changed and not added and not outputs_changed)
    print(json.dumps(dict(isolated_snapshot_verified=valid, isolated_project=str(target),
                          changed_inputs=changed, added_inputs=added, changed_outputs=outputs_changed,
                          original_source_note="Verification applies to the copied snapshot. Run audit-legacy again to verify newer reference source.",
                          units_verified=len(report["units"]) if valid else 0), indent=2))
    return 0 if valid else 1


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path, nargs="?")
    parser.add_argument("--status", action="store_true", help="validate the latest copy's inputs and outputs")
    args = parser.parse_args()
    if args.status:
        return check_latest()
    if args.source is None:
        parser.error("Supply the source project directory, or --status.")
    source = Path(os.path.abspath(args.source))
    run_id = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S%fZ")
    output = ROOT / "analysis/legacy-audit" / run_id
    target = output / "project"
    target.mkdir(parents=True, exist_ok=False)
    manifest = copy_inputs(source, target)
    (output / "inputs.json").write_text(json.dumps(dict(source=str(source), copied=manifest), indent=2))
    print(f"Copied {len(manifest)} inputs ({sum(p['size'] for p in manifest):,} bytes) to {target}", flush=True)
    order_rc = run_logged([sys.executable, "tools/check_source_order.py", "--check"], target,
                          output / "source-order.log")
    print(f"Source order exit: {order_rc}", flush=True)
    build_rc = run_logged([sys.executable, "tools/build_dra.py"], target, output / "build.log")
    rows = []
    originals = [("main", "disks/us/SLUS_014.04", "SLUS_014.04")]
    originals += [(n, f"assets/us/bin/{n}.bin", f"{n}.bin") for n in ("game", "title", "movie", *(f"st{i:02}" for i in range(10)))]
    for name, path, filename in originals:
        expected = target / path
        built = target / "build/us/out" / filename
        rows.append(dict(unit=name, identical=built.is_file() and built.read_bytes() == expected.read_bytes(),
                         expected_sha1=hashlib.sha1(expected.read_bytes()).hexdigest(),
                         built_sha1=hashlib.sha1(built.read_bytes()).hexdigest() if built.is_file() else None))
    changed = [p["path"] for p in manifest if sha256(source / p["path"]) != p["sha256"]]
    report = dict(source=str(source), isolated_project=str(target), source_order_exit=order_rc,
                  build_exit=build_rc, copied_inputs=len(manifest), source_changed=changed, units=rows)
    (output / "result.json").write_text(json.dumps(report, indent=2) + "\n")
    (ROOT / "analysis/legacy-audit/latest.json").write_text(json.dumps(report, indent=2) + "\n")
    snapshot = dict(report, audited_at=run_id, inputs_manifest_sha256=sha256(output / "inputs.json"),
                    copied_input_bytes=sum(p["size"] for p in manifest))
    (ROOT / "config/us/legacy-audit.json").write_text(json.dumps(snapshot, indent=2) + "\n")
    print(json.dumps(report, indent=2), flush=True)
    return 0 if order_rc == 0 and build_rc == 0 and all(r["identical"] for r in rows) and not changed else 1


if __name__ == "__main__":
    raise SystemExit(main())
