"""Extract Rumble Arena's VFS2 archive, including ZP00 compressed files.

Format reference: DarkChaosBlast's digimon_vfs2.bms, distributed in the
MIT-licensed bigger0gamer/TrueOGEdition repository. See docs/references.md.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import struct
import zlib


def decompress_limited(data: bytes, maximum: int) -> bytes:
    decoder = zlib.decompressobj()
    result = decoder.decompress(data, maximum + 1)
    if len(result) > maximum or decoder.unconsumed_tail or not decoder.eof:
        raise ValueError("Compressed VFS2 content is oversized or truncated")
    return result


def extract(archive: Path, output: Path, only: set[str] | None = None) -> list[dict]:
    data = archive.read_bytes()
    if len(data) < 0x800 or data[:4] != b"VFS2":
        raise ValueError("Not a VFS2 archive")
    count, base_sector, info_size = struct.unpack_from("<III", data, 4)
    base = base_sector * 0x800
    if not 0x800 <= info_size <= base <= len(data):
        raise ValueError("Invalid VFS2 header bounds")
    if not 1 <= count <= 100000:
        raise ValueError("Unreasonable VFS2 record count")
    table = decompress_limited(data[0x800:info_size], 64 * 1024 * 1024)
    names_base = count * 12
    if names_base > len(table):
        raise ValueError("Truncated VFS2 file table")
    output = (Path.cwd() / output).resolve() if not output.is_absolute() else output.resolve()
    result = []
    visited = set()
    filenames = set()

    def record(pos: int):
        if pos < 0 or pos % 12 or pos + 12 > names_base:
            raise ValueError("VFS2 directory offset outside file table")
        offset, size = struct.unpack_from("<II", table, pos)
        name_pos = names_base + int.from_bytes(table[pos + 8:pos + 11], "little")
        if not names_base <= name_pos < len(table):
            raise ValueError("VFS2 name outside string table")
        end = table.find(b"\0", name_pos)
        if end < 0:
            raise ValueError("Unterminated VFS2 name")
        name = table[name_pos:end].decode("ascii")
        return offset, size, name, table[pos + 11]

    def walk(pos: int, entries: int, parent: tuple[str, ...], depth: int = 0):
        if depth > 64 or entries > count:
            raise ValueError("Invalid VFS2 directory depth or size")
        for index in range(entries):
            here = pos + index * 12
            if here in visited:
                raise ValueError("Repeated VFS2 directory record")
            visited.add(here)
            offset, size, name, flags = record(here)
            if name == "..":
                continue
            if name in ("", "."):
                if name != "." or not flags & 8 or offset != here:
                    raise ValueError("Invalid VFS2 filename")
                parts = parent
            else:
                if any(c in name for c in '/\\:'):
                    raise ValueError("Unsafe VFS2 filename")
                parts = parent + (name,)
            if flags & 8:
                if offset == here:
                    walk(offset + 12, size - 1, parts, depth + 1)
                    return
                walk(offset, size, parts, depth + 1)
                continue
            path = "/".join(parts)
            if not path or path.lower() in filenames:
                raise ValueError("Empty or duplicate VFS2 output path")
            filenames.add(path.lower())
            start = base + offset * 0x800
            if start < base or start + size > len(data):
                raise ValueError("VFS2 file outside archive")
            if only is not None and path.lower() not in only:
                continue
            payload = data[start:start + size]
            compressed = payload.startswith(b"ZP00")
            if compressed:
                if len(payload) < 8:
                    raise ValueError("Truncated ZP00 header")
                unpacked_size = struct.unpack_from("<I", payload, 4)[0]
                if unpacked_size > 64 * 1024 * 1024:
                    raise ValueError("Unreasonable decompressed file size")
                payload = decompress_limited(payload[8:], unpacked_size)
                if len(payload) != unpacked_size:
                    raise ValueError("ZP00 decompressed size mismatch")
            destination = (output / path).resolve()
            if not destination.is_relative_to(output):
                raise ValueError("VFS2 output escapes extraction directory")
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_bytes(payload)
            result.append(dict(path=path, archive_offset=start, stored_size=size,
                               size=len(payload), flags=flags, compressed=compressed,
                               sha1=hashlib.sha1(payload).hexdigest(),
                               sha256=hashlib.sha256(payload).hexdigest()))

    walk(0, 1, ())
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("archive", type=Path)
    parser.add_argument("--output", type=Path, default=Path("extracted/us/vfs"))
    parser.add_argument("--manifest", type=Path, default=Path("config/us/vfs.json"))
    args = parser.parse_args()
    files = extract(args.archive, args.output)
    manifest = dict(format="VFS2", files=files)
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    args.manifest.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(f"Extracted {len(files)} files, {sum(f['size'] for f in files):,} bytes")
    for entry in files:
        if entry["path"].lower().endswith(".bin"):
            print(f"{entry['path']}: {entry['size']:#x} bytes; compressed={entry['compressed']}")


if __name__ == "__main__":
    main()
