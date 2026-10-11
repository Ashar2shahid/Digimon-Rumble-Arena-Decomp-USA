#include "game_destructor_api.h"
#include "game_base_api.h"
#include "common.h"

extern u8 D_800D3C2C[];
extern u8 D_800D3C54[];
extern u8 D_800D3CA4[];
extern void func_8002BCEC(void *a0, s32 a1);
extern void func_8002BDA8(void *a0);
extern u8 D_800D3BE4[];
extern u8 *func_8007C35C(u8 *, s32);
extern void *func_8002B364(s32);
void func_800D56F0(void *);

u8 *func_800D3D44(u8 *self, s32 value) {
    func_8007C35C(self, value);
    *(u8 **)(self + 4) = D_800D3BE4;
    *(s32 *)(self + 8) = 0;
    *(s32 *)(self + 0xC) = 0;
    *(s32 *)(self + 0x10) = 0;
    *(s32 *)(self + 0x14) = 0;
    *(s32 *)(self + 0x18) = 0;
    *(s32 *)(self + 0x1C) = 0;
    return self;
}

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D3D90);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D4038);

u8 *func_800D4350(s32 unused, s32 also_unused, s32 value) {
    u8 *self = func_8002B364(0x20);
    return func_800D3D44(self, value);
}

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D4384);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D445C);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D44C4);

void func_800D4548(u8 *arg0) {
    *(u16 *)(arg0 + 0x103C) = 0;
}

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D4550);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D45CC);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D46AC);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D4738);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D48D8);

void func_800D49B0(u8 *arg0) {
    *(u16 *)(arg0 + 0x15A2) = 0;
    *(u16 *)(arg0 + 0x15A4) = 0;
    *(u16 *)(arg0 + 0x15A8) = 0;
    *(u16 *)(arg0 + 0x15A6) = 0;
    *(u16 *)(arg0 + 0xF34) = 0x1E;
}

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D49CC);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D4A4C);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D4B84);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D4C80);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D4E58);

void func_800D4FBC(u8 *a0, s32 a1) {
    s32 f;
    f = a1;
    *(u8 **)(a0 + 0x14) = D_800D3C54;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D5010);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D51A8);

u8 *func_800D5348(u8 *arg0, u8 *arg1, s32 arg2) {
    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_800D3C2C;
    *(u8 **)(arg0 + 0x18) = arg1;
    *(u16 *)(arg0 + 0x1C) = arg2;
    *(s16 *)(arg0 + 0x34) = -0x40;
    *(s16 *)(arg0 + 0x24) = -0x40;
    *(s16 *)(arg0 + 0x3C) = 0x40;
    *(s16 *)(arg0 + 0x2C) = 0x40;
    *(s16 *)(arg0 + 0x2E) = -0x40;
    *(s16 *)(arg0 + 0x26) = -0x40;
    *(s16 *)(arg0 + 0x3E) = 0x40;
    *(s16 *)(arg0 + 0x36) = 0x40;
    *(s16 *)(arg0 + 0x40) = 0;
    *(s16 *)(arg0 + 0x38) = 0;
    *(s16 *)(arg0 + 0x30) = 0;
    *(s16 *)(arg0 + 0x28) = 0;
    *(s16 *)(arg0 + 0x1E) = 0;
    func_800D56F0(arg0);
    return arg0;
}

void func_800D53E4(u8 *a0, s32 a1) {
    s32 f;
    f = a1;
    *(u8 **)(a0 + 0x14) = D_800D3C2C;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

extern void func_800D5470(void *self);
void func_800D5438(u8 *self, void *owner) {
    func_800D56F0(self);
    func_800D5470(self);
    *(u16 *)(self + 0x1E) += 1;
}

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D5470);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D56F0);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D5830);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D5A0C);

void func_800D5AB4(u8 *a0, s32 a1) {
    s32 f;
    f = a1;
    *(u8 **)(a0 + 0x14) = D_800D3CA4;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D5B08);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D5C78);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D5E80);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D60BC);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D6198);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D63F0);

s32 func_800D6640(u8 *arg0) {
    return *(s32 *)(arg0 + 0x20) + 0x2C;
}

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D664C);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D66B4);

void func_800D675C(u8 *self, s32 destroyFlags) {
    *(u8 **)(self + 0x14) = D_800D3BE4 + 0x20;
    func_8002BCEC(self, 0);
    if (destroyFlags & 1) {
        func_8002BDA8(self);
    }
}

void func_800D67B0(u8 *self, void *owner) {
    u32 count = *(u16 *)(self + 0x1C) + 1;
    *(u16 *)(self + 0x1C) = (u16)count;
    if ((u16)count >= 17 && self != 0) {
        u8 *table = *(u8 **)(self + 0x14);
        void (*destroy)(u8 *, s32) = *(void (**)(u8 *, s32))(table + 0x1C);
        destroy(self + *(s16 *)(table + 0x18), 3);
    }
}

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D6818);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D69A0);

INCLUDE_ASM("asm/us/st09/nonmatchings/244", func_800D69D8);

void func_800D6A04(u8 *self, s32 flags) {
    func_8007C374(self, flags);
}

/* Preserved trailing tables/state; these bytes are data. */
INCLUDE_ASM("asm/us/st09/nonmatchings/244", D_800D6A24);
