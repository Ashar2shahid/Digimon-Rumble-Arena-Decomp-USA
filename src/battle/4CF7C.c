#include "game_rotation.h"
#include "game_action_api.h"
#include "game_velocity_api.h"
#include "game_b5bd8_constructors.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_actor_queries.h"
#include "game_random.h"

extern void func_8002BCEC(s32, s32);
extern void func_8002BDA8(s32);
extern void func_8007BB5C(s32);
extern void func_8007A97C(s32, s32, s32, s32);
extern s32 func_80053EFC(s32, s32);
extern void func_80077774(s32, s32);
extern void func_80076FD8(s32);
extern void func_80079D98(s32, s32);

extern s32 func_80078AD8(s32);
extern void func_800C4100(s32);
extern void func_800C3F98(s32, s32, s32, s32);
extern s32 func_8002BE14(s32);

extern s32 func_8007A084(s32);
extern void func_80079AA4(s32, s32, s32, s32, s32);
extern void func_80079D80(s32, s32);
extern void func_8007AFCC(s32, s32);
extern void func_800B2E60(s32, s32);
extern void func_800B2FC8(s32, s32);
extern s32 func_800B3C48(s32, s32, s32);
extern void func_800B525C(s32);
extern void func_800B5318(s32);
extern s32 func_80077730(s32);
extern void func_800C72C0(s32, s32, s32, s32);
extern void func_800C7478(s32);
extern s32 func_800B1D78(s32, s32, s32, s32, s32);
extern s32 func_800B2C7C(s32, s32, s32, s32);
extern s16 func_800B396C(s32, s32);
extern void func_800B18D0(s32, s32);
extern void func_800B19A8(s32, s32);
extern s32 func_800B24F8(s32, s32, s32, s32);
extern s32 func_800B3120(s32, s32, s32, s32, s32);
extern s32 func_800B41F0(s32, s32, s32, s32, s32);
extern void func_800B3788(s32);
extern void func_800B51C8(s32);

extern void func_800B53A4(s32, s32, s32, s32, s32);
extern u8 D_80065154;
extern u8 D_80065174;
extern u8 D_8006BC24;
extern u8 D_8006BC44;
extern u8 D_8006BAD4;
extern u8 D_8006BAF4;
extern u8 D_8006D730;
extern u8 D_8006D750;
extern void func_800794D4(s32, s32);
extern void func_8007C064(s32, s32, s32, s32, s32);
extern void func_80075F88(s32, s32, s32, s32);
extern s32 func_80077618(s32);
extern void func_8006F02C(s32, s32);
extern void func_8006F00C(s32, s32);
extern s32 func_800237A0(s32);
extern s32 func_80076D18(s32, s32, s32);
extern void func_800787A0(s32, s32);
extern s32 func_80079040(s32);
extern void func_800774C8(s32, s32);
extern void func_80079158(s32, s32, s32, s32);
extern u8 D_80010814;
extern void func_800254CC(s32, s32, s32, s32);
extern void func_8002447C(s32, s32, s32, s32);
extern void func_800213C4(s32);
extern s32 func_8002E860(s32, s32, s32, s32);
extern u8 D_800641B8;
extern u8 D_8006BA40;
extern u8 D_8006BA60;
extern void func_80024340(s32, s32, s32, s32);
extern void func_8007BC50(s32);
extern void func_80079964(s32, s32, s32, s32);
extern void func_8007A358(s32, s32);
extern s32 func_8007A0C4(s32, s32, s32, s32);
extern s32 func_80077978(s32);
extern void func_80079580(s32);

extern void func_800C357C(s32, s32, s32, s32, s32);
extern s32 func_80079C80(s32);
extern s32 func_8002087C(s32);
extern s32 func_80024688(s32, s32, s32);
extern u8 D_80010884;
extern u8 D_8006BA00;

extern u8 D_8006BA20;
extern u8 D_8006BA80;
extern void func_800C591C(s32, s32, s32, s32, s32, s32);
extern void func_80079D6C(s32);
extern void func_8007C0A0(s32, s32, s32);
extern void func_8007C0AC(s32, s32);
extern void func_80079D58(s32);
extern void func_80079D88(s32, s32);
extern s32 func_80079F68(s32, s32);
extern s32 func_80078FC4(s32);

extern void func_800C7898(s32, s32, s32);
extern void func_8002BF34(s32, s32);
extern u8 D_800D372C;
extern u8 D_8006B86C;
extern u8 D_8006B92C;
extern u8 D_8006BAA0;
extern u8 D_8006BAC0;
extern u8 D_8006BB44;
extern u8 D_8006BB64;
extern u8 D_8006BB1C;
extern u8 D_8006BBD4;
extern u8 D_8006BBFC;
extern u8 D_8006BE0C;
extern u8 D_8006BED4;
extern u8 D_8006BC6C;
extern u8 D_800D373C;
extern u8 D_8006B91C;
extern u8 D_8006BB8C;
extern u8 D_8006BBAC;

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B133C);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B14D8);

s32 func_800B1724(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    register s32 s0 asm("$16");
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");
    func_800C3F98(a0, a3, a4, 0xFFC080);
    s0 = a0;
    v0 = s0;
    __asm__ volatile ("" : "+r" (v0) : : "memory");
    v1 = (s32)&D_8006BC6C;
    *(s32 *)(s0 + 0x14) = v1;
    *(s32 *)(s0 + 0x54) = a1;
    v1 = 12;
    *(s32 *)(s0 + 0x4C) = v1;
    *(s32 *)(s0 + 0x50) = 24;
    return v0;
}

void func_800B1788(s32 a0) {
    s32 buf[4];
    func_800C4100(a0);
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    func_8007A724((u8 *)*(s32 *)(a0 + 0x54), (void *)(a0 + 0x28), 3, (u8 *)buf);
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B17D0);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B18D0);

void func_800B19A8(s32 a0, s32 a1) {
    s32 s0;
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");
    register s32 a0v asm("$4");
    s32 buf[8];
    buf[4] = 0;
    buf[5] = 0;
    buf[6] = 0;
    buf[7] = 0;
    func_8007A724((u8 *)a0, buf, 0x14, (u8 *)&buf[4]);
    v0 = func_8007A084(a0);
    v1 = *(volatile s32 *)&buf[0];
    a0v = *(volatile s32 *)&buf[1];
    v0 <<= 7;
    *(volatile s32 *)&buf[2] = 0;
    v1 += v0;
    buf[0] = v1;
    v0 = a0v - 0x40;
    buf[1] = v0;
    if (a1 != 0) {
        v0 = a0v + 0x1B;
        buf[1] = v0;
    }
    s0 = func_8002BE14(0x3C);
    if (s0 != 0) {
        func_800B24F8((s32)(u32)func_8002BD80(0x3C, (void *)(u32)s0), a0, (s32)buf, a1);
    }
    func_8007AFCC(a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B1A6C);

void func_800B1BF0(s32 a0) {
    s32 s1;
    s32 s0;
    s32 buf[4];
    s1 = a0;
    func_8007767C((u8 *)s1, buf);
    buf[0] += func_8007A084(s1) * 640;
    buf[1] -= 0xF0;
    s0 = func_8002BE14(0x1F4);
    if (s0 != 0) {
        func_800B3C48((s32)(u32)func_8002BD80(0x1F4, (void *)(u32)s0), s1, (s32)buf);
    }
    func_8007AFCC(s1, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B1C84);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B1D78);

void func_800B1F3C(s32 a0, s32 a1) {
    s32 s1;
    s32 s0;
    s32 p;
    s32 a2;
    s32 a0v;
    s1 = a0;
    s0 = a1;
    p = s1 + 0x38;
    a2 = *(s32 *)(s1 + 0x38);
    a0v = *(s32 *)(s1 + 0x3C);
    *(s32 *)(s1 + 0x18) = (s32)&D_8006BC24;
    *(s32 *)(s1 + 0x14) = (s32)&D_8006BC44;
    *(s32 *)(s1 + 0x68) = (s32)&D_80065174;
    *(s32 *)(a2 + 4) = a0v;
    a2 = *(s32 *)(p + 4);
    *(s32 *)(a2 + 0) = *(s32 *)(s1 + 0x38);
    *(s32 *)(s1 + 0x38) = p;
    *(s32 *)(s1 + 0x3C) = p;
    *(s32 *)(s1 + 0x18) = (s32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B1FDC);

void func_800B228C(s32 a0, s32 a1) {
    func_8007C0C8((u8 *)(u32)a0 + 0x18, (u8 *)(u32)a1);
    if (func_80078AD8(a1)) {
        *(u32 *)(a0 + 0x44) |= 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B22E0);

s32 func_800B24F8(s32 a0, s32 a1, s32 a2, s32 a3) {
    register s32 s0 asm("$16"); /* PIN $s0: preserve the object pointer across calls */
    register s32 s1 asm("$17"); /* PIN $s1: preserve the first callback argument */
    register s32 s2 asm("$18"); /* PIN $s2: preserve the source data pointer */
    register s32 s3 asm("$19"); /* PIN $s3: preserve the final halfword argument */
    register s32 sym asm("$2"); /* PIN $v0: match the vtable address register */
    register s32 callback asm("$4"); /* PIN $a0: match callback argument setup */
    s32 word0;
    s32 word1;
    s32 word2;
    s0 = a0;
    s1 = a1;
    s2 = a2;
    s3 = a3;
    __asm__ volatile ("" : "+r"(s0), "+r"(s1), "+r"(s2), "+r"(s3));
    func_8002BC9C(a0, 0);
    callback = s1;
    __asm__ volatile ("" : "+r"(callback));
    sym = (s32)&D_8006BBFC;
    *(s32 *)(s0 + 0x14) = sym;
    *(s16 *)(s0 + 0x26) = func_80077730(callback);
    *(s16 *)(s0 + 0x20) = func_8007A084(s1);
    __asm__ volatile ("addiu %0, $zero, 0x80" : "=r"(sym));
    *(u8 *)(s0 + 0x22) = sym;
    __asm__ volatile ("addiu %0, $zero, 0x1000" : "=r"(sym));
    *(s32 *)(s0 + 0x18) = s1;
    *(s16 *)(s0 + 0x24) = 0;
    *(s16 *)(s0 + 0x1E) = 0;
    *(s32 *)(s0 + 0x28) = sym;
    *(s16 *)(s0 + 0x1C) = s3;
    word0 = *(s32 *)(s2 + 0);
    word1 = *(s32 *)(s2 + 4);
    word2 = *(s32 *)(s2 + 8);
    *(s32 *)(s0 + 0x2C) = word0;
    *(s32 *)(s0 + 0x30) = word1;
    *(s32 *)(s0 + 0x34) = word2;
    return s0;
}

void func_800B25A4(s32 a0, s32 a1) {
    *(s32 *)(a0 + 0x14) = (s32)&D_8006BBFC;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

typedef struct B25F8State B25F8State;
typedef struct B25F8VTable {
    u8 prefix[0x18];
    s16 this_delta;
    s16 reserved;
    void (*complete)(B25F8State *, s32);
} B25F8VTable;
struct B25F8State {
    u8 prefix[0x14];
    B25F8VTable *vtable;
    u8 reserved_18[6];
    u16 counter;
    u8 reserved_20[2];
    u8 intensity;
    u8 reserved_23;
    u16 phase;
    u8 reserved_26[2];
    u32 progress;
};

void func_800B25F8(B25F8State *state) {
    u32 progress;
    s32 intensity;
    B25F8VTable *table;
    switch (state->phase) {
    case 0:
        progress = state->progress + ((u32)state->counter << 7);
        state->progress = progress;
        if ((s32)progress > 0x2000) {
            state->progress = 0x2000;
        }
        intensity = state->intensity;
        intensity += (-intensity) >> 3;
        state->intensity = (u8)intensity;
        if (state->intensity >= 9) {
            break;
        }
        state->phase++;
    case 1:
        if (state != 0) {
            table = state->vtable;
            table->complete((B25F8State *)((u32)state + (u32)(s32)table->this_delta), 3);
        }
        return;
    default:
        break;
    }
    state->counter++;
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B26CC);

s32 func_800B2884(s32 a0, s32 a1, s32 a2) {
    register s32 sym asm("$2"); /* PIN $v0: match the vtable address register */
    register s32 callback_arg asm("$4"); /* PIN $a0: stage the callback argument */
    s32 word0;
    s32 word1;
    s32 word2;
    func_8002BC9C(a0, 0);
    callback_arg = a1;
    __asm__ volatile ("" : "+r"(callback_arg));
    sym = (s32)&D_8006BBD4;
    *(s32 *)(a0 + 0x14) = sym;
    *(s16 *)(a0 + 0x24) = func_80077730(callback_arg);
    *(s16 *)(a0 + 0x1E) = func_8007A084(a1);
    *(s32 *)(a0 + 0x18) = a1;
    *(s16 *)(a0 + 0x22) = 0;
    *(u8 *)(a0 + 0x20) = 0x80;
    *(s16 *)(a0 + 0x1C) = 0;
    *(s32 *)(a0 + 0x28) = 0;
    word0 = *(s32 *)(a2 + 0);
    word1 = *(s32 *)(a2 + 4);
    word2 = *(s32 *)(a2 + 8);
    *(s32 *)(a0 + 0x2C) = word0;
    *(s32 *)(a0 + 0x30) = word1;
    *(s32 *)(a0 + 0x34) = word2;
    return a0;
}

void func_800B291C(s32 a0, s32 a1) {
    *(s32 *)(a0 + 0x14) = (s32)&D_8006BBD4;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800B2970(s32 a0) {
    s32 a1;
    a1 = a0;
    *(s32 *)(a1 + 0x28) += (0x1020 - *(s32 *)(a1 + 0x28)) >> 1;
    if (*(s32 *)(a1 + 0x28) >= 0x1001) {
        *(s32 *)(a1 + 0x28) = 0x1000;
    }
    if (*(u8 *)(a1 + 0x20) < 9) {
        if (a1 != 0) {
            u8 *v0 = *(u8 **)(a1 + 0x14);
            s16 off = *(s16 *)(v0 + 0x18);
            void (*fn)(s32, s32) = *(void (**)(s32, s32))(v0 + 0x1C);
            fn(a1 + off, 3);
        }
    } else {
        s32 v0 = *(u8 *)(a1 + 0x20);
        *(u8 *)(a1 + 0x20) = v0 + ((-v0) >> 3);
        *(u16 *)(a1 + 0x1C) += 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B2A14);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B2C7C);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B2D34);

void func_800B2DF8(s32 a0, s32 a1) {
    s32 s0;
    s32 s1;
    s32 c;
    s0 = a0;
    s1 = a1;
    c = 0;
    if (*(s32 *)(s0 + 0x38) == s0 + 0x38) {
        c = (*(s32 *)(s0 + 0x38) == *(s32 *)(s0 + 0x3C));
    }
    if (c == 0) {
        func_800B2E60(s0, s1);
    }
    func_800B2FC8(s0, s1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B2E60);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B2FC8);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B3120);

void func_800B3304(s32 a0, s32 a1) {
    register s32 flag asm("$2");
    *(s32 *)(a0 + 0x18) = (s32)&D_8006BB44;
    *(s32 *)(a0 + 0x14) = (s32)&D_8006BB64;
    if (*(u16 *)(a0 + 0x8A) != 0) {
        func_800794D4((s32)func_8007B16C(*(u8 **)(a0 + 0x80)), 0);
    }
    *(s32 *)(a0 + 0x68) = (s32)&D_80065174;
    {
        s32 p = a0 + 0x38;
        s32 tail = *(s32 *)(a0 + 0x38);
        s32 head = *(s32 *)(a0 + 0x3C);
        *(s32 *)(tail + 4) = head;
        tail = *(s32 *)(p + 4);
        *(s32 *)(tail + 0) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0x38) = p;
        *(s32 *)(a0 + 0x3C) = p;
    }
    *(s32 *)(a0 + 0x18) = (s32)&D_80065154;
    func_8002BCEC(a0, 0);
    flag = a1 & 1;
    if (flag != 0) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B33C4);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B3694);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B3788);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B396C);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B39B0);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B3C48);

void func_800B3D78(s32 a0, s32 a1) {
    *(s32 *)(a0 + 0x14) = (s32)&D_8006BB1C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B3DCC);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B3F84);

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B41F0);

void func_800B4344(s32 a0, s32 a1) {
    s32 s1;
    s32 s0;
    s32 p;
    s32 a2;
    s32 a0v;
    s1 = a0;
    s0 = a1;
    p = s1 + 0x38;
    a2 = *(s32 *)(s1 + 0x38);
    a0v = *(s32 *)(s1 + 0x3C);
    *(s32 *)(s1 + 0x18) = (s32)&D_8006BAD4;
    *(s32 *)(s1 + 0x14) = (s32)&D_8006BAF4;
    *(s32 *)(s1 + 0x68) = (s32)&D_80065174;
    *(s32 *)(a2 + 4) = a0v;
    a2 = *(s32 *)(p + 4);
    *(s32 *)(a2 + 0) = *(s32 *)(s1 + 0x38);
    *(s32 *)(s1 + 0x38) = p;
    *(s32 *)(s1 + 0x3C) = p;
    *(s32 *)(s1 + 0x18) = (s32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B43E4);

void func_800B4534(s32 a0, s32 a1) {
    func_8007C0C8((u8 *)(u32)a0 + 0x18, (u8 *)(u32)a1);
    if (func_80078AD8(a1)) {
        *(u32 *)(a0 + 0x44) |= 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B4588);

void func_800B4790(s32 a0, s32 a1) {
    s32 s1;
    s32 s0;
    s1 = a0;
    s0 = a1;
    func_8002BCEC(a0, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800B47D8(s32 a0, s32 a1) {
    s32 s1;
    s32 s0;
    s32 p;
    s32 a2;
    s32 a0v;
    s1 = a0;
    s0 = a1;
    p = s1 + 0x38;
    a2 = *(s32 *)(s1 + 0x38);
    a0v = *(s32 *)(s1 + 0x3C);
    *(s32 *)(s1 + 0x18) = (s32)&D_8006D730;
    *(s32 *)(s1 + 0x14) = (s32)&D_8006D750;
    *(s32 *)(s1 + 0x68) = (s32)&D_80065174;
    *(s32 *)(a2 + 4) = a0v;
    a2 = *(s32 *)(p + 4);
    *(s32 *)(a2 + 0) = *(s32 *)(s1 + 0x38);
    *(s32 *)(s1 + 0x38) = p;
    *(s32 *)(s1 + 0x3C) = p;
    *(s32 *)(s1 + 0x18) = (s32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

s32 func_800B4878(s32 a0) {
    func_80076FD8(a0);
    *(s32 *)(a0 + 0x14) = (s32)&D_8006BED4;
    func_80079D98(a0, (s32)&D_8006BE0C);
    *(u16 *)(a0 + 0x4A4) = 0;
    return a0;
}

void func_800B48C0(s32 a0, s32 a1) {
    *(s32 *)(a0 + 0x14) = (s32)&D_8006BED4;
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800B4914(s32 a0) {
    *(u16 *)(a0 + 0x4A4) = 0;
}

void func_800B491C(s32 a0, s32 a1) {
    s32 s1;
    s32 s0;
    s1 = a0;
    s0 = a1;
    func_8007BB5C(a0);
    if (s0 == 0) {
        func_8007A97C(s1, 1, 0x50, 8);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B4964);

void func_800B4B50(s32 a0, s32 a1) {
    switch (a1) {
    case 0:
        func_80079AA4(a0, 0x16, 0, 0, -1);
        func_800B5318(a0);
        func_80078754((u8 *)(u32)a0, 0xF5);
        break;
    case 5:
        func_800B525C(a0);
        func_80079D80(a0, 0x19);
        break;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/4CF7C", func_800B4BD4);

void func_800B50E0(s32 a0, s32 a1) {
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");
    switch (a1) {
    case 0:
        func_80079AA4(a0, 0x17, 2, 0, -1);
        func_800B5318(a0);
        func_80078754((u8 *)(u32)a0, 0xF5);
        break;
    case 5:
        v0 = func_8007A084(a0);
        v1 = (v0 * 3) << 12;
        v0 = *(s32 *)(a0 + 0x3B4);
        v0 -= v1;
        *(s32 *)(a0 + 0x3B4) = v0;
        func_800B525C(a0);
        func_80079D80(a0, 0x19);
        break;
    }
    if (a1 < 0xE) {
        *(s32 *)(a0 + 0x3B4) -= *(s32 *)(a0 + 0x3A4) >> 4;
        if (*(s32 *)(a0 + 0x3A8) > 0) {
            *(s32 *)(a0 + 0x3B8) -= *(s32 *)(a0 + 0x3A8);
        }
    }
}

void func_800B51C8(s32 a0) {
    s32 buf[4];
    s32 s0;
    func_8007767C((u8 *)a0, buf);
    if (func_8007A084(a0) > 0) {
        buf[0] -= 0xF5;
    } else {
        buf[0] += 0xF5;
    }
    s0 = func_8002BE14(0x34);
    if (s0 != 0) {
        func_800B61CC((u8 *)func_8002BD80(0x34, (void *)(u32)s0), (u8 *)(u32)a0, buf);
    }
    func_8007AFCC(a0, s0);
}

void func_800B525C(s32 a0) {
    s32 s0;
    s32 s2 = (s32)(u32)func_80077624((u8 *)(u32)a0);
    s32 buf[8];
    func_8007767C((u8 *)a0, buf);
    buf[1] -= 0xB0;
    buf[4] = func_8007A084(a0) * 48;
    buf[5] = 0;
    buf[6] = 0;
    s0 = func_8002BE14(0x160);
    if (s0 != 0) {
        func_800B53A4((s32)(u32)func_8002BD80(0x160, (void *)(u32)s0), a0, (s32)buf, (s32)&buf[4], s2);
    }
    func_8007AFCC(a0, s0);
    func_80079D80(a0, 0x28);
}

void func_800B5318(s32 a0) {
    s32 s1;
    s32 s2;
    s32 s0;
    s32 buf[4];
    s1 = a0;
    s2 = (s32)(u32)func_80077624((u8 *)(u32)s1);
    func_8007A724((u8 *)s1, buf, 9, (u8 *)&D_800D373C);
    s0 = func_8002BE14(0x74);
    if (s0 != 0) {
        func_800B5BD8((u8 *)func_8002BD80(0x74, (void *)(u32)s0), (u8 *)(u32)s1, (u8 *)(u32)s2, buf);
    }
    func_8007AFCC(s1, s0);
}
