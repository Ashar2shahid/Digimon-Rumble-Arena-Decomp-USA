#include "game_rotation.h"
#include "common.h"

/* Adapted from REGAME-DTBE quaternion.c; see the retained MIT license. */
INCLUDE_ASM("asm/us/main/nonmatchings/15800", func_80025000);

INCLUDE_ASM("asm/us/main/nonmatchings/15800", func_800251C4);

INCLUDE_ASM("asm/us/main/nonmatchings/15800", func_800252D4);

INCLUDE_ASM("asm/us/main/nonmatchings/15800", func_8002542C);

INCLUDE_ASM("asm/us/main/nonmatchings/15800", func_80025480);

INCLUDE_ASM("asm/us/main/nonmatchings/15800", func_800254CC);

INCLUDE_ASM("asm/us/main/nonmatchings/15800", func_8002551C);

RotationQuaternion *func_80025598(RotationQuaternion *q, s32 angle) {
    s16 sin, cos;
    angle /= 2;
    sin = D_8001093C[angle & 0xFFF].sin;
    cos = D_8001093C[angle & 0xFFF].cos;
    q->y = 0;
    q->z = 0;
    q->x = sin;
    q->w = cos;
    return q;
}

RotationQuaternion *func_800255D8(RotationQuaternion *q, s32 angle) {
    s16 sin, cos;
    angle /= 2;
    sin = D_8001093C[angle & 0xFFF].sin;
    cos = D_8001093C[angle & 0xFFF].cos;
    q->x = 0;
    q->z = 0;
    q->y = sin;
    q->w = cos;
    return q;
}

RotationQuaternion *func_80025618(RotationQuaternion *q, s32 angle) {
    s16 sin, cos;
    angle /= 2;
    sin = D_8001093C[angle & 0xFFF].sin;
    cos = D_8001093C[angle & 0xFFF].cos;
    q->x = 0;
    q->y = 0;
    q->z = sin;
    q->w = cos;
    return q;
}

INCLUDE_ASM("asm/us/main/nonmatchings/15800", func_80025658);

RotationQuaternion *func_80025750(RotationQuaternion *out, RotationQuaternion *q) {
    s16 x = q->x;
    s16 y = q->y;
    s16 z = q->z;
    s16 w = q->w;
    out->x = -x;
    out->y = -y;
    out->z = -z;
    out->w = w;
    return out;
}

INCLUDE_ASM("asm/us/main/nonmatchings/15800", func_80025784);
