#include "game_sprite_cleanup.h"
#include "game_rotation.h"
#include "game_math.h"
#include "game_placement_api.h"
#include "game_audio_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_random.h"

extern u8 D_80065154[];
extern u8 D_8005F824[];
extern u8 D_800D3EEC[];
extern u8 D_800D3DEC[];
extern u8 D_800D3DFC[];
extern u8 D_800D3E4C[];
extern u8 D_800D3EC4[];
extern u8 D_800D3DF4[];
extern u8 D_800D3E74[];
extern u8 D_800D3E9C[];
extern u8 D_800D3E24[];
extern u8 D_800D3D54[];
extern u8 D_800D3D5C[];
extern u8 D_800D3D7C[];
extern u8 D_800D3C94[];
extern u8 D_800D3C04[];
extern u8 D_800D3C34[];
extern u8 D_800D3B04[];
extern u8 D_800D3B14[];
extern u8 D_800D3B24[];
extern u8 D_800D3B34[];
extern u8 D_800D3B84[];
extern u8 D_800D3BD4[];
extern u8 D_800D3C64[];
extern u8 D_800D3C6C[];
extern u8 D_800D3C74[];
extern u8 D_800D3C84[];
extern u8 D_800D3F0C[];
extern u8 D_800D3F84[];
extern u8 D_80010894[];
extern u8 D_80010814[];
extern u8 D_800641B8[];
extern u8 D_80065174[];

extern void func_800727AC();
extern void func_800D4E94();
extern void func_8002B3D0();
extern void func_8001BEDC();

extern void func_8002BCEC();
extern void func_8002BDA8();
extern void func_8002BE14();
extern void func_8002D694();
extern void func_8002D6FC();
extern s32 func_8002D8B0();
extern u8 *func_8002E5C0();
extern u8 *func_8002FC28();
extern void func_8003E00C();
extern void func_8005844C();
extern void func_8006F04C();
extern void func_8006F06C();
extern void func_8006F09C();
extern s32 func_8006F12C();
extern s32 func_8006F178();
extern u8 *func_8006EF44();
extern u8 *func_800700B0();
extern void func_80070300();
extern void func_800720EC();

extern void func_80077654();

extern u8 *func_8007773C();
extern void func_80075F88();
extern void func_800794D4();
extern void func_80079964();
extern void func_8007F340();
extern void func_80079158();
extern void func_800C7A64();
extern void func_80071F64();
extern void func_800700CC();
extern u8 *func_8002BD88();
extern void func_8006F23C();
extern void func_8006ED08();
extern void func_80076B98();
extern void func_80076B50();
extern void func_80020F00();
extern void func_80020F7C();
extern void func_80020DC0();
extern void func_80020DE4();
extern void func_80070128();
extern u8 *func_8006EF4C();
extern u8 *func_80028078();
extern void func_80030228();
extern s32 func_80032EE8();
extern void func_80053E8C();
extern void func_800254CC();
extern void func_8002447C();
extern void func_800213C4();
extern void func_800237F4();
extern void func_8002E860();
extern void func_800330C8();
extern void func_8002310C();
extern void func_80023130();
extern void func_80023154();
extern void func_800231B0();
extern void func_80023258();
extern void func_800232A4();

typedef struct StageVec3 { s32 x, y, z; } StageVec3;

u8 *func_800D655C(u8 *self, StageVec3 *position, s32 target_x, s32 target_y) {
    s32 x, y, z;
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_800D3E4C;
    x = position->x;
    y = position->y;
    z = position->z;
    *(s32 *)(self + 0x30) = target_x;
    *(s32 *)(self + 0x34) = target_y;
    *(s32 *)(self + 0x28) = 0;
    *(s32 *)(self + 0x2C) = 0;
    *(s32 *)(self + 0x38) = 0xFF;
    *(s32 *)(self + 0x18) = x;
    *(s32 *)(self + 0x1C) = y;
    *(s32 *)(self + 0x20) = z;
    return self;
}

void func_800D65E8(u8 *arg0) {
    s32 target_x = *(s32 *)(arg0 + 0x30);
    s32 x = *(s32 *)(arg0 + 0x28);
    s32 target_y = *(s32 *)(arg0 + 0x34);
    s32 y = *(s32 *)(arg0 + 0x2C);
    s32 v;

    *(s32 *)(arg0 + 0x28) = (s32)((u32)x + (u32)((s32)((u32)target_x - (u32)x) >> 2));
    *(s32 *)(arg0 + 0x2C) = (s32)((u32)y + (u32)((s32)((u32)target_y - (u32)y) >> 2));
    v = (s32)((u32)*(s32 *)(arg0 + 0x38) - 0x18u);
    *(s32 *)(arg0 + 0x38) = v;
    if (v <= 0) {
        if (arg0 != 0) {
            u8 *p = *(u8 **)(arg0 + 0x14);
            void (*fn)(u8 *, s32);
            fn = *(void (**)(u8 *, s32))(p + 0x1C);
            fn((u8 *)((u32)arg0 + (u32)(s32)*(s16 *)(p + 0x18)), 3);
        }
    }
}

INCLUDE_ASM("asm/us/st05/nonmatchings/4CC", func_800D6668);

u8 *func_800D67DC(u8 *self, StageVec3 *position, s32 target_x, s32 target_y) {
    s32 x, y, z;
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_800D3E24;
    x = position->x;
    y = position->y;
    z = position->z;
    *(s32 *)(self + 0x2C) = target_y;
    *(s32 *)(self + 0x30) = target_x;
    *(s32 *)(self + 0x28) = 0;
    *(s32 *)(self + 0x34) = 0xFF;
    *(s32 *)(self + 0x18) = x;
    *(s32 *)(self + 0x1C) = y;
    *(s32 *)(self + 0x20) = z;
    return self;
}

/* Registers come out of the allocator swapped (retail: object $a1, three
   temporaries $v0/$a0/$v1, callback $v1); each is pinned to reproduce
   (see docs/DIFFICULT_FUNCTIONS.md, register pinning last resort). */
