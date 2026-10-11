#include "game_action_api.h"
#include "game_placement_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_actor_queries.h"
#pragma interface
class Bx {
    s32 fields[5];
public:
    virtual ~Bx();
};
class Cx {
    s32 fields[5];
public:
    virtual ~Cx();
};
class Dx {
    s32 fields[5];
public:
    virtual ~Dx();
};
class Ex {
    s32 fields[5];
public:
    virtual ~Ex();
};
__asm__(".set __builtin_delete, func_8002BDA8");
extern "C" {
extern long long func_80076FD8(void *);
extern void func_80079D98(u8 *, s32);
extern void func_80077774(u8 *, s32);
extern s32 func_800BD748(s32, ...);
extern s32 func_80077768(u8 *);
extern s32 func_80077730(u8 *);
extern s32 func_80075154(u8 *);

extern u8 D_8006A964;

extern u8 D_8006AA54;

extern u8 D_8006A79C;
extern u8 D_8006A9E4;



extern u8 D_8006D58C;

extern u8 D_80010874;
extern u8 D_80010884;

extern u8 D_8006A754;
extern u8 D_8006A774;
extern u8 D_8006A7EC;

extern s32 func_8007760C(u8 *);
extern s32 func_8007763C(u8 *);
extern void func_80079DA0(u8 *, s32);
extern void func_80079AA4(u8 *, s32, s32, s32, s32);
extern void func_8007AFCC(u8 *, u8 *);
extern void func_80079580(s32);
extern s32 func_8007A008(u8 *);
extern s32 func_8007A04C(u8 *);
extern s32 func_8007A0C4(u8 *, u8 *, s32, s32);
extern void func_8002BCEC(u8 *, s32);
extern void func_8002BDA8(u8 *);
extern u8 *func_8002BE14(s32);
extern void func_8002BF34(u8 *, u8 *);
extern void func_800C38F0(s32, s32, s32, s32, s32, s32);
extern void func_800C6588(u8 *, s32, u8 *, s32, s32, s32, s32);
extern s32 func_8007A084(u8 *);

extern u8 *func_800A2128(u8 *, u8 *, s32 *, s32 *, u8 *);
extern s32 func_800787A0(u8 *, s32);
extern void func_80079D80(u8 *, s32);
extern s32 func_8007953C(u8 *);

extern void func_800A1C20(s32);
extern s32 func_800A3A0C(s32);
extern s32 func_800A3AAC(s32);
extern u8 *func_800A4AAC(u8 *, u8 *);
extern void func_800A1418(s32, s32 *, s32 *, s32, s32 *);

}
Cx::~Cx() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_800A11B0\n"
    ".set func_800A11B0, _._2Cx\n"
    ".set _vt.2Cx, D_8006D58C"
);

Dx::~Dx() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_800A1204\n"
    ".set func_800A1204, _._2Dx\n"
    ".set _vt.2Dx, D_8006D58C"
);

Ex::~Ex() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_800A1258\n"
    ".set func_800A1258, _._2Ex\n"
    ".set _vt.2Ex, D_8006D58C"
);
extern "C" {

s32 func_800A12AC(s32 a0) {
    func_80076FD8((void *)a0);
    *(u32 *)(a0 + 0x14) = (u32)&D_8006A7EC;
    func_80079D98((u8 *)a0, (u32)&D_8006A754);
    *(s32 *)(a0 + 0x4A4) = 0;
    return a0;
}

void func_800A12F4(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_8006A7EC;
    func_80077774((u8 *)a0, 0);
    if (a1 & 1) {
        func_8002BDA8((u8 *)a0);
    }
}

void func_800A1348(void) {
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A1350);

void func_800A1418(s32 a0, s32 *a1, s32 *a2, s32 a3, s32 *a4) {
    a4[0] = a1[0] + (((a2[0] - a1[0]) * a3) >> 12);
    a4[1] = a1[1] + (((a2[1] - a1[1]) * a3) >> 12);
}

void func_800A1468(s32 a0) {
    s32 v0;
    if (*(s32 *)(a0 + 0x4B8) < 0) {
        *(s32 *)(a0 + 0x4B8) = 0;
    }
    v0 = *(s32 *)(a0 + 0x4B8);
    if (v0 >= 0x1001) {
        *(s32 *)(a0 + 0x4B8) = 0x1000;
    }
    func_800A1418(a0, (s32 *)(a0 + 0x4CC), (s32 *)(a0 + 0x4DC), *(s32 *)(a0 + 0x4B8), (s32 *)(a0 + 0x3C8));
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A14C8);

void func_800A1A18(s32 a0, u8 *a1) {
    s32 first[4];
    s32 second[4];
    if (*(s32 *)(a0 + 0x4B8) < 0) {
        *(s32 *)(a0 + 0x4B8) = 0;
    }
    if (*(s32 *)(a0 + 0x4B8) >= 0x1001) {
        *(s32 *)(a0 + 0x4B8) = 0x1000;
    }
    func_8007767C(a1, first);
    func_800A1418(a0, (s32 *)(a0 + 0x4CC), (s32 *)(a0 + 0x4DC), *(s32 *)(a0 + 0x4B8), second);
    *(s32 *)(a1 + 0x3BC) = 0;
    *(s32 *)(a1 + 0x3A4) = 0;
    *(s32 *)(a1 + 0x3A8) = 0;
    *(s32 *)(a1 + 0x3AC) = 0;
    *(s32 *)(a1 + 0x3B0) = 0;
    *(s32 *)(a1 + 0x3B4) = (second[0] - first[0]) << 8;
    *(s32 *)(a1 + 0x3B8) = (second[1] - first[1]) << 8;
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A1AD0);

void func_800A1B5C(s32 a0, s32 a1) {
    s32 v1;
    s32 v0;
    if (a1 == 0) {
        if (*(s32 *)(a0 + 0x4A4) != 0) {
            func_80079580(a0);
            return;
        }
        func_80078754((u8 *)a0, 0xC9);
        v1 = -1;
        func_80079AA4((u8 *)a0, 0x17, 2, 0, v1);
    }
    if (a1 == 3) {
        func_800A1C20(a0);
    }
    if (a1 < 0x11) {
        v1 = *(s32 *)(a0 + 0x3A4);
        v0 = *(s32 *)(a0 + 0x3B4);
        v1 = v1 >> 4;
        v0 = v0 - v1;
        *(s32 *)(a0 + 0x3B4) = v0;
        if (*(s32 *)(a0 + 0x3A8) > 0) {
            v0 = *(s32 *)(a0 + 0x3B8);
            v0 = v0 - *(s32 *)(a0 + 0x3A8);
            *(s32 *)(a0 + 0x3B8) = v0;
        }
    }
}

void func_800A1C20(s32 a0) {
    u8 *s1 = (u8 *)a0;
    s32 value;
    u8 *allocation;
    u8 *s2;
    s32 sp18[4];
    s32 sp28[3];
    value = func_8007A084(s1);
    func_8007767C(s1, sp18);
    sp28[0] = (value * 3) << 5;
    sp28[1] = 0;
    sp28[2] = 0;
    sp18[0] += value << 6;
    sp18[1] -= 0x60;
    s2 = func_80077624(s1);
    allocation = func_8002BE14(0xC8);
    if (allocation != 0) {
        func_800A2128((u8 *)func_8002BD80(0xC8, allocation), s1, sp18, sp28, s2);
    }
    func_8007AFCC(s1, allocation);
    func_800787A0(s1, 0xC6);
    func_80079D80(s1, 0x28);
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A1CFC);

s32 func_800A1F94(s32 a0) {
    s32 s0;
    s32 s1;
    s0 = (s32)func_8007B16C((u8 *)a0);
    if (func_8007A008((u8 *)s0) == 0) {
        return 0;
    }
    s0 = func_8007A04C((u8 *)a0) + func_8007A04C((u8 *)s0);
    s0 = s0 + 0xA0;
    s1 = s0 * s0;
    s0 = func_8007A0C4((u8 *)a0, &D_80010884, s1, 0x200);
    if (s0 != 0) {
        return s0;
    }
    return func_8007A0C4((u8 *)a0, &D_80010874, s1, 0x200);
}

s32 func_800A203C(s32 a0) {
    s32 v0;
    s32 v1;
    v1 = func_8007760C((u8 *)func_8007B16C((u8 *)a0));
    switch (v1) {
    case 0xB:
        v0 = 0x3FFC;
        break;
    case 0xC:
    case 0xF:
    case 0x14:
        v0 = 0x4718;
        break;
    default:
        v0 = 0x4E34;
        break;
    }
    return v0;
}

void func_800A20B4(s32 a0) {
    u8 *s1;
    u8 *s0;
    s1 = func_8002BE14(0x120);
    if (s1 != 0) {
        s0 = (u8 *)func_8002BD80(0x120, s1);
        func_800BD748((s32)s0, (u8 *)a0);
        *(u32 *)(s0 + 0x14) = (u32)&D_8006A774;
    }
    func_8007AFCC((u8 *)a0, s1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A2128);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A22AC);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A2354);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A24FC);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A29B8);

}
Bx::~Bx() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_800A2A50\n"
    ".set func_800A2A50, _._2Bx\n"
    ".set _vt.2Bx, D_8006A79C"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A2AA4);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A2B28);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A2F28);

void func_800A31D4(s32 a0, s32 a1) {
    func_8002BCEC((u8 *)a0, 0);
    if (a1 & 1) {
        func_8002BDA8((u8 *)a0);
    }
}

s32 func_800A321C(s32 a0) {
    func_800BD748(a0);
    *(u32 *)(a0 + 0x14) = (u32)&D_8006A774;
    return a0;
}

s32 func_800A3250(s32 a0) {
    func_80076FD8((void *)a0);
    *(u32 *)(a0 + 0x14) = (u32)&D_8006AA54;
    *(s32 *)(a0 + 0x4AC) = 0;
    func_80079D98((u8 *)a0, (u32)&D_8006A964);
    *(s32 *)(a0 + 0x4A4) = 0;
    *(s32 *)(a0 + 0x4A8) = 0;
    *(s32 *)(a0 + 0x4B0) = 0;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A32A4);

void func_800A33F4(s32 a0) {
    func_80079DA0((u8 *)a0, 0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A3414);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A35BC);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A3774);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A3880);

void func_800A39C8(s32 a0) {
    if (func_8007763C((u8 *)a0) == 0) {
        func_800A3A0C(a0);
    } else {
        func_800A3AAC(a0);
    }
}

/* PINS: $s1=object, $s0=flags, $v1=helper result/mask, $a0=branch result. */

s32 func_800A3A0C(s32 a0) {
    register s32 s1 asm("$17") = a0;
    register s32 s0 asm("$16");
    register s32 value asm("$3");
    register s32 result asm("$4");
    s0 = func_80075154((u8 *)func_80077768((u8 *)s1));
    if (s0 & 0x1000) {
        value = func_8007953C((u8 *)s1);
        result = 0;
        if (value != 0x1E) {
            result = -0x200;
        }
        return result;
    }
    if (s0 & 0x4000) {
        return 0x200;
    }
    value = func_8007A084((u8 *)s1);
    if (value > 0 && (s0 & 0x2000)) {
        return 0;
    }
    if (value >= 0) {
        return -1;
    }
    value = s0 & 0x8000;
    if (value) {
        return 0;
    }
    return -1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A3AAC);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A3B90);

void func_800A3CF8(s32 a0) {
    u8 *s0;
    s0 = func_8002BE14(0x44);
    if (s0) {
        func_800A4AAC((u8 *)func_8002BD80(0x44, s0), (u8 *)a0);
    }
    func_8007AFCC((u8 *)a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A3D54);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A3F50);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A40E8);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A4268);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A4704);

void func_800A4808(s32 a0) {
    u8 *s0;
    s0 = func_8002BE14(0x5C);
    if (s0) {
        func_800C38F0((s32)(u32)func_8002BD80(0x5C, s0), a0 + 0x84, a0 + 0xA4, 0x10, 0x408080, 9);
    }
    func_8002BF34((u8 *)a0, s0);
}

void func_800A4880(s32 a0) {
    u8 *s1 = (u8 *)a0;
    u8 *s0 = func_8002BE14(0x3C);
    if (s0 != 0) {
        u8 *buffer = (u8 *)func_8002BD80(0x3C, s0);
        func_800C6588(buffer, 9, s1 + 0x84, 0x20, 0x10, 8, 0x408080);
    }
    func_8002BF34(s1, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A4900);

u8 *func_800A4AAC(u8 *self, u8 *owner) {
    s32 position[3];
    s32 direction;
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = &D_8006A9E4;
    direction = func_8007A084(owner);
    func_8007767C(owner, position);
    *(u8 **)(self + 0x18) = owner;
    *(s32 *)(self + 0x2C) = 0;
    *(s32 *)(self + 0x30) = 0x80;
    *(s32 *)(self + 0x34) = direction;
    *(s32 *)(self + 0x38) = 0;
    *(s32 *)(self + 0x3C) = 0;
    *(s32 *)(self + 0x1C) = position[0];
    *(s32 *)(self + 0x20) = position[1];
    *(s32 *)(self + 0x24) = position[2];
    *(s32 *)(self + 0x40) = func_80077730(owner);
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A4B50);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A4CC0);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A4EBC);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A4FC8);

INCLUDE_ASM("asm/us/game/nonmatchings/3CDF0", func_800A50D4);
}
