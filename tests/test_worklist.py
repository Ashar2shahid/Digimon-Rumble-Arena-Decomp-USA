"""Opaque game data and false splits must remain visible for inventory review."""
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).absolute().parent.parent / "tools"))
import worklist


class WorklistTests(unittest.TestCase):
    def test_data_and_assembly_boundaries_are_not_scheduled_as_easy_c(self):
        temporary_root = worklist.ROOT / "analysis/test-temp"
        temporary_root.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(dir=temporary_root) as directory:
            root = Path(directory)
            rows = [dict(name=f"func_800100{i:02X}", address=0x80010000 + i, kind=kind)
                    for i, kind in [(0, "func"), (4, "asm"), (8, "data"),
                                    (12, "internal"), (16, "data"), (20, "asm")]]
            definitions = {rows[5]["name"]: dict(source="src/engine/test.c", category="ordinary_c")}
            assembly = root / "asm/us/main"
            assembly.mkdir(parents=True)
            for row in rows:
                (assembly / (row["name"] + ".s")).write_text(
                    f"nonmatching {row['name']}, 4\n/* 0 {row['address']:08X} 00000000 */ nop\n")
            with patch.object(worklist, "ROOT", root), patch.object(worklist, "UNITS", ["main"]), \
                    patch.object(worklist, "manifest", return_value=rows), \
                    patch.object(worklist, "source_functions", return_value=(definitions, {}, [])), \
                    patch.object(worklist, "sdk_symbols", return_value={("main", rows[4]["name"])}):
                result = worklist.build_worklist()
            candidates = {row["function"]: row for row in result["candidates"]}
            self.assertEqual(set(candidates), {rows[i]["name"] for i in (0, 1, 2, 5)})
            self.assertEqual(candidates[rows[0]["name"]]["difficulty"], "straightforward_candidate")
            for i in (1, 2, 5):
                row = candidates[rows[i]["name"]]
                self.assertEqual(row["work_type"], "review_non_function_boundary")
                self.assertEqual(row["difficulty"], "review")
                self.assertEqual(row["suggested_model"], "gpt-6.1-sol medium")


if __name__ == "__main__":
    unittest.main()
