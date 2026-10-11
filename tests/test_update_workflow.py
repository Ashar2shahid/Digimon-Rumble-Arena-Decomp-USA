"""Progress provenance and difficult-function registry tests."""

import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch


sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import update_workflow as W  # noqa: E402


class WorkflowTests(unittest.TestCase):
    def setUp(self):
        base = Path(__file__).resolve().parents[1] / "analysis/test-temp"
        base.mkdir(parents=True, exist_ok=True)
        temporary = tempfile.TemporaryDirectory(dir=base)
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.progress = {"all_modules_verified": True, "inventory_problems": [],
                         "game_manifest_functions": 100, "verified_unconstrained_source": 40,
                         "source_categories": {"ordinary_c": 40},
                         "verified_unconstrained_percent": 40.0, "sdk_manifest_entries": 5}
        saved = self.root / "config/us/progress.json"
        saved.parent.mkdir(parents=True)
        saved.write_text(json.dumps(self.progress, sort_keys=True))

    def checkpoint(self, name, progress=None):
        directory = self.root / "analysis/checkpoints" / name
        directory.mkdir(parents=True)
        body = b"verified source\n"
        for base in (self.root, directory):
            source = base / "src/engine/a.c"
            source.parent.mkdir(parents=True, exist_ok=True)
            source.write_bytes(body)
        (directory / "checkpoint.json").write_text(json.dumps({
            "game_functions": 100, "unconstrained_source": 40,
            "recorded_inputs": 1, "copied_inputs_sha256": {"src/engine/a.c": hashlib.sha256(body).hexdigest()},
        }))
        (directory / "progress.json").write_text(json.dumps(progress or self.progress, sort_keys=True))
        return directory

    def test_matching_checkpoint_requires_exact_saved_progress(self):
        old = dict(self.progress, source_categories={"ordinary_c": 39, "assembly": 61})
        self.checkpoint("20261008T000000Z", old)
        with self.assertRaisesRegex(ValueError, "matching checkpoint"):
            W.matching_checkpoint(self.progress, self.root)
        current = self.checkpoint("20261008T010000Z")
        self.assertEqual(W.matching_checkpoint(self.progress, self.root)[0], current)
        (self.root / "src/engine/a.c").write_text("unverified change\n")
        with self.assertRaisesRegex(ValueError, "matching checkpoint"):
            W.matching_checkpoint(self.progress, self.root)
        (self.root / "src/engine/a.c").write_bytes(b"verified source\n")
        self.progress["inventory_problems"] = ["stale"]
        with self.assertRaisesRegex(ValueError, "verified progress"):
            W.matching_checkpoint(self.progress, self.root)

    def test_capped_session_without_historical_attempt_is_registered(self):
        function = "func_80021074"
        directory = self.root / "analysis/scratch/main" / function
        directory.mkdir(parents=True)
        (directory / "session.json").write_text(json.dumps({
            "cycle": 0, "target": {"unit": "main", "function": function, "source": "src/engine/11800.c", "calibration": False},
            "probes": [{"cycle": 0, "exit_code": None} for _ in range(10)], "seed": "scratch/seed.c",
        }))
        candidate = {"unit": "main", "function": function, "source_slot": "src/engine/11800.c",
                     "manifest_kind": "func", "attempts": []}
        with patch.object(W, "ROOT", self.root):
            rows = W.difficult_rows({"candidates": [candidate]})
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0]["manual_probe_count"], 10)
        self.assertEqual(rows[0]["historical_summary_entries"], 0)
        self.assertIsNone(rows[0]["best_measured_differing_words"])

    def test_best_words_require_matching_structured_report_and_hash(self):
        function = "func_80021074"
        directory = self.root / "analysis/scratch/main" / function
        directory.mkdir(parents=True)
        good = directory / "probe-001.json"
        stale = directory / "probe-002.json"
        failed = directory / "probe-003.json"
        base = {"unit": "main", "source": "src/engine/11800.c", "source_sha256": "a" * 64,
                "results": [{"function": function, "built_size": 20, "retail_size": 20,
                             "differing_words": 3, "diagnostic_match": False}]}
        good.write_text("Python launcher warning\n" + json.dumps(base))
        stale.write_text(json.dumps(dict(base, source_sha256="b" * 64,
                                         results=[dict(base["results"][0], differing_words=0)])))
        failed.write_text(json.dumps(dict(base, results=[dict(base["results"][0], differing_words=0)])))
        attempts = [
            {"cycle": 0, "report": good.relative_to(self.root).as_posix(), "source_sha256": "a" * 64, "exit_code": 1},
            {"cycle": 0, "report": stale.relative_to(self.root).as_posix(), "source_sha256": "a" * 64, "exit_code": 1},
            {"cycle": 0, "report": failed.relative_to(self.root).as_posix(), "source_sha256": "a" * 64, "exit_code": None},
        ]
        (directory / "session.json").write_text(json.dumps({
            "cycle": 0, "target": {"unit": "main", "function": function, "source": "src/engine/11800.c"},
            "probes": attempts,
        }))
        candidate = {"unit": "main", "function": function, "source_slot": "src/engine/11800.c",
                     "manifest_kind": "func", "attempts": [{"outcome": "unmatched", "reason": "near miss"}]}
        with patch.object(W, "ROOT", self.root):
            rows = W.difficult_rows({"candidates": [candidate]})
        self.assertEqual(rows[0]["best_measured_differing_words"], 3)

    def test_invalid_source_experiment_cannot_supply_zero_best_diff(self):
        function = "func_80021074"
        directory = self.root / "analysis/scratch/main" / function
        directory.mkdir(parents=True)
        report = directory / "probe-001.json"
        report.write_text(json.dumps({
            "unit": "main", "source": "src/engine/11800.c", "source_sha256": "a" * 64,
            "results": [{"function": function, "built_size": 20, "retail_size": 20,
                         "differing_words": 0, "diagnostic_match": True}],
        }))
        attempt = {"report": report.relative_to(self.root).as_posix(),
                   "source_sha256": "a" * 64, "exit_code": 0,
                   "source_candidate_valid": False}
        self.assertIsNone(W.measured_words(attempt, "main", function, "src/engine/11800.c", self.root))
        attempt["source_candidate_valid"] = True
        self.assertEqual(W.measured_words(attempt, "main", function, "src/engine/11800.c", self.root), 0)

    def test_session_only_capped_function_is_visible(self):
        function = "func_80021074"
        directory = self.root / "analysis/scratch/main" / function
        directory.mkdir(parents=True)
        (directory / "session.json").write_text(json.dumps({
            "cycle": 1, "target": {"unit": "main", "function": function, "source": "src/engine/11800.c", "calibration": False},
            "probes": [{"cycle": 1} for _ in range(10)],
        }))
        with patch.object(W, "ROOT", self.root):
            rows = W.difficult_rows({"candidates": []})
        self.assertEqual([(row["unit"], row["function"]) for row in rows], [("main", function)])


if __name__ == "__main__":
    unittest.main()
