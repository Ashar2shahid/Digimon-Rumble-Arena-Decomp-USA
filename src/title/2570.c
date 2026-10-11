#include "game_thread.h"
#include "game_sprite_cleanup.h"
#include "game_lerp_words.h"
#include "game_audio_api.h"
#include "common.h"
#include "game_input.h"

extern u8 D_8006447C;

INCLUDE_ASM("asm/us/title/nonmatchings/2570", func_80066930);

extern u8 D_80064424[];
extern s32 D_8005F81C;
extern s32 D_80114210;
extern void func_8002B82C();
extern void func_80066BF0();

/* PINS: $s1 the returned x byte, $s2 y, $v0 x/index temporary, $a1
 * state/step, $v1 compare/x delta, $t2 index, $t0 currentX, $a3 currentY,
 * $a2 next table entry, and $t1 current table entry. */
void func_800669F4(s32 *arg0) {
    register s32 a1 asm("$5") = arg0[9];
    register s32 v1 asm("$3") = 1;
    register s32 t3 asm("$11") = D_80114210;
    register s32 color asm("$17");
    register s32 x asm("$2");
    register s32 y asm("$18");
    s32 new_var2;
    register s32 index asm("$10");
    register u8 *new_var asm("$2");
    register s32 indexPlusOne asm("$2");

    new_var2 = v1;
    if (a1 != new_var2) {
        if (a1 < 2) {
            if (a1 == 0) {
                index = arg0[10];
                new_var = D_80064424;
                a1 = arg0[11];
                {
                    s32 denominator;
                    register u8 *cur asm("$9");
                    register u8 *next asm("$6");
                    cur = new_var + index * 4;
                    new_var += 4;
                    next = new_var + index * 4;
                    denominator = *(s16 *)next;

                    v1 = next[2];
                    {
                        register s32 currentX asm("$8") = cur[2];
                        v1 -= currentX;
                        x = v1 * a1 / denominator;
                        x = (currentX + x) & 0xFF;
                        color = x;
                    }
                    x = next[3];
                    {
                        register s32 currentY asm("$7") = cur[3];
                        x -= currentY;
                        y = x * a1 / denominator;
                        y = (currentY + y) & 0xFF;
                    }
                    a1++;
                    arg0[11] = a1;
                    v1 = *(s16 *)next;
                    a1 = a1 < v1;
                    if (a1 == 0) {
                        indexPlusOne = index + 1;
                        arg0[10] = indexPlusOne;
                        a1 = 0;
                        arg0[11] = a1;
                        if (indexPlusOne >= 3) {
                            arg0[9] = 2;
                            goto draw;
                        }
                    }
                    if ((func_80027004(t3, -1) & 0x8F0) != 0) {
                        *(s16 *)((u8 *)arg0 + 0x30) = color;
                        *(s16 *)((u8 *)arg0 + 0x32) = y;
                        arg0[9]++;
                    }
                    goto draw;
                }
            }
        }
        goto mode_other;
    }

    x = *(s16 *)((u8 *)arg0 + 0x30);
    color = *(u8 *)((u8 *)arg0 + 0x30);
    v1 = x - 8;
    if (v1 < 0) {
        v1 = 0;
    }
    x = *(s16 *)((u8 *)arg0 + 0x32);
    x -= 8;
    *(s16 *)((u8 *)arg0 + 0x30) = v1;
    if (x < 0) {
        x = 0;
    }
    *(s16 *)((u8 *)arg0 + 0x32) = x;
    if (arg0[12] == 0) {
        arg0[11] = 0;
        arg0[9] = 2;
    }
    goto draw;

mode_other:
    arg0[11]++;
    if (arg0[11] < 4) {
        return;
    }
    func_8002B82C(arg0);
    return;

draw:
    {
        s32 object = D_8005F81C;
        func_80066BF0(object, 0, color);
        func_8005844C(object, func_800280A0(0x2A));
    }
}

INCLUDE_ASM("asm/us/title/nonmatchings/2570", func_80066BF0);

extern void func_8002B770();

void func_80066CF4(void) {
    func_8002B770();
}

void func_80066D14(s32 a0, s32 a1) {
    register s32 a2 asm("$6") = *(s32 *)(a0 + 0x1C);
    *(s32 *)(a0 + 0x20) = a1;
    (*(void (**)(s32))(a2 + 0x24))(a0 + *(s16 *)(a2 + 0x20));
}

extern s32 D_8007A630;

s32 func_80066D48(s32 arg0) {
    return arg0 * 180 / (D_8007A630 - 1) + 0x8F;
}

extern u8 *func_800280A0();
extern u8 *func_80028050();
extern void func_8005848C();
extern void func_8005844C();

u8 *func_80066D84(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4) {
    u8 *a;
    u8 *b;

    a = func_800280A0(*(u16 *)arg3);
    b = func_80028050();
    *(s32 *)(b + 0x8) = (arg2 << 16) | (arg1 & 0xFFFF);
    *(s32 *)(b + 0xC) = *(s32 *)(arg3 + 4);
    *(s32 *)(b + 0x10) = *(s32 *)(arg3 + 8);
    if (arg4 == 0) {
        func_8005848C(b, 0);
    } else {
        func_8005848C(b, 1);
    }
    func_8005844C(arg0, b);
    func_8005844C(arg0, a);
    return b;
}

INCLUDE_ASM("asm/us/title/nonmatchings/2570", func_80066E5C);

extern u8 *func_8002DD5C();

void func_80067100(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4) {
    u8 *s1; s32 s0; s32 s2; s32 s3; s32 s4; s32 s5;

    s0 = arg4;
    s3 = arg3[4];
    s2 = arg3[5];
    s4 = *(s16 *)(arg3 + 8);
    s5 = (s16)(*(u16 *)(arg3 + 0xA) - 1);
    s1 = func_8002DD5C(arg0);
    if (s0 == 0) {
        s1[0xC] = s3 + (s4 - 1); s1[0xD] = s2; s1[0x14] = s3; s1[0x15] = s2;
        s1[0x1C] = s3 + (s4 - 1); s1[0x1D] = s2 + s5; s1[0x24] = s3; s1[0x25] = s2 + s5;
    } else {
        s1[0xC] = s3; s1[0xD] = s2; s1[0x14] = s3 + s4; s1[0x15] = s2;
        s1[0x1C] = s3; s1[0x1D] = s2 + s5; s1[0x24] = s3 + s4; s1[0x25] = s2 + s5;
    }
    *(s16 *)(s1 + 0x8) = arg1;
    *(s16 *)(s1 + 0xA) = arg2;
    *(s16 *)(s1 + 0x10) = s4 + arg1;
    *(s16 *)(s1 + 0x12) = arg2;
    *(s16 *)(s1 + 0x18) = arg1;
    *(s16 *)(s1 + 0x1A) = s5 + arg2;
    *(s16 *)(s1 + 0x20) = s4 + arg1;
    *(s16 *)(s1 + 0x22) = s5 + arg2;
    *(s16 *)(s1 + 0xE) = *(u16 *)(arg3 + 6);
    func_8005848C(s1, 0);
    *(s16 *)(s1 + 0x16) = *(u16 *)(arg3 + 0);
    s1[4] = 0x80; s1[5] = 0x80; s1[6] = 0x80;
    func_8005844C(arg0, s1);
}

void func_80067250(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4) {
    u8 *s1; s32 s0; s32 s2; s32 s3; s32 s4; s32 s5;

    s0 = arg4; s3 = arg3[4]; s2 = arg3[5];
    s4 = *(s16 *)(arg3 + 8);
    s5 = (s16)(*(u16 *)(arg3 + 0xA) - 1);
    s1 = func_8002DD5C(arg0);
    if (s0 == 0) {
        s1[0xC] = s3 + (s4 - 1); s1[0xD] = s2; s1[0x14] = s3; s1[0x15] = s2;
        s1[0x1C] = s3 + (s4 - 1); s1[0x1D] = s2 + s5; s1[0x24] = s3; s1[0x25] = s2 + s5;
    } else {
        s1[0xC] = s3; s1[0xD] = s2; s1[0x14] = s3 + s4; s1[0x15] = s2;
        s1[0x1C] = s3; s1[0x1D] = s2 + s5; s1[0x24] = s3 + s4; s1[0x25] = s2 + s5;
    }
    *(s16 *)(s1 + 0x8) = arg1; *(s16 *)(s1 + 0xA) = arg2;
    *(s16 *)(s1 + 0x10) = s4 + arg1; *(s16 *)(s1 + 0x12) = arg2;
    *(s16 *)(s1 + 0x18) = arg1; *(s16 *)(s1 + 0x1A) = s5 + arg2;
    *(s16 *)(s1 + 0x20) = s4 + arg1; *(s16 *)(s1 + 0x22) = s5 + arg2;
    *(s16 *)(s1 + 0xE) = *(u16 *)(arg3 + 6) + 0x40;
    func_8005848C(s1, 1);
    *(s16 *)(s1 + 0x16) = 0x58;
    s1[4] = 0x40; s1[5] = 0x40; s1[6] = 0x40;
    func_8005844C(arg0, s1);
}

INCLUDE_ASM("asm/us/title/nonmatchings/2570", func_800673A4);

extern u8 D_8005F824[];

s32 func_800674B8(void) {
    return func_8001BE78((s32)(u32)D_8005F824, 0xF, 0);
}

s32 func_800674E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 != 0) {
        return -1;
    }
    func_8001BE78((s32)(u32)D_8005F824, 0x11, 0);
    return 0;
}

s32 func_80067520(s32 a0, s32 a1, s32 a2) {
    func_8002C3CC(a0, 0);
    *(s32 *)(a0 + 0x30) = a2;
    *(s32 *)(a0 + 0x20) = a1;
    *(u32 *)(a0 + 0x1C) = (u32)&D_8006447C;
    *(s32 *)(a0 + 0x24) = 0;
    *(s32 *)(a0 + 0x28) = 0x2000;
    *(s32 *)(a0 + 0x2C) = 0;
    return a0;
}

s32 func_80067588(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 != 0) {
        return 0;
    }
    if (arg0[12] == 1) {
        func_8001BE78((s32)(u32)D_8005F824, 0x12, 0);
        return -1;
    }
    func_8001BE78((s32)(u32)D_8005F824, 0x10, 0);
    return 0;
}

extern void func_8002C530();

s32 func_800675E8(s32 *arg0) {
    arg0[9] += 0x180;
    if (arg0[9] >= 0x5A00) {
        func_8002C530(arg0, arg0[3]);
    }
    return 1;
}

INCLUDE_ASM("asm/us/title/nonmatchings/2570", func_80067628);

extern s32 D_8005F928;

s32 func_8006774C(void) {
    return (D_8005F928 & 0x380) != 0;
}

INCLUDE_ASM("asm/us/title/nonmatchings/2570", func_80067764);

extern u8 D_800644DC[];
extern void func_8002C6B0();

void func_80067A30(s32 *arg0, s32 arg1) {
    arg0[7] = (s32)D_800644DC;
    func_8001EAD4(((u8 *)&D_8005F884), 0);
    func_8002D86C((u8 *)arg0 + 0x70, 2);
    func_8002C6B0((u8 *)arg0 + 0x2C, 2);
    func_8001EFB0((GameThread *)((u8 *)arg0 + 0x20), 2);
    func_8002B770(arg0, arg1);
}

INCLUDE_ASM("asm/us/title/nonmatchings/2570", func_80067AA8);

INCLUDE_ASM("asm/us/title/nonmatchings/2570", func_80067BF0);

extern u8 D_800192A8[];
extern void func_8002B3D0();

void func_80067EA4(s32 *arg0, s32 arg1) {
    s32 a2 = arg0[0];
    s32 a0 = arg0[1];

    arg0[7] = (s32)D_800192A8;
    ((s32 *)a2)[1] = a0;
    ((s32 *)arg0[1])[0] = arg0[0];
    arg0[0] = (s32)arg0;
    arg0[1] = (s32)arg0;
    if (arg1 & 1) {
        func_8002B3D0(arg0);
    }
}

s32 func_80067EFC(s32 arg0, s32 arg1, s32 arg2, u8 *arg3) {
    s32 *r = (s32 *)func_80028050();

    r[2] = (arg2 << 16) | (arg1 & 0xFFFF);
    r[3] = *(s32 *)(arg3 + 4);
    r[4] = *(s32 *)(arg3 + 8);
    func_8005844C(arg0, r);
    func_8005844C(arg0, (s32 *)func_800280A0(*(u16 *)arg3));
    return (s32)r;
}

INCLUDE_ASM("asm/us/title/nonmatchings/2570", func_80067F98);

INCLUDE_ASM("asm/us/title/nonmatchings/2570", func_80068178);

extern s32 D_800641A4;
extern u8 D_800645F8[];
extern s32 func_8001F278();
extern s32 func_8001BCF8();
extern s32 func_8001BCC4();
extern void func_80068D8C();
extern s32 func_8006ABAC();

void func_800682F0(s32 *arg0, s32 arg1) {
    arg0[7] = (s32)D_800645F8;
    func_8001F278(D_800641A4, 0, 0, 0);
    func_8001BCF8(D_8005F824);
    func_8001BCC4(D_8005F824);
    func_80068D8C((u8 *)arg0 + 0x38, 2);
    func_8006ABAC((u8 *)arg0 + 0x24, 2);
    func_8002B770(arg0, arg1);
}
