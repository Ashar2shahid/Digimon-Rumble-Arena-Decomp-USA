#include "game_destructor_api.h"
#include "game_base_api.h"
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

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D3E90);

void *func_800D3EE8(s32 unused0, s32 unused1, s32 value) {
    void *object = func_8002B364(0x18);
    return func_800D3C94(object, value);
}

void func_800D3F1C(u8 *arg0) {
    *(s16 *)(arg0 + 0xF70) = 0;
    *(s16 *)(arg0 + 0xF6A) = 0;
    *(s16 *)(arg0 + 0xF7E) = 0;
    *(s16 *)(arg0 + 0xF7C) = 0;
    *(s16 *)(arg0 + 0xF82) = 0;
    *(s16 *)(arg0 + 0xF80) = 0;
}

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D3F38);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D3FF0);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D4038);

void func_800D4174(u8 *arg0) {
    *(s16 *)(arg0 + 0xF84) = 0;
    *(s16 *)(arg0 + 0xF86) = 0;
    *(s16 *)(arg0 + 0xF8A) = 0;
    *(s16 *)(arg0 + 0xF88) = 0;
    *(s16 *)(arg0 + 0xF34) = 0x1E;
}

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D4190);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D4210);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D4324);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D4420);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D477C);

void func_800D486C(u8 *a0, s32 a1) {
    s32 f;
    f = a1;
    *(u8 **)(a0 + 0x14) = D_800D3BF4;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D48C0);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D49F8);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D4C90);

void func_800D4D98(u8 *a0, s32 a1) {
    s32 f;
    f = a1;
    *(u8 **)(a0 + 0x14) = D_800D3BCC;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D4DEC);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D4F44);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D50C4);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D5248);

u8 *func_800D5360(u8 *arg0, s32 arg1, s32 arg2) {
    func_8002BC9C(arg0, 0);
    *(s32 *)(arg0 + 0x14) = (s32)D_800D3BA4;
    *(s32 *)(arg0 + 0x18) = arg1;
    *(s16 *)(arg0 + 0x1C) = arg2;
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
    *(s32 *)(arg0 + 0x20) = 0;
    func_800D568C(arg0);
    return arg0;
}

void func_800D5400(u8 *a0, s32 a1) {
    s32 f;
    f = a1;
    *(u8 **)(a0 + 0x14) = D_800D3BA4;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D5454);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D54D0);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D568C);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D57CC);

u8 *func_800D5910(u8 *arg0, u8 *arg1, s32 *arg2) {
    s32 x;
    s32 y;
    s32 z;
    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_800D3B7C;
    *(u8 **)(arg0 + 0x18) = arg1;
    x = arg2[0];
    y = arg2[1];
    z = arg2[2];
    *(s16 *)(arg0 + 0x30) = -0x100;
    *(s16 *)(arg0 + 0x20) = -0x100;
    *(s16 *)(arg0 + 0x38) = 0x100;
    *(s16 *)(arg0 + 0x28) = 0x100;
    *(s16 *)(arg0 + 0x2A) = -0x100;
    *(s16 *)(arg0 + 0x22) = -0x100;
    *(s16 *)(arg0 + 0x3A) = 0x100;
    *(s16 *)(arg0 + 0x32) = 0x100;
    *(s16 *)(arg0 + 0x3C) = 0;
    *(s16 *)(arg0 + 0x34) = 0;
    *(s16 *)(arg0 + 0x2C) = 0;
    *(s16 *)(arg0 + 0x24) = 0;
    *(s16 *)(arg0 + 0x1C) = 0;
    *(s32 *)(arg0 + 0x40) = x;
    *(s32 *)(arg0 + 0x44) = y;
    *(s32 *)(arg0 + 0x48) = z;
    return arg0;
}

void func_800D59B8(u8 *a0, s32 a1) {
    s32 f;
    f = a1;
    *(u8 **)(a0 + 0x14) = D_800D3B7C;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

void func_800D5A0C(u8 *self, void *owner) {
    u32 count = *(u16 *)(self + 0x1C) + 1;
    *(u16 *)(self + 0x1C) = (u16)count;
    if ((u16)count >= 17 && self != 0) {
        u8 *table = *(u8 **)(self + 0x14);
        void (*destroy)(u8 *, s32) = *(void (**)(u8 *, s32))(table + 0x1C);
        destroy(self + *(s16 *)(table + 0x18), 3);
    }
}

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D5A74);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D5BF0);

void func_800D5C94(u8 *a0, s32 a1) {
    s32 f;
    f = a1;
    *(u8 **)(a0 + 0x14) = D_800D3B54;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D5CE8);

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D5DDC);

void func_800D60E4(u8 *self, s32 flags) {
    func_8007C374(self, flags);
}

INCLUDE_ASM("asm/us/st07/nonmatchings/194", func_800D6104);
