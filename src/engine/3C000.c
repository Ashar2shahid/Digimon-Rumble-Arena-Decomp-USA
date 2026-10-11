#include "common.h"

extern void func_8004BA1C(s32, s32, s32, s32);
extern void func_8004BC4C(s32);

INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004B800);

/* libsnd VRAM 0x8005485C (SSPLAY_2.SsSepPlay): sign-extend the four args
 * (s16, s16, s8, s16) and forward to the sequencer. */
INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004B9DC);

INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004BA1C);

INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004BB3C);

INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004BBFC);

INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004BC4C);

/* libsnd VRAM 0x80054CFC (UT_RON.SsUtReverbOn) / 0x80054D1C (SsUtReverbOff). */
INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004BE7C);

INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004BE9C);

INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004BEBC);

INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004BF08);

INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004BF5C);

INCLUDE_ASM("asm/us/main/nonmatchings/3C000", func_8004BFF8);
