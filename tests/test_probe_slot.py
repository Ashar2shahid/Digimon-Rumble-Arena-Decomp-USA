"""Relocation diagnostics must retain instruction opcode and register checks."""
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).absolute().parent.parent / "tools"))
from probe_slot import compare_words, original_size


def word(value):
    return value.to_bytes(4, "little")


class ProbeSlotTests(unittest.TestCase):
    def test_current_source_selects_complete_function_over_old_sector_split(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for slot, size in (("17800", "0x204"), ("17804", "0x25C")):
                assembly = root / "asm/us/main/nonmatchings" / slot / "func_800275FC.s"
                assembly.parent.mkdir(parents=True)
                assembly.write_text("nonmatching func_800275FC, " + size + "\n")
            source = root / "src/engine/17804.c"
            source.parent.mkdir(parents=True)
            source.write_text('INCLUDE_ASM("asm/us/main/nonmatchings/17804", func_80027214);\n')
            with patch("probe_slot.ROOT", root):
                self.assertEqual(original_size("main", "func_800275FC", source), 604)

    def test_i_relocation_masks_only_immediate(self):
        self.assertEqual(compare_words(word(0x3C028000), word(0x3C020123), {0}), [])

    def test_i_relocation_retains_register(self):
        self.assertTrue(compare_words(word(0x3C038000), word(0x3C020123), {0}))

    def test_j_relocation_masks_target(self):
        self.assertEqual(compare_words(word(0x0C001234), word(0x0C056789), {0}), [])

    def test_j_relocation_retains_opcode(self):
        self.assertTrue(compare_words(word(0x08001234), word(0x0C056789), {0}))

    def test_nonrelocated_immediate_must_match(self):
        self.assertTrue(compare_words(word(0x3C028000), word(0x3C020123), set()))


if __name__ == "__main__":
    unittest.main()
