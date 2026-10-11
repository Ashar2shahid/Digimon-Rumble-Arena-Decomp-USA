#include "game_heap_wrappers.h"
#include "game_thread.h"
#include "game_sprite_cleanup.h"
#include "game_lerp_words.h"
#include "game_audio_api.h"
#include "common.h"
#include "game_printer_storage.h"
#include "iterator_object.h"
#include "game_input.h"
#include "resource_loader.h"
#include "game_formatter.h"
extern "C" {

s32  func_80068484();
void  func_80069028();
void  func_80069178();
void  func_80069364();
extern void func_8002B770();
extern s32 D_8007A630;
extern u8 *func_800280A0();
extern u8 *func_80028050();
extern void func_8005848C();
extern void func_8005844C(void *, void *);
extern u8 *func_8002DD5C();
extern u8 D_8005F824[];

extern void func_8002C530();
extern s32 D_8005F928;
extern u8 D_800644DC[];
extern void func_8002C6B0();
extern u8 D_800192A8[];
extern void func_8002B3D0();
extern s32 D_800641A4;
extern u8 D_800645F8[];
extern s32 func_8001F278();
extern s32 func_8001BCF8();
extern s32 func_8001BCC4();
extern void func_80068D8C();
extern s32 func_8006ABAC();
extern s32 D_80114210;
extern u8 D_800645C0[];
extern void func_8003EC6C(u8 *, u8 *, s32, s32);
extern u8 D_800645D4[];
extern void func_80068F30(s32 *arg0, void *arg1);
extern void func_80068DB4(s32 *arg0);
extern const u8 *func_8007A54C[];
extern u8 D_8007A564[];
extern void func_8002B3D0(void);
extern void func_80069614(u8 *, s32);
extern s32 func_80069994(s32 *);
extern u8 D_80064780[];
extern u8 D_8006478C[];
extern void func_800694A4(u8 *);
extern s32 func_80069AD4(s32 *);
extern s32 D_8005F81C;
extern void func_8006A680(s32 *, s32 *, s32);
extern void func_8006A964(s32 *, s32 *);
extern void func_80069DA4(u8 *, u8 *);
extern void func_8006A5C0(s32 *, s32 *, s32);
extern void func_8006A3F8(s32 *, s32 *);
extern void func_8006AA34(s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32);
extern void func_80069E70(s32 *, s32 *);
extern u8 *func_8006940C(u8 *);
extern u8 D_800647AC[];
extern s32 func_8006AD8C(s32 *, s32, s32);
extern u8 D_800647A8[];
extern void func_80068570(void *);
extern void func_800686A0(void *);
extern void func_80068B00(void *);
extern void func_8002B82C(void *);

s32 func_80068484(void) {
    s32 g = D_80114210;

    return (func_80027004(g, 0) | func_80027004(g, 1)) & 0x840;
}

extern u8 D_800645C0[];

void func_800684CC(void) {
    u8 *s0;

    s0 = func_80027C14(D_800645C0);
    func_80027B20(s0);
    func_8002B2B4(s0);
}

extern void func_8003EC6C(u8 *, u8 *, s32, s32);
extern u8 D_800645D4[];

void func_80068508(u8 *arg0, s32 arg1, s32 arg2) {
    u8 buf[0x20];
    u8 *p;
    u8 c;

    func_8003EC6C(buf, D_800645D4, arg2, arg1);
    c = buf[0];
    p = buf + 1;
    while (c != 0) {
        *arg0 = 0x82;
        arg0[1] = c + 0x1F;
        arg0 += 2;
        c = *p;
        p++;
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_80068570);

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_800686A0);

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_800688AC);

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_800689A0);

void func_80068AF8(void) {
}

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_80068B00);

void func_80068C68(s32 a0, s32 a1) {
    register s32 a2 asm("$6") = *(s32 *)(a0 + 0x1C);
    *(s32 *)(a0 + 0x20) = a1;
    (*(void (**)(s32))(a2 + 0x24))(a0 + *(s16 *)(a2 + 0x20));
}

extern void func_80068F30(s32 *arg0, void *arg1);
extern void func_80068DB4(s32 *arg0);
extern const u8 *func_8007A54C[];
extern u8 D_8007A564[];

s32 func_80068C9C(s32 *arg0, s32 arg1, s32 arg2) {
    s32 v;

    arg0[0x17] = 0;
    arg0[2] = arg1;
    arg0[3] = arg2;
    arg0[0x2F] = 0;
    arg0[0x2E] = 0;
    v = 0x20;
    if (arg1 == 0) {
        func_80068F30(arg0, func_8007A54C);
    } else {
        func_80068F30(arg0, D_8007A564);
    }
    *(s16 *)((u8 *)arg0 + 0x74) = v;
    *(s16 *)((u8 *)arg0 + 0x76) = 0x50;
    *(s16 *)((u8 *)arg0 + 0x78) = 0x100;
    *(s16 *)((u8 *)arg0 + 0x7A) = 0x73;
    *(s16 *)((u8 *)arg0 + 0x7C) = 0x25;
    *(s16 *)((u8 *)arg0 + 0x7E) = 0x55;
    *(s16 *)((u8 *)arg0 + 0x80) = 0xF6;
    *(s16 *)((u8 *)arg0 + 0x82) = 0x69;
    arg0[0x2B] = arg0[0x15] * 20 - 0xFC;
    if (arg0[0x2B] < 0) {
        arg0[0x2B] = 0;
    }
    arg0[0x2C] = arg0[0x16] * 20 - *(s16 *)((u8 *)arg0 + 0x7A) + 4;
    if (arg0[0x2C] < 0) {
        arg0[0x2C] = 0;
    }
    func_80068DB4(arg0);
    return (s32)arg0;
}

extern void func_8002B3D0(void);

void func_80068D8C(s32 arg0, s32 arg1) {
    if (arg1 & 1) {
        func_8002B3D0();
    }
}

extern void func_80069614(u8 *, s32);
extern s32 func_80069994(s32 *);

void func_80068DB4(s32 *arg0) {
    s32 a = *(s16 *)((u8 *)arg0 + 0x78) >> 1;

    arg0[0xF] = 0xA;
    arg0[0x24] = 0x400;
    arg0[0] = 0;
    arg0[1] = 0;
    arg0[4] = 0;
    *(u8 *)((u8 *)arg0 + 0x14) = 0;
    arg0[0xE] = 0;
    arg0[0x13] = 0;
    arg0[0x12] = 0;
    arg0[0x11] = 0;
    arg0[0x10] = 0;
    arg0[0x1A] = 0;
    arg0[0x19] = 0;
    arg0[0x18] = 0;
    arg0[0x17] = 0;
    arg0[0x1C] = 0;
    arg0[0x1B] = 0;
    arg0[0x2A] = 0;
    arg0[0x29] = 0;
    arg0[0x26] = 0;
    arg0[0x25] = 0;
    arg0[0x33] = 0;
    arg0[0x32] = 0;
    arg0[0x31] = 0;
    arg0[0x30] = 0;
    arg0[0x2D] = 0;
    arg0[0x27] = *(s16 *)((u8 *)arg0 + 0x74) + a;
    arg0[0x28] = *(s16 *)((u8 *)arg0 + 0x76) + (*(s16 *)((u8 *)arg0 + 0x7A) >> 1);
    func_80069614((u8 *)arg0, a);
    arg0[0x22] = func_80069994(arg0);
}

s32 func_80068E84(s32 *arg0) {
    func_80068DB4(arg0);
    arg0[0] = 1;
    return 1;
}

void func_80068EB0(s32 *arg0) {
    arg0[0] = 0;
}

extern u8 D_80064780[];

void func_80068EB8(void) {
    u8 *s0;

    s0 = func_80027C14(D_80064780);
    func_80027B20(s0);
    func_8002B2B4(s0);
}

extern u8 D_8006478C[];

void func_80068EF4(void) {
    u8 *s0;

    s0 = func_80027C14(D_8006478C);
    func_80027B20(s0);
    func_8002B2B4(s0);
}

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_80068F30);

extern void func_800694A4(u8 *);
extern s32 func_80069AD4(s32 *);

void func_80069028(s32 *arg0) {
    if (arg0[0] == 0) {
        return;
    }
    if (arg0[0x10] == 0) {
        func_8001EAB4(((u8 *)&D_8005F884), 0);
        func_8001EAD4(((u8 *)&D_8005F884), 0xA);
    }
    if (arg0[0xF] == 0) {
        func_800694A4((u8 *)arg0);
    } else {
        arg0[0xF]--;
        arg0[0x1C] = 0;
        arg0[0x1B] = 0;
    }
    if (arg0[1] == 0) {
        if (func_80069AD4(arg0)) {
            arg0[0xE] = 1;
            arg0[0xF] = 0x63;
        }
    }
    if (arg0[0xE] != 0) {
        if (--arg0[0xE] == 0) {
            arg0[1] = 1;
            arg0[0x11] = 0;
            func_8001EAB4(((u8 *)&D_8005F884), 0xA);
        }
    }
    if (arg0[1] != 0) {
        if (++arg0[0x11] >= 0xB) {
            arg0[0] = 0;
            func_8001EAD4(((u8 *)&D_8005F884), 0xA);
        }
    }
    if (arg0[0x13] != 0) {
        arg0[0x13]--;
    }
    arg0[0x10]++;
}

extern s32 D_8005F81C;
extern void func_8006A680(s32 *, s32 *, s32);
extern void func_8006A964(s32 *, s32 *);
extern void func_80069DA4(u8 *, u8 *);
extern void func_8006A5C0(s32 *, s32 *, s32);
extern void func_8006A3F8(s32 *, s32 *);
extern void func_8006AA34(s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32);
extern void func_80069E70(s32 *, s32 *);

void func_80069178(s32 *arg0) {
    s32 *p;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;

    if (arg0[0] == 0) {
        return;
    }
    p = (s32 *)(D_8005F81C + 0x14);
    if (arg0[0x13] != 0) {
        func_8006A680(arg0, p, arg0[0x12]);
    }
    func_8006A964(arg0, p);
    func_80069DA4((u8 *)arg0, (u8 *)p);
    func_8006A5C0(arg0, p, arg0[2]);
    func_8006A3F8(arg0, p);
    a = *(s16 *)((u8 *)arg0 + 0x74);
    b = *(s16 *)((u8 *)arg0 + 0x76);
    c = *(s16 *)((u8 *)arg0 + 0x78);
    d = *(s16 *)((u8 *)arg0 + 0x7A);
    e = a + c;
    f = b + d;
    func_8006AA34(arg0, p, a, arg0[0x28], e, arg0[0x28], 0x20, 0xA0, 0x20);
    func_8006AA34(arg0, p, arg0[0x27], b, arg0[0x27], f, 0x20, 0xA0, 0x20);
    func_80069E70(arg0, p);
}

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_800692AC);

extern u8 *func_8006940C(u8 *);
extern u8 D_800647AC[];
extern s32 func_8006AD8C(s32 *, s32, s32);

void func_80069364(s32 *arg0, s32 *arg1) {
    u8 *p = func_8006940C((u8 *)arg0);

    if (*p == 0) {
        p = D_800647AC;
    }
    func_8006AD8C(arg1, (s32)p, arg0[0x19]);
}

void func_800693B8(s32 *arg0, u8 *arg1) {
    u8 *d;

    arg0[4] = 0;
    d = (u8 *)arg0 + 0x14;
    if (*arg1) {
        do {
            *d++ = *arg1++;
            *d++ = *arg1++;
            arg0[4]++;
        } while (*arg1);
    }
    *d = 0;
}

u8 *func_8006940C(u8 *arg0) {
    return arg0 + 0x14;
}

void func_80069414(u8 *arg0, s32 arg1) {
    u8 *p = arg0 + 0x14;

    p += *(s32 *)(arg0 + 0x10) * 2;
    p[0] = arg1 >> 8;
    p++;
    p[0] = arg1;
    p[1] = 0;
    if (*(s32 *)(arg0 + 0x10) < *(s32 *)(arg0 + 0xC) - 1) {
        *(s32 *)(arg0 + 0x10) = *(s32 *)(arg0 + 0x10) + 1;
    }
}

void func_8006945C(u8 *arg0) {
    s32 idx = *(s32 *)(arg0 + 0x10);
    u8 *p = arg0 + 0x14;

    p += idx * 2;
    if (idx < *(s32 *)(arg0 + 0xC) - 1 || p[0] == 0) {
        if (idx > 0) {
            *(s32 *)(arg0 + 0x10) = idx - 1;
            p -= 2;
        }
    }
    *p = 0;
}

void func_800694A4(u8 *arg0) {
    s32 v = D_80114210;

    *(s32 *)(arg0 + 0x6C) = func_80026FE4(v, *(s32 *)(arg0 + 0x5C));
    *(s32 *)(arg0 + 0x70) = func_80027044(v, *(s32 *)(arg0 + 0x5C));
}

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_800694F4);

void func_80069608(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x48) = arg1;
    *(s32 *)(arg0 + 0x4C) = arg2;
}

void func_80069614(u8 *arg0, s32 arg1) {
    s32 t;

    t = *(s16 *)(arg0 + 0x7C) + 0x50;
    if (*(s32 *)(arg0 + 0x9C) < t) {
        if (*(s32 *)(arg0 + 0xA4) > 0) {
            *(s32 *)(arg0 + 0xA4) -= t - *(s32 *)(arg0 + 0x9C);
            *(s32 *)(arg0 + 0x9C) = t;
        }
    }
    t = *(s16 *)(arg0 + 0x7C) + *(s16 *)(arg0 + 0x80) - 0x50;
    if (t < *(s32 *)(arg0 + 0x9C)) {
        if (*(s32 *)(arg0 + 0xA4) < *(s32 *)(arg0 + 0xAC)) {
            *(s32 *)(arg0 + 0xA4) += *(s32 *)(arg0 + 0x9C) - t;
            *(s32 *)(arg0 + 0x9C) = t;
        }
    }
    t = *(s16 *)(arg0 + 0x7E) + 0x28;
    if (*(s32 *)(arg0 + 0xA0) < t) {
        if (*(s32 *)(arg0 + 0xA8) > 0) {
            *(s32 *)(arg0 + 0xA8) -= t - *(s32 *)(arg0 + 0xA0);
            *(s32 *)(arg0 + 0xA0) = t;
        }
    }
    t = *(s16 *)(arg0 + 0x7E) + *(s16 *)(arg0 + 0x82) - 0x28;
    if (t < *(s32 *)(arg0 + 0xA0)) {
        if (*(s32 *)(arg0 + 0xA8) < *(s32 *)(arg0 + 0xB0)) {
            *(s32 *)(arg0 + 0xA8) += *(s32 *)(arg0 + 0xA0) - t;
            *(s32 *)(arg0 + 0xA0) = t;
        }
    }
    if (*(s32 *)(arg0 + 0xA4) < 0) { *(s32 *)(arg0 + 0xA4) = 0; }
    if (*(s32 *)(arg0 + 0xA8) < 0) { *(s32 *)(arg0 + 0xA8) = 0; }
    if (*(s32 *)(arg0 + 0xA4) > *(s32 *)(arg0 + 0xAC)) { *(s32 *)(arg0 + 0xA4) = *(s32 *)(arg0 + 0xAC); }
    if (*(s32 *)(arg0 + 0xA8) > *(s32 *)(arg0 + 0xB0)) { *(s32 *)(arg0 + 0xA8) = *(s32 *)(arg0 + 0xB0); }
    if (*(s32 *)(arg0 + 0x9C) < *(s16 *)(arg0 + 0x7C)) { *(s32 *)(arg0 + 0x9C) = *(s16 *)(arg0 + 0x7C); }
    if (*(s32 *)(arg0 + 0xA0) < *(s16 *)(arg0 + 0x7E)) { *(s32 *)(arg0 + 0xA0) = *(s16 *)(arg0 + 0x7E); }
    if (*(s16 *)(arg0 + 0x7C) + *(s16 *)(arg0 + 0x80) < *(s32 *)(arg0 + 0x9C)) { *(s32 *)(arg0 + 0x9C) = *(s16 *)(arg0 + 0x7C) + *(s16 *)(arg0 + 0x80); }
    if (*(s16 *)(arg0 + 0x7E) + *(s16 *)(arg0 + 0x82) < *(s32 *)(arg0 + 0xA0)) { *(s32 *)(arg0 + 0xA0) = *(s16 *)(arg0 + 0x7E) + *(s16 *)(arg0 + 0x82); }
}

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_800697E8);

void func_800698B0(u8 *arg0) {
    s32 v = *(s32 *)(arg0 + 0x94);
    s32 w;

    *(s32 *)(arg0 + 0x3C) = 0x16;
    *(s32 *)(arg0 + 0xB4) = 0x1000;
    *(s32 *)(arg0 + 0xC0) = v * 20 + 0xA;
    *(s32 *)(arg0 + 0xC8) = v * 20 + 0xA;
    w = *(s32 *)(arg0 + 0x98);
    *(s32 *)(arg0 + 0xC4) = w * 20 + 0xA;
    *(s32 *)(arg0 + 0xCC) = w * 20 + 0xA;
}

void func_800698FC(s32 *arg0) {
    s32 n;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;

    y = arg0[0x2D] == 0;
    if (y) {
        return;
    }
    arg0[0x2D] -= 0x155;
    if (arg0[0x2D] < 0) {
        arg0[0x2D] = 0;
    }
    dx = arg0[0x30] - arg0[0x2E];
    dy = arg0[0x31] - arg0[0x2F];
    n = arg0[0x2D];
    x = arg0[0x2E] + ((dx * n) >> 12);
    y = arg0[0x2F] + ((dy * n) >> 12);
    arg0[0x27] += x - arg0[0x32];
    arg0[0x28] += y - arg0[0x33];
    arg0[0x32] = x;
    arg0[0x33] = y;
}

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_80069994);

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_80069AD4);

extern u8 D_800647A8[];

void func_80069DA4(u8 *arg0, u8 *arg1) {
    GlyphPrinterRecord storage;
    const PrinterCallbackTable *v0;
    s32 s0;

    func_8007A3BC((u8 *)&storage, arg1);
    v0 = storage.base.table;
    v0->setColor((u8 *)&storage + v0->colorAdjustment, 0x606060);
    storage.base.cursor[1] = 0x2F;
    s0 = 0xA0 - (*(s32 *)(arg0 + 0xC) << 4) / 2;
    storage.base.cursor[0] = s0;
    func_800327B0((u8 *)&storage, arg0 + 0x14);
    if (*(s32 *)(arg0 + 0x40) & 8) {
        storage.base.cursor[1] = 0x30;
        storage.base.cursor[0] = (*(s32 *)(arg0 + 0x10) << 4) + s0;
        func_800327B0((u8 *)&storage, D_800647A8);
    }
    func_8003277C((u8 *)&storage, 2);
}

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_80069E70);

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_8006A178);

extern u8 *func_8002DD5C();
extern void func_8005844C(void *, void *);

void func_8006A25C(u8 *arg0, u8 *arg1) {
    s32 xa = *(s16 *)(arg0 + 0x74);
    s32 v1 = *(s32 *)(arg0 + 0xA4) >> 1;
    s32 x0 = xa - (v1 % 0x40);
    s32 ya = *(s16 *)(arg0 + 0x76);
    s32 a1 = *(s32 *)(arg0 + 0xA8) >> 1;
    s32 y0 = ya - (a1 % 0x40);
    s32 x1 = xa + *(s16 *)(arg0 + 0x78);
    s32 y1 = ya + *(s16 *)(arg0 + 0x7A);
    s32 x;
    s32 y;

    for (y = y0; y < y1; y += 0x40) {
        for (x = x0; x < x1; x += 0x40) {
            u8 *p = func_8002DD5C();

            p[0x4] = 0x20;
            p[0x5] = 0x20;
            p[0x6] = 0x20;
            *(s16 *)(p + 0x8) = x;
            *(s16 *)(p + 0xA) = y;
            *(s16 *)(p + 0x10) = x + 0x40;
            *(s16 *)(p + 0x12) = y;
            *(s16 *)(p + 0x18) = x;
            *(s16 *)(p + 0x1A) = y + 0x40;
            *(s16 *)(p + 0x20) = x + 0x40;
            *(s16 *)(p + 0x22) = y + 0x40;
            p[0xC] = 0x80;
            p[0xD] = 0x20;
            p[0x14] = 0xBF;
            p[0x15] = 0x20;
            p[0x1C] = 0x80;
            p[0x1D] = 0x5F;
            p[0x24] = 0xBF;
            p[0x25] = 0x5F;
            *(s16 *)(p + 0x16) = 0xC;
            *(s16 *)(p + 0xE) = 0x3C28;
            func_8005844C(arg1, p);
        }
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_8006A3F8);

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_8006A5C0);

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_8006A680);

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_8006A784);

INCLUDE_ASM("asm/us/title/nonmatchings/40C4", func_8006A874);
}
