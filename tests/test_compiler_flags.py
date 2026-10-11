"""Configured slot flags must reach the compiler process, without leaking."""
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).absolute().parent.parent / 'tools'))
import build_dra as B


class CompilerFlagTests(unittest.TestCase):
    def test_cxx_macro_is_available_for_c_linkage_headers(self):
        # Slot files have .c names even when compiled as C++. Both supported
        # preprocessors must expose the language to shared extern-C headers.
        for preprocessor in ('fake-cxx-cpp', 'CPPPSX.EXE'):
            with self.subTest(preprocessor=preprocessor), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                folder = root / 'src/engine'
                folder.mkdir(parents=True)
                for name in ('cxx.c', 'plain.c'):
                    (folder / name).write_text('void func_80010000(void) {}\n')
                commands = []

                def run(command, **kwargs):
                    commands.append(command)
                    target = (Path(command[command.index('-o') + 1]) if '-o' in command
                              else Path(command[-1]) if command[0] == 'CPPPSX.EXE' else None)
                    if target is not None:
                        target.parent.mkdir(parents=True, exist_ok=True)
                        target.write_text('.text\n')
                    return 0

                with patch.multiple(B, ROOT=str(root), BUILD=str(root / 'build'),
                                    UNIT_G={}, UNIT_CC1_EXE={}, UNIT_CXX={'main/cxx.c': True},
                                    UNIT_SDATA={}, UNIT_RODATA_SECTIONS={}, UNIT_MASPSX_VER={},
                                    UNIT_MASPSX={}, UNIT_MASPSX_AS={}, UNIT_CC1={}), \
                     patch.object(B, 'unit_toolchain', return_value=('fake-cc1', ['-O2', '-G0'], [], [])), \
                     patch.object(B, 'cxx_cpp_bin', return_value=preprocessor), \
                     patch.object(B, 'cxx_cc1_bin', return_value='fake-cxx-cc1'), \
                     patch.object(B, 'sdk_asm_includes', return_value=None), \
                     patch.object(B, 'text_tail_splits', return_value={}), \
                     patch.object(B, 'run', side_effect=run):
                    self.assertEqual(B.compile_c('fake-cpp', 'fake-cc1', 'fake-as', ['main']), 2)
                cxx = next(cmd for cmd in commands if cmd[0] == preprocessor)
                plain = next(cmd for cmd in commands if cmd[0] == 'fake-cpp')
                self.assertIn('-D__cplusplus', cxx)
                self.assertNotIn('-D_LANGUAGE_C', cxx)
                self.assertNotIn('-D__cplusplus', plain)

    def test_slot_flags_are_forwarded_only_to_that_slot(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            folder = root / 'src/engine'
            folder.mkdir(parents=True)
            for name in ('first.c', 'second.c'):
                (folder / name).write_text('void func_80010000(void) {}\n')
            commands = []

            def run(command, **kwargs):
                commands.append(command)
                if '-o' in command:
                    target = Path(command[command.index('-o') + 1])
                    target.parent.mkdir(parents=True, exist_ok=True)
                    target.write_text('.text\n')
                return 0

            with patch.multiple(B, ROOT=str(root), BUILD=str(root / 'build'),
                                UNIT_G={}, UNIT_CC1_EXE={}, UNIT_CXX={}, UNIT_SDATA={},
                                UNIT_RODATA_SECTIONS={}, UNIT_MASPSX_VER={}, UNIT_MASPSX={},
                                UNIT_MASPSX_AS={}, UNIT_CC1={'main/first.c': ['-fno-strength-reduce', '-O3']}), \
                 patch.object(B, 'unit_toolchain', return_value=('fake-cc1', ['-O2', '-G0'], [], [])), \
                 patch.object(B, 'sdk_asm_includes', return_value=None), \
                 patch.object(B, 'text_tail_splits', return_value={}), \
                 patch.object(B, 'run', side_effect=run):
                self.assertEqual(B.compile_c('fake-cpp', 'fake-cc1', 'fake-as', ['main']), 2)
            compiler_commands = [cmd for cmd in commands if cmd[0] == 'fake-cc1']
            by_slot = {Path(cmd[-1]).stem: cmd for cmd in compiler_commands}
            self.assertIn('-fno-strength-reduce', by_slot['first.c'])
            self.assertNotIn('-fno-strength-reduce', by_slot['second.c'])
            self.assertIn('-O3', by_slot['first.c'])
            preprocess_commands = [cmd for cmd in commands if cmd[0] == 'fake-cpp']
            first = next(cmd for cmd in preprocess_commands if cmd[-1].endswith('first.c'))
            second = next(cmd for cmd in preprocess_commands if cmd[-1].endswith('second.c'))
            self.assertIn('-DINCLUDE_ASM_IN_FUNC', first)
            self.assertNotIn('-DINCLUDE_ASM_IN_FUNC', second)


if __name__ == '__main__':
    unittest.main()
