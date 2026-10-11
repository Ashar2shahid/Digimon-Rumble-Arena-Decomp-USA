#include "game_heap_wrappers.h"
#include "game_thread.h"
#include "game_stepper_child_api.h"
#include "game_sprite_cleanup.h"
#include "game_lerp_words.h"
#include "game_rotation.h"
#include "game_audio_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_save_config.h"
#include "game_md5.h"
#include "game_sort.h"
#include "game_formatter.h"
#include "game_handles.h"

extern u8 D_80065144;

extern u8 D_8005F910[];

extern u8 D_8005F8B8;

extern s32 D_8007A5B8;
extern u8 D_8005F824[];
extern s32 D_80114210;

extern void func_8006BE1C();

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006A964);

extern u8 *func_8002DDC4();
extern s32 func_8005844C();

void func_8006AA34(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    register s32 *s7 asm("$23") = arg1;
    register s32 s0 asm("$16") = arg2;
    register s32 s1 asm("$17") = arg3;
    register s32 s2 asm("$18") = arg4;
    register s32 s3 asm("$19") = arg5;
    register s32 s4 asm("$20") = arg6;
    register s32 s5 asm("$21") = arg7;
    register s32 s6 asm("$22") = arg8;
    u8 *p = func_8002DDC4(arg0);

    *(s16 *)(p + 8) = s0;
    *(s16 *)(p + 0xA) = s1;
    *(s16 *)(p + 0xC) = s2;
    *(s16 *)(p + 0xE) = s3;
    p[4] = s4;
    p[5] = s5;
    p[6] = s6;
    p[7] |= 2;
    func_8005844C((s32)s7, p);
}

s32 func_8006AAE0(s32 *arg0) {
    return arg0[0];
}

s32 func_8006AAEC(s32 *arg0) {
    return arg0[1];
}

s32 func_8006AAF8(u8 *arg0) {
    return *(s32 *)(arg0 + 0x68);
}

s32 func_8006AB04(s32 *arg0) {
    return arg0[2];
}

void func_8006AB10(s32 *arg0, s32 arg1) {
    arg0[3] = arg1;
}

extern void func_8006AEEC(s32 *);

s32 *func_8006AB18(s32 *self, u8 *entries, s32 count) {
    self[1] = (s32)entries;
    self[2] = (s32)entries;
    self[0] = count;
    self[4] = 0;
    if (func_8006AE04(self) == -1) {
        func_8006AEEC(self);
    }
    count--;
    if (count != -1) {
        do {
            *(u8 **)entries = entries + 0x40;
            count--;
            entries += 0x40;
        } while (count != -1);
    }
    *(u32 *)(entries - 0x40) = 0;
    return self;
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006ABAC);

typedef struct TitleSortState {
    u32 unknown0;
    u32 unknown4;
    SortNode *head;
    SortNode *cursor;
} TitleSortState;

SortNode *func_8006B028(TitleSortState *state);
s32 func_8006B060(SortNode *left, SortNode *right);

SortNode *func_8006ACA4(TitleSortState *state) {
    return state->cursor = func_8006B028(state);
}

SortNode *func_8006ACCC(TitleSortState *state) {
    SortNode *node = state->cursor;
    if (node == 0) {
        return 0;
    }
    node = node->next;
    state->cursor = node;
    return node;
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006ACF8);

extern s32 func_8003E1AC();
extern s32 func_8003E15C();

s32 func_8006AD8C(s32 *arg0, s32 arg1, s32 arg2) {
    s32 v = arg0[4];

    if (v != 0) {
        u8 *p = (u8 *)(v + 0xC);

        *(s32 *)(v + 8) = arg2;
        *(u8 *)(v + 0xC) = 0;
        if ((u32)func_8003E1AC(arg1) < 0x24) {
            func_8003E15C(p, arg1);
            arg0[4] = 0;
            return 0;
        }
    }
    return -1;
}

extern s32 func_8003DF1C(const void *, const void *, s32);

s32 func_8006AE04(s32 *self) {
    s32 count = self[0];
    u8 *entry = (u8 *)self[1];
    u8 buffer[0x10];

    count--;
    if (count == -1) {
        return 0;
    }
    do {
        func_8006AE7C(entry, buffer);
        if (func_8003DF1C(buffer, entry + 0x30, 0x10) != 0) {
            return -1;
        }
        count--;
        entry += 0x40;
    } while (count != -1);
    return 0;
}

void func_8006AE7C(s32 *arg0, u8 *digest) {
    Md5Context context;

    func_800383B4(&context);
    func_80038418(&context, (u8 *)(arg0 + 1), 4);
    func_80038418(&context, (u8 *)(arg0 + 2), 4);
    func_80038418(&context, (u8 *)(arg0 + 3), 0x24);
    func_80037250(&context, digest);
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006AEEC);

SortNode *func_8006B028(TitleSortState *state) {
    return state->head = func_80038610(state->head, func_8006B060);
}

s32 func_8006B060(SortNode *left, SortNode *right) {
    return (s32)((u32)right->word4.key - (u32)left->word4.key);
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006B070);

extern void func_8005858C();
extern s32 func_8005859C();

void func_8006B210(void) {
    u8 buf[0x18];

    func_8005858C();
    while (func_8005859C(buf) != 0) {
        u16 *p = (u16 *)*(s32 *)(buf + 8);

        if (p != 0) {
            u8 *v = *(u8 **)(buf + 4);
            s32 n = *(s16 *)(v + 4) * *(s16 *)(v + 6);
            u16 *q = p;

            if (n > 0) {
                do {
                    *q |= 0x8000;
                    q++;
                } while (--n);
            }
        }
    }
}

s32 func_8006B294(u8 *arg0) {
    s32 v = 0;
    u8 c = *arg0;

    arg0++;
    while (c != 0) {
        if (c == 10) {
            v++;
        }
        c = *arg0;
        arg0++;
    }
    return v;
}

void func_8006B2D0(s32 *arg0, u8 *arg1) {
    u8 *start = arg1;
    u8 c = *arg1;

    arg1++;
    while (c != 0) {
        if (c == 10) {
            *arg0 = (s32)start;
            arg0++;
            start = arg1;
            arg1[-1] = 0;
        }
        c = *arg1;
        arg1++;
    }
}

extern u8 D_80064888[];
extern s32 func_8001C1C0();
extern s32 func_8002B3F8();
extern s32 func_800321D0();
extern void func_8002B770();

void func_8006B318(s32 *arg0, s32 arg1) {
    arg0[7] = (s32)D_80064888;
    func_8001C1C0(arg0);
    if (arg0[9] != 0) {
        func_8002B3F8(arg0[9]);
    }
    if (arg0[0xA] != 0) {
        func_8002B3F8(arg0[0xA]);
    }
    if (arg0[0xB] != 0) {
        func_800321D0(arg0[0xB], 3);
    }
    func_8002B2B4((void *)(u32)arg0[0xC]);
    func_8001EAD4(((u8 *)&D_8005F884), 0);
    func_8002B770(arg0, arg1);
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006B3C4);

extern s32 *func_800280A0(s32);
extern s32 *func_80028050(void);

void func_8006B624(s32 target, s32 x, s32 y, s32 brightness) {
    if (brightness != 0) {
        u8 *sprite = (u8 *)func_800280A0(0xD);
        u8 *cmd = (u8 *)func_80028050();
        *(s16 *)(cmd + 8) = x - 0x80;
        cmd[4] = brightness;
        cmd[5] = brightness;
        cmd[6] = brightness;
        *(s16 *)(cmd + 0xA) = y;
        cmd[0xC] = 0;
        cmd[0xD] = 0;
        *(s16 *)(cmd + 0x10) = 0x100;
        *(s16 *)(cmd + 0x12) = 0x78;
        *(s16 *)(cmd + 0xE) = 0x3DA0;
        func_8005844C(target, cmd);
        func_8005844C(target, sprite);
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006B6D4);

void func_8006B800(s32 a0, s32 a1) {
    register s32 a2 asm("$6") = *(s32 *)(a0 + 0x1C);
    *(s32 *)(a0 + 0x20) = a1;
    (*(void (**)(s32))(a2 + 0x24))(a0 + *(s16 *)(a2 + 0x20));
}

s32 func_8006B834(s32 arg0) {
    s32 t = (arg0 + D_8007A5B8) & 1;

    return 0x2D - t * 10;
}

s32 func_8006B860(s32 arg0) {
    return (arg0 + D_8007A5B8) * 17 + 0x33;
}

extern s32 func_8005844C();
extern s32 *func_80028050();
extern s32 *func_800280A0();

s32 func_8006B880(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *s2 = func_80028050();

    s2[2] = (arg2 << 16) | (arg1 & 0xFFFF);
    s2[3] = *(s32 *)(arg3 + 4);
    s2[4] = *(s32 *)(arg3 + 8);
    func_8005844C(arg0, (s32)s2);
    func_8005844C(arg0, func_800280A0(*(u16 *)arg3));
    return (s32)s2;
}

extern s32 *func_8002E688();

s32 func_8006B91C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 *s3 = func_8002E688();

    s3[2] = (arg2 << 16) | (arg1 & 0xFFFF);
    s3[3] = *(s32 *)(arg3 + 4) + (arg4 << 4);
    func_8005844C(arg0, (s32)s3);
    func_8005844C(arg0, func_800280A0(*(u16 *)arg3));
    return (s32)s3;
}

extern s32 func_8002C418();
extern void func_8006BB40();

void func_8006B9C4(s32 *arg0) {
    if (func_8002C418(arg0[0]) == 0) {
        func_8001BE78((s32)(u32)D_8005F824, 0x13, 0);
    }
    func_8006BB40(arg0);
}

void func_8006BA10(s32 **arg0) {
    if (func_8002C494(*arg0) == 0) {
        func_8001BE78((s32)(u32)D_8005F824, 0x13, 0);
        if ((*arg0)[3] == 6) {
            s32 temp_a0 = D_80114210;

            func_80026F0C(temp_a0, 0, 0, 0xFF, 0xFF, 0xA, 0);
        }
    }
    func_8006BB40(arg0);
}

extern s32 D_8005F914;
extern s32 D_8005F918;
extern s32 D_8005F91C;
extern s32 D_8005F920;

void func_8006BA9C(s32 *self) {
    switch (((s32 *)self[0])[3]) {
    case 0:
        ((s32 *)self[0])[4] = D_8005F920;
        return;
    case 1:
        ((s32 *)self[0])[4] = *(s32 *)D_8005F910;
        return;
    case 2:
        ((s32 *)self[0])[4] = D_8005F918;
        return;
    case 3:
        ((s32 *)self[0])[4] = D_8005F914 == 0;
        return;
    case 6:
        ((s32 *)self[0])[4] = D_8005F91C == 0;
        return;
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006BB40);

s32 func_8006BC2C(void) {
    return func_8001BE78((s32)(u32)D_8005F824, 0xF, 0);
}

s32 func_8006BC58(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 != 0) {
        return -1;
    }
    return 0;
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006BC6C);

s32 func_8006BD9C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 != 0) {
        return 0;
    }
    func_8001BE78((s32)(u32)D_8005F824, 0x10, 0);
    return 0;
}

s32 func_8006BDD0(s32 *arg0) {
    arg0[2] += 0x20;
    return 1;
}

/* PIN $v0 table base and $a0 signed sample for this lookup. */

s32 func_8006BDE8(s32 *arg0, s32 arg1) {
    register u8 *table asm("$2") = ((u8 *)&D_8001093C);
    s32 index = (arg0[2] & 0xFFF) << 2;
    register s32 sample asm("$4") = *(s16 *)(table + index);
    s32 result = sample >> 7;

    if (arg1 == 0) {
        return result + 0x40;
    }
    return result + 0x80;
}

extern s32 func_8006BDE8();

void func_8006BE1C(arg0, arg1, arg2, arg3)
s32 *arg0;
s32 arg1;
s32 arg2;
s32 arg3;
{
    s32 s1 = *(s32 *)(arg0[0] + 0xC);
    s32 s0;
    s32 v;
    u8 *p;

    s0 = func_8006B834(s1);
    v = func_8006B860(s1);
    p = func_8006B880(arg1, s0, v, arg0[1]);
    if (arg3 == 0) {
        arg0[2] = 0;
    }
    v = func_8006BDE8(arg0, arg2);
    p[4] = v;
    p[5] = v;
    p[6] = v;
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006BEC4);

void func_8006C01C(s32 *self, s32 context, s32 option, s32 arg3) {
    s32 *animation;
    s32 *entry;
    s32 frame;
    s32 x;
    s32 y;
    u8 *sprite;
    s32 color;

    func_8006BE1C(self, context, option, arg3);
    animation = (s32 *)self[0];
    entry = (s32 *)(self[3] + animation[4] * 4);
    frame = animation[3];
    x = func_8006B834(frame) + 0x80;
    y = func_8006B860(frame);
    sprite = (u8 *)func_8006B880(context, x, y, entry[0]);
    color = func_8006BDE8(self, option);
    sprite[4] = color;
    sprite[5] = color;
    sprite[6] = color;
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006C0CC);

extern u8 D_8005EE2C[];
extern s32 func_8002B364();
extern s32 func_8006ECC8();

s32 func_8006C21C(s32 *arg0) {
    s32 s0;

    if (func_80036F34(D_8005FE04, arg0[5]) != 0) {
        return -1;
    }
    s0 = func_8006ECC8(func_8002B364(0x58), arg0[3]);
    func_8002BB30((PriorityList *)D_8005EE2C, (PriorityNode *)(u32)s0);
    arg0[4] = s0;
    arg0[5] = *(s32 *)(s0 + 0xC);
    return 0;
}

extern s32 func_8002C4F4(s32);
extern s32 func_8002C810(s32, s32);

s32 func_8006C298(s32 *arg0) {
    s32 v;

    func_8006BDD0(arg0);
    if (func_80036F34(D_8005FE04, arg0[5]) != 0) {
        return 1;
    }
    v = arg0[3];
    arg0[4] = 0;
    arg0[5] = 0;
    if (v == 0) {
        func_8002C810(func_8002C4F4(arg0[0]), 0);
    }
    return 0;
}

s32 func_8006C304(void) {
    return -1;
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006C30C);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006C47C);

void func_8006C5C0(s32 a0) {
    register u8 *v0 asm("$2") = &D_8005F8B8;
    register s32 a1 asm("$5") = *(s16 *)(v0 + 0x6C);
    register s32 v1 asm("$3");
    *(s32 *)(a0 + 0xC) = a1;
    *(s32 *)(a0 + 0x14) = a1;
    v1 = *(s16 *)(v0 + 0x6E);
    *(s32 *)(a0 + 0x10) = v1;
    *(s32 *)(a0 + 0x18) = v1;
}

s32 func_8006C5EC(s32 a0) {
    register s32 v1 asm("$3") = a0;
    u8 *v0 = &D_8005F8B8;
    s32 t = *(s32 *)(v1 + 0x14);
    s32 a1;
    *(s32 *)(v1 + 0xC) = t;
    *(s16 *)(v0 + 0x6C) = t;
    a1 = *(s32 *)(v1 + 0x18);
    *(s32 *)(v1 + 0x10) = a1;
    *(s16 *)(v0 + 0x6E) = a1;
    func_8001E734(v0 + 0x58);
    func_8001BE78((s32)(u32)D_8005F824, 0x11, 0);
    return 0;
}

s32 func_8006C644(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8001BE78((s32)(u32)D_8005F824, 0x10, 0);
    if (arg3 != 0) {
        arg0[7] = 0;
        arg0[5] = arg0[3];
        arg0[6] = arg0[4];
        return -1;
    }
    arg0[7] = 1;
    return 0;
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006C6B0);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006C7CC);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006C888);

extern s32 func_80068E84();

s32 func_8006C9EC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 != 0) {
        return -1;
    }
    func_8001BE78((s32)(u32)D_8005F824, 0x10, 0);
    func_80068E84(arg0 + 3);
    func_8002C500((void *)(u32)arg0[0], 0);
    return 0;
}

extern s32 func_80069028();
extern s32 func_80069178();

s32 func_8006CA44(s32 *arg0) {
    if (arg0[3] != 0) {
        func_80069028(arg0 + 3);
        func_80069178(arg0 + 3);
        return 1;
    }
    func_8002C500((void *)(u32)arg0[0], 1);
    return 0;
}

void func_8006CA98(void) {
    func_8006BE1C();
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006CAB8);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006CBF0);



s32 func_8006CD28(s32 *self, s32 arg1, s32 arg2, s32 enabled) {
    u8 *base = D_8005F910;
    s32 index = *(s32 *)(self[0] + 0xC);
    func_8001BE78((s32)(u32)D_8005F824, 0x10, 0);
    if (enabled != 0) {
        func_8001E924((SaveConfig *)base, 0, index, self[4]);
        func_8001E924((SaveConfig *)base, 1, index, self[5]);
        func_8002C810(func_8002C4F4(self[0]), 0);
        self[3] = 0;
    } else {
        self[4] = func_8001E900(base, 0, index);
        self[5] = func_8001E900(base, 1, index);
        self[3] = 1;
    }
    return 0;
}

s32 func_8006CE08(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 != 0) {
        s32 v = arg0[0];
        s32 p = *(s32 *)(v + 0x1C);

        ((void (*)(s32, s32))*(s32 *)(p + 0x4C))(v + *(s16 *)(p + 0x48), 0);
        func_8001BE78((s32)(u32)D_8005F824, 0x11, 0);
    }
    return 0;
}

void func_8006CE5C(s32 a0) {
    u8 *s0 = D_8005F910;
    s32 s2 = *(s32 *)(*(s32 *)a0 + 0xC);
    *(s32 *)(a0 + 0x10) = func_8001E900(s0, 0, s2);
    *(s32 *)(a0 + 0x14) = func_8001E900(s0, 1, s2);
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006CEC4);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006CFE0);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006D100);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006D3F8);

s32 func_8006D574(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_8007A5B8 = 1;
    if (arg3 != 0) {
        return 0;
    }
    func_8001BE78((s32)(u32)D_8005F824, 0x10, 0);
    func_8002C500((void *)(u32)arg0[0], 0);
    func_8002C810(func_8002C4F4(arg0[0]), 0);
    return 0;
}

extern void func_8002CA5C(void);

void func_8006D5E0(void) {
    func_8002CA5C();
}

extern s32 func_8002CFB0();
extern s32 func_8006B834();
extern s32 func_8006B860();
extern u8 D_80064D98[];

void func_8006D600(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 == 0) {
        func_8006BE1C(arg0 + 9, arg1, arg2, 0);
    } else {
        s32 s0;
        u8 *p;

        func_8002CFB0(arg0, arg1);
        s0 = func_8006B834(-1) + 0x84;
        p = func_8006B880(arg1, s0, func_8006B860(-1), D_80064D98);
        p[4] = 0x80;
        p[5] = 0x80;
        p[6] = 0x80;
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006D684);

extern u8 D_80064C68[];
extern s32 func_8002C6B0();
extern void func_8002B770();

void func_8006D97C(s32 *arg0, s32 arg1) {
    arg0[7] = (s32)D_80064C68;
    func_8001EAD4(((u8 *)&D_8005F884), 0);
    func_8002D86C(arg0 + 0x1D, 2);
    func_8002C6B0(arg0 + 0xC, 2);
    func_8001EFB0((GameThread *)(arg0 + 8), 2);
    func_8002B770(arg0, arg1);
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006D9F4);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006DB1C);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006DD08);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006DE6C);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006DFD0);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006E140);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006E2A4);

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006E408);

s32 func_8006E554(void) {
    return -1;
}

s32 func_8006E55C(void) {
    return -1;
}

extern u8 D_8005F910[];

extern s32 func_8002C4F4(s32);
extern s32 func_8002C810(s32, s32);

s32 func_8006E564(s32 *arg0) {
    func_8001BE78((s32)(u32)D_8005F824, 0x10, 0);
    func_8001E7A4((SaveConfig *)D_8005F910);
    func_8002C810(func_8002C4F4(arg0[0]), 0);
    return -1;
}

extern s32 func_8002CA28(void *ctx);

s32 func_8006E5C0(void *ctx) {
    s32 v;

    v = func_8002CA28(ctx);
    if (v == 0) {
        D_8007A5B8 = 0;
    }
    return v;
}

struct ItemList;
extern void func_8002D0A0(struct ItemList *list, s32 value);

void func_8006E5F0(struct ItemList *list, s32 value) {
    func_8002D0A0(list, value);
}


s32 *func_8006E610(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8002BC9C(arg0, 0);
    arg0[9] = arg1;
    arg0[0xA] = arg2;
    arg0[0xB] = arg3;
    arg0[5] = (s32)&D_80065144;
    arg0[6] = 0;
    arg0[7] = 0;
    arg0[8] = 0;
    arg0[0xC] = arg4;
    return arg0;
}


void func_8006E694(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    register s32 s2 asm("$18") = arg2;
    register s32 s3 asm("$19") = arg3;
    s32 v = func_8003E1AC(s2);
    s32 x = (arg0[0xB] - (v << 3)) / 2;
    s32 y = arg0[0xA] + s3;

    arg1[0] = arg0[9] + x;
    arg1[1] = y;
    func_800327B0(arg1, (const u8 *)s2);
}

void func_8006E71C(s32 *arg0, s32 arg1) {
    arg0[7] = 1;
    arg0[8] = arg1;
}

s32 func_8006E72C(s32 *arg0) {
    arg0[7] = 1;
    return 1;
}

void func_8006E738(s32 *arg0) {
    arg0[7] = 0;
}

s32 func_8006E740(u8 *arg0) {
    return *(u32 *)(arg0 + 0x18) == 0x1000;
}

void func_8006E754(s32 *arg0) {
    if (arg0[7] != 0) {
        s32 v = arg0[6];

        if (v != 0x1000) {
            v += 0x111;
            arg0[6] = v;
            if (v >= 0x1001) {
                arg0[6] = 0x1000;
            }
        }
    } else {
        s32 v = arg0[6] - 0x111;

        arg0[6] = v;
        if (v < 0) {
            arg0[6] = 0;
        }
    }
}

void func_8006E7AC(s16 *arg0, s32 arg1) {
    s32 w = arg0[2];
    s32 h = arg0[3];
    s32 nw = (w * arg1) >> 12;
    s32 nh = (h * arg1) >> 12;

    if (nw == 0) {
        nw = 1;
    }
    if (nh == 0) {
        nh = 1;
    }
    arg0[2] = nw;
    *(u16 *)(arg0 + 0) = *(u16 *)(arg0 + 0) + (w - nw) / 2;
    arg0[3] = nh;
    *(u16 *)(arg0 + 1) = *(u16 *)(arg0 + 1) + (h - nh) / 2;
}

s32 func_8006E830(u8 *arg0) {
    s32 v = 1;
    u8 c = *arg0;

    arg0++;
    while (c != 0) {
        if (c == 10) {
            v++;
        }
        c = *arg0;
        arg0++;
    }
    return v;
}

u8 *func_8006E86C(u8 *arg0, u8 *arg1) {
    u8 c = *arg1;

    arg1++;
    while (c != 0 && c != 10) {
        *arg0 = c;
        arg0++;
        c = *arg1;
        arg1++;
    }
    *arg0 = 0;
    return c != 0 ? arg1 : 0;
}

INCLUDE_ASM("asm/us/title/nonmatchings/65A4", func_8006E8C0);
