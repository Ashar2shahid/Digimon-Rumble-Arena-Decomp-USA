#include "common.h"

extern void func_8004FCFC(s32, s32, s32, s32);
extern void func_8004FFEC(s32, s32);
extern u32 D_800628BC;

INCLUDE_ASM("asm/us/main/nonmatchings/40800", func_80050000);

/* libspu VRAM 0x8005994C (S_SPLV) / 0x8005997C (S_GPLV): the 0xCC/0xCD
 * register pair variants of SpuSet/GetPitchLFOVoice. */
INCLUDE_ASM("asm/us/main/nonmatchings/40800", func_8005001C);

INCLUDE_ASM("asm/us/main/nonmatchings/40800", func_8005004C);

INCLUDE_ASM("asm/us/main/nonmatchings/40800", func_8005007C);

INCLUDE_ASM("asm/us/main/nonmatchings/40800", func_8005011C);

INCLUDE_ASM("asm/us/main/nonmatchings/40800", func_800503CC);

INCLUDE_ASM("asm/us/main/nonmatchings/40800", func_8005042C);

/* libspu _spu_getInTransfer: true when the transfer flag is clear. */
INCLUDE_ASM("asm/us/main/nonmatchings/40800", func_80050454);
