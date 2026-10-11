#include "game_sprite_cleanup.h"
#include "game_rotation.h"
#include "game_math.h"
#include "game_placement_api.h"
#include "game_audio_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_random.h"

extern u8 D_80065154[];
extern u8 D_8005F824[];
extern u8 D_800D3EEC[];
extern u8 D_800D3DEC[];
extern u8 D_800D3DFC[];
extern u8 D_800D3E4C[];
extern u8 D_800D3EC4[];
extern u8 D_800D3DF4[];
extern u8 D_800D3E74[];
extern u8 D_800D3E9C[];
extern u8 D_800D3E24[];
extern u8 D_800D3D54[];
extern u8 D_800D3D5C[];
extern u8 D_800D3D7C[];
extern u8 D_800D3C94[];
extern u8 D_800D3C04[];
extern u8 D_800D3C34[];
extern u8 D_800D3B04[];
extern u8 D_800D3B14[];
extern u8 D_800D3B24[];
extern u8 D_800D3B34[];
extern u8 D_800D3B84[];
extern u8 D_800D3BD4[];
extern u8 D_800D3C64[];
extern u8 D_800D3C6C[];
extern u8 D_800D3C74[];
extern u8 D_800D3C84[];
extern u8 D_800D3F0C[];
extern u8 D_800D3F84[];
extern u8 D_80010894[];
extern u8 D_80010814[];
extern u8 D_800641B8[];
extern u8 D_80065174[];

extern void func_800727AC();
extern void func_800D4E94();
extern void func_8002B3D0();
extern void func_8001BEDC();

extern void func_8002BCEC();
extern void func_8002BDA8();
extern void func_8002BE14();
extern void func_8002D694();
extern void func_8002D6FC();
extern s32 func_8002D8B0();
extern u8 *func_8002E5C0();
extern u8 *func_8002FC28();
extern void func_8003E00C();
extern void func_8005844C();
extern void func_8006F04C();
extern void func_8006F06C();
extern void func_8006F09C();
extern s32 func_8006F12C();
extern s32 func_8006F178();
extern u8 *func_8006EF44();
extern u8 *func_800700B0();
extern void func_80070300();
extern void func_800720EC();

extern void func_80077654();

extern u8 *func_8007773C();
extern void func_80075F88();
extern void func_800794D4();
extern void func_80079964();
extern void func_8007F340();
extern void func_80079158();
extern void func_800C7A64();
extern void func_80071F64();
extern void func_800700CC();
extern u8 *func_8002BD88();
extern void func_8006F23C();
extern void func_8006ED08();
extern void func_80076B98();
extern void func_80076B50();
extern void func_80020F00();
extern void func_80020F7C();
extern void func_80020DC0();
extern void func_80020DE4();
extern void func_80070128();
extern u8 *func_8006EF4C();
extern u8 *func_80028078();
extern void func_80030228();
extern s32 func_80032EE8();
extern void func_80053E8C();
extern void func_800254CC();
extern void func_8002447C();
extern void func_800213C4();
extern void func_800237F4();
extern void func_8002E860();
extern void func_800330C8();
extern void func_8002310C();
extern void func_80023130();
extern void func_80023154();
extern void func_800231B0();
extern void func_80023258();
extern void func_800232A4();

typedef struct StageVec3 { s32 x, y, z; } StageVec3;

void func_800D6864(u8 *arg0) {
    register u8 *a1 asm("$5");
    register s32 v0 asm("$2");
    register s32 a0 asm("$4");
    register s32 v1 asm("$3");
    u8 *t;

    a1 = arg0;
    v0 = *(s32 *)(a1 + 0x28);
    a0 = *(s32 *)(a1 + 0x2C);
    v0 = v0 + a0;
    v1 = -a0 >> 3;
    *(s32 *)(a1 + 0x28) = v0;
    v0 = *(s32 *)(a1 + 0x34);
    a0 = a0 + v1;
    *(s32 *)(a1 + 0x2C) = a0;
    v0 = v0 - 8;
    *(s32 *)(a1 + 0x34) = v0;
    if (v0 <= 0 && a1 != 0) {
        register void (*fn)(u8 *, s32) asm("$3");
        t = *(u8 **)(a1 + 0x14);
        fn = *(void (**)(u8 *, s32))(t + 0x1C);
        fn(a1 + *(s16 *)(t + 0x18), 3);
    }
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D68D8);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D6A20);

/* The six field temps land in $a2/$a0/$a3/$a1/$v0/$v1 in retail and the vtable
   callback in $v1; pinning each of them reproduces the allocator's choice
   (see docs/DIFFICULT_FUNCTIONS.md, register pinning last resort). */
void func_800D6AF4(u8 *arg0) {
    register s32 a asm("$6");
    register s32 b asm("$4");
    register s32 c asm("$7");
    register s32 d asm("$5");
    register s32 e asm("$2");
    register s32 f asm("$3");

    a = *(s32 *)(arg0 + 0x18);
    b = *(s32 *)(arg0 + 0x1C);
    c = *(s32 *)(arg0 + 0x20);
    d = *(s32 *)(arg0 + 0x28);
    e = *(s32 *)(arg0 + 0x2C);
    f = *(s32 *)(arg0 + 0x30);
    a = a + d;
    e = e + 2;
    b = b + e;
    c = c + f;
    *(s32 *)(arg0 + 0x2C) = e;
    *(s32 *)(arg0 + 0x1C) = b;
    *(s32 *)(arg0 + 0x18) = a;
    *(s32 *)(arg0 + 0x20) = c;
    *(s32 *)(arg0 + 0x40) = *(s32 *)(arg0 + 0x40) + (d << 2);
    if (b >= 0x101) {
        if (arg0 != 0) {
            u8 *p = *(u8 **)(arg0 + 0x14);
            register void (*fn)(u8 *, s32) asm("$3");
            fn = *(void (**)(u8 *, s32))(p + 0x1C);
            fn(arg0 + *(s16 *)(p + 0x18), 3);
        }
    }
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D6B84);

s32 func_800D6CE8(u8 *arg0) {
    return *(s32 *)(arg0 + 0xD7C);
}

void func_800D6CF4(u8 *arg0, s32 arg1) {
    *(u32 *)arg0 = (u32)D_80065154;
    if (arg1 & 1) {
        func_8002B3D0(arg0);
    }
}

u8 *func_800D6D28(u8 *arg0, s32 arg1) {
    *(u32 *)arg0 = (u32)D_800D3EEC;
    *(s32 *)(arg0 + 4) = arg1;
    return arg0;
}

/* Retail loads the third word into $a2; cc1psx picks $a1, so the third temp
   is pinned (see docs/DIFFICULT_FUNCTIONS.md, register pinning last resort). */
void func_800D6D40(u8 *arg0, s32 *arg1) {
    s32 a = arg1[0];
    s32 b = arg1[1];
    register s32 c asm("$6") = arg1[2];

    *(s32 *)(arg0 + 0x8) = a;
    *(s32 *)(arg0 + 0xC) = b;
    *(s32 *)(arg0 + 0x10) = c;
}

void func_800D6D5C(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

/* Retail keeps the list node in $v1, `next` in $a2 (reused to reload the
   previous node) and `prev` in $a0; the arg1 copy is pinned to $s0 ($16) so
   the vtable/node address materialisation is hoisted above the callee-save
   stores, as in retail (see docs/DIFFICULT_FUNCTIONS.md, register pinning
   last resort). */
void func_800D6DA4(u8 *arg0, s32 arg1) {
    register u8 *n asm("$3");
    register u8 *next asm("$6");
    register u8 *prev asm("$4");
    register s32 f asm("$16");

    f = arg1;
    n = arg0 + 0x30;
    *(u32 *)(arg0 + 0x60) = (u32)D_80065174;
    next = *(u8 **)(arg0 + 0x30);
    prev = *(u8 **)(arg0 + 0x34);
    *(u8 **)(next + 4) = prev;
    next = *(u8 **)(n + 4);
    *(u8 **)(next + 0) = *(u8 **)(arg0 + 0x30);
    *(u8 **)(arg0 + 0x30) = n;
    *(u8 **)(arg0 + 0x34) = n;
    *(u32 *)(arg0 + 0x18) = (u32)D_80065154;
    func_8002BCEC(arg0, 0);
    if (f & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D6E2C(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D6E74(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D6EBC(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

u8 D_800D6F04[0x20] = {0};
