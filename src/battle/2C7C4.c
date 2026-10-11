#include "game_action_api.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#include "game_positions.h"
#include "game_actor_queries.h"
#include "game_deferred.h"

extern u8 *func_8002BE14(s32);

extern s32 func_800787A0(u8 *, s32);
u8 *func_80093718(u8 *, s32, s32, s32, s32);
extern u8 *func_800942D4(u8 *, u8 *, s32 *, s32, s32);
void func_80093210(u8 *);
void func_80093468(u8 *);

extern u8 D_80069804;

extern u8 D_800696DC;

extern u8 D_800694A4;

extern u8 D_80069794;

extern u8 D_800691B4;

extern u8 D_80069744;

extern u8 D_8006976C;

void func_800933FC(s32 *a0);

extern u8 D_800691DC[];
extern u8 D_800694E4[];
extern u8 D_80069554[];
extern u8 D_800696CC;
extern u8 D_8006982C;
extern u8 D_8006D4EC[];
extern u8 D_80065154[];
extern u8 D_80065174[];
extern u8 D_8006971C[];
extern u8 D_80069204[];
extern u8 D_80069224[];
extern u8 D_8006950C[];
extern u8 D_8006952C[];
extern u8 D_800697BC[];
extern u8 D_800697DC[];
extern void func_800C72C0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_8007C0A0(s32, s32, s32);
extern s32 func_80077730(u8 *);
extern s32 func_8007A084(u8 *);


INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80090B84);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800911A0);

void func_800912FC(u8 *a0, s32 a1) {
    u8 *v1;
    u32 a2, a0v, v0;
    register s32 f asm("$16"); /* PIN $s0: preserve the destruction flag across the base constructor. */

    f = a1;
    *(void **)(a0 + 0x18) = &D_80069204;
    *(void **)(a0 + 0x14) = &D_80069224;
    *(void **)(a0 + 0x68) = &D_80065174;
    v1 = a0 + 0x38;
    a2 = *(u32 *)(a0 + 0x38);
    a0v = *(u32 *)(a0 + 0x3C);
    *(u32 *)(a2 + 4) = a0v;
    a2 = *(u32 *)(v1 + 4);
    v0 = *(u32 *)(a0 + 0x38);
    *(u32 *)(a2 + 0) = v0;
    *(u32 *)(a0 + 0x38) = (u32)v1;
    *(u32 *)(a0 + 0x3C) = (u32)v1;
    *(void **)(a0 + 0x18) = &D_80065154;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

void func_8009139C(u8 *self) {
    u8 *state;
    u32 x = *(u32 *)(self + 0x9C);
    u32 y = *(u32 *)(self + 0xA0);
    u32 z = *(u32 *)(self + 0xA4);
    u32 dx = *(u32 *)(self + 0x8C);
    u32 dy = *(u32 *)(self + 0x90);
    u32 dz = *(u32 *)(self + 0x94);
    x += dx;
    y += dy;
    z += dz;
    *(u32 *)(self + 0x9C) = x;
    *(u32 *)(self + 0xA0) = y;
    *(u32 *)(self + 0x6C) = x;
    *(u32 *)(self + 0x70) = y;
    *(u32 *)(self + 0xA4) = z;
    *(u32 *)(self + 0x74) = z;
    state = *(u8 **)(self + 0x80);
    if (*(u16 *)(state + 0x4A4) != 0 || *(u16 *)(state + 0x4AC) == 0) {
        if (self != 0) {
            u8 *vtable = *(u8 **)(self + 0x14);
            void (*destructor)(u8 *, s32) = *(void (**)(u8 *, s32))(vtable + 0x1C);
            destructor(self + *(s16 *)(vtable + 0x18), 3);
        }
    } else {
        s32 fade = (s32)(*(u32 *)(self + 0x88) + *(u32 *)(self + 0x84));
        *(s32 *)(self + 0x88) = fade;
        if (fade >= 0x3001 && self != 0) {
            u8 *vtable = *(u8 **)(self + 0x14);
            void (*destructor)(u8 *, s32) = *(void (**)(u8 *, s32))(vtable + 0x1C);
            destructor(self + *(s16 *)(vtable + 0x18), 3);
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80091488);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800915C4);

u8 *func_80091734(u8 *self, u8 *owner, s32 *position) {
    s32 x, y, z;
    func_8002BC9C(self, 0);
    *(u32 *)(self + 0x14) = (u32)D_800691DC;
    *(s16 *)(self + 0x22) = func_80077730(owner);
    *(u8 **)(self + 0x18) = owner;
    *(s16 *)(self + 0x1E) = 0;
    self[0x20] = 0;
    *(s16 *)(self + 0x1C) = func_8007A084(owner);
    *(s32 *)(self + 0x24) = 0x1C00;
    x = position[0];
    y = position[1];
    z = position[2];
    *(s32 *)(self + 0x28) = x;
    *(s32 *)(self + 0x30) = z;
    *(s32 *)(self + 0x2C) = (s32)((u32)y + 0x40U);
    return self;
}

void func_800917CC(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_800691DC;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80091820(s32 a0) {
    *(u8 *)(a0 + 0x20) += (0x80 - *(u8 *)(a0 + 0x20)) >> 2;
    if (*(u16 *)(a0 + 0x1E) >= 0xB) {
        *(s32 *)(a0 + 0x24) += (-*(s32 *)(a0 + 0x24)) >> 2;
    }
    if (*(u16 *)(a0 + 0x1E) >= 0x29) {
        if (a0 != 0) {
            s32 v0 = *(s32 *)(a0 + 0x14);
            (*(void (**)(s32, s32))(v0 + 0x1C))(a0 + *(s16 *)(v0 + 0x18), 3);
        }
    } else {
        *(u16 *)(a0 + 0x1E) = *(u16 *)(a0 + 0x1E) + 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800918BC);

void func_80091BA4(s32 a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80091BEC(s32 a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80091C34(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D4EC;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

s32 func_80091C88(s32 a0, u16 a1, s32 a2, s32 a3, s32 a4, s32 a5) {
    func_800C357C(a0, a2, a3, a4, a5);
    *(u16 *)(a0 + 0x48) = a1;
    *(u32 *)(a0 + 0x14) = (u32)&D_800691B4;
    return a0;
}

u8 *func_80091CE0(u8 *a0) {
    func_8008D4D0(a0);
    *(u8 **)(a0 + 0x14) = D_80069554;
    return a0;
}

void func_80091D14(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_80069554;
    func_8008D530(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80091D68(s32 a0, s32 a1) {
    s32 buf[4];
    if (a1 == 1) {
        s32 s0;
        func_8007767C((u8 *)a0, buf);
        s0 = (s32)func_8002BE14(0x74);
        if (s0 != 0) {
            func_80092864((u8 *)func_8002BD80(0x74, (void *)(u32)s0), a0, buf);
        }
        func_8007AFCC((u8 *)a0, (u8 *)s0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80091DD8);

void func_80091FD8(s32 a0) {
    s32 a[4];
    s32 b[4];
    s32 s2;
    s32 s0;
    s2 = (s32)(u32)func_80077624((u8 *)(u32)a0);
    func_8007767C((u8 *)a0, a);
    b[0] = func_8007A084(a0) << 6;
    b[1] = 0;
    b[2] = 0;
    s0 = (s32)func_8002BE14(0xF0);
    if (s0 != 0) {
        func_800920EC((u8 *)func_8002BD80(0xF0, (void *)(u32)s0), a0, a, b, s2);
    }
    func_8007AFCC((u8 *)a0, (u8 *)s0);
}

void func_80092074(s32 a0) {
    u8 *s0 = func_8002BE14(0x690);
    if (s0 != 0) {
        func_800C591C((u8 *)func_8002BD80(0x690, s0), a0, (u32)&D_800694A4, 2, 8, 0xF);
    }
    func_8007AFCC((u8 *)a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800920EC);

void func_800922A8(u8 *a0, s32 a1) {
    u8 *v1;
    u32 a2, a0v, v0;
    register s32 f asm("$16"); /* PIN $s0: preserve the destruction flag across the base constructor. */

    f = a1;
    *(void **)(a0 + 0x18) = &D_8006950C;
    *(void **)(a0 + 0x14) = &D_8006952C;
    *(void **)(a0 + 0x68) = &D_80065174;
    v1 = a0 + 0x38;
    a2 = *(u32 *)(a0 + 0x38);
    a0v = *(u32 *)(a0 + 0x3C);
    *(u32 *)(a2 + 4) = a0v;
    a2 = *(u32 *)(v1 + 4);
    v0 = *(u32 *)(a0 + 0x38);
    *(u32 *)(a2 + 0) = v0;
    *(u32 *)(a0 + 0x38) = (u32)v1;
    *(u32 *)(a0 + 0x3C) = (u32)v1;
    *(void **)(a0 + 0x18) = &D_80065154;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80092348);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80092460);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800925C4);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80092864);

void func_8009295C(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_800694E4;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800929B0);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80092A80);

s32 func_80092D20(s32 a0) {
    func_80076FD8(a0);
    *(u32 *)(a0 + 0x14) = (u32)&D_8006982C;
    *(s32 *)(a0 + 0x4A4) = 0;
    func_80079D98(a0, (u32)&D_800696CC);
    return a0;
}

void func_80092D68(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_8006982C;
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80092DBC(s32 a0) {
    func_80078B70(a0);
    if (*(s32 *)(a0 + 0x4A4) != 0) {
        *(s32 *)(a0 + 0x4A4) -= 1;
    }
    if (func_8007A0A0((s32)func_8007B16C(a0)) == 0xF) {
        *(s32 *)(a0 + 0x4A4) = 0x1E;
    }
    if (*(s32 *)(a0 + 0x4A4) != 0) {
        s32 v = func_8007A0A0(a0);
        if (v < 7) {
            if (v >= 5) {
                *(s32 *)(a0 + 0x4A4) = 0x1E;
            }
        }
    }
}

void func_80092E48(s32 *a0) {
    func_800933FC(a0);
}

void func_80092E68(s32 a0, s32 a1) {
    u8 *s2;
    u8 *s0;
    if (a1 == 0xF) {
        s2 = func_80077624((u8 *)(u32)a0);
        s0 = (s32)func_8002BE14(0x58);
        if (s0 != 0) {
            func_80093D90((s32)(u32)func_8002BD80(0x58, s0), a0, s2);
        }
        func_8007AFCC((u8 *)a0, (u8 *)s0);
    }
}

extern s32 func_8007773C(s32);
extern void func_8007BA5C(s32);

void func_80092EE4(s32 a0, s32 a1) {
    func_8007BA5C(a0);
    if (a1 == 5) {
        s32 v = *(s32 *)(func_8007773C(a0) + 0x8C);
        s32 r = (s32)(((s64)v * *(s32 *)(a0 + 0x3C4)) >> 16);
        *(s32 *)(a0 + 0x3B4) += r * func_8007A084(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80092F74);

void func_80093084(s32 a0) {
    s32 buf[4];
    s32 b[4];
    u8 *s0;
    func_8007767C((u8 *)a0, buf);
    buf[1] = buf[1] - 0x84;
    b[0] = func_8007A084(a0) * 24;
    b[1] = 0;
    b[2] = 0;
    s0 = (s32)func_8002BE14(0x58);
    if (s0 != 0) {
        func_8009352C((s32)(u32)func_8002BD80(0x58, s0), a0, buf, b);
    }
    func_8007AFCC((u8 *)a0, (u8 *)s0);
}

void func_8009311C(s32 a0, s32 a1) {
    func_8007BCA0(a0, a1);
    if (a1 == 0) {
        func_80078754((u8 *)(u32)a0, 0xAC);
    }
    if (a1 == 0xA) {
        func_80093210(a0);
    }
}

void func_80093174(s32 a0, s32 a1) {
    func_8007BEC0(a0);
    if (a1 == 0) {
        func_80078754((u8 *)(u32)a0, 0xAC);
        func_800787A0((u8 *)a0, 0xA6);
    }
    if (a1 == 0xE) {
        func_80093210(a0);
    }
    if (a1 < 0xF) {
        *(s32 *)(a0 + 0x3B4) -= *(s32 *)(a0 + 0x3A4) >> 4;
        if (*(s32 *)(a0 + 0x3A8) > 0) {
            *(s32 *)(a0 + 0x3B8) -= *(s32 *)(a0 + 0x3A8);
        }
    }
}

void func_80093210(u8 *owner) {
    s32 position[4];
    s32 velocity[3];
    s32 payload;
    u8 *allocation;
    u8 *object;
    func_8007767C(owner, position);
    position[1] = (s32)((u32)position[1] - 0x84U);
    velocity[0] = (s32)((u32)func_8007A084(owner) * 144U);
    velocity[1] = 0;
    velocity[2] = 0;
    payload = (s32)(u32)func_80077624(owner);
    allocation = func_8002BE14(0xD4);
    if (allocation != 0) {
        object = (u8 *)func_8002BD80(0xD4, allocation);
        func_80093718(object, (s32)owner, payload, (s32)position, (s32)velocity);
    }
    func_8007AFCC(owner, allocation);
    func_800787A0(owner, 0xA7);
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800932D0);

void func_800933FC(s32 *a0) {
    a0[0x12A] = 1;
}

void func_80093408(s32 *a0) {
    s32 pos[4];
    s32 delta[3];
    register s32 dx asm("$6");
    register s32 dy asm("$7");
    register s32 dz asm("$3");
    register s32 base asm("$2");
    register s32 y asm("$5");
    register s32 *out asm("$4"); /* PIN $a2/$a3/$v1/$v0/$a1/$a0: vector-delta registers. */

    func_8007767C((u8 *)a0, pos);
    out = delta;
    dx = pos[0];
    dy = pos[1];
    base = *(s32 *)((u8 *)a0 + 0x4B0);
    dz = pos[2];
    y = *(s32 *)((u8 *)a0 + 0x4B4);
    dx -= base;
    base = *(s32 *)((u8 *)a0 + 0x4B8);
    dy -= y;
    delta[0] = dx;
    delta[1] = dy;
    dz -= base;
    delta[2] = dz;
    func_800237A0(out);
}

void func_80093468(u8 *owner) {
    s32 position[4];
    s32 payload;
    u8 *allocation;
    u8 *object;
    func_8007767C(owner, position);
    position[1] = (s32)((u32)position[1] - 0x10U);
    position[0] = (s32)((u32)position[0] + (u32)func_8007A084(owner) * 384U);
    payload = (s32)(u32)func_80077624(owner);
    allocation = func_8002BE14(0x54);
    if (allocation != 0) {
        object = (u8 *)func_8002BD80(0x54, allocation);
        func_800942D4(object, owner, position, func_8007A084(owner), payload);
    }
    func_8007AFCC(owner, allocation);
}

s32 func_8009352C(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 v0 = func_80077730(a1);
    func_800C31B0(a0, (u32)&D_800696DC, a2, a3, 0x33, 0x646464, v0);
    *(u32 *)(a0 + 0x14) = (u32)&D_80069804;
    return a0;
}

void func_800935AC(u8 *a0, s32 a1) {
    s32 v = 0xC8 - (*(s32 *)(a0 + 0x54) << 3);
    *(u32 *)(a0 + 0x24) = v | (v << 8) | (v << 16);
    *(s32 *)(a0 + 0x20) += 0xA;
    func_800C33D0(a0, a1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800935F8);

u8 *func_80093718(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    func_800C72C0((s32)a0, a1, a3, a4, 0x60, 0, 0x800, 3);
    *(u32 *)(a0 + 0x18) = (u32)D_800697BC;
    *(u32 *)(a0 + 0x14) = (u32)D_800697DC;
    *(s32 *)(a0 + 0xC0) = a1;
    *(s32 *)(a0 + 0xC4) = a2;
    *(s32 *)(a0 + 0xC8) = 0;
    *(s32 *)(a0 + 0xCC) = 0x707070;
    *(s32 *)(a0 + 0xD0) = 0x303030;
    func_8007C0A0((s32)(a0 + 0x18), 0x05A81800, 2);
    return a0;
}

void func_800937CC(s32 a0, s32 a1) {
    s32 s0;
    s32 buf[4];
    s32 v1;
    if (*(s32 *)(a0 + 0xB8) & 1) {
        s32 v0 = (s32)func_80037010((RandomState *)(*(u32 *)(a0 + 0xC4) + 0x360U));
        v1 = (-*(s32 *)(a0 + 0x90)) >> 4;
        buf[1] = (v0 & 0xF) - 8;
        buf[2] = 0;
        buf[0] = v1;
        s0 = (s32)func_8002BE14(0x58);
        if (s0 != 0) {
            func_80093B5C((s32)(u32)func_8002BD80(0x58, (void *)(u32)s0), *(s32 *)(a0 + 0xC0), a0 + 0x80, buf);
        }
        func_8002BF34(a0, s0);
    }
    *(s32 *)(a0 + 0xC8) += 1;
    if (*(s32 *)(a0 + 0xC8) >= 6) {
        *(s32 *)(a0 + 0xC8) = 0;
    }
    func_800C7478(a0, a1);
}

void func_800938A0(s32 a0, u8 *collider) {
    func_8007C0C8((u8 *)(u32)a0 + 0x18, collider);
    func_800C7644(a0, 0);
    if (a0 != 0) {
        s32 v0 = *(s32 *)(a0 + 0x14);
        (*(void (**)(s32, s32))(v0 + 0x1C))(a0 + *(s16 *)(v0 + 0x18), 3);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800938F8);

s32 func_80093B5C(s32 a0, s32 a1, s32 a2, s32 a3) {
    func_800C3258(a0, 9, a2, a3, 0x19, 0x202080, 0);
    *(u32 *)(a0 + 0x14) = (u32)&D_80069794;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80093BAC);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80093C68);

s32 func_80093D90(s32 a0, s32 a1) {
    func_8002BC9C(a0, 0);
    *(u32 *)(a0 + 0x14) = (u32)&D_8006976C;
    *(s32 *)(a0 + 0x18) = a1;
    *(s32 *)(a0 + 0x1C) = 0;
    *(s32 *)(a0 + 0x20) = 0;
    *(s32 *)(a0 + 0x24) = 0;
    *(s32 *)(a0 + 0x28) = 0;
    *(s32 *)(a0 + 0x2C) = 0;
    *(s32 *)(a0 + 0x30) = 0;
    *(s32 *)(a0 + 0x34) = 0;
    *(s32 *)(a0 + 0x38) = 0;
    *(s32 *)(a0 + 0x3C) = 0;
    *(s32 *)(a0 + 0x48) = 0;
    *(s32 *)(a0 + 0x4C) = 0;
    *(s32 *)(a0 + 0x40) = 0;
    *(s32 *)(a0 + 0x50) = 0;
    *(s16 *)(a0 + 0x54) = func_80077730(a1);
    return a0;
}

void func_80093E18(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_8006976C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80093E6C);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800940E8);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800942D4);

void func_80094394(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_80069744;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800943E8);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80094510);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_8009458C);

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_800948B0);

void func_80094AA4(u8 *a0, s32 a1) {
    u8 *v1;
    u32 a2;
    u32 *new_var;
    u32 *new_var2;
    u32 a0v;
    u32 v0;
    register s32 f asm("$16"); /* PIN $s0: preserve the destruction flag in the retail callee-save. */

    f = a1;
    *((void **)(a0 + 0x14)) = &D_8006971C;
    *((void **)(a0 + 0x6C)) = &D_80065174;
    v1 = a0 + 0x3C;
    new_var2 = (u32 *)((*((u32 *)(a0 + 0x3C))) + 4);
    ;
    a0v = *((u32 *)(a0 + 0x40));
    *new_var2 = a0v;
    new_var = (u32 *)(a0 + 0x3C);
    a2 = *((u32 *)(v1 + 4));
    v0 = *((u32 *)(a0 + 0x3C));
    *((u32 *)(a2 + 0)) = v0;
    *new_var = (u32)v1;
    *((u32 *)(a0 + 0x40)) = (u32)v1;
    *((void **)(a0 + 0x18)) = &D_80065154;
    func_8002BCEC(a0, 0);
    if (f & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/2C7C4", func_80094B38);
