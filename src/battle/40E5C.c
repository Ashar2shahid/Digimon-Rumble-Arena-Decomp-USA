#include "game_action_api.h"
#include "game_action_update_api.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"

extern "C" {
extern u8 D_8006B05C;

extern u8 D_8006AB7C[];
extern void func_8002BCEC(u8 *, s32);
extern void func_8002BDA8(u8 *);
extern void func_80077774(u8 *, s32);
extern void func_80079D80(u8 *, s32);
extern void func_8007A0C4(u8 *, u8 *, s32, s32);
extern void func_8007B9E4(u8 *, s32);
extern void func_8007BA5C(u8 *, s32);
extern void func_8007BAE4(u8 *, s32);
extern void func_8007BB5C(u8 *, s32);
extern void func_8007BDD4(u8 *, s32);
extern void func_800A5984(u8 *, s32);
extern void func_800A7548(u8 *, s32);
extern void func_800A7710(u8 *, s32);
extern s32 func_80078AD8(s32);
extern u8 D_8006AECC;
extern s32 func_80077730(u8 *);
/* The wide result reserves v0/v1 and keeps the retail constructor schedule. */
extern long long func_80076FD8(void *);
extern void func_800787A0(u8 *, s32);

extern u8 D_8006B02C;
extern s32 func_80077768(u8 *);

extern s32 func_8007A084(u8 *);
extern u8 D_8006B19C;
extern u8 *func_8002BE14(s32);
extern void func_800C591C(u8 *, u8 *, u8 *, s32, s32, s32);
extern void func_8007AFCC(u8 *, u8 *);
extern void func_800A836C(u8 *, u8 *, s32);
extern void func_800A624C(u8 *);
extern void func_800A6314(u8 *, s32 *);
extern void func_8002366C(u32 *, u32 *);
extern void func_8007C0AC(u8 *, u32 *);
extern void func_8007C0A0(u8 *, s32, s32);
extern u8 *func_8002BDC8(s32);
extern void func_800A8EDC(s32, s32);
extern void func_800A9238(s32, s32);
extern u8 D_8006B188;

extern void func_800A8B10(u8 *, u8 *, s32 *);
extern void func_800774EC(u8 *, s32);
extern u8 D_8006AA0C;
extern u8 D_8006AA2C;
extern u8 D_80065174;
extern u8 D_80065154;
extern void func_8007BD08(u8 *);
extern s32 func_80077978(u8 *);
extern void func_800A644C(u8 *);
extern void func_80079580(u8 *);
}

/* Keep retail vtables in rodata; the constructor aliases below use these symbols. */
#pragma interface
class Base {
    s32 fields[5];
public:
    Base(s32);
    virtual ~Base();
};
class A : public Base {
    u8 *f18;
    s32 f1C;
    s32 f20[4];
    s32 f30;
    s32 f34;
    s32 f38;
public:
    A(u8 *);
};
class B : public Base {
    u8 *f18;
    s32 fields[11];
    s32 f48;
public:
    B(u8 *);
};

extern "C" {
INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A521C);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A531C);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A5494);

void func_800A55C0(u8 *arg0, s32 arg1) {
    func_80077774(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800A5608(u8 *self, s32 flags) {
    u8 *link = self + 0x38;
    *(u8 **)(self + 0x18) = &D_8006AA0C;
    *(u8 **)(self + 0x14) = &D_8006AA2C;
    *(u8 **)(self + 0x68) = &D_80065174;
    *(u8 **)(*(u8 **)(self + 0x38) + 4) = *(u8 **)(self + 0x3C);
    *(u8 **)(*(u8 **)(link + 4)) = *(u8 **)(self + 0x38);
    *(u8 **)(self + 0x38) = link;
    *(u8 **)(self + 0x3C) = link;
    *(u8 **)(self + 0x18) = &D_80065154;
    func_8002BCEC(self, 0);
    if (flags & 1) {
        func_8002BDA8(self);
    }
}

void func_800A56A8(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800A56F0(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800A5738(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

s32 func_800A5780(s32 a0) {
    func_80076FD8((void *)a0);
    *(u32 *)(a0 + 0x14) = (u32)&D_8006B05C;
    *(s32 *)(a0 + 0x4B8) = 0;
    *(s32 *)(a0 + 0x4A4) = 0;
    *(s32 *)(a0 + 0x4B4) = 0;
    *(s32 *)(a0 + 0x4B0) = 0;
    *(s32 *)(a0 + 0x4AC) = 0;
    *(s32 *)(a0 + 0x4A8) = 0;
    *(s32 *)(a0 + 0x4BC) = 0;
    return a0;
}

void func_800A57D0(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x4A4)) {
        func_80079D80(arg0, 0x14);
    }
}

void func_800A5800(u8 *arg0, s32 arg1) {
    func_8007B978(arg0, arg1);
    if (arg1 == 0) {
        func_800A5984(arg0, 0xA);
    }
}

void func_800A5840(u8 *arg0, s32 arg1) {
    func_8007B9E4(arg0, arg1);
    if (arg1 == 0) {
        func_800A5984(arg0, 0xA);
    }
}

void func_800A5880(u8 *arg0, s32 arg1) {
    func_8007BA5C(arg0, arg1);
    if (arg1 == 0) {
        func_800A5984(arg0, 0x14);
    }
}

void func_800A58C0(u8 *arg0, s32 arg1) {
    func_8007BAE4(arg0, arg1);
    if (arg1 == 0) {
        func_800A5984(arg0, 0xA);
    }
}

void func_800A5900(u8 *arg0, s32 arg1) {
    func_8007BB5C(arg0, arg1);
    if (arg1 == 0xF) {
        func_800A5984(arg0, 8);
    }
}

void func_800A5944(u8 *arg0, s32 arg1) {
    func_8007BDD4(arg0, arg1);
    if (arg1 == 0) {
        func_800A5984(arg0, 0x11);
    }
}

void func_800A5984(u8 *arg0, s32 arg1) {
    u8 *alloc;

    alloc = func_8002BE14(0x690);
    if (alloc != 0) {
        func_800C591C((u8 *)func_8002BD80(0x690, alloc), arg0, &D_8006B19C, 3, 2, arg1);
    }
    func_8007AFCC(arg0, alloc);
}

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A5A04);

void func_800A5B80(u8 *arg0) {
    func_8007A0C4(arg0, D_8006AB7C, 0x100000, 0x2AA);
}

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A5BAC);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A5D88);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A5E50);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A5FFC);

void func_800A6158(u8 *self, s32 event) {
    s32 velocity[3];
    s32 vertical;
    func_8007BEF4(self, event);
    switch (event) {
    case 0:
        func_80078754(self, 0xD9);
        break;
    case 4:
        func_800A624C(self);
        break;
    case 16:
        velocity[0] = func_8007A084(self) * 128;
        velocity[1] = 128;
        velocity[2] = 0;
        func_800A6314(self, velocity);
        break;
    }
    *(s32 *)(self + 0x3B4) = (s32)(0u - *(u32 *)(self + 0x3A4)) >> 2;
    vertical = *(s32 *)(self + 0x3A8);
    if (vertical > 0) {
        s32 scaled = (s32)(((s64)*(s32 *)(self + 0x3C4) * 0x71C) >> 16);
        *(u32 *)(self + 0x3B8) = 0u - (u32)vertical - (u32)scaled;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A624C);

void func_800A6314(u8 *a0, s32 *a1) {
    u8 *v0 = func_8002BDC8(*(s32 *)(a0 + 0x4B8));
    if (v0 != 0) {
        func_800A836C(v0, (u8 *)a1, 0x47AC1400);
        func_800787A0((u8 *)a0, 0xD2);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A636C);

void func_800A644C(u8 *self) {
    s32 position[4];
    u8 *allocated;
    func_8007A724(self, position, 0x13, &D_8006B188);
    allocated = func_8002BE14(0x4C);
    if (allocated != 0) {
        func_800A8B10((u8 *)func_8002BD80(0x4C, allocated), self, position);
    }
    func_8007AFCC(self, allocated);
    func_800774EC(self, 0xFFFF0000);
    func_800787A0(self, 0xD3);
}

}

A::A(u8 *arg1) : Base(0) {
    f18 = arg1;
    f1C = func_80077768(arg1);
    func_8007A8D0(arg1, (u8 *)f20);
    f30 = func_8007A084(arg1) * 3 << 5;
    f34 = 0;
    f38 = 0;
}
__asm__(
    ".globl func_800A64D8\n"
    ".set func_800A64D8, __1APUc\n"
    ".set __4Basei, func_8002BC9C\n"
    ".set _vt.1A, D_8006B02C"
);

extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A6558);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A6690);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A6808);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A68B0);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A6A30);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A6BB4);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A6D68);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A6E9C);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A6FAC);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A7170);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A7244);

void func_800A750C(u8 *a0, s32 a1) {
    func_800A7548(a0, a1);
    func_800A7710(a0, a1);
}


INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A7548);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A7710);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A794C);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A7A20);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A7C88);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A7F48);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A808C);

void func_800A8240(u8 *arg0, s32 arg1) {
    func_8007C0C8(arg0 + 0x18, (u8 *)(u32)arg1);
    if (func_80078AD8(arg1) != 0 && *(s32 *)(arg0 + 0xAC) == 0) {
        *(s32 *)(arg0 + 0x44) |= 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A82A4);

void func_800A836C(u8 *arg0, u8 *arg1, s32 arg2) {
    u32 temp[3];
    u32 first = *(u32 *)(arg1 + 0);
    u32 second = *(u32 *)(arg1 + 4);
    u32 third = *(u32 *)(arg1 + 8);

    *(u32 *)(arg0 + 0xA8) = 0;
    *(u32 *)(arg0 + 0xB0) = 0;
    *(u32 *)(arg0 + 0x94) = first;
    *(u32 *)(arg0 + 0x98) = second;
    *(u32 *)(arg0 + 0x9C) = third;
    *(u32 *)(arg0 + 0xAC) += 1;
    func_8002366C(temp, (u32 *)arg1);
    temp[0] <<= 1;
    temp[1] <<= 2;
    temp[2] = 0;
    arg0 += 0x18;
    func_8007C0AC(arg0, temp);
    func_8007C0A0(arg0, arg2, 0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A8408);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A852C);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A8698);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A879C);

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A8960);

}

B::B(u8 *arg1) : Base(0) {
    f18 = arg1;
    fields[0] = 0;
    fields[1] = 0;
    fields[2] = 0;
    fields[3] = 0;
    fields[4] = 0;
    fields[5] = 0;
    fields[6] = 0;
    fields[7] = 0;
    fields[8] = 0;
    fields[9] = 0;
    fields[10] = 0;
    f48 = func_80077730(arg1);
}
__asm__(
    ".globl func_800A8B10\n"
    ".set func_800A8B10, __1BPUc\n"
    ".set _vt.1B, D_8006AECC"
);

extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A8B90);

void func_800A8EA0(s32 a0, s32 a1) {
    func_800A8EDC(a0, a1);
    func_800A9238(a0, a1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/40E5C", func_800A8EDC);
}
