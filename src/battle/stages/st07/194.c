#include "common.h"

extern u8 D_800D3BA4[];
extern u8 D_800D3C1C[];
extern u8 D_800D3BF4[];
extern u8 D_800D3BCC[];
extern u8 D_800D3B54[];
extern u8 D_800D3B7C[];
extern u8 D_800D3B34[];
extern void func_8002BCEC(void *a0, s32 a1);
extern void func_8002BDA8(void *a0);
extern void *func_8002B364(s32);
extern void *func_800D3C94(void *, s32);

void *func_800D3C94(void *object, s32 value) {
    u8 *self = object;
    func_8007C35C(self, value);
    *(u8 **)(self + 4) = D_800D3B34;
    *(s32 *)(self + 8) = 0;
    *(s32 *)(self + 0xC) = 0;
    *(s32 *)(self + 0x10) = 0;
    *(s32 *)(self + 0x14) = 0;
    return self;
}

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D3CD8);

u8 *func_800D3DF4(u8 *arg0) {
    func_800D057C(arg0);
    *(u8 **)(arg0 + 0xD34) = D_800D3C1C;
    *(s32 *)(arg0 + 0xD38) = 9;
    *(s32 *)(arg0 + 0xD3C) = 10;
    *(s32 *)(arg0 + 0xD40) = 11;
    *(s32 *)(arg0 + 0xD44) = 13;
    *(s32 *)(arg0 + 0xD48) = 14;
    *(s32 *)(arg0 + 0xD4C) = 15;
    *(s32 *)(arg0 + 0xD50) = 16;
    *(s32 *)(arg0 + 0xD54) = 12;
    return arg0;
}

