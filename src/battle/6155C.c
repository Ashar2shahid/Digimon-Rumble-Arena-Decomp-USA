#include "game_sprite_cleanup.h"
#include "game_collision_forwarders.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_effect_constructor.h"
#include "game_positions.h"

extern u8 D_800D3A78;
extern u8 D_800D3A7C;
extern u8 D_8006D58C[];
extern u8 D_8006D564[];
extern u8 D_8006D53C[];
extern u8 D_8006D514[];
extern u8 D_8006D4EC[];
extern u8 D_8006D4C4[];
extern u8 D_8006D49C[];
extern u8 D_8006DB90[];
extern u8 D_800641B8;
extern s32 D_80010814[];

extern s32 func_8007B150(u8 *);
extern s32 func_80079518(u8 *);
extern s32 func_8002BD68(s32);
extern void func_8002BCEC(u8 *, s32);
extern void func_8002BDA8(u8 *);
extern s32 func_800C2F68(s32, s32, s32);

extern s32 func_80053EFC(s32, s32);
extern s32 func_8002BE14(s32);
extern void func_8007AFCC(s32, s32);
extern void func_800CA6EC(s32, s32, s32);
extern void func_800CAA24(s32, s32, s32);
extern void func_800CAD88(s32, s32, s32, s32, s32, s32);
extern void func_800CB1AC(s32, s32, s32, s32);
extern void func_8002BF34(s32, s32);
extern void func_8006F06C(s32, s32);
extern void func_800C7710(s32, s32);
extern s32 func_80078AD8(s32);
extern u8 *func_800C6588(u8 *, s32, s32 *, s32, s32, s32, s32);
extern u8 *func_800C8588(u8 *, s32, s32, s32);
extern s32 func_80073010(s32, s32);
extern s32 func_8007A0A0(s32);
extern void func_800C7644(s32, s32);
extern s32 func_800C75F4(s32);
extern void func_800C5AD0(u8 *);
extern void func_800C5C70(u8 *);
extern void func_800C9544(void);
extern void func_800C93FC(void);
INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C591C);

void func_800C5A14(u8 *self, s32 opaque) {
    s32 timer = (s32)((u32)*(s32 *)(self + 0x24) - 1u);
    *(s32 *)(self + 0x24) = timer;
    if (timer < 0) {
        s32 count = (s32)((u32)*(s32 *)(self + 0x20) - 1u);
        *(s32 *)(self + 0x20) = count;
        if (count < 3) {
            if (self != 0) {
                u8 *vtable = *(u8 **)(self + 0x14);
                void (*destructor)(u8 *, s32) = *(void (**)(u8 *, s32))(vtable + 0x1C);
                destructor(self + *(s16 *)(vtable + 0x18), 3);
            }
            return;
        }
    } else {
        func_800C5AD0(self);
        if (func_8007B150(*(u8 **)(self + 0x18)) ||
            func_80079518(*(u8 **)(self + 0x18)) == 0x13) {
            *(s32 *)(self + 0x24) = 0;
        }
    }
    func_800C5C70(self);
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C5AD0);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C5C70);

void func_800C5DB4(s32 a0, u8 *a1, s32 a2) {
    register u8 *dst asm("$7"); /* PIN $a3 */
    if (a2 >= 5) {
        a2 = 4;
    }
    *(s32 *)(a0 + 0x2C) = a2;
    if (a2 <= 0) {
        return;
    }
    dst = (u8 *)(a0 + 0x30);
    do {
        s32 v1, v2, v3;
        a1 += 0x18;
        *(s32 *)(dst + 0x0) = *(s32 *)(a1 - 0x18);
        v1 = *(s32 *)(a1 - 0x14);
        v2 = *(s32 *)(a1 - 0x10);
        v3 = *(s32 *)(a1 - 0xC);
        a2--;
        *(s32 *)(dst + 0x4) = v1;
        *(s32 *)(dst + 0x8) = v2;
        *(s32 *)(dst + 0xC) = v3;
        __builtin_memcpy(dst + 0x14, a1 - 4, 4);
        dst += 0x18;
    } while (a2 != 0);
}

void func_800C5E20(s32 a0, u8 *a1, s32 a2) {
    register s32 count asm("$3"); /* PIN $v1 */
    register s32 remaining asm("$2"); /* PIN $v0 */
    u8 *dst;
    count = *(s32 *)(a0 + 0x2C);
    if (count > a2) {
        count = a2;
    }
    if (count <= 0) {
        return;
    }
    dst = (u8 *)(a0 + 0x44);
    remaining = count;
    do {
        __builtin_memcpy(dst, a1, 4);
        a1 += 4;
        remaining--;
        dst += 0x18;
    } while (remaining != 0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C5E70);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C5EE8);

extern u8 D_8006D304[];
extern u8 D_8006D2DC[];
extern u8 D_8006D2B4[];
extern u8 D_8006D28C[];

u8 *func_800C6090(u8 *a0, s32 a1, s32 *a2, s32 *a3, s32 p4, s32 p5, s32 p6) {
    register s32 a4 asm("$20") = p4;  /* retail: stack args land in s4/s5/s6 */
    register s32 a5 asm("$21") = p5;
    register s32 a6 asm("$22") = p6;
    register s32 t0 asm("$2");        /* retail loads a2[0..2] into v0/v1/a0 */
    register s32 t1 asm("$3");
    s32 t2, t3, t4, t5;
    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    *(u8 **)(a0 + 0x14) = D_8006D304;
    *(s32 *)(a0 + 0x18) = a1;
    t0 = a2[0]; t1 = a2[1]; t2 = a2[2];
    *(s32 *)(a0 + 0x1C) = t0;
    *(s32 *)(a0 + 0x20) = t1;
    *(s32 *)(a0 + 0x24) = t2;
    t3 = a3[0]; t4 = a3[1]; t5 = a3[2];
    *(s32 *)(a0 + 0x2C) = t3;
    *(s32 *)(a0 + 0x30) = t4;
    *(s32 *)(a0 + 0x34) = t5;
    *(s32 *)(a0 + 0x3C) = a4;
    *(s32 *)(a0 + 0x40) = a5;
    *(s32 *)(a0 + 0x44) = a6;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C6150);

u8 *func_800C6324(u8 *a0, s32 a1, s32 *a2, s32 p3, s32 p4, s32 p5, s32 p6) {
    register s32 a3 asm("$19") = p3;  /* retail: a3 + stack args map to s3..s6 */
    register s32 a4 asm("$20") = p4;
    register s32 a5 asm("$21") = p5;
    register s32 a6 asm("$22") = p6;
    s32 t0, t1, t2;
    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    *(u8 **)(a0 + 0x14) = D_8006D2DC;
    *(s32 *)(a0 + 0x18) = a1;
    t0 = a2[0]; t1 = a2[1]; t2 = a2[2];
    *(s32 *)(a0 + 0x1C) = t0;
    *(s32 *)(a0 + 0x20) = t1;
    *(s32 *)(a0 + 0x24) = t2;
    *(s32 *)(a0 + 0x2C) = a3;
    *(s32 *)(a0 + 0x30) = a4;
    *(s32 *)(a0 + 0x34) = a5;
    *(s32 *)(a0 + 0x38) = a6;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C63D0);

u8 *func_800C6588(u8 *a0, s32 a1, s32 *a2, s32 p3, s32 p4, s32 p5, s32 p6) {
    register s32 a3 asm("$19") = p3;
    register s32 a4 asm("$20") = p4;
    register s32 a5 asm("$21") = p5;
    register s32 a6 asm("$22") = p6;
    s32 t0, t1, t2;
    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    *(u8 **)(a0 + 0x14) = D_8006D2B4;
    *(s32 *)(a0 + 0x18) = a1;
    t0 = a2[0]; t1 = a2[1]; t2 = a2[2];
    *(s32 *)(a0 + 0x1C) = t0;
    *(s32 *)(a0 + 0x20) = t1;
    *(s32 *)(a0 + 0x24) = t2;
    *(s32 *)(a0 + 0x2C) = a3;
    *(s32 *)(a0 + 0x30) = a4;
    *(s32 *)(a0 + 0x34) = a5;
    *(s32 *)(a0 + 0x38) = a6;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C6634);

u8 *func_800C67C8(u8 *a0, s32 a1, s32 *a2, s32 p3, s32 p4, s32 p5, s32 p6) {
    register s32 a3 asm("$19") = p3;
    register s32 a4 asm("$20") = p4;
    register s32 a5 asm("$21") = p5;
    register s32 a6 asm("$22") = p6;
    s32 t0, t1, t2;
    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    *(u8 **)(a0 + 0x14) = D_8006D28C;
    *(s32 *)(a0 + 0x18) = a1;
    t0 = a2[0]; t1 = a2[1]; t2 = a2[2];
    *(s32 *)(a0 + 0x1C) = t0;
    *(s32 *)(a0 + 0x20) = t1;
    *(s32 *)(a0 + 0x24) = t2;
    *(s32 *)(a0 + 0x2C) = a3;
    *(s32 *)(a0 + 0x30) = a4;
    *(s32 *)(a0 + 0x34) = a5;
    *(s32 *)(a0 + 0x38) = a6;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C6874);

s32 func_800C6A5C(s32 *a0) {
    return a0[0];
}

void func_800C6A68(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

u8 *func_800C6ABC(u8 *a0, s32 a1, s32 a2) {
    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    func_800C2F68((s32)(a0 + 0x18), a1, a2);
    *(u8 **)(a0 + 0x14) = D_8006D58C;
    return a0;
}

void func_800C6B1C(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

u8 *func_800C6B70(u8 *self, s32 kind, s32 *first, s32 *second, s32 value1, s32 value2) {
    func_800C3258(self, kind, first, second, value1, value2, 0);
    *(u8 **)(self + 0x14) = D_8006D564;
    return self;
}

u8 *func_800C6BB8(u8 *self, s32 *first, s32 *second, s32 value, s32 kind) {
    func_800C3258(self, kind, first, second, value, 0x808080, 0);
    *(u8 **)(self + 0x14) = D_8006D564;
    return self;
}

void func_800C6C0C(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

u8 *func_800C6C60(u8 *self, s32 *first, s32 *second, s32 value, s32 kind) {
    func_800C3258(self, (s32)((u32)kind + 3u), first, second, value, 0x808080, 0);
    *(u8 **)(self + 0x14) = D_8006D53C;
    return self;
}

void func_800C6CBC(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

u8 *func_800C6D10(u8 *self, s32 *first, s32 *second, s32 value1, s32 value2) {
    func_800C3258(self, 6, first, second, value1, value2, 0);
    *(u8 **)(self + 0x14) = D_8006D514;
    return self;
}

void func_800C6D64(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D4EC;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C6DB8(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D58C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

u8 *func_800C6E0C(u8 *self, s32 *first, s32 value1, s32 value2) {
    func_800C3258(self, 8, first, D_80010814, value1, value2, 0);
    *(u8 **)(self + 0x14) = D_8006D4C4;
    return self;
}

void func_800C6E5C(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D49C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C6EB0(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D49C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C6F04(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006D49C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C6F58(s32 a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C6FA0(s32 a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C6FE8(u8 *a0, s32 a1) {
    func_8002D86C(a0 + 0x28, 2);
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C7040(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C7088(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C70D0(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C7118(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C7160(s32 a0) {
    if (*(s32 *)(a0 + 0x24) > 0) {
        func_800C5AD0((u8 *)(u32)a0);
        func_800C5C70((u8 *)(u32)a0);
    }
}

void func_800C71A0(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C71E8(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C7230(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800C7278(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C72C0);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C7478);

void func_800C7574(s32 a0, s32 a1) {
    func_8007C0C8((u8 *)(u32)a0 + 0x18, (u8 *)(u32)a1);
    func_800C7644(a0, func_800C75F4(a0));
    func_800C7710(a0, func_80078AD8(a1));
    if (a0 != 0) {
        s32 v0 = *(s32 *)(a0 + 0x14);
        ((void (*)(s32, s32))(*(s32 *)(v0 + 0x1C)))(a0 + *(s16 *)(v0 + 0x18), 3);
    }
}

s32 func_800C75F4(s32 a0) {
    s32 v;
    v = *(s32 *)(a0 + 0xA0);
    switch (v) {
    case 0:
    case 1:
        return 3;
    case 2:
        return 4;
    case 3:
        return 5;
    }
    return 3;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C7644);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C7710);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C7898);

extern u8 D_8006D730;
extern u8 D_8006D750;
extern u8 D_80065174;
extern u8 D_80065154;

void func_800C79B0(void *arg0, s32 arg1) {
    u8 *node;
    u32 next, previous, value;

    *(void **)((u8 *)arg0 + 0x18) = &D_8006D730;
    *(void **)((u8 *)arg0 + 0x14) = &D_8006D750;
    *(void **)((u8 *)arg0 + 0x68) = &D_80065174;
    node = (u8 *)arg0 + 0x38;
    next = *(u32 *)((u8 *)arg0 + 0x38);
    previous = *(u32 *)((u8 *)arg0 + 0x3C);
    *(u32 *)(next + 4) = previous;
    next = *(u32 *)(node + 4);
    value = *(u32 *)((u8 *)arg0 + 0x38);
    *(u32 *)(next + 0) = value;
    *(u32 *)((u8 *)arg0 + 0x38) = (u32)node;
    *(u32 *)((u8 *)arg0 + 0x3C) = (u32)node;
    *(void **)((u8 *)arg0 + 0x18) = &D_80065154;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800C7A50(void) {
}

u8 *func_800C7A58(void) {
    return &D_800D3A78;
}

void func_800C7A64(s32 a0, s32 a1, s32 a2) {
    s32 s0 = func_8002BE14(0x3C);
    if (s0 != 0) {
        func_800C8588((u8 *)func_8002BD80(0x3C, (void *)(u32)s0), a0, a1, a2);
    }
    func_8006F06C(a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C7AE0);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C7BC0);

void func_800C7DCC(s32 a0, s32 a1) {
    s32 s0 = func_8002BE14(0x24);
    if (s0 != 0) {
        func_800CA6EC((s32)(u32)func_8002BD80(0x24, (void *)(u32)s0), a0, a1);
    }
    func_8007AFCC(a0, s0);
}

void func_800C7E38(s32 a0, s32 a1) {
    s32 s0 = func_8002BE14(0x30);
    if (s0 != 0) {
        func_800CAA24((s32)(u32)func_8002BD80(0x30, (void *)(u32)s0), a0, a1);
    }
    func_8007AFCC(a0, s0);
}

void func_800C7EA4(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    s32 s0 = func_8002BE14(0x48);
    if (s0 != 0) {
        func_800CAD88((s32)(u32)func_8002BD80(0x48, (void *)(u32)s0), a0, a1, a2, a3, a4);
    }
    func_8007AFCC(a0, s0);
}

void func_800C7F38(s32 a0, s32 a1, s32 a2) {
    register s32 s1 asm("$17"); /* PIN $s1 */
    register s32 s2 asm("$18"); /* PIN $s2 */
    s32 buf[4];
    s32 s0;
    s1 = a0;
    s2 = a2;
    func_8007A8D0((u8 *)a0, (u8 *)buf);
    s0 = func_8002BE14(0x54);
    if (s0 != 0) {
        func_800CB1AC((s32)(u32)func_8002BD80(0x54, (void *)(u32)s0), (s32)buf, 0x100, s2);
    }
    func_8007AFCC(s1, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C7FB0);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C80B8);

s32 func_800C81B0(s32 a0, s32 a1) {
    s32 a = *(s32 *)a1;
    s32 b = *(s32 *)(a1 + 4);
    s32 c = *(s32 *)(a0 + 4);
    s32 d = *(s32 *)a0;
    return func_80053EFC(b - c, a - d) & 0xFFF;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C81E4);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C82A4);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C83D8);

u8 *func_800C8588(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *entry;
    s32 count;

    func_8002BC9C((u8 *)(u32)(s32)arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_8006DB90;
    *(u8 **)(arg0 + 0x24) = &D_800D3A78;
    *(s32 *)(arg0 + 0x18) = arg1;
    *(s32 *)(arg0 + 0x1C) = arg2;
    *(s32 *)(arg0 + 0x20) = arg3;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s32 *)(arg0 + 0x30) = 0x5A;
    *(s32 *)(arg0 + 0x34) = 0x12C;
    *(s32 *)(arg0 + 0x38) = 0;
    *(s32 *)&D_800D3A78 = 0;
    entry = *(u8 **)(arg0 + 0x24) + 0x7C;
    count = 0xF;
    do {
        *entry = 0;
        count -= 1;
        entry -= 8;
    } while (count >= 0);
    func_800C8784((s32)arg0);
    return arg0;
}

void func_800C863C(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006DB90;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C8690);

void func_800C8784(s32 a0) {
    u8 *p = *(u8 **)(a0 + 0x1C);
    *(s32 *)(a0 + 0x28) = 0;
    if (p == 0) {
        return;
    }
    if (*(s16 *)p != -1) {
        do {
            *(s32 *)(a0 + 0x28) += 1;
        } while (*(s16 *)(p + *(s32 *)(a0 + 0x28) * 10) != -1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C87DC);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C8880);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C8914);

u8 *func_800C89A0(s32 a0, s32 a1) {
    s32 a2;
    u8 *v0;
    *(s32 *)(a0 + 0x30) = 0x5A;
    a2 = *(s32 *)(a0 + 0x24);
    *(s32 *)a2 -= 1;
    v0 = (u8 *)(*(s32 *)(a0 + 0x24) + (*(s32 *)(a1 + 0x8C) << 3));
    v0[4] = 0;
    return v0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C89D4);

void func_800C8A10(u8 *adapter, u8 *collider) {
    func_800C90B8(*(u8 **)(adapter + 4), collider);
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C8A34);

extern u8 D_8006DB40;

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C8BDC);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C8C70);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C8DC8);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C8EFC);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C8F8C);

void func_800C90B8(u8 *self, u8 *collider) {
    u8 *table = *(u8 **)(self + 0x14);
    s16 adjustment = *(s16 *)(table + 0x20);
    void (*callback)(u8 *, u8 *) = *(void (**)(u8 *, u8 *))(table + 0x24);
    callback((u8 *)((u32)self + (u32)(s32)adjustment), collider);
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C90EC);

s32 func_800C91C0(s32 a0, s32 a1) {
    s32 v = *(s32 *)(a1 + 0x14);
    if (v == 0) {
        return 0;
    }
    return func_8002BD68(v);
}

void func_800C91F0(s32 a0) {
    s32 v0 = *(s32 *)(a0 + 0x38);
    *(s32 *)(a0 + 0x7C) = 0;
    *(s32 *)(a0 + 0x80) = 0;
    *(s32 *)(a0 + 0x84) = 0;
    *(s32 *)(a0 + 0x88) = 0;
    if (v0 > 0) {
        *(s32 *)(a0 + 0x7C) = 0x133;
    }
    if (*(s32 *)(a0 + 0x38) < 0) {
        *(s32 *)(a0 + 0x7C) = -0x133;
    }
    *(s32 *)(a0 + 0x38) = 0;
    *(s32 *)(a0 + 0x3C) = 0;
    *(s32 *)(a0 + 0x40) = 0;
    *(s32 *)(a0 + 0x44) = 0;
}

s32 func_800C9238(s32 a0, s32 a1) {
    return func_8007B150((u8 *)(u32)a1) ^ 1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C9258);

void func_800C92F0(s32 a0) {
    if (*(s32 *)(a0 + 0xA4) != 0) {
        u8 *p = (u8 *)((*(s32 *)(a0 + 0x8C) << 3) + (s32)&D_800D3A7C);
        *(u16 *)(p + 2) = *(u16 *)(a0 + 0x6C);
        *(u16 *)(p + 4) = *(u16 *)(a0 + 0x70);
        *(u16 *)(p + 6) = *(u16 *)(a0 + 0x74);
    }
}

void func_800C933C(s32 a0, s32 a1) {
    u8 mask = a1;
    if (*(s32 *)(a0 + 0xA4) != 0) {
        register u8 *base asm("$4") = &D_800D3A78; /* PIN $a0 */
        u8 *p = base + (*(s32 *)(a0 + 0x8C) << 3);
        p[4] |= mask;
    }
}

void func_800C937C(s32 a0, s32 a1) {
    u8 mask = a1;
    if (*(s32 *)(a0 + 0xA4) != 0) {
        register u8 *base asm("$3") = &D_800D3A78; /* PIN $v1 */
        u8 *p = base + (*(s32 *)(a0 + 0x8C) << 3);
        p[4] &= ~mask;
    }
}

void func_800C93B8(s32 a0) {
    if (*(s32 *)(a0 + 0x68) < 0xB) {
        func_800C9544();
    } else {
        func_800C93FC();
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C93FC);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C9544);

INCLUDE_ASM("asm/us/game/nonmatchings/6155C", func_800C9780);
