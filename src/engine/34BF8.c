#include "common.h"

/* libds accessor: byte-exact only under psyq 4.0 (2.7.2.SN32.3.7.0002); the
   2.7.2-win cc1 that builds the rest of the 3C4B0 slot emits the shift after
   the `lui`.  See UNIT_CC1_EXE.  The table at 0x800626A0 carries no global
   symbol (the split names it `.L800626A0`, a local label inside
   func_80057AE4), so its address is written out. */
INCLUDE_ASM("asm/us/main/nonmatchings/34BF8", func_800443F8);
