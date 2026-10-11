"""Record the PS-X EXE header and printable strings with original addresses."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import struct


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("exe", type=Path)
    parser.add_argument("--output", type=Path, default=Path("analysis/us"))
    args = parser.parse_args()
    data = args.exe.read_bytes()
    if data[:8] != b"PS-X EXE" or len(data) < 0x800:
        raise ValueError("Not a PS-X executable")
    fields = {name: struct.unpack_from("<I", data, offset)[0] for name, offset in (
        ("entry", 0x10), ("gp", 0x14), ("load_address", 0x18), ("load_size", 0x1C),
        ("bss_address", 0x28), ("bss_size", 0x2C), ("stack_address", 0x30), ("stack_size", 0x34))}
    if fields["load_size"] + 0x800 != len(data):
        raise ValueError("Header payload size disagrees with file size")
    fields.update(file=args.exe.name, file_size=len(data), sha1=hashlib.sha1(data).hexdigest())
    args.output.mkdir(parents=True, exist_ok=True)
    (args.output / "exe.json").write_text(json.dumps(fields, indent=2) + "\n", encoding="utf-8")
    strings = []
    for match in re.finditer(rb"[ -~]{6,}", data[0x800:]):
        offset = match.start() + 0x800
        strings.append({"offset": offset, "address": fields["load_address"] + match.start(),
                        "text": match.group().decode("ascii")})
    (args.output / "strings.json").write_text(json.dumps(strings, indent=2) + "\n", encoding="utf-8")
    for name, value in fields.items():
        print(f"{name}: {value:#x}" if isinstance(value, int) else f"{name}: {value}")
    print(f"Printable strings: {len(strings)}")
    for item in strings:
        if re.search(r"gcc|psyq|codewarrior|hudson|\.c(?:pp)?$|vfs|version|cdrom", item["text"], re.I):
            print(f"{item['address']:08X}: {item['text']}")


if __name__ == "__main__":
    main()
