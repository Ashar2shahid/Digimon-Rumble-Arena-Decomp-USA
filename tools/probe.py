"""Temporary exploratory analysis; results are not confirmed source boundaries."""
import json
from pathlib import Path
import struct

d = Path('extracted/us/disc/SLUS_014.04').read_bytes()
strings = json.loads(Path('analysis/us/strings.json').read_text())
for s in strings:
    if 0x80019000 <= s['address'] <= 0x8001af10 or s['address'] >= 0x8005d000:
        print(hex(s['address']), s['text'])
for o in range(0x800, 0x65000, 0x1000):
    w = struct.unpack_from('<1024I', d, o)
    returns = sum(x == 0x03e00008 for x in w)
    prologues = sum(x >> 16 == 0x27bd and x & 0x8000 != 0 for x in w)
    jals = sum(x >> 26 == 3 for x in w)
    zeros = w.count(0)
    print(f'{o+0x8000f800:08x}: jrra={returns:2}, prologues={prologues:2}, jals={jals:3}, zeros={zeros:4}')
