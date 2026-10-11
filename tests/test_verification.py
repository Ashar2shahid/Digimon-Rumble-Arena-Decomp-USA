"""Placement evidence must survive even when complete output bytes match."""
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).absolute().parent.parent / "tools"))
import source_inventory
import verify


class VerificationTests(unittest.TestCase):
    def setUp(self):
        base = source_inventory.ROOT / "analysis/test-temp"
        base.mkdir(parents=True, exist_ok=True)
        self.directory = tempfile.TemporaryDirectory(dir=base)
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        for module in (verify, source_inventory):
            patched = patch.object(module, "ROOT", self.root)
            patched.start()
            self.addCleanup(patched.stop)
        (self.root / "config/us/functions").mkdir(parents=True)
        (self.root / "src/engine").mkdir(parents=True)
        self.manifest = self.root / "config/us/functions/main.txt"
        self.manifest.write_text("func_80010000 80010000 func\n")
        (self.root / "src/engine/slot.c").write_text("void func_80010000(void) {}\n")

    def test_absent_manifest_cannot_be_accepted(self):
        self.manifest.unlink()
        with self.assertRaisesRegex(ValueError, "Missing or empty"):
            verify.input_manifest("main")

    def test_absent_symbol_cannot_be_accepted(self):
        with patch.object(verify.build_dra, "parse_map_symbols", return_value=[]):
            with self.assertRaisesRegex(ValueError, "not defined"):
                verify.require_placement("main")

    def test_wrong_address_cannot_be_accepted(self):
        symbols = [("func_80010000", 0x80010004, "build/us/src/engine/slot.c.o")]
        with patch.object(verify.build_dra, "parse_map_symbols", return_value=symbols):
            with self.assertRaisesRegex(ValueError, "placement differs"):
                verify.require_placement("main")

    def test_asm_object_cannot_receive_source_credit(self):
        symbols = [("func_80010000", 0x80010000, "build/us/asm/us/main/slot.s.o")]
        with patch.object(verify.build_dra, "parse_map_symbols", return_value=symbols):
            with self.assertRaisesRegex(ValueError, "wrong object"):
                verify.require_placement("main")

    def test_explicit_binding_and_own_source_object_are_accepted(self):
        (self.root / "src/engine/slot.c").write_text('void func_80010000(void) {}\nasm(".set func_80010000, func_80010000__Fv");\n')
        symbols = [("func_80010000", 0x80010000, "build/us/src/engine/slot.c.o")]
        with patch.object(verify.build_dra, "parse_map_symbols", return_value=symbols):
            verify.require_placement("main")

    def test_saved_output_without_map_evidence_is_stale(self):
        data = b"matching retail output"
        cfg = dict(target="target.bin", out="output.bin", elf="module.elf", sha1=hashlib.sha1(data).hexdigest())
        for name in ("target.bin", "output.bin"):
            (self.root / name).write_bytes(data)
        records = self.root / "verification"
        records.mkdir()
        record = dict(inputs_sha256=verify.fingerprint({}), output_sha256=hashlib.sha256(data).hexdigest())
        (records / "main.json").write_text(json.dumps(record))
        with patch.object(verify, "RECORDS", records), patch.object(verify, "input_manifest", return_value={}), patch.dict(verify.build_dra.CONFIG, main=cfg):
            self.assertFalse(verify.current_verification("main")["current_verified_build"])


if __name__ == "__main__":
    unittest.main()
