#include "game_action_api.h"
#include "game_action_update_api.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#include "game_actor_queries.h"
#include "game_positions.h"
#pragma interface
class C1 {
    s32 fields[5];
public:
    virtual ~C1();
};
class C2 {
    s32 fields[5];
public:
    virtual ~C2();
};
class C3 {
    s32 fields[5];
public:
    virtual ~C3();
};
class C4 {
    s32 fields[5];
public:
    virtual ~C4();
};
class C5 {
    s32 fields[5];
public:
    virtual ~C5();
};

extern "C" {


void func_8007A97C(u8 *, s32, s32, s32);
extern s32 func_80077730(u8 *);
void func_8007B9E4(u8 *);
void func_8007BB5C(u8 *);
void func_8007BA5C(u8 *);
extern void func_8007BDD4(u8 *);
extern void func_8007BAE4(u8 *);
extern void func_800794D4(u8 *actor, s32 mode);
s32 func_8007A084(u8 *);
u8 *func_8002BE14(s32);
void func_8007AFCC(u8 *, u8 *);
void func_800C357C(void *, void *, void *, s32, s32);
void func_8008ED54(u8 *, u8 *, void *, void *, void *);
void func_8008F710(u8 *, u8 *, void *, void *);
void func_8008FFB4(u8 *, u8 *, void *, void *, void *);
void func_8009057C(u8 *, u8 *, void *, void *, void *);
void func_800911A0(u8 *, u8 *, void *, void *, void *);
void func_80079AA4(u8 *, s32, void *, s32, s32);
void func_80079D80(u8 *, s32);
s32 func_8007760C(u8 *);
void func_8008E7BC(u8 *);
void func_8008E864(u8 *, s32);
void func_8008EBA0(u8 *);
extern void func_800C4100(void);
extern void func_8002BCEC(u8 *, s32);
extern void func_8002BDA8(u8 *);
extern u8 D_800692BC[];
extern u8 D_8006924C[];
extern u8 D_80068DEC[];
extern u8 D_80068DC4[];
extern void func_80077774(u8 *, s32);
extern u8 D_8006937C[];
extern u8 *func_80076FD8(u8 *);

extern u8 D_800690C0[];
extern u8 D_800690D0[];
extern u8 D_80069128[];
extern u8 D_800690E0[];
extern void func_800C591C(u8 *, u8 *, u8 *, s32, s32, s32);
extern void func_800C6588(u8 *, s32, s32 *, s32, s32, s32, s32);

extern u8 *func_80078AD8(u8 *);
void func_8008C8D4(u8 *arg0) {
    register u8 *t0 asm("$8"); /* PIN $t0: stable object base */
    register s32 v0 asm("$2"); /* PIN $v0: loaded state/value */
    register s32 v1 asm("$3"); /* PIN $v1: field/callback temporary */
    register s32 a0 asm("$4"); /* PIN $a0: field/callback argument */
    register s32 a1 asm("$5"); /* PIN $a1: aggregate field */
    register s32 a2 asm("$6"); /* PIN $a2: aggregate field */
    register s32 a3 asm("$7"); /* PIN $a3: aggregate field */

    t0 = arg0;
    __asm__ volatile ("" : "+r"(t0));
    v0 = *(s32 *)(t0 + 0x80);
    v1 = *(s16 *)(v0 + 0x4A8);
    if (v1 != 0) {
        *(s16 *)(t0 + 0xBA) = 1;
        v0 = *(s32 *)(t0 + 0x44);
        v0 |= 1;
        *(s32 *)(t0 + 0x44) = v0;
    }
    v0 = *(u16 *)(t0 + 0xBA);
    if (v0 != 0) {
        v0 = *(s32 *)(t0 + 0x98);
        v1 = v0 >> 2;
        v0 -= v1;
        *(s32 *)(t0 + 0x98) = v0;
        a0 = *(s32 *)(t0 + 0x9C);
        v1 = a0 >> 2;
        a0 -= v1;
        *(s32 *)(t0 + 0x9C) = a0;
        v0 = *(s32 *)(t0 + 0xA0);
        v1 = v0 >> 2;
        v0 -= v1;
        *(s32 *)(t0 + 0xA0) = v0;
    }

    a1 = *(s32 *)(t0 + 0x88);
    a2 = *(s32 *)(t0 + 0x8C);
    a3 = *(s32 *)(t0 + 0x90);
    v0 = *(s32 *)(t0 + 0x98);
    v1 = *(s32 *)(t0 + 0x9C);
    a0 = *(s32 *)(t0 + 0xA0);
    a1 += v0;
    a2 += v1;
    a3 += a0;
    *(s32 *)(t0 + 0x88) = a1;
    *(s32 *)(t0 + 0x8C) = a2;
    *(s32 *)(t0 + 0x90) = a3;
    *(s32 *)(t0 + 0x6C) = a1;
    *(s32 *)(t0 + 0x70) = a2;
    *(s32 *)(t0 + 0x74) = a3;
    v0 = *(s32 *)(t0 + 0xB4);
    v0 = v0 + 1;
    *(s32 *)(t0 + 0xB4) = v0;
    v0 = v0 < 0x29;
    if (v0 == 0) {
        if (t0 == 0) {
            goto done;
        }
        v0 = *(s32 *)(t0 + 0x14);
        a0 = *(s16 *)(v0 + 0x18);
        v1 = *(s32 *)(v0 + 0x1C);
        ((void (*)(u8 *, s32))v1)(t0 + a0, 3);
        goto done;
    }
    v0 = *(volatile s32 *)(t0 + 0xB4);
    v0 = v0 < 0x21;
    if (v0 != 0) {
        goto done;
    }
    *(s16 *)(t0 + 0xBA) = 1;
    v0 = *(s32 *)(t0 + 0x44);
    v0 |= 1;
    *(s32 *)(t0 + 0x44) = v0;
done:
    ;
}

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008C9FC);

u8 *func_8008CC00(u8 *arg0, u8 *arg1) {
    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_80068DEC;
    func_8007A94C(arg1, arg0 + 0x18);
    *(s16 *)(arg0 + 0x2C) = func_80077730(arg1);
    *(s32 *)(arg0 + 0x28) = 0;
    return arg0;
}

}
C1::~C1() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_8008CC60\n"
    ".set func_8008CC60, _._2C1\n"
    ".set _vt.2C1, D_80068DEC\n"
    ".set __builtin_delete, func_8002BDA8"
);
extern "C" {

void func_8008CCB4(u8 *arg0) {
    volatile s32 *count = (volatile s32 *)(arg0 + 0x28);
    if (*count >= 0x18) {
        if (arg0 != 0) {
            u8 *vtable = *(u8 **)(arg0 + 0x14);
            s16 offset = *(s16 *)(vtable + 0x18);
            register u8 *receiver asm("$4"); /* PIN $a0: preserve the computed callback receiver before jalr. */
            register void (*callback)(u8 *, s32) asm("$3"); /* PIN $v1: retail keeps the indirect target in v1. */
            receiver = arg0 + offset;
            callback = (void (*)(u8 *, s32))(*(u32 *)(vtable + 0x1C));
            callback(receiver, 3);
        }
    } else {
        (*count)++;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008CD28);

u8 *func_8008D11C(u8 *self, u8 *owner, u8 *random_context) {
    RandomState *random_base;
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_80068DC4;
    func_8007A94C(owner, self + 0x18);
    *(s16 *)(self + 0x3C) = func_80077730(owner);
    random_base = (RandomState *)((u32)random_context + 0x360U);
    *(s32 *)(self + 0x28) = (((s32)func_80037010(random_base) & 0x3F) - 0x20) * 2;
    *(s32 *)(self + 0x2C) = (((s32)func_80037010(random_base) & 0x3F) - 0x20) * 2;
    *(s32 *)(self + 0x30) = 0;
    *(s32 *)(self + 0x38) = 0;
    *(s16 *)(self + 0x3C) = func_80077730(owner);
    return self;
}

}
C2::~C2() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_8008D1CC\n"
    ".set func_8008D1CC, _._2C2\n"
    ".set _vt.2C2, D_80068DC4"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008D220);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008D2DC);

u8 *func_8008D4D0(u8 *self) {
    func_80076FD8(self);
    *(u8 **)(self + 0x14) = D_8006937C;
    *(s16 *)(self + 0x4A6) = 0;
    *(s16 *)(self + 0x4A8) = 0;
    *(s16 *)(self + 0x4AA) = 0;
    *(s32 *)(self + 0x4B0) = 0;
    *(s32 *)(self + 0x4B4) = 0;
    *(s32 *)(self + 0x4B8) = 0;
    *(s32 *)(self + 0x4BC) = 0;
    *(s32 *)(self + 0x4C0) = 0;
    *(s32 *)(self + 0x4C4) = 0;
    *(s32 *)(self + 0x4C8) = 0;
    *(s32 *)(self + 0x4CC) = 0;
    return self;
}

}
C3::~C3() {
    func_80077774((u8 *)this, 0);
}
__asm__(
    ".globl func_8008D530\n"
    ".set func_8008D530, _._2C3\n"
    ".set _vt.2C3, D_8006937C"
);
extern "C" {

void func_8008D584(u8 *arg0) {
    *(u16 *)(arg0 + 0x4AA) = 0;
    if (*(u16 *)(arg0 + 0x4AC) != 0) {
        func_800794D4(func_8007B16C(arg0), 1);
        *(u16 *)(arg0 + 0x4AC) = 0;
        *(u16 *)(arg0 + 0x4A8) = 0;
    }
}

void func_8008D5D0(u8 *arg0, s32 arg1) {
    func_8007BB5C(arg0);
    if (arg1 == 0x11) {
        func_8007A97C(arg0, 1, 0x50, 8);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008D61C);

void func_8008D838(u8 *actor, s32 mode) {
    func_8007B978(actor, mode);
    switch (mode) {
    case 4: {
        s64 product = (s64)*(s32 *)(actor + 0x3C4) * 0x71C0;
        *(s32 *)(actor + 0x3A4) = 0;
        s32 impulse = (s32)(product >> 16);
        impulse *= func_8007A084(actor);
        *(u32 *)(actor + 0x3B4) += (u32)impulse;
        break;
    }
    case 7:
        func_8008EBA0(actor);
        break;
    }
    if (mode >= 5) {
        *(u32 *)(actor + 0x3B4) -= (u32)(*(s32 *)(actor + 0x3A4) >> 4);
    }
}

void func_8008D904(u8 *arg0, s32 arg1) {
    func_8007B9E4(arg0);
    if (arg1 == 8) {
        func_8008EBA0(arg0);
    }
}

void func_8008D948(u8 *arg0, s32 arg1) {
    func_8007BA5C(arg0);
    if (arg1 == 0x16) {
        func_8007A97C(arg0, 1, 0x50, 8);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008D994);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008DA3C);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008DC30);

void func_8008DE50(u8 *arg0, s32 arg1) {
    func_8007BDD4(arg0);
    if (arg1 == 5) {
        register s32 source asm("$2"); /* PIN $v0: retain the fixed-point input through the multiply. */
        register s32 factor asm("$5"); /* PIN $a1: match the retail constant multiplier operand. */
        register long long product asm("$2"); /* PIN $v0: place the low product half in the retail register pair. */
        source = *(s32 *)(arg0 + 0x3C4);
        factor = 0x6388;
        product = (long long)source * factor;
        *(s32 *)(arg0 + 0x3B8) -= product >> 16;
    }
    if (*(s32 *)(arg0 + 0x3A8) > 0) {
        *(s32 *)(arg0 + 0x3B8) -= *(s32 *)(arg0 + 0x3A8);
    }
}

void func_8008DEDC(u8 *arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        func_80079AA4(arg0, 0x17, (void *)2, 0, -1);
        func_8008E864(arg0, 1);
        func_80079D80(arg0, 0x14);
        if (func_8007760C(arg0) == 5) {
            func_80078754(arg0, 0x9A);
        } else {
            func_80078754(arg0, 0xA3);
        }
        break;
    case 0xA:
        func_8008E7BC(arg0);
        break;
    }
}

void func_8008DF84(u8 *arg0, s32 arg1) {
    register u8 *s1 asm("$17"); /* PIN $s1: retain the object base across the helper call. */
    register s32 s0 asm("$16"); /* PIN $s0: preserve the mode for the switch. */
    s1 = arg0;
    s0 = arg1;
    func_8007BAE4(s1);
    switch (s0) {
    case 6: {
        register s32 source asm("$2"); /* PIN $v0: retain the fixed-point input through the multiply. */
        register s32 factor asm("$5"); /* PIN $a1: match the retail constant multiplier operand. */
        register long long product asm("$2"); /* PIN $v0: place the low product half in the retail register pair. */
        source = *(s32 *)(s1 + 0x3C4);
        factor = 0x71C0;
        product = (long long)source * factor;
        *(s32 *)(s1 + 0x3B8) -= product >> 16;
        break;
    }
    case 0x10:
        *(s32 *)(s1 + 0x3B8) = 0;
        break;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008E008);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008E13C);

void func_8008E72C(u8 *arg0) {
    s32 sp18[4];
    s32 sp28[4];
    u8 *v = func_8007B16C(arg0);
    u8 *s0;

    sp28[0] = 0;
    sp28[1] = 0;
    sp28[2] = 0;
    sp28[3] = 0;
    func_8007767C(v, sp18);
    s0 = func_8002BE14(0x48);
    if (s0) {
        func_800C357C((u8 *)func_8002BD80(0x48, s0), sp18, sp28, 0x60, 0x808080);
    }
    func_8007AFCC(arg0, s0);
}

void func_8008E7BC(u8 *arg0) {
    s32 sp18[4];
    s32 sp28[3];
    u8 *s2 = func_80077624(arg0);
    u8 *s0;

    func_8007A724(arg0, (u8 *)sp18, 0xC, D_800690C0);
    sp28[0] = func_8007A084(arg0) << 6;
    sp28[1] = 0;
    sp28[2] = 0;
    s0 = func_8002BE14(0x160);
    if (s0) {
        func_8008ED54((u8 *)func_8002BD80(0x160, s0), arg0, sp18, sp28, s2);
    }
    func_8007AFCC(arg0, s0);
}

void func_8008E864(u8 *arg0, s32 arg1) {
    s32 buf[4];
    u8 *s2 = func_80077624(arg0);
    u8 *s0;

    func_8007A724(arg0, (u8 *)buf, 0xC, D_800690D0);
    buf[3] = arg1;
    s0 = func_8002BE14(0x150);
    if (s0) {
        func_8008F710((u8 *)func_8002BD80(0x150, s0), arg0, buf, s2);
    }
    func_8007AFCC(arg0, s0);
}

void func_8008E8F8(u8 *arg0) {
    s32 sp18[4];
    s32 sp28[4];
    s32 sp38[4];
    u8 *s2 = func_80077624(arg0);
    u8 *s0;

    sp28[0] = func_8007A084(arg0) << 6;
    sp28[1] = 0;
    sp28[2] = 0;
    sp38[0] = 0;
    sp38[1] = 0;
    sp38[2] = 0;
    sp38[3] = 0;
    func_8007A724(arg0, (u8 *)sp18, 0xC, (u8 *)sp38);
    s0 = func_8002BE14(0xA4);
    if (s0) {
        func_8008FFB4((u8 *)func_8002BD80(0xA4, s0), arg0, sp18, sp28, s2);
    }
    func_8007AFCC(arg0, s0);
}

void func_8008E9AC(u8 *self) {
    u8 *allocation = func_8002BE14(0x690);
    if (allocation != 0) {
        func_800C591C((u8 *)func_8002BD80(0x690, allocation), self,
                      D_800690E0, 3, 8, 0xE);
    }
    func_8007AFCC(self, allocation);
}

void func_8008EA24(u8 *arg0) {
    s32 sp18[4];
    s32 sp28[3];
    u8 *s2 = func_80077624(arg0);
    u8 *s0;

    func_8007767C(arg0, sp18);
    sp28[0] = func_8007A084(arg0) << 8;
    sp28[1] = -0x40;
    sp28[2] = 0;
    s0 = func_8002BE14(0x920);
    if (s0) {
        func_8009057C((u8 *)func_8002BD80(0x920, s0), arg0, sp18, sp28, s2);
    }
    func_8007AFCC(arg0, s0);
}

void func_8008EAC4(u8 *arg0) {
    s32 sp18[4];
    s32 sp28[3];
    s32 sp38[3];
    u8 *s0;

    func_8007A724(arg0, (u8 *)sp18, 1, D_80069128);
    sp18[0] += func_8007A084(arg0) << 8;
    sp28[0] = func_8007A084(arg0) << 8;
    sp28[1] = 0;
    sp28[2] = 0;
    sp38[0] = func_8007A084(arg0) * 0x71C0;
    sp38[1] = -0x38E0;
    sp38[2] = 0;
    s0 = func_8002BE14(0xAC);
    if (s0) {
        func_800911A0((u8 *)func_8002BD80(0xAC, s0), arg0, sp18, sp28, sp38);
    }
    func_8007AFCC(arg0, s0);
}

void func_8008EBA0(u8 *self) {
    s32 position[3];
    u8 *allocation;
    func_8007767C(self, position);
    position[0] = (s32)((u32)position[0] + (u32)func_8007A084(self) * 0xC0U);
    position[1] = (s32)((u32)position[1] - 0x20U);
    allocation = func_8002BE14(0x3C);
    if (allocation != 0) {
        func_800C6588((u8 *)func_8002BD80(0x3C, allocation), 6, position, 0x10, 0x50, 8, 0xA0A0A0);
    }
    func_8007AFCC(self, allocation);
}

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008EC54);

void func_8008ECB0(u8 *arg0) {
    s32 sp18[4];
    s32 value;
    u8 *dest;
    func_800C4100();
    value = *(s32 *)(arg0 + 0x54);
    dest = arg0 + 0x28;
    sp18[0] = 0;
    sp18[1] = 0;
    sp18[2] = 0;
    sp18[3] = 0;
    func_8007A724((u8 *)value, dest, 0xC, (u8 *)sp18);
}

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008ECF8);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008ED54);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008EFB4);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008F054);

void func_8008F278(u8 *arg0, u8 *arg1) {
    s32 sp10[4];
    register u8 *s1 asm("$17"); /* PIN $s1: object */
    register u8 *s0 asm("$16"); /* PIN $s0: second object */
    u8 *v0;
    register s32 v1 asm("$3"); /* PIN $v1: flag word */

    s1 = arg0;
    s0 = arg1;
    func_8007C0C8(s1 + 0x18, s0);
    v0 = func_80078AD8(s0);
    if (v0 != 0) {
        func_8007767C(v0, sp10);
        v1 = *(s32 *)(s1 + 0x44);
        v1 |= 1;
        *(s32 *)(s1 + 0x44) = v1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008F2D4);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008F710);

}
C4::~C4() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_8008F8E8\n"
    ".set func_8008F8E8, _._2C4\n"
    ".set _vt.2C4, D_800692BC"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008F93C);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008FA94);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008FC4C);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008FC90);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8008FFB4);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8009018C);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8009022C);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_80090310);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_800903D8);

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_8009057C);

}
C5::~C5() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_800907A8\n"
    ".set func_800907A8, _._2C5\n"
    ".set _vt.2C5, D_8006924C"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/28514", func_800907FC);
}
