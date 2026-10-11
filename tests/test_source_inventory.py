"""Counter regressions: prototypes, calls, comments, and assembly constraints."""
import sys
from pathlib import Path
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).absolute().parent.parent / "tools"))
import source_inventory


class SourceInventoryTests(unittest.TestCase):
    def classify(self, text):
        temporary_root = source_inventory.ROOT / "analysis/test-temp"
        temporary_root.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(dir=temporary_root) as directory:
            root = Path(directory)
            (root / "src/engine").mkdir(parents=True)
            (root / "src/engine/test.c").write_text(text)
            previous = source_inventory.ROOT
            try:
                source_inventory.ROOT = root
                return source_inventory.source_functions("main")
            finally:
                source_inventory.ROOT = previous

    def test_prototypes_and_calls_do_not_create_definitions(self):
        definitions, _, duplicates = self.classify("""
extern void func_80010000(void);
void func_80010020(void) {
    func_80010000();
    do { func_80010000(); } while (0);
}
""")
        self.assertEqual(set(definitions), {"func_80010020"})
        self.assertEqual(duplicates, [])

    def test_comments_do_not_create_source_or_stubs(self):
        definitions, stubs, _ = self.classify('''
/* void func_80010000(void) {} */
// INCLUDE_ASM("somewhere", func_80010004);
INCLUDE_ASM("somewhere", func_80010008);
''')
        self.assertEqual(definitions, {})
        self.assertEqual(set(stubs), {"func_80010008"})

    def test_constraints_are_distinct_from_plain_c(self):
        definitions, _, _ = self.classify('''
void func_80010000(void) { /* asm("nop"); */ }
int func_80010004(int a) { return a + 1; }
int func_80010008(int a) { register int r asm("$16") = a; return r; }
void func_8001000C(void) { __asm__("nop"); }
''')
        self.assertEqual([definitions[n]["category"] for n in sorted(definitions)],
                         ["empty_c", "ordinary_c", "assisted_c", "assisted_c"])

    def test_knr_and_cxx_alias_remain_explicit(self):
        definitions, _, _ = self.classify('''
int func_80010000(a)
int a;
{ return a; }
asm(".globl func_80010020\\n" ".set func_80010020, _method__4Test\\n");
''')
        self.assertTrue(definitions["func_80010000"]["knr"])
        self.assertEqual(definitions["func_80010020"]["category"], "cxx_alias")

    def test_duplicate_source_bodies_are_detected(self):
        _, _, duplicates = self.classify("void func_80010000(void) {}\nvoid func_80010000(void) {}\n")
        self.assertEqual(duplicates, ["func_80010000"])

    def test_documented_register_forcing_source_is_not_plain_credit(self):
        definitions, _, _ = self.classify("int func_80010000(void) { int v; /* v is read before its assignment: register-forcing */ return v; }")
        self.assertEqual(definitions["func_80010000"]["category"], "source_hack_c")


if __name__ == "__main__":
    unittest.main()
