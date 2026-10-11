#include "game_lerp_words.h"
#include "game_audio_api.h"
#include "common.h"
#include "game_input.h"
#include "game_resources.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
extern "C" {

extern u8 D_8005F8B8[];
extern u8 D_80065C20[];
extern u8 D_80065BF8[];
extern s32 D_80114210;
extern void func_8002C244(u8 *);
extern void func_8002BCEC(u8 *, s32);
extern void func_8002BDA8(u8 *);
extern s32 D_8005FB70;
extern u8 D_8005F824[];
extern void func_80075424(u8 *);
extern s32 func_800755D4(u8 *);

extern void func_80075898(u8 *);
extern void func_800759D4(u8 *);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80072A6C);

void func_80072B4C(u8 *arg0) {
    S32(arg0, 0x80) += 5 * S32(arg0, 0x74);
    U16(arg0, 0x720) -= 8;
    if ((s16)U16(arg0, 0x720) < 0) {
        U16(arg0, 0x720) = 0;
    }
    if (S32(arg0, 0x80) > 0x8000) {
        S32(arg0, 0x80) = 0x8000;
    }
    S32(arg0, 0x7C) += 0x12;
    if (S32(arg0, 0x7C) >= 0x100) {
        S32(arg0, 0x7C) = 0xFF;
    }
    S32(arg0, 0x74) += 1;
    if (S32(arg0, 0x74) >= 0x3D) {
        S32(arg0, 0x1128) += 1;
    }
}

void func_80072BF0(u8 *arg0) {
    func_80039354(0x44);
    S32(arg0, 0x1128) += 1;
}

void func_80072C24(u8 *arg0) {
    func_8001EAB4(((u8 *)&D_8005F884), S32(arg0, 0x6C) != 0 ? 0x40 : 0x80);
    S32(arg0, 0x1128) = -1;
}

void func_80072C70(void) {
}

void func_80072C78(void) {
}

void func_80072C80(void) {
}

void func_80072C88(void) {
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80072C90);

extern void func_8007236C(void);
extern void func_80073154(s32);
extern void func_80072E08(s32);

void func_80072DD4(s32 arg0) {
    func_8007236C();
    func_80073154(arg0);
    func_80072E08(arg0);
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80072E08);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80073154);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80073438);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_8007361C);

void func_8007374C(u8 *arg0) {
    s32 v = D_80114210;
    v = func_80027004(v, 0) | func_80027004(v, 1);
    v &= 0x820;
    if (v != 0) {
        func_8002C244(arg0 + 0x50);
        S32(arg0, 0x7C) = 0xFF;
        S32(arg0, 0x80) = 0x1000;
        S32(arg0, 0x88) = 0x50;
        S32(arg0, 0x1128) = 2;
        U16(arg0, 0x1138) = 0;
        U16(arg0, 0x724) = 0;
        U16(arg0, 0x726) = 0;
    }
}

void func_800737DC(u8 *arg0) {
    s32 v = D_80114210;
    v = func_80027004(v, 0) | func_80027004(v, 1);
    v &= 0x800;
    if (v != 0) {
        S32(arg0, 0x6C) = 1;
        S32(arg0, 0x84) = 0;
        S32(arg0, 0x1128) = 3;
        S32(arg0, 0x74) = 0;
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_8007384C);

void func_800738F4(u8 *arg0, s32 arg1) {
    S32(arg0, 0x14) = (s32)D_80065C20;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

/* Pins preserve the retail register map: x=$v0, y=$a3, dx=$v1, z=$a0, dy=$a1. */
void func_80073948(u8 *arg0) {
    register s32 x asm("$2") = S32(arg0, 0x1C);
    register s32 y asm("$7") = S32(arg0, 0x20);
    register s32 dx asm("$3") = *(volatile s32 *)(arg0 + 0x2C);
    register s32 z asm("$4") = *(volatile s32 *)(arg0 + 0x24);
    register s32 dy asm("$5") = S32(arg0, 0x30);

    x += dx;
    y += dy;
    *(volatile s32 *)(arg0 + 0x1C) = x;
    if (x < 0) {
        x = -x;
    }
    z += S32(arg0, 0x34);
    S32(arg0, 0x20) = y;
    S32(arg0, 0x24) = z;
    if (x <= 0x400) {
        register s32 absY asm("$2");

        absY = y < 0 ? -y : y;
        if (absY <= 0x400) {
            return;
        }
    }
    if (arg0 != 0) {
        u8 *vtable = (u8 *)S32(arg0, 0x14);
        ((void (*)(u8 *, s32))U32(vtable, 0x1C))(arg0 + S16(vtable, 0x18), 3);
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_800739E4);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80073AFC);

void func_80073BC4(u8 *arg0, s32 arg1) {
    S32(arg0, 0x14) = (s32)D_80065BF8;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_80073C18(u8 *arg0) {
    S32(arg0, 0x48) += S32(arg0, 0x44);
    if (S32(arg0, 0x48) < 0x200) {
        U16(arg0, 0x3E) += 1;
        if ((s16)U16(arg0, 0x3E) >= 0x81) {
            U16(arg0, 0x3E) = 0x80;
        }
    } else {
        S16(arg0, 0x3E) = U16(arg0, 0x3E) + ((0x80 - S16(arg0, 0x3E)) >> 2);
    }
    if (S32(arg0, 0x48) >= 0x401) {
        if (arg0 != 0) {
            u8 *vt = (u8 *)S32(arg0, 0x14);
            ((void (*)(u8 *, s32))U32(vt, 0x1C))(arg0 + (s16)U16(vt, 0x18), 3);
        }
    } else {
        U16(arg0, 0x3C) += 1;
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80073CEC);

void func_80073F54(s32 a0, s32 a1) {
    u32 table = *(u32 *)((u32)a0 + 0x1Cu);
    *(u32 *)((u32)a0 + 0x20u) = (u32)a1;
    (*(void (**)(s32, s32))(table + 0x24u))(
        (s32)((u32)a0 + (u32)(s32)*(s16 *)(table + 0x20u)), a1);
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80073F88);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80074594);


INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_8007466C);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_800749F8);

extern s32 func_80027B98(s32, s32);
extern void func_8005858C(s32);
extern s32 func_8005859C(u8 *);
extern void func_80057F74(s32, s32);

void func_80074B90(s32 arg0, s32 arg1, s32 arg2) {
    s32 s0 = arg1;
    u8 buf[0x18];
    s32 v = func_80027B98(arg0, arg2);

    func_8005858C(v);
    if (func_8005859C(buf) != 0) {
        s32 a = *(s32 *)(buf + 0x10);

        if (a != 0) {
            func_80057F74(s0, a);
        }
        a = *(s32 *)(buf + 8);
        if (a != 0) {
            func_80057F74(s0 + 8, a);
        }
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80074C00);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80074DB4);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80074F78);


INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80075004);


INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_800751A8);

void func_8007530C(s32 *arg0) {
    if (++arg0[0x26] >= 0x20) {
        arg0[0x22] = 1;
        arg0[0x56] = 0;
    }
}

void func_80075338(u8 *arg0) {
    func_80075424(arg0);
    if (D_8005FB70 == 0 && func_800755D4(arg0) != 0) {
        func_8001BE78((s32)(u32)D_8005F824, 0x11, 0);
        S32(arg0, 0x130) = 0;
        S32(arg0, 0x88) = 8;
        return;
    }
    s32 *right = (s32 *)(arg0 + 0xEC);
    s32 *left = (s32 *)(arg0 + 0xE8);
    s32 *value = (s32 *)(arg0 + 0xD0);
    for (s32 i = 1; i >= 0; i--) {
        *value = 0;
        *left = (s32)((u32)*left - 0x10U);
        if (*left < 0) *left = 0;
        *right = (s32)((u32)*right - 0x10U);
        if (*right < 0) *right = 0;
        right += 0x38 / 4;
        left += 0x38 / 4;
        value += 0x38 / 4;
    }
    if ((S32(arg0, 0x130) & 0xC) != 4) {
        func_80075898(arg0);
    } else {
        func_800759D4(arg0);
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80075424);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_800755D4);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_800756D4);


INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_800757E0);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80075898);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_800759D4);

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80075B74);

extern void func_80071CB0(u8 *, volatile s32 *, s32 *);

void func_80075D60(u8 *arg0) {
    s32 v;

    *(u32 *)(arg0 + 0x190) -= 4u;
    *(u32 *)(arg0 + 0x1A0) += 0x30u;
    func_80071CB0(*(u8 **)(arg0 + 0x220), (volatile s32 *)(arg0 + 0x18C), (s32 *)(arg0 + 0x19C));
    v = (s32)(*(u32 *)(arg0 + 0x94) + 8u);
    *(s32 *)(arg0 + 0x94) = v;
    if (v >= 0x380) {
        *(s32 *)(arg0 + 0x88) = 4;
        *(s32 *)(arg0 + 0x190) = 0x1F4;
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80075DD0);

extern s32 D_80114210;
void func_80075EE4(s32 *arg0) {
    if (func_80027004(D_80114210, -1) & 0x40) {
        arg0[0x22] = 8;
    }
}

void func_80075F24(u8 *object) {
    s32 v0;
    S32(object, 0x190) = (s32)((u32)S32(object, 0x190) - 4u);
    S32(object, 0x1A0) = (s32)((u32)S32(object, 0x1A0) + 0x30u);
    func_80071CB0(*(u8 **)(object + 0x220), (volatile s32 *)(object + 0x18C), (s32 *)(object + 0x19C));
    v0 = (s32)((u32)S32(object, 0x94) + 8u);
    S32(object, 0x94) = v0;
    if (v0 >= 0x380) {
        S32(object, 0x88) = 6;
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_80075F8C);

extern void func_80078F68(void);

void func_800760BC(s32 *arg0) {
    func_80078F68();
    if (arg0[0x22] == 1) {
        arg0[0x25] = 0;
    }
}

void func_800760F4(u8 *arg0) {
    func_80039354(0x44);
    S32(arg0, 0x88) = 9;
}

void func_80076124(u8 *arg0) {
    S32(arg0, 0x9C) += 4;
    if (S32(arg0, 0x9C) >= 0x100) {
        S32(arg0, 0x9C) = 0xFF;
        S32(arg0, 0x88) = 0xA;
    }
    S32(arg0, 0x98) = (0xFF - S32(arg0, 0x9C)) >> 3;
}

void func_80076164(u8 *arg0) {
    if (U32(arg0, 0x130) & 4) {
        s32 value = S32(arg0, 0x1AC);
        S32(D_8005F8B8, 0) = value;
        S32(D_8005F8B8, 0x31C) = value;
    }
    if (U32(arg0, 0x130) & 8) {
        s32 value = S32(arg0, 0x1AC);
        S32(D_8005F8B8, 0) = value;
        S32(D_8005F8B8, 0x320) = value;
        S32(D_8005F8B8, 0x50) = S32(arg0, 0x1AC) - 7;
    }
    if ((U32(arg0, 0x130) & 0xC) == 4) {
        u8 *settings = D_8005F8B8;
        S32(settings, 0x338) = S32(arg0, 0xF0);
        S32(settings, 0x350) = S32(arg0, 0x128);
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/E6AC", func_800761FC);

void func_80076E1C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 < 6) {
        s32 base = (arg3 * 0x10 - arg3) * 2;
        U16(arg0, 0) = base + 8;
        if (arg3 >= 3) {
            U16(arg0, 0) = base + 0x62;
        }
        U16(arg0, 2) = 0xB;
    } else if (arg3 < 0xF) {
        s32 b = arg3 - 6;
        U16(arg0, 0) = (b * 0x10 - b) * 2 + 8;
        U16(arg0, 2) = 0x29;
    } else {
        s32 b = arg3 - 0xF;
        U16(arg0, 0) = (b * 0x10 - b) * 2 + 8;
        U16(arg0, 2) = 0x47;
    }
    U16(arg0, 0) += arg1;
    U16(arg0, 2) += arg2;
}
}
