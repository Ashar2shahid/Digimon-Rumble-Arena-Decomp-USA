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

extern s32 func_8007773C(u8 *arg0);
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

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D3FCC);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D42A0);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D43AC);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D44F0);

void func_800D47AC(u8 *arg0) {
    s32 flag;
    s32 i;
    func_80070300(arg0);
    flag = 0;
    if (func_8006F12C(arg0) != 0) {
        flag = 1;
    } else if (func_8006F178(arg0) != 0) {
        flag = 1;
    }
    for (i = 0; i < 2; i++) {
        u8 *p = func_800700B0(arg0, i);
        func_800D4850(arg0, p);
        if (flag == 0) {
            func_800D48C0(arg0, p);
        }
    }
}

void func_800D4850(u8 *arg0, u8 *arg1) {
    s32 v[3];
    s32 x;

    func_8007767C(arg1, v);
    x = v[0];
    if ((u32)(x + 0xE00) < 0x1D01) {
        return;
    }
    if (x >= -0xE00) {
        if (x > 0xF00) {
            x = 0xF00;
        }
    } else {
        x = -0xE00;
    }
    v[0] = x;
    func_80077654(arg1, v);
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D48C0);

/* The object selects a zone record; its first halfword determines the range. */
s32 func_800D4A48(u8 *object) {
    s32 v;
    s32 high_zone = 0x100;
    u16 *zone = (u16 *)(u32)func_8007773C(object);

    v = *zone;
    v &= 0x300;
    switch (v) {
    case 0x000:
        return 0xC0;
    case 0x100:
        return 0x40;
    case 0x200:
        return 0x80;
    case 0x300:
        return high_zone;
    }
    return 0xC0;
}

s32 func_800D4AB4(s32 arg0, u8 *arg1) {
    return *(s32 *)(arg1 + 4) >= 0x401;
}

void func_800D4AC8(u8 *arg0) {
    func_800727AC(arg0);
    func_800D4E94(arg0);
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D4AF4);

/* The three field loads land in $a0/$v1/$a1 in retail; pinning the two temps
   that the allocator otherwise swaps ($a0/$v1) reproduces the choice
   (see docs/DIFFICULT_FUNCTIONS.md, register pinning last resort). */
void func_800D4CF0(u8 *arg0) {
    u8 *v0;
    register s32 a asm("$4");
    register s32 b asm("$3");
    register s32 c asm("$5");

    func_800720EC();
    if (*(s32 *)(arg0 + 0x320) >= -0x2FF) {
        *(s32 *)(arg0 + 0x320) = -0x300;
        v0 = func_8006EF4C(arg0);
        *(s32 *)(v0 + 0x50) = 1;
        a = *(s32 *)(arg0 + 0x31C);
        b = *(s32 *)(arg0 + 0x320);
        c = *(s32 *)(arg0 + 0x324);
        *(s32 *)(v0 + 0x0) = a;
        *(s32 *)(v0 + 0x4) = b;
        *(s32 *)(v0 + 0x8) = c;
    }
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D4D54);

/* Retail keeps the loop counter in $a3, the record pointer in $a2, the arg0
   copy in $t0 and the two mult operands/products in $a0/$v0 (that is what
   makes cc1 emit `mult $4,$3; mflo $4` and the retail load schedule); each is
   pinned to reproduce the allocator's choice (see docs/DIFFICULT_FUNCTIONS.md,
   register pinning last resort). `tab` is deliberately left unpinned. */
void func_800D4DF0(u8 *arg0) {
    s32 v[3];
    register s32 i asm("$7") = 0;
    u8 *tab = ((u8 *)&D_8001093C) + 2;
    register u8 *base asm("$8") = arg0;
    register u8 *p asm("$6") = base + 0xE98;
    register s32 a asm("$4");
    register s32 b asm("$2");
    register s32 x asm("$5");
    register s32 y asm("$3");

    for (; i < 3; i++, p += 0x48) {
        s32 t = ((i << 10) + (*(s32 *)(base + 0xD78) << 5) + 0x10) & 0xFFF;
        s16 f = *(s16 *)(tab + t * 4);

        a = *(s32 *)(p + 0x20);
        a = a * f;
        a = a >> 12;
        x = *(s32 *)(p + 0x10) + a;
        b = *(s32 *)(p + 0x24);
        b = b * f;
        b = b >> 12;
        y = *(s32 *)(p + 0x14) + b;
        v[2] = 0;
        *(s32 *)(p + 0x8) = 0;
        *(s32 *)(p + 0x0) = x;
        *(s32 *)(p + 0x4) = y;
        v[0] = x;
        v[1] = y;
    }
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D4E94);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D501C);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D50E4);

void func_800D52DC(void) {
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D52E4);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D5424);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D5534);

void func_800D5644(u8 *arg0) {
    if (*(s32 *)(arg0 + 0xD80) == 0) {
        *(s32 *)(arg0 + 0xD80) = func_8001BE78((s32)(u32)D_8005F824, 0x67, 0);
    }
}

void func_800D5688(u8 *arg0) {
    if (*(s32 *)(arg0 + 0xD80) != 0) {
        func_8001BEDC(*(s32 *)(arg0 + 0xD80));
        *(s32 *)(arg0 + 0xD80) = 0;
    }
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D56C4);

/* cc1psx emits `sw s0`/`move s0,a1` before the vtable lui/addiu pair and orders
   `sw s0` before `sw ra`; retail hoists the lui/addiu pair above `sw ra`/
   `sw s0`.  Pinning the arg1 copy to $s0 ($16) reproduces retail's schedule
   (see docs/DIFFICULT_FUNCTIONS.md, register pinning last resort). */
void func_800D5798(u8 *arg0, s32 arg1) {
    register s32 f asm("$16");

    f = arg1;
    *(u32 *)(arg0 + 0x14) = (u32)D_800D3EC4;
    func_8001BEDC(*(s32 *)(arg0 + 0x8D8));
    func_8002BCEC(arg0, 0);
    if (f & 1) {
        func_8002BDA8(arg0);
    }
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D57F8);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D5970);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D5C48);

/* Retail loads arg1+0xD7C into $v1 and keeps it there for the delay-slot
   shift; pinning that temp to $3 reproduces it, and the vtable callback also
   comes out in $v1 only with the $3 pin (see docs/DIFFICULT_FUNCTIONS.md,
   register pinning last resort). */
void func_800D5D70(u8 *arg0, u8 *arg1) {
    s32 i;
    s32 j;
    s32 a;
    s32 b;
    s32 c;
    s32 x;
    s32 y;
    s32 z;
    s32 v;
    s32 n;
    s32 u;
    register s32 w asm("$3");
    u8 *p;
    u8 *q;

    i = *(s32 *)(arg0 + 0x68);
    a = *(s32 *)(arg0 + 0x58);
    p = arg0 + 0x18 + i * 0x10;
    j = (i + 1) & 3;
    x = *(s32 *)(p + 0x0);
    y = *(s32 *)(p + 0x4);
    z = *(s32 *)(p + 0x8);
    b = *(s32 *)(arg0 + 0x5C);
    x = x + a;
    y = y + b;
    q = arg0 + 0x18 + j * 0x10;
    c = *(s32 *)(arg0 + 0x60);
    *(s32 *)(q + 0x0) = x;
    *(s32 *)(q + 0x4) = y;
    z = z + c;
    *(s32 *)(q + 0x8) = z;
    *(s32 *)(arg0 + 0x68) = j;
    w = *(s32 *)(arg1 + 0xD7C);
    v = w << 2;
    *(s32 *)(arg0 + 0x58) = *(s32 *)(arg0 + 0x58) + (s32)func_80037010(&D_8005EE48) % 4;
    n = -((s32)func_80037010(&D_8005EE48) & 7);
    u = v + 0x10;
    *(s32 *)(arg0 + 0x5C) = n - u;
    *(s32 *)(arg0 + 0x60) = *(s32 *)(arg0 + 0x60) + (s32)func_80037010(&D_8005EE48) % 4;
    *(s32 *)(arg0 + 0x6C) = *(s32 *)(arg0 + 0x6C) - 2;
    if (*(s32 *)(arg0 + 0x6C) <= 0) {
        if (arg0 != 0) {
            u8 *r = *(u8 **)(arg0 + 0x14);
            register void (*fn)(u8 *, s32) asm("$3");
            fn = *(void (**)(u8 *, s32))(r + 0x1C);
            fn(arg0 + *(s16 *)(r + 0x18), 3);
        }
    }
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D5EB4);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D6034);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D611C);

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D64FC);

