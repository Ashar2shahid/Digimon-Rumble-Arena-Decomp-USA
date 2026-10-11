#include "common.h"
#include "game_input.h"

extern s32 D_80065D70;
extern u32 *D_80065EB8;
extern u8 D_800643FC[];
extern u8 D_800643D4[];
extern u8 *D_800641A4;
extern u8 *D_80114210;
extern u32 D_80065D78[];
extern u32 D_80065DB8[];
extern u32 D_80065DFC[];
extern u32 D_80065D74;
extern u32 D_80065DF8;
extern void func_80065620(u32 *, u16);

void func_80064A30(u8 *a0);
s32 func_80064CB4(u8 *a0);
void func_8006492C(u8 *a0);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80064474);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80064514);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80064594);

void func_80064614(u8 *a0) {
    u8 *s0;
    u8 *s1;
    s32 r;

    if (*(s32 *)(a0 + 0x24) < 0) {
        return;
    }
    s0 = *(u8 **)(a0 + 0x20);
    s1 = D_80114210;
    func_80064A30(s0);
    r = func_80027004(s1, -1);
    if (func_80064CB4(s0) != 0 || (r & 0x8F0) != 0) {
        *(s32 *)(a0 + 0x24) = -1;
        func_8002B82C(a0);
    } else {
        *(s32 *)(a0 + 0x24) = *(s32 *)(a0 + 0x24) + 1;
    }
}

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_800646B4);

void func_8006471C(s32 *a0, s32 a1) {
    *a0 = a1;
}

void func_80064724(u8 *a0, s32 a1, s32 a2) {
    *(s32 *)(a0 + 0xC) = a1;
    *(s32 *)(a0 + 0x10) = a2;
}

void func_80064730(u8 *a0, s32 a1, s32 a2) {
    *(s32 *)(a0 + 0x14) = a1;
    *(s32 *)(a0 + 0x18) = a2;
}

s32 func_8006473C(u8 *a0) {
    s32 v1;
    s32 v0;

    v1 = *(s32 *)(a0 + 4);
    v0 = 0;
    if (v1 >= 0) {
        v0 = v1 < *(s32 *)(a0 + 8);
    }
    return v0;
}

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80064760);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_800648D0);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_8006492C);

u8 *func_80064990(u8 *a0) {
    return a0 + 0x7C;
}

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80064998);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80064A30);

s32 func_80064CB4(u8 *a0) {
    return *(s32 *)(a0 + 0x6C);
}

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80064CC0);
INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80064D58);


void func_80064DD0(s32 a0) {
    func_800457FC(a0, 0x1E0);
}

void func_80064DF0(void) {
    func_80064E18(D_80065D70);
}

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80064E18);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80064FCC);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065060);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_800651E8);

void func_80065260(void) {
}

void func_80065268(void) {
}

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065270);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_800652A4);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065330);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_800653C8);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065444);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065464);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_800654A0);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_800654E8);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_8006550C);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065530);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065620);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_800656B0);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_8006573C);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_800657D0);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065864);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_8006587C);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065900);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065930);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065C80);

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065D30);
__asm__(".word 0\n.word 0\n.word 0");
s32 D_80065D70 __attribute__((section(".text"), used)) = 0;

INCLUDE_ASM("asm/us/movie/nonmatchings/B4", func_80065D74);
