#include "common.h"

extern s32 func_8002150C(const s32 *plane, const s32 *point);

INCLUDE_ASM("asm/us/main/nonmatchings/11800", func_80021000);

void *func_80021074(u8 *self) {
    return *(void **)(self + 0x30);
}

INCLUDE_ASM("asm/us/main/nonmatchings/11800", func_80021080);


void func_800212F0(s32 *plane, const s32 *point) {
    u32 sum = (u32)((s64)plane[0] * point[0]) +
              (u32)((s64)plane[1] * point[1]) +
              (u32)((s64)plane[2] * point[2]);
    plane[3] = (s32)(0u - sum);
}

INCLUDE_ASM("asm/us/main/nonmatchings/11800", func_80021340);

INCLUDE_ASM("asm/us/main/nonmatchings/11800", func_800213C4);

INCLUDE_ASM("asm/us/main/nonmatchings/11800", func_80021430);

s32 func_800214E0(const s32 *plane, const s32 *point, s32 threshold) {
    s32 value = func_8002150C(plane, point);
    return (s32)(0u - (u32)threshold) < value;
}

s32 func_8002150C(const s32 *plane, const s32 *point) {
    u32 sum = (u32)((s64)plane[0] * point[0]) +
              (u32)((s64)plane[1] * point[1]) +
              (u32)((s64)plane[2] * point[2]) + (u32)plane[3];
    return (s32)sum >> 12;
}


INCLUDE_ASM("asm/us/main/nonmatchings/11800", func_80021560);

INCLUDE_ASM("asm/us/main/nonmatchings/11800", func_80021694);

INCLUDE_ASM("asm/us/main/nonmatchings/11800", func_80021710);
