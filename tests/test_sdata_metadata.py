"""External small-data metadata must not define or allocate game data."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).absolute().parent.parent / "tools"))
from build_dra import append_external_sdata_metadata


class ExternalSmallDataTests(unittest.TestCase):
    def test_valid_external_adds_size_only(self):
        original = ".extern D_800641A8, 4\n.text\n"
        result = append_external_sdata_metadata(original, {"D_800641A8": 4}, 8)
        self.assertEqual(result, original + "\n.sdata\n.size D_800641A8,4\n.text\n")
        self.assertNotIn("D_800641A8:", result)

    def test_without_metadata_preserves_assembly(self):
        original = ".text\n.globl function\nfunction:\n jr $ra\n nop\n"
        self.assertEqual(append_external_sdata_metadata(original, {}, 0), original)

    def test_unknown_external_cannot_be_added(self):
        with self.assertRaisesRegex(ValueError, "Missing or inconsistent"):
            append_external_sdata_metadata(".text\n", {"D_800641A8": 4}, 8)

    def test_mismatched_external_size_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "Missing or inconsistent"):
            append_external_sdata_metadata(".extern D_800641A8,2\n", {"D_800641A8": 4}, 8)

    def test_wrong_compiler_limit_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "compiler -G limit"):
            append_external_sdata_metadata(".extern D_800641A8,4\n", {"D_800641A8": 4}, 0)

    def test_already_defined_data_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "already defined"):
            append_external_sdata_metadata(".extern D_800641A8,4\nD_800641A8:\n.word 0\n", {"D_800641A8": 4}, 8)


if __name__ == "__main__":
    unittest.main()
