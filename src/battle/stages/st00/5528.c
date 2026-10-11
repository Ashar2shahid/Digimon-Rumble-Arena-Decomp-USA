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
INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D9028);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D91B4);

void func_800D9294(u8 *a0, s32 a1) {
  s32 f;
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3C2C;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D92E8);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D9408);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D9514);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D960C);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D97EC);

void func_800D98A0(u8 *a0, s32 a1) {
  s32 f;
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3C04;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D98F4);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D9A5C);

/* Pin the object/value registers; volatile stack stores preserve the frame writes. */
