#include "common.h"

/* Sub-range 0x67EC..0x6948 (func_800D67EC only), built with shipped 2.8.1 +
   -fno-strength-reduce (UNIT_CC1; the default cc1): retail keeps the non-LSR
   loop shape and the 0x15C region size.  Kept as a stub — see
   docs/DIFFICULT_FUNCTIONS.md and the subdivision report for the residue. */
INCLUDE_ASM("asm/us/st04/nonmatchings/67EC", func_800D67EC);
