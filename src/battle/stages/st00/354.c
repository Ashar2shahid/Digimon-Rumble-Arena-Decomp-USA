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
extern void func_80055B64(void *a0, void *a1);
INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D3E54);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D3F14);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D3F88);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D4074);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D4160);

void func_800D4354(u8 *self) {
    *(u16 *)(self + 0xDA8) = 0x300;
    *(u16 *)(self + 0xDAA) = 0xFE;
    *(u16 *)(self + 0xEF4) = 0;
    *(u16 *)(self + 0xDAC) = 0x10;
    *(u16 *)(self + 0xDAE) = 1;
    func_80055B64(self + 0xDA8, self + 0xE90);
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D43A0);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D4478);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D496C);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D4AA8);

void func_800D4D50(u8 *a0) {
    func_80071F64();
    if (func_8006F18C(a0) != 0) {
        *(s32 *)(a0 + 0x10C0) = 1;
        return;
    }
    *(s32 *)(a0 + 0x10C0) = 0;
    if (func_8006F12C(a0) != 0) {
        if (func_8006F178(a0) == 0) {
            return;
        }
    }
    func_800D4E90(a0);
    *(s32 *)(a0 + 0xD3C) = *(s32 *)(a0 + 0xD3C) + 1;
}

void func_800D4DC8(u8 *a0) {
    func_8001BEDC(*(u32 *)(a0 + 0xD4C));
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D4DEC);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D4E90);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D50A4);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D536C);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D5434);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D5894);

void func_800D5CAC(u8 *self) {
    u16 value = func_8006EFEC(self) & 3;
    s32 i;
    for (i = 0; i < 4; i++) {
        u16 current = value;
        value = current + 1;
        *(s32 *)(self + 0x1034 + i * 4) = current & 3;
    }
    *(s32 *)(self + 0x1044) = 0;
    *(s32 *)(self + 0x1030) = 0;
    *(s16 *)(self + 0x1048) = func_8006EFEC(self) & 1;
}

s32 func_800D5D14(u8 *a0) {
    s32 count;
    s32 i;
    u32 *p;

    count = 0;
    p = (u32 *)(a0 + 0x1020);
    for (i = 3; i >= 0; i--) {
        if (*p != 0) {
            count++;
        }
        p++;
    }
    return count;
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D5D48);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D6110);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D6814);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D7054);

void func_800D732C(u8 *a0) {
    u32 v;

    v = *(u32 *)(a0 + 0xEC8);
    v = (v + 0x40) & 0xFFF;
    *(u32 *)(a0 + 0xEC8) = v;
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D7344);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D73C4);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D79DC);

u8 *func_800D7C58(u8 *self, u8 *owner, u8 *other) {
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x18) = owner;
    *(u8 **)(self + 0x1C) = other;
    *(u8 **)(self + 0x14) = D_800D3D94;
    return self;
}


/* Pin $s0 ($16) to hoist the vtable lui/addiu above the arg-1 save. */
void func_800D7CB0(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3D94;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

void func_800D7D04(u8 *a0) {
    u8 *p;

    p = *(u8 **)(a0 + 0x18);
    if (*(s32 *)(p + 0x10C0) == 0) {
        func_8001FE8C(p + 0x1060);
        func_8001FD40(*(u8 **)(a0 + 0x18) + 0x1060);
    }
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D7D50);

/* Pin $s0 ($16) to hoist the vtable lui/addiu above the arg-1 save. */
void func_800D7E58(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3D1C;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

void func_800D7EAC(void) {
}

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D7EB4);

INCLUDE_ASM("asm/us/st00/nonmatchings/354", func_800D8170);

/* Pin $s0 ($16) to hoist the vtable lui/addiu above the arg-1 save. */
void func_800D8214(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3CF4;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

