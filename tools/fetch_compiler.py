"""Fetch a hash-pinned, Linux PS1 compiler rebuilt by decompals/old-gcc."""
import argparse
import hashlib
from pathlib import Path
import tarfile
import urllib.request

HASHES = {
    "2.7.2": "500a459b3485e885a8d302cac23c2a4632f3900e03a09153f6190699fd723571",
    "2.8.1": "f6f6e883942d4d3289d048236c672e71ed410e546aaae8ff655952f1567e1be0",
    # Same release archive pinned by ReGame-Labs/dtbe_decomp at a54d64e.
    "2.95.2": "932ed3669710a82b12570c29c46ff42989b6505b2af10db84d4551d55dfc0b1c",
}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("version", choices=HASHES, default="2.8.1", nargs="?")
    args = parser.parse_args()
    name = f"gcc-{args.version}-psx.tar.gz"
    path = Path(".tools") / name
    path.parent.mkdir(exist_ok=True)
    if not path.exists():
        url = f"https://github.com/decompals/old-gcc/releases/download/0.17/{name}"
        with urllib.request.urlopen(url, timeout=60) as response:
            path.write_bytes(response.read())
    if hashlib.sha256(path.read_bytes()).hexdigest() != HASHES[args.version]:
        raise ValueError(f"Compiler archive hash mismatch: {path}")
    destination = Path(".tools") / f"gcc-{args.version}"
    destination.mkdir(exist_ok=True)
    with tarfile.open(path) as archive:
        archive.extractall(destination, filter="data")
    print(f"Verified compiler archive and extracted to {destination}")


if __name__ == "__main__":
    main()
