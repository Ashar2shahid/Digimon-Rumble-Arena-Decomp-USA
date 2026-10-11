#include "common.h"

extern void func_8004FCFC(s32, s32, s32, s32);
extern void func_8004FFEC(s32, s32);

INCLUDE_ASM("asm/us/main/nonmatchings/40000", func_8004F800);

INCLUDE_ASM("asm/us/main/nonmatchings/40000", func_8004FB34);

/* libspu VRAM 0x800594CC (S_SPLV.SpuSetPitchLFOVoice): forward with
 * LFO registers 0xCA/0xCB. */
INCLUDE_ASM("asm/us/main/nonmatchings/40000", func_8004FCCC);

INCLUDE_ASM("asm/us/main/nonmatchings/40000", func_8004FCFC);

/* libspu VRAM 0x800597BC (S_GPLV.SpuGetPitchLFOVoice): read regs 0xCA/0xCB. */
INCLUDE_ASM("asm/us/main/nonmatchings/40000", func_8004FFBC);

INCLUDE_ASM("asm/us/main/nonmatchings/40000", func_8004FFEC);
