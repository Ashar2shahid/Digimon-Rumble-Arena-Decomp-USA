"""Create an isolated worker snapshot from a verified checkpoint.

Usage: python tools/worker_workspace.py prepare NAME [--checkpoint PATH]
The snapshot contains only recorded inputs, checkpoint scripts, and explicitly
identified current workflow files and vendored tools. It does not copy Git,
disc images, runtime virtual environments, or builds.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
import shutil
import sys


ROOT = Path(__file__).resolve().parent.parent
HELPERS = ("decomp_session.py", "learning_search.py", "worker_workspace.py", "profile_audit.py",
           "calibrate_permuter.py", "permuter_batch.py", "update_workflow.py")
CURRENT_DOCUMENTS = ("AGENTS.md", "docs/CODEGEN_MODEL.md", "docs/DECOMPILATION_LEARNINGS.md",
                     "docs/DW2_WORKFLOW.md")
VENDORED_TOOLS = ("m2c", "decomp-permuter")
EXCLUDED_VENDOR_PARTS = frozenset((".git", "__pycache__", ".venv", "venv", ".tox", ".pytest_cache"))
NAME_RE = re.compile(r"[A-Za-z][A-Za-z0-9_-]{0,63}\Z")
SHA_RE = re.compile(r"[0-9a-f]{64}\Z")
WINDOWS_DEVICES = frozenset(("CON", "PRN", "AUX", "NUL", *(f"COM{i}" for i in range(1, 10)),
                             *(f"LPT{i}" for i in range(1, 10))))


def digest(path):
    value = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1 << 20), b""):
            value.update(chunk)
    return value.hexdigest()


def _name(value):
    if not NAME_RE.fullmatch(value) or value.upper() in WINDOWS_DEVICES:
        raise ValueError("Worker name must be 1-64 ASCII letters/digits/_/- and start with a letter")
    return value


def _relative(value):
    if not isinstance(value, str) or not value or "\\" in value or ":" in value:
        raise ValueError(f"Unsafe recorded path: {value!r}")
    path = PurePosixPath(value)
    if path.is_absolute() or any(part in ("", ".", "..") for part in value.split("/")):
        raise ValueError(f"Unsafe recorded path: {value!r}")
    if any(part.upper().split(".")[0] in WINDOWS_DEVICES for part in path.parts):
        raise ValueError(f"Unsafe recorded path: {value!r}")
    return path


def _inside(path, directory):
    if not path.resolve().is_relative_to(directory.resolve()):
        raise ValueError(f"Path escapes {directory}: {path}")


def _no_symlink_components(path, directory):
    _inside(path, directory)
    relative = path.relative_to(directory)
    current = directory
    for component in relative.parts:
        current = current / component
        if current.is_symlink():
            raise ValueError(f"Symlink is not allowed in a worker snapshot: {current}")


def _metadata(checkpoint):
    path = checkpoint / "checkpoint.json"
    if not path.is_file() or path.is_symlink():
        raise ValueError(f"Missing checkpoint metadata: {path}")
    data = json.loads(path.read_text(encoding="utf-8"))
    inputs = data.get("copied_inputs_sha256")
    if not isinstance(inputs, dict) or not inputs or data.get("recorded_inputs") != len(inputs):
        raise ValueError("Checkpoint input metadata is incomplete")
    seen = set()
    for relative, expected in inputs.items():
        _relative(relative)
        if not isinstance(expected, str) or not SHA_RE.fullmatch(expected):
            raise ValueError(f"Invalid input digest: {relative}")
        folded = relative.casefold()
        if folded in seen:
            raise ValueError(f"Case-colliding checkpoint input: {relative}")
        seen.add(folded)
    return data


def _checkpoint(root, selected):
    checkpoints = root / "analysis" / "checkpoints"
    if selected is not None:
        path = Path(selected)
        path = path if path.is_absolute() else root / path
        _inside(path, checkpoints)
        if path.parent.resolve() != checkpoints.resolve() or path.is_symlink():
            raise ValueError("Checkpoint must be a direct directory in analysis/checkpoints")
        _metadata(path)
        return path
    for path in sorted(checkpoints.iterdir(), key=lambda item: item.name, reverse=True):
        if not path.is_dir() or path.is_symlink():
            continue
        try:
            _metadata(path)
        except (ValueError, OSError, json.JSONDecodeError):
            continue
        return path
    raise ValueError("No checkpoint with valid metadata was found")


def _plan(root, checkpoint, metadata):
    files = {}

    def add(relative, source, expected, origin):
        safe = _relative(relative)
        destination = safe.as_posix()
        if destination in files or destination in ("state.json", "README.md"):
            raise ValueError(f"Duplicate snapshot path: {destination}")
        _no_symlink_components(source, checkpoint if origin != "current_workflow" else root)
        if not source.is_file() or digest(source) != expected:
            raise ValueError(f"Checkpoint/current helper hash mismatch: {source}")
        files[destination] = {"source": source, "sha256": expected, "origin": origin}

    for relative, expected in sorted(metadata["copied_inputs_sha256"].items()):
        add(relative, checkpoint / _relative(relative), expected, "checkpoint_input")
    tools = checkpoint / "tools"
    if tools.is_dir():
        _no_symlink_components(tools, checkpoint)
        for source in sorted(tools.glob("*.py")):
            relative = f"tools/{source.name}"
            if relative not in files:
                add(relative, source, digest(source), "checkpoint_tool")
    powershell = checkpoint / "decomp.ps1"
    if powershell.is_file():
        add("decomp.ps1", powershell, digest(powershell), "checkpoint_script")
    for name in HELPERS:
        source = root / "tools" / name
        if source.is_file():
            add(f"current_workflow/tools/{name}", source, digest(source), "current_workflow")
            if f"tools/{name}" not in files:
                add(f"tools/{name}", source, digest(source), "current_workflow")
    for relative in CURRENT_DOCUMENTS:
        source = root / relative
        if source.is_file():
            add(relative, source, digest(source), "current_workflow")
    for name in VENDORED_TOOLS:
        vendor = root / ".tools" / name
        if not vendor.is_dir():
            continue
        _no_symlink_components(vendor, root)
        for directory, subdirectories, filenames in os.walk(vendor, followlinks=False):
            base = Path(directory)
            subdirectories[:] = sorted(part for part in subdirectories if part not in EXCLUDED_VENDOR_PARTS)
            for part in subdirectories:
                _no_symlink_components(base / part, root)
            for filename in sorted(filenames):
                if filename.endswith(".pyc") or filename in EXCLUDED_VENDOR_PARTS:
                    continue
                source = base / filename
                relative = source.relative_to(root).as_posix()
                add(relative, source, digest(source), "current_workflow")
    return files


def _readme(checkpoint, files):
    expected = list(CURRENT_DOCUMENTS)
    expected += [f"current_workflow/tools/{name}" for name in HELPERS]
    expected += [f".tools/{name}/{name if name == 'm2c' else 'permuter'}.py" for name in VENDORED_TOOLS]
    missing = [name for name in expected if name not in files]
    current_count = sum(entry["origin"] == "current_workflow" for entry in files.values())
    lines = ["# Isolated decompilation worker snapshot", "", f"Baseline: {checkpoint.name}",
             "", "Recorded inputs and saved tools came from the immutable verified checkpoint.",
             "Current-session documents and vendored tools are at their functional root-relative paths.",
             "Current-session helper copies are in `current_workflow/tools`; all current copies are listed with SHA-256 and origin in `state.json`.",
             "If a helper is absent from checkpoint `tools/`, a current copy is also placed there. Checkpoint scripts are never overwritten.",
             "To invoke a newer helper when a checkpoint has an older namesake, set `PYTHONPATH=tools` and run its `current_workflow/tools` copy.",
             "This directory is a snapshot, not a Git checkout. It contains no disc image or build output.",
             "No runtime virtual environment was copied. An externally installed venv interpreter may be used read-only.",
             "Use private diagnostics here; integrate reviewed changes into the parent workspace separately.",
             "", f"Current-session files copied: {current_count}.", "",
             "Unavailable current-session components:"]
    lines.extend(f"- `{name}`" for name in missing)
    if not missing:
        lines.append("- None")
    return "\n".join(lines) + "\n"


def _plan_text(name, checkpoint):
    return (f"# {name} worker plan\n\n"
            f"Verified baseline: `{checkpoint.name}`.\n\n"
            "Source ownership: edit only files explicitly assigned to this worker by the parent. "
            "Keep shared headers, profiles, linker files, retail ASM, and SDK bodies under parent ownership.\n\n"
            "Use private probes and preserve readable failed attempts. A local score or byte comparison "
            "is diagnostic; return source hashes and evidence to the parent for the complete linked gate.\n")


def _expected_state(root, checkpoint, files, readme, plan):
    return {
        "schema": 1,
        "baseline": checkpoint.relative_to(root).as_posix(),
        "checkpoint_metadata_sha256": digest(checkpoint / "checkpoint.json"),
        "readme_sha256": hashlib.sha256(readme.encode("utf-8")).hexdigest(),
        "plan_sha256": hashlib.sha256(plan.encode("utf-8")).hexdigest(),
        "files": {name: {"sha256": entry["sha256"], "origin": entry["origin"]}
                  for name, entry in sorted(files.items())},
    }


def _validate_existing(destination, expected):
    if not destination.is_dir() or destination.is_symlink():
        raise ValueError(f"Existing worker path is not a normal directory: {destination}")
    state_path = destination / "state.json"
    if not state_path.is_file() or state_path.is_symlink():
        raise ValueError(f"Existing worker lacks state metadata: {destination}")
    state = json.loads(state_path.read_text(encoding="utf-8"))
    if state != expected:
        raise ValueError(f"Existing worker baseline or inventory changed: {destination}")
    expected_paths = set(expected["files"]) | {"state.json", "README.md", "PLAN.md"}
    actual = set()
    for path in destination.rglob("*"):
        _no_symlink_components(path, destination)
        if path.is_file():
            actual.add(path.relative_to(destination).as_posix())
    if actual != expected_paths:
        raise ValueError(f"Existing worker file inventory changed: {destination}")
    for relative, entry in expected["files"].items():
        if digest(destination / _relative(relative)) != entry["sha256"]:
            raise ValueError(f"Existing worker file changed: {relative}")
    if digest(destination / "README.md") != expected["readme_sha256"]:
        raise ValueError("Existing worker README changed")
    if digest(destination / "PLAN.md") != expected["plan_sha256"]:
        raise ValueError("Existing worker PLAN changed")


def prepare(name, checkpoint=None, *, root=ROOT):
    """Return (status, path). Reuse is read-only and never resets changed work."""
    root = Path(root).resolve()
    _name(name)
    baseline = _checkpoint(root, checkpoint)
    metadata = _metadata(baseline)
    files = _plan(root, baseline, metadata)
    readme = _readme(baseline, files)
    plan = _plan_text(name, baseline)
    state = _expected_state(root, baseline, files, readme, plan)
    workers = root / "analysis" / "workers"
    destination = workers / name
    _inside(destination, workers)
    if destination.exists() or destination.is_symlink():
        _validate_existing(destination, state)
        return "reused", destination
    workers.mkdir(parents=True, exist_ok=True)
    # mkdir is exclusive. A failed copy leaves an invalid snapshot for review;
    # a later invocation cannot erase, reset, or adopt it silently.
    destination.mkdir(exist_ok=False)
    for relative, entry in files.items():
        target = destination / _relative(relative)
        _inside(target, destination)
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(entry["source"], target)
        if digest(target) != entry["sha256"] or digest(entry["source"]) != entry["sha256"]:
            raise ValueError(f"Input changed during worker snapshot: {relative}")
    (destination / "README.md").write_bytes(readme.encode("utf-8"))
    (destination / "PLAN.md").write_bytes(plan.encode("utf-8"))
    (destination / "state.json").write_text(json.dumps(state, indent=2) + "\n", encoding="utf-8")
    _validate_existing(destination, _expected_state(root, baseline, files, readme, plan))
    return "created", destination


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    command = commands.add_parser("prepare", help="create or validate an isolated worker")
    command.add_argument("name")
    command.add_argument("--checkpoint", help="direct child of analysis/checkpoints; defaults to newest valid metadata")
    arguments = parser.parse_args(argv)
    try:
        status, path = prepare(arguments.name, arguments.checkpoint)
    except (OSError, ValueError, json.JSONDecodeError) as error:
        parser.exit(2, f"worker_workspace: {error}\n")
    print(json.dumps({"status": status, "path": str(path)}))
    return 0


if __name__ == "__main__":
    sys.exit(main())
