#include "game_audio_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_input.h"
#include "render_context.h"
#include "game_loading_screen.h"
#pragma interface

struct Node {
    Node *next;
    Node *prev;
};

class D1640 {
public:
    Node link;
    int f8;
    int fC;
    int f10;
    virtual ~D1640();
};

class D1AFC {
public:
    Node link;
    int f8;
    int fC;
    int f10;
    virtual ~D1AFC();
};

extern "C" {
extern void func_8001BEDC(u8 *);
extern u8 D_8006E13C[];
extern u8 D_8006DD5C[];
extern void func_8002BCEC(u8 *, s32);
extern void func_8002BDA8(u8 *);
extern s32 func_80077618(u8 *);
extern void func_80077498(u8 *, s32);
extern void func_800CE270(u8 *);
extern void func_8006ED08(s32);
extern s32 func_8002AFFC(s32, s32, s32);
extern void func_8005844C(s32, s32);
extern u8 D_8006E114[];
extern u8 D_8006E0EC[];
extern RenderContext *D_800641A4;
extern void func_8001F278(RenderContext *, s32, s32, s32);
extern void func_8006F23C(u8 *, s32);
extern u8 *func_80028050(void);
extern s32 D_8005F820;
extern s32 D_80114210;
extern s32 func_800700B0(u8 *, s32);
extern s32 func_8007760C(s32);

extern void func_80079AA4(s32, s32, s32, s32, s32);
extern s16 D_8006DF44[];
extern u8 D_8005F824[];

extern void func_800794C8(s32);
extern s32 func_8002BD88(s32);
extern s32 func_800CBA6C(s32, s32, s32);
extern s32 func_8006F09C(u8 *, s32);
extern s32 func_8002BD74(s32);
extern void func_80073318(u8 *);
extern void func_80073340(u8 *);


INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CDB7C);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CDCD4);

void func_800CDE2C(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006DD5C;
    func_800CE270(a0);
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CDE88);

void func_800CE1C8(u8 *self) {
    if (func_80027004(D_80114210, *(s32 *)(self + 0x18)) & 0x8F0) {
        s32 enabled;
        func_800CE270(self);
        enabled = *(s32 *)(self + 0x20);
        *(s32 *)(self + 0x38) = 0xF2;
        *(s32 *)(self + 0x3C) = 0;
        *(s32 *)(self + 0x40) = 0;
        *(s32 *)(self + 0x44) = 0xE8;
        *(s32 *)(self + 0x48) = 0xC5;
        if (enabled) {
            *(s16 *)(self + 0x4C) = 0x40;
            *(s16 *)(self + 0x4E) = 0x94;
            *(s16 *)(self + 0x50) = 0x60;
            *(s16 *)(self + 0x52) = 0x18;
        }
        *(s32 *)(self + 0x54) = 0xA;
        *(s32 *)(self + 0x58) = 0x80;
        *(s32 *)(self + 0x5C) = 7;
    }
}

void func_800CE270(u8 *arg0) {
    s32 i;
    u8 *p;
    p = arg0 + 0x28;
    for (i = 2; i >= 0; i--) {
        *(s32 *)(arg0 + 0x34) += *(s32 *)p;
        *(s32 *)p = 0;
        p += 4;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CE2A0);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CE4F4);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CE63C);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CECF4);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CEDC0);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CEFC4);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CF190);

void func_800CF354(u8 *arg0, u32 *arg1, u32 *arg2) {
    register u32 field0 asm("$4"); /* PIN $a0: descriptor constant/data */
    register u32 field1 asm("$5"); /* PIN $a1: descriptor data then pointer */
    register u32 field2 asm("$3"); /* PIN $v1: descriptor color byte */
    u8 *p = func_80028050();

    field0 = 0x00808080;
    field2 = *(volatile u8 *)(p + 7);
    *(volatile u32 *)(p + 4) = (field2 << 24) | field0;
    field0 = arg1[0];
    field2 = *(volatile u8 *)(p + 7);
    *(volatile u32 *)(p + 8) = field0;
    field1 = arg2[0];
    field2 |= 2;
    *(volatile u32 *)(p + 0xC) = field1;
    field0 = arg1[1];
    *(volatile u8 *)(p + 7) = field2;
    *(volatile u32 *)(p + 0x10) = field0;
    field1 = (u32)p;
    func_8005844C((s32)arg0, (s32)field1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CF3D8);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CF558);

s32 func_800CF714(u8 character) {
    s32 code = character;
    u32 high;
    u32 low;
    if ((u8)(code - 'A') < 26) {
        code = (u8)(code - 'A');
        high = (code << 2) & 0xE0;
        low = (code << 5) & 0xFF;
    } else if ((u32)(code - '0') < 11) {
        code = (u8)(code - '.');
        high = (((code & 0xF8) << 2) + 0x60) & 0xFF;
        low = (code << 5) & 0xFF;
    } else {
        switch (code) {
        case '!': low = 0xA0; high = 0x80; break;
        case '?': low = 0xC0; high = 0x80; break;
        case '_': low = 0xE0; high = 0x80; break;
        default: return -1;
        }
    }
    return (high << 8) | low;
}

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CF7DC);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CF9A4);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CFC48);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CFDF0);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800CFFC4);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D00FC);

void func_800D0268(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D02B0(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D02F8(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D0340(s32 arg0) {
    func_8005844C(arg0, func_8002AFFC(0, 0, 0x1E));
}

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D037C);

void func_800D04B8(u8 *arg0) {
    GameLoadingScreenWithCaption *self = (GameLoadingScreenWithCaption *)arg0;
    u8 *p;

    if (self->captionVisible != 0) {
        p = func_80028050();
        *(u32 *)(p + 4) = (p[7] << 24) | 0x01808080;
        *(u32 *)(p + 8) = 0x00100008;
        *(u32 *)(p + 0xC) = 0x1F7B40A0;
        *(u32 *)(p + 0x10) = 0x00200038;
        func_8005844C(D_8005F820 - 4, (s32)p);
    }
    func_8001ED7C(arg0);
}

s32 func_800D0548(s32 a0) {
    register u32 address asm("$3"); /* PIN $v1: keep the address out of the return register. */
    func_8001EC08((GameLoadingScreen *)(u32)a0);
    address = (u32)&D_8006DF24;
    *(u32 *)(a0 + 0x10) = address;
    return a0;
}

s32 func_800D057C(s32 a0) {
    register u32 address asm("$3"); /* PIN $v1: keep the address out of the return register. */
    func_8006ED08(a0);
    address = (u32)D_8006E13C;
    *(u32 *)(a0 + 0xD34) = address;
    return a0;
}

void func_800D05B0(u8 *arg0, s32 arg1) {
    RenderContext **table = &D_800641A4;
    u8 *vtable = D_8006E13C;
    RenderContext *state = *table;

    *(u8 **)(arg0 + 0xD34) = vtable;
    func_8001F278(state, 0, 0, 0);
    func_8001BEDC(*(u8 **)(arg0 + 0xDA4));
    func_8006F23C(arg0, arg1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D0618);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D07B8);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D0984);

void func_800D0AB0(u8 *arg0) {
    func_8001BEDC(*(u8 **)(arg0 + 0xDA4));
}

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D0AD4);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D0C5C);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D0D8C);

void func_800D0E50(u8 *self) {
    s32 first;
    s32 second;
    s32 allocated;
    s32 constructed;
    func_8001BE78((s32)(u32)D_8005F824, 0x8009, 0);
    func_8001BE78((s32)(u32)D_8005F824, 0x42, 0);
    first = func_800700B0(self, 0);
    second = func_800700B0(self, 1);
    func_800794C8(first);
    func_800794C8(second);
    allocated = func_8002BD88(0x59C);
    constructed = func_800CBA6C(allocated, 9, 0);
    *(s32 *)(self + 0xDA0) = func_8002BD74(func_8006F09C(self, constructed));
    func_80073318(self);
    func_80073340(self);
    *(s16 *)(self + 0xD9C) = 2;
}

void func_800D0F20(u8 *arg0, s32 arg1) {
    register s32 i asm("$5") = (s16)arg1; /* PIN $a1: signed index */
    register u8 *p asm("$6"); /* PIN $a2: table element pointer */
    register s32 temp asm("$2"); /* PIN $v0: scaled index and stride */
    register s32 count asm("$3"); /* PIN $v1: indexed value/address */

    p = arg0 + 0xF38;
    temp = i * 2;
    p += temp;
    temp = i * 20;
    count = *(s16 *)p;
    count = count * 2 + temp;
    arg0 += count;
    i = 1;
    *(s16 *)(arg0 + 0xF3C) = i;
    *(u16 *)p = *(u16 *)p + 1;
}

void func_800D0F6C(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *s0;
    u8 *s1;
    s32 s2;
    s0 = arg0;
    s1 = arg1;
    s2 = arg2 & 0xFFFF;
    s0 = s0 + ((func_80077618(s1) & 0xFFFF) * 2);
    func_80077498(s1, *(u16 *)(s0 + 0xF64) + s2);
}

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D0FC8);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D11EC);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D124C);

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D13DC);

s32 func_800D15F8(s32 arg0, s32 arg1) {
    func_8002BC9C((u8 *)(u32)arg0, 0);
    *(s32 *)(arg0 + 0x18) = arg1;
    *(s32 *)(arg0 + 0x14) = (s32)D_8006E114;
    return arg0;
}

}
D1640::~D1640() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_800D1640\n"
    ".set func_800D1640, _._5D1640\n"
    ".set _vt.5D1640, D_8006E114\n"
    ".set __builtin_delete, func_8002BDA8"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D1694);

s32 func_800D1AB4(s32 arg0, s32 arg1) {
    func_8002BC9C((u8 *)(u32)arg0, 0);
    *(s32 *)(arg0 + 0x18) = arg1;
    *(s32 *)(arg0 + 0x14) = (s32)D_8006E0EC;
    return arg0;
}

}
D1AFC::~D1AFC() {
    func_8002BCEC((u8 *)this, 0);
}
__asm__(
    ".globl func_800D1AFC\n"
    ".set func_800D1AFC, _._5D1AFC\n"
    ".set _vt.5D1AFC, D_8006E0EC"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/697BC", func_800D1B50);
}
