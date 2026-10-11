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
void func_800D9C50(u32 *a0, s32 a1) {
    volatile u32 stack[3];
    register u32 *v0 asm("$2");
    register u32 value asm("$4");

    v0 = a0;
    v0[0] = (u32)D_800D3DBC;
    value = 0x40;
    stack[0] = value;
    stack[1] = 0;
    stack[2] = 0;
    v0[1] = a1;
    v0[2] = value;
    v0[3] = 0;
    v0[4] = 0;
}

/* Pin the live values to retail's GPRs for its interleaved field updates. */
