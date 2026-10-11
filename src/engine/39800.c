#include "common.h"

extern void func_80048FBC(s16);
extern void func_80047A0C(s32);

INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_80049000);

/* libsnd VRAM 0x800519C8 (SSCLOSE.SsSeqClose) and the identical-shaped
 * 0x800519EC: sign-extend the 16-bit access number and forward. */
INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_80049138);

INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_8004915C);

INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_8004918C);

INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_8004922C);

/* libsnd VRAM 0x80051AFC (UT_ROFF.SsUtReverbOff). */
INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_8004926C);

INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_8004928C);

INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_8004942C);

INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_8004943C);
INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_8004947C);

INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_800494B4);

INCLUDE_ASM("asm/us/main/nonmatchings/39800", func_8004977C);
