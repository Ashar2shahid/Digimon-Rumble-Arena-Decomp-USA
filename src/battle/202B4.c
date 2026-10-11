#include "game_action_api.h"
#include "game_velocity_api.h"
#include "game_placement_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_deferred.h"

extern "C" {

extern void func_8002BCEC(u8 *, s32);
extern void func_8002BDA8(u8 *);
extern u8 *func_8002BE14(s32);

extern void func_80077774(u8 *, s32);
extern void func_80079DA0(u8 *, s32);
extern s32 func_8007A084(u8 *);
extern void func_8007B9E4(u8 *, s32);
extern void func_8007BA5C(u8 *, s32);
extern void func_80085400(u8 *, u8 *, u8 *);
extern void func_80085E30(u8 *, u8 *, u8 *);
extern u8 *func_80086574(u8 *, u8 *, u8 *);
extern u8 *func_80087B30(u8 *, u8 *);

extern void func_80076FD8(u8 *);
extern void func_80079D98(u8 *, u8 *);
extern u8 D_80068C2C[];
extern u8 D_80068B5C[];
extern u8 D_8006874C[];
extern u8 D_80068724[];
extern u8 D_800686FC[];
extern u8 D_800686D4[];
extern void func_80024340(u8 *, s32);
extern void func_80085984(u8 *, u8 *, u8 *, u8 *);
extern u8 *func_80087944(u8 *, u8 *, u8 *, u8 *);
extern void func_8007BCA0(u8 *, s32);
extern void func_80079D58(u8 *);
extern void func_800787A0(u8 *, s32);
extern s32 func_80077730(u8 *);

extern void func_80086BA0(u8 *, u8 *, u8 *, u8 *, u8 *);
extern u8 D_80068644[];
extern void func_800876B4(u8 *);
extern void func_8007BEC0(u8 *, s32);
extern u8 *func_800C72C0(u8 *, u8 *, s32 *, s32 *, s32, u32, s32, s32);
extern u8 D_800689E4[], D_8006893C[], D_8006899C[], D_800689BC[], D_80068974[];
extern u8 D_8006868C[], D_800686AC[], D_8006D730[], D_8006D750[];
extern u8 D_80065174[], D_80065154[];
extern void func_800C591C(u8 *, u8 *, u8 *, s32, s32, s32);
INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80084674);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80084830);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_8008496C);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80084B10);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80084C74);

struct FactoryData {
    s32 words[12];
};
extern FactoryData D_800685CC;

void func_80084E00(u8 *owner, s32 extra) {
    FactoryData config = D_800685CC;
    u8 *allocation = func_8002BE14(0x690);
    if (allocation) {
        func_800C591C((u8 *)func_8002BD80(0x690, allocation), owner,
                        (u8 *)&config, 2, 8, extra);
    }
    func_8007AFCC(owner, allocation);
}


void func_80084EB8(u8 *a0) {
    u8 *s2 = func_80077624(a0);
    u8 *s0 = func_8002BE14(0x48);
    if (s0) {
        func_80085400((u8 *)func_8002BD80(0x48, s0), a0, s2);
    }
    func_8007AFCC(a0, s0);
}

void func_80084F28(u8 *a0) {
    u8 *s3 = func_80077624(a0);
    u8 *s1 = func_8002BE14(0x34);
    if (s1) {
        s32 tmp[4];
        u8 *s0 = (u8 *)func_8002BD80(0x34, s1);
        u8 *p = (u8 *)func_8007767C(a0, tmp);
        func_80085984(s0, a0, p, s3);
    }
    func_8007AFCC(a0, s1);
}


INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80084FB4);

void func_8008510C(u8 *a0) {
    s32 tmp[4];
    u8 *s0;
    func_8007767C(a0, tmp);
    s0 = func_8002BE14(0xDC);
    if (s0) {
        func_80085E30((u8 *)func_8002BD80(0xDC, s0), a0, (u8 *)tmp);
    }
    func_8007AFCC(a0, s0);
}

void func_80085174(u8 *a0) {
    s32 tmp[4];
    u8 *s0;
    func_8007767C(a0, tmp);
    s0 = func_8002BE14(0x54);
    if (s0) {
        func_80086574((u8 *)func_8002BD80(0x54, s0), a0, (u8 *)tmp);
    }
    func_8007AFCC(a0, s0);
}

void func_800851DC(u8 *a0, s32 a1) {
    u32 buf[4];
    u32 info[4];
    s32 value = (s16)a1;
    u8 *s2 = func_80077624(a0);
    u8 *s0;
    func_8007A724(a0, (u8 *)buf, 0x12, D_80068644);
    buf[0] += func_8007A084(a0) << 8;
    info[0] = 0;
    info[1] = 0;
    info[2] = 0;
    info[3] = value;
    s0 = func_8002BE14(0xB8);
    if (s0) {
        func_80086BA0((u8 *)func_8002BD80(0xB8, s0), a0, (u8 *)buf, (u8 *)info, s2);
    }
    func_8007AFCC(a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_8008529C);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80085400);

void func_80085574(u8 *a0, s32 a1) {
    register u8 *s1 asm("$17"); /* PIN $s1: retain the object pointer across both calls. */
    register s32 s0 asm("$16"); /* PIN $s0: retain the option bit across the initializer call. */
    s1 = a0;
    *(u8 **)(s1 + 0x14) = D_8006874C;
    s0 = a1;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_800855C8);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80085768);




}
// Retail owns these vtables; the common base vptr is at object+0x14.
#pragma interface
class CallbackObject {
    s32 fields[5];
public:
    CallbackObject(s32);
    virtual void func0();
    virtual void func1();
    virtual ~CallbackObject();
};
class D : public CallbackObject {
    u8 *f18;
    s16 f1c;
    u8 f1e;
    u8 f1f;
    s16 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
public:
    D(u8 *, s32 *);
    virtual ~D();
};
D::D(u8 *a1, s32 *a2) : CallbackObject(0) {
    register u8 *s1 asm("$17");
    register volatile s32 *s2 asm("$18");
    register s32 word0 asm("$3");
    register s32 word1 asm("$2");
    register s32 word2 asm("$6");
    s1 = a1;
    s2 = a2;
    f20 = func_80077730(s1);
    f18 = s1;
    f1c = 0;
    f1e = 0x80;
    word0 = s2[0];
    word1 = s2[1];
    word2 = s2[2];
    f24 = word0;
    f28 = word1;
    f2c = word2;
    func_800787A0(s1, 0x7A);
}
__asm__(
    ".globl func_80085984\n"
    ".set func_80085984, __1DPUcPi\n"
    ".set __14CallbackObjecti, func_8002BC9C\n"
    ".set _vt.1D, D_80068724"
);
extern "C" {
void func_80085A14(u8 *a0, s32 a1) {
    register u8 *s1 asm("$17"); /* PIN $s1: retain the object pointer across both calls. */
    register s32 s0 asm("$16"); /* PIN $s0: retain the option bit across the initializer call. */
    s1 = a0;
    *(u8 **)(s1 + 0x14) = D_80068724;
    s0 = a1;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}
void func_80085A68(u8 *a0) {
    u8 *s0 = a0;
    u16 count;
    func_8007767C(*(u8 **)(s0 + 0x18), (s32 *)(s0 + 0x24));
    if (*(u16 *)(s0 + 0x1C) >= 0xD) {
        *(u8 *)(s0 + 0x1E) -= 0x10;
    }
    count = *(u16 *)(s0 + 0x1C);
    if (count >= 0x15) {
        if (s0) {
            delete (CallbackObject *)s0;
        }
    } else {
        *(u16 *)(s0 + 0x1C) = count + 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80085AFC);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80085E30);

void func_80085F44(u8 *a0, s32 a1) {
    register u8 *s1 asm("$17"); /* PIN $s1: retain the object pointer across both calls. */
    register s32 s0 asm("$16"); /* PIN $s0: retain the option bit across the initializer call. */
    s1 = a0;
    *(u8 **)(s1 + 0x14) = D_800686FC;
    s0 = a1;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80085F98);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_800861A8);

u8 *func_80086574(u8 *self, u8 *owner, u8 *unused) {
    s32 count;
    s32 scale;
    s16 *values;
    s32 *scales;
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_800686D4;
    *(s16 *)(self + 0x30) = func_80077730(owner);
    *(u8 **)(self + 0x18) = owner;
    *(s16 *)(self + 0x1E) = 0;
    *(s16 *)(self + 0x32) = 0;
    *(u8 *)(self + 0x1C) = 0x80;
    scale = 0x2800;
    values = (s16 *)(self + 0x20);
    scales = (s32 *)(self + 0x34);
    count = 7;
    do {
        *scales = scale;
        *values++ = 0;
        scales++;
    } while (--count >= 0);
    return self;
}

void func_80086600(u8 *a0, s32 a1) {
    register u8 *s1 asm("$17"); /* PIN $s1: retain the object pointer across both calls. */
    register s32 s0 asm("$16"); /* PIN $s0: retain the option bit across the initializer call. */
    s1 = a0;
    *(u8 **)(s1 + 0x14) = D_800686D4;
    s0 = a1;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80086654);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_800867E4);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80086BA0);

void func_80086D34(u8 *self, s32 flags) {
    u8 *object = self;
    s32 deletionFlags = flags;
    u8 *link;
    u8 *next;
    u8 *previous;
    *(u8 **)(object + 0x18) = D_8006868C;
    *(u8 **)(object + 0x14) = D_800686AC;
    *(u8 **)(object + 0x68) = D_80065174;
    link = object + 0x38;
    next = *(u8 **)(object + 0x38);
    previous = *(u8 **)(object + 0x3C);
    *(u8 **)(next + 4) = previous;
    next = *(u8 **)(link + 4);
    *(u8 **)(next + 0) = *(u8 **)(object + 0x38);
    *(u8 **)(object + 0x38) = link;
    *(u8 **)(object + 0x3C) = link;
    *(u8 **)(object + 0x18) = D_80065154;
    func_8002BCEC(object, 0);
    if (deletionFlags & 1) {
        func_8002BDA8(object);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80086DD4);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80086F64);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_800870FC);

u8 *func_800873A4(u8 *self) {
    func_80076FD8(self);
    *(u8 **)(self + 0x14) = D_800689E4;
    func_80079D98(self, D_8006893C);
    *(s32 *)(self + 0x4A4) = 0;
    return self;
}

void func_800873EC(u8 *a0) {
    func_80079DA0(a0, 0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_8008740C);

void func_8008755C(u8 *a0, s32 a1) {
    func_8007BCA0(a0, a1);
    func_80079D58(a0);
    switch (a1) {
    case 0:
        func_80078754(a0, 0x85);
        func_80079DA0(a0, 1);
        break;
    case 0xE:
        func_800787A0(a0, 0x82);
        func_80079DA0(a0, 0);
        func_800876B4(a0);
        break;
    }
}

void func_800875EC(u8 *a0, s32 a1) {
    register u8 *s0 asm("$16");
    register s32 s1 asm("$17");
    register s32 v0 asm("$2");
    s0 = a0;
    s1 = a1;
    func_8007BEC0(s0, s1);
    func_80079D58(s0);
    switch (s1) {
    case 0:
        func_80078754(s0, 0x85);
        func_80079DA0(s0, 1);
        break;
    case 14:
        func_800787A0(s0, 0x82);
        func_80079DA0(s0, 0);
        func_800876B4(s0);
        break;
    }
    v0 = s1 < 15;
    if (v0) {
        *(s32 *)(s0 + 0x3B4) -= *(s32 *)(s0 + 0x3A4) >> 4;
        if (*(s32 *)(s0 + 0x3A8) > 0) {
            *(s32 *)(s0 + 0x3B8) -= *(s32 *)(s0 + 0x3A8);
        }
    }
}

void func_800876B4(u8 *a0) {
    register s32 v1 asm("$3"); /* PIN $v1: hold the adjusted scratch value through the adjacent call. */
    s32 tmp[4];
    u32 area[3];
    u8 *s0;
    func_8007767C(a0, tmp);
    v1 = tmp[1];
    v1 -= 0xC0;
    tmp[1] = v1;
    area[0] = func_8007A084(a0) * 96;
    area[1] = 0;
    area[2] = 0;
    s0 = func_8002BE14(0xC0);
    if (s0) {
        func_80087944((u8 *)func_8002BD80(0xC0, s0), a0, (u8 *)tmp, (u8 *)area);
    }
    func_8007AFCC(a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_8008774C);

void func_800878E8(u8 *a0) {
    u8 *s0 = func_8002BE14(0x54);
    if (s0) {
        func_80087B30((u8 *)func_8002BD80(0x54, s0), a0);
    }
    func_8007AFCC(a0, s0);
}

u8 *func_80087944(u8 *self, u8 *owner, u8 *position, u8 *vector) {
    func_800C72C0(self, owner, (s32 *)position, (s32 *)vector, 0x60, 0x06A81E00, 0x900, 3);
    *(u8 **)(self + 0x18) = D_8006899C;
    *(u8 **)(self + 0x14) = D_800689BC;
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_800879A8);

u8 *func_80087B30(u8 *self, u8 *owner) {
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_80068974;
    *(u8 **)(self + 0x18) = owner;
    *(s32 *)(self + 0x1C) = 0x1000;
    *(s32 *)(self + 0x24) = 0x1000;
    *(s32 *)(self + 0x2C) = 0x1000;
    *(s32 *)(self + 0x20) = 0;
    *(s32 *)(self + 0x28) = 0;
    *(s32 *)(self + 0x30) = 0;
    *(s32 *)(self + 0x34) = 0;
    *(s32 *)(self + 0x38) = 0;
    *(s32 *)(self + 0x3C) = 0;
    *(s32 *)(self + 0x40) = 0;
    *(s32 *)(self + 0x44) = 0x80;
    *(s32 *)(self + 0x48) = 0;
    *(s32 *)(self + 0x4C) = 0;
    *(s32 *)(self + 0x50) = func_80077730(owner);
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80087BC0);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80087F10);

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_800880C8);

void func_80088178(u8 *a0) {
    u8 *s0 = a0;
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");
    func_80024340(s0 + 0x18, 0xB0);
    v0 = 0x280;
    v1 = *(s32 *)(s0 + 0x38);
    v0 -= v1;
    v0 >>= 3;
    v1 += v0;
    *(s32 *)(s0 + 0x38) = v1;
    *(s32 *)(s0 + 0x3C) -= 0x10;
    if (*(s32 *)(s0 + 0x3C) <= 0 && s0 != 0) {
        delete (CallbackObject *)s0;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_800881F0);

void func_80088348(u8 *a0, s32 a1) {
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80088390(u8 *self, s32 flags) {
    u8 *object = self;
    s32 deletionFlags = flags;
    u8 *link;
    u8 *next;
    u8 *previous;
    *(u8 **)(object + 0x18) = D_8006D730;
    *(u8 **)(object + 0x14) = D_8006D750;
    *(u8 **)(object + 0x68) = D_80065174;
    link = object + 0x38;
    next = *(u8 **)(object + 0x38);
    previous = *(u8 **)(object + 0x3C);
    *(u8 **)(next + 4) = previous;
    next = *(u8 **)(link + 4);
    *(u8 **)(next + 0) = *(u8 **)(object + 0x38);
    *(u8 **)(object + 0x38) = link;
    *(u8 **)(object + 0x3C) = link;
    *(u8 **)(object + 0x18) = D_80065154;
    func_8002BCEC(object, 0);
    if (deletionFlags & 1) {
        func_8002BDA8(object);
    }
}

void func_80088430(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80088478(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

u8 *func_800884C0(u8 *a0) {
    register u8 *v1 asm("$3"); /* $v1 keeps the vtable address live across the initializer call. */
    func_80076FD8(a0);
    v1 = D_80068C2C;
    *(u8 **)(a0 + 0x14) = v1;
    func_80079D98(a0, D_80068B5C);
    return a0;
}

void func_80088504(u8 *a0, s32 a1) {
    register u8 *s1 asm("$17"); /* PIN $s1: retain the object pointer across both calls. */
    register s32 s0 asm("$16"); /* PIN $s0: retain the option bit across the initializer call. */
    s1 = a0;
    *(u8 **)(s1 + 0x14) = D_80068C2C;
    s0 = a1;
    func_80077774(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_80088558(u8 *a0, s32 a1) {
    func_8007B9E4(a0, a1);
    if ((u32)(a1 - 1) < 4) {
        func_800785BC(a0, func_8007A084(a0) * 9100);
    }
}

void func_800885C4(u8 *a0, s32 a1) {
    func_8007BA5C(a0, a1);
    if ((u32)(a1 - 0x10) < 4) {
        func_800785BC(a0, func_8007A084(a0) * 18200);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/202B4", func_80088630);

}
