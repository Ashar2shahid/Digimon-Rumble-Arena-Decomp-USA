#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/16000", func_80025800);

INCLUDE_ASM("asm/us/main/nonmatchings/16000", func_800259BC);

extern void func_800251C4(s32, s32);

void func_80025D00(s32 a0, s32 a1) {
    func_800251C4(a1, a0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/16000", func_80025D28);

