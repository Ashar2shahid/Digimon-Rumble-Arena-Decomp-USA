#include "common.h"

void func_8002BCEC(u8 *, s32);
void func_8002BDA8(u8 *);

void func_800D5DF4(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

INCLUDE_ASM("asm/us/st06/nonmatchings/22F4", func_800D5E3C);
