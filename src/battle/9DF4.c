#include "game_thread.h"
#include "game_audio_api.h"
#include "common.h"
#include "object_factory_api.h"
#include "game_handles.h"
#include "game_deferred.h"
#include "game_input.h"
#include "game_random.h"
#include "game_vfs.h"
#include "game_lerp_words.h"
#include "game_loading_screen.h"

extern u8 D_8005F8B8[];
extern u8 D_800643C4[];
extern u8 D_80064414[];
extern u8 D_8005F824[];
void func_8006E2F8(s32, s32);
void func_8006EC8C(u32 completionWord);
extern void func_8003470C(VfsNotificationFn callback, void *user);
extern u8 D_80064FE4[];
extern void func_80077654(u8 *, s32 *);

u8 *func_8006E1B4(u8 *a0, u8 *opaqueContext) {
    func_8002B6D4(a0, 0x2000, D_800643C4);
    *(u8 **)(a0 + 0x1C) = D_80064414;
    func_8001EEF4(a0 + 0x28, func_8006E2F8, 0x2000, a0, 0);
    func_8003470C(func_8006EC8C, 0);
    *(s32 *)(a0 + 0x24) = 0;
    return a0;
}

void func_8006E224(s32 a0, s32 a1) {
    s32 s0;
    *(u8 **)(a0 + 0x1C) = D_80064414;
    func_8003470C(0, 0);
    func_8001BCC4(D_8005F824);
    func_8001BCF8(D_8005F824);
    s0 = *(s32 *)(a0 + 0x24);
    if (s0 != 0) {
        s32 v0 = *(s32 *)(s0 + 0xD34);
        ((void (*)(s32, s32))(*(s32 *)(v0 + 0x6C)))(s0 + *(s16 *)(v0 + 0x68), 3);
    }
    func_8001C1C0();
    func_8001EFB0((GameThread *)(u32)(a0 + 0x28), 2);
    func_8002B770(a0, a1);
}

void func_8006E2D4(s32 a0) {
    func_8001F020((GameThread *)(u32)(a0 + 0x28), 0);
}

void func_8006E2F8(s32 a0, s32 a1) {
    func_8006E318(a1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006E318);

void func_8006E5E8(s32 a0) {
    GameLoadingScreenWithCaption loading;
    s32 i;
    func_8001EC08(&loading.base);
    loading.base.vtable = &D_8006DF24;
    for (i = 2; i >= 0; i--) {
        func_8001EC24(&loading.base);
        func_8001F04C((GameThread *)(u32)(a0 + 0x28), 0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006E648);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006E930);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006EA4C);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006EB98);

extern s32 D_800D3584;
extern void func_8006EB98(s32 index);
extern s32 func_8003F4EC(s32 mode);

void func_8006EC8C(u32 completionWord) {
    s32 current = D_800D3584;
    D_800D3584 = (s32)((u32)current + 1u);
    func_8006EB98(current);
    D_800D3584 &= 0xF;
    func_8003F4EC(0);
}

void func_8006ECD4(s32 a0, s32 a1) {
    register s32 a2 asm("$6");  /* retail keeps the object pointer in $a2 */
    a2 = *(s32 *)(a0 + 0x1C);
    *(s32 *)(a0 + 0x20) = a1;
    ((void (*)(s32))(*(s32 *)(a2 + 0x24)))(a0 + *(s16 *)(a2 + 0x20));
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006ED08);

s32 func_8006EF44(s32 a0) {
    return a0 + 0x1B0;
}

s32 func_8006EF4C(s32 a0) {
    return a0 + 0x12C;
}

s32 func_8006EF54(s32 a0, s32 a1) {
    register u8 *base asm("$3") = D_8005F8B8; /* PIN $v1: keeps retail symbol base live */
    return *((s32 *) ((D_8005F8B8 + 0x334) + ((a1 * 3) << 3)));
}

void func_8006EF78(s32 a0, s32 a1, s32 a2) {
    register u8 *base asm("$4") = D_8005F8B8; /* PIN $a0: preserve the separate symbol base */
    s32 *value = (s32 *)((D_8005F8B8 + 0x334) + ((a1 * 3) << 3));
    *value += a2;
}

void func_8006EFA8(s16 a0) {
    register u8 *base asm("$5") = D_8005F8B8; /* PIN $a1: preserve the symbol base */
    *(s32 *)(D_8005F8B8 + 0x70) |= 1 << (s16)a0;
}

s32 func_8006EFD0(s32 *a0, s32 a1) {
    a0 += a1;
    return a0[0x90];
}

s32 func_8006EFE4(s32 a0) {
    return a0 + 0x2A4;
}

s32 func_8006EFEC(u8 *owner) {
    return (s32)func_80037010((RandomState *)((u32)owner + 0x360U));
}

void func_8006F00C(s32 a0) {
    func_80075D08(a0 + 0x228);
}

void func_8006F02C(s32 a0) {
    func_80075D08(a0 + 0x230);
}

void func_8006F04C(s32 a0) {
    func_80075D08(a0 + 0x238);
}

u8 *func_8006F06C(u8 *a0, u8 *a1) {
    if (a1 != 0) {
        func_8002C210((DtorList *)(a0 + 0x3C), (DtorNode *)a1);
    }
    return a1;
}

u8 *func_8006F09C(u8 *a0, u8 *a1) {
    if (a1 != 0) {
        func_8002C210((DtorList *)(a0 + 0x4C), (DtorNode *)a1);
    }
    return a1;
}

void func_8006F0CC(u8 *a0, u8 *node) {
    func_8002C210((DtorList *)(a0 + 0x5C), (DtorNode *)node);
}

s32 func_8006F0EC(s32 a0) {
    return func_8002C2FC(a0 + 0x5C) != 0;
}

void func_8006F10C(s32 a0, u32 a1) {
    ((u32 *)(a0 + 0x2C8))[0] = (*(u32 *)(a0 + 0x2C8) & 0xFFFFFFFB) | ((a1 & 1) << 2);
}

s32 func_8006F12C(s32 a0) {
    s32 s0 = 0;
    if ((*(u32 *)(a0 + 0x2C8) >> 2) & 1) {
        s0 = 1;
    } else if (func_8006F0EC(a0)) {
        s0 = 1;
    }
    return s0;
}

s32 func_8006F178(s32 a0) {
    return (*(u32 *)(a0 + 0x2C8) >> 4) & 1;
}

s32 func_8006F18C(s32 a0) {
    return (*(u32 *)(a0 + 0x2C8) >> 8) & 1;
}

s32 func_8006F1A0(s32 a0) {
    return *(s32 *)(a0 + 0x10);
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006F1AC);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006F23C);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006F3FC);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006F564);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006F678);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006F768);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006FADC);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8006FE98);

void func_8006FFBC(s32 a0) {
    s32 s2 = func_80031B40(*(s32 *)(a0 + 0x10));
    s32 s0;
    for (s0 = 0; s0 < s2; s0++) {
        s32 v1 = *(s32 *)(a0 + 0xD34);
        s32 v0 = ((s32 (*)(s32, s32, s32))(*(s32 *)(v1 + 0x54)))(a0 + *(s16 *)(v1 + 0x50), s0, *(s32 *)(a0 + 0x10));
        if (v0 != 0) {
            func_8002C210((DtorList *)((u32)a0 + 0x3CU), (DtorNode *)v0);
        }
    }
}

s32 func_80070044(s32 a0, s32 a1) {
    if (a1 < func_80031B40(*(s32 *)(a0 + 0x10)) && a1 >= 0) {
        s32 v1 = *(s32 *)(a0 + 0xD34);
        return ((s32 (*)(s32, s32, s32))(*(s32 *)(v1 + 0x54)))(a0 + *(s16 *)(v1 + 0x50), a1, *(s32 *)(a0 + 0x10));
    }
    return 0;
}

s32 func_800700A8(void) {
    return 0;
}

s32 func_800700B0(s32 a0, s32 a1) {
    a0 += a1 * 4;
    return *(s32 *)(*(s32 *)(a0 + 0x2C) + 8);
}

void func_800700CC(s32 *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5) {
    s32 value = ((a4 - a3) << 2) / 3;
    a0[0xCF] = a1;
    a0[0xD0] = a3;
    a0[0xD3] = a2;
    a0[0xD4] = a4;
    a0[0xD5] = a5;
    if (a2 - a1 < value) {
        value = a2 - a1;
    }
    a0[0xD7] = value >> 1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_80070128);

s32 func_800702CC(s32 a0, s32 a1, s32 a2) {
    return func_8007C454(func_8002B364(0x6C), a2);
}

void func_80070300(s32 a0) {
    func_8001F020((GameThread *)(u32)(a0), 0);
    if (func_8006F0EC(a0)) {
        func_8002C010(a0 + 0x5C, a0);
        func_800750DC(*(s32 *)(a0 + 0x24), 0);
        func_800750DC(*(s32 *)(a0 + 0x28), 0);
        func_80070C14(a0);
    } else {
        func_800703A8(a0);
        func_8002C010(a0 + 0x3C, a0);
        func_80070C14(a0);
    }
}

void func_80070388(s32 a0, s32 a1) {
    func_800710FC(a1);
}

void func_800703A8(s32 a0) {
    s32 s1;

    func_80070460(a0);
    s1 = 0;
    if (func_8006F178(a0) != 0 || ((*(u32 *)(a0 + 0x2C8) >> 5) & 1) != 0) {
        s1 = 1;
    }
    if (s1 == 0) {
        func_8007F504(*(s32 *)(a0 + 0x2C));
        func_8007F504(*(s32 *)(a0 + 0x30));
    }
    func_8002C010(a0 + 0x4C, a0);
    if (s1 == 0) {
        func_800708B0(a0);
        func_800708E0(a0);
    }
    if (func_8006F18C(a0) == 0) {
        func_80070690(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_80070460);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_80070690);

s32 func_80070810(s32 a0, s32 a1) {
    return *(s32 *)(a0 + 0x350) + 0x1000 < *(s32 *)(a1 + 4);
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_80070824);

void func_800708B0(s32 a0) {
    func_8007A3CC(*(s32 *)(*(s32 *)(a0 + 0x2C) + 8), *(s32 *)(*(s32 *)(a0 + 0x30) + 8));
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_800708E0);

void func_80070C14(s32 a0) {
    s32 v1;
    *(s32 *)(a0 + 0xD24) += 1;
    v1 = *(s32 *)(a0 + 0xD34);
    ((void (*)(s32))(*(s32 *)(v1 + 0x64)))(a0 + *(s16 *)(v1 + 0x60));
    func_80072FBC(a0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_80070C60);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_80070DA8);

s32 func_80070F2C(s32 arg0, s32 arg1, s32 arg2) {
    s32 v0 = *(s32 *)(arg0 + (arg1 << 2) + 0x2C);
    s32 a1 = *(s32 *)(v0 + 0x20);
    s32 a3 = *(s32 *)(v0 + 0x1C);

    switch (arg2) {
    case 0:
        return (a1 == a3) ? 0x2710 : 0;
    case 1:
        return a1 * 10000 / a3;
    case 2:
    case 4:
        return *(s32 *)(arg0 + 0xD28) / 30 * 100;
    case 3:
        return 0x1388;
    }
    return 0;
}

s32 func_80071000(s32 a0, s32 a1) {
    s32 sum;

    if ((*(s32 *)(a0 + 0xD2C) & 1) == 0) {
        sum = func_80070F2C(a0, a1, 0);
        sum += func_80070F2C(a0, a1, 1);
        sum += func_80070F2C(a0, a1, 2);
    } else {
        sum = func_80070F2C(a0, a1, 3);
        sum += func_80070F2C(a0, a1, 4);
    }
    return sum;
}

void func_800710A4(s32 a0, s32 a1) {
    do {
        func_8001F04C((GameThread *)(u32)(a0), 0);
    } while (--a1 > 0);
}

s32 func_800710E8(s32 a0) {
    u32 v = *(u32 *)(a0 + 0x2C8);
    v |= 8;
    *(u32 *)(a0 + 0x2C8) = v;
    return v;
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_800710FC);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_8007144C);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_800715D8);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_80071724);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_80071880);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_80071A84);

void func_80071B6C(s32 a0) {
    u8 *p = D_8005F824;
    s32 v0;
    func_8001BE78((s32)(u32)p, 0x8009, 0);
    func_8001BE78((s32)(u32)p, 0x42, 0);
    v0 = func_800CBA6C(func_8002BD88(0x59C), 0xA, 0);
    v0 = (s32)func_8006F09C((u8 *)a0, (u8 *)v0);
    func_80071D30(a0, v0, -1);
}

void func_80071BF0(s32 a0) {
    u8 *p = D_8005F824;
    s32 s0;
    s32 v0;

    func_8001BE78((s32)(u32)p, 0x8009, 0);
    func_8001BE78((s32)(u32)p, 0x42, 0);
    s0 = *(s32 *)(*(s32 *)(a0 + 0x30) + 8);
    func_800794C8(*(s32 *)(*(s32 *)(a0 + 0x2C) + 8));
    func_800794C8(s0);
    v0 = func_800CBA6C(func_8002BD88(0x59C), 9, 0);
    v0 = (s32)func_8006F09C((u8 *)a0, (u8 *)v0);
    func_80071D30(a0, v0, -1);
}

void func_80071C94(s32 a0) {
    s32 s0;
    s32 v0;
    func_8001C1C0();
    func_8001BE78((s32)(u32)D_8005F824, 0x8007, 0);
    s0 = *(s32 *)(*(s32 *)(a0 + 0x30) + 8);
    func_800794C8(*(s32 *)(*(s32 *)(a0 + 0x2C) + 8));
    func_800794C8(s0);
    v0 = func_8002BD88(0x59C);
    v0 = func_800CBA6C(v0, 1, 0);
    v0 = (s32)func_8006F09C((u8 *)a0, (u8 *)v0);
    func_80071D30(a0, v0, -1);
    func_80071EB8(a0);
}

void func_80071D30(s32 a0, s32 a1, s32 a2) {
    func_80071D74(a0, func_8002BD74(a1), a2);
}

extern s32 D_80114210;

s32 func_80071D74(s32 a0, s32 a1, s32 a2) {
    while (func_8002BDC8(a1)) {
        func_800710A4(a0, 0);
        if (a2 >= 0 && (func_80027004(D_80114210, a2) & 0x800)) {
            func_8002BE64(a1);
            return 1;
        }
    }
    return 0;
}

void func_80071E08(s32 a0) {
    *(s32 *)(a0 + 0x2B8) = 0x20;
    do {
        func_800710A4(a0, 0);
        *(s32 *)(a0 + 0x2B8) -= 2;
    } while (*(s32 *)(a0 + 0x2B8) >= -4);
}


void func_80071E58(s32 a0) {
    s32 t;
    *(s32 *)(a0 + 0x2B8) = 0;
    do {
        func_800710A4(a0, 0);
        t = (s32)((u32)*(s32 *)(a0 + 0x2B8) + 2u);
        *(s32 *)(a0 + 0x2B8) = t;
    } while (t < 0x25);
    func_8001EAF4((u8 *)&D_8005F884, 0, 0);
}

void func_80071EB8(s32 a0) {
    func_80071E58(a0);
    *(s32 *)(a0 + 0x2C8) |= 1;
    for (;;) {
        func_800710A4(a0, 0);
    }
}

void func_80071EF0(s32 a0) {
    register s32 v0 asm("$2");  /* retail keeps the 0xD34 pointer in $v0 */
    func_8006FE98(a0);
    func_8006FADC(a0);
    v0 = *(s32 *)(a0 + 0xD34);
    ((void (*)(s32))(*(s32 *)(v0 + 0xC)))(a0 + *(s16 *)(v0 + 8));
    func_80034550(0);
    func_8001C0FC(func_8001D640(D_8005F8B8), 0);
    func_8001C148(D_8005F824);
}

void func_80071F64(void) {
}

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_80071F6C);

INCLUDE_ASM("asm/us/game/nonmatchings/9DF4", func_800720EC);
