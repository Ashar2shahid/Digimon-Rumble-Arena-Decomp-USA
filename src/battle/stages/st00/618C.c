#include "game_rotation.h"
#include "common.h"
#include "game_random.h"

extern void func_800D9E7C();
extern void func_8002B3D0();
extern void func_8001BEDC();
extern void func_80071F64();
extern s32 func_8006F18C();
extern s32 func_8006F12C();
extern s32 func_8006F178();
extern void func_800D4E90();
extern void func_8001FE8C();
extern void func_8001FD40();
extern u8 D_80065154;
extern u8 D_800D3D94[];
extern u8 D_800D3D1C[];
extern u8 D_800D3CF4[];
extern u8 D_800D3CCC[];
extern u8 D_800D3CA4[];
extern u8 D_800D3C7C[];
extern u8 D_800D3C54[];
extern u8 D_800D3C2C[];
extern u8 D_800D3C04[];
extern u8 D_800D3DBC[];
extern void func_8002BCEC(void *a0, s32 a1);
extern void func_8002BDA8(void *a0);
void func_800D9C8C(u32 *a0, u32 *a1) {
    register u32 t0 asm("$8");
    register u32 v0 asm("$2");
    register u32 v1 asm("$3");
    register u32 a3 asm("$7");
    register u32 a2 asm("$6");

    t0 = a1[8];
    v0 = a1[6];
    v1 = a0[1];
    a3 = a1[9];
    v0 += v1;
    a1[6] = v0;
    v1 = a0[2];
    v0 = a1[10];
    a2 = a0[3];
    t0 += v1;
    v1 = a0[4];
    a3 += a2;
    a1[8] = t0;
    a1[9] = a3;
    v0 += v1;
    a1[10] = v0;
}


INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D9CD0);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D9DE8);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D9E7C);

void func_800DA09C(u8 *a0) {
    func_800D9E7C(a0);
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800DA0BC);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800DA1BC);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800DA250);

s32 func_800DA420(u8 *a0) {
    return *(u32 *)(a0 + 0x1050) != 0;
}

void func_800DA42C(u32 *a0, s32 a1) {
    *a0 = (u32)&D_80065154;
    if (a1 & 1) {
        func_8002B3D0();
    }
}

void func_800DA460(u32 *a0, u32 *a1) {
    u32 v0 = a1[0];
    u32 v1 = a1[1];
    u32 v2;

    v2 = a1[2];
    a0[2] = v0;
    a0[3] = v1;
    a0[4] = v2;
}
void func_800DA47C(s32 *a0, s32 a1) {
    a0[1] = a1;
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800DA484);
