#include "game_rotation.h"
#include "game_action_api.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_actor_queries.h"
#include "game_positions.h"
#include "game_effect_constructor.h"

extern u8 D_80069A44;

extern u8 D_80069AE4;

extern u8 D_80069B5C;

extern u8 D_80069BCC;

extern u8 D_8006D58C;

extern u8 D_80069BF4;

extern u8 *func_8002BE14(s32);
extern void func_8002BF34(u8 *, u8 *);
extern s32 func_80077730(s32);
extern s32 func_800787A0(u8 *, s32);
extern s32 func_8007A084(u8 *);
extern s32 func_8007A0A0(u8 *);
extern s32 func_8007773C(u8 *);
extern void func_8007BAE4(u8 *, s32);
extern u8 *func_8007A0C4(u8 *, u8 *, s32, s32);
extern void func_8007AFCC(u8 *, u8 *);
extern void func_8007BCD4(u8 *);
extern void func_80095B4C(u8 *);
extern void func_80095BE0(u8 *);
extern u8 *func_80096570(u8 *, u8 *, u8 *, u8 *, s32 *);
extern u8 *func_80096C98(u8 *, s32);
extern u8 *func_80096FB4(u8 *, s32, u8 *, s32);
extern u8 *func_80097498(u8 *, s32, s32, s32);
extern void func_80097904(u8 *, u8 *, u8 *, s32);
extern void func_80098258(u8 *, u8 *, u8 *);
extern u8 *func_800989D8(u8 *, s32, s32 *);
extern void func_800C31B0(s32, s32, s32, s32, s32, s32, s32);

extern u8 D_80010814;
extern u8 D_80010884;
extern u8 D_80069954;
extern u8 D_80069964;
extern u8 D_80069974;
extern u8 D_80069988;
extern u8 D_80069B0C;
extern u8 D_80069B34;
extern u8 D_80065154;
extern u8 D_80065174;
extern u8 D_80069ABC;
extern u8 D_80069A6C;
extern u8 D_8006D730;
extern u8 D_8006D750;
extern u8 D_80069A94;
extern u8 D_80069B84;
extern u8 D_80069BA4;
extern void func_800C72C0(s32, s32, s32, s32, s32, s32, s32, s32);
u8 *func_80096250(u8 *, u8 *, s32 *, s32, s32);
extern void func_80078B70(u8 *);
extern u8 *func_80078AD8(u8 *);
extern s32 func_80079040(u8 *);
extern void func_800C7710(u8 *, u8 *);
extern void func_800C7644(u8 *, s32);
extern void func_80096C3C(u8 *);
extern void func_800C33D0(u8 *);
extern u8 *func_80098D30(u8 *, u8 *, s32, s32 *, s32 *);

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80094DB0);

void func_80095080(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800950D4(s32 a0, s32 a1) {
    s32 s1;
    s32 s0;
    s32 p;
    register s32 node asm("$6"); /* PIN $a2: retail keeps the first list node in $a2 */
    s32 a2;
    s32 a0v;

    s1 = a0;
    s0 = a1;
    p = s1 + 0x38;
    node = *(s32 *)(s1 + 0x38);
    a0v = *(s32 *)(s1 + 0x3C);
    *(s32 *)(s1 + 0x18) = (s32)&D_8006D730;
    *(s32 *)(s1 + 0x14) = (s32)&D_8006D750;
    *(s32 *)(s1 + 0x68) = (s32)&D_80065174;
    *(s32 *)(node + 4) = a0v;
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

void func_80095174(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

s32 func_800951C8(s32 a0) {
    func_80076FD8(a0);
    *(u32 *)(a0 + 0x14) = (u32)&D_80069BF4;
    *(s32 *)(a0 + 0x4A4) = 0;
    return a0;
}

void func_80095200(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_80069BF4;
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80095254(u8 *a0) {
    s32 count;
    s32 status;

    func_80078B70(a0);
    count = *(s32 *)(a0 + 0x4A4);
    if (count != 0) {
        count--;
        *(s32 *)(a0 + 0x4A4) = count;
        if (count != 0) {
            status = func_8007A0A0(a0);
            if (status >= 7) {
                return;
            }
            if (status < 5) {
                return;
            }
            *(s32 *)(a0 + 0x4A4) = 0x23;
    }
}
}

s32 func_800952B4(u8 *a0) {
    *(s32 *)(a0 + 0x4AC) = 1;
    return 1;
}

void func_800952C0(u8 *a0, s32 a1) {
    s32 value;

    func_8007BAE4(a0, a1);
    if (a1 == 4) {
        value = (s32)(((s64)*(s32 *)(func_8007773C(a0) + 0xD4) *
                       *(s32 *)(a0 + 0x3C4)) >> 16);
        *(s32 *)(a0 + 0x3B4) += value * func_8007A084(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80095350);

void func_8009554C(u8 *self, s32 tag) {
    s32 position[4];
    u8 *handle;
    u8 *object;
    func_8007767C(self, position);
    position[1] = (s32)((u32)position[1] - 0x133U);
    handle = func_8002BE14(0x40);
    if (handle != 0) {
        object = (u8 *)func_8002BD80(0x40, handle);
        func_80096250(object, self, position, func_8007A084(self), tag);
    }
    func_8007AFCC(self, handle);
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_800955E8);

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80095738);

void func_8009588C(u8 *a0, s32 a1) {
    u8 *s2;
    u8 *s0;
    s2 = func_80077624(a0);
    s0 = func_8002BE14(0x30);
    if (s0 != 0) {
        func_80097498((u8 *)func_8002BD80(0x30, s0), a0, a1, (s32)s2);
    }
    func_8007AFCC(a0, s0);
}

void func_8009590C(u8 *a0) {
    s32 tmp[4];
    s32 v[3];
    u8 *s2;
    u8 *s0;
    s32 t;
    func_8007A724(a0, tmp, 6, &D_80069954);
    t = func_8007A084(a0);
    v[0] = (t * 2 + t) << 6;
    v[1] = 0;
    v[2] = 0;
    s2 = func_80077624(a0);
    s0 = func_8002BE14(0x15C);
    if (s0 != 0) {
        func_80096570((u8 *)func_8002BD80(0x15C, s0), a0, s2, (u8 *)tmp, v);
    }
    func_8007AFCC(a0, s0);
    func_800787A0(a0, 0xAE);
}

void func_800959CC(u8 *a0) {
    s32 tmp[4];
    u8 *s0;
    s32 s1;
    s32 s2;
    s32 v;
    func_8007A724(a0, tmp, 6, &D_80069964);
    v = func_8007A084(a0);
    s1 = (v > 0) ? 0x100 : 0xA00;
    for (s2 = 5; s2 >= 0; s2--) {
        s0 = func_8002BE14(0x58);
        if (s0 != 0) {
            func_80096FB4((u8 *)func_8002BD80(0x58, s0), (s32)a0, (u8 *)tmp, s1);
        }
        func_8007AFCC(a0, s0);
        s1 += 0x100;
    }
}

void func_80095A78(u8 *a0) {
    u8 *s0;
    s0 = func_8002BE14(0x5C);
    if (s0 != 0) {
        func_80097224((u8 *)func_8002BD80(0x5C, s0), a0);
    }
    func_8007AFCC(a0, s0);
}

void func_80095AD4(u8 *a0, s32 a1) {
    func_8007BCD4(a0);
    if (a1 == 0) {
        func_80078754(a0, 0xB4);
    }
    if (a1 == 7) {
        func_80095B4C(a0);
    }
    if (a1 == 0xE) {
        s32 s0;
        s0 = 0x13;
        do {
            func_80095BE0(a0);
            s0--;
        } while (s0 >= 0);
    }
}

void func_80095B4C(u8 *a0) {
    u8 *s3;
    u8 *s1;
    s3 = func_80077624(a0);
    s1 = func_8002BE14(0xA4);
    if (s1 != 0) {
        func_80097904((u8 *)func_8002BD80(0xA4, s1), a0, s3, func_8007A084(a0));
    }
    func_8007AFCC(a0, s1);
    func_800787A0(a0, 0xAF);
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80095BE0);

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80095D28);

void func_80095EFC(u8 *a0) {
    u8 *s2;
    u8 *s0;
    s2 = func_80077624(a0);
    s0 = func_8002BE14(0xB4);
    if (s0 != 0) {
        func_80098258((u8 *)func_8002BD80(0xB4, s0), a0, s2);
    }
    func_8007AFCC(a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80095F6C);

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80096040);

void func_80096144(u8 *a0) {
    u8 *s0;
    s32 tmp1[4];
    s32 tmp2[4];
    s32 s1;
    s32 s2;
    s32 s3;
    s32 v2;
    s32 v1;
    s0 = func_8007A0C4(a0, &D_80010884, 0x640000, 0x238);
    if (s0 != 0) {
        func_8007767C(a0, tmp1);
        func_8007767C(s0, tmp2);
        s1 = tmp2[0] - tmp1[0];
        s3 = tmp2[1] - tmp1[1];
        v2 = func_8007A084(a0);
        s2 = s1 * v2;
        if (func_8007A0A0(s0) == 0) {
            v1 = 0x1000;
        } else {
            v1 = 0x400;
        }
        if ((u32)(s3 + 0x57F) < 0xAFF) {
            if ((u32)(s2 - 0x221) < 0x7DF) {
                if (s1 > 0) {
                    *(s32 *)(s0 + 0x3B4) -= v1;
                } else {
                    *(s32 *)(s0 + 0x3B4) += v1;
                }
            } else if ((u32)(s2 - 1) < 0x1E0) {
                if (s1 > 0) {
                    *(s32 *)(s0 + 0x3B4) += v1;
                } else {
                    *(s32 *)(s0 + 0x3B4) -= v1;
                }
            }
        }
    }
}


u8 *func_80096250(u8 *self, u8 *owner, s32 *position, s32 value, s32 tag) {
    s32 x, y, z;
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = &D_80069BCC;
    *(u8 **)(self + 0x18) = owner;
    x = position[0];
    y = position[1];
    z = position[2];
    *(s32 *)(self + 0x2C) = value;
    *(s32 *)(self + 0x34) = 0x3C;
    *(s32 *)(self + 0x38) = 0;
    *(s32 *)(self + 0x1C) = x;
    *(s32 *)(self + 0x20) = y;
    *(s32 *)(self + 0x24) = z;
    *(s32 *)(self + 0x30) = tag;
    *(s16 *)(self + 0x3C) = func_80077730(owner);
    return self;
}

void func_800962F4(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_80069BCC;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80096348(u8 *a0) {
    u8 *obj = a0;

    if (*(s32 *)(obj + 0x38) >= 3) {
        if (obj != 0) {
            u8 *base = *(u8 **)(obj + 0x14);
            s32 offset = *(s16 *)(base + 0x18);

            ((void (*)(u8 *, s32))*(u32 *)(base + 0x1C))(obj + offset, 3);
        }
    } else {
        *(s32 *)(obj + 0x34) -= 0xF;
        *(volatile s32 *)(obj + 0x38) += 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_800963BC);

u8 *func_80096570(u8 *self, u8 *owner, u8 *object, u8 *vector, s32 *scale) {
    s32 i;
    func_800C72C0((s32)self, (s32)owner, (s32)vector, (s32)scale, 0x80, 0x04A82800, 0x1000, 3);
    *(u8 **)(self + 0x18) = &D_80069B84;
    *(u8 **)(self + 0x14) = &D_80069BA4;
    *(u8 **)(self + 0xC0) = owner;
    *(u8 **)(self + 0xC4) = object;
    *(s32 *)(self + 0xC8) = 0;
    for (i = 3; i >= 0; i--) {
        *(s16 *)(self + 0xCC + i * 0x24) = 0;
    }
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80096618);

void func_800967F0(u8 *a0, u8 *a1) {
    u8 *s0;
    u8 *s1;

    s1 = a0;
    func_8007C0C8(s1 + 0x18, a1);
    s0 = func_80078AD8(a1);
    if (s0 != 0) {
        if (func_80079040(s0) == 0) {
            func_80096C3C(s1);
        }
        func_800C7710(s1, s0);
    } else {
        func_800C7644(s1, 4);
    }
    if (s1 != 0) {
        u8 *object = *(u8 **)(s1 + 0x14);
        s16 offset = *(s16 *)(object + 0x18);

        ((void (*)(u8 *, s32))*(u32 *)(object + 0x1C))(s1 + offset, 3);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80096890);

void func_80096C3C(u8 *a0) {
    u8 *s0;
    s0 = func_8002BE14(0x40);
    if (s0 != 0) {
        func_80096C98((u8 *)func_8002BD80(0x40, s0), *(s32 *)(a0 + 0xC0));
    }
    func_8002BF34(a0, s0);
}

u8 *func_80096C98(u8 *a0, s32 a1) {
    func_8002BC9C(a0, 0);
    *(u32 *)(a0 + 0x14) = (u32)&D_80069B5C;
    *(s32 *)(a0 + 0x18) = a1;
    *(s32 *)(a0 + 0x2C) = 0xC0C0C0;
    *(s32 *)(a0 + 0x30) = 0xB3;
    *(s32 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0x38) = 0;
    *(s16 *)(a0 + 0x3A) = func_80077730(a1);
    *(s32 *)(a0 + 0x3C) = 0;
    return a0;
}

void func_80096D0C(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_80069B5C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80096D60(u8 *self) {
    u32 cycle;

    func_8007A8D0(func_8007B16C(*(u8 **)(self + 0x18)), self + 0x1C);
    if (*(s32 *)(self + 0x3C) >= 11) {
        if (self != 0) {
            u8 *vtable = *(u8 **)(self + 0x14);
            s16 adjustment = *(s16 *)(vtable + 0x18);
            void (*destroy)(u8 *, s32) = *(void (**)(u8 *, s32))(vtable + 0x1C);
            destroy((u8 *)((u32)self + (u32)(s32)adjustment), 3);
        }
    } else {
        cycle = *(u16 *)(self + 0x38) + 1;
        *(u16 *)(self + 0x38) = cycle;
        if ((u16)cycle >= 3) {
            *(u16 *)(self + 0x38) = 0;
        }
        *(u32 *)(self + 0x3C) = *(u32 *)(self + 0x3C) + 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80096E0C);

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80096FB4);

void func_8009707C(u8 *a0) {
    u8 *a3 = a0;

    if (*(s32 *)(a3 + 0x54) >= 5) {
        if (a3 != 0) {
            u8 *object = *(u8 **)(a3 + 0x14);
            s16 offset = *(s16 *)(object + 0x18);

            ((void (*)(u8 *, s32))*(u32 *)(object + 0x1C))(a3 + offset, 3);
        }
    } else {
        s32 x = *(s32 *)(a3 + 0x28);
        s32 y = *(s32 *)(a3 + 0x2C);
        s32 z = *(s32 *)(a3 + 0x30);
        s32 dx = *(s32 *)(a3 + 0x44);
        s32 dy;
        s32 dz;

        *(s32 *)(a3 + 0x24) = 0xA02828;
        dy = *(s32 *)(a3 + 0x48);
        x += dx;
        y += dy;
        dz = *(s32 *)(a3 + 0x4C);
        *(s32 *)(a3 + 0x28) = x;
        *(s32 *)(a3 + 0x2C) = y;
        z += dz;
        *(s32 *)(a3 + 0x30) = z;
        *(volatile s32 *)(a3 + 0x54) += 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_8009711C);

u8 *func_80097224(u8 *a0, u8 *a1) {
    s32 v0;
    v0 = func_80077730((s32)a1);
    func_800C31B0((s32)a0, (s32)&D_80069974, (s32)&D_80010814, (s32)&D_80010814, 0x33, 0x646464, v0);
    *(u32 *)(a0 + 0x14) = (u32)&D_80069B0C;
    func_8007A724(a1, a0 + 0x28, 6, &D_80069988);
    *(s32 *)(a0 + 0x58) = func_8007A084(a1);
    return a0;
}

void func_800972C0(u8 *a0) {
    u8 *a3 = a0;
    register s32 value asm("$6"); /* PIN $a2: keep the 0x64 accumulator in retail's update register */
    s32 packed;
    register s32 callback_arg asm("$5"); /* PIN $a1: preserve retail's callback argument across object loads */
    value = 0x64;

    if (*(s32 *)(a3 + 0x54) >= 5) {
        callback_arg = 3;
        if (a3 != 0) {
            u8 *object = *(u8 **)(a3 + 0x14);
            s16 offset = *(s16 *)(object + 0x18);

            ((void (*)(u8 *, s32))*(u32 *)(object + 0x1C))(a3 + offset, callback_arg);
        }
    } else {
        register u8 *target asm("$4"); /* PIN $a0: preserve the retail update call pointer */
        target = a3;
        do {
            value -= *(volatile s32 *)(a3 + 0x54) * 0x14;
            packed = value >> 2;
            packed |= packed << 8;
        } while (0);
        packed |= value << 16;
        *(s32 *)(a3 + 0x24) = packed;
        *(s32 *)(a3 + 0x20) += 0x33;
        func_800C33D0(target);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80097360);

u8 *func_80097498(u8 *a0, s32 a1, s32 a2, s32 a3) {
    func_8002BC9C(a0, 0);
    *(u32 *)(a0 + 0x14) = (u32)&D_80069AE4;
    *(s32 *)(a0 + 0x18) = a1;
    *(s32 *)(a0 + 0x1C) = 0;
    *(s32 *)(a0 + 0x20) = 0;
    *(s32 *)(a0 + 0x28) = 0;
    *(s32 *)(a0 + 0x24) = a2;
    *(s16 *)(a0 + 0x2C) = func_80077730(a1);
    return a0;
}

void func_80097508(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_80069AE4;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_8009755C(u8 *self) {
    s32 frame;
    s32 limit;
    s32 current;
    u8 *vtable;
    limit = *(s32 *)(self + 0x28);
    current = *(s32 *)(self + 0x24);
    if (current < limit) {
        if (self != 0) {
            vtable = *(u8 **)(self + 0x14);
            ((void (*)(u8 *, s32))*(u32 *)(vtable + 0x1C))
                (self + *(s16 *)(vtable + 0x18), 3);
        }
    } else {
        frame = (s32)((u32)*(s32 *)(self + 0x1C) + 1u);
        *(s32 *)(self + 0x1C) = frame;
        if (frame >= 3) {
            *(s32 *)(self + 0x1C) = 0;
        }
        *(s32 *)(self + 0x20) = (s32)((u32)*(s32 *)(self + 0x20) - 0x180u);
        *(s32 *)(self + 0x28) = (s32)((u32)*(s32 *)(self + 0x28) + 1u);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_800975F4);

void func_80097888(s32 a0, s16 *a1, u8 *a2, u8 *a3, s32 a4) {
    a1[0] = *(u16 *)(a2 + 0) + (((*(s32 *)(a3 + 0) - *(s32 *)(a2 + 0)) * a4) >> 12);
    a1[1] = *(u16 *)(a2 + 4) + (((*(s32 *)(a3 + 4) - *(s32 *)(a2 + 4)) * a4) >> 12);
    a1[2] = *(u16 *)(a2 + 8) + (((*(s32 *)(a3 + 8) - *(s32 *)(a2 + 8)) * a4) >> 12);
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80097904);

void func_80097A48(s32 a0, s32 a1) {
    s32 s1;
    s32 s0;
    s32 p;
    register s32 node asm("$4"); /* PIN $a0: retail's first list-node pointer */
    s32 a2;
    s32 a0v;

    s1 = a0;
    s0 = a1;
    p = s1 + 0x3C;
    node = *(s32 *)(s1 + 0x3C);
    a0v = *(s32 *)(s1 + 0x40);
    *(s32 *)(s1 + 0x14) = (s32)&D_80069ABC;
    *(s32 *)(s1 + 0x6C) = (s32)&D_80065174;
    *(s32 *)(node + 4) = a0v;
    a2 = *(s32 *)(p + 4);
    *(s32 *)(a2 + 0) = *(s32 *)(s1 + 0x3C);
    *(s32 *)(s1 + 0x3C) = p;
    *(s32 *)(s1 + 0x40) = p;
    *(s32 *)(s1 + 0x18) = (s32)&D_80065154;
    func_8002BCEC((u8 *)s1, 0);
    if (s0 & 1) {
        func_8002BDA8((u8 *)s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80097ADC);

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80097CE8);

u8 *func_80098008(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    func_800C3258(a0, 9, (s32 *)a2, (s32 *)a3, 2, 0, 0);
    *(u32 *)(a0 + 0x14) = (u32)&D_80069A94;
    *(u32 *)(a0 + 0x58) = a4 & 0xFFF;
    return a0;
}

void func_80098064(u8 *self, void *context) {
    if (*(s32 *)(self + 0x54) >= 11) {
        if (self != 0) {
            u8 *table = *(u8 **)(self + 0x14);
            void (*destroy)(u8 *, s32) = *(void (**)(u8 *, s32))(table + 0x1C);
            destroy((u8 *)((u32)self + (u32)(s32)*(s16 *)(table + 0x18)), 3);
        }
    } else {
        s32 tick;
        s32 color;
        s32 quarter;
        u32 x;
        u32 y;
        u32 z;
        *(u32 *)(self + 0x20) += 7u;
        if (*(s32 *)(self + 0x20) >= 26) {
            *(s32 *)(self + 0x20) = 25;
        }
        x = *(u32 *)(self + 0x28);
        y = *(u32 *)(self + 0x2C);
        z = *(u32 *)(self + 0x30);
        tick = *(s32 *)(self + 0x54);
        x += *(u32 *)(self + 0x44);
        y += *(u32 *)(self + 0x48);
        *(u32 *)(self + 0x28) = x;
        *(u32 *)(self + 0x2C) = y;
        z += *(u32 *)(self + 0x4C);
        color = 120 - tick * 10;
        quarter = color >> 2;
        *(u32 *)(self + 0x30) = z;
        *(u32 *)(self + 0x24) = (u32)quarter | ((u32)quarter << 8) | ((u32)color << 16);
        *(u32 *)(self + 0x54) = (u32)tick + 1u;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80098148);

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80098258);

void func_800983E0(s32 a0, s32 a1) {
    s32 s1;
    s32 s0;
    s32 p;
    register s32 node asm("$4"); /* PIN $a0: retail's first list-node pointer */
    s32 a2;
    s32 a0v;

    s1 = a0;
    s0 = a1;
    p = s1 + 0x3C;
    node = *(s32 *)(s1 + 0x3C);
    a0v = *(s32 *)(s1 + 0x40);
    *(s32 *)(s1 + 0x14) = (s32)&D_80069A6C;
    *(s32 *)(s1 + 0x6C) = (s32)&D_80065174;
    *(s32 *)(node + 4) = a0v;
    a2 = *(s32 *)(p + 4);
    *(s32 *)(a2 + 0) = *(s32 *)(s1 + 0x3C);
    *(s32 *)(s1 + 0x3C) = p;
    *(s32 *)(s1 + 0x40) = p;
    *(s32 *)(s1 + 0x18) = (s32)&D_80065154;
    func_8002BCEC((u8 *)s1, 0);
    if (s0 & 1) {
        func_8002BDA8((u8 *)s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80098474);

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_800986B4);

void func_80098978(u8 *a0) {
    u8 *s0;
    s0 = func_8002BE14(0x44);
    if (s0 != 0) {
        func_800989D8((u8 *)func_8002BD80(0x44, s0), *(s32 *)(a0 + 0x84), (s32 *)(a0 + 0x8C));
    }
    func_8002BF34(a0, s0);
}

u8 *func_800989D8(u8 *a0, s32 a1, s32 *a2) {
    s32 x;
    s32 y;
    s32 z;

    func_8002BC9C(a0, 0);
    *(u32 *)(a0 + 0x14) = (u32)&D_80069A44;
    *(s32 *)(a0 + 0x18) = a1;
    x = a2[0];
    y = a2[1];
    z = a2[2];
    *(s32 *)(a0 + 0x2C) = 0x320;
    *(s32 *)(a0 + 0x30) = 0;
    *(s32 *)(a0 + 0x34) = 0x5A00;
    *(s32 *)(a0 + 0x38) = 0x14;
    *(s32 *)(a0 + 0x3C) = 0;
    *(s32 *)(a0 + 0x1C) = x;
    *(s32 *)(a0 + 0x20) = y;
    *(s32 *)(a0 + 0x24) = z;
    *(s16 *)(a0 + 0x40) = func_80077730(a1);
    return a0;
}

void func_80098A70(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_80069A44;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80098AC4);

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80098B5C);

INCLUDE_ASM("asm/us/game/nonmatchings/309F0", func_80098D30);
