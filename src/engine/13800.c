#include "common.h"
#include "game_sdk_printf.h"

extern s32 D_800107A4[4];
extern s32 D_800107B4[4];
extern s32 D_800107C4[4];
extern u16 D_800107D4[8];
extern u16 D_800107E4[8];
extern u16 D_800107F4[8];
extern s32 D_80010804[24];
extern void func_8002320C(u32 *matrix, const s32 *values);
extern void func_80023258(u16 *matrix, const s32 *values);
extern void func_800232A4(u32 *matrix, const s32 *values);
extern void func_8002310C(u16 *matrix, const u16 *values);
extern void func_80023130(u16 *matrix, const u16 *values);
extern void func_80023154(u16 *matrix, const u16 *values);
extern void func_800231B0(u8 *matrix, const s32 *values);
extern void func_800232F0(u32 *matrix);
void func_80023034(u32 *matrix) {
    matrix[0] = 0x1000;
    matrix[1] = 0;
    matrix[2] = 0x1000;
    matrix[3] = 0;
    matrix[4] = 0x1000;
    matrix[5] = 0;
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 0x1000;
    matrix[9] = 0;
    matrix[10] = 0x1000;
    matrix[11] = 0;
    matrix[12] = 0x1000;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 0;
    func_8002320C(matrix, D_800107A4);
    func_80023258((u16 *)matrix, D_800107B4);
    func_800232A4(matrix, D_800107C4);
    func_8002310C((u16 *)matrix, D_800107D4);
    func_80023130((u16 *)matrix, D_800107E4);
    func_80023154((u16 *)matrix, D_800107F4);
    func_800231B0((u8 *)matrix, D_80010804);
    func_800232F0(matrix);
}

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_8002310C);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_80023130);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_80023154);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_80023178);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_800231B0);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_8002320C);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_80023258);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_800232A4);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_800232F0);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_80023354);

s32 func_80023468(s32 arg0) {
    return arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_80023470);

extern char D_80010914[];

void func_800234EC(u16 *arg0) {
    func_8003E2DC(D_80010914, arg0[0], arg0[1], arg0[2]);
}

extern char D_80010928[];

void func_8002351C(u32 *arg0) {
    func_8003E2DC(D_80010928, arg0[0], arg0[1], arg0[2]);
}

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_8002354C);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_800235DC);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_8002366C);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_800237A0);

INCLUDE_ASM("asm/us/main/nonmatchings/13800", func_800237F4);
