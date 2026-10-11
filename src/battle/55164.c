#include "game_action_api.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_actor_queries.h"

extern void func_800213C4(s32);
extern void func_800BCE90(s32);
extern void func_800BCF34(s32);
extern void func_800C5A14(u8 *, s32);
extern void func_800BDD08(s32, s32, s32, s32, s32);
extern void func_800787A0(s32, s32);
extern void func_800774EC(s32, s32);
extern void func_800C591C(s32, s32, s32, s32, s32, s32);
extern s32 func_8007A084(s32);
extern u8 D_8006CA6C[];
extern void func_800C5210(s32, s32);
extern s32 func_80077730(s32);
extern u8 D_8006C6E4[];
extern void func_80077774(s32, s32);
extern s32 func_80078AD8(s32);
extern void func_80079AA4(s32, s32, s32, s32, s32);
extern void func_800BA1DC(s32, s32);
extern void func_8002BCEC(s32, s32);
extern long long func_80076FD8(u8 *);
extern void func_80079D98(u8 *, u8 *);
extern u8 D_8006C70C[];
extern u8 D_8006C4EC[];
extern u8 D_8006C674[];
extern u8 D_8006CB34[];
extern u8 D_8006C69C[];
extern u8 D_8006C6BC[];
extern u8 D_8006CA44[];
typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 pad;
} Vector3i;
extern u8 D_80065174[];
extern u8 D_80065154[];
extern void func_8002BDA8(s32);
extern s32 func_8002BE14(s32);
extern void func_8007B598(s32);
extern void func_8007B5C4(s32);
extern void func_800BAD5C(s32, s32, s32);
extern void func_8007AFCC(s32, s32);
extern void func_8007B9E4(s32, s32);
extern void func_8007BA5C(s32, s32);
extern void func_8007BAE4(s32, s32);
extern void func_8007BB5C(s32, s32);
extern void func_8007BDD4(s32, s32);
extern void func_800245B8(s32, s32, s32, s32);
extern void func_8007BE3C(s32, s32);
extern s32 func_800BD748(s32, s32);
extern void func_800BB570(s32, s32, s32, s32, s32);
extern u8 D_8006CB0C[];
extern s32 func_8002BD74(s32);

extern void func_80079158(s32, s32, s32, s32);
typedef struct { s32 words[18]; } SpawnConfig;
extern SpawnConfig D_8006C5EC;

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800B9524);

s32 func_800B96C8(u8 *a0) {
    func_80076FD8(a0);
    *(s32 *)(a0 + 0x14) = (s32)D_8006C70C;
    func_80079D98(a0, D_8006C4EC);
    *(s16 *)(a0 + 0x4A4) = 0;
    return (s32)a0;
}


void func_800B9710(s32 a0, s32 a1) {
    *(s32 *)(a0 + 0x14) = (s32)D_8006C70C;
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800B9764(s32 a0) {
    s32 s0;
    func_8007B598(a0);
    if (*(s16 *)(a0 + 0x4A4) == 0) {
        s0 = func_8002BE14(0x4C);
        if (s0 != 0) {
            func_800BAD5C((s32)(u32)func_8002BD80(0x4C, (void *)(u32)s0), a0, 0);
        }
        func_8007AFCC(a0, s0);
        *(u16 *)(a0 + 0x4A4) = 1;
    }
}

void func_800B97E0(s32 a0) {
    s32 s0;
    func_8007B5C4(a0);
    if (*(s16 *)(a0 + 0x4A4) == 0) {
        s0 = func_8002BE14(0x4C);
        if (s0 != 0) {
            func_800BAD5C((s32)(u32)func_8002BD80(0x4C, (void *)(u32)s0), a0, 1);
        }
        func_8007AFCC(a0, s0);
        *(u16 *)(a0 + 0x4A4) = 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800B985C);

void func_800B99E4(s32 a0, s32 a1) {
    switch (a1) {
    case 0:
        func_80079AA4(a0, 0x16, 0, 0, -1);
        func_80078754((u8 *)(u32)a0, 0x105);
        break;
    case 0xD:
        func_800BA1DC(a0, 0);
        break;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800B9A54);

void func_800B9C60(s32 self, s32 mode) {
    func_8007BDD4(self, mode);
    switch (mode) {
    case 0:
        func_80079AA4(self, 0xA, 2, 0, -1);
        *(s32 *)(self + 0x3A8) = 0;
        break;
    case 5:
        *(s32 *)(self + 0x3B8) -= ((s64)*(s32 *)(self + 0x3C4) * 0x4718) >> 16;
        break;
    }
    if (*(s32 *)(self + 0x3A8) > 0) {
        *(s32 *)(self + 0x3B8) -= *(s32 *)(self + 0x3A8);
    }
}

void func_800B9D1C(s32 self, s32 mode) {
    func_8007BAE4(self, mode);
    if (mode == 4) {
        s32 product = ((s64)*(s32 *)(self + 0x3C4) * 0x38E0) >> 16;
        *(s32 *)(self + 0x3A4) = 0;
        *(s32 *)(self + 0x3B4) += product * func_8007A084(self);
    }
    if (mode >= 5) {
        *(s32 *)(self + 0x3B4) += (-*(s32 *)(self + 0x3A4)) >> 2;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800B9DD0);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800B9F00);

void func_800BA110(s32 self) {
    SpawnConfig config = D_8006C5EC;
    s32 memory = func_8002BE14(0x690);
    if (memory != 0) {
        s32 object = (s32)(u32)func_8002BD80(0x690, (void *)(u32)memory);
        func_800C591C(object, self, (s32)&config, 3, 8, 0x17);
    }
    func_8007AFCC(self, memory);
    func_800787A0(self, 0x102);
}

void func_800BA1DC(s32 self, s32 mode) {
    s32 position[4];
    s32 velocity[3];
    s32 reference = (s32)(u32)func_80077624((u8 *)(u32)self);
    s32 allocated;
    func_8007767C((u8 *)self, position);
    if (mode == 0) {
        position[1] -= 0x60;
    } else {
        position[1] -= 0x70;
    }
    velocity[0] = func_8007A084(self) * 3 << 4;
    velocity[1] = 0;
    velocity[2] = 0;
    allocated = func_8002BE14(0x184);
    if (allocated != 0) {
        func_800BA2A8((u8 *)func_8002BD80(0x184, (void *)(u32)allocated), self, position, velocity, reference);
    }
    func_8007AFCC(self, allocated);
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BA2A8);

void func_800BA4B0(s32 self, s32 flags) {
    s32 link = self + 0x38;
    *(u32 *)(self + 0x18) = (u32)D_8006C69C;
    *(u32 *)(self + 0x14) = (u32)D_8006C6BC;
    *(u32 *)(self + 0x68) = (u32)D_80065174;
    *(s32 *)(*(s32 *)(self + 0x38) + 4) = *(s32 *)(self + 0x3C);
    *(s32 *)*(s32 *)(link + 4) = *(s32 *)(self + 0x38);
    *(s32 *)(self + 0x38) = link;
    *(s32 *)(self + 0x3C) = link;
    *(u32 *)(self + 0x18) = (u32)D_80065154;
    func_8002BCEC(self, 0);
    if (flags & 1) {
        func_8002BDA8(self);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BA550);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BA754);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BA850);

s32 func_800BA9EC(s32 a0, s32 a1, s32 a2) {
    func_800C5210(a0, a2);
    *(s32 *)(a0 + 0x14) = (s32)D_8006C6E4;
    *(s16 *)(a0 + 0x4A8) = func_80077730(a1);
    *(s32 *)(a0 + 0x488) = (*(s32 *)(a0 + 0x488) * 5) / 6;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BAA64);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BAB64);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BAD5C);

void func_800BAEC0(s32 a0, s32 a1) {
    s32 p = *(s32 *)(a0 + 0x18);
    *(s32 *)(a0 + 0x14) = (s32)D_8006C674;
    *(s16 *)(p + 0x4A4) = 0;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BAF1C);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BB150);

void func_800BB2A4(s32 a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

s32 func_800BB2EC(s32 self) {
    func_80076FD8((u8 *)self);
    *(u32 *)(self + 0x14) = (u32)D_8006CB34;
    *(s32 *)(self + 0x4A4) = 0;
    *(s32 *)(self + 0x4A8) = 0;
    *(s32 *)(self + 0x4AC) = 0;
    *(s32 *)(self + 0x4B0) = 1;
    *(s32 *)(self + 0x4B4) = 0;
    *(s32 *)(self + 0x4B8) = 0;
    *(s32 *)(self + 0x4BC) = 0;
    *(s32 *)(self + 0x4C0) = 0;
    return self;
}

void func_800BB344(s32 a0) {
    if (*(s32 *)(a0 + 0x4AC) == 1) {
        *(s32 *)(a0 + 0x4AC) = 0;
        *(s32 *)(a0 + 0x3F0) = 0;
    }
}

void func_800BB364(s32 a0, s32 a1) {
    func_8007B9E4(a0, a1);
    if (a1 == 2) {
        func_800BB570(a0, 0x10, 2, 8, 0x404040);
    }
}

void func_800BB3BC(s32 a0, s32 a1) {
    func_8007BA5C(a0, a1);
    if (a1 == 4) {
        func_800BB570(a0, 5, 2, 6, 0x404040);
    }
}

void func_800BB414(s32 a0, s32 a1) {
    func_8007BAE4(a0, a1);
    if (a1 == 0) {
        func_800BB570(a0, 5, 2, 8, 0x404040);
    }
}

void func_800BB468(s32 a0, s32 a1) {
    func_8007BB5C(a0, a1);
    if (a1 == 2) {
        func_800BB570(a0, 5, 3, 0xE, 0xFFFFFF);
    }
}

void func_800BB4C0(s32 a0, s32 a1) {
    func_8007BDD4(a0, a1);
    if (a1 == 3) {
        func_800BB570(a0, 5, 2, 8, 0x404040);
    }
}

void func_800BB518(s32 a0, s32 a1) {
    func_8007BE3C(a0, a1);
    if (a1 == 2) {
        func_800BB570(a0, 5, 3, 0xE, 0xFFFFFF);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BB570);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BB684);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BB8B0);

u8 *func_800BBA44(u8 *self, s32 owner, u32 mode) {
    s32 local[3];
    s32 object;
    u32 offset;
    func_8002BC9C((u8 *)(u32)(s32)self, 0);
    *(u8 **)(self + 0x14) = D_8006CB0C;
    object = (s32)func_8007B16C((u8 *)owner);
    *(s32 *)(self + 0x18) = func_8002BD74(object);
    *(s32 *)(self + 0x1C) = owner;
    *(u32 *)(self + 0x20) = mode;
    func_8007767C((u8 *)object, local);
    *(s32 *)(self + 0x24) = local[1];
    offset = (mode << 3) - mode;
    local[0] = (offset + (offset << 6)) << 3;
    local[1] = 0xD548;
    local[2] = 0;
    func_80079158(object, 0x40000000, (s32)local, 0);
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BBB08);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BBC5C);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BBFD0);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BC1B8);

void func_800BC384(s32 a0, s32 a1) {
    s32 v0 = 1;
    *(s32 *)(a0 + 0x4AC) = v0;
    *(s32 *)(a0 + 0x4B4) = a1;
    *(s32 *)(a0 + 0x448) = 0;
}

void func_800BC398(s32 a0, s32 a1) {
    if (*(s32 *)(a0 + 0x4B4) > 0) {
        func_80079AA4(a0, a1, 0, 0, -1);
        *(s32 *)(a0 + 0x3A4) = 0;
        *(s32 *)(a0 + 0x3A8) = 0;
        *(s32 *)(a0 + 0x3AC) = 0;
        *(s32 *)(a0 + 0x3B0) = 0;
        *(s32 *)(a0 + 0x4BC) = 0;
        *(s32 *)(a0 + 0x4C0) = 0;
        *(s32 *)(a0 + 0x448) = 0;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BC3F4);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BC510);

void func_800BC680(s32 a0) {
    s32 s0;
    s0 = func_8002BE14(0x120);
    if (s0 != 0) {
        func_800BD748((s32)(u32)func_8002BD80(0x120, (void *)(u32)s0), a0);
    }
    func_8007AFCC(a0, s0);
}

void func_800BC6DC(s32 a0, s32 a1) {
    if (*(s32 *)(a0 + 0x4B4) > 0) {
        *(s32 *)(a0 + 0x3E0) = a1;
        *(s32 *)(a0 + 0x3F0) = a1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BC6FC);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BC854);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BC9AC);

void func_800BCA84(s32 a0, s32 a1, s32 a2) {
    s32 v0 = func_8002BE14(0xD4);
    register s32 v1 asm("$3");
    if (v0 != 0) {
        func_800BDD08((s32)(u32)func_8002BD80(0xD4, (void *)(u32)v0), a0, a1, a2, 0x300);
    }
    func_8007AFCC(a0, v0);
    func_800787A0(a0, 0x109);
    v1 = 0xA;
    *(s32 *)(a0 + 0x498) = v1;
    func_800774EC(a0, 0xFFFF0000);
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BCB28);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BCC94);

void func_800BCD28(s32 a0, s32 a1) {
    func_8007C0C8((u8 *)(u32)a0 + 0x18, (u8 *)(u32)a1);
    if (func_80078AD8(a1) && a0 != 0) {
        s32 object = *(s32 *)(a0 + 0x14);
        s32 callback = *(s32 *)(object + 0x1C);
        ((void (*)(s32, s32))callback)(a0 + *(s16 *)(object + 0x18), 3);
    }
}

s32 func_800BCD90(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    func_800C591C(a0, a1, a2, a3, a4, a5);
    *(s32 *)(a0 + 0x14) = (s32)D_8006CA6C;
    *(s32 *)(a0 + 0x690) = 0;
    *(s32 *)(a0 + 0x694) = 0;
    *(s32 *)(a0 + 0x698) = func_8007A084(a1);
    *(s32 *)(a0 + 0x69C) = a6;
    return a0;
}

void func_800BCE04(s32 a0, s32 a1) {
    *(s32 *)(a0 + 0x690) += *(s32 *)(a0 + 0x694);
    *(s32 *)(a0 + 0x694) += *(s32 *)(a0 + 0x698) * 10;
    func_800BCE90(a0);
    if (*(s32 *)(a0 + 0x69C) == 1 && *(s32 *)(a0 + 0x24) <= 0) {
        func_800BCF34(a0);
    }
    func_800C5A14((u8 *)(u32)a0, a1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BCE90);

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BCF34);

void func_800BD0D4(s32 a0, s32 a1) {
    s32 value;
    s32 matrix[8];
    value = *(s32 *)(a0 + 0x690);
    matrix[0] = 0x1000;
    matrix[1] = 0;
    matrix[2] = 0x1000;
    matrix[3] = 0;
    matrix[4] = 0x1000;
    matrix[5] = value;
    matrix[6] = 0;
    matrix[7] = 0;
    func_800213C4((s32)matrix);
    {
        s32 object = *(s32 *)(a0 + 0x14);
        s32 callback = *(s32 *)(object + 0x24);
        ((void (*)(s32, s32))callback)(a0 + *(s16 *)(object + 0x20), a1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BD14C);

/* PIN $v0/$v1: keep the field update and state test in retail registers. */
void func_800BD274(s32 object) {
    register s32 position asm("$3");
    register s32 active asm("$2");

    func_800245B8(object + 0x18, *(s32 *)(object + 0x38), 0, 0);
    position = *(s32 *)(object + 0x38);
    active = *(s32 *)(object + 0x4C);
    position += 4;
    *(s32 *)(object + 0x38) = position;
    if (active != 0) {
        s32 value = *(s32 *)(object + 0x48) - 0x10;

        *(s32 *)(object + 0x48) = value;
        if (value >= 0) {
            *(s32 *)(object + 0x50) += 1;
        } else if (object != 0) {
            s32 vtable = *(s32 *)(object + 0x14);
            s32 callback = *(s32 *)(vtable + 0x1C);
            ((void (*)(s32, s32))callback)(object + *(s16 *)(vtable + 0x18), 3);
        }
    } else {
        s32 value = *(s32 *)(object + 0x44) - *(s32 *)(object + 0x40);

        value >>= 1;
        *(s32 *)(object + 0x40) += value;
        if (value == 0) {
            *(s32 *)(object + 0x4C) = 1;
        }
        *(s32 *)(object + 0x50) += 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BD334);

u8 *func_800BD47C(u8 *self, Vector3i position, s32 tag) {
    func_8002BC9C((u8 *)(u32)(s32)self, 0);
    *(s32 *)(self + 0x14) = (s32)D_8006CA44;
    *(s32 *)(self + 0x28) = 0;
    *(s32 *)(self + 0x2C) = -0x14;
    *(s32 *)(self + 0x30) = 0;
    *(s32 *)(self + 0x3C) = 0x40;
    *(s32 *)(self + 0x38) = 0x40;
    *(s32 *)(self + 0x44) = tag;
    *(s32 *)(self + 0x40) = 0x14;
    *(s32 *)(self + 0x18) = position.x;
    *(s32 *)(self + 0x1C) = position.y;
    *(s32 *)(self + 0x20) = position.z;
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/55164", func_800BD50C);
