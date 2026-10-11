from pathlib import Path
import hashlib
import json
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import decomp_session as S


class SessionTests(unittest.TestCase):
    def fixture_root(self):
        base = Path(__file__).resolve().parents[1] / "analysis/test-temp"
        base.mkdir(parents=True, exist_ok=True)
        temporary = tempfile.TemporaryDirectory(dir=base)
        self.addCleanup(temporary.cleanup)
        return Path(temporary.name)

    def test_cap_counts_only_current_cycle(self):
        state = dict(cycle=1, probes=[dict(cycle=0)] * 20 + [dict(cycle=1)] * 9)
        S.require_attempt_available(state)
        state["probes"].append(dict(cycle=1))
        with self.assertRaisesRegex(ValueError, "Ten manual probes"):
            S.require_attempt_available(state)

    def profile_refresh_fixture(self):
        root = self.fixture_root()
        function = "func_80021074"
        directory = root / "analysis/scratch/main" / function
        directory.mkdir(parents=True)
        target = directory / "target.s"
        target.write_bytes(b"retail body\n")
        info = dict(unit="main", function=function, source="src/engine/11800.c",
                    assembly="asm/us/main/nonmatchings/11800/func_80021074.s",
                    address="0x80021074", assembly_sha256=hashlib.sha256(target.read_bytes()).hexdigest(),
                    compiler="old-cc1", cc1_flags=["-O2", "-G0"], maspsx_flags=[], as_flags=[], calibration=False)
        state = dict(target=info, cycle=0, probes=[dict(cycle=0, report=f"probe-{i:03d}.json") for i in range(10)], requeues=[])
        path = directory / "session.json"
        path.write_text(json.dumps(state))
        evidence = root / "reviewed-family.json"
        evidence.write_text("whole family reviewed\n")
        return root, function, directory, path, info

    def test_explicit_profile_refresh_keeps_exhausted_cycle_and_target_history(self):
        root, function, directory, path, info = self.profile_refresh_fixture()
        current = dict(info, compiler="reviewed-cc1")
        with patch.object(S, "ROOT", root), patch.object(S, "target_info", return_value=current):
            S.requeue("main", function, "reviewed-family.json", "all siblings match under reviewed family", True)
            state = json.loads(path.read_text())
            self.assertEqual(state["target"], current)
            self.assertEqual(state["requeues"][0]["previous_target"], info)
            self.assertEqual(len(state["probes"]), 10)
            self.assertEqual(state["cycle"], 1)
            self.assertEqual(S.attempts_this_cycle(state), 0)
            S.require_attempt_available(state)
            self.assertEqual((directory / "target.s").read_bytes(), b"retail body\n")
            with self.assertRaisesRegex(ValueError, "already reopened"):
                S.requeue("main", function, "reviewed-family.json", "same evidence cannot reset cap", True)

    def test_profile_refresh_cannot_silently_change_retail_reference(self):
        root, function, _, path, info = self.profile_refresh_fixture()
        before = path.read_bytes()
        current = dict(info, compiler="new-cc1", assembly_sha256="0" * 64)
        with patch.object(S, "ROOT", root), patch.object(S, "target_info", return_value=current):
            with self.assertRaisesRegex(ValueError, "cannot change the target"):
                S.requeue("main", function, "reviewed-family.json", "different reference requires review", True)
        self.assertEqual(path.read_bytes(), before)

    def test_profile_refresh_rejects_corrupted_scratch_reference(self):
        root, function, directory, path, info = self.profile_refresh_fixture()
        before = path.read_bytes()
        (directory / "target.s").write_bytes(b"edited target\n")
        with patch.object(S, "ROOT", root), patch.object(S, "target_info", return_value=dict(info, compiler="new-cc1")):
            with self.assertRaisesRegex(ValueError, "Scratch retail assembly changed"):
                S.requeue("main", function, "reviewed-family.json", "compiler finding cannot bless edited target", True)
        self.assertEqual(path.read_bytes(), before)

    def test_recovery_probe_cannot_report_retained_assembly_as_source_match(self):
        root, function, _, path, info = self.profile_refresh_fixture()
        state = json.loads(path.read_text())
        state["probes"] = []
        path.write_text(json.dumps(state))
        before = path.read_bytes()
        with (patch.object(S, "ROOT", root), patch.object(S, "target_info", return_value=info),
              patch.object(S, "source_functions", return_value=({}, {function: info["source"]}, [])),
              patch.object(S.subprocess, "run") as compiler):
            with self.assertRaisesRegex(ValueError, "write a source candidate"):
                S.probe("main", function, "a source staging failure must not create a green result")
            compiler.assert_not_called()
        self.assertEqual(path.read_bytes(), before)

    def test_target_validation_disallows_paths_and_unknown_units(self):
        self.assertEqual(S.parse_target("st09:func_800d3b00"), ("st09", "func_800D3B00"))
        for value in ("../main:func_80027214", "sdk:func_80027214", "main:../../escape", "st10:func_80027214"):
            with self.assertRaises(ValueError):
                S.parse_target(value)

    def test_sdk_rejected_before_source_or_compiler_reads(self):
        with patch.object(S, "sdk_symbols", return_value={("main", "func_8005B8BC")}):
            with self.assertRaisesRegex(ValueError, "SDK routines"):
                S.target_info("main", "func_8005B8BC")

    def test_excerpt_ignores_braces_in_comments_and_strings(self):
        text = 'void func_80027214(void) { /* } */ if (1) { use("{"); } }\nvoid next(void) {}'
        result = S.body_excerpt(text, "func_80027214")
        self.assertTrue(result.endswith('use("{"); } }'))
        self.assertNotIn("next", result)

    def test_calibration_requires_existing_c_body(self):
        with (patch.object(S, "sdk_symbols", return_value=set()),
              patch.object(S, "manifest", return_value=[{"name": "func_80021074", "address": 0x80021074, "kind": "func"}]),
              patch.object(S, "source_functions", return_value=({}, {"func_80021074": "src/engine/11800.c"}, []))):
            with self.assertRaisesRegex(ValueError, "existing C body"):
                S.target_info("main", "func_80021074", calibration=True)

    def test_target_uses_its_active_complete_assembly(self):
        root = self.fixture_root()
        function = "func_80021074"
        source = root / "src/engine/11800.c"
        source.parent.mkdir(parents=True)
        source.write_text('INCLUDE_ASM("asm/us/main/nonmatchings/other", func_80021070);\n'
                          'INCLUDE_ASM("asm/us/main/nonmatchings/active", func_80021074);\n')
        active = root / "asm/us/main/nonmatchings/active" / (function + ".s")
        stale = root / "asm/us/main/nonmatchings/other" / (function + ".s")
        active.parent.mkdir(parents=True)
        stale.parent.mkdir(parents=True)
        active.write_text("nonmatching func_80021074, 0x8\n"
                          "glabel func_80021074\n"
                          "/* 0 80021074 00000000 */ nop\n"
                          "/* 4 80021078 0800E003 */ jr $ra\n"
                          "endlabel func_80021074\n")
        stale.write_text("nonmatching func_80021074, 0x4\n"
                         "glabel func_80021074\n"
                         "/* 0 80021074 00000000 */ nop\n"
                         "endlabel func_80021074\n")
        with (patch.object(S, "ROOT", root), patch.object(S, "sdk_symbols", return_value=set()),
              patch.object(S, "manifest", return_value=[{"name": function, "address": 0x80021074, "kind": "func"}]),
              patch.object(S, "source_functions", return_value=({}, {function: "src/engine/11800.c"}, [])),
              patch.object(S.B, "unit_toolchain", return_value=("cc1", [], [], []))):
            info = S.target_info("main", function)
            self.assertEqual(info["assembly"], active.relative_to(root).as_posix())
            self.assertEqual(info["assembly_sha256"], hashlib.sha256(active.read_bytes()).hexdigest())
            active.write_text(active.read_text().replace("0x8", "0xC"))
            with self.assertRaisesRegex(ValueError, "incomplete declared body"):
                S.target_info("main", function)

    def test_interrupted_tenth_probe_remains_reserved(self):
        root = self.fixture_root()
        function = "func_80021074"
        directory = root / "analysis/scratch/main" / function
        directory.mkdir(parents=True)
        source = root / "src/engine/11800.c"
        source.parent.mkdir(parents=True)
        source.write_text("candidate\n")
        target = directory / "target.s"
        target.write_text("retail\n")
        info = {"unit": "main", "function": function, "source": "src/engine/11800.c",
                "assembly": target.relative_to(root).as_posix(),
                "assembly_sha256": hashlib.sha256(target.read_bytes()).hexdigest(), "calibration": False}
        state = {"target": info, "cycle": 0,
                 "probes": [{"cycle": 0} for _ in range(9)], "requeues": []}
        (directory / "session.json").write_text(json.dumps(state))
        with (patch.object(S, "ROOT", root), patch.object(S, "target_info", return_value=info),
              patch.object(S, "source_functions", return_value=({function: {"source": info["source"]}}, {}, [])),
              patch.object(S.subprocess, "run", side_effect=KeyboardInterrupt)):
            with self.assertRaises(KeyboardInterrupt):
                S.probe("main", function, "test one scheduling hypothesis")
            persisted = json.loads((directory / "session.json").read_text())
            self.assertEqual(len(persisted["probes"]), 10)
            self.assertIsNone(persisted["probes"][-1]["exit_code"])
            with self.assertRaisesRegex(ValueError, "Ten manual probes"):
                S.probe("main", function, "another hypothesis")

    def test_recovery_session_can_probe_its_first_c_body(self):
        root = self.fixture_root()
        function = "func_80021074"
        relative = "src/engine/11800.c"
        source = root / relative
        source.parent.mkdir(parents=True)
        asm = root / "asm/us/main/nonmatchings/older_boundary" / (function + ".s")
        asm.parent.mkdir(parents=True)
        asm.write_text("nonmatching func_80021074, 0x8\nglabel func_80021074\n"
                       "/* 0 80021074 0800E003 */ jr $ra\n"
                       "/* 4 80021078 00000000 */ nop\nendlabel func_80021074\n")
        stale = root / "asm/us/main/nonmatchings/11800" / (function + ".s")
        stale.parent.mkdir(parents=True)
        stale.write_text(asm.read_text().replace("0x8", "0x4"))
        source.write_text('INCLUDE_ASM("asm/us/main/nonmatchings/older_boundary", func_80021074);\n')

        def inventory(_unit):
            if "INCLUDE_ASM" in source.read_text():
                return {}, {function: relative}, []
            return {function: {"source": relative, "category": "ordinary_c"}}, {}, []

        with (patch.object(S, "ROOT", root), patch.object(S, "sdk_symbols", return_value=set()),
              patch.object(S, "manifest", return_value=[{"name": function, "address": 0x80021074, "kind": "func"}]),
              patch.object(S, "source_functions", side_effect=inventory),
              patch.object(S.B, "unit_toolchain", return_value=("cc1", [], [], []))):
            info = S.target_info("main", function)
            directory = S.session_dir("main", function)
            directory.mkdir(parents=True)
            (directory / "target.s").write_bytes(asm.read_bytes())
            (directory / "session.json").write_text(json.dumps({"target": info, "cycle": 0, "probes": [], "requeues": []}))
            source.write_text("void func_80021074(void) {}\n")
            with self.assertRaisesRegex(ValueError, "Target already has source"):
                S.target_info("main", function)
            with patch.object(S.subprocess, "run", return_value=SimpleNamespace(returncode=0)):
                self.assertEqual(S.probe("main", function, "first natural body"), 0)
            state = json.loads((directory / "session.json").read_text())
            self.assertEqual(len(state["probes"]), 1)
            self.assertEqual(state["target"], info)
            self.assertEqual(state["probes"][0]["source_sha256"], hashlib.sha256(source.read_bytes()).hexdigest())
            asm.write_text(asm.read_text().replace("nop", "sll $zero, $zero, 0"))
            with self.assertRaisesRegex(ValueError, "metadata changed"):
                S.probe("main", function, "changed retail reference must be rejected")
