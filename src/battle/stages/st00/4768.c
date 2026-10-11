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
void func_800D8268(u8 *a0) {
  u8 *a1 = ((u8 *)&D_8001093C);
  u16 idx = *(volatile u16 *)(a0 + 0x20);
  u16 cur = *(volatile u16 *)(a0 + 0x20);
  u8 b;
  __asm__("" : "+r"(a1));
  a1 += (idx & 0xFFF) << 2;
  b = ((s16)*(u16 *)(a1 + 2) >> 6) - 0x80;
  *(u16 *)(a0 + 0x20) = cur + 8;
  *(s32 *)(a0 + 0x1C) = b | ((b >> 2) << 8) | ((b >> 2) << 16);
}

