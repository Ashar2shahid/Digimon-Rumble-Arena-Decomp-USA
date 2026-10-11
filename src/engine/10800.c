#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/10800", func_80020000);

INCLUDE_ASM("asm/us/main/nonmatchings/10800", func_80020108);

INCLUDE_ASM("asm/us/main/nonmatchings/10800", func_80020240);

extern u32 D_801141B8;
extern u32 D_801141BC;


s32 func_80020258(void) {
    return D_801141B8;
}

s32 func_80020268(void) {
    return D_801141BC;
}

INCLUDE_ASM("asm/us/main/nonmatchings/10800", func_80020278);

u8 *func_800202E4(u8 *arg0) {
    return arg0 + 0x70;
}

INCLUDE_ASM("asm/us/main/nonmatchings/10800", func_800202EC);

INCLUDE_ASM("asm/us/main/nonmatchings/10800", func_80020430);

INCLUDE_ASM("asm/us/main/nonmatchings/10800", func_800204E4);

INCLUDE_ASM("asm/us/main/nonmatchings/10800", func_800206C0);

extern void func_80030458(u8 *);
extern void func_80030464(u8 *);
extern void func_80030470(u8 *);
extern void func_8003047C(u8 *);
extern void func_80030760(u8 *);

void func_80020720(u8 *a0) {
    func_80030458(a0 + 0x68);
}

void func_80020740(u8 *a0) {
    func_80030464(a0 + 0x68);
}

void func_80020760(u8 *a0) {
    func_80030470(a0 + 0x68);
}

void func_80020780(u8 *a0) {
    func_8003047C(a0 + 0x68);
}

void func_800207A0(u8 *a0) {
    func_80030760(a0 + 0x68);
}

extern s32 func_800304BC(void *channel, s32 animation, s32 value, s32 repeat, s32 speed);

s32 func_800207C0(u8 *object, s32 animation, s32 value, s32 repeat, s32 speed) {
    return func_800304BC(object + 0x68, animation, value, repeat, speed);
}

INCLUDE_ASM("asm/us/main/nonmatchings/10800", func_800207E8);
