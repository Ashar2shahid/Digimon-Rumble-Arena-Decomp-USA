#include "common.h"

extern u32 D_80062838;
extern s32 D_80062834;

/* libds setter: byte-exact only under psyq 4.0 (2.7.2.SN32.3.7.0002). */
INCLUDE_ASM("asm/us/main/nonmatchings/36B44", func_80046344);

INCLUDE_ASM("asm/us/main/nonmatchings/36B44", func_80046358);

INCLUDE_ASM("asm/us/main/nonmatchings/36B44", func_80046634);

INCLUDE_ASM("asm/us/main/nonmatchings/36B44", func_800466EC);

INCLUDE_ASM("asm/us/main/nonmatchings/36B44", func_80046764);

/* libds getter (PSY-Q 4.7; cc1 gcc-2.7.2) */
INCLUDE_ASM("asm/us/main/nonmatchings/36B44", func_80046794);

INCLUDE_ASM("asm/us/main/nonmatchings/36B44", func_800467A4);

INCLUDE_ASM("asm/us/main/nonmatchings/36B44", func_800467FC);
