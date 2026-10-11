#include "game_rotation.h"
#include "game_action_api.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#include "game_positions.h"
#include "game_actor_queries.h"
#include "game_deferred.h"
#pragma interface
class A {
    s32 fields[5];
public:
    virtual ~A();
};
class B {
    s32 fields[5];
public:
    virtual ~B();
};
class C {
    s32 fields[5];
public:
    virtual ~C();
};
class D {
    s32 fields[5];
public:
    virtual ~D();
};
class VirtualDelete {
    s32 fields[5];
public:
    virtual void method0();
    virtual void method1();
    virtual ~VirtualDelete();
};
__asm__(".set __builtin_delete, func_8002BDA8");
extern "C" {

extern u8 D_80068ECC[];
extern u8 D_80068D74[];
extern u8 D_80068D9C[];
extern u8 D_80068E5C[];
extern u8 D_80065154[];
extern u8 D_80065174[];
extern u8 D_80068BE4[];
extern u8 D_80068C04[];
extern u8 D_80068B9C[];
extern u8 D_80068BBC[];
extern u8 D_80068E84[];
extern u8 D_80068EA4[];
extern u8 D_80068E14[];
extern u8 D_80068E34[];
extern u8 D_80068B6C[];
extern u8 D_80010824[];
extern u8 D_80068D54[];

extern u8 *func_80078AD8(u8 *);
extern u8 *func_800C7898(u8 *, u8 *, s32);
extern u8 *func_800C6588(u8 *, s32, s32 *, s32, s32, s32, s32);
extern void func_8008C4C0(u8 *, u8 *, u8 *, u8 *, u8 *);


extern void func_8008AC70(u8 *, u8 *, u8 *, u8 *, u8 *);
extern void func_80088ED8(u8 *, u8 *, u8 *, u8 *, u8 *);
extern void func_80089670(u8 *, u8 *, u8 *, u8 *, u8 *);

extern void func_8007BCA0(u8 *);
extern void func_8007BCD4(u8 *);
extern void func_8007BEC0(u8 *);
extern s32 func_8007A084(u8 *);
extern void func_80079D58(u8 *);
extern void func_80079D88(u8 *, s32);
extern void func_800787A0(u8 *, s32);
extern void func_8008A638(u8 *);
extern void func_8008A8DC(u8 *, s32);

extern void func_80079AA4(u8 *, s32, s32, s32, s32);
extern void func_80079D80(u8 *, s32);
extern void func_80088D18(u8 *, s32);
extern void func_8002BCEC(u8 *, s32);
extern void func_8002BDA8(u8 *);
extern u8 *func_8002BE14(s32);
extern long long func_80076FD8(u8 *);

extern s32 func_80077730(u8 *);
extern void func_80077774(u8 *, s32);
extern u8 *func_8008B3D8(u8 *, u8 *);
extern void func_8008A700(u8 *);
extern u8 *func_8008B8E0(u8 *, u8 *, u8 *);

void func_800887B0(u8 *self, s32 mode) {
    switch (mode) {
    case 0:
        func_80079AA4(self, 0x16, 0, 0, -1);
        func_80079D80(self, 0x1B);
        func_80078754(self, 0x8B);
        break;
    case 0xE:
        func_80088D18(self, 0);
        break;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008882C);

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_80088A20);

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_80088B4C);

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_80088D18);

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_80088DD0);

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_80088ED8);

void func_800890FC(u8 *self, s32 flags) {
    u8 *link = self + 0x38;
    *(u8 **)(self + 0x18) = D_80068BE4;
    *(u8 **)(self + 0x14) = D_80068C04;
    *(u8 **)(self + 0x68) = D_80065174;
    *(u8 **)(*(u8 **)(self + 0x38) + 4) = *(u8 **)(self + 0x3C);
    *(u8 **)(*(u8 **)(link + 4)) = *(u8 **)(self + 0x38);
    *(u8 **)(self + 0x38) = link;
    *(u8 **)(self + 0x3C) = link;
    *(u8 **)(self + 0x18) = D_80065154;
    func_8002BCEC(self, 0);
    if (flags & 1) {
        func_8002BDA8(self);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008919C);

void func_80089358(u8 *self, u8 *owner) {
    u8 *child;
    u8 *allocated;
    u8 *methods;
    func_8007C0C8(self + 0x18, owner);
    child = func_80078AD8(owner);
    if (child != 0) {
        func_8002BF34((DtorNode *)self, (DtorNode *)func_800C7898(child, self + 0x100, 0x80));
    }
    allocated = func_8002BE14(0x3C);
    if (allocated != 0) {
        func_800C6588((u8 *)func_8002BD80(0x3C, allocated),
                        3, (s32 *)(self + 0x9C), *(s32 *)(self + 0x130) >> 2,
                        0x60, 6, 0x808080);
    }
    func_8002BF34((DtorNode *)self, (DtorNode *)allocated);
    if (self != 0) {
        methods = *(u8 **)(self + 0x14);
        ((void (*)(u8 *, s32))*(u32 *)(methods + 0x1C))
            (self + *(s16 *)(methods + 0x18), 3);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_80089434);

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_80089670);

void func_80089884(u8 *self, s32 flags) {
    u8 *link = self + 0x38;
    *(u8 **)(self + 0x18) = D_80068B9C;
    *(u8 **)(self + 0x14) = D_80068BBC;
    *(u8 **)(self + 0x68) = D_80065174;
    *(u8 **)(*(u8 **)(self + 0x38) + 4) = *(u8 **)(self + 0x3C);
    *(u8 **)(*(u8 **)(link + 4)) = *(u8 **)(self + 0x38);
    *(u8 **)(self + 0x38) = link;
    *(u8 **)(self + 0x3C) = link;
    *(u8 **)(self + 0x18) = D_80065154;
    func_8002BCEC(self, 0);
    if (flags & 1) {
        func_8002BDA8(self);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_80089924);

void func_80089C54(u8 *arg0) {
    *(u32 *)(arg0 + 0x44) |= 1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_80089C68);

u8 *func_8008A26C(u8 *self) {
    func_80076FD8(self);
    *(u8 **)(self + 0x14) = D_80068ECC;
    *(s16 *)(self + 0x4A4) = 0;
    *(s16 *)(self + 0x4A6) = 0;
    *(s16 *)(self + 0x4A8) = 0;
    return self;
}

}
A::~A() {
    func_80077774((u8 *)this, 0);
}
__asm__(
    ".globl func_8008A2AC\n"
    ".set func_8008A2AC, _._1A\n"
    ".set _vt.1A, D_80068ECC"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008A300);

void func_8008A4CC(u8 *arg0, s32 arg1) {
    func_8007BCA0(arg0);
    func_80079D58(arg0);
    if (arg1 == 1) {
        func_80078754(arg0, 0x92);
        func_8008A700(arg0);
    }
    if (arg1 == 6) {
        func_8008A638(arg0);
        func_800787A0(arg0, 0x8D);
    }
    if (arg1 < 7) {
        *(s32 *)(arg0 + 0x3B4) = *(s32 *)(arg0 + 0x3B4) + ((-*(s32 *)(arg0 + 0x3A4)) >> 4);
    }
}

void func_8008A568(u8 *arg0, s32 arg1) {
    func_8007BEC0(arg0);
    func_80079D58(arg0);
    if (arg1 == 1) {
        func_80078754(arg0, 0x92);
        func_8008A700(arg0);
    }
    if (arg1 == 6) {
        func_8008A638(arg0);
        func_800787A0(arg0, 0x8D);
        *(s32 *)(arg0 + 0x3B4) = *(s32 *)(arg0 + 0x3B4) - (func_8007A084(arg0) * 0x3000);
    }
    if (arg1 < 7) {
        *(s32 *)(arg0 + 0x3B4) = *(s32 *)(arg0 + 0x3B4) - (*(s32 *)(arg0 + 0x3A4) >> 4);
        if (*(s32 *)(arg0 + 0x3A8) > 0) {
            *(s32 *)(arg0 + 0x3B8) = *(s32 *)(arg0 + 0x3B8) - *(s32 *)(arg0 + 0x3A8);
        }
    }
}

void func_8008A638(u8 *arg0) {
    s32 tmp[4];
    s32 info[3];
    s16 v;
    s32 raw;
    u8 *s2;
    u8 *s0;
    func_8007A724(arg0, tmp, 0xC, D_80010824);
    raw = func_8007A084(arg0);
    *(u16 *)(arg0 + 0x4A4) = raw;
    v = raw;
    info[0] = (v * 3) << 5;
    info[1] = 0;
    info[2] = 0;
    s2 = func_80077624(arg0);
    s0 = func_8002BE14(0x2CC);
    if (s0) {
        func_8008AC70((u8 *)func_8002BD80(0x2CC, s0), arg0, (u8 *)tmp, (u8 *)info, s2);
    }
    func_8007AFCC(arg0, s0);
    func_80079D80(arg0, 0x1E);
}

void func_8008A700(u8 *arg0) {
    u8 *s0 = func_8002BE14(0x48);
    if (s0) {
        func_8008B3D8((u8 *)func_8002BD80(0x48, s0), arg0);
    }
    func_8007AFCC(arg0, s0);
}

void func_8008A75C(u8 *self, s32 mode) {
    func_8007BCD4(self);
    func_80079D58(self);
    if (mode == 0) {
        *(s16 *)(self + 0x4A8) = 0;
        func_80079D88(self, 0x3C);
        func_80078754(self, 0x93);
        func_800787A0(self, 0x8E);
    }
    if (((u32)mode - 3u) < 0x17) {
        if (func_8007A084(self) > 0) {
            func_8008A8DC(self, 0);
        } else {
            func_8008A8DC(self, 0x800);
        }
        s32 damping = (s32)(0u - (u32)*(s32 *)(self + 0x3A4)) >> 4;
        *(s32 *)(self + 0x3B4) = (s32)((u32)*(s32 *)(self + 0x3B4) + (u32)damping);
    }
}

void func_8008A814(u8 *self, s32 mode) {
    func_8007BEF4(self, mode);
    func_80079D58(self);
    if (mode == 0) {
        *(s16 *)(self + 0x4A8) = 0;
        func_80079D88(self, 0x3C);
        func_80078754(self, 0x93);
        func_800787A0(self, 0x8E);
    }
    if (mode < 0x1A) {
        if (func_8007A084(self) > 0) {
            func_8008A8DC(self, 0);
        } else {
            func_8008A8DC(self, 0x800);
        }
        s32 damping = *(s32 *)(self + 0x3A4) >> 4;
        *(s32 *)(self + 0x3B4) = (s32)((u32)*(s32 *)(self + 0x3B4) - (u32)damping);
        s32 vertical = *(s32 *)(self + 0x3A8);
        if (vertical > 0) {
            *(s32 *)(self + 0x3B8) = (s32)((u32)*(s32 *)(self + 0x3B8) - (u32)vertical);
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008A8DC);

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008A9E4);

void func_8008ABD0(u8 *arg0) {
    s32 tmp[4];
    u8 *s0 = func_80077624(arg0);
    u8 *p;
    func_8007767C((u8 *)func_8007B16C(arg0), tmp);
    tmp[0] += ((s32)(func_80037010((RandomState *)((u32)s0 + 0x360U)) & 0x3F) - 0x20) * 9;
    p = func_8002BE14(0x38);
    if (p) {
        func_8008B8E0((u8 *)func_8002BD80(0x38, p), arg0, (u8 *)tmp);
    }
    func_8007AFCC(arg0, p);
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008AC70);

void func_8008ADF8(u8 *self, s32 flags) {
    u8 *link = self + 0x38;
    *(u8 **)(self + 0x18) = D_80068E84;
    *(u8 **)(self + 0x14) = D_80068EA4;
    *(u8 **)(self + 0x68) = D_80065174;
    *(u8 **)(*(u8 **)(self + 0x38) + 4) = *(u8 **)(self + 0x3C);
    *(u8 **)(*(u8 **)(link + 4)) = *(u8 **)(self + 0x38);
    *(u8 **)(self + 0x38) = link;
    *(u8 **)(self + 0x3C) = link;
    *(u8 **)(self + 0x18) = D_80065154;
    func_8002BCEC(self, 0);
    if (flags & 1) {
        func_8002BDA8(self);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008AE98);

void func_8008AFD4(u8 *arg0) {
    register u8 *object asm("$7") = arg0;
    __asm__ volatile ("" : "+r"(object));
    register s32 check asm("$2") = *(volatile s32 *)(object + 0x2C4);
    if (check < 0x41) {
        goto update;
    }
    if (object != 0) {
        delete (VirtualDelete *)object;
    }
    return;
update:
    register s32 a0 asm("$4") = *(s32 *)(object + 0x84);
    register s32 a1 asm("$5") = *(s32 *)(object + 0x88);
    register s32 a2 asm("$6") = *(s32 *)(object + 0x8C);
    register s32 v0 asm("$2") = *(s32 *)(object + 0x2A4);
    register s32 v1 asm("$3") = *(s32 *)(object + 0x2A8);
    a0 += v0;
    a1 += v1;
    v0 = *(s32 *)(object + 0x2AC);
    v1 = *(volatile s32 *)(object + 0x2C4);
    *(s32 *)(object + 0x84) = a0;
    *(s32 *)(object + 0x88) = a1;
    *(s32 *)(object + 0x6C) = a0;
    *(s32 *)(object + 0x70) = a1;
    a2 += v0;
    v1 += 1;
    *(s32 *)(object + 0x8C) = a2;
    *(s32 *)(object + 0x74) = a2;
    *(volatile s32 *)(object + 0x2C4) = v1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008B078);

u8 *func_8008B3D8(u8 *arg0, u8 *arg1) {
    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_80068E5C;
    *(u8 **)(arg0 + 0x18) = arg1;
    func_8007767C(arg1, (s32 *)(arg0 + 0x1C));
    *(s32 *)(arg0 + 0x2C) = 0x40;
    *(s32 *)(arg0 + 0x30) = 0x40;
    *(s32 *)(arg0 + 0x34) = 0x80;
    *(s32 *)(arg0 + 0x38) = 0;
    *(s32 *)(arg0 + 0x3C) = 0;
    *(s32 *)(arg0 + 0x40) = 0;
    *(s16 *)(arg0 + 0x44) = func_80077730(arg1);
    return arg0;
}

}
B::~B() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_8008B458\n"
    ".set func_8008B458, _._1B\n"
    ".set _vt.1B, D_80068E5C"
);
extern "C" {

void func_8008B4AC(u8 *arg0) {
    register u8 *p asm("$3") = arg0;
    register s32 count asm("$4");
    register s32 increment asm("$2");
    __asm__ volatile ("" : "+r"(p));
    count = *(s32 *)(p + 0x3C);
    if (count < 10) {
        increment = count + 1;
        *(s32 *)(p + 0x3C) = increment;
    } else if (p != (u8 *)0) {
        delete (VirtualDelete *)p;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008B510);

u8 *func_8008B8E0(u8 *arg0, u8 *arg1, u8 *arg2) {
    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_80068D9C;
    s32 temp_v0 = *(s32 *)(arg2 + 0x00);
    s32 temp_v1 = *(s32 *)(arg2 + 0x04);
    s32 temp_a1 = *(s32 *)(arg2 + 0x08);
    *(u8 **)(arg0 + 0x18) = arg1;
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x1C) = temp_v0;
    *(s32 *)(arg0 + 0x20) = temp_v1;
    *(s32 *)(arg0 + 0x24) = temp_a1;
    *(s16 *)(arg0 + 0x34) = func_80077730(arg1);
    return arg0;
}

}
C::~C() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_8008B95C\n"
    ".set func_8008B95C, _._1C\n"
    ".set _vt.1C, D_80068D9C"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008B9B0);

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008BB14);

u8 *func_8008C0B8(u8 *arg0, u8 *arg1) {
    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_80068D74;
    *(u8 **)(arg0 + 0x18) = arg1;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s16 *)(arg0 + 0x30) = func_80077730(arg1);
    return arg0;
}

}
D::~D() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_8008C110\n"
    ".set func_8008C110, _._1D\n"
    ".set _vt.1D, D_80068D74"
);
extern "C" {

void func_8008C164(u8 *arg0) {
    register u8 *s0 asm("$16") = arg0;
    register s32 is_short asm("$3");
    register s32 increment asm("$2");
    __asm__ volatile ("" : "+r"(s0));
    func_8007767C(*(u8 **)(s0 + 0x18), (s32 *)(s0 + 0x1C));
    volatile s32 *counter = (volatile s32 *)(s0 + 0x2C);
    is_short = *counter < 0x18;
    if (is_short) {
        goto increment_count;
    }
    if (s0 != (u8 *)0) {
        delete (VirtualDelete *)s0;
    }
    return;
increment_count:
    increment = *counter + 1;
    *counter = increment;
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008C1E0);

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008C4C0);

void func_8008C654(u8 *self, s32 flags) {
    u8 *link = self + 0x38;
    *(u8 **)(self + 0x18) = D_80068E14;
    *(u8 **)(self + 0x14) = D_80068E34;
    *(u8 **)(self + 0x68) = D_80065174;
    *(u8 **)(*(u8 **)(self + 0x38) + 4) = *(u8 **)(self + 0x3C);
    *(u8 **)(*(u8 **)(link + 4)) = *(u8 **)(self + 0x38);
    *(u8 **)(self + 0x38) = link;
    *(u8 **)(self + 0x3C) = link;
    *(u8 **)(self + 0x18) = D_80065154;
    func_8002BCEC(self, 0);
    if (flags & 1) {
        func_8002BDA8(self);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/243F0", func_8008C6F4);
}
