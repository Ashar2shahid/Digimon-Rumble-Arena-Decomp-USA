"""Focused regression checks for probe_slot's local relocation diagnostics."""
import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from probe_slot import compare_words, parse_relocation_metadata  # noqa: E402


class ProbeRelocationTests(unittest.TestCase):
    # Real E1F4 object slices: original worker (bad), corrected worker (fixed),
    # and retail. Both object bodies differ only at the R_MIPS_26 local jump.
    BAD = bytes.fromhex(
        "0000848C0000000010008010000000001000828C00000000030045142B104500"
        "0800E0032110800004004010000000000800848C8E000008000000000C00848C"
        "00000000F2FF8014000000000800E00321108000")
    FIXED = bytes.fromhex(
        "0000848C0000000010008010000000001000828C00000000030045142B104500"
        "0800E0032110800004004010000000000800848C8D000008000000000C00848C"
        "00000000F2FF8014000000000800E00321108000")
    RETAIL = bytes.fromhex(
        "0000848C0000000010008010000000001000828C00000000030045142B104500"
        "0800E0032110800004004010000000000800848C8DB80008000000000C00848C"
        "00000000F2FF8014000000000800E00321108000")
    LOCAL_TEXT = {0x34: dict(kind="R_MIPS_26", symbol=".text",
                             symbol_section=".text", symbol_value=0)}

    def test_elf_objdump_metadata_preserves_section_and_value(self):
        symbols = ("00000000 l    d  .text 00000000 .text\n"
                   "000001f4 g     F .text 00000054 func_8002E1F4\n"
                   "00000000         *UND* 00000000 external\n")
        relocations = ("RELOCATION RECORDS FOR [.text]:\n"
                       "OFFSET TYPE VALUE\n"
                       "00000228 R_MIPS_26 .text\n"
                       "0000022c R_MIPS_26 external\n")
        parsed = parse_relocation_metadata(symbols, relocations)[".text"]
        self.assertEqual(parsed[0x228]["symbol_section"], ".text")
        self.assertEqual(parsed[0x228]["symbol_value"], 0)
        self.assertNotEqual(parsed[0x22c]["symbol_section"], ".text")

    def test_real_e1f4_old_false_exact_now_fails_fixed_passes(self):
        self.assertEqual(len(self.BAD), 84)
        self.assertEqual(len(self.FIXED), 84)
        self.assertEqual(len(self.RETAIL), 84)
        # Legacy coarse comparison intentionally retains its old API behavior.
        self.assertEqual(compare_words(self.BAD, self.RETAIL, {0x34}), [])
        kwargs = dict(function_vram=0x8002E1F4, function_offset=0x1F4,
                      section=".text")
        bad = compare_words(self.BAD, self.RETAIL, self.LOCAL_TEXT, **kwargs)
        self.assertEqual(len(bad), 1)
        self.assertEqual(bad[0]["reason"], "local_jump_target")
        self.assertEqual(bad[0]["actual_relative_target"], "0x44")
        self.assertEqual(bad[0]["retail_relative_target"], "0x40")
        self.assertEqual(compare_words(self.FIXED, self.RETAIL,
                                       self.LOCAL_TEXT, **kwargs), [])

    def test_jump_opcode_and_register_bits_are_not_masked(self):
        relocation = {0: dict(kind="R_MIPS_26", symbol=".text",
                              symbol_section=".text", symbol_value=0)}
        j = (0x0800008D).to_bytes(4, "little")
        jal = (0x0C00008D).to_bytes(4, "little")
        self.assertEqual(len(compare_words(jal, j, relocation)), 1)
        for kind in ("R_MIPS_HI16", "R_MIPS_LO16", "R_MIPS_GPREL16"):
            relocation[0]["kind"] = kind
            # The low immediate changes, but an rt register change must show.
            got = (0x3C030001).to_bytes(4, "little")
            want = (0x3C020002).to_bytes(4, "little")
            self.assertEqual(len(compare_words(got, want, relocation)), 1)
            got = (0x3C020001).to_bytes(4, "little")
            self.assertEqual(compare_words(got, want, relocation), [])

    def test_external_jump_remains_masked_pending_linked_gate(self):
        external = {0x34: dict(kind="R_MIPS_26", symbol="func_external",
                                  symbol_section=None, symbol_value=None)}
        self.assertEqual(compare_words(self.BAD, self.RETAIL, external,
                                       function_vram=0x8002E1F4,
                                       function_offset=0x1F4,
                                       section=".text"), [])


if __name__ == "__main__":
    unittest.main()
