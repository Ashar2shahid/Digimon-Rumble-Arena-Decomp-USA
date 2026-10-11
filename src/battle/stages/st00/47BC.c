#include "game_rotation.h"
#include "game_base_api.h"
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
INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D82BC);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D847C);

/* Pin $s0 ($16) to hoist the vtable lui/addiu above the arg-1 save. */
void func_800D8508(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3CCC;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}


INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D855C);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D85B4);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D8750);

/* Pin $s0 ($16) to hoist the vtable lui/addiu above the arg-1 save. */
void func_800D88D4(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3CA4;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D8928);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D8A3C);

u8 *func_800D8C10(u8 *self, u8 *owner) {
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_800D3C7C;
    *(u8 **)(self + 0x18) = owner;
    *(s32 *)(self + 0x1C) = 0;
    *(s16 *)(self + 0x34) = -0x540;
    *(s16 *)(self + 0x24) = -0x540;
    *(s16 *)(self + 0x3C) = -0x240;
    *(s16 *)(self + 0x2C) = -0x240;
    *(s16 *)(self + 0x2E) = 0x60;
    *(s16 *)(self + 0x26) = 0x60;
    *(s16 *)(self + 0x3E) = 0x360;
    *(s16 *)(self + 0x36) = 0x360;
    *(s16 *)(self + 0x40) = -0x400;
    *(s16 *)(self + 0x38) = -0x400;
    *(s16 *)(self + 0x30) = -0x400;
    *(s16 *)(self + 0x28) = -0x400;
    *(s16 *)(self + 0x54) = 0x240;
    *(s16 *)(self + 0x44) = 0x240;
    *(s16 *)(self + 0x5C) = 0x540;
    *(s16 *)(self + 0x4C) = 0x540;
    *(s16 *)(self + 0x4E) = 0x60;
    *(s16 *)(self + 0x46) = 0x60;
    *(s16 *)(self + 0x5E) = 0x360;
    *(s16 *)(self + 0x56) = 0x360;
    *(s16 *)(self + 0x60) = -0x400;
    *(s16 *)(self + 0x58) = -0x400;
    *(s16 *)(self + 0x50) = -0x400;
    *(s16 *)(self + 0x48) = -0x400;
    *(u32 *)(self + 0x20) = 0x808010;
    return self;
}

/* Pin $s0 ($16) to hoist the vtable lui/addiu above the arg-1 save. */
void func_800D8CE4(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3C7C;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

void func_800D8D38(u8 *self) {
    u8 *owner = *(u8 **)(self + 0x18);
    if (*(s32 *)(owner + 0x1050) != 0) {
        if (*(s32 *)(self + 0x1C) != 1) {
            *(u32 *)(self + 0x20) = 0x101080;
            *(s32 *)(self + 0x1C) = 1;
        }
    } else if (*(s32 *)(self + 0x1C) != 0) {
        *(u32 *)(self + 0x20) = 0x808010;
        *(s32 *)(self + 0x1C) = 0;
    }
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D8D94);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D8EEC);

/* Pin $s0 ($16) to hoist the vtable lui/addiu above the arg-1 save. */
void func_800D8F80(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3C54;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

