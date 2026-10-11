"""Reviewed internal labels must survive future manifest regeneration."""
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).absolute().parent.parent / "tools"))
import source_inventory


class BoundaryOverrideTests(unittest.TestCase):
    def check_manifest(self, kind):
        base = source_inventory.ROOT / "analysis/test-temp"
        base.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(dir=base) as directory:
            root = Path(directory)
            (root / "config/us/functions").mkdir(parents=True)
            (root / "config/us/functions/main.txt").write_text(f"func_80010000 80010000 {kind}\n")
            correction = dict(unit="main", symbol="func_80010000", address="0x80010000", kind="internal")
            (root / "config/us/boundary_overrides.json").write_text(json.dumps(dict(overrides=[correction])))
            with patch.object(source_inventory, "ROOT", root):
                return source_inventory.manifest("main")

    def test_reviewed_internal_label_is_preserved(self):
        self.assertEqual(self.check_manifest("internal")[0]["kind"], "internal")

    def test_regeneration_cannot_restore_false_function(self):
        with self.assertRaisesRegex(ValueError, "boundary correction was lost"):
            self.check_manifest("func")


if __name__ == "__main__":
    unittest.main()
