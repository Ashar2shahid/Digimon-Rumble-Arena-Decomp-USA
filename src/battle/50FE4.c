#include "game_action_api.h"
#include "game_action_update_api.h"
#include "game_velocity_api.h"
#include "game_b5bd8_constructors.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_actor_queries.h"
#include "game_positions.h"
#include "game_deferred.h"


/* Typed16-byte producer storage: union views preserve PS1 little-endian words. */
typedef union EffectSpawnBuffer {
    u32 words[4];
    s32 position[4];
    u16 halfwords[8];
    u8 bytes[16];
} EffectSpawnBuffer;
typedef char EffectSpawnBuffer_size_is_16[(sizeof(EffectSpawnBuffer) == 16) ? 1 : -1];

extern u8 D_800D376C[];
extern u8 D_800D377C[];
extern u8 D_8006C094[];
extern u8 D_8006C374[];
extern u8 D_8006C314[];
extern u8 D_8006C14C[];
extern u8 D_8006C04C[];
extern u8 D_8006C06C[];
extern u8 D_8006C34C[];
extern u8 D_8006C324[];
extern u8 D_8006C0BC[];
extern u8 D_8006C0DC[];
extern u8 D_8006BE64[];
extern u8 D_8006BE3C[];
extern u8 D_8006C104;
extern u8 D_8006C124;
extern u8 D_80010814;
extern u8 D_80065174[];
extern u8 D_80065154[];
extern u8 D_8006D730[];
extern u8 D_8006D750[];
extern u8 D_8006BE8C[];
extern u8 D_8006BEAC[];

u8 *func_8002BE14(s32);

u8 *func_800B76A0();
u8 *func_800B7AD8(u8 *, u8 *);
u8 *func_80078AD8(u8 *);
s32 func_80079040(u8 *);
u8 *func_800C7898(u8 *, u8 *, s32);
volatile unsigned int func_800C72C0(s32, s32, s32, s32, s32, s32, s32, s32);
void func_8001BEDC(u8 *);
void func_8007C064();
void func_80075F88();
void func_8007C0AC();
s32 func_80077618();
void func_8006F02C();
void func_8006F00C();
void func_8007BC50();
void func_80079158();
void func_800794D4();
void func_80079964();
s32 func_8007A0C4();
s32 func_80077978();
void func_800C357C();
void func_80079580();
extern u8 D_80010884[];
extern s32 D_8006C05C[];
u8 *func_800B9264(u8 *, u8 *, const s32 *, s32);
u8 *func_800B8E74(u8 *, u8 *, const EffectSpawnBuffer *, s32);
void func_8007BCA0();
void func_80079D58();
void func_800B6B20();
u8 *func_800B7454();
void func_800787A0();
void func_8007BEC0();
void func_8007B9E4();
s32 func_8007A084(u8 *);
s32 func_80077730(u8 *);
void func_80079AA4();
void func_80079D80();
u8 *func_8007773C();
void func_8007A97C();
void func_8007A358();
s32 func_80079500();
s32 func_8007B150();
void func_80076FD8();
void func_80079D98();
void func_8002BCEC();
void func_8002BDA8();
void func_80077774();

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B53A4);

void func_800B55D8(u8 *arg0, s32 arg1) {
    u8 *s0;
    s32 s1;
    u8 *p;
    u8 *a2;
    u8 *a0v;
    s0 = arg0;
    s1 = arg1;
    *(u32 *)(s0 + 0x18) = (u32)&D_8006BE8C;
    *(u32 *)(s0 + 0x14) = (u32)&D_8006BEAC;
    if (*(u8 **)(s0 + 0x15C) != 0) {
        func_8001BEDC(*(u8 **)(s0 + 0x15C));
    }
    *(u32 *)(s0 + 0x68) = (u32)&D_80065174;
    p = s0 + 0x38;
    a2 = *(u8 **)(s0 + 0x38);
    a0v = *(u8 **)(s0 + 0x3C);
    *(u32 *)(a2 + 4) = (u32)a0v;
    a2 = *(u8 **)(p + 4);
    *(u32 *)(a2 + 0) = *(u32 *)(s0 + 0x38);
    *(u32 *)(s0 + 0x38) = (u32)p;
    *(u32 *)(s0 + 0x3C) = (u32)p;
    *(u32 *)(s0 + 0x18) = (u32)&D_80065154;
    func_8002BCEC(s0, 0);
    if (s1 & 1) {
        func_8002BDA8(s0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B5688);

void func_800B58A4(u8 *s1, u8 *arg1) {
    s32 buf[4];
    u8 *s0;
    func_8007C0C8(s1 + 0x18, arg1);
    s0 = func_80078AD8(arg1);
    if (s0 != 0) {
        func_8007767C(s0, buf);
        if (func_80079040(s0) != 0) {
            func_8002BF34((DtorNode *)s1, (DtorNode *)func_800C7898(s0, s1 + 0x128, 0x60));
            goto done;
        }
    }
    s0 = func_8002BE14(0x3C);
    if (s0 != 0) {
        func_800C6588((u8 *)func_8002BD80(0x3C, s0), 3, s1 + 0xC8, *(s32 *)(s1 + 0x158) >> 1, 0x60, 6, 0x808080);
    }
    func_8002BF34((DtorNode *)s1, (DtorNode *)s0);
done:
    if (s1 != 0) {
        u8 *vt = *(u8 **)(s1 + 0x14);
        (*(void (**)(u8 *, s32))(vt + 0x1C))(s1 + *(s16 *)(vt + 0x18), 3);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B59A4);

u8 *func_800B5BD8(u8 *s0, u8 *s2, u8 *s3, const s32 *s1) {
    s32 t0, t1, t2;
    func_8002BC9C(s0, 0);
    *(u32 *)(s0 + 0x14) = (u32)D_8006BE64;
    *(u32 *)(s0 + 0x18) = (u32)s2;
    *(u32 *)(s0 + 0x1C) = (u32)s3;
    *(s16 *)(s0 + 0x26) = func_8007A084(s2);
    *(s16 *)(s0 + 0x24) = 0;
    *(s16 *)(s0 + 0x28) = 0;
    *(s16 *)(s0 + 0x2A) = 0;
    *(u32 *)(s0 + 0x30) = 0;
    *(u32 *)(s0 + 0x2C) = 0;
    *(u8 *)(s0 + 0x20) = 0x80;
    *(u8 *)(s0 + 0x21) = 0x80;
    t0 = s1[0];
    t1 = s1[1];
    t2 = s1[2];
    *(u32 *)(s0 + 0x44) = t0;
    *(u32 *)(s0 + 0x48) = t1;
    *(u32 *)(s0 + 0x4C) = t2;
    *(u32 *)(s0 + 0x34) = t0;
    *(u32 *)(s0 + 0x38) = t1;
    *(u32 *)(s0 + 0x3C) = t2;
    *(s16 *)(s0 + 0x22) = func_80077730(s2);
    *(s16 *)(s0 + 0x64) = -0x5A;
    *(s16 *)(s0 + 0x54) = -0x5A;
    *(s16 *)(s0 + 0x5E) = -0x5A;
    *(s16 *)(s0 + 0x56) = -0x5A;
    *(s16 *)(s0 + 0x6C) = 0x5A;
    *(s16 *)(s0 + 0x5C) = 0x5A;
    *(s16 *)(s0 + 0x6E) = 0x5A;
    *(s16 *)(s0 + 0x66) = 0x5A;
    *(s16 *)(s0 + 0x70) = -0x10;
    *(s16 *)(s0 + 0x68) = -0x10;
    *(s16 *)(s0 + 0x60) = -0x10;
    *(s16 *)(s0 + 0x58) = -0x10;
    return s0;
}

void func_800B5CD4(u8 *arg0, s32 arg1) {
    *(u32 *)(arg0 + 0x14) = (u32)D_8006BE64;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B5D28);

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B5F48);

u8 *func_800B61CC(u8 *s0, u8 *a1, const s32 *a2) {
    s32 t0, t1, t2;
    func_8002BC9C(s0, 0);
    *(u8 **)(s0 + 0x14) = D_8006BE3C;
    *(u16 *)(s0 + 0x1A) = func_80077730(a1);
    *(u16 *)(s0 + 0x1C) = func_8007A084(a1);
    t0 = a2[0];
    t1 = a2[1];
    t2 = a2[2];
    *(u16 *)(s0 + 0x18) = 0;
    *(u8 *)(s0 + 0x20) = 0x80;
    *(u8 *)(s0 + 0x1F) = 0x80;
    *(u8 *)(s0 + 0x1E) = 0x80;
    *(s32 *)(s0 + 0x24) = t0;
    *(s32 *)(s0 + 0x28) = t1;
    *(s32 *)(s0 + 0x2C) = t2;
    return s0;
}

void func_800B6260(u8 *arg0, s32 arg1) {
    *(u32 *)(arg0 + 0x14) = (u32)D_8006BE3C;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B62B4);

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B63E8);

u8 *func_800B65D4(u8 *arg0) {
    func_80076FD8(arg0);
    *(u32 *)(arg0 + 0x14) = (u32)D_8006C14C;
    func_80079D98(arg0, D_8006C04C);
    *(u32 *)(arg0 + 0x4A8) = 0;
    *(u32 *)(arg0 + 0x4A4) = 0;
    return arg0;
}

void func_800B6620(u8 *arg0, s32 arg1) {
    *(u32 *)(arg0 + 0x14) = (u32)D_8006C14C;
    func_80077774(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800B6674(u8 *s0, s32 s2) {
    u8 *s1;
    func_80079D58(s0);
    s1 = (u8 *)func_8007773C(s0);
    if (s2 == 0) {
        s32 t;
        func_80079AA4(s0, 0x14, 0, 0, -1);
        *(s32 *)(s0 + 0x44C) = *(s32 *)(s1 + 0x110);
        t = *(s32 *)(s1 + 0x108) * func_8007A084(s0);
        *(s32 *)(s0 + 0x458) = -*(s32 *)(s1 + 0x10C);
        *(s32 *)(s0 + 0x45C) = 0;
        *(s32 *)(s0 + 0x454) = t;
        func_8007A97C(s0, -1, 0x60, 3);
    }
    if (s2 < 0x11) {
        func_800785BC(s0, (func_8007A084(s0) * (0x10 - s2) * 3) << 9);
    }
    if (s2 >= *(s16 *)(s1 + 0xF4) && *(s16 *)(s1 + 0xF6) >= s2) {
        func_8007A358(s0, *(s32 *)(s1 + 0xF0));
    } else {
        *(s32 *)(s0 + 0x448) = 0;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B6798);

void func_800B69B4(u8 *s0, s32 s1) {
    func_8007BCA0(s0);
    func_80079D58(s0);
    if (s1 == 1) {
        func_800B6BC8(s0);
        func_80078754(s0, 0xFB);
    }
    if (s1 == 0xD) {
        func_800B6B20(s0);
        func_800787A0(s0, 0xF7);
    }
    if (s1 < 0xE) {
        *(s32 *)(s0 + 0x3B4) += (-*(s32 *)(s0 + 0x3A4)) >> 4;
    }
}

void func_800B6A50(u8 *s0, s32 s1) {
    func_8007BEC0(s0);
    func_80079D58(s0);
    if (s1 == 1) {
        func_800B6BC8(s0);
        func_80078754(s0, 0xFB);
    }
    if (s1 == 0xD) {
        func_800B6B20(s0);
        func_800787A0(s0, 0xF7);
        *(s32 *)(s0 + 0x3B4) -= (func_8007A084(s0) * 3) << 12;
    }
    if (s1 < 0xE) {
        *(s32 *)(s0 + 0x3B4) -= (*(s32 *)(s0 + 0x3A4)) >> 4;
        if (*(s32 *)(s0 + 0x3A8) > 0) {
            *(s32 *)(s0 + 0x3B8) -= *(s32 *)(s0 + 0x3A8);
        }
    }
}

void func_800B6B20(u8 *s2) {
    s32 sp18[4];
    s32 sp28[3];
    u8 *s0;
    u8 *s1;
    /* PIN $v1 to match the retail buffer-load temporary. */
    register s32 v1 asm("$3");
    func_8007767C(s2, sp18);
    v1 = sp18[1];
    v1 -= 0x80;
    sp18[1] = v1;
    sp28[0] = func_8007A084(s2) << 7;
    sp28[1] = 0;
    sp28[2] = 0;
    s1 = func_80077624(s2);
    s0 = func_8002BE14(0xC0);
    if (s0 != 0) {
        func_800B7454((u8 *)func_8002BD80(0xC0, s0), s2, sp18, sp28, s1);
    }
    func_8007AFCC(s2, s0);
}

void func_800B6BC8(u8 *arg0) {
    u8 *s0 = (u8 *)func_8002BE14(0x44);
    if (s0 != 0) {
        func_800B76A0((u8 *)func_8002BD80(0x44, s0), arg0);
    }
    func_8007AFCC(arg0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B6C24);

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B6E40);

void func_800B7034(u8 *arg0) {
    u8 *s0 = (u8 *)func_8002BE14(0x120);
    if (s0 != 0) {
        func_800B7AD8((u8 *)func_8002BD80(0x120, s0), arg0);
    }
    func_8007AFCC(arg0, s0);
}

s32 *func_800B7090(s32 *a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    s32 *s0;
    s32 sp18[4];
    s32 sp28[4];
    s32 sp38[3];
    s32 t0, t1, t2, d;
    func_8002BC9C((u8 *)a0, 0x30000);
    func_8007C064((u8 *)a0 + 0x18, a1, a4, &D_80010814, 1);
    *(s32 *)((u8 *)a0 + 0x18) = (s32)&D_8006C104;
    *(s32 *)((u8 *)a0 + 0x14) = (s32)&D_8006C124;
    func_80075F88((u8 *)a0 + 0x38, a2, 0x80, (u8 *)a0 + 0x18);
    func_8007767C(a1, sp18);
    func_8007A91C(a1, sp28);
    d = sp28[0] - sp18[0];
    if (d > 0) {
        d = 0x2AA8;
    } else {
        d = -0x2AA8;
    }
    sp38[0] = d;
    sp38[1] = 0;
    sp38[2] = 0;
    func_8007C0AC((u8 *)a0 + 0x18, sp38);
    *(s32 *)((u8 *)a0 + 0x80) = a1;
    t0 = ((s32 *)a2)[0];
    t1 = ((s32 *)a2)[1];
    t2 = ((s32 *)a2)[2];
    s0 = (s32 *)((u8 *)a0 + 0x38);
    *(s32 *)((u8 *)a0 + 0x4C) = (s32)a0;
    *(s32 *)((u8 *)a0 + 0x84) = t0;
    *(s32 *)((u8 *)a0 + 0x88) = t1;
    *(s32 *)((u8 *)a0 + 0x8C) = t2;
    if (func_80077618(a1) == 0) {
        func_8006F02C(a3, s0);
    } else {
        func_8006F00C(a3, s0);
    }
    return a0;
}

void func_800B71DC(u8 *s1, s32 s0) {
    u8 *v1 = s1 + 0x38;
    u8 *a2;
    u8 *a0;
    *(u8 **)(s1 + 0x18) = &D_8006C104;
    *(u8 **)(s1 + 0x14) = &D_8006C124;
    *(u8 **)(s1 + 0x68) = D_80065174;
    a2 = *(u8 **)(s1 + 0x38);
    a0 = *(u8 **)(s1 + 0x3C);
    *(u8 **)(a2 + 4) = a0;
    a2 = *(u8 **)(v1 + 4);
    *(u8 **)a2 = *(u8 **)(s1 + 0x38);
    *(u8 **)(s1 + 0x38) = v1;
    *(u8 **)(s1 + 0x3C) = v1;
    *(u8 **)(s1 + 0x18) = D_80065154;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B727C);

void func_800B7410(u8 *arg0) {
    u8 *v0;
    if (arg0 != 0) {
        v0 = *(u8 **)(arg0 + 0x14);
        ((void (*)(u8 *, s32))*(u32 *)(v0 + 0x1C))((u8 *)(arg0 + *(s16 *)(v0 + 0x18)), 3);
    }
}

u8 *func_800B7454(u8 *s0, u8 *s1, s32 *s2, s32 *s3, u8 *arg4) {
    u8 (*new_var)[];
    s32 *new_var2;
    func_800C72C0((s32)s0, (s32)s1, (s32)(new_var2 = s2), ((s32)s3) ^ 0, 0x80, 0x07A81800, 0x2000, 3);
    *(u8 **)(s0 + 0x18) = D_8006C0BC;
    new_var = &D_8006C0DC;
    *(u8 **)(s0 + 0x14) = *new_var;
    return s0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B74B8);

u8 *func_800B76A0(u8 *s0, u8 *s1) {
    func_8002BC9C(s0, 0);
    *(u32 *)(s0 + 0x14) = (u32)D_8006C094;
    *(u32 *)(s0 + 0x18) = (u32)s1;
    func_8007767C(s1, (s32 *)(s0 + 0x1C));
    *(u32 *)(s0 + 0x2C) = 0x40;
    *(u32 *)(s0 + 0x30) = 0x80;
    *(u32 *)(s0 + 0x34) = 0;
    *(u32 *)(s0 + 0x38) = 0;
    *(u32 *)(s0 + 0x3C) = 0;
    *(s16 *)(s0 + 0x40) = func_80077730(s1);
    return s0;
}

void func_800B771C(u8 *arg0, s32 arg1) {
    *(u32 *)(arg0 + 0x14) = (u32)D_8006C094;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800B7770(u8 *s0) {
    s32 value = *(s32 *)(s0 + 0x38);
    /* PIN $v1 for the post-call object-field adjustment. */
    register s32 v1 asm("$3");
    if (value >= 13) {
        if (s0 != 0) {
            u8 *v0 = *(u8 **)(s0 + 0x14);
            s32 offset = *(s16 *)(v0 + 0x18);
            void (*callback)(u8 *, s32) = (void (*)(u8 *, s32))*(u32 *)(v0 + 0x1C);
            callback(s0 + offset, 3);
        }
    } else {
        *(s32 *)(s0 + 0x38) = value + 1;
        func_8007767C(*(u8 **)(s0 + 0x18), (s32 *)(s0 + 0x1C));
        v1 = *(s32 *)(s0 + 0x20);
        v1 -= 0x60;
        *(s32 *)(s0 + 0x20) = v1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B77F0);

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B7AD8);

void func_800B7C8C(u8 *arg0, s32 arg1) {
    *(u32 *)(arg0 + 0x14) = (u32)D_8006C06C;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B7CE0);

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B7E68);

void func_800B80F4(u8 *s1, s32 s0) {
    u8 *v1 = s1 + 0x38;
    u8 *a2;
    u8 *a0;
    *(u8 **)(s1 + 0x18) = D_8006D730;
    *(u8 **)(s1 + 0x14) = D_8006D750;
    *(u8 **)(s1 + 0x68) = D_80065174;
    a2 = *(u8 **)(s1 + 0x38);
    a0 = *(u8 **)(s1 + 0x3C);
    *(u8 **)(a2 + 4) = a0;
    a2 = *(u8 **)(v1 + 4);
    *(u8 **)a2 = *(u8 **)(s1 + 0x38);
    *(u8 **)(s1 + 0x38) = v1;
    *(u8 **)(s1 + 0x3C) = v1;
    *(u8 **)(s1 + 0x18) = D_80065154;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

u8 *func_800B8194(u8 *arg0) {
    /* PIN $v1 for the initialized vtable address. */
    register u8 *v1 asm("$3");
    func_80076FD8(arg0);
    v1 = D_8006C374;
    *(u8 **)(arg0 + 0x14) = v1;
    func_80079D98(arg0, D_8006C314);
    return arg0;
}

void func_800B81D8(u8 *arg0, s32 arg1) {
    *(u32 *)(arg0 + 0x14) = (u32)D_8006C374;
    func_80077774(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800B822C(u8 *arg0) {
    *(u32 *)(arg0 + 0x3F0) = 0;
    *(u32 *)(arg0 + 0x3E0) = 0;
}

void func_800B8238(s32 arg0, s32 arg1) {
    s32 s2 = arg0;
    s32 s3 = arg1;
    s32 s0;
    s64 v;
    func_8007B978((u8 *)(u32)s2, s3);
    if (s3 == 3) {
        v = (s64)*(s32 *)(s2 + 0x3C4) * 0x2AA8;
        v >>= 16;
        s0 = (s32)v;
        s0 = s0 * func_8007A084(s2);
        *(s32 *)(s2 + 0x3B4) += s0;
    }
    if (s3 >= 4) {
        *(s32 *)(s2 + 0x3B4) += (-*(s32 *)(s2 + 0x3A4)) >> 2;
    }
}

void func_800B82E8(s32 arg0, s32 arg1) {
    s32 s2 = arg0;
    s32 s3 = arg1;
    s32 s0;
    s64 v;
    func_8007B9E4(s2, s3);
    if (s3 == 4) {
        v = (s64)*(s32 *)(s2 + 0x3C4) * 0x38E0;
        v >>= 16;
        s0 = (s32)v;
        s0 = s0 * func_8007A084(s2);
        *(s32 *)(s2 + 0x3B4) += s0;
    }
    if (s3 >= 5) {
        *(s32 *)(s2 + 0x3B4) += (-*(s32 *)(s2 + 0x3A4)) >> 2;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B8398);

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B8570);

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B8738);

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B8928);

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B8ACC);

void func_800B8D60(u8 *s1, u32 s0) {
    EffectSpawnBuffer buf;
    s32 s2;
    u8 *r;
    s2 = (s32)(u32)func_80077624(s1);
    func_8007A724(s1, buf.bytes, 2, D_800D376C);
    buf.words[3] = s0;
    r = (u8 *)func_8002BE14(0x58);
    if (r != 0) {
        func_800B8E74((u8 *)func_8002BD80(0x58, r), s1, &buf, s2);
    }
    func_8007AFCC(s1, r);
}

void func_800B8DF4(u8 *s1) {
    EffectSpawnBuffer buf;
    s32 s2 = (s32)(u32)func_80077624(s1);
    u8 *s0;
    func_8007767C(s1, buf.position);
    s0 = (u8 *)func_8002BE14(0x60);
    if (s0 != 0) {
        func_800B9264((u8 *)func_8002BD80(0x60, s0), s1, buf.position, s2);
    }
    func_8007AFCC(s1, s0);
}

u8 *func_800B8E74(u8 *self, u8 *owner, const EffectSpawnBuffer *settings, s32 value) {
    s32 negative;
    u16 initial;
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_8006C34C;
    *(u8 **)(self + 0x18) = owner;
    *(s32 *)(self + 0x1C) = value;
    *(s16 *)(self + 0x26) = 0;
    *(s16 *)(self + 0x22) = func_80077730(owner);
    negative = (s32)(0u - (u32)func_8007A084(*(u8 **)(self + 0x18)));
    *(s16 *)(self + 0x24) = (s16)negative;
    initial = settings->halfwords[6];
    *(s16 *)(self + 0x38) = -0x80;
    *(s16 *)(self + 0x28) = -0x80;
    *(s16 *)(self + 0x40) = 0x80;
    *(s16 *)(self + 0x30) = 0x80;
    *(s16 *)(self + 0x32) = -0x80;
    *(s16 *)(self + 0x2A) = -0x80;
    *(s16 *)(self + 0x42) = 0x80;
    *(s16 *)(self + 0x3A) = 0x80;
    *(s16 *)(self + 0x44) = -0x80;
    *(s16 *)(self + 0x3C) = -0x80;
    *(s16 *)(self + 0x34) = -0x80;
    *(s16 *)(self + 0x2C) = -0x80;
    *(u16 *)(self + 0x20) = initial;
    return self;
}

void func_800B8F38(u8 *arg0, s32 arg1) {
    *(u32 *)(arg0 + 0x14) = (u32)D_8006C34C;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800B8F8C(u8 *s0) {
    /* PIN $v1 to normalize the callback threshold in place. */
    register u32 v1 asm("$3");
    func_8007A724(*(u8 **)(s0 + 0x18), s0 + 0x48, 2, D_800D377C);
    v1 = *(u16 *)(s0 + 0x26);
    v1 = (v1 < 11);
    if (v1 == 0) {
        if (s0 != 0) {
            u8 *v0 = *(u8 **)(s0 + 0x14);
            s32 offset = *(s16 *)(v0 + 0x18);
            void (*callback)(u8 *, s32) = (void (*)(u8 *, s32))*(u32 *)(v0 + 0x1C);
            callback(s0 + offset, 3);
        }
    } else {
        /* Preserve retail's second counter load in this branch. */
        volatile u16 *counter = (volatile u16 *)(s0 + 0x26);
        *counter = *counter + 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/50FE4", func_800B9014);

u8 *func_800B9264(u8 *self, u8 *owner, const s32 *position, s32 value) {
    s32 x;
    s32 y;
    s32 z;
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_8006C324;
    *(u8 **)(self + 0x18) = owner;
    *(s32 *)(self + 0x1C) = value;
    *(s16 *)(self + 0x24) = 0;
    *(s16 *)(self + 0x20) = func_80077730(owner);
    *(s16 *)(self + 0x22) = (s16)(0u - (u32)func_8007A084(*(u8 **)(self + 0x18)));
    x = position[0];
    y = position[1];
    z = position[2];
    *(u8 *)(self + 0x48) = 0;
    *(s16 *)(self + 0x4A) = 0;
    *(s16 *)(self + 0x4C) = 0;
    *(s16 *)(self + 0x38) = -0xA0;
    *(s16 *)(self + 0x28) = -0xA0;
    *(s16 *)(self + 0x40) = 0xA0;
    *(s16 *)(self + 0x30) = 0xA0;
    *(s16 *)(self + 0x32) = -0xA0;
    *(s16 *)(self + 0x2A) = -0xA0;
    *(s16 *)(self + 0x42) = 0xA0;
    *(s16 *)(self + 0x3A) = 0xA0;
    *(s16 *)(self + 0x44) = 0;
    *(s16 *)(self + 0x3C) = 0;
    *(s16 *)(self + 0x34) = 0;
    *(s16 *)(self + 0x2C) = 0;
    *(s32 *)(self + 0x50) = x;
    *(s32 *)(self + 0x58) = z;
    *(s32 *)(self + 0x54) = (s32)((u32)y - 0x80u);
    return self;
}

void func_800B9348(u8 *arg0, s32 arg1) {
    *(u32 *)(arg0 + 0x14) = (u32)D_8006C324;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800B939C(u8 *arg0) {
    u8 *s0 = arg0;
    s32 s1;
    s32 vv;
    func_8007767C(*(u8 **)(s0 + 0x18), (s32 *)(s0 + 0x50));
    vv = *(s32 *)(s0 + 0x54);
    vv -= 0x80;
    *(s32 *)(s0 + 0x54) = vv;
    vv = *(u16 *)(s0 + 0x4A);
    switch (vv) {
    case 0:
        {
            s32 t = *(u8 *)(s0 + 0x48);
            t += (0x84 - t) >> 2;
            *(u8 *)(s0 + 0x48) = t;
            if ((s8)t < 0) {
                *(u16 *)(s0 + 0x4C) = 0;
                (*(u16 *)(s0 + 0x4A))++;
            } else {
                break;
            }
        }
    case 1:
        if (++(*(u16 *)(s0 + 0x4C)) < 0x16) break;
        (*(u16 *)(s0 + 0x4A))++;
    case 2:
        *(u8 *)(s0 + 0x48) = *(u8 *)(s0 + 0x48) - (*(u8 *)(s0 + 0x48) >> 2);
        if (*(u8 *)(s0 + 0x48) >= 5) break;
        (*(u16 *)(s0 + 0x4A))++;
    case 3:
        if (s0) {
            s32 v0 = *(s32 *)(s0 + 0x14);
            ((void (*)(u8 *, s32))*(s32 *)(v0 + 0x1C))(s0 + *(s16 *)(v0 + 0x18), 3);
        }
        return;
    default:
        break;
    }
    s1 = *(s32 *)func_80079500(*(s32 *)(s0 + 0x18));
    if (func_8007B150(*(s32 *)(s0 + 0x18)) != 0 || s1 == 0x13) {
        if (s0) {
            s32 v0 = *(s32 *)(s0 + 0x14);
            ((void (*)(u8 *, s32))*(s32 *)(v0 + 0x1C))(s0 + *(s16 *)(v0 + 0x18), 3);
        }
        return;
    }
    (*(u16 *)(s0 + 0x24))++;
}
