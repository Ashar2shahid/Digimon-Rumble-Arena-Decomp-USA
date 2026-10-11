#!/usr/bin/env python3
"""Install the exact Windows matching toolchain from pinned public downloads."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tarfile
import tempfile
import urllib.request

REPOSITORY = Path(__file__).resolve().parent.parent

def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()

def checked(data: bytes, expected: str, name: str) -> bytes:
    actual = digest(data)
    if actual != expected:
        raise ValueError(f"{name}: SHA-256 mismatch: expected {expected}, found {actual}")
    return data

def destination(root: Path, relative: str) -> Path:
    path = (root / relative).resolve()
    if not path.is_relative_to(root) or path == root:
        raise ValueError(f"Unsafe manifest destination: {relative}")
    return path

def fetch(url: str, sha256: str, cache: Path, fresh: bool) -> bytes:
    path = cache / sha256
    if path.exists() and not fresh:
        return checked(path.read_bytes(), sha256, str(path))
    print(f"Download {url}", flush=True)
    request = urllib.request.Request(url, headers={"User-Agent": "dra-us-toolchain-setup/1"})
    with urllib.request.urlopen(request, timeout=60) as response:
        data = checked(response.read(), sha256, url)
    cache.mkdir(parents=True, exist_ok=True)
    temp = cache / (sha256 + ".part")
    temp.write_bytes(data)
    temp.replace(path)
    return data

def existing(path: Path, expected: str) -> bool:
    if not path.exists():
        return False
    if not path.is_file():
        raise ValueError(f"Expected a file: {path}")
    checked(path.read_bytes(), expected, str(path))
    return True

def install(path: Path, data: bytes, expected: str) -> None:
    checked(data, expected, str(path))
    if existing(path, expected):
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    staged = path.with_name(path.name + ".setup-part")
    if staged.exists():
        raise ValueError(f"Unfinished setup file exists; inspect and remove it: {staged}")
    staged.write_bytes(data)
    staged.replace(path)

def entries(manifest: dict) -> list[dict]:
    result = list(manifest["files"])
    result += [entry for archive in manifest["archives"] for entry in archive["members"]]
    result += manifest["maspsx"]["files"]
    return result

def verify(root: Path, manifest: dict) -> int:
    failures = []
    for entry in entries(manifest):
        try:
            if not existing(destination(root, entry["path"]), entry["sha256"]):
                failures.append(f"Missing: {entry['path']}")
        except ValueError as error:
            failures.append(str(error))
    if failures:
        print("\n".join(failures), file=sys.stderr)
        return 1
    print(f"Verified {len(entries(manifest))} exact toolchain files in {root}")
    return 0

def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=REPOSITORY, help="install destination, including an empty audit directory")
    parser.add_argument("--verify", action="store_true", help="check installed file hashes without network access")
    parser.add_argument("--fresh-download", action="store_true", help="download every input again instead of using verified cached/installed files")
    args = parser.parse_args()
    root = args.root.resolve()
    manifest = json.loads((REPOSITORY / "docs/toolchain_manifest.json").read_text(encoding="utf-8"))
    if manifest["schema_version"] != 1:
        raise ValueError("Unsupported manifest version")
    if args.verify:
        return verify(root, manifest)
    if sys.platform != "win32":
        raise ValueError("This manifest installs Windows executables; use Windows Python 3.10 or newer")
    # Preflight all destinations before any change. Unknown files are preserved.
    for entry in entries(manifest):
        existing(destination(root, entry["path"]), entry["sha256"])
    patch_spec = manifest["maspsx"]
    patch = destination(REPOSITORY, patch_spec["patch"])
    checked(patch.read_bytes(), patch_spec["patch_sha256"], str(patch))
    cache = root / ".tools/downloads"
    for entry in manifest["files"]:
        path = destination(root, entry["path"])
        if args.fresh_download or not path.exists():
            install(path, fetch(entry["url"], entry["sha256"], cache, args.fresh_download), entry["sha256"])
    for archive in manifest["archives"]:
        if not args.fresh_download and all(destination(root, e["path"]).exists() for e in archive["members"]):
            continue
        data = fetch(archive["url"], archive["sha256"], cache, args.fresh_download)
        import io
        with tarfile.open(fileobj=io.BytesIO(data), mode="r:gz") as bundle:
            for entry in archive["members"]:
                member = bundle.getmember(entry["member"])
                if not member.isfile():
                    raise ValueError(f"Compiler member is not an ordinary file: {member.name}")
                stream = bundle.extractfile(member)
                if stream is None:
                    raise ValueError(f"Cannot read compiler member: {member.name}")
                install(destination(root, entry["path"]), stream.read(), entry["sha256"])
    if args.fresh_download or not all(destination(root, e["path"]).exists() for e in patch_spec["files"]):
        if not shutil.which("git"):
            raise ValueError("Install Git for Windows and make git available on PATH to apply the tracked maspsx patch")
        cache.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(prefix="maspsx-", dir=cache) as temporary:
            stage = Path(temporary)
            for entry in patch_spec["files"]:
                data = fetch(entry["source_url"], entry["source_sha256"], cache, args.fresh_download)
                target = stage / Path(entry["path"]).relative_to("external/maspsx")
                target.parent.mkdir(parents=True, exist_ok=True)
                target.write_bytes(data.replace(b"\r\n", b"\n"))
            # No Git checkout, original project, disc image or assembly is used here.
            subprocess.run(["git", "apply", "--check", str(patch)], cwd=stage, check=True)
            subprocess.run(["git", "apply", str(patch)], cwd=stage, check=True)
            for entry in patch_spec["files"]:
                source = stage / Path(entry["path"]).relative_to("external/maspsx")
                data = source.read_bytes().replace(b"\r\n", b"\n")
                if entry["line_endings"] == "CRLF":
                    data = data.replace(b"\n", b"\r\n")
                install(destination(root, entry["path"]), data, entry["sha256"])
    return verify(root, manifest)

if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, ValueError, subprocess.CalledProcessError, tarfile.TarError) as error:
        raise SystemExit(f"Toolchain setup failed: {error}")
