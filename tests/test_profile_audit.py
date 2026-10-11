"""Small fixture tests for compiler-profile inventory; no build tools execute."""
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).absolute().parent.parent / "tools"))
import profile_audit as audit
import source_inventory


class ProfileAuditTests(unittest.TestCase):
    def temporary_fixture(self):
        directory = Path(__file__).absolute().parent.parent / "analysis/test-temp"
        directory.mkdir(parents=True, exist_ok=True)
        return tempfile.TemporaryDirectory(dir=directory)

    def fixture(self, root):
        sources = root / "src/engine"
        manifests = root / "config/us/functions"
        sources.mkdir(parents=True)
        manifests.mkdir(parents=True)
        (sources / "plain.c").write_text('''
void func_80010000(void) { int x = 1; (void)x; }
INCLUDE_ASM("asm", func_80010010);
''')
        (sources / "isolated.c").write_text('''
void func_80010020(void) { int x = 2; (void)x; }
INCLUDE_ASM("asm", func_80010030);
''')
        (sources / "cxx.c").write_text('''
asm(".globl func_80010040\\n" ".set func_80010040, _method__4Test\\n");
asm(".globl func_80010050\\n" ".set func_80010050, _internal__4Test\\n");
''')
        (manifests / "main.txt").write_text('''
func_80010000 0x80010000 func
func_80010010 0x80010010 func
func_80010020 0x80010020 func
func_80010030 0x80010030 func
func_80010040 0x80010040 func
func_80010050 0x80010050 asm
func_80010060 0x80010060 func
''')
        (root / "config/us/psyq_funcs.txt").write_text("main func_80010030\n")

    @staticmethod
    def toolchain(unit, name=None):
        if name == "isolated.c":
            compiler = "/tmp/psyq46/CC1PSX.EXE"
        elif name == "cxx.c":
            compiler = "/tmp/CC1PLPSX.EXE"
        else:
            compiler = "/tmp/gcc-2.8.1-psx/cc1"
        return compiler, ["-O2", "-G8" if name == "isolated.c" else "-G0"], ["--aspsx-version=2.77"], ["-EL"]

    def report(self, root, evidence=None):
        with patch.object(source_inventory, "ROOT", root), \
             patch.object(audit.build_dra, "unit_toolchain", side_effect=self.toolchain), \
             patch.dict(audit.build_dra.UNIT_CXX, {"main/cxx.c": True}):
            return audit.build_report(units=["main"], root=root, evidence=evidence)

    def test_inventory_excludes_sdk_and_nonfunc_aliases(self):
        with self.temporary_fixture() as directory:
            root = Path(directory)
            self.fixture(root)
            result = self.report(root, evidence={})
        by_key = {x["profile_key"]: x for x in result["source_slots"]}
        self.assertEqual(result["summary"]["function_count"], 4)
        self.assertEqual(result["summary"]["unconstrained_count"], 3)
        self.assertEqual(result["summary"]["unassigned_function_count"], 1)
        self.assertEqual(result["unassigned_manifest_functions"][0]["function"], "func_80010060")
        self.assertEqual(by_key["main/plain.c"]["function_count"], 2)
        self.assertEqual(by_key["main/plain.c"]["categories"], {"ordinary_c": 1, "assembly": 1})
        self.assertEqual(by_key["main/isolated.c"]["function_count"], 1)
        self.assertEqual(by_key["main/isolated.c"]["review_flags"], ["needs_object_boundary_review"])
        self.assertEqual(by_key["main/isolated.c"]["original_object_provenance"]["status"], "unreviewed")
        self.assertEqual(by_key["main/isolated.c"]["min_manifest_address"], "0x80010020")
        self.assertEqual(by_key["main/cxx.c"]["current_profile"]["language"], "cxx")
        self.assertEqual(by_key["main/cxx.c"]["categories"], {"cxx_alias": 1})
        self.assertEqual(by_key["main/cxx.c"]["review_flags"], ["needs_object_boundary_review"])
        self.assertEqual(result["summary"]["single_function_compiler_isolations"], 2)

    def test_manual_provenance_requires_references_and_stays_separate(self):
        with self.temporary_fixture() as directory:
            root = Path(directory)
            self.fixture(root)
            config = root / audit.EVIDENCE
            config.parent.mkdir(parents=True, exist_ok=True)
            config.write_text(json.dumps({"profiles": {"main/isolated.c": {
                "byte_verified_evidence": ["analysis/byte-gate.json"],
                "original_object_provenance": {"status": "reviewed", "evidence": []}}}}))
            with self.assertRaisesRegex(ValueError, "reviewed provenance requires evidence"):
                audit.load_evidence(root)
            config.write_text(json.dumps({"profiles": {"main/isolated.c": {
                "byte_verified_evidence": ["analysis/byte-gate.json"],
                "original_object_provenance": {"status": "reviewed", "evidence": ["analysis/object-map.json"]}}}}))
            annotations = audit.load_evidence(root)
            result = self.report(root, annotations)
        by_key = {x["profile_key"]: x for x in result["source_slots"]}
        self.assertEqual(by_key["main/isolated.c"]["byte_verified_evidence"], ["analysis/byte-gate.json"])
        self.assertEqual(by_key["main/isolated.c"]["original_object_provenance"]["evidence"], ["analysis/object-map.json"])
        self.assertEqual(by_key["main/plain.c"]["original_object_provenance"]["status"], "unreviewed")
        self.assertEqual(result["summary"]["reviewed_original_object_profiles"], 1)


if __name__ == "__main__":
    unittest.main()
