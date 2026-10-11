"""Actual symbol boundaries and include reset directives in generated assembly."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from build_dra import split_text_sections


class TailSplitterTests(unittest.TestCase):
    def test_g8_wrapper_symbol_is_not_a_successor_definition(self):
        source = ('\t.text\n__maspsx_include_asm_hack_func_80012340:\n #APP\n'
                  '\t.text # maspsx-keep\n'
                  '.include "asm/x/func_80012340.s" # maspsx-keep\n'
                  '\t.text # maspsx-keep\n')
        result = split_text_sections(source, ['func_80012340'])
        self.assertIn('__maspsx_include_asm_hack_func_80012340:\n', result)
        self.assertNotIn('__maspsx_include_asm_hack_\t.section', result)
        self.assertIn('\t.section .text.tail_func_80012340, "ax" # maspsx-keep\n.include', result)
        self.assertTrue(result.endswith('\t.section .text.tail_func_80012340, "ax" # maspsx-keep\n'))

    def test_g0_include_and_real_definition(self):
        sources = ['.section .text\n.include "asm/x/func_80012340.s"\n.section .text\n',
                   '\t.globl\tfunc_80012340\nfunc_80012340:\n\t.text\n']
        for source in sources:
            result = split_text_sections(source, ['func_80012340'])
            self.assertIn('.text.tail_func_80012340', result)
            self.assertNotIn('# maspsx-keep', result)

    def test_two_successors_keep_their_sections(self):
        source = 'func_80012340:\n.text\nfunc_80012500:\n.section .text\n'
        result = split_text_sections(source, ['func_80012340', 'func_80012500'])
        self.assertTrue(result.endswith('.section .text.tail_func_80012500, "ax"\n'))
        self.assertIn('.section .text.tail_func_80012500, "ax"\nfunc_80012500:', result)

    def test_missing_entry_and_suffix_do_not_match(self):
        self.assertIsNone(split_text_sections('__maspsx_include_asm_hack_func_80012340:\n', ['func_80012340']))
        self.assertIsNone(split_text_sections('other:\n', ['func_80012340']))


if __name__ == '__main__':
    unittest.main()
