"""Extract PS1 code inputs from ISO9660 in a 2048-byte ISO or raw BIN/CUE.

Only normal Form 1 files are extracted by default. XA movie/audio streams
remain on the original disc; --streams preserves their full 2336-byte sectors.
No original image is modified.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re
import struct


def digest_file(path: Path) -> dict[str, str]:
    hashes = {name: hashlib.new(name) for name in ("sha1", "sha256")}
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            for value in hashes.values():
                value.update(block)
    return {name: value.hexdigest() for name, value in hashes.items()}


class Disc:
    def __init__(self, path: Path):
        if not path.is_absolute():
            path = Path.cwd() / path
        self.path = path.resolve()
        self.sector_offset = 0
        if path.suffix.lower() == ".cue":
            cue = path.read_text(encoding="utf-8-sig")
            files = re.findall(r'^\s*FILE\s+"([^"]+)"\s+BINARY\s*$', cue, re.M | re.I)
            tracks = re.findall(r'^\s*TRACK\s+\d+\s+(\S+)\s*$', cue, re.M | re.I)
            indices = re.findall(r'^\s*INDEX\s+01\s+(\d+):(\d+):(\d+)\s*$', cue, re.M | re.I)
            if len(files) != 1 or len(tracks) != 1 or len(indices) != 1:
                raise ValueError("Only one-file, one-data-track CUE sheets are supported")
            if tracks[0].upper() not in ("MODE2/2352", "MODE1/2352", "MODE1/2048"):
                raise ValueError(f"Unsupported track: {tracks[0]}")
            candidate = (path.parent / files[0]).resolve()
            if not candidate.is_relative_to(path.parent.resolve()):
                raise ValueError("CUE file points outside its directory")
            self.path = candidate
            minute, second, frame = map(int, indices[0])
            if second >= 60 or frame >= 75:
                raise ValueError("Invalid CUE index")
            self.sector_offset = (minute * 60 + second) * 75 + frame
        self.stream = self.path.open("rb")
        self.size = self.path.stat().st_size
        self.sector_size = 0
        self.payload_offset = 0
        for sector_size, offset in ((2352, 24), (2352, 16), (2048, 0)):
            self.stream.seek((self.sector_offset + 16) * sector_size + offset)
            if self.stream.read(7) == b"\x01CD001\x01":
                self.sector_size, self.payload_offset = sector_size, offset
                break
        if not self.sector_size:
            raise ValueError("No supported ISO9660 primary volume descriptor")
        if self.size % self.sector_size:
            raise ValueError("Disc size is not a whole number of sectors")
        self.pvd = self.read_extent(16, 2048)
        self.volume = self.pvd[40:72].decode("ascii", "replace").strip()
        self.volume_sectors = struct.unpack_from("<I", self.pvd, 80)[0]
        available = self.size // self.sector_size - self.sector_offset
        if self.volume_sectors > available:
            raise ValueError("ISO volume extends beyond the image")

    def read_sector(self, lba: int) -> bytes:
        if lba < 0 or (lba + self.sector_offset + 1) * self.sector_size > self.size:
            raise ValueError(f"Sector outside image: {lba}")
        self.stream.seek((lba + self.sector_offset) * self.sector_size)
        block = self.stream.read(self.sector_size)
        if len(block) != self.sector_size:
            raise ValueError(f"Truncated sector: {lba}")
        return block

    def read_extent(self, lba: int, size: int) -> bytes:
        return b"".join(
            self.read_sector(lba + i)[self.payload_offset:self.payload_offset + 2048]
            for i in range((size + 2047) // 2048)
        )[:size]

    def files(self) -> list[dict]:
        root = self.pvd[156:190]
        root_lba = struct.unpack_from("<I", root, 2)[0]
        root_size = struct.unpack_from("<I", root, 10)[0]
        found: list[dict] = []
        seen: set[tuple[int, int]] = set()

        def visit(lba: int, size: int, prefix: str = "") -> None:
            if (lba, size) in seen:
                raise ValueError("Repeated directory extent")
            seen.add((lba, size))
            block = self.read_extent(lba, size)
            pos = 0
            while pos < len(block):
                length = block[pos]
                if not length:
                    pos = (pos // 2048 + 1) * 2048
                    continue
                if length < 34 or pos + length > len(block) or pos % 2048 + length > 2048:
                    raise ValueError("Invalid ISO directory record")
                record = block[pos:pos + length]
                pos += length
                name_length = record[32]
                if 33 + name_length > length:
                    raise ValueError("Truncated ISO filename")
                raw_name = record[33:33 + name_length]
                if raw_name in (b"\x00", b"\x01"):
                    continue
                name = raw_name.decode("ascii").split(";")[0]
                if name in ("", ".", "..") or any(c in name for c in '/\\:'):
                    raise ValueError("Unsafe ISO filename")
                extent = struct.unpack_from("<I", record, 2)[0]
                file_size = struct.unpack_from("<I", record, 10)[0]
                if record[25] & 0x80:
                    raise ValueError("Multi-extent files are not yet supported")
                if record[26] or record[27]:
                    raise ValueError("Interleaved ISO files are not yet supported")
                if extent + (file_size + 2047) // 2048 > self.volume_sectors:
                    raise ValueError("File extent outside ISO volume")
                fullname = prefix + name
                if record[25] & 2:
                    visit(extent, file_size, fullname + "/")
                else:
                    found.append({"path": fullname, "lba": extent, "iso_size": file_size})
        visit(root_lba, root_size)
        return found

    def extract(self, entry: dict, output: Path, streams: bool = False) -> dict:
        path = (output / entry["path"]).resolve()
        if not path.is_relative_to(output.resolve()):
            raise ValueError("Output path escapes extraction directory")
        sectors = (entry["iso_size"] + 2047) // 2048
        form2 = False
        if self.sector_size == 2352 and self.payload_offset == 24:
            form2 = any(self.read_sector(entry["lba"] + i)[18] & 0x20 for i in range(sectors))
        result = dict(entry, xa_form2=form2)
        if form2 and not streams:
            result["extracted"] = False
            return result
        path.parent.mkdir(parents=True, exist_ok=True)
        with path.open("wb") as dest:
            left = entry["iso_size"]
            for i in range(sectors):
                raw = self.read_sector(entry["lba"] + i)
                if form2:
                    dest.write(raw[16:])
                else:
                    payload = raw[self.payload_offset:self.payload_offset + min(2048, left)]
                    dest.write(payload)
                    left -= len(payload)
        result.update(extracted=True, output_size=path.stat().st_size, **digest_file(path))
        if form2:
            result["storage"] = "2336-byte XA sectors, including subheaders and EDC"
        return result


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", type=Path)
    parser.add_argument("--output", type=Path, default=Path("extracted/us/disc"))
    parser.add_argument("--manifest", type=Path, default=Path("config/us/disc.json"))
    parser.add_argument("--streams", action="store_true")
    args = parser.parse_args()
    if not args.output.is_absolute():
        args.output = Path.cwd() / args.output
    disc = Disc(args.image)
    try:
        files = [disc.extract(entry, args.output, args.streams) for entry in disc.files()]
        manifest = {
            "volume_id": disc.volume,
            "image": disc.path.name,
            "image_size": disc.size,
            "image_hashes": digest_file(disc.path),
            "sector_size": disc.sector_size,
            "payload_offset": disc.payload_offset,
            "track_sector_offset": disc.sector_offset,
            "files": files,
        }
        args.manifest.parent.mkdir(parents=True, exist_ok=True)
        args.manifest.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
        for file in files:
            print(f"{file['path']}: {'extracted' if file['extracted'] else 'XA stream left on disc'} ({file['iso_size']} ISO bytes)")
        print(f"Volume {disc.volume}; manifest {args.manifest}")
    finally:
        disc.stream.close()


if __name__ == "__main__":
    main()
