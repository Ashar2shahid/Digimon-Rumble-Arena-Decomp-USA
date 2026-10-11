#include "game_action_api.h"
#include "game_placement_api.h"
#include "game_audio_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"

extern void func_80079DA0(void *a0, s32 a1);
extern void *func_80081CB8(void *a0);
extern void func_8007FF28(void *a0, s32 a1, s32 a2);
extern void *func_800826C4(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_80078B14(void *a0, s32 a1, s32 a2);
extern void *func_80082968(void *a0);
extern void *func_800829C0(void *a0);
extern void func_8007BCA0(void *a0);
extern void func_8007BEC0(void *a0);
extern void func_80079D58(void *a0);
extern void func_800787A0(void *a0, s32 a1);
extern void func_80082DD0(void *a0);
/* func_8007FBF8 returns void in retail, but a 64-bit return is a cc1 local-alloc
 * lever (reserves $v0/$v1) needed for func_80081CB8's exact register shape. */
extern long func_8007FBF8(void *a0, s32 a1);
extern void func_8007FF04(void *a0, s32 a1, s32 a2);
extern void func_8007FFD4(void *a0);
extern void func_800801B0(void *a0);
extern void func_800801F4(void *a0);
extern void *func_80080BC4(void *a0, s32 a1);
extern void *func_80076FD8(void *a0);
extern void func_8007B2B4(void *a0);
extern void func_8007B38C(void *a0);
extern void func_8007A97C(void *a0, s32 a1, s32 a2, s32 a3);
extern void *func_8007FC14(void *a0);
extern s32 func_8007FC3C(void *a0);
extern void func_8007FCB4(void *a0);
extern void *func_8007FE88(void *a0);
extern void func_8007FE94(void *a0, s32 a1);
extern void func_8007FECC(void *a0, s32 a1);
extern s32 func_8007F498(void *a0);
extern void func_8007F490(void *a0);
extern s32 func_80079A2C(void *a0, s32 a1);
extern void func_80079964(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8007760C(void *a0);
extern void func_8007FF90(void *a0);
extern u8 D_8006809C;
extern u8 D_800656C4;

extern s32 func_80077838(void *a0);
extern s32 func_800778EC(void *a0);
extern s32 func_80077978(void *a0);
extern s32 func_80077768(void *a0);
extern void *func_800778D0(void *a0);
extern s32 func_80075154(void *a0);
extern void func_800751FC(void *a0, s32 a1);
extern s32 func_800754E4(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_8007A718(void *a0);
extern void func_8007A3A0(void *a0, s32 a1);
extern void func_800802C0(void *a0);
extern void func_80080238(void *a0);
extern void *func_80081B4C(void *a0);
extern void func_80081E5C(void *a0, s32 a1);
extern void func_800820F0(void *a0);
extern void func_800821C4(void *a0);
extern void func_8008229C(void *a0);
extern void func_8008027C(void *a0);
extern void func_8007F45C(void *a0);
extern s32 func_8007FF54(void *a0, s32 a1);
extern s32 func_8007FE74(void);
extern s32 func_80079B68(void *a0, s32 a1);
extern s32 func_8007798C(void *a0, s32 a1);
extern s32 func_8007FC64(void *a0);
extern void *func_80082374(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_80079D98(void *a0, void *a1);
extern void *func_8002BE14(s32 a0);
extern void func_8002BF34(void *a0, void *a1);
extern void *func_800839D8(void *a0, void *a1);
extern void func_8007AFCC(void *a0, void *a1);
extern void func_8002BCEC(void *a0, s32 a1);
extern void func_8002BDA8(void *a0);
extern void func_80077774(void *a0, s32 a1);
extern s32 func_80077730(void *a0);
extern void func_80083BF4(void *a0, s32 a1);
extern void func_80083E68(void *a0, s32 a1);

extern void func_8007BB5C(void *a0, s32 a1);
extern s32 func_8007A084(void *a0);
extern void func_800C7574(void *a0, s32 a1);
extern u8 *func_800C72C0(u8 *self, u8 *owner, s32 *position, s32 *settings, s32 size, u32 mode, s32 scale, s32 flags);
extern void *func_800836D0(void *a0, void *a1, s32 a2, s32 a3, s32 a4);
extern void *func_80081D2C(void *a0, s32 a1);
extern void *func_800825E4(void *a0);
extern void func_80079BC4(void *a0);
extern void *func_80081A8C(void *a0);
extern void *func_8008189C(void *a0);
extern void *func_8008198C(void *a0, s32 a1);
extern void func_80080128(void *a0);
extern void func_8008016C(void *a0);
extern void func_80080018(void *a0);
extern void func_8008005C(void *a0);

extern void *func_80081194(void *a0, s32 a1, s32 a2);
extern void func_80081010(void *a0);
extern void *func_80080EC8(void *a0, s32 a1);
extern void *func_800812B4(void *a0, s32 a1);
extern void *func_800814D8(void *a0, s32 a1);
extern void *func_80081710(void *a0, s32 a1);
extern void func_800800A0(void *a0);
extern void func_800800E4(void *a0);

extern u8 D_8005F824;
extern u8 D_80067F4C;
extern u8 D_80067EDC;
extern u8 D_80067E34;
extern u8 D_80067EA4;
extern s32 D_80067CBC[];
extern s32 D_80067CC4[];
extern s32 D_80067CCC[];
extern s32 D_80067CD4[];
extern s32 D_80067CDC[];
extern s32 D_80067CE4[];
extern s32 D_80067CEC[];
extern s32 D_80067C34[];
extern u8 D_80067D84;
extern u8 D_80067DC4;
extern u8 D_8006842C;
extern u8 D_800681CC;
extern u8 D_800683BC;
extern u8 D_800683DC;
extern u8 D_80068394;
extern u8 D_8006836C;
extern u8 D_80010814;
extern u8 D_8006D730;
extern u8 D_8006D750;
extern u8 D_80065174;
extern u8 D_80065154;
extern u8 D_80067FF4;
extern u8 D_80067FBC;
extern u8 D_80067F84;
extern u8 D_8006802C;

extern u8 D_8006810C;
extern u8 D_80068064;
extern u8 D_80067DFC;
extern u8 D_80067E6C;
extern u8 D_800680D4;
extern u8 D_80068774;

extern s32 D_80067CF4[];
extern s32 D_80067CFC[];
extern u8 D_80067D44;
extern u8 D_80067D04;

void func_800804E0(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xD8);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xDC))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080524(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xE0);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xE4))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080568(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xE8);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xEC))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_800805AC(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xF0);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xF4))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_800805F0(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0xF8);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0xFC))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080634(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x100);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x104))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080678(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x108);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x10C))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_800806BC(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x110);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x114))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

void func_80080700(u8 *a0) {
    u8 *a3 = *(u8 **)(a0 + 8);
    u8 *a2 = *(u8 **)(a3 + 0x14);
    s16 v1 = *(s16 *)(a2 + 0x118);
    (*(void (**)(u8 *, s32, u8 *))(a2 + 0x11C))(a3 + v1, (*(s32 *)(a0 + 4))++, a2);
}

s32 func_80080744(void *a0) {
    s32 flags = func_80075154(a0);
    if (flags & 0x8000) {
        func_800751FC(a0, 0xA);
        if (func_800754E4(a0, 0x8000, 2, 0) != 0) {
            return 3;
        }
        return 1;
    }
    if (flags & 0x2000) {
        goto low_flag;
    }
    goto done;
low_flag:
    func_800751FC(a0, 0xA);
    if (func_800754E4(a0, 0x2000, 2, 0) != 0) {
        return 4;
    }
    return 2;
done:
    return 0;
}

void func_800807E8(void *a0, s32 a1) {
    s32 state = *(s32 *)func_8007FC14(a0);
    if (state == 9) {
        goto check_9;
    }
    if (state == 10) {
        goto check_10;
    }
    goto call;
check_9:
    if (a1 & 0x10000000) {
        goto call;
    }
    goto done;
check_10:
    if ((a1 & 0x08000000) == 0) {
        goto done;
    }
call:
    func_80081710(a0, a1);
done:
    ;
}

void func_80080868(void *a0) {
    void *a1 = *(void **)((u8 *)a0 + 8);
    u8 *v0 = *(u8 **)((u8 *)a1 + 0x14);
    (*(void (**)(void *))(v0 + 0x24))(a1 + *(s16 *)(v0 + 0x20));
    func_80081CB8(a0);
}

void *func_800808B4(void *a0) {
    s32 v0;
    u32 v1;
    u8 *tbl;
    func_8007FBF8(a0, 0);
    *(void **)((u8 *)a0 + 0xC) = &D_8006809C;
    tbl = &D_800656C4;
    v0 = func_8007760C(*(void **)((u8 *)a0 + 8));
    v1 = (v0 * 3) << 7;
    v1 += (u32)tbl;
    v0 = (((*(u16 *)v1) & 3) ^ 1) != 0;
    *(s32 *)((u8 *)a0 + 0x10) = v0;
    if (v0 == 0) {
        func_80079A2C(*(void **)((u8 *)a0 + 8), 0x1E);
    }
    *(s32 *)((u8 *)a0 + 0x14) = 0;
    func_8007FF90(a0);
    return a0;
}

void func_80080948(void *a0) {
    /* PIN: hold the incremented timer in the target's $v0 register. */
    register s32 count asm("$2") = *(s32 *)((u8 *)a0 + 0x14);
    count += 1;
    *(s32 *)((u8 *)a0 + 0x14) = count;
    if (count == 0xA) {
        if (*(s32 *)((u8 *)a0 + 0x10) != 0) {
            func_8007FF04(a0, 0x1E, 0);
        } else {
            void *context = *(void **)((u8 *)a0 + 8);
            func_80079964(context, 0x1E, 0, 0);
            func_80079964(*(void **)((u8 *)a0 + 8), 0x1E, 0x32, 1);
        }
    }
    {
        s32 current = *(s32 *)((u8 *)a0 + 0x14);
        if (current < 0x5A) {
            if (current < 0xB) {
                goto running;
            }
            if (func_8007FF54(a0, 0) == 0) {
                goto running;
            }
        }
        func_80080BC4(a0, 1);
        return;
    }
running:
    func_8007FF90(a0);
}

void *func_80080A08(void *a0) {
    register void *v1 asm("$3"); /* PIN $v1 - symbol address, retail keeps it in $v1 */
    func_8007FBF8(a0, 0x11);
    v1 = &D_8006810C;
    *(void **)((u8 *)a0 + 0xC) = v1;
    func_8007FF04(a0, 0x1D, 0xA);
    return a0;
}

void *func_80080A50(void *a0, s32 a1) {
    register void *v1 asm("$3"); /* PIN $v1 - symbol address, retail keeps it in $v1 */
    func_8007FBF8(a0, a1);
    v1 = &D_8006810C;
    *(void **)((u8 *)a0 + 0xC) = v1;
    return a0;
}

void *func_80080A84(void *a0) {
    func_80080A50(a0, 0x12);
    *(void **)((u8 *)a0 + 0xC) = &D_8006810C;
    func_8007FF04(a0, 0x1C, 0xA);
    return a0;
}

void *func_80080ACC(void *a0, s32 a1) {
    void *s0;
    func_8007FBF8(a0, 0x13);
    *(void **)((u8 *)a0 + 0xC) = &D_8006802C;
    *(s32 *)((u8 *)a0 + 0x10) = a1;
    func_8007FF04(a0, -1, 0);
    s0 = func_80077630(*(void **)((u8 *)a0 + 8));
    if (func_8007F498(s0) != 0) {
        func_8007F490(s0);
    }
    return a0;
}

void func_80080B4C(void *a0) {
    u8 *v0 = func_80077630(*(void **)((u8 *)a0 + 8));
    if (*(s32 *)(v0 + 0x20) <= 0) {
        func_8008198C(a0, 0xE);
    } else if (*(s32 *)((u8 *)a0 + 0x10) == 0) {
        func_80080BC4(a0, 1);
    } else if (*(s32 *)((u8 *)a0 + 0x10) > 0) {
        *(s32 *)((u8 *)a0 + 0x10) = *(s32 *)((u8 *)a0 + 0x10) - 1;
    }
}

void *func_80080BC4(void *a0, s32 a1) {
    func_8007FBF8(a0, a1);
    *(void **)((u8 *)a0 + 0xC) = &D_80068064;
    if (func_80077978(*(void **)((u8 *)a0 + 8)) == 0) {
        func_80081194(a0, 0, 0);
    } else if (*(s32 *)((u8 *)a0 + 0) == 1) {
        func_8007FF04(a0, 0, 4);
    }
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80080C40);

void func_80080DB4(void *a0, s32 a1) {
    if (a1 > 0 && func_8007FC3C(a0) != 0) {
        switch (*(s32 *)func_8007FC14(a0)) {
        case 2:
        case 9:
        case 10:
            break;
        default:
            func_80080EC8(a0, 0);
            break;
        }
    }
}

void func_80080E24(void *a0) {
    if (func_800778EC(*(void **)((u8 *)a0 + 8)) != 0) {
        if (func_8007FC3C(a0) != 0) {
            func_80081194(a0, 1, 0);
            func_8007A718(*(void **)((u8 *)a0 + 8));
        }
    }
}

void *func_80080E80(void *a0) {
    func_80080BC4(a0, 2);
    *(void **)((u8 *)a0 + 0xC) = &D_80068064;
    func_8008016C(a0);
    func_8007FCB4(a0);
    return a0;
}

void *func_80080EC8(void *a0, s32 a1) {
    func_8007FBF8(a0, 3);
    *(void **)((u8 *)a0 + 0xC) = &D_80067FF4;
    func_8001BE78((s32)(u32)&D_8005F824, 8, 0);
    *(s32 *)((u8 *)a0 + 0x10) = a1 + 1;
    func_80080128(a0);
    *(s32 *)((u8 *)a0 + 0x14) = 0;
    return a0;
}

void *func_80080F34(void *a0, s32 a1, s32 a2) {
    register void *v1 asm("$3"); /* PIN $v1 - symbol address, retail keeps it in $v1 */
    func_8007FBF8(a0, a1);
    *(s32 *)((u8 *)a0 + 0x10) = a2;
    v1 = &D_80067FF4;
    *(void **)((u8 *)a0 + 0xC) = v1;
    return a0;
}

void func_80080F78(void *a0) {
    s32 value = *(s32 *)((u8 *)func_8007FE88(a0) + 4);
    void *state = *(void **)((u8 *)a0 + 8);
    if (value >= 0) {
        func_80081194(a0, *(s32 *)((u8 *)a0 + 0x10), 1);
        return;
    }
    if (*(s32 *)((u8 *)a0 + 0x14) != 0) {
        s32 velocity = *(s32 *)((u8 *)state + 0x3C4);
        s32 delta = (s32)(((s64)velocity * 0x71C) >> 16);
        *(s32 *)((u8 *)state + 0x3B8) += delta;
    }
    *(s32 *)((u8 *)a0 + 0x14) = 1;
    func_80081010(a0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80081010);

void func_80081140(void *a0, s32 a1) {
    s32 v;
    *(s32 *)((u8 *)a0 + 0x14) = 0;
    if (a1 <= 0) {
        return;
    }
    if (func_8007FC3C(a0) == 0) {
        return;
    }
    v = *(s32 *)((u8 *)a0 + 0x10);
    if (v < 2) {
        func_80080EC8(a0, v);
    }
}

void *func_80081194(void *a0, s32 a1, s32 a2) {
    func_80080F34(a0, 4, a1);
    *(void **)((u8 *)a0 + 0xC) = &D_80067FBC;
    *(s32 *)((u8 *)a0 + 0x1C) = a2;
    func_8007FF04(a0, 4, 6);
    return a0;
}

void func_800811F4(void *a0) {
    u8 *s0 = *(u8 **)((u8 *)a0 + 8);
    if (func_80077978(s0) != 0 && *(s32 *)(s0 + 0x48C) <= 0) {
        s32 s1 = func_80077838(s0) ? 2 : 3;
        func_8007A97C(s0, 1, 0x60, s1);
        func_8007A97C(s0, -1, 0x60, s1);
        func_8001BE78((s32)(u32)&D_8005F824, 9, 0);
        func_80080BC4(a0, 1);
    } else {
        func_80081010(a0);
    }
}

void *func_800812B4(void *a0, s32 a1) {
    s32 v1;
    func_8007FBF8(a0, a1);
    *(void **)((u8 *)a0 + 0xC) = &D_80067F84;
    func_8001BE78((s32)(u32)&D_8005F824, 0xB, 0);
    v1 = *(s32 *)((u8 *)a0 + 0);
    if (v1 == 5) {
        func_80080018(a0);
        v1 = *(s32 *)((u8 *)a0 + 0);
    }
    if (v1 == 6) {
        func_8008005C(a0);
    }
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_8008132C);

void func_80081490(void *a0, s32 a1) {
    if (func_8007FC3C(a0) != 0 && a1 > 0) {
        func_80080EC8(a0, 0);
    }
}

/* Constructor family: retail keeps the symbol address in $v1 and the tag
   constant in $v0 (`lui $v1; addiu $v1; lw $s0; addiu $v0,7; bne; sw $v1`);
   the pinned base pointer reproduces it byte-exactly under the psyq46 slot cc1
   (and under esa4.5).  Last-resort `register asm`, flagged â€” see
   docs/DIFFICULT_FUNCTIONS.md Â§ Techniques accepted. */
void *func_800814D8(void *a0, s32 a1) {
    register void *v1 asm("$3"); /* PIN $v1 - symbol address, retail keeps it in $v1 */
    s32 s0;
    func_800812B4(a0, a1);
    v1 = &D_80067F4C;
    *(void **)((u8 *)a0 + 0xC) = v1;
    s0 = *(s32 *)a0;
    if (s0 == 7) {
        func_800800A0(a0);
    }
    if (s0 == 8) {
        func_800800E4(a0);
    }
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_8008153C);

void *func_8008165C(void *a0) {
    func_80080BC4(a0, 9);
    *(void **)((u8 *)a0 + 0xC) = &D_80068064;
    func_800801B0(a0);
    return a0;
}

void *func_8008169C(void *a0, s32 a1) {
    func_80080BC4(a0, a1);
    *(void **)((u8 *)a0 + 0xC) = &D_80068064;
    return a0;
}

void *func_800816D0(void *a0) {
    func_8008169C(a0, 0xA);
    *(void **)((u8 *)a0 + 0xC) = &D_80068064;
    func_800801F4(a0);
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80081710);

void func_80081800(void *a0) {
    u8 *v;
    u8 *s0 = *(u8 **)((u8 *)a0 + 8);
    v = func_80077630(s0);
    *(s32 *)((u8 *)a0 + 0x10) = *(s32 *)((u8 *)a0 + 0x10) - 1;
    if (func_80077978(s0) == 0) {
        func_8008189C(a0);
    } else if (*(s32 *)(v + 0x20) <= 0) {
        func_8008198C(a0, 0xE);
    } else if (*(s32 *)((u8 *)a0 + 0x10) < 0) {
        func_80080BC4(a0, 1);
    }
}

void *func_8008189C(void *a0) {
    func_8007FBF8(a0, 0xC);
    *(void **)((u8 *)a0 + 0xC) = &D_80067EDC;
    func_8007A3A0(*(void **)((u8 *)a0 + 8), 0);
    *(s32 *)((u8 *)a0 + 0x10) = 4;
    func_800802C0(a0);
    return a0;
}

void func_800818F0(void *a0) {
    s32 v = *(s32 *)((u8 *)a0 + 0x10) - 1;
    s32 s1;
    *(s32 *)((u8 *)a0 + 0x10) = v;
    if (v < 0) {
        if (func_80077978(*(void **)((u8 *)a0 + 8)) != 0) {
            s1 = func_80077838(*(void **)((u8 *)a0 + 8)) ? 2 : 3;
            func_8007A97C(*(void **)((u8 *)a0 + 8), 1, 0x60, s1);
            func_8007A97C(*(void **)((u8 *)a0 + 8), -1, 0x60, s1);
            func_8008198C(a0, 0xE);
        }
    }
}

void *func_8008198C(void *a0, s32 a1) {
    func_8007FBF8(a0, a1);
    *(void **)((u8 *)a0 + 0xC) = &D_80067EA4;
    if (a1 == 0xD) {
        goto phase_d;
    }
    if (a1 == 0xE) {
        goto phase_e;
    }
phase_d:
    func_8007FF04(a0, 0x10, 1);
    *(s32 *)((u8 *)a0 + 0x10) = 0x16;
    goto done;
phase_e:
    func_8007FF04(a0, 0x11, 2);
    *(s32 *)((u8 *)a0 + 0x10) = 0;
done:
    return a0;
}

void func_80081A0C(void *a0) {
    s32 v;
    if (*(s32 *)(func_80077630(*(void **)((u8 *)a0 + 8)) + 0x20) <= 0) {
        return;
    }
    v = *(s32 *)((u8 *)a0 + 0x10) - 1;
    *(s32 *)((u8 *)a0 + 0x10) = v;
    if (v > 0) {
        return;
    }
    if (func_80077978(*(void **)((u8 *)a0 + 8)) == 0) {
        return;
    }
    if (func_8007FF54(a0, 0) != 0) {
        func_80081A8C(a0);
    }
}

void *func_80081A8C(void *a0) {
    register void *v1 asm("$3"); /* PIN $v1 - symbol address, retail keeps it in $v1 */
    func_8007FBF8(a0, 0xF);
    v1 = &D_80067E6C;
    *(void **)((u8 *)a0 + 0xC) = v1;
    func_8007FFD4(a0);
    return a0;
}

void func_80081ACC(void *a0) {
    if (func_8007FF54(a0, 0) != 0) {
        if (func_8007F498(func_80077630(*(void **)((u8 *)a0 + 8))) != 0) {
            func_80081B4C(a0);
        } else {
            *(s32 *)(*(void **)((u8 *)a0 + 8) + 0x498) = 8;
            func_80080BC4(a0, 1);
        }
    } else {
        func_8007FFD4(a0);
    }
}

void *func_80081B4C(void *a0) {
    func_8007FBF8(a0, 0x10);
    *(void **)((u8 *)a0 + 0xC) = &D_80067E34;
    func_80080238(a0);
    *(s32 *)((u8 *)a0 + 0x10) = 0;
    return a0;
}

void func_80081B90(void *self) {
    u8 *owner = func_80077630(*(void **)((u8 *)self + 8));
    if (*(s32 *)(owner + 0x20) <= 0) {
        func_8008198C(self, 0xE);
    } else {
        func_80080238(self);
        if ((s32)(*(u32 *)((u8 *)self + 0x10))++ % 22 == 0) {
            func_8001BE78((s32)(u32)&D_8005F824, 0xC, 0);
        }
        if (func_8007FF54(self, 0) != 0) {
            func_8007F490(owner);
            func_80080BC4(self, 1);
        }
    }
}

void func_80081C70(void *a0, s32 a1) {
    func_8007F490(func_80077630(*(void **)((u8 *)a0 + 8)));
    func_80081710(a0, a1);
}

void *func_80081CB8(void *a0) {
    register void *v1 asm("$3"); /* PIN $v1 - symbol address, retail keeps it in $v1 */
    u8 *v0;
    func_8007FBF8(a0, 1);
    v0 = *(u8 **)((u8 *)a0 + 8);
    v1 = &D_80067DFC;
    *(void **)((u8 *)a0 + 0xC) = v1;
    *(s32 *)(v0 + 0x448) = 0;
    return a0;
}

void *func_80081CF8(void *a0, s32 a1) {
    register void *v1 asm("$3"); /* PIN $v1 - symbol address, retail keeps it in $v1 */
    func_8007FBF8(a0, a1);
    v1 = &D_80067DFC;
    *(void **)((u8 *)a0 + 0xC) = v1;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80081D2C);

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80081E5C);

void func_800820F0(void *a0) {
    s32 v1 = func_8007FE74();
    void *s0 = *(void **)((u8 *)a0 + 8);
    if (v1 < 5) {
        if (v1 < 3) {
            goto other;
        }
        if (func_80079B68(s0, 0x17) != 0) {
            return;
        }
        if (func_8007798C(s0, 2) == 0) {
            return;
        }
        func_80082374(a0, 0x1E, D_80067CBC[0], D_80067CBC[1]);
        func_80078B14(s0, 0xA, 0x64);
        return;
    }
other:
    if (func_80079B68(s0, 0x16) != 0) {
        return;
    }
    func_80082374(a0, 0x1D, D_80067CC4[0], D_80067CC4[1]);
    func_80078B14(s0, 0xA, 0x64);
}

void func_800821C4(void *a0) {
    s32 v1 = func_8007FE74();
    void *s0 = *((void **)((u8 *)a0 + 8));
    if (v1 < 5) {
        if (v1 < 3) {
            goto other;
        }
        if (func_80079B68(*((void **)((u8 *)a0 + 8)), 0x19) != 0) {
            return;
        }
        if (func_8007798C(*((void **)((u8 *)a0 + 8)), 3) == 0) {
            return;
        }
        func_80082374(a0, 0x20, D_80067CCC[0], D_80067CCC[1]);
        func_80078B14(s0, 0xB, 0x3E8);
        return;
    }
other:
    if (func_80079B68(s0, 0x18) != 0) {
        return;
    }
    func_80082374(a0, 0x1F, D_80067CD4[0], D_80067CD4[1]);
    func_80078B14(s0, 0xB, 0x3E8);
}

void func_8008229C(void *a0) {
    void *s0 = *(void **)((u8 *)a0 + 8);
    s32 v1 = func_8007FE74();
    if (v1 < 5) {
        if (v1 < 3) {
            goto other;
        }
        if (func_80079B68(s0, 0x1B) != 0) {
            return;
        }
        if (func_8007798C(s0, 4) == 0) {
            return;
        }
        func_80082374(a0, 0x22, D_80067CDC[0], D_80067CDC[1]);
        func_80078B14(s0, 0xC, 0xBB8);
        return;
    }
other:
    if (func_80079B68(s0, 0x1A) != 0) {
        return;
    }
    func_80082374(a0, 0x21, D_80067CE4[0], D_80067CE4[1]);
    func_80078B14(s0, 0xC, 0xBB8);
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80082374);

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80082430);

void func_80082548(void *a0) {
    u8 *a1 = *(u8 **)((u8 *)a0 + 8);
    u8 *v0 = *(u8 **)(a1 + 0x14);
    s16 off = *(s16 *)(v0 + 0x20);
    void (*fn)(void *) = *(void (**)(void *))(v0 + 0x24);
    fn(a1 + off);
    func_80081CB8(a0);
    func_8007FF28(a0, -1, 0);
}

void func_800825A4(void *a0, s32 a1) {
    if (func_8007FC64(a0) == 0) {
        func_80081D2C(a0, a1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_800825E4);

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_800826C4);

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80082790);

void func_80082884(void *a0, s32 a1) {
    if (func_8007FC64(a0) == 0 && a1 == 0) {
        u8 *v0;
        s16 off;
        void (*fn)(void *);
        *(s32 *)((u8 *)a0 + 0x10) = 1;
        func_8007FF28(a0, -1, 0);
        v0 = *(u8 **)((u8 *)a0 + 0xC);
        off = *(s16 *)(v0 + 0x30);
        fn = *(void (**)(void *))(v0 + 0x34);
        fn((u8 *)a0 + off);
    }
}

void func_800828F4(void *a0) {
    func_80082968(a0);
}

void func_80082914(void *a0) {
    func_80081CB8(a0);
    func_8007FF28(a0, -1, 0);
}

void func_80082948(void *a0) {
    func_800829C0(a0);
}

void *func_80082968(void *a0) {
    func_800826C4(a0, 0x15, D_80067CF4[0], D_80067CF4[1]);
    *(void **)((u8 *)a0 + 0xC) = &D_80067D44;
    func_80078B14(*(void **)((u8 *)a0 + 8), 1, 0x64);
    return a0;
}

void *func_800829C0(void *a0) {
    func_800826C4(a0, 0x16, D_80067CFC[0], D_80067CFC[1]);
    *(void **)((u8 *)a0 + 0xC) = &D_80067D04;
    func_80078B14(*(void **)((u8 *)a0 + 8), 2, 0xC8);
    return a0;
}

void func_80082A18(void) {
}

void func_80082A20(void) {
}

void func_80082A28(void) {
}

void func_80082A30(void) {
}

void func_80082A38(void) {
}

s32 func_80082A40(s32 a0, s32 a1) {
    return a1;
}

s32 func_80082A48(s32 *a0) {
    return *a0;
}

void *func_80082A54(void *a0, s32 a1) {
    register void *v1 asm("$3"); /* PIN $v1 - symbol address, retail keeps it in $v1 */
    func_8007FBF8(a0, a1);
    v1 = &D_8006810C;
    *(void **)((u8 *)a0 + 0xC) = v1;
    return a0;
}

void *func_80082A88(void *a0, s32 a1) {
    register void *v1 asm("$3"); /* PIN $v1 - symbol address, retail keeps it in $v1 */
    func_8007FBF8(a0, a1);
    v1 = &D_800680D4;
    *(void **)((u8 *)a0 + 0xC) = v1;
    return a0;
}

void func_80082ABC(void) {
}

void *func_80082AC4(void *a0) {
    func_80076FD8(a0);
    *(void **)((u8 *)a0 + 0x14) = &D_8006842C;
    func_80079D98(a0, &D_800681CC);
    return a0;
}

void func_80082B08(void *a0) {
    func_80079DA0(a0, 0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80082B28);

void func_80082C78(void *a0, s32 a1) {
    func_8007BCA0(a0);
    func_80079D58(a0);
    switch (a1) {
    case 0:
        func_80078754(a0, 0x77);
        func_80079DA0(a0, 1);
        break;
    case 0xD:
        func_800787A0(a0, 0x73);
        func_80079DA0(a0, 0);
        func_80082DD0(a0);
        break;
    }
}

void func_80082D08(void *a0, s32 a1) {
    func_8007BEC0(a0);
    func_80079D58(a0);
    switch (a1) {
    case 0:
        func_80078754(a0, 0x77);
        func_80079DA0(a0, 1);
        break;
    case 7:
        func_800787A0(a0, 0x73);
        func_80079DA0(a0, 0);
        func_80082DD0(a0);
        break;
    }
    if (a1 < 8) {
        *(s32 *)((u8 *)a0 + 0x3B4) = *(s32 *)((u8 *)a0 + 0x3B4) - (*(s32 *)((u8 *)a0 + 0x3A4) >> 4);
        if (*(s32 *)((u8 *)a0 + 0x3A8) > 0) {
            *(s32 *)((u8 *)a0 + 0x3B8) = *(s32 *)((u8 *)a0 + 0x3B8) - *(s32 *)((u8 *)a0 + 0x3A8);
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80082DD0);

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80082EE8);

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80083094);

void func_80083164(void *a0) {
    void *s0 = func_8002BE14(0x4C);
    if (s0 != 0) {
        func_800839D8((u8 *)func_8002BD80(0x4C, s0), a0);
    }
    func_8007AFCC(a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_800831C0);

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_800832C8);

u8 *func_800833E0(u8 *self, u8 *owner, s32 *position, s32 *settings) {
    func_800C72C0(self, owner, position, settings,
                   0x80, 0x05A81C00, 0xA00, 3);
    *(u8 **)(self + 0x18) = &D_800683BC;
    *(u8 **)(self + 0x14) = &D_800683DC;
    *(s32 *)(self + 0xC0) = 0;
    return self;
}

void func_80083448(void *a0) {
    if (*(u32 *)((u8 *)a0 + 0xB8) & 1) {
        s32 v = *(s32 *)((u8 *)a0 + 0xC0) + 1;
        *(s32 *)((u8 *)a0 + 0xC0) = v;
        if (v >= 5) {
            *(s32 *)((u8 *)a0 + 0xC0) = 1;
        }
    }
    func_800C7478();
}

void func_8008349C(void *a0, s32 a1) {
    void *s0 = func_8002BE14(0x38);
    if (s0 != 0) {
        func_800836D0((u8 *)func_8002BD80(0x38, s0), (u8 *)a0 + 0x80, 0x180, 0xC0,
                      *(s32 *)((u8 *)a0 + 0xBC));
    }
    func_8002BF34(a0, s0);
    func_800C7574(a0, a1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80083520);

void *func_800836D0(void *a0, void *a1, s32 a2, s32 a3, s32 a4) {
    /* PIN: keep constructor arguments in the target's saved registers. */
    register s32 arg2 asm("$19") = a2;
    register s32 arg3 asm("$18") = a3;
    register s32 arg4 asm("$20") = a4;
    s32 v0;
    s32 v1;
    s32 v2;
    func_8002BC9C(a0, 0);
    *(void **)((u8 *)a0 + 0x14) = &D_80068394;
    v0 = *(s32 *)a1;
    v1 = *(s32 *)((u8 *)a1 + 4);
    v2 = *(s32 *)((u8 *)a1 + 8);
    *(s32 *)((u8 *)a0 + 0x30) = arg2;
    *(s32 *)((u8 *)a0 + 0x2C) = arg3;
    *(s32 *)((u8 *)a0 + 0x34) = arg4;
    *(s32 *)((u8 *)a0 + 0x28) = 0;
    *(s32 *)((u8 *)a0 + 0x18) = v0;
    *(s32 *)((u8 *)a0 + 0x1C) = v1;
    *(s32 *)((u8 *)a0 + 0x20) = v2;
    return a0;
}

void func_80083760(void *a0) {
    s32 v0 = *(s32 *)((u8 *)a0 + 0x28);
    s32 v1 = *(s32 *)((u8 *)a0 + 0x2C);
    v0 += 0x10;
    *(s32 *)((u8 *)a0 + 0x28) = v0;
    if (v0 < v1) {
        return;
    }
    if (a0 != 0) {
        u8 *p = *(u8 **)((u8 *)a0 + 0x14);
        (*(void (**)(void *, s32))(p + 0x1C))(a0 + *(s16 *)(p + 0x18), 3);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_800837BC);

void *func_800839D8(void *a0, void *a1) {
    func_8002BC9C(a0, 0);
    *(void **)((u8 *)a0 + 0x14) = &D_8006836C;
    *(void **)((u8 *)a0 + 0x18) = a1;
    func_8007A724((u8 *)a1, (u8 *)a0 + 0x1C, 2, &D_80010814);
    *(s32 *)((u8 *)a0 + 0x2C) = 0x80;
    *(s32 *)((u8 *)a0 + 0x30) = 0x180;
    *(s32 *)((u8 *)a0 + 0x34) = 0;
    *(s32 *)((u8 *)a0 + 0x38) = 0;
    *(s32 *)((u8 *)a0 + 0x3C) = 0;
    *(s32 *)((u8 *)a0 + 0x40) = 0;
    *(s32 *)((u8 *)a0 + 0x44) = 0;
    *(s32 *)((u8 *)a0 + 0x48) = func_80077730(a1);
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80083A68);

void func_80083B80(void *a0, s32 a1) {
    switch (*(s32 *)((u8 *)a0 + 0x40)) {
    case 0:
        func_80083BF4(a0, a1);
        break;
    case 1:
        func_80083BF4(a0, a1);
        func_80083E68(a0, a1);
        break;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80083BF4);

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80083E68);

void func_80084024(void *a0, s32 a1) {
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_8008406C(void *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800840B4(void *a0, s32 a1) {
    u8 *v1;
    u32 a2, a0v, v0;
    *(void **)((u8 *)a0 + 0x18) = &D_8006D730;
    *(void **)((u8 *)a0 + 0x14) = &D_8006D750;
    *(void **)((u8 *)a0 + 0x68) = &D_80065174;
    v1 = (u8 *)a0 + 0x38;
    a2 = *(u32 *)((u8 *)a0 + 0x38);
    a0v = *(u32 *)((u8 *)a0 + 0x3C);
    *(u32 *)(a2 + 4) = a0v;
    a2 = *(u32 *)(v1 + 4);
    v0 = *(u32 *)((u8 *)a0 + 0x38);
    *(u32 *)(a2 + 0) = v0;
    *(u32 *)((u8 *)a0 + 0x38) = (u32)v1;
    *(u32 *)((u8 *)a0 + 0x3C) = (u32)v1;
    *(void **)((u8 *)a0 + 0x18) = &D_80065154;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80084154(void *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_8008419C(void *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void *func_800841E4(void *a0) {
    func_80076FD8(a0);
    *(void **)((u8 *)a0 + 0x14) = &D_80068774;
    *(s16 *)((u8 *)a0 + 0x4A4) = 0;
    *(s16 *)((u8 *)a0 + 0x4A6) = 0;
    return a0;
}

void func_80084220(void *a0, s32 a1) {
    *(void **)((u8 *)a0 + 0x14) = &D_80068774;
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_80084274(void *a0) {
    *(u16 *)((u8 *)a0 + 0x4A6) = 0;
}

void func_8008427C(void *a0) {
    func_8007B2B4(a0);
    func_8007A97C(a0, -1, 0xA0, 4);
}

void func_800842B4(void *a0) {
    func_8007B38C(a0);
    func_8007A97C(a0, -1, 0xA0, 4);
}

void func_800842EC(void *a0, s32 a1) {
    func_8007BB5C(a0, a1);
    if (a1 < 0x12 && (a1 & 3) == 0) {
        func_8007A97C(a0, -1, 0xA0, 2);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_80084340);

INCLUDE_ASM("asm/us/game/nonmatchings/1C120", func_800844D8);
