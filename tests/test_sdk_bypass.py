"""Fail-closed source classification for direct SDK assembly builds."""
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import build_dra


class SDKAssemblyBypassTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        self.source = self.root / "src/engine/30000.c"
        self.source.parent.mkdir(parents=True)
        folder = self.root / "asm/us/main/nonmatchings/30000"
        folder.mkdir(parents=True)
        for name in ("func_8003F800", "func_8003F820"):
            (folder / (name + ".s")).write_text("glabel " + name + "\n")
        metadata = self.root / "config/us/psyq_funcs.txt"
        metadata.parent.mkdir(parents=True)
        metadata.write_text("main func_8003F800 func\nmain func_8003F820 asm\n")
        self.root_patch = patch.object(build_dra, "ROOT", str(self.root))
        self.root_patch.start()

    def tearDown(self):
        self.root_patch.stop()
        self.temp.cleanup()

    def classify(self, body):
        self.source.write_text(body)
        return build_dra.sdk_asm_includes(str(self.source), "main")

    def test_ordered_confirmed_sdk_includes(self):
        includes = self.classify('''#include "common.h"
extern int state;
INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F820);
INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F800);
''')
        self.assertEqual([Path(path).name for path in includes],
                         ["func_8003F820.s", "func_8003F800.s"])
        text = build_dra.sdk_asm_text(includes)
        self.assertLess(text.index("func_8003F820.s"), text.index("func_8003F800.s"))
        self.assertIn('.include "include/labels.inc"', text)
        self.assertEqual(text.count(".set noreorder"), 2)
        self.assertEqual(text.count(".set noat"), 2)

    def test_ambiguous_sources_keep_c_pipeline(self):
        stub = 'INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F800);\n'
        for extra in ('int game(void) { return 1; }\n',
                      'extern int initialized = 1;\n',
                      '#include "other.h"\n',
                      'extern int alias __asm__("retail_name");\n',
                      'extern int alias __asm("retail_name");\n',
                      '__asm__(".globl extra");\n',
                      'INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F840);\n'):
            with self.subTest(extra=extra):
                self.assertIsNone(self.classify('#include "common.h"\n' + extra + stub))

    def test_comments_cannot_create_includes(self):
        body = '''#include "common.h"
/* INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F820); */
INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F800);
'''
        self.assertEqual([Path(path).name for path in self.classify(body)],
                         ["func_8003F800.s"])

    def test_metadata_mismatch_keeps_c_pipeline(self):
        body = 'INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F800);\n'
        (self.root / "config/us/psyq_funcs.txt").write_text("main func_8003F820 asm\n")
        self.assertIsNone(self.classify(body))


if __name__ == "__main__":
    unittest.main()
