"""Inspect candidate overlay code edges. These heuristics require manual review."""
from pathlib import Path
import struct
import rabbitizer

for path in sorted(Path("extracted/us/vfs/bin").glob("*.bin")):
    data = path.read_bytes()
    first = next(i for i in range(0, len(data), 4)
                 if struct.unpack_from("<I", data, i)[0] >> 16 == 0x27BD
                 and struct.unpack_from("<I", data, i)[0] & 0x8000)
    last = data.rfind(bytes.fromhex("0800e003"))
    base = 0x800D3B00 if path.stem.startswith("st") else 0x800643C0
    print(f"\n{path.name}: candidate {first:#x}..{last+8:#x}")
    for start, end in ((max(0, first-48), first+8), (last, min(len(data), last+56))):
        for i in range(start, end, 4):
            word = struct.unpack_from("<I", data, i)[0]
            inst = rabbitizer.Instruction(word, base+i, rabbitizer.InstrCategory.R3000GTE)
            print(f"{i:06x} {base+i:08x} {word:08x} {inst.disassemble()}")
