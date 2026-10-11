#include "game_renew_handle_api.h"
#include "character_getters.h"
#include "game_action_api.h"
#include "game_velocity_api.h"
#include "game_audio_api.h"
#include "common.h"
#include "game_actor_queries.h"
#include "game_positions.h"
#include "game_handles.h"
#include "game_deferred.h"
#include "task_manager.h"

extern void func_8001FD10(s32, s32);
extern void func_8007F3CC(s32);
extern void func_8007F4D4(s32, s32);
extern void func_8007FE74(s32);
extern void func_80080ACC(s32);
extern s32 func_80079500(u8 *arg0);
extern s32 func_8007A2B8(u8 *);
extern s32 func_800769C0(u8 *, s32, s32);
extern void func_800750C4(s32, s32);
extern void func_800C9A4C(u8 *);
extern void func_800C9C6C(u8 *);

extern void func_800795B0(u8 *);
extern s32 func_8002BD68(u8 *);
extern void func_80079AA4(u8 *, s32, s32, s32, s32);
extern void func_80079E90(s32 *, u8 *, u8 *, s32);
extern s32 func_8007F880(s32);
extern s32 func_80078FC4(u8 *);
extern s32 func_8006EF78(s32, s32, s32);
extern s32 func_80020780(s32);
extern u8 D_80064358[];
extern u8 D_80067AC4[];
extern s32 D_800D3A70;
extern s32 *func_80078678(u8 *, s32 *);
extern u32 D_800D3A60[];
extern u8 D_800108B4[];
extern u8 D_800651FC[];
extern s32 func_8007B150(u8 *);
extern void func_80079DA0(u8 *, s32);
extern void func_80080BC4(s32, s32);
extern void func_80081CB8(s32);
extern u8 D_8005F824[];
extern s32 func_8007663C(u8 *);
extern void func_8007C25C(u8 *, s32, s32);

extern s32 func_80073010(u8 *, u8 *);

extern void func_80079680(u8 *);
extern s32 func_8002BDC8(s32);
extern s32 func_800207C0(s32, s32, s32, s32, s32);
extern s32 func_800207A0(s32);
extern s32 func_80076518(u8 *, s32 *, s32 *);
extern u8 D_8005F8B8[];
extern s32 D_80114210;
extern void func_80026F0C(s32, s32, s32, s32, s32, s32, s32);
extern void func_800764E8(u8 *);
extern s32 func_8007A008(u8 *);
extern s32 func_8007A04C(u8 *);
extern s32 func_8007A0C4(u8 *, u8 *, s32, s32);
extern s16 D_80065260[];
extern u8 D_80010884[];
extern s32 func_80079C80(u8 *);

extern s32 func_800207E8(s32, s32);
extern u8 *func_8002BD88(s32);
extern u8 *func_800C44A0(u8 *, s32);
extern s32 func_8002BD74(u8 *);
extern s32 func_8001D97C(u8 *, s32);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80076758);

s32 func_8007692C(u8 *arg0, s32 *arg1) {
    s32 a = *(s16 *)(arg0 + 8);
    s32 b = *(s16 *)(arg0 + 0xA);
    a *= arg1[0];
    b *= arg1[1];
    return a + b;
}

s32 func_8007695C(u8 *arg0, s32 *arg1) {
    return *(s16 *)(arg0 + 8) * arg1[0] + *(s16 *)(arg0 + 0xA) * arg1[1] + *(s32 *)(arg0 + 0xC);
}

void func_80076994(u8 *arg0, s32 *arg1) {
    s32 *p = arg1;
    func_800769C0(arg0, p[0], p[1]);
}

s32 func_800769C0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 x = arg1 - *(s16 *)(arg0 + 0);
    s32 y = arg1 - *(s16 *)(arg0 + 4);
    s32 z = arg2 - *(s16 *)(arg0 + 2);
    s32 w = arg2 - *(s16 *)(arg0 + 6);
    return (x * y + z * w) < 1;
}

u32 *func_800769FC(u32 *arg0, u32 *arg1) {
    register u32 *right asm("$5"); /* PIN $a1: keep the right record in its input register. */
    register u32 left0 asm("$7"); /* PIN $a3: first value from the left record. */
    register u32 right0 asm("$3"); /* PIN $v1: first value from the right record. */
    register u32 left1 asm("$8"); /* PIN $t0: second value from the left record. */
    register u32 right1 asm("$6"); /* PIN $a2: second value from the right record. */
    right = arg1;
    __asm__ volatile ("" : "+r"(right));
    if (right == arg0) {
        return right;
    }
    left0 = arg0[0];
    right0 = right[0];
    left1 = arg0[1];
    right1 = right[1];
    right0 ^= left0;
    right1 ^= left1;
    left0 ^= right0;
    left1 ^= right1;
    right0 ^= left0;
    right1 ^= left1;
    arg0[0] = left0;
    right[0] = right0;
    arg0[1] = left1;
    right[1] = right1;
    left0 = arg0[2];
    right0 = right[2];
    left1 = arg0[3];
    right1 = right[3];
    right0 ^= left0;
    right1 ^= left1;
    left0 ^= right0;
    left1 ^= right1;
    right0 ^= left0;
    right1 ^= left1;
    arg0[2] = left0;
    right[2] = right0;
    arg0[3] = left1;
    right[3] = right1;
    return right;
}

s32 *func_80076A80(s32 *arg0) {
    s32 a = arg0[0];
    s32 b = arg0[1];
    s32 c = arg0[2];
    D_800D3A60[0] = a;
    D_800D3A60[1] = b;
    D_800D3A60[2] = c;
    return (s32 *)D_800D3A60;
}

u8 *func_80076AA4(void) {
    return D_80064358;
}

void func_80076AB0(u8 *arg0) {
    u32 *head = (u32 *)D_80064358;
    *(u32 *)(*(u32 *)arg0 + 4) = *(u32 *)(arg0 + 4);
    *(u32 *)(*(u32 *)(arg0 + 4)) = *(u32 *)arg0;
    *(u32 *)arg0 = (u32)arg0;
    *(u32 *)(arg0 + 4) = (u32)head;
    *(u32 *)arg0 = head[0];
    *(u32 *)(head[0] + 4) = (u32)arg0;
    head[0] = (u32)arg0;
}

void func_80076B00(u8 *arg0) {
    u32 *head = (u32 *)D_80064358;
    *(u32 *)(*(u32 *)arg0 + 4) = *(u32 *)(arg0 + 4);
    *(u32 *)(*(u32 *)(arg0 + 4)) = *(u32 *)arg0;
    *(u32 *)(arg0 + 4) = (u32)arg0;
    *(u32 *)arg0 = (u32)head;
    *(u32 *)(arg0 + 4) = head[1];
    *(u32 *)head[1] = (u32)arg0;
    head[1] = (u32)arg0;
}

void func_80076B50(u8 *arg0, s32 arg1, s32 arg2) {
    u32 *head = (u32 *)D_80064358;
    *(u32 *)(arg0 + 4) = (u32)head;
    *(u32 *)(arg0 + 0) = head[0];
    *(u32 *)(head[0] + 4) = (u32)arg0;
    head[0] = (u32)arg0;
    *(u32 *)(arg0 + 0xC) = (u32)D_800108B4;
    *(u32 *)(arg0 + 8) = arg1;
    *(u32 *)(arg0 + 0x10) = arg2;
    *(u32 *)(arg0 + 0x14) = 1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80076B98);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80076C58);

s32 func_80076D18(s32 arg0, s32 arg1, s32 arg2) {
    s16 d = ((arg0 - arg1 - 0x800) & 0xFFF) - 0x800;
    if (d < -arg2) {
        d = -arg2;
    } else if (arg2 < d) {
        d = arg2;
    }
    return arg1 + d;
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80076D58);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80076FD8);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80077150);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_800772B0);

void func_80077498(u8 *arg0, s32 arg1) {
    func_8006EF78(*(s32 *)(arg0 + 0x228), *(s32 *)(arg0 + 0x21C), arg1);
}

void func_800774C8(u8 *arg0) {
    func_8007F3CC(*(s32 *)(arg0 + 0x238));
}

void func_800774EC(u8 *arg0, s32 delta) {
    func_8007F4D4(*(s32 *)(arg0 + 0x238), delta);
}

void func_80077510(u8 *arg0) {
    if (func_8007F880(*(s32 *)(arg0 + 0x238)) != 0) {
        func_800795B0(arg0);
    }
}

void func_8007754C(u8 *arg0) {
    *(s32 *)(arg0 + 0x464) = 0;
    *(s32 *)(arg0 + 0x468) = 0;
    *(s32 *)(arg0 + 0x46C) = 0;
    *(s32 *)(arg0 + 0x470) = 0;
    *(s32 *)(arg0 + 0x474) = 0;
}

void func_80077564(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    *(s32 *)(arg0 + 0x464) = arg1;
    *(s32 *)(arg0 + 0x468) = arg2;
    *(s32 *)(arg0 + 0x46C) = arg3;
    *(s32 *)(arg0 + 0x470) = 0;
    *(s32 *)(arg0 + 0x474) = 0;
}

void func_8007757C(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x464) != 0) {
        func_800C9A4C(arg0);
    }
}

void func_800775AC(u8 *arg0) {
    *(s32 *)(arg0 + 0x478) = 0;
    *(s32 *)(arg0 + 0x47C) = 0;
    *(s32 *)(arg0 + 0x480) = 0;
    *(s32 *)(arg0 + 0x484) = 0;
    *(s32 *)(arg0 + 0x488) = 0;
}

void func_800775C4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    *(s32 *)(arg0 + 0x478) = arg1;
    *(s32 *)(arg0 + 0x47C) = arg2;
    *(s32 *)(arg0 + 0x480) = arg3;
    *(s32 *)(arg0 + 0x484) = 0;
    *(s32 *)(arg0 + 0x488) = 0;
}

void func_800775DC(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x478) != 0) {
        func_800C9C6C(arg0);
    }
}

s32 func_8007760C(u8 *arg0) {
    return *(s32 *)(arg0 + 0x218);
}

s32 func_80077618(u8 *arg0) {
    return *(s32 *)(arg0 + 0x21C);
}

u8 *func_80077624(u8 *arg0) {
    return *(u8 **)(arg0 + 0x228);
}

u8 *func_80077630(u8 *arg0) {
    return *(u8 **)(arg0 + 0x238);
}

s32 func_8007763C(u8 *arg0) {
    return *(s32 *)(arg0 + 0x37C) & 1;
}

s32 func_80077648(u8 *arg0) {
    return *(s32 *)(arg0 + 0x3FC);
}

void func_80077654(u8 *arg0, s32 *arg1) {
    s32 a = (s32)((u32)arg1[0] << 8);
    s32 b = (s32)((u32)arg1[1] << 8);
    s32 c = (s32)((u32)arg1[2] << 8);
    *(s32 *)(arg0 + 0x384) = a;
    *(s32 *)(arg0 + 0x388) = b;
    *(s32 *)(arg0 + 0x38C) = c;
}

s32 *func_8007767C(u8 *arg0, s32 *arg1) {
    arg1[0] = *(s32 *)(arg0 + 0x384) >> 8;
    arg1[1] = *(s32 *)(arg0 + 0x388) >> 8;
    arg1[2] = *(s32 *)(arg0 + 0x38C) >> 8;
    return arg1;
}

s32 *func_800776B0(u8 *arg0, s32 *arg1) {
    arg1[0] = *(s32 *)(arg0 + 0x394) >> 8;
    arg1[1] = *(s32 *)(arg0 + 0x398) >> 8;
    arg1[2] = *(s32 *)(arg0 + 0x39C) >> 8;
    return arg1;
}

s32 *func_800776E4(u8 *arg0, s32 *arg1) {
    arg1[0] = (*(s32 *)(arg0 + 0x384) + *(s32 *)(arg0 + 0x3A4)) >> 8;
    arg1[1] = (*(s32 *)(arg0 + 0x388) + *(s32 *)(arg0 + 0x3A8)) >> 8;
    arg1[2] = (*(s32 *)(arg0 + 0x38C) + *(s32 *)(arg0 + 0x3AC)) >> 8;
    return arg1;
}

s32 func_80077730(u8 *arg0) {
    return *(s32 *)(arg0 + 0x440);
}

s32 func_8007773C(u8 *arg0) {
    return *(s32 *)(arg0 + 0x220);
}

u8 *func_80077748(u8 *arg0) {
    u8 *b = D_80067AC4;
    return b + *(s32 *)(arg0 + 0x218) * 10;
}

s32 func_80077768(u8 *arg0) {
    return *(s32 *)(arg0 + 0x234);
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80077774);

s32 func_80077838(u8 *arg0) {
    u8 *p = (u8 *)func_8007773C(arg0);
    return (*(u16 *)p ^ 1) & 1;
}

s32 func_80077860(u8 *arg0) {
    return (*(u32 *)(arg0 + 0x37C) >> 1) & 1;
}

void func_80077874(u8 *arg0, s32 arg1) {
    s32 v = *(s32 *)(arg0 + 0x3FC);
    func_8001FD10(arg1, v);
}

void func_8007789C(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x3FC);
    *(u8 **)(*(s32 *)p + 4) = *(u8 **)(p + 4);
    *(u8 **)(*(s32 *)(p + 4)) = *(s32 *)p;
    *(u8 **)p = p;
    *(u8 **)(p + 4) = p;
}

s32 func_800778D0(u8 *arg0) {
    u32 v = *(u32 *)(arg0 + 0x37C);
    u32 r = v >> 7;
    v &= ~0x80;
    *(u32 *)(arg0 + 0x37C) = v;
    return r & 1;
}

s32 func_800778EC(u8 *arg0) {
    s32 first[4];
    s32 second[4];
    u8 work[0x80];
    if (((*(u32 *)(arg0 + 0x37C) >> 3) & 1) == 0) {
        return 0;
    }
    func_8007767C(arg0, first);
    first[1] = (s32)((u32)first[1] + 0x26U);
    func_8007767C(arg0, second);
    second[1] = (s32)((u32)second[1] + 0x1E26U);
    func_800764E8(work);
    return func_80076518(work, first, second);
}

s32 func_80077978(u8 *arg0) {
    return (*(u32 *)(arg0 + 0x37C) >> 2) & 1;
}

s32 func_8007798C(u8 *arg0, s32 arg1) {
    s32 bit = 1 << arg1;
    if (*(s32 *)(arg0 + 0x380) & bit) {
        return 0;
    }
    *(s32 *)(arg0 + 0x380) |= bit;
    return 1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_800779B8);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80077BDC);

void func_80077D44(u8 *arg0) {
    if (func_8007B150(arg0) != 0) {
        u32 value = *(u32 *)func_80079500(arg0);
        func_80079DA0(arg0, value - 0xB < 4 || value == 0x10);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80077DA8);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80077F00);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80078090);

s32 func_800783AC(u8 *arg0, s32 arg1) {
    if (func_80077978(arg0) == 0) {
        return 0;
    }
    return arg1 == func_8007663C(arg0 + 0x260);
}

s32 func_800783FC(u8 *arg0) {
    u8 *new_var;
    s32 first[4];
    s32 second[4];
    new_var = arg0 + 0x260;
    func_8007767C(arg0, first);
    func_8007767C(arg0, second);
    first[1] -= 0x80;
    second[1] += 8;
    if (func_80076518(new_var, first, second) != 0) {
        /* Preserve the retail compiler's branch/return scheduling. */
        do { return 1; } while (0);
    }
    func_800776B0(arg0, first);
    first[1] -= 0x40;
    func_8007767C(arg0, second);
    return func_80076518(arg0 + (0x260 ^ 0), first, second) != 0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_800784B4);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_800785BC);

s32 *func_80078678(u8 *arg0, s32 *arg1) {
    s32 first = (s32)(0u - *(u32 *)(arg0 + 0x3A4));
    s32 second = *(s32 *)(arg0 + 0x3C4);
    s32 intermediate = (s32)(((s64)first * second) >> 16);

    arg1[1] = 0;
    arg1[2] = 0;
    arg1[0] = (s32)(((s64)intermediate * D_800D3A70) >> 16);
    return arg1;
}

s32 func_800786D8(u8 *arg0, s32 arg1) {
    s32 buf[8];
    s32 delta;
    func_8007767C(arg0, buf);
    delta = arg1 * func_8007A084(arg0);
    buf[6] = buf[2];
    buf[5] = buf[1] - 0x4C;
    buf[1] += 0x100;
    buf[0] += delta;
    buf[4] = buf[0];
    func_80073010((u8 *)buf, (u8 *)&buf[4]);
}

s32 func_80078754(u8 *arg0, s32 arg1) {
    char index = (*(u8 *)(arg0 + 0x21C) << 7) + *(u8 *)(arg0 + 0x218) + 0x40;
    s32 result = func_8001BE78((s32)(u32)D_8005F824, arg1, index & 0xFF);
    *(s32 *)(arg0 + 0x25C) = result;
    return result;
}

s32 func_800787A0(u8 *arg0, s32 arg1) {
    s32 index = *(u8 *)(arg0 + 0x218) + (*(u8 *)(arg0 + 0x21C) << 7);
    return func_8001BE78((s32)(u32)D_8005F824, arg1, index & 0xFF);
}

static __inline__ void approach_angle(u32 *current, s32 difference) {
    u32 value = *current;
    u32 result;
    if ((u32)(difference + 3) >= 7U) {
        result = value + (u32)(difference / 4);
    } else {
        result = value + (u32)difference;
    }
    *current = result;
}

void func_800787D8(u8 *self) {
    s32 dx = (s32)((*(u32 *)(self + 0x3E8) - *(u32 *)(self + 0x3D8) - 0x800U) & 0xFFFU) - 0x800;
    s32 dy = (s32)((*(u32 *)(self + 0x3EC) - *(u32 *)(self + 0x3DC) - 0x800U) & 0xFFFU) - 0x800;
    s32 dz = (s32)((*(u32 *)(self + 0x3F0) - *(u32 *)(self + 0x3E0) - 0x800U) & 0xFFFU) - 0x800;
    approach_angle((u32 *)(self + 0x3D8), dx);
    approach_angle((u32 *)(self + 0x3DC), dy);
    approach_angle((u32 *)(self + 0x3E0), dz);
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_800788C0);

void func_80078A64(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x3EC) = -0x401;
    if (arg1 != 0) {
        *(s32 *)(arg0 + 0x3DC) = -0x401;
    }
}

void func_80078A7C(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x3EC) = 0x401;
    if (arg1 != 0) {
        *(s32 *)(arg0 + 0x3DC) = 0x401;
    }
}

void func_80078A94(u8 *arg0) {
    *(s32 *)(arg0 + 0x3EC) = 0x800;
}

void func_80078AA0(u8 *arg0) {
    *(s32 *)(arg0 + 0x3EC) = 0;
}

void func_80078AA8(u8 *arg0, s32 arg1) {
    func_800750C4(arg1, (*(s32 *)(arg0 + 0x3EC) ^ -0x401) == 0);
}

u8 *func_80078AD8(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x14);
    if (func_8002BD68(p) != 0x10000) {
        return 0;
    }
    return p;
}

void func_80078B14(u8 *arg0, s32 arg1, s32 arg2) {
    register u16 *data asm("$2"); /* pin $v0: retain the helper's returned base */
    data = (u16 *)func_8007773C(arg0);
    data += arg1;
    func_8007C25C(arg0 + 0x348 + arg1 * 4, arg2 & 0xFFFF, *(u16 *)((u8 *)data + 0x1C));
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80078B70);

void func_80078E88(u8 *arg0, s32 arg1) {
    register u8 *obj asm("$6"); /* pin $a2: callback receiver remains live for both field loads */
    *(s32 *)(arg0 + 0x234) = arg1;
    obj = *(u8 **)(arg0 + 0x14);
    ((void (*)(u8 *))*(u32 *)(obj + 0x34))(arg0 + *(s16 *)(obj + 0x30));
}

void func_80078EBC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 new_var;
    s32 new_var2;
    register u8 *obj asm("$9"); /* PIN $t1: retain the object base. */
    register s32 low2 asm("$8"); /* PIN $t0: retain the low byte of arg2. */
    register s32 low3 asm("$7"); /* PIN $a3: retain the low byte of arg3. */
    register s32 callArg asm("$6"); /* PIN $a2: preserve arg1 for the helper call. */
    register u8 *base asm("$2"); /* PIN $v0: hold the global base and loaded pointer. */
    register s32 global asm("$4"); /* PIN $a0: retain the global helper argument. */
    register s32 stack4 asm("$2"); /* PIN $v0: retain arg4 for the helper call. */
    register s32 stack5 asm("$3"); /* PIN $v1: retain arg5 for the helper call. */

    obj = arg0;
    new_var = arg2 & 0xFF;
    __asm__ volatile ("" : "+r"(obj));
    low2 = new_var;
    __asm__ volatile ("" : "+r"(low2));
    low3 = arg3 & 0xFF;
    new_var2 = (*(u32 *)(obj + 0x37C) & 1) != 0;
    if (new_var2) {
        return;
    }
    base = D_8005F8B8;
    __asm__ volatile ("" : "+r"(base));
    if (*(s32 *)(base + 0x2B4) != 0) {
        return;
    }
    __asm__ volatile ("" : : : "memory");
    base = (u8 *)(*((volatile s32 *)(base + 0x64)));
    if (base == 0) {
        return;
    }
    global = D_80114210;
    __asm__ volatile ("" : "+r"(global));
    stack4 = arg4;
    stack5 = arg5;
    __asm__ volatile ("" : "+r"(stack4), "+r"(stack5));
    callArg = arg1;
    __asm__ volatile ("" : "+r"(callArg));
    func_80026F0C(global, *(s32 *)(obj + 0x21C), callArg, low2, low3, stack4, stack5);
}

s32 *func_80078F40(u8 *self, s32 *out) {
    s32 scale = *(s32 *)(self + 0x3C4);
    out[0] = (s32)(((s64)*(s32 *)(self + 0x3A4) * scale) >> 16);
    out[1] = (s32)(((s64)*(s32 *)(self + 0x3A8) * scale) >> 16);
    out[2] = (s32)(((s64)*(s32 *)(self + 0x3AC) * scale) >> 16);
    return out;
}

s32 func_80078FC4(u8 *arg0) {
    u32 state = *(u32 *)func_80079500(arg0);
    u32 mode = *(u32 *)func_8007950C(arg0);
    register s32 result asm("$5"); /* PIN $a1: retail holds the zero/one result here. */
    result = 0;
    if (state == 0xF) {
        goto active;
    }
    if (state == 0xD) {
        goto active;
    }
    if (state == 0xE) {
        goto active;
    }
    if (mode == 0x18) {
        goto active;
    }
    if (*(s32 *)(arg0 + 0x498) <= 0) {
        goto done;
    }
active:
    result = 1;
done:
    return result;
}

s32 func_80079040(u8 *arg0) {
    u8 *p = (u8 *)func_80079500(arg0);
    return (*(u32 *)p - 9) < 2;
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80079068);

u32 func_800790CC(u8 *arg0, u32 arg1) {
    if ((u32)(*(s32 *)(arg0 + 0x464) - 1) < 2U) {
        s32 temp_a0 = (s32)(arg1 & 0x3FFFF);

        temp_a0 = (temp_a0 * *(s32 *)(arg0 + 0x46C)) >> 8;
        arg1 = temp_a0 | (arg1 & 0xFFFC0000);
    }
    return arg1;
}

s32 func_80079110(s32 arg0, s32 arg1, s32 arg2) {
    register u8 *table asm("$3"); /* PIN $v1: keep the symbol base in retail's register. */
    s32 value;
    table = D_800651FC;
    __asm__ volatile ("" : "+r"(table));
    arg1 += arg0 * 4;
    arg1 += (s32)table;
    value = *(s8 *)(u8 *)arg1;
    return arg2 * (value + 0x64) / 100;
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80079158);

void func_800794BC(u8 *arg0) {
    *(s32 *)(arg0 + 0x258) = 0x12;
}

void func_800794C8(u8 *arg0) {
    *(s32 *)(arg0 + 0x258) = 0x11;
}

void func_800794D4(u8 *arg0) {
    func_80080ACC(*(s32 *)(arg0 + 0x22C));
}

void func_800794F8(void) {
}

s32 func_80079500(u8 *arg0) {
    return *(s32 *)(arg0 + 0x22C);
}

s32 func_8007950C(u8 *arg0) {
    return *(s32 *)(arg0 + 0x230);
}

s32 func_80079518(u8 *arg0) {
    u8 *p = (u8 *)func_80079500(arg0);
    return *(s32 *)p;
}

s32 func_8007953C(u8 *arg0) {
    u8 *p = (u8 *)func_8007950C(arg0);
    return *(s32 *)p;
}

u8 *func_80079560(u8 *arg0) {
    u8 *r = arg0 + 0x2DC;
    *(s32 *)(arg0 + 0x2F4) = 0;
    *(s32 *)(arg0 + 0x2F8) = 0;
    *(s32 *)(arg0 + 0x2FC) = 0;
    *(s32 *)(arg0 + 0x300) = 0;
    *(s32 *)(arg0 + 0x304) = 0;
    *(s32 *)(arg0 + 0x308) = 0;
    return r;
}

void func_80079580(u8 *arg0) {
    func_80079AA4(arg0, -1, 0, 0, -1);
}

void func_800795B0(u8 *arg0) {
    s32 p = *(s32 *)(arg0 + 0x238);
    if (*(s32 *)(p + 0x20) > 0) {
        func_8007754C(arg0);
        func_800775AC(arg0);
        func_8007F9D4(*(u8 **)(arg0 + 0x238));
    }
}

s32 func_80079604(u8 *arg0) {
    /* $v0/$v1 keep the counter and destination in the retail register order. */
    register u32 counter asm("$2");
    register u32 manager asm("$3");
    *(u8 **)(*(u8 **)arg0 + 4) = *(u8 **)(arg0 + 4);
    *(u8 **)(*(u8 **)(arg0 + 4)) = *(u8 **)arg0;
    *(u8 **)arg0 = arg0;
    *(u8 **)(arg0 + 4) = arg0;
    func_8006F0CC(*(u8 **)(arg0 + 0x228), arg0);
    func_80079680(arg0);
    counter = *(u32 *)(arg0 + 0x21C);
    manager = *(u32 *)(arg0 + 0x228);
    *(s32 *)(manager + 0xD30) = counter + 1;
    return func_8002BDC8(*(s32 *)(arg0 + 0x248)) != 0;
}

void func_80079680(u8 *self) {
    switch (*(u32 *)(self + 0x218)) {
    case 0:
    case 2:
    case 3:
    case 11:
    case 12:
    case 17:
    case 18:
    case 19:
    case 20: {
        u8 *allocation = func_8002BD88(0x40);
        u8 *object = func_800C44A0(allocation, *(s32 *)(self + 0x21C));
        *(s32 *)(self + 0x248) = func_8002BD74(object);
        func_8002BF34((DtorNode *)self, (DtorNode *)object);
        func_8001BE78((s32)(u32)D_8005F824, func_8001D97C(D_8005F8B8, *(s32 *)(self + 0x21C)), 0);
        break;
    }
    default:
        break;
    }
}

void func_8007972C(u8 *arg0) {
    func_8002BE64(*(s32 *)(arg0 + 0x248));
    *(s32 *)(arg0 + 0x248) = 0;
    *(u8 **)(*(u8 **)arg0 + 4) = *(u8 **)(arg0 + 4);
    *(u8 **)(*(u8 **)(arg0 + 4)) = *(u8 **)arg0;
    *(u8 **)arg0 = arg0;
    *(u8 **)(arg0 + 4) = arg0;
    func_8006F09C(*(u8 **)(arg0 + 0x228), arg0);
    *(s32 *)(*(u8 **)(arg0 + 0x228) + 0xD30) = 0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80079794);

s32 func_80079964(u8 *self, s32 animation, s32 value, s32 options) {
    s32 handler = *(s32 *)(self + 0x3FC);
    s32 result;
    if (animation < 0) {
        result = func_800207C0(handler, -1, 0, 0, 0);
    } else {
        *(s32 *)(self + 0x250) = animation;
        *(s32 *)(self + 0x24C) = value;
        result = func_80079C80(self);
        if (result != 0) {
            func_800207C0(handler, animation, value,
                          func_80031298(*(u8 **)(self + 0x3F8), animation), options);
            result = func_800207E8(handler, func_80031258(*(u8 **)(self + 0x3F8), animation));
        }
    }
    return result;
}

void func_80079A2C(u8 *arg0, s32 arg1) {
    s32 object = *(s32 *)(arg0 + 0x3FC);
    s32 count = 2;
    do {
        func_800207C0(object, arg1, 0, 0, 0);
        func_800207A0(object);
        count--;
    } while (count != 0);
    func_800207C0(object, -1, 0, 0, 0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80079AA4);

s32 func_80079B68(u8 *arg0, s32 arg1) {
    register u8 *self asm("$16"); /* pin $s0: retail retains the object base across calls */
    register s32 value asm("$17"); /* pin $s1: retail retains the second argument */
    self = arg0;
    value = arg1;
    /* This no-op preserves the compiler's retail scheduling for the saved arguments. */
    do { } while (0);
    if (func_8003049C((const TaskManager *)(u32)(*(u32 *)(self + 0x3FC) + 0x68u), value) != 0) {
        return 1;
    }
    return func_80031298(*(u8 **)(self + 0x3F8), value) >= 0x1000;
}

s32 func_80079BC4(u8 *arg0) {
    s32 result = func_80020780(*(s32 *)(arg0 + 0x3FC));
    if (result != 0 && *(s32 *)(arg0 + 0x254) >= 0) {
        *(s32 *)(arg0 + 0x254) = -1;
    }
    return result;
}

s32 func_80079C14(u8 *arg0) {
    register u8 *self asm("$17"); /* pin $s1: keep the base live through the second call */
    register s32 object asm("$16"); /* pin $s0: retain the resource pointer across calls */
    self = arg0;
    object = *(s32 *)(self + 0x3FC);
    if (func_80020780(object) == 0 && *(s32 *)(self + 0x250) >= 0) {
        return func_80020760(object) != *(s32 *)(self + 0x250);
    }
    return 1;
}

s32 func_80079C80(u8 *arg0) {
    register u8 *self asm("$17"); /* pin $s1: keep the base live through the second call */
    register s32 object asm("$16"); /* pin $s0: retain the resource pointer across calls */
    self = arg0;
    object = *(s32 *)(self + 0x3FC);
    if (func_80020780(object) == 0 && *(s32 *)(self + 0x254) >= 0) {
        return func_80020760(object) != *(s32 *)(self + 0x254);
    }
    return 1;
}

void func_80079CEC(u8 *arg0) {
    *(s32 *)(arg0 + 0x37C) |= 0x20;
    ((void (*)(u8 *, s32))func_800774C8)(arg0, 1);
    *(s32 *)(arg0 + 0x3B4) = 0;
    *(s32 *)(arg0 + 0x3B8) = 0;
    *(s32 *)(arg0 + 0x3BC) = 0;
    *(s32 *)(arg0 + 0x3C0) = 0;
    *(s32 *)(arg0 + 0x3A4) = 0;
    *(s32 *)(arg0 + 0x3A8) = 0;
    *(s32 *)(arg0 + 0x3AC) = 0;
    *(s32 *)(arg0 + 0x3B0) = 0;
    func_80080BC4(*(s32 *)(arg0 + 0x22C), 1);
    func_80081CB8(*(s32 *)(arg0 + 0x230));
}

void func_80079D58(u8 *arg0) {
    *(s32 *)(arg0 + 0x37C) |= 0x80;
}

void func_80079D6C(u8 *arg0) {
    *(s32 *)(arg0 + 0x37C) |= 0x40;
}

void func_80079D80(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x334) = arg1;
}

void func_80079D88(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x338) = arg1;
}

void func_80079D90(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x33C) = arg1;
}

void func_80079D98(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x224) = arg1;
}

void func_80079DA0(u8 *arg0, s32 arg1) {
    s32 v = *(s32 *)(arg0 + 0x444);
    if ((v ^ -1) != arg1) {
        *(s32 *)(arg0 + 0x444) = arg1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80079DC0);

void func_80079E4C(u8 *arg0) {
    s32 buf[4];
    func_80079E90(buf, arg0 + 0x3A4, arg0 + 0x3B4, *(s32 *)(arg0 + 0x3C4));
    *(s32 *)(arg0 + 0x3B4) = 0;
    *(s32 *)(arg0 + 0x3B8) = 0;
    *(s32 *)(arg0 + 0x3BC) = 0;
    *(s32 *)(arg0 + 0x3C0) = 0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_80079E90);

s32 func_80079F68(u8 *arg0, s32 arg1) {
    u8 *target = func_800732A8(*(u8 **)(arg0 + 0x228), arg0);
    s32 total;
    if (func_8007A008(target) == 0) {
        return 0;
    }
    total = func_8007A04C(arg0) + func_8007A04C(target) + D_80065260[arg1];
    return func_8007A0C4(arg0, D_80010884, (s32)((s64)total * total), 0x155);
}

s32 func_8007A008(u8 *arg0) {
    if (func_80078FC4(arg0) != 0) {
        return 0;
    }
    return (*(u32 *)(arg0 + 0x37C) >> 3) & 1;
}

s32 func_8007A04C(u8 *arg0) {
    s32 v = *(s16 *)((u8 *)func_8007773C(arg0) + 2);
    return v - v / 4;
}

s32 func_8007A084(u8 *arg0) {
    s32 r = -1;
    if (*(s32 *)(arg0 + 0x3EC) == 0x401) {
        r = 1;
    }
    return r;
}

void func_8007A0A0(u8 *arg0) {
    func_8007FE74(*(s32 *)(arg0 + 0x22C));
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_8007A0C4);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_8007A260);

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_8007A2B8);

void func_8007A328(u8 *arg0) {
    *(s32 *)(arg0 + 0x448) |= func_8007A2B8(arg0);
}

void func_8007A358(u8 *arg0) {
    *(s32 *)(arg0 + 0x448) = func_8007A2B8(arg0);
}

s32 func_8007A380(u8 *arg0) {
    return *(s32 *)(arg0 + 0x340);
}

s32 func_8007A38C(u8 *arg0) {
    return ++*(s32 *)(arg0 + 0x340);
}

void func_8007A3A0(u8 *arg0, s32 arg1) {
    if (arg1 != 0) {
        if (*(s32 *)(arg0 + 0x494) <= 0) {
            *(s32 *)(arg0 + 0x494) = 5;
        }
    } else {
        *(s32 *)(arg0 + 0x494) = 0;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_8007A3CC);

s32 func_8007A660(s32 *point, s32 y_offset, s32 width) {
    s32 left[4];
    s32 center[4];
    s32 right[4];
    s32 extent = (s32)((u32)width + (u32)(width / 3));
    s32 result = 0;
    center[0] = point[0];
    center[2] = point[2];
    center[1] = (s32)((u32)point[1] + (u32)y_offset);
    left[0] = (s32)((u32)center[0] - (u32)extent);
    left[1] = center[1];
    left[2] = center[2];
    right[0] = (s32)((u32)center[0] + (u32)extent);
    right[1] = center[1];
    right[2] = center[2];
    if (func_80073010((u8 *)left, (u8 *)center) != 0) {
        result = -1;
    }
    if (func_80073010((u8 *)right, (u8 *)center) != 0) {
        result += 1;
    }
    return result;
}

void func_8007A718(u8 *arg0) {
    *(s32 *)(arg0 + 0x48C) = 8;
}

INCLUDE_ASM("asm/us/game/nonmatchings/12398", func_8007A724);
