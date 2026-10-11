#include "game_renew_handle_api.h"
#include "game_destructor_api.h"
#include "game_audio_api.h"
#include "common.h"
#include "game_positions.h"

extern s32 func_8007773C();
extern s32 func_80077768();
extern s32 func_80075154();
extern s32 func_80078A64();
extern s32 func_80078A7C();
extern s32 func_80079C80();
extern s32 func_80079C14();
extern s32 func_8007FC28();
extern void func_80079964(u8 *, s32, s32, s32);
extern void func_80079AA4(u8 *, s32, s32, s32, s32);

extern u8 *func_8002BD88(s32);
extern u8 *func_800C4C80(u8 *, u8 *);
extern void func_8002BF34(u8 *, u8 *);
extern void func_80079794(u8 *, u8 *);
extern void func_8002B3D0(u8 *);
extern u8 *func_800C5210(s32, s32);
extern void func_80079D80(u8 *, s32);
extern void func_80079D88(u8 *, s32);
extern void func_80079D90(u8 *, s32);
extern u8 D_8005F824[];
extern s32 func_80077838(u8 *);
extern void func_8007F4D4(u8 *, s32);
extern s32 D_80068144;
extern s32 func_80077860(u8 *);
extern void func_8007FA78(u8 *);
extern s32 func_8007760C(u8 *);
extern u8 D_800656C4[];
extern u8 D_800656AC[];

extern u8 *func_80075DE8(u8 *, u8 *, u8 *);
extern s32 func_80077618(u8 *);
extern s32 D_800D3A5C;
extern s32 func_8007B150(u8 *);
extern s32 func_80079518(u8 *);
extern void *func_800816D0(void *);
extern void *func_80080E80(void *);
extern void *func_8008165C(void *);
extern void *func_80080BC4(void *, s32);
extern void func_8007FACC(u8 *);

INCLUDE_ASM("asm/us/game/nonmatchings/18104", func_8007C4C4);

s32 func_8007F0B0(u8 *a0, u8 *a1) {
    /* Pins preserve state/input/allocator bases and the three-word copy order. */
    register u8 *s1 asm("$17") = a0;
    register u8 *s0 asm("$16") = a1;
    register u8 *s2 asm("$18");
    register s32 v1 asm("$3");
    register s32 v0 asm("$2");
    register s32 a0v asm("$4");
    s32 buf[4];
    u8 *result;
    s32 index;
    s2 = (u8 *)D_800D3A5C;
    func_8007A8D0(s0, (u8 *)buf);
    *(s32 *)(s1 + 0x40) = 0;
    index = func_80077618(s0);
    result = func_80075DE8(s2 + (index ? 0x230 : 0x228), (u8 *)buf, s1 + 0x1C);
    if (result != 0) {
        v0 = 1;
        *(s32 *)(s1 + 0x40) = v0;
        v1 = *(s32 *)(result + 0x20);
        v0 = *(s32 *)(result + 0x24);
        a0v = *(s32 *)(result + 0x28);
        *(s32 *)(s1 + 0x2C) = v1;
        *(s32 *)(s1 + 0x30) = v0;
        *(s32 *)(s1 + 0x34) = a0v;
        v0 = *(s32 *)(result + 0x44);
        *(s32 *)(s1 + 0x3C) = v0 << 8;
    }
    return *(s32 *)(s1 + 0x40);
}

s32 func_8007F158(s32 a0, s32 a1) {
    s32 v;

    if (a1 >= 0) {
        v = a0 | 0x2000;
    } else {
        v = a0 | 0x8000;
    }
    return v;
}

void func_8007F170(u8 *self, s32 flags) {
    func_8007C374(self, flags);
}

INCLUDE_ASM("asm/us/game/nonmatchings/18104", func_8007F190);

void func_8007F224(u8 *a0) {
    /* Pins preserve the retail list-link temporaries in $v0/$v1/$a1/$a2. */
    register u8 *v0 asm("$2");
    register u8 *v1 asm("$3");
    register u8 *a1 asm("$5");
    register u8 *a2 asm("$6");
    v0 = *(u8 **)a0;
    a1 = *(u8 **)v0;
    v1 = *(u8 **)(v0 + 4);
    *(u8 **)(a1 + 4) = v1;
    if (a0) {
        a2 = *(u8 **)(v0 + 4);
        v1 = *(u8 **)v0;
    } else {
        a2 = *(u8 **)(v0 + 4);
        v1 = *(u8 **)v0;
    }
    *(u8 **)a2 = v1;
    *(u8 **)v0 = v0;
    *(u8 **)(v0 + 4) = v0;
    v1 = *(u8 **)a0;
    a1 = *(u8 **)(a0 + 4);
    if (v1 == a1) {
        return;
    }
    v1 = *(u8 **)a1;
    v0 = *(u8 **)(a1 + 4);
    *(u8 **)(v1 + 4) = v0;
    a0 = *(u8 **)(a1 + 4);
    v0 = *(u8 **)a1;
    *(u8 **)a0 = v0;
    *(u8 **)a1 = a1;
    *(u8 **)(a1 + 4) = a1;
}

void func_8007F298(u8 *a0, s32 a1) {
    /* Pins hold mode, object, and callback addresses in retail registers. */
    u8 *s0 = a0;
    register s32 s1 asm("$17") = a1;
    register u8 *a2 asm("$6");
    /* Keep the original mode available after callbacks. */
    s32 mode;
    u8 *v0;
    s16 offset;
    register void (*callback)(u8 *, s32) asm("$3");
    *(u8 **)(s0 + 0x38) = D_800656AC;
    a2 = *(u8 **)s0;
    if (a2 != 0) {
        v0 = *(u8 **)(a2 + 0x14);
        offset = *(s16 *)(v0 + 0x18);
        callback = *(void (**)(u8 *, s32))(v0 + 0x1C);
        callback(a2 + offset, 3);
    }
    v0 = *(u8 **)s0;
    a2 = *(u8 **)(s0 + 4);
    mode = s1;
    if (v0 != a2 && a2 != 0) {
        v0 = *(u8 **)(a2 + 0x14);
        offset = *(s16 *)(v0 + 0x18);
        callback = *(void (**)(u8 *, s32))(v0 + 0x1C);
        callback(a2 + offset, 3);
    }
    if ((mode & 1) != 0) {
        func_8002B3D0(s0);
    }
}

void func_8007F340(u8 *a0, s32 a1) {
    /* Pin the state in the retail saved register. */
    register u8 *s1 asm("$17") = a0;
    if (*(s32 *)(s1 + 0x2C) != 0) {
        return;
    }
    if (func_80077838(*(u8 **)(s1 + 8)) ||
        func_80077860(*(u8 **)(s1 + 8))) {
        func_8007F4D4(s1, (a1 + (s32)((u32)a1 >> 31)) >> 1);
    }
    a1 = *(s32 *)(s1 + 0x20) - a1;
    if (a1 < 0) {
        a1 = 0;
    }
    *(s32 *)(s1 + 0x20) = a1;
}

void func_8007F3CC(u8 *a0, s32 a1) {
    /* Pin $v1 for the stored value's base while the sum stays in $a1. */
    register s32 v1 asm("$3") = *(s32 *)(a0 + 0x20);
    s32 a2 = *(s32 *)(a0 + 0x1C);
    a1 += v1;
    if (a1 > a2) {
        a1 = a2;
    }
    if (a1 < 0) {
        a1 = 0;
    }
    *(s32 *)(a0 + 0x20) = a1;
}

void func_8007F3FC(u8 *a0, s32 a1) {
    s32 v;
    if (*(s32 *)(a0 + 0x2C) != 0) {
        return;
    }
    v = *(s32 *)(a0 + 0x28) + (a1 << 12);
    if (v < *(s32 *)(a0 + 0x28)) {
        v = *(u16 *)((u8 *)func_8007773C(*(s32 *)(a0 + 8)) + 0x14);
    }
    *(s32 *)(a0 + 0x28) = v;
}

INCLUDE_ASM("asm/us/game/nonmatchings/18104", func_8007F45C);

void func_8007F490(u8 *arg0) {
    *(s32 *)(arg0 + 0x28) = 0;
}

s32 func_8007F498(u8 *arg0) {
    return !(*(s32 *)(arg0 + 0x28) < *(u16 *)((u8 *)func_8007773C(*(s32 *)(arg0 + 0x8)) + 0x14));
}

void func_8007F4D4(u8 *a0, s32 a1) {
    /* Pin $v1 for the stored value's base while the sum stays in $a1. */
    register s32 v1 asm("$3") = *(s32 *)(a0 + 0x24);
    a1 += v1;
    if (a1 > 0x10000) {
        a1 = 0x10000;
    }
    if (a1 < 0) {
        a1 = 0;
    }
    *(s32 *)(a0 + 0x24) = a1;
}

void func_8007F504(u8 *a0) {
    /* Pins preserve the state and entity across helper calls. */
    register u8 *s0 asm("$16") = a0;
    register u8 *s1 asm("$17");
    s32 value;
    register s32 s2 asm("$18");
    if (*(s32 *)(s0 + 0x2C) != 0) {
        return;
    }
    s1 = *(u8 **)(s0 + 8);
    s2 = *(u16 *)(u8 *)func_8007773C((s32)s1);
    value = func_8007F498(s0);
    if (!value) {
        value = *(s32 *)(s0 + 0x28) - 0x44;
        *(s32 *)(s0 + 0x28) = value;
        if (value < 0) {
            *(s32 *)(s0 + 0x28) = 0;
        }
    }
    value = s2 & 1;
    if (value == 0) {
        return;
    }
    value = func_80077860(s1);
    if (value != 0) {
        return;
    }
    value = *(s32 *)(s0 + 0x24) - 0x49;
    *(s32 *)(s0 + 0x24) = value;
    if (value < 0) {
        *(s32 *)(s0 + 0x24) = 0;
    }
    value = *(volatile s32 *)(s0 + 0x24);
    if (value > 0) {
        return;
    }
    value = func_8007B150(s1);
    if (value != 0) {
        func_8007FACC(s0);
    }

}
INCLUDE_ASM("asm/us/game/nonmatchings/18104", func_8007F5D8);

void func_8007F874(u8 *arg0) {
    *(s32 *)(arg0 + 0x2C) = 1;
}

/* Pins keep the state/table in $s1/$s0 and the fetched mode in $v1. */
s32 func_8007F880(u8 *a0) {
    register u8 *s1 asm("$17") = a0;
    register u8 *s0 asm("$16") = D_800656C4;
    register s32 v1 asm("$3");
    s32 index;
    index = func_8007760C(*(u8 **)(s1 + 8));
    if ((*(u16 *)(s0 + index * 0x180) & 1) != 0) {
        return 0;
    }
    if (!func_8007B150(*(u8 **)(s1 + 8))) {
        return 0;
    }
    v1 = func_80079518(*(u8 **)(s1 + 8));
    if (v1 == 0xB) return 0;
    if (v1 == 0xC) return 0;
    if (v1 == 0xD) return 0;
    if (v1 == 0xE) return 0;
    if (v1 == 0xF) return 0;
    if (v1 == 0x10) return 0;
    if (v1 == 0x13) return 0;
    return *(s32 *)(s1 + 0x24) > 0xFFFF;
}

s32 func_8007F94C(u8 *a0) {
    /* Pins preserve the retail table, comparison, and boolean result registers. */
    register u8 *s1 asm("$17") = a0;
    register u8 *s0 asm("$16");
    register s32 v0 asm("$2");
    register s32 a0ret asm("$4");
    s32 index;
    u16 flags;
    s0 = D_800656C4;
    index = func_8007760C(*(u8 **)(s1 + 8));
    flags = *(u16 *)(s0 + index * 0x180);
    if (func_80077860(*(u8 **)(s1 + 8))) {
        v0 = 0xFFFF;
        return v0 < *(s32 *)(s1 + 0x24);
    }
    if ((flags & 1) == 0) {
        a0ret = 0;
    } else {
        v0 = *(s32 *)(s1 + 0x24);
        a0ret = v0 != 0;
    }
    return a0ret;
}

INCLUDE_ASM("asm/us/game/nonmatchings/18104", func_8007F9D4);

void func_8007FA08(u8 *a0) {
    /* Pins match the retail bit-test and paired constant stores. */
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");
    u8 *p = *(u8 **)(a0 + 8);
    if (func_80077860(p) == 0) {
        return;
    }
    v1 = *(u16 *)(u8 *)func_8007773C((s32)p);
    if ((v1 & 2) != 0) {
        return;
    }
    func_8007FA78(a0);
    v0 = 0x1E;
    v1 = 3;
    *(s32 *)(a0 + 0x10) = v0;
    *(s32 *)(a0 + 0x18) = v1;
}

void func_8007FA78(u8 *a0) {
    u8 *p;
    func_8001BE78((s32)(u32)D_8005F824, 0x800E, 0);
    p = func_8002BD88(0x48);
    p = func_800C4C80(p, a0);
    func_8002BF34(*(u8 **)(a0 + 8), p);
}

void func_8007FACC(u8 *a0) {
    /* Pins keep the state and owned resource in the retail saved registers. */
    register u8 *s1 asm("$17") = a0;
    register u8 *s0 asm("$16");
    if (*(s32 *)(s1 + 0x14) > 0) {
        return;
    }
    s0 = *(u8 **)(s1 + 8);
    *(s32 *)(s1 + 0x14) = 0x10;
    func_8001BE78((s32)(u32)D_8005F824, 0x800F, 0);
    func_8002BF34(s0,
                  func_800C5210((s32)func_8002BD88(0x4A8), (s32)s1));
    func_8002BEE8(s0);
    func_80079D80(s0, 0x1E);
    func_80079D88(s0, 0x1E);
    func_80079D90(s0, 0x1E);
    func_8007F490(s1);
}

void func_8007FB74(u8 *a0) {
    /* Pin the source pointer in the retail saved register. */
    register u8 *s0 asm("$16") = *(u8 **)(a0 + 8);
    u8 *a0v = *(u8 **)(a0 + 4);
    if (s0 == a0v) {
        a0v = *(u8 **)a0;
    }
    *(u8 **)(a0 + 8) = a0v;
    func_80079794(a0v, s0);
    func_8002BEE8(s0);
}

s32 func_8007FBBC(s32 *a0) {
    return a0[2];
}

s32 func_8007FBC8(s32 *a0) {
    return a0[8];
}

s32 func_8007FBD4(s32 *a0) {
    return a0[7];
}

s32 func_8007FBE0(s32 *a0) {
    return a0[9];
}

s32 func_8007FBEC(s32 *a0) {
    return a0[10];
}

s32 *func_8007FBF8(s32 *a0, s32 a1) {
    a0[3] = (s32)&D_80068144;
    a0[0] = a1;
    a0[1] = 0;
    return a0;
}

/* Pin $v1 to keep the pointer separate from the returned value. */
s32 func_8007FC14(u8 *a0) {
    register u8 *v1 asm("$3") = *(u8 **)(a0 + 8);
    return *(s32 *)(v1 + 0x22C);
}

/* Pin $v1 to keep the pointer separate from the returned value. */
s32 func_8007FC28(u8 *a0) {
    register u8 *v1 asm("$3") = *(u8 **)(a0 + 8);
    return *(s32 *)(v1 + 0x230);
}

s32 func_8007FC3C(u8 *arg0) {
    return *(s32 *)func_8007FC28(arg0) == 1;
}

/* Pins preserve the $v1 base and $v0 bit result used by the retail sequence. */
s32 func_8007FC64(u8 *a0) {
    register u8 *v1 asm("$3") = *(u8 **)(a0 + 8);
    register u32 v0 asm("$2");
    v0 = *(u32 *)(v1 + 0x37C);
    return ((v0 >> 6) & 1) ^ 1;
}

s32 func_8007FC84(s32 *a0) {
    return ((u32)func_80075154(func_80077768(a0[2])) >> 2) & 1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/18104", func_8007FCB4);

s32 func_8007FD98(s32 *a0) {
    return ((u32)func_80075154(func_80077768(a0[2])) >> 14) & 1;
}

/* Pin $s0 to keep the saved transition state across helper calls. */
s32 func_8007FDC8(s32 *a0) {
    register s32 s0 asm("$16") = a0[0];
    if (func_8007FD98(a0)) {
        if ((s0 == 2) || (s0 == 0xA)) {
            return 0;
        }
        if (s0 == 9) {
            func_800816D0(a0);
            return 1;
        }
        func_80080E80(a0);
        return 1;
    }
    if (s0 == 0xA) {
        func_8008165C(a0);
        return 1;
    }
    if (s0 == 2) {
        func_80080BC4(a0, 1);
        return 1;
    }
    return 0;
}

/* Pin $v1 to keep the pointer separate from the returned value. */
s32 func_8007FE74(u8 *a0) {
    register u8 *v1 asm("$3") = *(u8 **)(a0 + 8);
    return *(s32 *)(v1 + 0x250);
}

s32 func_8007FE88(u8 *arg0) {
    return *(s32 *)(arg0 + 0x8) + 0x3A4;
}

void func_8007FE94(s32 *a0) {
    if (func_8007FC3C(a0)) {
        func_80078A64(a0[2], 0);
    }
}

void func_8007FECC(s32 *a0) {
    if (func_8007FC3C(a0)) {
        func_80078A7C(a0[2], 0);
    }
}

void func_8007FF04(u8 *a0, s32 a1, s32 a2) {
    func_80079964(*(u8 **)(a0 + 8), a1, a2, 0);
}

void func_8007FF28(u8 *a0, s32 a1, s32 a2) {
    func_80079AA4(*(u8 **)(a0 + 8), a1, a2, 0, -1);
}

void func_8007FF54(s32 *a0, s32 a1) {
    if (a1) {
        func_80079C80(a0[2]);
    } else {
        func_80079C14(a0[2]);
    }
}

void func_8007FF90(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x38);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x3C))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_8007FFD4(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x40);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x44))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080018(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x48);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x4C))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_8008005C(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x50);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x54))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_800800A0(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x58);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x5C))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_800800E4(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x60);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x64))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080128(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x68);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x6C))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_8008016C(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x70);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x74))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_800801B0(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x78);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x7C))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_800801F4(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x80);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x84))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080238(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x88);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x8C))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_8008027C(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x90);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x94))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_800802C0(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x98);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x9C))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080304(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xA0);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xA4))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080348(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xA8);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xAC))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_8008038C(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xB0);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xB4))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_800803D0(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xB8);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xBC))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080414(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xC0);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xC4))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080458(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xC8);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xCC))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_8008049C(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xD0);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xD4))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}
