#include "game_action_api.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_actor_queries.h"
#include "game_deferred.h"

extern u8 *func_8002BE14(s32);
extern void func_800787A0(u8 *, s32);
extern void func_80079D58(u8 *);
extern void func_8007B0B4(u8 *);
extern void func_8007BA5C(u8 *, s32);
extern void func_8007BCA0(u8 *);
extern void func_8007BEC0(u8 *);
extern u8 *func_800AEFC4(u8 *, u8 *);
extern void func_800AE424(u8 *);
extern void func_800AD528(u8 *);
extern u8 *func_800B0030(u8 *, u8 *, u8 *);
extern u8 *func_800B0464(u8 *, u8 *, u8 *);
extern u8 *func_800B07C4(u8 *, u8 *, u8 *);
extern void func_800B1C84(u8 *);
extern u8 D_8006B63C[];
extern u8 D_8006B614[];
extern u8 D_8006B5EC[];
extern u8 D_8006B86C[];
extern void func_8007BB5C(u8 *, s32);
extern void func_800C591C(u8 *, u8 *, u8 *, s32, s32, s32);


extern s32 func_80077730(u8 *);

extern u8 D_8006B744[];
extern u8 D_8006BC94[];

extern void func_80077774(u8 *, s32);
extern void func_8002BDA8(u8 *);
extern u8 D_8006B6D4[];
extern u8 D_8006B6AC[];

extern void func_8002BCEC(u8 *, s32);
extern void func_800AE28C(u8 *);
extern void func_800AE148(u8 *, s32, s32);
extern s32 func_8007A084(u8 *);





INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AD308);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AD488);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AD528);

void func_800AD638(u8 *a0, u8 *collider) {
    func_8007C0C8(a0 + 0x18, collider);
    func_800AD528(a0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AD668);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AD708);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AD874);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AD9B0);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800ADA50);

/* PIN $a2/$v1/$a0/$v0/$a1 to the retail base, copy words, and callback. */
void func_800ADA84(u8 *a0) {
    register u8 *a2 __asm__("$6") = a0;
    register u32 value84 __asm__("$3") = *(u32 *)(a2 + 0x84);
    register u32 value88 __asm__("$4") = *(u32 *)(a2 + 0x88);
    register s32 count __asm__("$2") = *(s32 *)(a2 + 0xA4);
    register u32 value8C __asm__("$5") = *(u32 *)(a2 + 0x8C);
    *(u32 *)(a2 + 0x6C) = value84;
    *(u32 *)(a2 + 0x70) = value88;
    *(u32 *)(a2 + 0x74) = value8C;
    if (count < 8) {
        goto increment;
    }
    if (a2 != 0) {
        u8 *object = *(u8 **)(a2 + 0x14);
        s32 offset = *(s16 *)(object + 0x18);
        register u32 callback __asm__("$3") = *(u32 *)(object + 0x1C);
        ((void (*)(u8 *, s32))callback)(a2 + offset, 3);
    }
    return;
increment:
    *(s32 *)(a2 + 0xA4) += 1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800ADB00);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800ADCFC);

void func_800ADD34(u8 *a0, s32 a1) {
    register u8 *s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    *(u8 **)(s1 + 0x14) = D_8006B744;
    s0 = a1;
    func_80077774(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800ADD88(u8 *owner) {
    func_8007B0B4(func_8007B16C(owner));
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800ADDB0);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800ADFA0);

void func_800AE058(u8 *self, s32 mode) {
    s32 i;
    s32 active;
    func_8007BEF4(self, mode);
    func_80079D58(self);
    if (mode == 1) {
        func_800AE28C(self);
        func_80078754(self, 0xE8);
    }
    active = mode < 11;
    if (mode == 10) {
        for (i = 0; i < 7; i++) {
            func_800AE148(self, 0x200, i);
        }
        *(s32 *)(self + 0x3B4) = (s32)((u32)*(s32 *)(self + 0x3B4) -
            ((u32)func_8007A084(self) * 3u << 12));
        func_800787A0(self, 0xE2);
    }
    if (active) {
        *(s32 *)(self + 0x3B4) = (s32)((u32)*(s32 *)(self + 0x3B4) -
            (u32)(*(s32 *)(self + 0x3A4) >> 4));
        if (*(s32 *)(self + 0x3A8) > 0) {
            *(s32 *)(self + 0x3B8) = (s32)((u32)*(s32 *)(self + 0x3B8) -
                ((u32)*(s32 *)(self + 0x3A8) << 1));
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AE148);

void func_800AE28C(u8 *a0) {
    u8 *s0;
    s0 = func_8002BE14(0x44);
    if (s0 != 0) {
        func_800AEFC4((u8 *)func_8002BD80(0x44, s0), a0);
    }
    func_8007AFCC(a0, s0);
}

void func_800AE2E8(u8 *a0, s32 a1) {
    func_8007BCA0(a0);
    func_80079D58(a0);
    if (a1 == 1) {
        func_800AE424(a0);
        func_80078754(a0, 0xE7);
    }
    if (a1 == 0x14) {
        func_800787A0(a0, 0xE3);
    }
    if (a1 < 0x15) {
        *(s32 *)(a0 + 0x3B4) += -*(s32 *)(a0 + 0x3A4) >> 4;
    }
}

void func_800AE37C(u8 *a0, s32 a1) {
    func_8007BEC0(a0);
    func_80079D58(a0);
    if (a1 == 1) {
        func_800AE424(a0);
        func_80078754(a0, 0xE7);
    }
    if (a1 == 0x14) {
        func_800787A0(a0, 0xE3);
    }
    if (a1 < 0x15) {
        *(s32 *)(a0 + 0x3B4) -= *(s32 *)(a0 + 0x3A4) >> 4;
        if (*(s32 *)(a0 + 0x3A8) > 0) {
            *(s32 *)(a0 + 0x3B8) -= *(s32 *)(a0 + 0x3A8);
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AE424);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AE4FC);

void func_800AE6F0(u8 *a0) {
    u8 *s2 = func_80077624(a0);
    u8 *s0 = func_8002BE14(0x60);
    if (s0 != 0) {
        func_800B0030((u8 *)func_8002BD80(0x60, s0), a0, s2);
    }
    func_8007AFCC(a0, s0);
}

void func_800AE760(u8 *a0) {
    u8 *s2 = func_80077624(a0);
    u8 *s0 = func_8002BE14(0x40);
    if (s0 != 0) {
        func_800B0464((u8 *)func_8002BD80(0x40, s0), a0, s2);
    }
    func_8007AFCC(a0, s0);
}

void func_800AE7D0(u8 *a0) {
    u8 *s2 = func_80077624(a0);
    u8 *s0 = func_8002BE14(0x40);
    if (s0 != 0) {
        func_800B07C4((u8 *)func_8002BD80(0x40, s0), a0, s2);
    }
    func_8007AFCC(a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AE840);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AE9EC);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AEA8C);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AEB48);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AEDA8);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AEFC4);

void func_800AF040(u8 *a0, s32 a1) {
    register u8 *s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    *(u8 **)(s1 + 0x14) = D_8006B6D4;
    s0 = a1;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800AF094(u8 *a0) {
    if (*(s32 *)(a0 + 0x38) < 0x10) {
        goto increment;
    }
    if (a0 != 0) {
        u8 *object = *(u8 **)(a0 + 0x14);
        s32 offset = *(s16 *)(object + 0x18);
        register u32 callback __asm__("$3") = *(u32 *)(object + 0x1C);
        ((void (*)(u8 *, s32))callback)(a0 + offset, 3);
    }
    return;
increment:
    *(s32 *)(a0 + 0x38) += 1;
    func_8007767C(*(u8 **)(a0 + 0x18), (s32 *)(a0 + 0x1C));
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AF100);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AF358);

void func_800AF3EC(u8 *a0, s32 a1) {
    register u8 *s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    *(u8 **)(s1 + 0x14) = D_8006B6AC;
    s0 = a1;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

/* PIN $a3/$t0/$v0/$a0/$a1/$a2/$v1 to the retail update path. */
void func_800AF440(u8 *a0) {
    register u8 *a3 __asm__("$7") = a0;
    register s32 t0 __asm__("$8") = *(s32 *)(a3 + 0x3C);
    if (t0 < 8) {
        register s32 v0 __asm__("$2") = t0 + 1;
        register u32 a0 __asm__("$4") = *(u32 *)(a3 + 0x1C);
        register u32 a1 __asm__("$5") = *(u32 *)(a3 + 0x20);
        register u32 a2 __asm__("$6") = *(u32 *)(a3 + 0x24);
        register u32 v1 __asm__("$3") = *(u32 *)(a3 + 0x2C);
        *(s32 *)(a3 + 0x3C) = v0;
        v0 = *(u32 *)(a3 + 0x30);
        a0 += v1;
        v1 = *(u32 *)(a3 + 0x34);
        a1 += v0;
        *(u32 *)(a3 + 0x1C) = a0;
        *(u32 *)(a3 + 0x20) = a1;
        a2 += v1;
        *(u32 *)(a3 + 0x24) = a2;
    } else if (a3 != 0) {
        u8 *object = *(u8 **)(a3 + 0x14);
        s32 offset = *(s16 *)(object + 0x18);
        register void (*callback)(u8 *, s32) __asm__("$3") =
            *(void (**)(u8 *, s32))(object + 0x1C);
        callback(a3 + offset, 3);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AF4CC);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AF61C);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AF7BC);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AF85C);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AF9A8);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800AFC28);

u8 *func_800B0030(u8 *a0, u8 *a1, u8 *a2) {
    register u8 *s0 __asm__("$16") = a0;
    register u8 *s1 __asm__("$17") = a1;
    register u8 *s2 __asm__("$18") = a2;
    register u8 *callarg __asm__("$4");
    func_8002BC9C(s0, 0);
    callarg = s1;
    __asm__ volatile ("" : "+r" (callarg));
    *(u8 **)(s0 + 0x14) = D_8006B63C;
    *(u8 **)(s0 + 0x18) = s1;
    *(u8 **)(s0 + 0x1C) = s2;
    *(s32 *)(s0 + 0x30) = 0;
    *(s32 *)(s0 + 0x34) = 0;
    *(s32 *)(s0 + 0x38) = 0;
    *(u16 *)(s0 + 0x5E) = func_80077730(callarg);
    return s0;
}

void func_800B00A0(u8 *a0, s32 a1) {
    register u8 *s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    *(u8 **)(s1 + 0x14) = D_8006B63C;
    s0 = a1;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B00F4);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B01F8);

u8 *func_800B0464(u8 *a0, u8 *a1, u8 *a2) {
    register u8 *s0 __asm__("$16") = a0;
    register u8 *s1 __asm__("$17") = a1;
    register u8 *s2 __asm__("$18") = a2;
    register u8 *callarg __asm__("$4");
    func_8002BC9C(s0, 0);
    callarg = s1;
    __asm__ volatile ("" : "+r" (callarg));
    *(u8 **)(s0 + 0x14) = D_8006B614;
    *(u8 **)(s0 + 0x18) = s1;
    *(u8 **)(s0 + 0x1C) = s2;
    *(s32 *)(s0 + 0x30) = 0;
    *(s32 *)(s0 + 0x34) = 0;
    *(s32 *)(s0 + 0x38) = 0;
    *(u16 *)(s0 + 0x3C) = func_80077730(callarg);
    return s0;
}

void func_800B04D4(u8 *a0, s32 a1) {
    register u8 *s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    *(u8 **)(s1 + 0x14) = D_8006B614;
    s0 = a1;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800B0528(u8 *a0) {
    s32 *counter = (s32 *)(a0 + 0x34);
    if (*counter < 0x18) {
        goto increment;
    }
    if (a0 != 0) {
        u8 *object = *(u8 **)(a0 + 0x14);
        s32 offset = *(s16 *)(object + 0x18);
        register u32 callback __asm__("$3") = *(u32 *)(object + 0x1C);
        ((void (*)(u8 *, s32))callback)(a0 + offset, 3);
    }
    return;
increment:
    *counter += 1;
    *(s32 *)(a0 + 0x24) -= 0x120;
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B0598);

u8 *func_800B07C4(u8 *a0, u8 *a1, u8 *a2) {
    register u8 *s0 __asm__("$16") = a0;
    register u8 *s1 __asm__("$17") = a1;
    register u8 *s2 __asm__("$18") = a2;
    register u8 *callarg __asm__("$4");
    func_8002BC9C(s0, 0);
    callarg = s1;
    __asm__ volatile ("" : "+r" (callarg));
    *(u8 **)(s0 + 0x14) = D_8006B5EC;
    *(u8 **)(s0 + 0x18) = s1;
    *(u8 **)(s0 + 0x1C) = s2;
    *(s32 *)(s0 + 0x30) = 0;
    *(s32 *)(s0 + 0x34) = 0;
    *(s32 *)(s0 + 0x38) = 0;
    *(u16 *)(s0 + 0x3C) = func_80077730(callarg);
    return s0;
}

void func_800B0834(u8 *a0, s32 a1) {
    register u8 *s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    *(u8 **)(s1 + 0x14) = D_8006B5EC;
    s0 = a1;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800B0888(u8 *a0) {
    s32 *counter = (s32 *)(a0 + 0x34);
    if (*counter < 0x10) {
        goto increment;
    }
    if (a0 != 0) {
        u8 *object = *(u8 **)(a0 + 0x14);
        s32 offset = *(s16 *)(object + 0x18);
        register u32 callback __asm__("$3") = *(u32 *)(object + 0x1C);
        ((void (*)(u8 *, s32))callback)(a0 + offset, 3);
    }
    return;
increment:
    *counter += 1;
    *(s32 *)(a0 + 0x24) -= 0x120;
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B08F8);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B0B0C);

void func_800B0B44(u8 *a0, s32 a1) {
    register u8 *s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    *(u8 **)(s1 + 0x14) = D_8006BC94;
    s0 = a1;
    func_80077774(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800B0B98(u8 *a0) {
    *(u16 *)(a0 + 0x4A4) = 0;
}

/* PIN $s1/$s0 for the retained arguments; $v1/$v0/$a0 for the copy pointers. */
void func_800B0BA0(u8 *a0, s32 a1) {
    register u8 *s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16") = a1;
    u32 buf[24];
    register u32 *dst __asm__("$3");
    register u32 *src __asm__("$2");
    register u32 *end __asm__("$4");
    __asm__ ("" : "+r"(s1));
    __asm__ ("" : "+r"(s0));

    dst = buf;
    src = (u32 *)D_8006B86C;
    end = src + 24;
    do {
        u32 t0 = src[0];
        u32 t1 = src[1];
        u32 t2 = src[2];
        u32 t3 = src[3];
        dst[0] = t0;
        dst[1] = t1;
        dst[2] = t2;
        dst[3] = t3;
        __asm__ volatile ("" : "+r"(src) : : "memory");
        src += 4;
        dst += 4;
    } while (src != end);
    func_8007BB5C(s1, s0);
    if (s0 == 8) {
        s0 = (s32)func_8002BE14(0x690);
        if (s0 != 0) {
            func_800C591C((u8 *)func_8002BD80(0x690, (void *)(u32)s0), s1, (u8 *)buf, 4, 5, 5);
        }
        func_8007AFCC(s1, (u8 *)s0);
    }
}

void func_800B0C68(u8 *a0, s32 a1) {
    func_8007BA5C(a0, a1);
    if (a1 == 5) {
        func_800B1C84(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B0CAC);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B0DC0);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B0E30);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B0F74);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B1090);

INCLUDE_ASM("asm/us/game/nonmatchings/48F48", func_800B1200);
