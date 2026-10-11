#include "common.h"
extern void func_80024A84(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80023B10(u8 *a0, u8 *a1, u8 *a2);
extern void func_8002EFDC(u8 *a0, s32 *a1);
extern void func_8002EE60(s32 *a0, s32 *a1);
extern void func_800240C8(u8 *a0, s32 a1);
extern void func_80024204(u8 *a0, s32 a1);
extern u8 D_80010884;


INCLUDE_ASM("asm/us/main/nonmatchings/1F000", func_8002E860);

INCLUDE_ASM("asm/us/main/nonmatchings/1F000", func_8002E8F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1F000", func_8002E99C);

INCLUDE_ASM("asm/us/main/nonmatchings/1F000", func_8002EC04);

INCLUDE_ASM("asm/us/main/nonmatchings/1F000", func_8002ED70);

INCLUDE_ASM("asm/us/main/nonmatchings/1F000", func_8002ED98);

void func_8002EDDC(u8 *a0) {
    *(s32 *)(a0 + 0x24) = 0x1000;
    *(s32 *)(a0 + 0x20) = 0;
    *(s32 *)(a0 + 0x28) = 0;
    *(s32 *)(a0 + 0x50) = 1;
}

void func_8002EDF8(u8 *a0, u8 *a1) {
    s32 matrix[12];

    func_8002EFDC(a0, &matrix[4]);
    matrix[9] = 0;
    matrix[10] = 0;
    matrix[11] = 0;
    func_80023B10((u8 *)&matrix[4], (u8 *)matrix, a1);
    func_8002EE60((s32 *)a0, matrix);
}

void func_8002EE60(s32 *a0, s32 *a1) {
    register s32 d0 asm("$6");
    register s32 d1 asm("$7");
    register s32 d2 asm("$8");
    register s32 d4 asm("$10");
    register s32 d5 asm("$11");
    register s32 d6 asm("$9");
    register s32 s0 asm("$2");
    register s32 s1 asm("$3");

    d0 = a0[0];
    d1 = a0[1];
    d2 = a0[2];
    d4 = a0[4];
    d5 = a0[5];
    s0 = a1[0];
    d6 = a0[6];
    s1 = a1[1];

    d0 += s0;
    d1 += s1;
    s0 = a1[2];
    a0[0] = d0;
    a0[1] = d1;
    d2 += s0;
    a0[2] = d2;

    s1 = a1[0];
    d0 = a1[1];
    d1 = a1[2];
    a0[20] = 1;
    d4 += s1;
    d5 += d0;
    d6 += d1;
    a0[4] = d4;
    a0[5] = d5;
    a0[6] = d6;
}

void func_8002EECC(u8 *a0, s32 a1, s32 a2) {
    s32 matrix[8];

    if (a1 | a2) {
        func_8002EFDC(a0, matrix);
        func_80024204((u8 *)matrix, -a1);
        func_800240C8((u8 *)matrix, -a2);
        func_80023B10((u8 *)matrix, a0 + 0x10, &D_80010884);
        *(s32 *)(a0 + 0x50) = 1;
    }
}

void func_8002EF48(u8 *a0, s32 *a1) {
    register s32 *src asm("$6");
    register s32 v0 asm("$5");
    register s32 v1 asm("$4");
    register s32 v2 asm("$3");
    register s32 v3 asm("$2");

    if (*(s32 *)(a0 + 0x50) != 0) {
        func_80024A84((s32)(a0 + 0x30), (s32)a0, (s32)(a0 + 0x10),
                      (s32)(a0 + 0x20));
        *(s32 *)(a0 + 0x50) = 0;
    }

    src = (s32 *)(a0 + 0x30);
    __asm__("" : "+r"(src));
    v0 = src[0];
    v1 = src[1];
    v2 = src[2];
    v3 = src[3];

    a1[0] = v0;
    a1[1] = v1;
    a1[2] = v2;
    a1[3] = v3;

    v0 = src[4];
    v1 = src[5];
    v2 = src[6];
    v3 = src[7];
    a1[4] = v0;
    a1[5] = v1;
    a1[6] = v2;
    a1[7] = v3;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1F000", func_8002EFDC);
