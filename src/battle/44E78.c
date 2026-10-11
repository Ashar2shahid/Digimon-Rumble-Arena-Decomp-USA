#include "game_action_api.h"
#include "game_placement_api.h"
#include "game_audio_api.h"
#include "game_collision_api.h"
#include "common.h"
#include "game_actor_queries.h"

s32 func_8007B0B4();
void func_8002BCEC();
void func_8002BDA8();
void func_80077774();
void func_800ABAE8();
void func_800AC92C();
void func_800ACF1C();
void func_8007BCA0();
void func_80079D58();
s32 func_800787A0();
void func_8001BEDC();

s32 func_80078AD8();
void func_800A64D8();
void func_8007BEC0();
s32 func_8007A084();
s32 func_8002BE14();
void func_8002BF34();
s32 func_800C6588();
s32 func_800AD874();
extern u8 D_8006AFFC[];
extern u8 D_8005F824[];
extern u8 D_8006B4B4[];
extern u8 D_80065154[];
extern u8 D_80065174[];
extern u8 D_8006AE7C[];
extern u8 D_8006AE9C[];
extern u8 D_8006AF1C[];
extern u8 D_8006AF3C[];
extern u8 D_8006AFB4[];
extern u8 D_8006AFD4[];
extern u8 D_8006B34C[];
extern u8 D_8006B36C[];
extern u8 D_8006B3DC[];
extern u8 D_8006B3FC[];
extern u8 D_8006B424[];
extern u8 D_8006B444[];
extern u8 D_8006B46C[];
extern u8 D_8006B48C[];

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800A9238);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800A9524);

void func_800A96E0(u8 *arg0, s32 arg1) {
    u8 *s1;
    s32 s0;
    u8 *p;
    u8 *a2;
    u8 *a0v;

    s1 = arg0;
    s0 = arg1;
    *(u32 *)(s1 + 0x18) = (u32)&D_8006AE7C;
    *(u32 *)(s1 + 0x14) = (u32)&D_8006AE9C;
    func_8001BEDC(*(u32 *)(s1 + 0xD4));
    p = s1 + 0x38;
    a2 = *(u8 **)(s1 + 0x38);
    a0v = *(u8 **)(s1 + 0x3C);
    *(u32 *)(s1 + 0x68) = (u32)&D_80065174;
    *(u32 *)(a2 + 4) = (u32)a0v;
    a2 = *(u8 **)(p + 4);
    *(u32 *)(a2 + 0) = *(u32 *)(s1 + 0x38);
    *(u32 *)(s1 + 0x38) = (u32)p;
    *(u32 *)(s1 + 0x3C) = (u32)p;
    *(u32 *)(s1 + 0x18) = (u32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800A9788(u8 *arg0) {
    s32 v = func_8001BE78((s32)(u32)&D_8005F824, 0xD4, 0);
    *(s32 *)(arg0 + 0xD4) = v;
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800A97C0);

void func_800A9BFC(u8 *arg0, u8 *arg1) {
    u8 *s1 = arg0;
    func_8007C0C8(s1 + 0x18, arg1);
    if (func_80078AD8(arg1)) {
        *(s32 *)(s1 + 0xB4) = *(s32 *)(s1 + 0xB4) >> 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800A9C50);

typedef struct AA304Vector {
    s32 x;
    s32 y;
    s32 z;
} AA304Vector;

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800A9F04);

void func_800A9FC4(u8 *arg0) {
    s32 v1;
    u8 *v0;
    register u32 fn asm("$3");       /* PIN $v1 - virtual-call target */
    v1 = *(s32 *)(arg0 + 0x38);
    v1 = v1 + ((0x804 - v1) >> 2);
    *(s32 *)(arg0 + 0x38) = v1;
    if (v1 >= 0x800) {
        if (arg0 != 0) {
            v0 = *(u8 **)(arg0 + 0x14);
            fn = *(u32 *)(v0 + 0x1C);
            ((void (*)(u8 *, s32))fn)((u8 *)(arg0 + *(s16 *)(v0 + 0x18)), 3);
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AA028);

void func_800AA274(u8 *arg0, s32 arg1) {
    func_80077774(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800AA2BC(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

AA304Vector *func_800AA304(u8 *self, AA304Vector *out) {
    s32 x = *(s32 *)(self + 0x20);
    s32 y = *(s32 *)(self + 0x24);
    s32 z = *(s32 *)(self + 0x28);
    out->x = x;
    out->y = y;
    out->z = z;
    return out;
}

void func_800AA324(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

u8 *func_800AA36C(u8 *arg0) {
    u8 *s0 = arg0;
    register u8 *v1 asm("$3");       /* PIN $v1 - vtable address temp */
    func_800A64D8();
    v1 = D_8006AFFC;
    *(u8 **)(s0 + 0x14) = v1;
    return s0;
}

void func_800AA3A0(u8 *arg0, s32 arg1) {
    u8 *s1;
    u8 *p;
    u8 *a2;
    u8 *a0v;

    s1 = arg0;
    p = s1 + 0x38;
    a2 = *(u8 **)(s1 + 0x38);
    a0v = *(u8 **)(s1 + 0x3C);
    *(u32 *)(s1 + 0x18) = (u32)&D_8006AFB4;
    *(u32 *)(s1 + 0x14) = (u32)&D_8006AFD4;
    *(u32 *)(s1 + 0x68) = (u32)&D_80065174;
    *(u32 *)(a2 + 4) = (u32)a0v;
    a2 = *(u8 **)(p + 4);
    *(u32 *)(a2 + 0) = *(u32 *)(s1 + 0x38);
    *(u32 *)(s1 + 0x38) = (u32)p;
    *(u32 *)(s1 + 0x3C) = (u32)p;
    *(u32 *)(s1 + 0x18) = (u32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (arg1 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800AA440(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800AA488(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800AA4D0(u8 *arg0, s32 arg1) {
    u8 *s1;
    u8 *p;
    u8 *a2;
    u8 *a0v;

    s1 = arg0;
    p = s1 + 0x38;
    a2 = *(u8 **)(s1 + 0x38);
    a0v = *(u8 **)(s1 + 0x3C);
    *(u32 *)(s1 + 0x18) = (u32)&D_8006AF1C;
    *(u32 *)(s1 + 0x14) = (u32)&D_8006AF3C;
    *(u32 *)(s1 + 0x68) = (u32)&D_80065174;
    *(u32 *)(a2 + 4) = (u32)a0v;
    a2 = *(u8 **)(p + 4);
    *(u32 *)(a2 + 0) = *(u32 *)(s1 + 0x38);
    *(u32 *)(s1 + 0x38) = (u32)p;
    *(u32 *)(s1 + 0x3C) = (u32)p;
    *(u32 *)(s1 + 0x18) = (u32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (arg1 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800AA570(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800AA5B8(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800AA600(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

u8 *func_800AA648(u8 *arg0) {
    u8 *s0 = arg0;
    func_80076FD8(s0);
    *(u8 **)(s0 + 0x14) = D_8006B4B4;
    *(u32 *)(s0 + 0x4A4) = 0;
    return s0;
}

void func_800AA680(u8 *arg0, s32 arg1) {
    u8 *s1 = arg0;
    u8 *v0 = D_8006B4B4;
    *(u8 **)(s1 + 0x14) = v0;
    func_80077774(s1, 0);
    if (arg1 & 1) {
        func_8002BDA8(s1);
    }
}

s32 func_800AA6D4(u8 *arg0) {
    return func_8007B0B4((s32)func_8007B16C(arg0));
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AA6FC);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AA90C);

void func_800AACA8(u8 *arg0, s32 arg1) {
    u8 *s0 = arg0;
    s32 s1 = arg1;
    func_8007BCA0(arg0, arg1);
    func_80079D58(s0);
    if (s1 == 0) {
        func_80078754(s0, 0xDF);
    }
    if (s1 == 7) {
        func_800AAE04(s0, -0x15);
        func_800787A0(s0, 0xDB);
    }
    if (s1 < 8) {
        *(s32 *)(s0 + 0x3B4) = *(s32 *)(s0 + 0x3B4) + ((-*(s32 *)(s0 + 0x3A4)) >> 4);
    }
}

void func_800AAD3C(u8 *arg0, s32 arg1) {
    u8 *s0 = arg0;
    s32 s1 = arg1;
    func_8007BEC0(arg0, arg1);
    func_80079D58(s0);
    if (s1 == 0) {
        func_80078754(s0, 0xDF);
        func_800787A0(s0, 0xDB);
    }
    if (s1 == 7) {
        func_800AAE04(s0, 0);
        *(s32 *)(s0 + 0x3B4) = *(s32 *)(s0 + 0x3B4) - ((func_8007A084(s0) * 3) << 12);
    }
    if (s1 < 8) {
        *(s32 *)(s0 + 0x3B4) = *(s32 *)(s0 + 0x3B4) - (*(s32 *)(s0 + 0x3A4) >> 3);
        if (*(s32 *)(s0 + 0x3A8) > 0) {
            *(s32 *)(s0 + 0x3B8) = *(s32 *)(s0 + 0x3B8) - *(s32 *)(s0 + 0x3A8);
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AAE04);

void func_800AAF78(u8 *s1, s32 s2) {
    register s32 s0 asm("$16");
    register s32 v1 asm("$3");
    register s32 v0 asm("$2");
    register s32 a0 asm("$4");

    func_8007BD08();
    func_80079D58(s1);
    if (s2 == 0) {
        func_800774EC(s1, -0x10000);
        func_80078754(s1, 0xE1);
        v1 = 0xA;
        *(s32 *)(s1 + 0x498) = v1;
    }
    if (s2 == 0x13) {
        *(s32 *)(s1 + 0x4A8) = func_800787A0(s1, 0xDB);
    }
    s0 = s2 - 0x13;
    if (s2 == 0x47) {
        a0 = *(s32 *)(s1 + 0x4A8);
        if (a0 != 0) {
            func_8001BEDC();
        }
    }
    if ((u32)s0 < (u32)0x34) {
        if (s2 & 1) {
            func_800AB068(s1, s2);
        }
        func_800AB354(s1, s0);
        v0 = s2 & 7;
        if (v0 == 0) {
            func_800AB1E8(s1, s0);
            func_800AB7A4(s1, s2 >> 3);
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AB068);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AB1E8);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AB354);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AB7A4);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AB8E8);

void func_800ABA48(u8 *arg0, s32 arg1) {
    u8 *s1;
    u8 *p;
    u8 *a2;
    u8 *a0v;

    s1 = arg0;
    p = s1 + 0x38;
    a2 = *(u8 **)(s1 + 0x38);
    a0v = *(u8 **)(s1 + 0x3C);
    *(u32 *)(s1 + 0x18) = (u32)&D_8006B46C;
    *(u32 *)(s1 + 0x14) = (u32)&D_8006B48C;
    *(u32 *)(s1 + 0x68) = (u32)&D_80065174;
    *(u32 *)(a2 + 4) = (u32)a0v;
    a2 = *(u8 **)(p + 4);
    *(u32 *)(a2 + 0) = *(u32 *)(s1 + 0x38);
    *(u32 *)(s1 + 0x38) = (u32)p;
    *(u32 *)(s1 + 0x3C) = (u32)p;
    *(u32 *)(s1 + 0x18) = (u32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (arg1 & 1) {
        func_8002BDA8(s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800ABAE8);

void func_800ABCAC(u8 *arg0, u8 *collider) {
    func_8007C0C8(arg0 + 0x18, collider);
    func_800ABAE8(arg0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800ABCDC);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800ABE0C);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800ABFC0);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AC124);

void func_800AC298(u8 *arg0, s32 arg1) {
    u8 *s1;
    u8 *p;
    u8 *a2;
    u8 *a0v;

    s1 = arg0;
    p = s1 + 0x38;
    a2 = *(u8 **)(s1 + 0x38);
    a0v = *(u8 **)(s1 + 0x3C);
    *(u32 *)(s1 + 0x18) = (u32)&D_8006B424;
    *(u32 *)(s1 + 0x14) = (u32)&D_8006B444;
    *(u32 *)(s1 + 0x68) = (u32)&D_80065174;
    *(u32 *)(a2 + 4) = (u32)a0v;
    a2 = *(u8 **)(p + 4);
    *(u32 *)(a2 + 0) = *(u32 *)(s1 + 0x38);
    *(u32 *)(s1 + 0x38) = (u32)p;
    *(u32 *)(s1 + 0x3C) = (u32)p;
    *(u32 *)(s1 + 0x18) = (u32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (arg1 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800AC338(u8 *arg0, u8 *collider) {
    s32 s0;
    s32 s2;
    register u32 v asm("$2");        /* PIN $v0 - 0xBC state halfword */
    func_8007C0C8(arg0 + 0x18, collider);
    v = *(u16 *)(arg0 + 0xBC);
    if (v == 0) {
        s2 = *(s32 *)(arg0 + 0xA4) >> 2;
        s0 = func_8002BE14(0x3C);
        if (s0 != 0) {
            func_800C6588((u8 *)func_8002BD80(0x3C, (void *)(u32)s0), 3, arg0 + 0x94, s2, 0x60, 2, 0x808080);
        }
        func_8002BF34(arg0, s0);
        *(u16 *)(arg0 + 0xBC) = 1;
        *(s32 *)(arg0 + 0x44) |= 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AC3F0);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AC4D4);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AC728);

void func_800AC88C(u8 *arg0, s32 arg1) {
    u8 *s1;
    u8 *p;
    u8 *a2;
    u8 *a0v;

    s1 = arg0;
    p = s1 + 0x38;
    a2 = *(u8 **)(s1 + 0x38);
    a0v = *(u8 **)(s1 + 0x3C);
    *(u32 *)(s1 + 0x18) = (u32)&D_8006B3DC;
    *(u32 *)(s1 + 0x14) = (u32)&D_8006B3FC;
    *(u32 *)(s1 + 0x68) = (u32)&D_80065174;
    *(u32 *)(a2 + 4) = (u32)a0v;
    a2 = *(u8 **)(p + 4);
    *(u32 *)(a2 + 0) = *(u32 *)(s1 + 0x38);
    *(u32 *)(s1 + 0x38) = (u32)p;
    *(u32 *)(s1 + 0x3C) = (u32)p;
    *(u32 *)(s1 + 0x18) = (u32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (arg1 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800AC92C(u8 *arg0) {
    s32 s0;
    s32 s2;
    s0 = func_8002BE14(0xB0);
    if (s0 != 0) {
        func_800AD874((u8 *)func_8002BD80(0xB0, (void *)(u32)s0), *(s32 *)(arg0 + 0x80), *(s32 *)(arg0 + 0x84),
                      arg0 + 0x88, 0x280, 0x7B00500);
    }
    func_8002BF34(arg0, s0);
    s2 = *(s32 *)(arg0 + 0x98);
    s0 = func_8002BE14(0x3C);
    if (s0 != 0) {
        func_800C6588((u8 *)func_8002BD80(0x3C, (void *)(u32)s0), 3, arg0 + 0x88, s2, 0x100, 3, 0x808080);
    }
    func_8002BF34(arg0, s0);
    if (arg0 != 0) {
        u8 *v0 = *(u8 **)(arg0 + 0x14);
        ((void (*)(u8 *, s32)) * (u32 *)(v0 + 0x1C))(arg0 + *(s16 *)(v0 + 0x18), 3);
    }
}

void func_800ACA30(u8 *arg0, u8 *collider) {
    func_8007C0C8(arg0 + 0x18, collider);
    func_800AC92C(arg0);
}

void func_800ACA60(u8 *arg0) {
    register u8 *t0 asm("$8"); /* PIN $t0 - retain the object base. */
    register s32 a1 asm("$5"); /* PIN $a1 - updated first component. */
    register s32 a2 asm("$6"); /* PIN $a2 - updated second component. */
    register s32 a3 asm("$7"); /* PIN $a3 - updated third component. */
    register s32 v0 asm("$2"); /* PIN $v0 - third offset, then frame count. */
    register s32 v1 asm("$3"); /* PIN $v1 - second offset. */
    register s32 a0 asm("$4"); /* PIN $a0 - third offset. */

    t0 = arg0;
    a1 = *(s32 *)(t0 + 0x88);
    a2 = *(s32 *)(t0 + 0x8C);
    a3 = *(s32 *)(t0 + 0x90);
    v0 = *(s32 *)(t0 + 0x98);
    v1 = *(volatile s32 *)(t0 + 0x9C);
    a0 = *(volatile s32 *)(t0 + 0xA0);
    a1 += v0;
    a2 += v1;
    v0 = *(s32 *)(t0 + 0xA8);
    a3 += a0;
    *(s32 *)(t0 + 0x88) = a1;
    *(s32 *)(t0 + 0x8C) = a2;
    *(s32 *)(t0 + 0x90) = a3;
    *(s32 *)(t0 + 0x6C) = a1;
    *(s32 *)(t0 + 0x70) = a2;
    *(s32 *)(t0 + 0x74) = a3;
    v0++;
    *(s32 *)(t0 + 0xA8) = v0;
    if (v0 < 0xC) {
        return;
    }
    func_800AC92C(t0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800ACAD8);

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800ACD18);

void func_800ACE7C(u8 *arg0, s32 arg1) {
    u8 *s1;
    u8 *p;
    u8 *a2;
    u8 *a0v;

    s1 = arg0;
    p = s1 + 0x38;
    a2 = *(u8 **)(s1 + 0x38);
    a0v = *(u8 **)(s1 + 0x3C);
    *(u32 *)(s1 + 0x18) = (u32)&D_8006B34C;
    *(u32 *)(s1 + 0x14) = (u32)&D_8006B36C;
    *(u32 *)(s1 + 0x68) = (u32)&D_80065174;
    *(u32 *)(a2 + 4) = (u32)a0v;
    a2 = *(u8 **)(p + 4);
    *(u32 *)(a2 + 0) = *(u32 *)(s1 + 0x38);
    *(u32 *)(s1 + 0x38) = (u32)p;
    *(u32 *)(s1 + 0x3C) = (u32)p;
    *(u32 *)(s1 + 0x18) = (u32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (arg1 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800ACF1C(u8 *arg0) {
    s32 s0;
    s32 s2;
    func_800787A0(*(s32 *)(arg0 + 0x80), 0x4D);
    s0 = func_8002BE14(0xB0);
    if (s0 != 0) {
        func_800AD874((u8 *)func_8002BD80(0xB0, (void *)(u32)s0), *(s32 *)(arg0 + 0x80), *(s32 *)(arg0 + 0x84),
                      arg0 + 0x88, 0x280, 0x7B00500);
    }
    func_8002BF34(arg0, s0);
    s2 = *(s32 *)(arg0 + 0x98);
    s0 = func_8002BE14(0x3C);
    if (s0 != 0) {
        func_800C6588((u8 *)func_8002BD80(0x3C, (void *)(u32)s0), 3, arg0 + 0x88, s2, 0x100, 3, 0x808080);
    }
    func_8002BF34(arg0, s0);
    if (arg0 != 0) {
        u8 *v0 = *(u8 **)(arg0 + 0x14);
        ((void (*)(u8 *, s32)) * (u32 *)(v0 + 0x1C))(arg0 + *(s16 *)(v0 + 0x18), 3);
    }
}

void func_800AD02C(u8 *arg0, u8 *collider) {
    func_8007C0C8(arg0 + 0x18, collider);
    func_800ACF1C(arg0);
}

void func_800AD05C(u8 *arg0) {
    register u8 *t0 asm("$8"); /* PIN $t0 - retain the object base. */
    register s32 a1 asm("$5"); /* PIN $a1 - updated first component. */
    register s32 a2 asm("$6"); /* PIN $a2 - updated second component. */
    register s32 a3 asm("$7"); /* PIN $a3 - updated third component. */
    register s32 v0 asm("$2"); /* PIN $v0 - third offset, then frame count. */
    register s32 v1 asm("$3"); /* PIN $v1 - second offset. */
    register s32 a0 asm("$4"); /* PIN $a0 - third offset. */

    t0 = arg0;
    a1 = *(s32 *)(t0 + 0x88);
    a2 = *(s32 *)(t0 + 0x8C);
    a3 = *(s32 *)(t0 + 0x90);
    v0 = *(s32 *)(t0 + 0x98);
    v1 = *(volatile s32 *)(t0 + 0x9C);
    a0 = *(volatile s32 *)(t0 + 0xA0);
    a1 += v0;
    a2 += v1;
    v0 = *(s32 *)(t0 + 0xA8);
    a3 += a0;
    *(s32 *)(t0 + 0x88) = a1;
    *(s32 *)(t0 + 0x8C) = a2;
    *(s32 *)(t0 + 0x90) = a3;
    *(s32 *)(t0 + 0x6C) = a1;
    *(s32 *)(t0 + 0x70) = a2;
    *(s32 *)(t0 + 0x74) = a3;
    v0++;
    *(s32 *)(t0 + 0xA8) = v0;
    if (v0 < 0xC) {
        return;
    }
    func_800ACF1C(t0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/44E78", func_800AD0D4);
