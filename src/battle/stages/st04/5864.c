#include "common.h"

/* Sub-range 0x5864..0x59B0 (func_800D5864 only), built with psyq4.0 +
   -fno-strength-reduce (UNIT_CC1_EXE / UNIT_CC1): retail keeps the non-LSR
   `sll a0,s2,4; addu v0,s1,a0` loop shape.  Kept as a stub — see
   docs/DIFFICULT_FUNCTIONS.md and the subdivision report for the residue. */
INCLUDE_ASM("asm/us/st04/nonmatchings/5864", func_800D5864);
