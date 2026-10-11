#include "common.h"
#include "game_matrix_components.h"
#include "game_arc_cos.h"

INCLUDE_ASM("asm/us/main/nonmatchings/16800", func_80026000);

INCLUDE_ASM("asm/us/main/nonmatchings/16800", func_8002606C);

INCLUDE_ASM("asm/us/main/nonmatchings/16800", func_800260B8);

s32 func_80026168(s32 cosine) {
    if (cosine > 4096) {
        return 0;
    }
    if (cosine < -4096) {
        return 2048;
    }
    return D_8001493C[cosine + 4096];
}

s32 func_800261A8(s32 arg0) {
    return arg0;
}

s32 func_800261B0(s32 arg0) {
    return arg0;
}

MathWords2 *func_800261B8(MathWords2 *dst, const MathWords2 *src) {
    u32 first = src->words[0];
    u32 second = src->words[1];
    dst->words[0] = first;
    dst->words[1] = second;
    return dst;
}

s16 *func_800261D0(s16 *arg0, s16 arg1, s16 arg2, s16 arg3) {
    arg0[0] = arg1;
    arg0[1] = arg2;
    arg0[2] = arg3;
    return arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/16800", func_800261E4);

INCLUDE_ASM("asm/us/main/nonmatchings/16800", func_80026234);

s32 func_80026284(s32 arg0) {
    return arg0;
}

s32 func_8002628C(s32 arg0) {
    return arg0;
}

s32 *func_80026294(s32 *arg0) {
    arg0[0] = 0;
    arg0[1] = 0;
    arg0[2] = 0;
    arg0[3] = 0;
    return arg0;
}

MathVector3 *func_800262AC(MathVector3 *dst, const MathVector3 *src) {
    s32 x = src->x;
    s32 y = src->y;
    s32 z = src->z;
    dst->x = x;
    dst->y = y;
    dst->z = z;
    return dst;
}

s32 *func_800262CC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0[0] = arg1;
    arg0[1] = arg2;
    arg0[2] = arg3;
    return arg0;
}

s32 *func_800262E0(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0[0] = arg1;
    arg0[1] = arg2;
    arg0[2] = arg3;
    arg0[3] = arg4;
    return arg0;
}

MathVector3 *func_800262FC(MathVector3 *a, const MathVector3 *b) {
    u32 x = (u32)a->x;
    u32 y = (u32)a->y;
    u32 z = (u32)a->z;
    x += (u32)b->x;
    y += (u32)b->y;
    z += (u32)b->z;
    a->x = (s32)x;
    a->y = (s32)y;
    a->z = (s32)z;
    return a;
}

MathVector3 *func_80026334(MathVector3 *out, const MathVector3 *a, const MathVector3 *b) {
    u32 x = (u32)a->x;
    u32 y = (u32)a->y;
    u32 z = (u32)a->z;
    x += (u32)b->x;
    y += (u32)b->y;
    z += (u32)b->z;
    out->x = (s32)x;
    out->y = (s32)y;
    out->z = (s32)z;
    return out;
}

MathVector3 *func_8002636C(MathVector3 *a, const MathVector3 *b) {
    u32 x = (u32)a->x;
    u32 y = (u32)a->y;
    u32 z = (u32)a->z;
    x -= (u32)b->x;
    y -= (u32)b->y;
    z -= (u32)b->z;
    a->x = (s32)x;
    a->y = (s32)y;
    a->z = (s32)z;
    return a;
}

MathVector3 *func_800263A4(MathVector3 *out, const MathVector3 *a, const MathVector3 *b) {
    u32 x = (u32)a->x;
    u32 y = (u32)a->y;
    u32 z = (u32)a->z;
    x -= (u32)b->x;
    y -= (u32)b->y;
    z -= (u32)b->z;
    out->x = (s32)x;
    out->y = (s32)y;
    out->z = (s32)z;
    return out;
}

extern void func_8002366C(s32, s32);

void func_800263DC(s32 a0) {
    func_8002366C(a0, a0);
}

s32 func_800263FC(const MathVector3 *v) {
    u32 squared = (u32)((s64)v->x * v->x) + (u32)((s64)v->y * v->y) + (u32)((s64)v->z * v->z);
    return (s32)squared;
}

u32 func_80026438(const MathVector3 *v) {
    u32 squared = (u32)((s64)v->x * v->x) + (u32)((s64)v->y * v->y) + (u32)((s64)v->z * v->z);
    return squared >> 12;
}

extern s32 *func_800264C8(s32 *arg0, const s32 *arg1, const s32 *arg2);

s32 *func_80026478(s32 *arg0, const s32 *arg1, const s32 *arg2) {
    func_800264C8(arg0, arg1, arg2);
    return arg0;
}

extern s32 *func_80026528(s32 *arg0, const s32 *arg1, const s32 *arg2);

s32 *func_800264A0(s32 *arg0, const s32 *arg1, const s32 *arg2) {
    func_80026528(arg0, arg1, arg2);
    return arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/16800", func_800264C8);

INCLUDE_ASM("asm/us/main/nonmatchings/16800", func_80026528);

s32 func_80026588(s32 arg0) {
    return arg0;
}

s32 func_80026590(s32 arg0) {
    return arg0;
}

s32 func_80026598(s32 arg0) {
    return arg0 + 0x14;
}

INCLUDE_ASM("asm/us/main/nonmatchings/16800", func_800265A0);

extern void func_80024688(s32, s32, s32);

s32 func_800265EC(s32 a0, s32 a1) {
    func_80024688(a0, a0, a1);
    return a0;
}

u32 *func_8002661C(u32 *arg0) {
    arg0[0] = 0x1000;
    arg0[1] = 0;
    arg0[2] = 0x1000;
    arg0[3] = 0;
    arg0[4] = 0x1000;
    arg0[5] = 0;
    arg0[6] = 0;
    arg0[7] = 0;
    return arg0;
}

u32 *func_80026648(u32 *arg0, u32 arg1, u32 arg2, u32 arg3) {
    arg0[0] = (u16)arg1;
    arg0[1] = 0;
    arg0[2] = (u16)arg2;
    arg0[3] = 0;
    arg0[4] = (u16)arg3;
    arg0[5] = 0;
    arg0[6] = 0;
    arg0[7] = 0;
    return arg0;
}

u32 *func_8002667C(u32 *arg0, u32 arg1, u32 arg2, u32 arg3) {
    arg0[0] = 0x1000;
    arg0[1] = 0;
    arg0[2] = 0x1000;
    arg0[3] = 0;
    arg0[4] = 0x1000;
    arg0[5] = arg1;
    arg0[6] = arg2;
    arg0[7] = arg3;
    return arg0;
}

u32 *func_800266A8(u32 *m, const MathVector3 *v) {
    s32 x = v->x;
    s32 y = v->y;
    s32 z = v->z;
    m[0] = 0x1000;
    m[1] = 0;
    m[2] = 0x1000;
    m[3] = 0;
    m[4] = 0x1000;
    m[5] = (u32)x;
    m[6] = (u32)y;
    m[7] = (u32)z;
    return m;
}

u32 *func_800266E0(u32 *arg0, u32 arg1, u32 arg2, u32 arg3) {
    arg0[0] = (u16)arg1;
    arg0[1] = 0;
    arg0[2] = (u16)arg2;
    arg0[3] = 0;
    arg0[4] = (u16)arg3;
    return arg0;
}

s32 *func_80026708(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0[5] = arg1;
    arg0[6] = arg2;
    arg0[7] = arg3;
    return arg0;
}

u32 *func_8002671C(u32 *m, const MathVector3 *scale) {
    s32 y = scale->y;
    s32 z = scale->z;
    u16 x = scale->x;
    m[1] = 0;
    m[3] = 0;
    m[0] = x;
    m[2] = (u16)y;
    m[4] = (u16)z;
    return m;
}

u32 *func_8002674C(u32 *m, const s16 *scale) {
    s32 y = scale[1];
    s32 z = scale[2];
    u16 x = scale[0];
    m[1] = 0;
    m[3] = 0;
    m[0] = x;
    m[2] = (u16)y;
    m[4] = (u16)z;
    return m;
}

s32 *func_8002677C(s32 *m, const MathVector3 *v) {
    s32 x = v->x;
    s32 y = v->y;
    s32 z = v->z;
    m[5] = x;
    m[6] = y;
    m[7] = z;
    return m;
}

s32 *func_8002679C(s32 *m, const s16 *v) {
    s32 x = v[0];
    s32 y = v[1];
    s32 z = v[2];
    m[5] = x;
    m[6] = y;
    m[7] = z;
    return m;
}

s32 *func_800267BC(s32 *arg0) {
    arg0[5] = 0;
    arg0[6] = 0;
    arg0[7] = 0;
    return arg0;
}

extern s32 **func_8002447C(s32 **, s32, s32, s32);

void func_800267D0(s32 **arg0, const s32 *arg1) {
    func_8002447C(arg0, arg1[0], arg1[1], arg1[2]);
}

