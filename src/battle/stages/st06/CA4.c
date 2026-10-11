#include "game_rotation.h"
#include "game_placement_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#include "psx.h"

extern u8 D_800D3C5C[];
extern u8 D_800D3D84[];
extern u8 D_800D3DAC[];
DISPENV *func_8001F92C(void);
s32 func_8002366C();
void func_80023F8C();
void func_80024204();
void func_8002BCEC(u8 *, s32);
void func_8002BDA8(u8 *);
s32 func_8002BD74();
s32 func_8002BD88();
s32 func_8002BDC8();
s32 func_8002BE14();
u8 *func_8002E6B0(const void *, s32, s32);
s32 func_80031C20();
void func_8005844C();
s32 func_8006EF44();
void func_8006F06C();
void func_800727AC();
u8 *func_800D4684(u8 *);
void func_800D5444();
u8 *func_800D489C();
u8 *func_800D49A4();
u8 *func_800D51A0();

/* The retail build keeps the object pointer in $a1 and the table address in
   $a0; pinning both locals reproduces the allocator's choice (see
   docs/DIFFICULT_FUNCTIONS.md, register pinning last resort). */
s32 func_800D47A4(u8 *arg0) {
    register u8 *a1 asm("$5") = arg0;
    register u8 *g asm("$4");
    s32 v;

    if (*(s32 *)(a1 + 0x20) == 0) {
        *(u16 *)(a1 + 0x1C) = *(u16 *)(a1 + 0x1C) + 8;
    } else {
        g = (u8 *)&D_8001093C;
        v = *(s16 *)(g + ((*(s32 *)(a1 + 0x24) << 5) & 0x3FE0));
        v = (s16)v;
        *(u16 *)(a1 + 0x1C) = -0x1C0 - (v >> 5);
    }
    return ++*(s32 *)(a1 + 0x24);
}

/* Pinned: retail keeps the faded `arg1>>1` half-rate byte in $v1 while the
   second expression reuses $v0; splitting the two temporaries into distinct
   locals and pinning the first to $v1 reproduces the allocator's choice.  See
   docs/DIFFICULT_FUNCTIONS.md, register pinning last resort. */
void func_800D4800(u8 *arg0, s32 arg1) {
    if (arg1 >= 0) {
        if (arg1 >= 0x100) {
            arg1 = 0xFF;
        }
    } else {
        arg1 = 0;
    }
    *(s32 *)(arg0 + 0x18) = arg1;
    if (*(s32 *)(arg0 + 0x20) == 0) {
        register s32 a asm("$3");
        s32 b;
        a = arg1 >> 1;
        b = ~(((arg1 * 3) << 6) >> 8);
        *(u8 *)(arg0 + 0x1E) = a;
        *(u8 *)(arg0 + 0x1F) = b;
    } else {
        *(u8 *)(arg0 + 0x1E) = arg1;
        *(u8 *)(arg0 + 0x1F) = arg1;
    }
}

void func_800D485C(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x20) == 0) {
        func_800D489C(arg0);
    } else {
        func_800D49A4(arg0);
    }
}

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D489C);

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D49A4);

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D4C38);

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D4CE0);

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D4E58);

u8 *func_800D506C(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 *p;
    u32 *q;
    u8 *s;
    u8 *t;
    s32 i;
    u8 *a1 = arg1;
    u8 *a2 = arg2;

    func_8002BC9C(arg0, 0);
    i = 0;
    p = D_800D3C5C;
    q = (u32 *)(arg0 + 0x1C);
    *(u32 *)(arg0 + 0x18) = 0;
    *(u32 *)(arg0 + 0x14) = (u32)D_800D3DAC;
    do {
        s = (u8 *)func_80031C20(a2, *(u32 *)p);
        p += 4;
        i++;
        t = (u8 *)func_800D51A0((u8 *)func_8002BD88(0x38), s);
        *q = func_8002BD74(t);
        func_8006F06C(a1, t);
        q++;
    } while (i < 4);
    return arg0;
}

void func_800D5144(u8 *arg0, s32 arg1) {
    s32 s2;
    u8 *p;
    s32 i;

    s2 = ((arg1 << 2) + arg1) << 3;
    p = arg0;
    p = p + 0x1C;
    i = 3;
    *(s32 *)(arg0 + 0x18) = arg1;
    do {
        u32 v = *(u32 *)p;
        p += 4;
        *(u32 *)(func_8002BDC8(v) + 0x34) = s2;
        i--;
    } while (i >= 0);
}

u8 *func_800D51A0(u8 *arg0, u8 *arg1) {
    u32 a;
    u32 b;
    u32 c;
    u32 r;
    s32 v;

    func_8002BC9C(arg0, 0);
    *(u32 *)(arg0 + 0x14) = (u32)D_800D3D84;
    *(u32 *)(arg0 + 0x18) = (u32)arg1;
    a = (s32)func_80037010(&D_8005EE48);
    b = (s32)func_80037010(&D_8005EE48);
    c = (s32)func_80037010(&D_8005EE48);
    *(u32 *)(arg0 + 0x1C) = a;
    *(u32 *)(arg0 + 0x20) = b;
    *(u32 *)(arg0 + 0x24) = c;
    func_8002366C(arg0 + 0x1C, arg0 + 0x1C);
    *(u32 *)(arg0 + 0x2C) = (s32)func_80037010(&D_8005EE48) & 0xFFF;
    v = (s32)func_80037010(&D_8005EE48);
    r = v % 8;
    *(u32 *)(arg0 + 0x30) = r;
    if (r == 0) {
        *(u32 *)(arg0 + 0x30) = 8;
    }
    return arg0;
}

void func_800D527C(u8 *arg0, u8 *arg1) {
    s32 a = *(s32 *)(arg1 + 0xD74);
    u8 *p;
    u8 *vec;
    s32 angle;
    *(s32 *)(arg0 + 0x2C) += *(s32 *)(arg0 + 0x30);
    p = *(u8 **)(arg0 + 0x18);
    *(s32 *)(p + 0x8) = 0;
    *(s32 *)(p + 0x2C) = 0x1000;
    *(s32 *)(p + 0x30) = 0;
    *(s32 *)(p + 0x34) = 0x1000;
    *(s32 *)(p + 0x38) = 0;
    *(s32 *)(p + 0x3C) = 0x1000;
    *(s32 *)(p + 0x40) = a;
    *(s32 *)(p + 0x44) = 0;
    *(s32 *)(p + 0x48) = 0;
    angle = *(u16 *)(arg0 + 0x34);
    vec = arg0 + 0x1C;
    *(s32 *)(p + 0x30) = 0;
    *(s32 *)(p + 0x38) = 0;
    *(s32 *)(p + 0x2C) = angle;
    *(s32 *)(p + 0x34) = angle;
    *(s32 *)(p + 0x3C) = angle;
    func_80023F8C(p + 0x2C, vec, *(s32 *)(arg0 + 0x2C));
    func_80024204(p + 0x2C, (u32)*(s32 *)(arg0 + 0x2C) << 1);
}

