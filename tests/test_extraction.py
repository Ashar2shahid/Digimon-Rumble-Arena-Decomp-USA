"""Synthetic format tests: extraction, XA preservation, bounds, and safe paths."""
from pathlib import Path
import struct
import tempfile
import unittest
import zlib

from tools.extract_disc import Disc
from tools.extract_vfs import decompress_limited, extract


def make_vfs(directory_name="sub", declared_size=7, bad_file_offset=False):
    names = b".\0raw.bin\0" + directory_name.encode() + b"\0..\0packed.bin\0"
    packed = b"ZP00" + struct.pack("<I", declared_size) + zlib.compress(b"payload")

    def record(offset, size, name, flags):
        name_offset = names.index(name.encode() + b"\0")
        return struct.pack("<II", offset, size) + name_offset.to_bytes(3, "little") + bytes([flags])

    table = b"".join((record(0, 3, ".", 8), record(999 if bad_file_offset else 0, 3, "raw.bin", 0),
                      record(36, 3, directory_name, 8), record(36, 3, ".", 8),
                      record(0, 3, "..", 8), record(1, len(packed), "packed.bin", 0))) + names
    info = zlib.compress(table)
    data = bytearray(0x1800 + len(packed))
    struct.pack_into("<4sIII", data, 0, b"VFS2", 6, 2, 0x800 + len(info))
    data[0x800:0x800 + len(info)] = info
    data[0x1000:0x1003] = b"raw"
    data[0x1800:] = packed
    return data


def make_iso(raw=False, form2=False):
    sectors = [bytearray(2048) for _ in range(24)]
    pvd = sectors[16]
    pvd[:7] = b"\x01CD001\x01"
    pvd[40:72] = b"TEST".ljust(32, b" ")
    struct.pack_into("<I", pvd, 80, 24)

    def record(name, lba, size, flags):
        length = (33 + len(name) + 1) & ~1
        item = bytearray(length)
        item[0] = length
        struct.pack_into("<I", item, 2, lba)
        struct.pack_into(">I", item, 6, lba)
        struct.pack_into("<I", item, 10, size)
        struct.pack_into(">I", item, 14, size)
        item[25] = flags
        item[32] = len(name)
        item[33:33 + len(name)] = name
        return item

    root = record(b"\0", 20, 2048, 2)
    pvd[156:156 + len(root)] = root
    directory = root + record(b"\1", 20, 2048, 2) + record(b"TEST.DAT;1", 22, 3, 0)
    sectors[20][:len(directory)] = directory
    sectors[22][:3] = b"raw"
    if not raw:
        return b"".join(sectors)
    blocks = []
    for number, payload in enumerate(sectors):
        sector = bytearray(2352)
        sector[0:12] = b"\0" + b"\xff" * 10 + b"\0"
        sector[15] = 2
        sector[18] = sector[22] = 0x20 if form2 and number == 22 else 0x08
        sector[24:24 + 2048] = payload
        blocks.append(sector)
    return b"".join(blocks)


class VFSTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        self.archive = self.root / "A.VFS"
        self.output = self.root / "out"

    def tearDown(self):
        self.temp.cleanup()

    def test_nested_and_compressed_files(self):
        self.archive.write_bytes(make_vfs())
        before = self.archive.read_bytes()
        files = extract(self.archive, self.output)
        self.assertEqual({f["path"] for f in files}, {"raw.bin", "sub/packed.bin"})
        self.assertEqual((self.output / "raw.bin").read_bytes(), b"raw")
        self.assertEqual((self.output / "sub/packed.bin").read_bytes(), b"payload")
        self.assertTrue(next(f for f in files if f["path"].endswith("packed.bin"))["compressed"])
        self.assertEqual(self.archive.read_bytes(), before)

    def test_directory_traversal_rejected(self):
        self.archive.write_bytes(make_vfs("../escape"))
        with self.assertRaisesRegex(ValueError, "Unsafe"):
            extract(self.archive, self.output)
        self.assertFalse((self.root / "escape").exists())

    def test_extent_outside_archive_rejected(self):
        self.archive.write_bytes(make_vfs(bad_file_offset=True))
        with self.assertRaisesRegex(ValueError, "outside archive"):
            extract(self.archive, self.output)

    def test_wrong_decompressed_size_rejected(self):
        self.archive.write_bytes(make_vfs(declared_size=6))
        with self.assertRaises(ValueError):
            extract(self.archive, self.output)

    def test_truncated_and_oversized_zlib_rejected(self):
        encoded = zlib.compress(b"a" * 100)
        with self.assertRaises(ValueError):
            decompress_limited(encoded, 20)
        with self.assertRaises(ValueError):
            decompress_limited(encoded[:-2], 100)


class DiscTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)

    def tearDown(self):
        self.temp.cleanup()

    def test_iso_and_raw_form1_extract_identically(self):
        for raw in (False, True):
            path = self.root / ("test.bin" if raw else "test.iso")
            path.write_bytes(make_iso(raw))
            disc = Disc(path)
            try:
                entries = disc.files()
                self.assertEqual(len(entries), 1)
                result = disc.extract(entries[0], self.root / "output")
                self.assertFalse(result["xa_form2"])
                self.assertEqual((self.root / "output/TEST.DAT").read_bytes(), b"raw")
                with self.assertRaisesRegex(ValueError, "outside image"):
                    disc.read_sector(24)
            finally:
                disc.stream.close()

    def test_form2_is_skipped_or_preserved_as_sectors(self):
        path = self.root / "xa.bin"
        path.write_bytes(make_iso(raw=True, form2=True))
        disc = Disc(path)
        try:
            entry = disc.files()[0]
            result = disc.extract(entry, self.root / "output")
            self.assertFalse(result["extracted"])
            result = disc.extract(entry, self.root / "output", streams=True)
            self.assertEqual(result["output_size"], 2336)
            self.assertEqual((self.root / "output/TEST.DAT").read_bytes(), disc.read_sector(22)[16:])
        finally:
            disc.stream.close()

    def test_cue_cannot_reference_parent(self):
        cue = self.root / "test.cue"
        cue.write_text('FILE "../outside.bin" BINARY\n TRACK 01 MODE2/2352\n INDEX 01 00:00:00\n')
        with self.assertRaisesRegex(ValueError, "outside its directory"):
            Disc(cue)


if __name__ == "__main__":
    unittest.main()
