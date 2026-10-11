#include "game_placement_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#include "game_positions.h"
#include "game_actor_queries.h"
#include "game_effect_constructor.h"

extern void func_8002BCEC(u8 *a0, s32 a1);
extern void func_8002BDA8(u8 *a0);
extern void func_80077774(u8 *a0, s32 a1);
extern void func_80078B70(u8 *a0);
extern void func_800C1F7C(u8 *a0);
extern void func_800C2FA0(u8 *a0);
extern s32 func_8002BE14(s32 a0);
extern s32 func_800C3F98(u8 *a0, s32 *a1, s32 a2, s32 a3);
extern void func_8002BF34(s32 a0, s32 a1);
extern s32 func_800BD748(s32 a0, s32 a1);
extern s32 func_800BDD08(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_8007C0A0(s32 a0, s32 a1, s32 a2);
extern s32 func_8007AFCC(s32 a0, s32 a1);
extern void func_800787A0(s32 a0, s32 a1);
extern void func_800774EC(s32 a0, s32 a1);
extern void func_800C2FF4(u8 *a0);
extern void func_800C3120(u8 *a0, s32 *a1, s32 *a2);
extern void func_800C3314(u8 *a0, s32 *a1, s32 *a2, s32 a3, s32 a4);
extern void func_800C33D0(u8 *a0);
extern s32 func_800C2500(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_800C339C(u8 *a0, s32 *a1, s32 a2);

extern s32 func_8002E860(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8002F6D0(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_8002F5B4(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_800254CC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8002447C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_800213C4(s32 a0);
extern s32 func_8006F0EC(s32 a0);
extern s32 func_8002BD74(s32 a0);
extern s32 func_8007A0A0(s32 a0);
extern void func_800C3090(u8 *a0, s32 *a1);
extern s32 func_800C38F0(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

extern s32 func_800BB2EC(s32 a0);
extern s32 func_800C31B0(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_800280A0(s32 a0);
extern s32 func_80030228(void);
extern void func_8002366C(s32 a0, s32 a1);
extern u8 D_8006D3FC[];
extern void func_8005844C(s32 a0, s32 a1);

extern s32 func_8007773C(s32 a0);
extern s32 func_80077860(s32 a0);
extern s32 func_8007760C(s32 a0);
extern void func_800C6588(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80077978(s32 a0);
extern void func_80079158(s32 a0, s32 a1, s32 a2, s32 a3);


extern s32 func_800237A0(s32 a0);

extern s32 D_800641B8;
extern s32 D_8006D00C;
extern s32 D_8006CFBC;
extern s32 D_8006CFDC;
extern s32 D_8006D58C;
extern s32 D_8006D034;
extern u8 D_8006CD84[];
extern u8 D_8006CD9C[];
extern u8 D_8006C9CC[];
extern u8 D_8006C9EC[];
extern u8 D_80065174[];
extern u8 D_80065154[];
extern s32 D_800D3A5C;
typedef struct { u8 bytes[20]; } EffectDescriptor;
extern EffectDescriptor D_8006D5B4[13];
extern u8 D_8006D4EC[];
extern s32 func_80053EFC(s32, s32);
extern u8 D_8006D49C[];
extern u8 D_8006D474[];
extern u8 D_8006D44C[];
extern u8 D_8006D424[];
extern u8 D_80010894[];
extern u8 D_8006D3AC[];
extern u8 D_8006D384[];
extern u8 D_8006D6B8[];
extern u8 D_800656C4[];
extern u8 D_8006CF78[];
extern u8 D_8006CF88[];

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C178C);

s32 func_800C1994(u8 *a0, s32 a1, s32 a2, s32 a3) {
    func_800C31B0(a0, (s32)&D_8006CD84, a1, a2, 0x40, 0x808080, a3);
    *(s32 *)(a0 + 0x14) = (s32)&D_8006CD9C;
    return (s32)a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C19F4);

void func_800C1ADC(u8 *a0, s32 a1) {
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C1B24(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C1B6C(u8 *a0, s32 a1) {
    *(s32 *)(a0 + 0x14) = (s32)&D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

s32 func_800C1BC0(u8 *a0) {
    func_800BB2EC((s32)a0);
    *(s32 *)(a0 + 0x14) = (s32)&D_8006D034;
    *(s32 *)(a0 + 0x4C4) = 0;
    return (s32)a0;
}

void func_800C1BF8(u8 *a0) {
    func_80078B70(a0);
    func_800C1F7C(a0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C1C24);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C1D28);

void func_800C1F7C(u8 *a0) {
    u8 *s0 = (u8 *)func_8007B16C(a0);

    if ((*(s32 *)(s0 + 0x388) >> 8) - (*(s32 *)(s0 + 0x398) >> 8) < -0x800) {
        *(s32 *)(a0 + 0x4C4) = 0;
        return;
    }
    if (*(s32 *)(a0 + 0x4C4) != 1) {
        return;
    }
    if (func_80077978(s0) != 0) {
        s32 buf[4];
        buf[0] = *(s32 *)((s32)D_8006CF78 + 0);
        buf[1] = *(s32 *)((s32)D_8006CF78 + 4);
        buf[2] = *(s32 *)((s32)D_8006CF78 + 8);
        buf[3] = *(s32 *)((s32)D_8006CF78 + 12);
        *(s32 *)(s0 + 0x3B4) = 0;
        *(s32 *)(s0 + 0x3B8) = 0;
        *(s32 *)(s0 + 0x3BC) = 0;
        *(s32 *)(s0 + 0x3C0) = 0;
        *(s32 *)(s0 + 0x3A4) = 0;
        *(s32 *)(s0 + 0x3A8) = 0;
        *(s32 *)(s0 + 0x3AC) = 0;
        *(s32 *)(s0 + 0x3B0) = 0;
        func_80079158((s32)s0, 0x408C1000, (s32)buf, 0);
        *(s32 *)(a0 + 0x4C4) = 2;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C2058);

void func_800C2100(u8 *a0) {
    u8 *s1 = (u8 *)func_8002BE14(0x120);

    if (s1 != NULL) {
        u8 *s0 = (u8 *)func_8002BD80(0x120, s1);
        func_800BD748((s32)s0, (s32)a0);
        *(s32 *)(s0 + 0x14) = (s32)&D_8006D00C;
    }
    func_8007AFCC((s32)a0, (s32)s1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C2174);

void func_800C22A0(u8 *a0, s32 a1, s32 a2) {
    s32 s0 = func_8002BE14(0xD4);
    register s32 v1 asm("$3"); /* PIN $v1 */

    if (s0 != 0) {
        s32 p = (s32)(u32)func_8002BD80(0xD4, (void *)(u32)s0);
        func_800C2500((u8 *)p, (s32)a0, a1, a2, 0x200);
    }
    func_8007AFCC((s32)a0, s0);
    func_800787A0((s32)a0, 0x11B);
    v1 = 0xA;
    *(s32 *)(a0 + 0x498) = v1;
    func_800774EC((s32)a0, 0xFFFF0000);
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C2344);

s32 func_800C2500(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    func_800BDD08((s32)a0, a1, a2, a3, a4);
    *(s32 *)(a0 + 0x18) = (s32)&D_8006CFBC;
    *(s32 *)(a0 + 0x14) = (s32)&D_8006CFDC;
    func_8007C0A0((s32)(a0 + 0x18), 0x5B05333, 0);
    return (s32)a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C255C);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C2654);

void func_800C29F0(u8 *a0, s32 a1) {
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C2A38(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

s32 func_800C2A80(u8 *a0, s32 a1) {
    s32 r;

    func_800BD748((s32)a0, a1);
    r = (s32)a0;
    *(s32 *)(a0 + 0x14) = (s32)&D_8006D00C;
    return r;
}

void func_800C2AB4(u8 *a0, s32 a1) {
    u8 *v1;

    *(s32 *)(a0 + 0x18) = (s32)&D_8006C9CC;
    *(s32 *)(a0 + 0x14) = (s32)&D_8006C9EC;
    *(s32 *)(a0 + 0x68) = (s32)&D_80065174;
    v1 = a0 + 0x38;
    *(s32 *)(*(s32 *)(a0 + 0x38) + 4) = *(s32 *)(a0 + 0x3C);
    *(s32 *)(*(s32 *)(v1 + 4)) = *(s32 *)(a0 + 0x38);
    *(s32 *)(a0 + 0x38) = (s32)v1;
    *(s32 *)(a0 + 0x3C) = (s32)v1;
    *(s32 *)(a0 + 0x18) = (s32)&D_80065154;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C2B54);

s32 func_800C2F68(s32 a0, s32 a1, s32 a2) {
    *(s32 *)a0 = a1;
    *(s16 *)(a0 + 4) = (s16)((a2 & 0x100) >> 4);
    func_800C2FA0(a0);
    return a0;
}

void func_800C2FA0(u8 *a0) {
    u16 *p = *(u16 **)a0;

    *(u16 *)(a0 + 0x20) = p[0];
    *(u16 *)(a0 + 0x22) = p[1];
    *(u16 *)(a0 + 0x24) = p[0] + p[2] - 1;
    *(u16 *)(a0 + 0x26) = p[1] + p[3] - 1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C2FF4);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C3090);

void func_800C3120(u8 *a0, s32 *a1, s32 *a2) {
    u8 *p = (u8 *)a2;
    s32 b0, b2, b4, b3, t;

    a1[1] = (s32)p;
    a1[2] = (s32)(p + 8);
    a1[3] = (s32)(p + 0x10);
    a1[4] = (s32)(p + 0x18);
    a1[5] = *(s32 *)(a0 + 0xC);
    b2 = *(u8 *)(a0 + 0x22);
    b0 = *(u8 *)(a0 + 0x20);
    b4 = *(u8 *)(a0 + 0x24);
    b3 = *(u8 *)(a0 + 0x26);
    *(u16 *)((u8 *)a1 + 0x18) = b0 | (b2 << 8);
    *(u16 *)((u8 *)a1 + 0x1C) = b0 | (b3 << 8);
    *(u16 *)((u8 *)a1 + 0x20) = b4 | (b2 << 8);
    *(u16 *)((u8 *)a1 + 0x24) = b4 | (b3 << 8);
    t = *(s32 *)a0;
    *(u16 *)((u8 *)a1 + 0x1A) = *(u16 *)(t + 0x10) + (*(u16 *)(a0 + 4) << 10);
    *(u16 *)((u8 *)a1 + 0x1E) = *(u16 *)(t + 0x12) | *(u16 *)(a0 + 4);
}

s32 func_800C31B0(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    func_800C2F68((s32)(a0 + 0x18), a1, a6);
    *(s32 *)(a0 + 0x14) = (s32)&D_8006D58C;
    func_800C3314(a0, (s32 *)a2, (s32 *)a3, a4, a5);
    return (s32)a0;
}

u8 *func_800C3258(u8 *a0, s32 a1, s32 *a2, s32 *a3, s32 a4, s32 a5, s32 a6) {
    u32 descriptor_base;
    u32 descriptor_offset;
    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    descriptor_base = (u32)D_8006D5B4;
    descriptor_offset = (u32)a1 * 20u;
    func_800C2F68((s32)(a0 + 0x18),
                    (s32)(descriptor_base + descriptor_offset), a6);
    *(s32 *)(a0 + 0x14) = (s32)&D_8006D58C;
    func_800C3314(a0, a2, a3, a4, a5);
    return a0;
}

void func_800C3314(u8 *a0, s32 *a1, s32 *a2, s32 a3, s32 a4) {
    s32 x, y, z;
    s32 dx, dy, dz;
    *(u16 *)(a0 + 0x40) = 0;
    x = a1[0];
    y = a1[1];
    z = a1[2];
    *(s32 *)(a0 + 0x28) = x;
    *(s32 *)(a0 + 0x2C) = y;
    *(s32 *)(a0 + 0x30) = z;
    dx = a2[0];
    dy = a2[1];
    dz = a2[2];
    *(s32 *)(a0 + 0x20) = a3;
    *(u16 *)(a0 + 0x1E) = 0;
    *(s32 *)(a0 + 0x54) = 0;
    *(s32 *)(a0 + 0x24) = a4;
    *(s32 *)(a0 + 0x44) = dx;
    *(s32 *)(a0 + 0x48) = dy;
    *(s32 *)(a0 + 0x4C) = dz;
}

s32 func_800C3360(u8 *a0) {
    s32 v;

    func_800C2FF4(a0 + 0x18);
    v = *(u16 *)(a0 + 0x40) + 1;
    *(u16 *)(a0 + 0x40) = v;
    return (s16)v;
}

void func_800C339C(u8 *a0, s32 *a1, s32 a2) {
    func_800C3120(a0 + 0x18, a1, (s32 *)a2);
    *a1 |= 8;
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C33D0);

void func_800C34D4(u8 *a0, u8 *a1) {
    s32 local[10];
    s32 *buffer = local;
    buffer[0] = 0;
    func_800C3090(a0 + 0x18, buffer);
    buffer[0] |= 8;
    D_800641B8 = func_8002E860((s32)buffer, D_800641B8, *(s32 *)(a1 + 8), *(s32 *)(a1 + 0x2C));
}

void func_800C3540(u8 *a0) {
    register u32 v1 asm("$3") = *(u16 *)(a0 + 0x44);
    register u32 v0 asm("$2") = *(u16 *)(a0 + 0x1E);
    register s32 a2 asm("$6");
    __asm__ volatile ("" ::: "memory");
    a2 = *(s32 *)(a0 + 0x20);
    v1 <<= 1;
    v0 += v1;
    a2 += 8;
    *(u16 *)(a0 + 0x1E) = (u16)v0;
    *(s32 *)(a0 + 0x20) = a2;
    func_800C33D0(a0);
}

u8 *func_800C357C(u8 *self, s32 *position, s32 *data, s32 mode, s32 tag) {
    s32 x, y, z;
    s32 base;
    func_8002BC9C((u8 *)(u32)(s32)self, 0);
    base = (s32)D_8006D5B4;
    func_800C2F68((s32)(self + 0x18), base + 0x8C, 0);
    *(u8 **)(self + 0x14) = D_8006D4EC;
    x = position[0];
    y = position[1];
    z = position[2];
    *(s32 *)(self + 0x28) = x;
    *(s32 *)(self + 0x2C) = y;
    *(s32 *)(self + 0x30) = z;
    *(s16 *)(self + 0x1E) = func_80053EFC(data[1], data[0]);
    *(s32 *)(self + 0x40) = mode;
    *(s32 *)(self + 0x24) = tag;
    *(s32 *)(self + 0x20) = 0;
    *(s32 *)(self + 0x44) = 0;
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C3638);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C3718);

void func_800C3870(u8 *a0, u8 *a1) {
    s32 local[10];
    s32 *buffer;
    s32 result;
    s32 mode;
    s32 a3;
    s32 a2;
    result = func_8006F0EC(D_800D3A5C);
    buffer = local;
    mode = (result == 0);
    buffer[0] = 0;
    func_800C3090(a0 + 0x18, buffer);
    a3 = *(s32 *)(a1 + 0x2C);
    a2 = *(s32 *)(a1 + 8);
    D_800641B8 = func_8002E860((s32)buffer, D_800641B8, a2, a3 + mode);
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C38F0);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C39E8);

void func_800C3AE8(u8 *a0, u8 *a1) {
    s32 local[10];
    s32 *buffer = local;
    buffer[0] = 0;
    func_8002F6D0(a0 + 0x24, *(s16 *)(a0 + 0x50), *(u8 *)(a0 + 0x52), *(u8 *)(a0 + 0x53));
    func_800C3090(a0 + 0x18, buffer);
    buffer[0] = (buffer[0] & ~3) | 9;
    D_800641B8 = func_8002E860((s32)buffer, D_800641B8, *(s32 *)(a1 + 8), *(s32 *)(a1 + 0x2C));
}

s32 func_800C3B74(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    func_800C38F0(a0, a1, a2, a3, a4, 0xA);
    *(s32 *)(a0 + 0x14) = (s32)&D_8006D474;
    return (s32)a0;
}

s32 func_800C3BB8(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    func_800C38F0(a0, a1, a2, a3, a4, 0xB);
    *(s32 *)(a0 + 0x14) = (s32)&D_8006D44C;
    return (s32)a0;
}

s32 func_800C3BFC(u8 *a0, s32 a1) {
    s32 v;

    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    *(s32 *)(a0 + 0x14) = (s32)&D_8006D424;
    *(s32 *)(a0 + 0x18) = func_8002BD74(a1);
    *(s32 *)(a0 + 0xE0) = 0;
    v = func_8007A0A0(a1);
    *(s32 *)(a0 + 0xDC) = ((u32)(v ^ 0xF) < 1);
    return (s32)a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C3C64);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C3DDC);

s32 func_800C3F98(u8 *a0, s32 *a1, s32 a2, s32 a3) {
    s32 s3;
    s32 a;
    s32 b;
    s32 c;
    register s32 x asm("$3"); /* PIN $v1 */
    s32 y;
    s32 z;

    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    *(s32 *)(a0 + 0x14) = (s32)&D_8006D3FC;
    s3 = (a2 >> 5) + 1;
    a = (s32)func_80037010(&D_8005EE48) >> 1;
    b = (s32)func_80037010(&D_8005EE48);
    c = (s32)func_80037010(&D_8005EE48);
    *(s32 *)(a0 + 0x18) = a;
    *(s32 *)(a0 + 0x1C) = b;
    *(s32 *)(a0 + 0x20) = c;
    func_8002366C((s32)(a0 + 0x18), (s32)(a0 + 0x18));
    x = a1[0];
    y = a1[1];
    z = a1[2];
    *(s32 *)(a0 + 0x38) = a2;
    *(s32 *)(a0 + 0x28) = x;
    *(s32 *)(a0 + 0x2C) = y;
    *(s32 *)(a0 + 0x30) = z;
    *(s32 *)(a0 + 0x3C) = (s32)func_80037010(&D_8005EE48) & 0xFFF;
    *(s32 *)(a0 + 0x40) = (s32)func_80037010(&D_8005EE48) % 48;
    *(s32 *)(a0 + 0x44) = ((u32)(s32)func_80037010(&D_8005EE48) % s3) + s3;
    *(s32 *)(a0 + 0x48) = a3;
    *(s32 *)(a0 + 0x4C) = 0;
    *(s32 *)(a0 + 0x50) = ((s32)func_80037010(&D_8005EE48) & 0x1F) + 0x10;
    return (s32)a0;
}

void func_800C4100(u8 *a0) {
    u8 *a1 = a0;
    s32 v;

    *(s32 *)(a1 + 0x3C) = *(s32 *)(a1 + 0x3C) + *(s32 *)(a1 + 0x40);
    v = *(s32 *)(a1 + 0x4C) + 1;
    *(s32 *)(a1 + 0x4C) = v;
    if (*(s32 *)(a1 + 0x50) < v) {
        if (a1 != NULL) {
            u8 *p = *(u8 **)(a1 + 0x14);
            ((void (*)(s32, s32))*(s32 *)(p + 0x1C))((s32)(a1 + *(s16 *)(p + 0x18)), 3);
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C416C);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C44A0);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C456C);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C471C);

s32 func_800C4AFC(u8 *a0, s32 a1, s32 a2, s32 a3) {
    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    *(s32 *)(a0 + 0x14) = (s32)&D_8006D3AC;
    *(s32 *)(a0 + 0x18) = a1 + a3;
    *(s32 *)(a0 + 0x1C) = a1;
    *(s32 *)(a0 + 0x20) = a2;
    *(s32 *)(a0 + 0x24) = a3;
    *(s32 *)(a0 + 0x28) = 0;
    *(s32 *)(a0 + 0x2C) = 0;
    return (s32)a0;
}

void func_800C4B74(u8 *a0) {
    u8 *a1 = a0;
    s32 v = *(s32 *)(a1 + 0x24);

    *(s32 *)(a1 + 0x18) = *(s32 *)(a1 + 0x18) + v;
    *(s32 *)(a1 + 0x1C) = *(s32 *)(a1 + 0x1C) + (v >> 1);
    if ((u32)*(s32 *)(a1 + 0x1C) >= 0x141) {
        if (a1 != NULL) {
            u8 *p = *(u8 **)(a1 + 0x14);
            ((void (*)(s32, s32))*(s32 *)(p + 0x1C))((s32)(a1 + *(s16 *)(p + 0x18)), 3);
        }
    }
}

void func_800C4BDC(u8 *a0, u8 *a1) {
    s32 source = *(s32 *)(a1 + 0x14);
    s32 s1 = source + 8;
    s32 s2 = func_800280A0(0x29);
    u8 *out = (u8 *)func_80030228();
    register s32 v asm("$7"); /* PIN $a3 */
    register u16 v1 asm("$3"); /* PIN $v1 */
    register u8 flags asm("$6"); /* PIN $a2 */
    register s32 t0 asm("$8"); /* PIN $t0 */

    v = *(volatile s32 *)(a0 + 0x20);
    v1 = *(volatile u16 *)(a0 + 0x18);
    flags = *(volatile u8 *)(out + 7);
    *(u16 *)(out + 8) = v1;
    v1 = 0xC0;
    *(u16 *)(out + 0xA) = v;
    t0 = *(u16 *)(a0 + 0x1C);
    flags |= 2;
    *(u16 *)(out + 0x12) = v;
    *(u8 *)(out + 4) = v1;
    *(u8 *)(out + 5) = v1;
    *(u8 *)(out + 6) = v1;
    *(u8 *)(out + 0xC) = 0;
    *(u8 *)(out + 0xD) = 0;
    *(u8 *)(out + 0xE) = 0;
    *(u8 *)(out + 7) = flags;
    *(u16 *)(out + 0x10) = t0;
    func_8005844C(s1, (s32)out);
    func_8005844C(s1, s2);
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C4C80);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C4D78);

void func_800C4F74(s32 a0) {
    s32 s0;

    s0 = func_8002BE14(0x54);
    if (s0 != 0) {
        s32 v0 = (s32)(u32)func_8002BD80(0x54, (void *)(u32)s0);
        func_800C3F98(v0, a0 + 0x1C, 0x280, 0x403020);
    }
    func_8002BF34(a0, s0);
}

void func_800C4FDC(u8 *a0, s32 a1, s32 a2) {
    u8 *s0 = (u8 *)func_8002BE14(0x3C);

    if (s0 != NULL) {
        u8 *p = (u8 *)func_8002BD80(0x3C, s0);
        func_800C6588((s32)p, a1, (s32)(a0 + 0x1C), 0x60, 0x20, a2, 0x8090A0);
    }
    func_8002BF34((s32)a0, (s32)s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C5070);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C5210);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C5560);

INCLUDE_ASM("asm/us/game/nonmatchings/5D3CC", func_800C571C);
