"""Safety and integrity checks for isolated worker snapshots."""

import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest


sys.path.insert(0, str(Path(__file__).absolute().parent.parent / "tools"))
from worker_workspace import prepare  # noqa: E402


def sha(data):
    return hashlib.sha256(data).hexdigest()


class WorkerWorkspaceTests(unittest.TestCase):
    def setUp(self):
        base = Path(__file__).absolute().parent.parent / "analysis" / "test-temp"
        base.mkdir(parents=True, exist_ok=True)
        self.temporary = tempfile.TemporaryDirectory(dir=base)
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.checkpoint = self.root / "analysis" / "checkpoints" / "20261008T000000Z"
        self.checkpoint.mkdir(parents=True)
        self._metadata({"src/engine/100.c": b"verified source\n"})
        (self.checkpoint / "tools").mkdir()
        (self.checkpoint / "tools" / "probe.py").write_text("print('checkpoint')\n")
        (self.checkpoint / "decomp.ps1").write_text("Write-Output checkpoint\n")
        (self.root / "tools").mkdir()
        (self.root / "tools" / "learning_search.py").write_text("print('current')\n")
        (self.root / "tools" / "calibrate_permuter.py").write_text("print('calibrate')\n")
        (self.root / "AGENTS.md").write_text("worker instructions\n")
        docs = self.root / "docs"
        docs.mkdir()
        (docs / "CODEGEN_MODEL.md").write_text("codegen model\n")
        (docs / "DECOMPILATION_LEARNINGS.md").write_text("learning journal\n")
        (docs / "DW2_WORKFLOW.md").write_text("workflow\n")
        m2c = self.root / ".tools/m2c"
        m2c.mkdir(parents=True)
        (m2c / "m2c.py").write_text("print('m2c')\n")
        (m2c / "LICENSE").write_text("license\n")
        (m2c / ".git").mkdir()
        (m2c / ".git/config").write_text("do not copy\n")
        (m2c / "__pycache__").mkdir()
        (m2c / "__pycache__/m2c.pyc").write_bytes(b"cache")
        (m2c / ".venv").mkdir()
        (m2c / ".venv/python.exe").write_bytes(b"runtime")
        permuter = self.root / ".tools/decomp-permuter"
        permuter.mkdir()
        (permuter / "permuter.py").write_text("print('permuter')\n")
        (permuter / "test.pyc").write_bytes(b"cache")

    def _metadata(self, files):
        manifest = {}
        for relative, data in files.items():
            # Malicious paths are metadata only; never write them in the fixture.
            if ".." not in relative and not relative.startswith("/") and ":" not in relative and "\\" not in relative:
                path = self.checkpoint / relative
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(data)
            manifest[relative] = sha(data)
        (self.checkpoint / "checkpoint.json").write_text(json.dumps({
            "recorded_inputs": len(manifest),
            "copied_inputs_sha256": manifest,
        }))

    def test_prepare_success_and_unchanged_reuse(self):
        status, destination = prepare("Worker_1", root=self.root)
        self.assertEqual(status, "created")
        self.assertEqual((destination / "src/engine/100.c").read_bytes(), b"verified source\n")
        self.assertTrue((destination / "tools/probe.py").is_file())
        self.assertTrue((destination / "tools/learning_search.py").is_file())
        self.assertTrue((destination / "current_workflow/tools/learning_search.py").is_file())
        self.assertTrue((destination / "current_workflow/tools/calibrate_permuter.py").is_file())
        self.assertEqual((destination / "AGENTS.md").read_text(), "worker instructions\n")
        self.assertTrue((destination / "docs/CODEGEN_MODEL.md").is_file())
        self.assertTrue((destination / "docs/DECOMPILATION_LEARNINGS.md").is_file())
        self.assertTrue((destination / "docs/DW2_WORKFLOW.md").is_file())
        self.assertTrue((destination / ".tools/m2c/m2c.py").is_file())
        self.assertTrue((destination / ".tools/decomp-permuter/permuter.py").is_file())
        self.assertFalse((destination / ".tools/m2c/.git").exists())
        self.assertFalse((destination / ".tools/m2c/__pycache__").exists())
        self.assertFalse((destination / ".tools/m2c/.venv").exists())
        self.assertFalse((destination / ".tools/decomp-permuter/test.pyc").exists())
        self.assertFalse((destination / ".git").exists())
        self.assertIn("Source ownership", (destination / "PLAN.md").read_text())
        self.assertIn("external", (destination / "README.md").read_text())
        state = json.loads((destination / "state.json").read_text())
        self.assertEqual(state["baseline"], "analysis/checkpoints/20261008T000000Z")
        self.assertEqual(state["files"]["src/engine/100.c"]["sha256"], sha(b"verified source\n"))
        self.assertEqual(state["files"]["AGENTS.md"]["origin"], "current_workflow")
        self.assertEqual(state["files"][".tools/m2c/m2c.py"]["origin"], "current_workflow")
        self.assertEqual(state["files"]["tools/learning_search.py"]["origin"], "current_workflow")
        self.assertEqual(prepare("Worker_1", root=self.root), ("reused", destination))

    def test_missing_components_are_reported(self):
        (self.root / "docs/DW2_WORKFLOW.md").unlink()
        (self.root / ".tools/decomp-permuter/permuter.py").unlink()
        _, destination = prepare("Worker_1", root=self.root)
        readme = (destination / "README.md").read_text()
        self.assertIn("docs/DW2_WORKFLOW.md", readme)
        self.assertIn(".tools/decomp-permuter/permuter.py", readme)

    def test_current_document_change_rejects_reuse(self):
        _, destination = prepare("Worker_1", root=self.root)
        (destination / "docs/CODEGEN_MODEL.md").write_text("worker edit")
        with self.assertRaisesRegex(ValueError, "Existing worker file changed"):
            prepare("Worker_1", root=self.root)

    def test_checkpoint_helper_is_not_overwritten(self):
        (self.checkpoint / "tools/learning_search.py").write_text("print('baseline')\n")
        _, destination = prepare("Worker_1", root=self.root)
        self.assertEqual((destination / "tools/learning_search.py").read_text(), "print('baseline')\n")
        self.assertEqual((destination / "current_workflow/tools/learning_search.py").read_text(), "print('current')\n")
        state = json.loads((destination / "state.json").read_text())
        self.assertEqual(state["files"]["tools/learning_search.py"]["origin"], "checkpoint_tool")

    def test_reject_modified_existing_snapshot_without_reset(self):
        _, destination = prepare("Worker_1", root=self.root)
        changed = destination / "src/engine/100.c"
        changed.write_text("worker edit\n")
        with self.assertRaisesRegex(ValueError, "Existing worker file changed"):
            prepare("Worker_1", root=self.root)
        self.assertEqual(changed.read_text(), "worker edit\n")

    def test_reject_untracked_file_in_existing_snapshot(self):
        _, destination = prepare("Worker_1", root=self.root)
        (destination / "extra.txt").write_text("new")
        with self.assertRaisesRegex(ValueError, "file inventory changed"):
            prepare("Worker_1", root=self.root)

    def test_reject_modified_state_metadata(self):
        _, destination = prepare("Worker_1", root=self.root)
        state_path = destination / "state.json"
        state = json.loads(state_path.read_text())
        state["baseline"] = "analysis/checkpoints/another"
        state_path.write_text(json.dumps(state))
        with self.assertRaisesRegex(ValueError, "baseline or inventory changed"):
            prepare("Worker_1", root=self.root)

    def test_reject_traversal_and_absolute_recorded_paths(self):
        for path in ("../escape.c", "src/../escape.c", "/tmp/escape.c", "C:/escape.c", "src\\escape.c"):
            with self.subTest(path=path):
                self._metadata({path: b"bad"})
                with self.assertRaisesRegex(ValueError, "Unsafe recorded path"):
                    prepare("Worker_1", checkpoint=self.checkpoint, root=self.root)
                self.assertFalse((self.root / "analysis/workers/Worker_1").exists())

    def test_reject_invalid_worker_names(self):
        for name in ("../escape", "/absolute", "CON", "worker/name", "bad.name", ""):
            with self.subTest(name=name), self.assertRaises(ValueError):
                prepare(name, root=self.root)

    def test_reject_changed_checkpoint_input(self):
        (self.checkpoint / "src/engine/100.c").write_text("changed checkpoint\n")
        with self.assertRaisesRegex(ValueError, "hash mismatch"):
            prepare("Worker_1", root=self.root)
        self.assertFalse((self.root / "analysis/workers/Worker_1").exists())

    def test_reject_external_checkpoint(self):
        other = self.root / "elsewhere"
        other.mkdir()
        with self.assertRaisesRegex(ValueError, "Path escapes"):
            prepare("Worker_1", checkpoint=other, root=self.root)


if __name__ == "__main__":
    unittest.main()
