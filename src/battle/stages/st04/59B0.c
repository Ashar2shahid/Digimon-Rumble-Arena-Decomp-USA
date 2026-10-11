#include "common.h"

extern u8 D_800D3D04[];
extern void func_8002BCEC(u8*, u32);
extern void func_8002BDA8(u8*);

INCLUDE_ASM("asm/us/st04/nonmatchings/59B0", func_800D59B0);

INCLUDE_ASM("asm/us/st04/nonmatchings/59B0", func_800D5A3C);

INCLUDE_ASM("asm/us/st04/nonmatchings/59B0", func_800D5B8C);

INCLUDE_ASM("asm/us/st04/nonmatchings/59B0", func_800D6170);

INCLUDE_ASM("asm/us/st04/nonmatchings/59B0", func_800D6260);

void func_800D63B4(u8* a0, u32 a1) {
    *(u8**)(a0 + 0x14) = D_800D3D04;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st04/nonmatchings/59B0", func_800D6408);

INCLUDE_ASM("asm/us/st04/nonmatchings/59B0", func_800D6650);
