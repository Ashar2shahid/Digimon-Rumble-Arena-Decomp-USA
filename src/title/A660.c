#include "game_thread.h"
#include "game_sprite_cleanup.h"
#include "game_sdk_memcpy.h"
#include "render_context.h"
#include "game_lerp_words.h"
#include "character_getters.h"
#include "game_rotation.h"
#include "game_audio_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_printer_storage.h"
#include "iterator_object.h"
#include "deferred_objects.h"
#include "game_input.h"
extern void func_8006FBBC();
extern s32 D_80114210;
extern u8 D_8005F824[];
extern u8 *D_8007A5BC;
extern s32 D_8007A5C8[];

extern s32 func_8006E72C();
extern s32 func_8006E754();
extern s32 func_8006E740();
extern void func_8006E738();
extern s32 func_800599F4();
extern void func_8007374C();
extern void func_8002BCEC();
extern void func_8002BDA8();
extern void func_800207C0();

extern void func_800207E8();
extern void func_80055B64();
extern void func_8002B3D0();
extern void func_8006F1C4();
extern void func_8006FC10();
extern s32 func_8006E610();
extern void func_8006EE84();
extern u8 D_8006511C[];
extern u8 D_80065114[];
extern s32 func_80058888();
extern s32 func_80058C0C();
extern s32 func_80058F1C();
extern s32 func_80059D80();
extern u8 D_80064EA0[];
extern u8 D_80064EA8[];
extern u8 D_8006516C[];
extern u8 D_80064EB0[];
extern s32 D_8005F820;
extern u8 D_8005FC8C[];
extern u8 D_8005F910[];
extern u8 D_8005F94C[];
extern u8 D_80064EB8[];
extern u8 D_80064EE0[];
extern u8 D_80064F18[];
extern u8 D_80064F2C[];
extern u8 D_80064F38[];
extern u8 D_80064F6C[];
extern u8 D_80064F84[];
extern u8 D_80064F94[];
extern u8 D_80064FA0[];
extern u8 D_80064FC0[];
extern u8 D_80064FDC[];
extern u8 D_80065004[];
extern u8 D_80065014[];
extern u8 D_8006504C[];
extern u8 D_8006505C[];
extern u8 D_80065064[];
extern u8 D_80065354[];
extern u8 D_80065374[];
extern u8 D_8006539C[];
extern u8 D_800653BC[];
extern u8 D_800653E0[];
extern s32 D_8007A5C0;
extern s32 func_8006E694();
extern s32 func_8006E71C();
extern s32 func_8006E8C0();
extern void func_8006F09C();
extern void func_8006F100();
extern void func_8006F140();
extern void func_8006F184();
extern s32 func_8006F6A4();
extern s32 func_8006F7F4();
extern s32 func_8006F868();
extern s32 func_8006F884();
extern s32 func_8006F8C4();
extern s32 func_8006FA74();
extern s32 func_8006FAF4();
extern s32 func_8006FB6C();
extern s32 func_8006FC98();
extern s32 func_80059E7C();
extern s32 func_80059C50();
extern s32 func_800595B4();
extern s32 func_8002B6D4();
extern s32 func_8002B3F8();
extern s32 func_8002BD88();
extern s32 func_8002BF6C();
extern s32 func_8002BF88();
extern s32 func_8002B770();
extern s32 func_80058848();
extern s32 func_800587D8();
extern s32 func_8006AB18();
extern s32 func_8006ABAC();
extern s32 func_8001EEF4();
extern s32 func_8001E688();
extern s32 func_8001E734();
extern s32 func_8003DEC4();
extern s32 func_80032284();
extern s32 func_80032318();
extern s32 func_80032334();
extern void func_8006EEA4();
extern void func_8006F338();
extern void func_80071008();
extern void func_80020780();


void func_8006EA20(u8 *arg0, s32 arg1) {
    func_8006E72C(arg0);
    if (arg1) {
        *(s32 *)(arg0 + 0x34) = 0;
    } else {
        *(s32 *)(arg0 + 0x34) = 1;
    }
    *(s32 *)(arg0 + 0x38) = 0;
}

s32 func_8006EA68(u8 *arg0) {
    return *(s32 *)(arg0 + 0x38);
}

s32 func_8006EA74(u8 *arg0) {
    return *(u32 *)(arg0 + 0x34) == 0;
}

void func_8006EA80(u8 *arg0) {
    s32 a0;
    s32 v1;

    func_8006E754();
    if (func_8006E740(arg0) == 0) {
        return;
    }
    if (func_8006EA68(arg0) != 0) {
        return;
    }
    v1 = func_80027004(D_80114210, -1);
    if (v1 & 0x840) {
        func_8001BE78((s32)(u32)D_8005F824, 0x10, 0);
        *(s32 *)(arg0 + 0x38) = 1;
        func_8006E738(arg0);
        return;
    }
    a0 = *(s32 *)(arg0 + 0x34);
    if (a0 <= 0) {
        if (!(v1 & 0x4000)) {
            return;
        }
        *(s32 *)(arg0 + 0x34) = a0 + 1;
        func_8001BE78((s32)(u32)D_8005F824, 0xF, 0);
    } else {
        if (!(v1 & 0x1000)) {
            return;
        }
        *(s32 *)(arg0 + 0x34) = a0 - 1;
        func_8001BE78((s32)(u32)D_8005F824, 0xF, 0);
    }
}

void func_8006EB64(u8 *arg0, s32 arg1) {
    s32 c0, c1;
    TextPrinterRecord storage;
    const PrinterCallbackTable *p;
    s16 off;
    void (*fn)(void *, u32);

    if (func_8006E740(arg0) == 0) {
        return;
    }
    c0 = 0x808080;
    c1 = 0x404040;
    if (*(s32 *)(arg0 + 0x34) != 0) {
        c0 = 0x404040;
        c1 = 0x808080;
    }
    func_80032284((u8 *)&storage, D_8005F820 - 4);
    func_80032318((u8 *)&storage, 1);
    func_80032334((u8 *)&storage, 0x700000);
    p = storage.base.table;
    off = p->colorAdjustment;
    fn = p->setColor;
    fn((u8 *)&storage + off, c0);
    func_8006E694(arg0, (u8 *)&storage, D_80064EA0, 0);
    p = storage.base.table;
    off = p->colorAdjustment;
    fn = p->setColor;
    fn((u8 *)&storage + off, c1);
    func_8006E694(arg0, (u8 *)&storage, D_80064EA8, 0x10);
    func_8006E8C0(arg0, arg1);
    func_8003277C((u8 *)&storage, 2);
}

s32 *func_8006EC84(s32 *arg0, s32 *arg1) {
    *arg0 = (s32)arg1;
    *arg1 = 1;
    return arg0;
}

void func_8006EC98(s32 **arg0, s32 arg1) {
    s32 *v0 = arg0[0];

    *v0 = 0;
    if (arg1 & 1) {
        func_8002B3D0();
    }
}

u8 *func_8006ECC8(u8 *arg0, s32 arg1) {
    u8 buf[0x18];
    u8 *s2;
    u8 *s0;

    func_8002B6D4(arg0, 0, D_80064EB0);
    *(u8 **)(arg0 + 0x1C) = D_8006516C;
    func_8001EEF4(arg0 + 0x24, func_8006EE84, 0x1000, arg0, 0);
    s2 = arg0 + 0x34;
    func_8002BF6C(s2);
    *(s32 *)(arg0 + 0x20) = arg1;
    func_800587D8();
    func_80059C50(func_8006F868);
    *(s32 *)(arg0 + 0x30) = 0;
    func_8006AB18(buf, D_8005F94C, 8);
    *(s32 *)(arg0 + 0x48) = func_8006E610(func_8002BD88(0x34), 0x20, 0x30, 0x100, 0x50);
    s0 = (u8 *)func_8002BD88(0x3C);
    func_8006E610(s0, 0x78, 0x90, 0x50, 0x20);
    *(u8 **)(s0 + 0x14) = D_8006511C;
    *(s32 *)(s0 + 0x34) = 0;
    *(u8 **)(arg0 + 0x4C) = s0;
    func_8002C210((DtorList *)s2, (DtorNode *)*(u8 **)(arg0 + 0x48));
    func_8002C210((DtorList *)s2, (DtorNode *)*(u8 **)(arg0 + 0x4C));
    D_8007A5BC = arg0;
    *(s32 *)(arg0 + 0x44) = 0;
    func_8006ABAC(buf, 2);
    return arg0;
}

void func_8006EE04(u8 *arg0, s32 arg1) {
    *(u8 **)(arg0 + 0x1C) = D_8006516C;
    func_80059C50(0);
    func_80058848();
    D_8007A5BC = 0;
    func_8002BF88(arg0 + 0x34, 2);
    func_8001EFB0((GameThread *)(arg0 + 0x24), 2);
    func_8002B770(arg0, arg1);
}

s32 func_8006EE78(u8 *arg0) {
    return *(s32 *)(arg0 + 0x44);
}


void func_8006EE84(s32 arg0, s32 arg1) {
    func_8006EEA4(arg1);
}

void func_8006EEA4(u8 *arg0) {
    u8 *s0 = arg0;

    switch (*(s32 *)(s0 + 0x20)) {
    case 0:
        func_8006F09C(s0);
        break;
    case 1:
        func_8006F100(s0);
        break;
    case 2:
        func_8006F140(s0);
        break;
    case 3:
        func_8006F184(s0);
        break;
    }
    s0 += 0x24;
    for (;;) {
        func_8001F04C((GameThread *)(s0), 1);
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_8006EF44);

void func_8006F078(s32 *arg0, s32 arg1) {
    func_8006E71C(*(s32 *)((u8 *)arg0 + 0x48), arg1);
}

void func_8006F09C(u8 *arg0) {
    func_8006F078((s32 *)arg0, (s32)D_80064F2C);
    if (func_8006FC98(arg0, 0) != 0) {
        func_8006F1C4(arg0, 0);
    }
    func_8006E738(*(s32 *)(arg0 + 0x48));
    func_8006FC10(arg0, 0x14, 0);
}


void func_8006F100(s32 *arg0) {
    func_8006F338();
    func_8006E738(arg0[0x12]);
    func_8006FC10(arg0, 0x14, 0);
}

void func_8006F140(s32 *arg0) {
    func_8006F1C4(arg0, 1);
    func_8006E738(*(s32 *)((u8 *)arg0 + 0x48));
    func_8006FC10(arg0, 0x14, 0);
}

void func_8006F184(s32 *arg0) {
    func_8006F338();
    func_8006E738(arg0[0x12]);
    func_8006FC10(arg0, 0x14, 0);
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_8006F1C4);

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_8006F338);

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_8006F51C);

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_8006F6A4);

extern u8 D_800650DC[];

s32 func_8006F7F4(s32 *context, s32 kind, s32 name) {
    switch (kind) {
    case 0:
        return 0;
    case 1:
    case 3:
        func_8006F078(context, (s32)D_800650DC);
        break;
    case 2:
    case 4:
    case 5:
    default:
        func_8006F078(context, name);
        break;
    }
    return -1;
}


s32 func_8006F868(s32 arg0, s32 arg1) {
    u8 *p = D_8007A5BC;

    *(volatile s32 *)(p + 0x50) = arg0;
    *(volatile s32 *)(p + 0x54) = arg1;
}

s32 func_8006F884(u8 *arg0, s32 arg1) {
    s32 out;
    u8 buf[0x28];
    s32 r;

    r = func_800599F4(*(s32 *)(arg0 + 0x30), arg1, buf, &out, 0, 1);
    if (r != 0) {
        return -1;
    }
    return out;
}

s32 func_8006F8C4(u8 *arg0) {
    s32 out;
    u8 buf[0x258];
    s32 i;
    s32 total;
    s32 r;

    total = 0xF;
    r = func_800599F4(*(s32 *)(arg0 + 0x30), (s32)D_80065114, buf, &out, 0, total);
    if (r != 0) {
        return -1;
    }
    for (i = 0; i < out; i++) {
        total -= (*(s32 *)(buf + i * 0x28 + 0x18) + 0x1FFF) / 0x2000;
    }
    return total;
}

s32 func_8006F954(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n;
    s32 ret;

    ret = 0;
    n = arg3;
    while (n != 0) {
        ret = func_80058F1C(*(s32 *)(arg0 + 0x30), arg1, 2);
        if (ret == 0) {
            return 0;
        }
        if (ret == 5) {
            break;
        }
        func_8001F04C((GameThread *)(arg0 + 0x24), 0);
        n--;
    }
    if (ret != 5) {
        return ret;
    }
    n = arg3;
    while (n != 0) {
        ret = func_80059D80(*(s32 *)(arg0 + 0x30), arg1, arg2);
        if (ret == 0) {
            break;
        }
        func_8001F04C((GameThread *)(arg0 + 0x24), 0);
        n--;
    }
    if (ret != 0) {
        return ret;
    }
    n = arg3;
    while (n != 0) {
        ret = func_80058F1C(*(s32 *)(arg0 + 0x30), arg1, 2);
        if (ret == 0) {
            break;
        }
        func_8001F04C((GameThread *)(arg0 + 0x24), 0);
        n--;
    }
    return ret;
}

s32 func_8006FA74(u8 *arg0) {
    s32 i;
    s32 r;

    for (i = 3; i != 0; i--) {
        while (func_80058888(*(s32 *)(arg0 + 0x30)) == 0) {
            func_8001F04C((GameThread *)(arg0 + 0x24), 0);
        }
        r = func_8006FB6C(arg0);
        if (r == 0 || r == 3) {
            return 1;
        }
    }
    return 0;
}

s32 func_8006FAF4(u8 *arg0) {
    s32 i;
    s32 r;

    for (i = 3; i != 0; i--) {
        while (func_80058C0C(*(s32 *)(arg0 + 0x30)) == 0) {
            func_8001F04C((GameThread *)(arg0 + 0x24), 0);
        }
        r = func_8006FB6C(arg0);
        if (r == 0 || r == 3) {
            break;
        }
    }
    return r;
}

s32 func_8006FB6C(u8 *arg0) {
    *(s32 *)(arg0 + 0x50) = 0;
    while (*(volatile s32 *)(arg0 + 0x50) == 0) {
        func_8001F04C((GameThread *)(arg0 + 0x24), 0);
    }
    return *(s32 *)(arg0 + 0x54);
}

void func_8006FBBC(u8 *arg0) {
    s32 s0 = D_80114210;

    while ((func_80027004(s0, -1) & 0x8F0) == 0) {
        func_8001F04C((GameThread *)(arg0 + 0x24), 0);
    }
}

void func_8006FC10(u8 *arg0, s32 arg1, s32 arg2) {
    s32 s0 = arg1;

    while (1) {
        s0--;
        if (s0 == -1) {
            break;
        }
        if (arg2 != 0) {
            if ((func_80027004(D_80114210, -1) & 0x8F0) != 0) {
                break;
            }
        }
        func_8001F04C((GameThread *)(arg0 + 0x24), 0);
    }
}

s32 func_8006FC98(u8 *arg0, s32 arg1) {
    s32 *s0 = *(s32 **)(arg0 + 0x4C);

    func_8006EA20(s0, arg1);
    do {
        func_8001F04C((GameThread *)(arg0 + 0x24), 0);
    } while (func_8006EA68(s0) == 0);
    return func_8006EA74(s0);
}

extern void func_8002B82C();
extern void func_8002C010();
extern void func_8002C19C();

void func_8006FCF0(u8 *arg0) {
    s32 s0 = func_8001F020((GameThread *)(arg0 + 0x24), 0);
    s32 v0 = 0 < s0;
    *(s32 *)(arg0 + 0x44) = v0;
    if (v0 != 0) {
        func_8002B82C(arg0);
    }
    if (s0 >= 0) {
        func_8002C010(arg0 + 0x34, arg0);
        func_8002C19C(arg0 + 0x34, arg0);
    }
}

extern void func_8005858C();
extern s32 func_8005859C();
extern void func_8003DEEC();
extern void func_8003E26C();
extern void *memcpy();

u8 *func_8006FD5C(u32 *arg0, u8 *arg1, s32 arg2, u8 *arg3, s32 arg4) {
    s32 local[6];
    register s32 n asm("$17");
    s32 shift;
    u32 size;
    s32 end;
    u8 *buf;
    u8 *src;
    u8 *src2;

    func_8005858C(arg2);
    func_8005859C(local);
    n = *((s16 *)(*((s32 *)(((u8 *)local) + 0xC)) + 6));
    if (n < 0) {
        n += 0xF;
    }
    n >>= 4;
    shift = n << 7;
    end = arg4 + 0x80;
    size = shift + end;
    *arg0 = size;
    buf = func_8003DEC4(((size + 3) >> 2) << 2);
    func_8003DEEC(buf, 0x80);
    buf[0] = 0x53;
    buf[1] = 0x43;
    buf[3] = ((*arg0) + 0x1FFF) >> 13;
    buf[2] = n + 0x10;
    func_8003E26C(buf + 4, arg1, 0x40);
    src2 = *((u8 **)(((u8 *)local) + 0x10));
    src = *((u8 **)(((u8 *)local) + 8));
    memcpy(buf + 0x60, src, 0x20);
    func_8003DF5C(buf + 0x80, src2, shift);
    func_8003DF5C(buf + (shift + 0x80), arg3, arg4);
    return buf;
}

void func_8006FF00(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_8006FF48(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

u8 *func_8006FF90(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    func_8006E610(a0, a1, a2, a3, a4);
    *(u8 **)(a0 + 0x14) = D_8006511C;
    *(s32 *)(a0 + 0x34) = 0;
    return a0;
}

extern u8 *func_80028050();
extern s32 func_800280A0();
extern void func_8005844C();

u8 *func_8006FFD0(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    u8 *s2 = func_80028050();
    *(u32 *)(s2 + 8) = (arg2 << 16) | (arg1 & 0xFFFF);
    *(u32 *)(s2 + 0xC) = *(u32 *)(arg3 + 4);
    *(u32 *)(s2 + 0x10) = *(u32 *)(arg3 + 8);
    func_8005844C(arg0, s2);
    func_8005844C(arg0, (u8 *)func_800280A0(*(u16 *)arg3));
    return s2;
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_8007006C);

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_80070240);

extern u8 D_8006594C[];
extern void func_8001BEDC();
extern void func_8001BCF8();
extern void func_8001BCC4();
extern void func_80020BFC();

void func_80070418(u8 *arg0, s32 arg1) {
    s32 *a2;
    u8 *v = D_8006594C;
    *(u32 *)(arg0 + 0x1C) = (u32)v;
    func_8001BEDC(*(s32 *)(arg0 + 0x38));
    func_8001BCF8(D_8005F824);
    func_8001BCC4(D_8005F824);
    a2 = (s32 *)*(u32 *)(arg0 + 0x34);
    if (a2 != 0) {
        s32 v0 = a2[5];
        ((void (*)(s32, s32)) * (s32 *)(v0 + 0x1C))(
            (s32)a2 + *(s16 *)(v0 + 0x18), 3);
    }
    func_8001EAD4(((u8 *)&D_8005F884), 0);
    func_80020BFC(arg0 + 0x3C, 2);
    func_8002BF88(arg0 + 0x24, 2);
    func_8002B770(arg0, arg1);
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_800704D8);

void func_800705E4(u8 *arg0) {
    u8 *s5 = (u8 *)D_80114210;
    s32 s2 = 0;
    s32 s4 = -1;

    for (; s2 < 2; s2++) {
        s32 s1 = func_80027004(s5, s2);

        if ((s1 & 0x10) != 0 && *(s16 *)(arg0 + 0xA6E) == 0) {
            *(s16 *)(arg0 + 0xA6E) = s4;
            func_8001EAB4(((u8 *)&D_8005F884), 0x1E);
            func_80071C58(*(s32 *)(arg0 + 0x34), 1);
        }
        if (s1 & 0x40) {
            if (*(s16 *)(arg0 + 0xA88) == 0) {
                *(s16 *)(arg0 + 0xA76) = 1;
            } else if (func_80071C80(*(s32 *)(arg0 + 0x34)) == 0) {
                func_80071C58(*(s32 *)(arg0 + 0x34), 9);
            }
            if (*(s16 *)(arg0 + 0xA8A) != 0 && *(s16 *)(arg0 + 0xA6E) == 0) {
                *(s16 *)(arg0 + 0xA6E) = s4;
                func_8001EAB4(((u8 *)&D_8005F884), 0x1E);
                func_80071C58(*(s32 *)(arg0 + 0x34), 1);
            }
        }
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_80070714);

void func_8007152C(void);

void func_800707F0(s32 arg0) {
    func_8007152C();
    func_80071008(arg0);
}

extern void func_80071534();
extern void func_80071044();
extern void func_80070A04();
extern void func_80070BF0();

void func_8007081C(u8 *arg0) {
    func_80071534(arg0);
    if (*(s16 *)(arg0 + 0xA72) >= 0x21) {
        func_80071044(arg0);
    } else {
        *(s16 *)(arg0 + 0xA72) = *(u16 *)(arg0 + 0xA72) + 1;
    }
    func_80070A04(arg0);
    func_80070BF0(arg0);
}

void func_80070878(void) {
}

extern u8 D_8006597C[];
extern void func_8007006C();

void func_80070880(u8 *arg0) {
    u8 *s2 = (u8 *)*(u32 *)(arg0 + 0x40);
    u8 *v1;
    u8 *s5;
    u8 *s1;

    func_8007006C(s2, *(u16 *)(arg0 + 0xA6C));
    s1 = D_8006597C;
    v1 = func_8006FFD0(s2, 0x2F, 0xD,
                       (u8 *)(((*(u16 *)(arg0 + 0xA74) + 4) & 0xFFFF) * 12 +
                              (u32)s1));
    v1[4] = 0x80;
    v1[5] = 0x80;
    v1[6] = 0x80;
    v1 = func_8006FFD0(s2, 0x46, 0xD1, (u8 *)((u32)s1 + 0xA8));
    v1[4] = 0x80;
    v1[5] = 0x80;
    v1[6] = 0x80;
    s5 = (u8 *)func_800280A0(6);
    v1 = func_80028050();
    v1[4] = 0x80;
    v1[5] = 0x80;
    v1[6] = 0x80;
    v1[0xC] = 0;
    v1[0xD] = 0;
    *(u16 *)(v1 + 8) = 0;
    *(u16 *)(v1 + 0xA) = 0;
    *(u16 *)(v1 + 0x10) = 0x100;
    *(u16 *)(v1 + 0x12) = 0xF0;
    *(u16 *)(v1 + 0xE) = 0x3FD8;
    func_8005844C(s2, v1);
    func_8005844C(s2, s5);
    s5 = (u8 *)func_800280A0(7);
    v1 = func_80028050();
    v1[4] = 0x80;
    v1[5] = 0x80;
    v1[6] = 0x80;
    v1[0xC] = 0;
    v1[0xD] = 0;
    *(u16 *)(v1 + 8) = 0x100;
    *(u16 *)(v1 + 0xA) = 0;
    *(u16 *)(v1 + 0x10) = 0x40;
    *(u16 *)(v1 + 0x12) = 0xF0;
    *(u16 *)(v1 + 0xE) = 0x3FD8;
    func_8005844C(s2, v1);
    func_8005844C(s2, s5);
}

void func_800709FC(void) {
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_80070A04);

void func_80070BE8(void) {
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_80070BF0);

void func_80071008(u8 *arg0) {
    u32 v = *(u16 *)(arg0 + 0xA74);
    s32 a1;

    *(s16 *)(arg0 + 0xA76) = 0;
    *(s16 *)(arg0 + 0xA78) = 0;
    *(s16 *)(arg0 + 0xA7A) = 0;
    *(s16 *)(arg0 + 0xA7C) = 0;
    a1 = D_8007A5C8[v];
    *(s16 *)(arg0 + 0xA88) = 0;
    *(s16 *)(arg0 + 0xA8A) = 0;
    *(s32 *)(arg0 + 0xA80) = a1;
    *(s32 *)(arg0 + 0xA84) = a1;
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_80071044);

void func_80071524(void) {
}

void func_8007152C(void) {
}

void func_80071534(u8 *arg0) {
    u8 *s1;
    u8 *a3;
    s32 s2;
    s1 = *(u8 **)(arg0 + 0x44);
    if (*(s16 *)(arg0 + 0xA88) == 0) {
        return;
    }
    s2 = func_800280A0(0x17);
    a3 = (u8 *)func_80028050();
    a3[4] = 0x80;
    a3[5] = 0x80;
    a3[6] = 0x80;
    if (((*(u16 *)(arg0 + 0xA6C) >> 3) ^ 1) & 1) {
        *(u8 *)(a3 + 0xC) = 0x40;
        *(u8 *)(a3 + 0xD) = 0;
    } else {
        *(u8 *)(a3 + 0xC) = 0x50;
        *(u8 *)(a3 + 0xD) = 0;
    }
    *(u16 *)(a3 + 8) = 0x110;
    *(u16 *)(a3 + 0xA) = 0xB4;
    *(u16 *)(a3 + 0x10) = 0x10;
    *(u16 *)(a3 + 0x12) = 0x10;
    *(u16 *)(a3 + 0xE) = 0x7F9C;
    func_8005844C(s1, a3);
    func_8005844C(s1, s2);
}

void func_800715FC(u8 *arg0) {
    *(s16 *)(arg0 + 0xA6E) = 0;
    *(s16 *)(arg0 + 0xA70) = 0;
    *(s16 *)(arg0 + 0xA72) = 0;
}

void func_8007160C(u8 *arg0) {
    if (*(s16 *)(arg0 + 0xA6E) != 0) {
        if (*(s16 *)(arg0 + 0xA70) == 0x20) {
            func_8001BEDC(*(u32 *)(arg0 + 0x38));
        }
        if (*(s16 *)(arg0 + 0xA70) >= 0x80) {
            func_8002B82C(arg0);
        } else {
            *(u16 *)(arg0 + 0xA70) = *(u16 *)(arg0 + 0xA70) + 1;
        }
    }
}

void func_80071680(u8 *arg0, s32 arg1) {
    u8 *a2 = *(u8 **)(arg0 + 0x1C);
    *(s32 *)(arg0 + 0x20) = arg1;
    (*(void (**)(u8 *, s32))(a2 + 0x24))((u8 *)(arg0 + *(s16 *)(a2 + 0x20)), arg1);
}

extern s32 func_8002B364();
extern s32 func_80030C64();
extern void func_80030DF8();
extern u8 *func_80031208(u8 *);
extern u8 *func_80031230(u8 *);
extern s32 func_800204E4();
extern void func_800245B8();
extern void func_800240C8();
extern void func_80024204();
extern void func_80024340();
extern void func_80071C08();
extern u8 D_80065AD0[];
u8 *func_800716B4(u8 *arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 t;
    s32 b;
    s32 a;
    func_8002BC9C(arg0, 0);
    *(u32 *)(arg0 + 0x14) = (u32)D_80065AD0;
    *(s32 *)(arg0 + 0x18) = arg1;
    t = func_80030C64(func_8002B364(0x30), 0x18);
    *(s32 *)(arg0 + 0x1C) = t;
    func_80030DF8(t);
    b = func_8002B364(0x98);
    a = (s32)func_80031208(*(u8 **)(arg0 + 0x1C));
    *(s32 *)(arg0 + 0x20) = func_800204E4(b, a, (s32)func_80031230(*(u8 **)(arg0 + 0x1C)));
    func_80071C08(arg0, 0, 0, 0);
    func_800245B8((u8 *)(*(s32 *)(arg0 + 0x20) + 0x2C), arg2[0], arg2[1], arg2[2]);
    func_800240C8((u8 *)(*(s32 *)(arg0 + 0x20) + 0x2C), arg3[0]);
    func_80024204((u8 *)(*(s32 *)(arg0 + 0x20) + 0x2C), arg3[1]);
    func_80024340((u8 *)(*(s32 *)(arg0 + 0x20) + 0x2C), arg3[2]);
    *(s32 *)(*(s32 *)(arg0 + 0x20) + 8) = 0;
    *(u16 *)(arg0 + 0x26) = 0;
    *(u16 *)(arg0 + 0x28) = 0;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(u16 *)(arg0 + 0x30) = 0;
    *(u16 *)(arg0 + 0x32) = 0;
    *(u16 *)(arg0 + 0x34) = 0;
    *(u16 *)(arg0 + 0x36) = 0;
    *(u16 *)(arg0 + 0x24) = 0;
    *(s32 *)(arg0 + 0x38) = 0;
    *(s32 *)(arg0 + 0x3C) = 0;
    return arg0;
}

extern void func_80030CF8();
void func_800717FC(u8 *arg0, s32 arg1) {
    u8 *a2;
    u8 *v0;
    a2 = *(u8 **)(arg0 + 0x20);
    *(u32 *)(arg0 + 0x14) = (u32)D_80065AD0;
    if (a2 != 0) {
        v0 = *(u8 **)(a2 + 0x54);
        (*(void (**)(u8 *, s32))(v0 + 0x24))((u8 *)(a2 + *(s16 *)(v0 + 0x20)), 3);
    }
    if (*(u32 *)(arg0 + 0x1C) != 0) {
        func_80030CF8(*(u32 *)(arg0 + 0x1C), 3);
    }
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_80071890);

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_80071A98);

extern void func_800207A0();
extern void func_8001FE8C();
void func_80071BAC(u8 *arg0) {
    u8 *s0 = *(u8 **)(arg0 + 0x20);
    u8 *vt;
    func_800207A0(s0);
    vt = *(u8 **)(s0 + 0x54);
    (*(void (**)(u8 *))(vt + 0xC))((u8 *)(s0 + *(s16 *)(vt + 8)));
    func_8001FE8C(s0, *(u32 *)(arg0 + 0x18));
}

void func_80071C08(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_800207C0(arg0[8], arg1, arg2, arg3, 0);
    func_800207E8(arg0[8], func_80031258(*(u8 **)((u8 *)arg0 + 0x1C), arg1));
}

void func_80071C58(u8 *arg0, s32 arg1) {
    *(s16 *)(arg0 + 0x26) = arg1;
    if (*(s32 *)(arg0 + 0x38) == 1) {
        *(s16 *)(arg0 + 0x28) = 0;
        *(s32 *)(arg0 + 0x3C) = 0;
    }
}

void func_80071C78(s32 *arg0, s32 arg1) {
    arg0[0xF] = arg1;
}

s16 func_80071C80(u8 *arg0) {
    return *(s16 *)(arg0 + 0x28);
}


void func_80071C8C(s32 *arg0) {
    func_80020780(arg0[8]);
}

void func_80071CB0(u8 *arg0, volatile s32 *arg1, s32 *arg2) {
    {
        register s32 *p asm("$2"); /* PIN $v0: retail matrix pointer for initialization. */

        p = *(s32 **)(arg0 + 0x20);
        p[0xB] = 0x1000;
        p[0xC] = 0;
        p[0xD] = 0x1000;
        p[0xE] = 0;
        p[0xF] = 0x1000;
        p[0x10] = 0;
        p[0x11] = 0;
        p[0x12] = 0;
    }
    func_800240C8(*(s32 **)(arg0 + 0x20) + 0xB, arg2[0]);
    func_80024204(*(s32 **)(arg0 + 0x20) + 0xB, arg2[1]);
    func_80024340(*(s32 **)(arg0 + 0x20) + 0xB, arg2[2]);
    {
        register s32 *q asm("$3"); /* PIN $v1: retail destination for the trailing copy. */
        register s32 t0 asm("$2"); /* PIN $v0: retail first copy temporary. */
        register s32 t1 asm("$4"); /* PIN $a0: retail second copy temporary. */
        register s32 t2 asm("$5"); /* PIN $a1: retail third copy temporary. */

        q = *(s32 * volatile *)(arg0 + 0x20);
        t0 = arg1[0];
        t1 = arg1[1];
        t2 = arg1[2];
        q[0x10] = t0;
        q[0x11] = t1;
        q[0x12] = t2;
    }
    (*(s32 **)(arg0 + 0x20))[2] = 0;
}

extern u8 *D_8007A5D4[][2];
extern u8 *func_8002E6B0(const void *, s32, s32);
void func_80071D64(u8 *owner, s32 index) {
    u32 path[2];
    u8 *context;
    u8 *target;
    u8 *result;

    context = *(u8 **)(owner + 0x18);
    target = *(u8 **)(context + 8);
    __builtin_memcpy(path, D_8007A5D4[index][0], sizeof(path));
    result = func_8002E6B0(path, 0x168, 0);
    func_8005844C(target, result);
    __builtin_memcpy(path, D_8007A5D4[index][1], sizeof(path));
    result = func_8002E6B0(path, 0x140, 0xFE);
    func_8005844C(target, result);
}
extern u8 *D_8007A5F4[][2];
void func_80071E3C(u8 *owner, s32 index) {
    u32 path[2];
    u8 *context;
    u8 *target;
    u8 *result;

    context = *(u8 **)(owner + 0x18);
    target = *(u8 **)(context + 8);
    __builtin_memcpy(path, D_8007A5F4[index][0], sizeof(path));
    result = func_8002E6B0(path, 0x170, 0);
    func_8005844C(target, result);
    __builtin_memcpy(path, D_8007A5F4[index][1], sizeof(path));
    result = func_8002E6B0(path, 0x140, 0xFD);
    func_8005844C(target, result);
}

s32 func_80071F14(s32 *arg0) {
    arg0[14] = 1;
    return 1;
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_80071F20);

extern u8 D_80065C48[];
extern s32 D_8005FC88;
extern s32 D_800641A4;
extern void func_8001F678();
void func_80072210(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x1C) = (s32)D_80065C48;
    func_8001BEDC(*(s32 *)(arg0 + 0x1134));
    {
        s32 s0 = D_800641A4;

        func_8001F678(s0, 0);
        func_8001F4BC((RenderContext *)s0, 0x140, 0xF0);
    }
    D_8005FC88 = (u32)*(u32 *)(arg0 + 0x6C) < 1;
    if (*(s32 *)(arg0 + 0x60) != 0) {
        func_8002D86C((void *)(u32)*(s32 *)(arg0 + 0x60), 3);
    }
    if (*(s32 *)(arg0 + 0x64) != 0) {
        func_8002D86C((void *)(u32)*(s32 *)(arg0 + 0x64), 3);
    }
    if (*(s32 *)(arg0 + 0x68) != 0) {
        func_8002D86C((void *)(u32)*(s32 *)(arg0 + 0x68), 3);
    }
    func_8001BCF8(D_8005F824);
    func_8001BCC4(D_8005F824);
    func_8001EAD4(((u8 *)&D_8005F884), 0);
    func_80020BFC(arg0 + 0x10EC, 2);
    func_8002BF88(arg0 + 0x50, 2);
    func_8002B770(arg0, arg1);
}

void func_80072320(u8 *arg0) {
    *(s16 *)(arg0 + 0x24) = 0x200;
    *(s16 *)(arg0 + 0x26) = 0xFD;
    *(s16 *)(arg0 + 0x4C) = 0;
    *(s16 *)(arg0 + 0x28) = 0x10;
    *(s16 *)(arg0 + 0x2A) = 1;
    func_80055B64(arg0 + 0x24, arg0 + 0x2C);
}

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_8007236C);

INCLUDE_ASM("asm/us/title/nonmatchings/A660", func_8007240C);

void func_80072814(u8 *arg0) {
    s32 v = *(s32 *)(arg0 + 0x74) + 1;

    *(s32 *)(arg0 + 0x74) = v;
    if (v >= 0x101) {
        *(s32 *)(arg0 + 0x74) = 0;
        *(s32 *)(arg0 + 0x1128) += 1;
    }
    func_8007374C();
}

extern void func_8002C244();

void func_80072860(u8 *arg0) {
    s32 x;

    if (*(s32 *)(arg0 + 0x74) == 0) {
        func_8002C244(arg0 + 0x50);
    }
    *(s32 *)(arg0 + 0x7C) = *(s32 *)(arg0 + 0x7C) + 3;
    if (*(s32 *)(arg0 + 0x7C) >= 0x100) {
        *(s32 *)(arg0 + 0x7C) = 0xFF;
    }
    switch (*(s16 *)(arg0 + 0x722)) {
    case 0:
        *(s32 *)(arg0 + 0x80) = (*(s32 *)(arg0 + 0x74) << 15) / 60 >> 1;
        if (*(s32 *)(arg0 + 0x80) < 0x1800) {
            break;
        }
        *(u16 *)(arg0 + 0x722) = *(u16 *)(arg0 + 0x722) + 1;
    case 1: {
        s32 t = *(s32 *)(arg0 + 0x74) - 23;
        s32 a = t * 2;
        s32 b = t * 4;

        *(s32 *)(arg0 + 0x80) = 0x1800 - ((b + a) * 8 + a) * 4;
        if (*(s32 *)(arg0 + 0x80) >= 0x1001) {
            break;
        }
        *(s32 *)(arg0 + 0x80) = 0x1000;
        *(u16 *)(arg0 + 0x722) = *(u16 *)(arg0 + 0x722) + 1;
    }
    case 2: {
        s32 t = *(s32 *)(arg0 + 0x74) - 34;
        s32 d = t * 46 + 0x80;
        u8 *p = ((u8 *)&D_8001093C);
        u8 *q = p + 2;

        *(s16 *)(arg0 + 0x724) = *(s16 *)(q + ((t << 12) & 0x3000)) / d;
        *(s16 *)(arg0 + 0x726) = *(s16 *)(q + ((t << 10) & 0x3C00)) / d;
        break;
    }
    }
    x = *(s32 *)(arg0 + 0x74);
    *(s32 *)(arg0 + 0x88) = x * 80 / 60;
    *(s32 *)(arg0 + 0x74) = x + 1;
    if (x >= 0x78) {
        *(s32 *)(arg0 + 0x74) = 0;
        *(s16 *)(arg0 + 0x724) = 0;
        *(s16 *)(arg0 + 0x726) = 0;
        *(s32 *)(arg0 + 0x1128) = *(s32 *)(arg0 + 0x1128) + 1;
    }
    func_8007374C(arg0);
}
