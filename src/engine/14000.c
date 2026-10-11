#include "common.h"
#include "game_math.h"

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023800);


s32 func_8002384C(const VECTOR *v) {
    s32 xx = ((s64)v->vx * v->vx) >> 16;
    s32 yy = ((s64)v->vy * v->vy) >> 16;
    s32 zz = ((s64)v->vz * v->vz) >> 16;
    return (s32)((u32)xx + (u32)yy + (u32)zz);
}

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_800238C4);

s32 func_800239CC(const VECTOR *a, const VECTOR *b) {
    return (s32)((u32)((s64)a->vx * b->vx) +
                 (u32)((s64)a->vy * b->vy) +
                 (u32)((s64)a->vz * b->vz));
}

s32 func_80023A14(const VECTOR *a, const VECTOR *b) {
    return (s32)((u32)((s64)a->vx * b->vx) +
                 (u32)((s64)a->vy * b->vy) +
                 (u32)((s64)a->vz * b->vz)) >> 12;
}

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023A60);

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023ADC);

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023B10);

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023BE8);

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023C80);


INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023D50);

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023D60);

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023DC4);

INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023E34);



INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023EAC);
INCLUDE_ASM("asm/us/main/nonmatchings/14000", func_80023F8C);

