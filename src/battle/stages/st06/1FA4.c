#include "game_rotation.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#include "psx.h"

extern u8 D_800D3C5C[];
extern u8 D_800D3D84[];
extern u8 D_800D3DAC[];
DISPENV *func_8001F92C(void);
s32 func_8002366C();
void func_8002BCEC(u8 *, s32);
void func_8002BDA8(u8 *);
s32 func_8002BD74();
s32 func_8002BD88();
s32 func_8002BDC8();
u8 *func_8002E6B0(const void *, s32, s32);
s32 func_80031C20();
void func_8005844C();
s32 func_8006EF44();
void func_8006F06C();
void func_800727AC();
u8 *func_800D4684(u8 *);
u8 *func_800D489C();
u8 *func_800D49A4();
u8 *func_800D51A0();
extern u8 D_80010814[];
extern u8 D_800D3CDC[];
extern u8 D_800D3E3C[];
s32 func_800C3F98();
void func_800C4100(u8 *, u8 *);

/* psyq 4.6 (2.95.2) shape: the shipped 2.8.1 scheduler hoists the `func_80037010`
   load-delay differently, so this sub-range is built with 4.6 (UNIT_CC1_EXE). */
u8 *func_800D5AA4(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 x;

    func_800C3F98(arg0, D_80010814, arg1, arg2);
    *(u8 **)(arg0 + 0x14) = D_800D3CDC;
    x = (s32)func_80037010(&D_8005EE48) & 0x1F;
    *(s32 *)(arg0 + 0x50) = x + 0x60;
    return arg0;
}


void func_800D5B04(u8 *arg0, u8 *arg1) {
    s32 value;

    func_800C4100(arg0, arg1);
    value = *(s32 *)(arg1 + 0xD74);
    *(s32 *)(arg0 + 0x2C) = -0x200;
    *(s32 *)(arg0 + 0x30) = 0x4000;
    *(s32 *)(arg0 + 0x28) = value;
}

u8 *func_800D5B4C(u8 *arg0) {
    return arg0 + 0x31C;
}

s32 func_800D5B54(u8 *arg0) {
    return *(s32 *)(arg0 + 0xD74);
}

void func_800D5B60(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D5BA8(void) {
}

void func_800D5BB0(void) {
}

/* psyq 4.6 (2.95.2) shape: the store address is materialised before the call
   so 2.95.2 restores `ra` after the `lui %hi` (see UNIT_CC1_EXE). */
u8 *func_800D5BB8(u8 *arg0) {
    u8 *p;
    u32 *q;

    q = (u32 *)(arg0 + 0x18);
    func_8002BC9C(arg0, 0);
    p = arg0 + 0x14;
    *q = 0;
    *(u32 *)p = (u32)D_800D3E3C;
    *q = 0;
    return arg0;
}


void func_800D5BF4(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x18) = arg1;
}

void func_800D5BFC(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D5C44(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D5C8C(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D5CD4(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D5D1C(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D5D64(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D5DAC(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}
