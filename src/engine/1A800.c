#include "common.h"
extern u8 D_800192A8[];
extern void func_8002B0CC(void *);


INCLUDE_ASM("asm/us/main/nonmatchings/1A800", func_8002A010);

INCLUDE_ASM("asm/us/main/nonmatchings/1A800", func_8002A0F4);

void func_8002A240(u8 *arg0, s32 arg1) {
    register u8 *a3 __asm__("$7") = arg0;
    register s32 flag __asm__("$5") = arg1;
    register u8 *next __asm__("$6");
    register u8 *prev __asm__("$4");
    register u8 *next2 __asm__("$2");
    register u8 *prev2 __asm__("$3");
    register u32 *table __asm__("$2");

    /* Split the relocation halves around the list reads to match retail scheduling. */
    __asm__ ("lui %0, %%hi(D_800192A8)" : "=r"(table));
    __asm__("" : "=r"(a3) : "0"(a3));
    next = *(u8 **)a3;
    __asm__ volatile ("" : "=r"(next) : "0"(next) : "memory");
    prev = *(u8 **)(a3 + 4);
    __asm__ volatile ("addiu %0, %0, %%lo(D_800192A8)" : "=r"(table) : "0"(table));
    *(u32 **)(a3 + 0x1C) = table;
    *(u8 **)(next + 4) = prev;
    prev2 = *(u8 **)(a3 + 4);
    __asm__ volatile ("" : "=r"(prev2) : "0"(prev2) : "memory");
    next2 = *(u8 **)a3;
    flag &= 1;
    *(u8 **)prev2 = next2;
    *(u8 **)a3 = a3;
    *(u8 **)(a3 + 4) = a3;
    if (flag != 0) {
        func_8002B0CC(a3);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A800", func_8002A298);

INCLUDE_ASM("asm/us/main/nonmatchings/1A800", func_8002A3D8);

void func_8002A4FC(u8 *self, u32 flags) {
    *(void **)(self + 0x1C) = D_800192A8;
    *(u8 **)(*(u8 **)self + 4) = *(u8 **)(self + 4);
    *(u8 **)*(u8 **)(self + 4) = *(u8 **)self;
    *(u8 **)self = self;
    *(u8 **)(self + 4) = self;
    if (flags & 1) {
        func_8002B0CC(self);
    }
}

void func_8002A554(u8 *self, u32 flags) {
    *(void **)(self + 0x1C) = D_800192A8;
    *(u8 **)(*(u8 **)self + 4) = *(u8 **)(self + 4);
    *(u8 **)*(u8 **)(self + 4) = *(u8 **)self;
    *(u8 **)self = self;
    *(u8 **)(self + 4) = self;
    if (flags & 1) {
        func_8002B0CC(self);
    }
}

void func_8002A5AC(u8 *self, u32 flags) {
    *(void **)(self + 0x1C) = D_800192A8;
    *(u8 **)(*(u8 **)self + 4) = *(u8 **)(self + 4);
    *(u8 **)*(u8 **)(self + 4) = *(u8 **)self;
    *(u8 **)self = self;
    *(u8 **)(self + 4) = self;
    if (flags & 1) {
        func_8002B0CC(self);
    }
}

void func_8002A604(u8 *self, u32 flags) {
    *(void **)(self + 0x1C) = D_800192A8;
    *(u8 **)(*(u8 **)self + 4) = *(u8 **)(self + 4);
    *(u8 **)*(u8 **)(self + 4) = *(u8 **)self;
    *(u8 **)self = self;
    *(u8 **)(self + 4) = self;
    if (flags & 1) {
        func_8002B0CC(self);
    }
}

void func_8002A65C(u8 *self, u32 flags) {
    *(void **)(self + 0x1C) = D_800192A8;
    *(u8 **)(*(u8 **)self + 4) = *(u8 **)(self + 4);
    *(u8 **)*(u8 **)(self + 4) = *(u8 **)self;
    *(u8 **)self = self;
    *(u8 **)(self + 4) = self;
    if (flags & 1) {
        func_8002B0CC(self);
    }
}

void func_8002A6B4(u8 *self, u32 flags) {
    *(void **)(self + 0x1C) = D_800192A8;
    *(u8 **)(*(u8 **)self + 4) = *(u8 **)(self + 4);
    *(u8 **)*(u8 **)(self + 4) = *(u8 **)self;
    *(u8 **)self = self;
    *(u8 **)(self + 4) = self;
    if (flags & 1) {
        func_8002B0CC(self);
    }
}

void func_8002A70C(u8 *self, u32 flags) {
    *(void **)(self + 0x1C) = D_800192A8;
    *(u8 **)(*(u8 **)self + 4) = *(u8 **)(self + 4);
    *(u8 **)*(u8 **)(self + 4) = *(u8 **)self;
    *(u8 **)self = self;
    *(u8 **)(self + 4) = self;
    if (flags & 1) {
        func_8002B0CC(self);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A800", func_8002A764);

void func_8002A7B8(u8 *self, u32 flags) {
    *(void **)(self + 0x1C) = D_800192A8;
    *(u8 **)(*(u8 **)self + 4) = *(u8 **)(self + 4);
    *(u8 **)*(u8 **)(self + 4) = *(u8 **)self;
    *(u8 **)self = self;
    *(u8 **)(self + 4) = self;
    if (flags & 1) {
        func_8002B0CC(self);
    }
}
