#include "game_action_api.h"
#include "game_velocity_api.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_actor_queries.h"
#include "game_effects.h"

extern void func_8009CBCC(u8 *, u8 *);
extern void func_8009CE10(u8 *, u8 *);
extern void func_8009A274(u8 *, u8 *);
extern void func_8009A3A4(u8 *);
extern void func_8002BCEC(u8 *, s32);
extern void func_8002BDA8(u8 *);
extern void func_8001BEDC(u8 *);
extern u8 *func_80076FD8(u8 *);

extern s32 func_8007773C(u8 *);
extern void func_80077654(u8 *, s32 *);
extern void func_8007B0B4(u8 *);
extern u8 D_800699F4[];
extern u8 D_800699CC[];
extern u8 D_8006D58C[];
extern u8 D_8006A29C[];
extern u8 D_80069D1C[];
extern void func_8009C930(u8 *);
extern void func_8009CB50(u8 *);
extern s32 func_800787A0(u8 *, s32);
extern void func_80079D58(u8 *);
extern void func_80079D80(u8 *, s32);
extern void func_80079D88(u8 *, s32);
extern s32 func_8007A084(u8 *);
extern void func_8007AFCC(u8 *, u8 *);
extern s32 func_80077730(u8 *);
extern s32 func_80077978(u8 *);
extern void func_8007BD08(u8 *);
extern void func_800774EC(u8 *, s32);
extern u8 *func_8002BE14(s32);
extern s32 func_8009ADF8(u8 *, u8 *, s32);
extern void func_8009BAEC(u8 *, u8 *, s32, s32);
extern void func_8009D4C4(u8 *, u8 *);
extern void func_8009D7A4(u8 *, u8 *);
extern void func_8009ABD8(u8 *);
extern void func_8009AA1C(u8 *);
extern u8 D_80069ED0[];
extern s32 func_800237A0(s32);
extern void func_800C6588(u8 *, s32, u8 *, s32, s32, s32, s32);
extern void func_800C7478(s32, s32);
extern void func_8002BF34(u8 *, u8 *);
extern void func_8007BCD4(u8 *);
extern u8 *func_800C6090(u8 *, s32, u8 *, u8 *, s32, s32, s32);
extern void func_800C72C0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_8007C0A0(s32, s32, s32);
extern u8 D_8006A204;
extern u8 D_8006A224;
extern u8 D_8006D730[];
extern u8 D_8006D750[];
extern u8 D_80065174[];
extern u8 D_80065154[];
extern u8 D_80069D2C[];
extern void func_80079AA4(u8 *, s32, s32, s32, s32);
extern void func_8007B748(u8 *, s32, u8 *, s32);
extern void func_8007BE3C(u8 *, s32);
extern void func_8007BD70(u8 *, s32);
extern void func_800C591C(u8 *, u8 *, u8 *, s32, s32, s32);
extern void func_8009B27C(u8 *, u8 *);
extern void func_8009B91C(u8 *, u8 *);
extern void func_8009B628(u8 *, u8 *);
extern u8 D_8006A274[];
extern void func_8007BC50(void);
extern void func_8007BCA0(u8 *);
extern void func_8007BEC0(u8 *);
extern void func_800794D4(u8 *, s32);
extern void func_80079158(u8 *, s32, u8 *, s32);
extern void func_8007AFF0(u8 *, u8 *, s32);
extern u8 D_80010814;
extern u8 *func_800994D4(u8 *, u8 *, s32, const s32 *, s32, s32);
extern void func_8009A1E8(u8 *);
extern void func_8009A468(u8 *, s32, u8 *);
extern void func_8009A3E0(u8 *);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_80098EBC);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_80098F50);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_80099184);

void func_80099444(u8 *a0) {
    s32 s0;
    u8 *s1;

    s0 = *(s32 *)(a0 + 0xBC);
    if (s0 < 0x12C) {
        s0 = 0x12C;
    }
    s1 = func_8002BE14(0x54);
    if (s1 != 0) {
        func_800994D4((u8 *)func_8002BD80(0x54, s1), (u8 *)(u32)*(s32 *)(a0 + 0x84),
                      *(s32 *)(a0 + 0x88), (s32 *)(a0 + 0x8C), *(s32 *)(a0 + 0xB0), s0);
    }
    func_8002BF34(a0, s1);
}

u8 *func_800994D4(u8 *self, u8 *actor, s32 kind, const s32 *position, s32 lifetime, s32 power) {
    s32 x, y, z;
    s32 step;

    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_800699F4;
    *(u8 **)(self + 0x18) = actor;
    *(s32 *)(self + 0x1C) = kind;
    x = position[0];
    y = position[1];
    z = position[2];
    step = -0xC;
    *(s32 *)(self + 0x34) = 0;
    *(s32 *)(self + 0x38) = 0;
    *(s32 *)(self + 0x3C) = 0;
    *(s32 *)(self + 0x40) = 0;
    *(s32 *)(self + 0x20) = x;
    *(s32 *)(self + 0x24) = y;
    *(s32 *)(self + 0x28) = z;
    *(s32 *)(self + 0x30) = lifetime;
    *(s32 *)(self + 0x48) = power;
    if (lifetime > 0) {
        step = 0xC;
    }
    *(s32 *)(self + 0x34) = step;
    *(s16 *)(self + 0x44) = (s16)func_80077730(actor);
    *(s16 *)(self + 0x46) = 0;
    *(s32 *)(self + 0x4C) = 0x20;
    *(s32 *)(self + 0x50) = 0;
    return self;
}

void func_800995AC(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_800699F4;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80099600(u8 *self) {
    u32 x = *(u32 *)(self + 0x20);
    u32 y = *(u32 *)(self + 0x24);
    u32 z = *(u32 *)(self + 0x28);
    u32 dx = *(u32 *)(self + 0x34);
    u32 dy = *(u32 *)(self + 0x38);
    u32 dz = *(u32 *)(self + 0x3C);
    x += dx;
    y += dy;
    z += dz;
    *(u32 *)(self + 0x20) = x;
    *(u32 *)(self + 0x24) = y;
    *(u32 *)(self + 0x28) = z;
    if (*(s32 *)(self + 0x50) < 5) {
        *(u32 *)(self + 0x4C) += 0x10U;
    } else {
        *(u32 *)(self + 0x4C) -= 6U;
    }
    if (*(s32 *)(self + 0x4C) <= 0) {
        if (self != 0) {
            u8 *vtable = *(u8 **)(self + 0x14);
            (*(void (**)(u8 *, s32))(vtable + 0x1C))(self + *(s16 *)(vtable + 0x18), 3);
        }
    } else {
        *(u16 *)(self + 0x46) ^= 1;
        *(u32 *)(self + 0x50) += 1U;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_800996C8);

u8 *func_80099874(u8 *self, u8 *actor, u8 *manager, const s32 *position, const s32 *velocity) {
    s32 x0, y0, z0, x1, y1, z1, x2, y2, z2;

    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_800699CC;
    *(u8 **)(self + 0x18) = actor;
    *(u8 **)(self + 0x1C) = manager;
    x0 = position[0];
    y0 = position[1];
    z0 = position[2];
    *(s32 *)(self + 0x20) = x0;
    *(s32 *)(self + 0x24) = y0;
    *(s32 *)(self + 0x28) = z0;
    x1 = position[0];
    y1 = position[1];
    z1 = position[2];
    *(s32 *)(self + 0x30) = x1;
    *(s32 *)(self + 0x34) = y1;
    *(s32 *)(self + 0x38) = z1;
    x2 = velocity[0];
    y2 = velocity[1];
    z2 = velocity[2];
    *(s32 *)(self + 0x50) = 0xC8;
    *(s32 *)(self + 0x54) = 0;
    *(s32 *)(self + 0x40) = x2;
    *(s32 *)(self + 0x44) = y2;
    *(s32 *)(self + 0x48) = z2;
    return self;
}

void func_80099938(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_800699CC;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009998C);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_80099A88);

void func_80099B98(s32 a0, s32 a1) {
    s32 s1;
    s32 s0;
    s32 p;
    s32 a2;
    s32 a0v;

    s1 = a0;
    s0 = a1;
    p = s1 + 0x38;
    a2 = *(s32 *)(s1 + 0x38);
    a0v = *(s32 *)(s1 + 0x3C);
    *(s32 *)(s1 + 0x18) = (s32)&D_8006D730;
    *(s32 *)(s1 + 0x14) = (s32)&D_8006D750;
    *(s32 *)(s1 + 0x68) = (s32)&D_80065174;
    *(s32 *)(a2 + 4) = a0v;
    a2 = *(s32 *)(p + 4);
    *(s32 *)(a2 + 0) = *(s32 *)(s1 + 0x38);
    *(s32 *)(s1 + 0x38) = p;
    *(s32 *)(s1 + 0x3C) = p;
    *(s32 *)(s1 + 0x18) = (s32)&D_80065154;
    func_8002BCEC((u8 *)s1, 0);
    if (s0 & 1) {
        func_8002BDA8((u8 *)s1);
    }
}

void func_80099C38(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80099C8C(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80099CE0(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

u8 *func_80099D34(u8 *a0) {
    func_80076FD8(a0);
    *(u8 **)(a0 + 0x14) = D_8006A29C;
    *(u32 *)(a0 + 0x4A8) = 0;
    *(u32 *)(a0 + 0x4CC) = 0;
    return a0;
}

void func_80099D70(u8 *a0) {
    func_8001BEDC(*(u8 **)(a0 + 0x4CC));
    *(u32 *)(a0 + 0x4CC) = 0;
}

void func_80099DA0(u8 *arg0, s32 arg1) {
    u8 *p;

    func_80079D58(arg0);
    p = (u8 *)(func_8007773C(arg0) + 0x60);
    switch (arg1) {
    case 0:
        func_80079AA4(arg0, 6, 0, 0, -1);
        break;
    case 5:
        func_8007B748(arg0, 0, p, 1);
        break;
    }
    if (arg1 >= 6) {
        func_8007B748(arg0, arg1, p, 1);
    }
}

void func_80099E50(u8 *arg0, s32 arg1) {
    u8 *p;

    func_80079D58(arg0);
    p = (u8 *)(func_8007773C(arg0) + 0xA8);
    switch (arg1) {
    case 0:
        func_80079AA4(arg0, 8, 2, 0, -1);
        break;
    case 6:
        func_8007B748(arg0, 0, p, 2);
        break;
    }
    if (arg1 >= 7) {
        func_8007B748(arg0, arg1, p, 1);
    }
}

void func_80099F00(u8 *arg0, s32 arg1) {
    func_8007BE3C(arg0, arg1);
    if (arg1 == 2) {
        func_80099FD0(arg0);
    }
    if (arg1 >= 3) {
        s32 v = *(s32 *)(arg0 + 0x448);
        if (v != 0) {
            *(s32 *)(arg0 + 0x448) = v | 0xD0000;
        }
    }
}

void func_80099F68(u8 *arg0, s32 arg1) {
    func_8007BD70(arg0, arg1);
    if (arg1 == 2) {
        func_80099FD0(arg0);
    }
    if (arg1 >= 3) {
        s32 v = *(s32 *)(arg0 + 0x448);
        if (v != 0) {
            *(s32 *)(arg0 + 0x448) = v | 0xD0000;
        }
    }
}

void func_80099FD0(u8 *arg0) {
    u8 *s1 = D_80069D2C;
    u8 *s5 = s1 + 0x120;
    s32 a4 = 2;
    s32 a5 = 0x10;

    do {
        u8 *s0 = func_8002BE14(0x690);
        if (s0 != 0) {
            func_800C591C((u8 *)func_8002BD80(0x690, s0), arg0, s1, 4, a4, a5);
        }
        func_8007AFCC(arg0, s0);
        s1 += 0x60;
    } while (s1 != s5);
}

void func_8009A07C(u8 *a0, s32 a1) {
    u8 *s1;
    func_8007BC50();
    s1 = (u8 *)func_8007B16C(a0);
    func_800785BC(a0, 0);
    switch (a1) {
    case 0:
        *(s32 *)(a0 + 0x4A4) = 0;
        *(s32 *)(a0 + 0x4A8) = 0;
        *(s32 *)(a0 + 0x4AC) = 0x1000;
        *(s32 *)(a0 + 0x4B0) = 0;
        *(s32 *)(a0 + 0x4B4) = 0x1000;
        *(s32 *)(a0 + 0x4B8) = 0;
        *(s32 *)(a0 + 0x4BC) = 0x1000;
        *(s32 *)(a0 + 0x4C0) = 0;
        *(s32 *)(a0 + 0x4C4) = 0;
        *(s32 *)(a0 + 0x4C8) = 0;
        func_800794D4(s1, 2);
        /* fallthrough */
    case 1:
        func_8009A1E8(a0);
        break;
    case 2:
        func_8009A468(a0, 0x8C0C00, &D_80010814);
        func_8009A274(a0, 0);
        break;
    case 15:
        func_8009A468(a0, 0x8C1400, &D_80010814);
        break;
    case 30: {
        s32 v[3];
        func_8009A3A4(a0);
        v[0] = func_8007A084(a0) * 0x38E0;
        v[1] = -0x38E0;
        v[2] = 0;
        func_8009A468(a0, 0x408C2000, (u8 *)v);
        break;
    }
    }
    if ((u32)(a1 - 3) < 0x1B) {
        func_8009A3E0(a0);
    }
}

void func_8009A1E8(u8 *a0) {
    u8 *t = (u8 *)func_8007B16C(a0);
    s32 buf[4];
    func_8007A724(a0, (u8 *)buf, 5, D_80069D1C);
    buf[1] += *(s16 *)((u8 *)func_8007773C(t) + 2);
    func_80077654(t, buf);
    *(u32 *)(t + 0x3B4) = 0;
    *(u32 *)(t + 0x3B8) = 0;
    *(u32 *)(t + 0x3BC) = 0;
    *(u32 *)(t + 0x3C0) = 0;
    *(u32 *)(t + 0x3A4) = 0;
    *(u32 *)(t + 0x3A8) = 0;
    *(u32 *)(t + 0x3AC) = 0;
    *(u32 *)(t + 0x3B0) = 0;
    *(u32 *)(t + 0x3E0) = 0;
    *(u32 *)(t + 0x3F0) = 0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009A274);

void func_8009A3A4(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x4A8);
    if (p != 0) {
        func_8007B0B4(p);
    }
    *(u32 *)(a0 + 0x4A8) = 0;
}

void func_8009A3E0(u8 *a0) {
    u32 c;
    u32 *p;
    if (*(u32 *)(a0 + 0x4A4) == 0) {
        p = *(u32 **)(a0 + 0x4A8);
        c = (p[0] == (u32)p) && ((u32)p == p[1]);
        if (c) {
            func_8009A3A4(a0);
            *(u32 *)(a0 + 0x4A4) = *(u32 *)(a0 + 0x4A4) + 1;
        }
    } else {
        func_8009A274(a0, a0 + 0x4AC);
        *(u32 *)(a0 + 0x4A4) = 0;
    }
}

void func_8009A468(u8 *a0, s32 a1, u8 *a2) {
    u8 *t = (u8 *)func_8007B16C(a0);
    s32 sp20[4];
    s32 sp30[3];
    u8 *s0;
    func_80079158(t, a1, a2, 1);
    func_8007A724(a0, (u8 *)sp20, 5, D_80069D1C);
    sp30[0] = -(func_8007A084(a0) << 5);
    sp30[1] = -0x10;
    sp30[2] = 0;
    s0 = func_8002BE14(0x48);
    if (s0 != 0) {
        func_800C6090((u8 *)func_8002BD80(0x48, s0), 6, (u8 *)sp20, (u8 *)sp30, 0x80, 8, 0xFFE0C0);
    }
    func_8007AFCC(a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009A548);

void func_8009A614(u8 *a0, s32 a1) {
    s64 v;
    func_8007BEC0(a0);
    func_80079D58(a0);
    switch (a1) {
    case 0:
        func_80078754(a0, 0xBB);
        func_8009A790(a0);
        break;
    case 0xD:
        func_8009A704(a0);
        v = (s64)(func_8007A084(a0) * 0x1C70) * *(s32 *)(a0 + 0x3C4);
        v >>= 16;
        *(s32 *)(a0 + 0x3B4) -= (s32)v;
        break;
    }
    if (a1 < 0x14) {
        if (*(s32 *)(a0 + 0x3A8) > 0) {
            *(s32 *)(a0 + 0x3B8) -= *(s32 *)(a0 + 0x3A8) >> 1;
        }
    }
    *(s32 *)(a0 + 0x4A0) = 1;
}

void func_8009A704(u8 *a0) {
    u8 *s1;
    u8 *s0;

    *(s32 *)(a0 + 0x4CC) = func_800787A0(a0, 0xB6);
    s1 = func_8002BE14(0x4C);
    if (s1) {
        s0 = (u8 *)func_8002BD80(0x4C, s1);
        func_8009ADF8(s0, a0, func_80077730(a0));
    }
    func_8007AFCC(a0, s1);
    func_80079D80(a0, 0x32);
}

void func_8009A790(u8 *a0) {
    u8 *s0 = func_8002BE14(0x50);

    if (s0) {
        func_8009BAEC((u8 *)func_8002BD80(0x50, s0), a0, 0x200, 0xFF8080);
    }
    func_8007AFCC(a0, s0);
}

void func_8009A7F8(u8 *a0, s32 a1) {
    func_8007BCD4(a0);
    func_80079D58(a0);
    switch (a1) {
    case 0:
        func_80078754(a0, 0xBC);
        break;
    case 0x13:
        func_8009AA1C(a0);
        *(s32 *)(a0 + 0x3B4) -=
            (s32)(((s64)(func_8007A084(a0) * 35 * 520) * *(s32 *)(a0 + 0x3C4)) >> 16);
        break;
    case 0x28:
        if (func_80077978(a0) != 0) {
            *(s32 *)(a0 + 0x3A4) = 0;
            *(s32 *)(a0 + 0x3B4) -=
                (s32)(((s64)(func_8007A084(a0) * 21 * 520) * *(s32 *)(a0 + 0x3C4)) >> 16);
        }
        break;
    }
}

void func_8009A8FC(u8 *a0, s32 a1) {
    s32 v;

    func_8007BEF4(a0, a1);
    func_80079D58(a0);
    switch (a1) {
    case 0:
        func_80078754(a0, 0xBC);
        break;
    case 0x13:
        func_8009AA1C(a0);
        *(s32 *)(a0 + 0x3B4) -=
            (s32)(((s64)(func_8007A084(a0) * 21 * 520) * *(s32 *)(a0 + 0x3C4)) >> 16);
        v = (s32)(((s64)*(s32 *)(a0 + 0x3C4) * 0x2AA8) >> 16);
        v += *(s32 *)(a0 + 0x3A8);
        *(s32 *)(a0 + 0x3B8) -= v;
        break;
    }
    if (a1 < 0x13) {
        if (*(s32 *)(a0 + 0x3A8) > 0) {
            *(s32 *)(a0 + 0x3B8) -= *(s32 *)(a0 + 0x3A8) >> 1;
        }
    }
}

void func_8009AA1C(u8 *a0) {
    s32 tmp[4];
    s32 info[3];
    u8 *s0;

    func_8007A724(a0, tmp, 0, D_80069ED0);
    info[0] = (func_8007A084(a0) * 3) << 3;
    info[1] = 0;
    info[2] = 0;
    s0 = func_8002BE14(0xC8);
    if (s0) {
        func_8009C0C0((u8 *)func_8002BD80(0xC8, s0), a0, tmp, info);
    }
    func_8007AFCC(a0, s0);
    func_80079D88(a0, 0x3C);
    func_800787A0(a0, 0xB7);
}

void func_8009AACC(u8 *a0, s32 a1) {
    u8 *s0;

    func_8007BD08(a0);
    if (a1 == 0) {
        s0 = func_8002BE14(0x24);
        if (s0) {
            func_8009D4C4((u8 *)func_8002BD80(0x24, s0), a0);
        }
        func_8007AFCC(a0, s0);
        *(s32 *)(a0 + 0x498) = 0xC;
        func_800774EC(a0, -0x8000);
    }
    if (func_80077978(a0) != 0 && a1 < 0x2D && (a1 & 3) == 0) {
        s0 = func_8002BE14(0x14C);
        if (s0) {
            func_8009D7A4((u8 *)func_8002BD80(0x14C, s0), a0);
        }
        func_8007AFCC(a0, s0);
    }
    if (a1 == 0x14) {
        func_80078754(a0, 0xBD);
    }
    if (a1 == 0x2D) {
        func_8009ABD8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009ABD8);

s32 func_8009ADF8(u8 *a0, u8 *a1, s32 a2) {
    s32 v;
    func_8002BC9C(a0, 0);
    *(u8 **)(a0 + 0x14) = D_8006A274;
    *(u8 **)(a0 + 0x18) = a1;
    func_8007A724(a1, a0 + 0x1C, 5, D_80069D1C);
    *(s32 *)(a0 + 0x2C) = 4;
    v = func_8007A084(a1);
    *(s32 *)(a0 + 0x30) = v;
    *(s32 *)(a0 + 0x48) = a2;
    *(s32 *)(a0 + 0x38) = 0;
    *(s32 *)(a0 + 0x34) = 0x2000;
    *(s32 *)(a0 + 0x3C) = 0x40;
    *(s32 *)(a0 + 0x40) = 0;
    *(s32 *)(a0 + 0x44) = 0;
    return (s32)a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009AE98);

void func_8009B234(u8 *a0, u8 *a1) {
    func_8009B27C(a0, a1);
    func_8009B628(a0, a1);
    func_8009B91C(a0, a1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009B27C);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009B628);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009B91C);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009BAEC);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009BCD0);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009BEDC);

u8 *func_8009C0C0(u8 *a0, u8 *a1, s32 *a2, s32 *a3) {
    func_800C72C0((s32)a0, (s32)a1, (s32)a2, (s32)a3, 0x80, 0, 0x1000, 3);
    *(s32 *)(a0 + 0x18) = (s32)&D_8006A204;
    *(s32 *)(a0 + 0x14) = (s32)&D_8006A224;
    func_8007C0A0((s32)(a0 + 0x18), 0x84AC4000, 7);
    *(s32 *)(a0 + 0xC0) = 0;
    *(s32 *)(a0 + 0xC4) = 0;
    return a0;
}

void func_8009C138(u8 *a0, u8 *a1) {
    u8 *s0 = a0;
    u8 *s2 = a1;
    u8 *s1;
    s32 v;
    s32 c0;
    *(s32 *)(s0 + 0x90) = (*(s32 *)(s0 + 0x90) * 0x11) >> 4;
    *(s32 *)(s0 + 0xAC) = func_800237A0((s32)(s0 + 0x90));
    c0 = *(s32 *)(s0 + 0xC0);
    *(s32 *)(s0 + 0xC0) = c0 + ((0x100 - c0) >> 2);
    v = *(s32 *)(s0 + 0xC4) + 0x10;
    *(s32 *)(s0 + 0xC4) = v;
    if (v >= 0xA1) {
        *(s32 *)(s0 + 0xC4) = 0x70;
    }
    s1 = (u8 *)func_8002BE14(0x3C);
    if (s1 != 0) {
        func_800C6588((u8 *)func_8002BD80(0x3C, s1), 6, s0 + 0x80, 0x30, 0xC0, 1, 0x808080);
    }
    func_8002BF34((s32)s0, (s32)s1);
    func_800C7478((s32)s0, (s32)s2);
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009C224);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009C300);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009C54C);

void func_8009C6F4(u8 *a0) {
    u8 *s0 = a0;
    s32 v0;
    if (*(s32 *)(s0 + 0xB4) != 0) {
        v0 = *(s32 *)(s0 + 0xD0) - 1;
        *(s32 *)(s0 + 0xD0) = v0;
        if (v0 <= 0) {
            if (s0 != 0) {
                u8 *vt = *(u8 **)(s0 + 0x14);
                ((void (*)(u8 *, s32)) * (u32 *)(vt + 0x1C))(s0 + *(s16 *)(vt + 0x18), 3);
            }
            return;
        }
    } else {
        func_8009C930(s0);
        v0 = *(s32 *)(s0 + 0xD0);
        v0 += 1;
        *(s32 *)(s0 + 0xD0) = v0;
        if (v0 >= 0x11) {
            *(s32 *)(s0 + 0xD0) = 0x10;
        }
    }
    func_8009CB50(s0);
    v0 = *(s32 *)(s0 + 0xC0);
    v0 += 1;
    *(s32 *)(s0 + 0xC0) = v0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009C7A4);

void func_8009C8E4(u8 *a0, u8 *a1) {
    u8 *s0 = a0;
    u8 *s1 = a1;
    if (*(u32 *)(s0 + 0xB4) == 0) {
        func_8009CBCC(a0, a1);
    }
    func_8009CE10(s0, s1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009C930);

void func_8009CB50(u8 *a0) {
    s32 *a2 = (s32 *)(a0 - 0x10);
    u8 *a3 = a0;
    s32 idx;
    s32 i;
    *(s32 *)(a3 + 0xCC) += 1;
    if (*(s32 *)(a3 + 0xCC) >= 0x10) {
        *(s32 *)(a3 + 0xCC) = 0;
    }
    idx = *(s32 *)(a3 + 0xCC);
    {
        s32 x = *(s32 *)(a3 + 0x84);
        s32 y = *(s32 *)(a3 + 0x88);
        s32 z = *(s32 *)(a3 + 0x8C);
        s32 *d = (s32 *)(a3 + 0xD4 + (idx << 4));
        d[0] = x;
        d[1] = y;
        d[2] = z;
        d[3] = 0x10;
    }
    a2 = (s32 *)(a3 + 0xE0);
    for (i = 0xF; i >= 0; i--) {
        *a2 += 3;
        a2 += 4;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009CBCC);

INCLUDE_ASM("asm/us/game/nonmatchings/34AFC", func_8009CE10);
