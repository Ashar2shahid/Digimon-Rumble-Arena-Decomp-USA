"""Disc-based setup must reject unsupported or changed inputs before installing."""
import hashlib
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import setup_game
from test_extraction import make_iso, make_vfs


def game_iso():
    image = bytearray(make_iso())
    image.extend(bytes(8 * 2048))
    struct.pack_into('<I', image, 16 * 2048 + 80, 32)
    def record(name, lba, size):
        name = name.encode() + b';1'
        data = bytearray((33 + len(name) + 1) & ~1)
        data[0] = len(data)
        struct.pack_into('<I', data, 2, lba)
        struct.pack_into('<I', data, 10, size)
        data[32] = len(name)
        data[33:33 + len(name)] = name
        return data
    directory = image[20 * 2048:20 * 2048 + 68]
    archive = make_vfs('bin')
    directory += record('SLUS_014.04', 22, 3) + record('A.VFS', 23, len(archive))
    image[20 * 2048:21 * 2048] = directory.ljust(2048, b'\0')
    image[23 * 2048:23 * 2048 + len(archive)] = archive
    return bytes(image)


class GameSetupTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        self.image = self.root / 'game.iso'
        self.image.write_bytes(game_iso())
        self.config = {
            'main': {'target': 'disks/us/SLUS_014.04', 'sha1': hashlib.sha1(b'raw').hexdigest()},
            'packed': {'target': 'assets/us/bin/packed.bin', 'sha1': hashlib.sha1(b'payload').hexdigest()},
        }

    def tearDown(self):
        self.temp.cleanup()

    def test_disc_setup_extracts_only_verified_code_inputs(self):
        with patch.dict(setup_game.build_dra.CONFIG, self.config, clear=True):
            result = setup_game.setup(self.image, self.root)
        self.assertEqual((self.root / 'disks/us/SLUS_014.04').read_bytes(), b'raw')
        self.assertEqual((self.root / 'assets/us/bin/packed.bin').read_bytes(), b'payload')
        self.assertEqual([f['path'] for f in result['archive_files']], ['bin/packed.bin'])
        self.assertFalse((self.root / 'raw.bin').exists())

    def test_wrong_revision_installs_no_game_inputs(self):
        self.config['main']['sha1'] = '0' * 40
        with patch.dict(setup_game.build_dra.CONFIG, self.config, clear=True):
            with self.assertRaisesRegex(ValueError, 'Unsupported executable'):
                setup_game.setup(self.image, self.root)
        self.assertFalse((self.root / 'disks').exists())
        self.assertFalse((self.root / 'assets').exists())

    def test_one_bad_overlay_installs_no_targets(self):
        self.config['packed']['sha1'] = '0' * 40
        with patch.dict(setup_game.build_dra.CONFIG, self.config, clear=True):
            with self.assertRaisesRegex(ValueError, 'Unsupported game revision'):
                setup_game.setup(self.image, self.root)
        self.assertFalse((self.root / 'disks').exists())

    def test_changed_destination_is_preserved_without_partial_install(self):
        destination = self.root / 'assets/us/bin/packed.bin'
        destination.parent.mkdir(parents=True)
        destination.write_bytes(b'changed')
        with patch.dict(setup_game.build_dra.CONFIG, self.config, clear=True):
            with self.assertRaisesRegex(ValueError, 'Refusing to overwrite'):
                setup_game.setup(self.image, self.root)
        self.assertEqual(destination.read_bytes(), b'changed')
        self.assertFalse((self.root / 'disks').exists())


if __name__ == '__main__':
    unittest.main()
