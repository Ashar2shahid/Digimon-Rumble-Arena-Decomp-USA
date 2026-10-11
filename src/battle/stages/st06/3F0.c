#include "game_rotation.h"
#include "game_placement_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#include "psx.h"

extern u8 D_800D3C5C[];
extern u8 D_800D3D84[];
extern u8 D_800D3DAC[];
DISPENV *func_8001F92C(void);
s32 func_8002366C();
void func_80023F8C();
void func_80024204();
void func_8002BCEC(u8 *, s32);
void func_8002BDA8(u8 *);
s32 func_8002BD74();
s32 func_8002BD88();
s32 func_8002BDC8();
s32 func_8002BE14();
u8 *func_8002E6B0(const void *, s32, s32);
s32 func_80031C20();
void func_8005844C();
s32 func_8006EF44();
void func_8006F06C();
void func_800727AC();
u8 *func_800D4684(u8 *);
void func_800D5444();
u8 *func_800D489C();
u8 *func_800D49A4();
u8 *func_800D51A0();

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D3EF0);

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D3FB0);

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D4020);

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D41B8);

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D42E8);

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D449C);

void func_800D461C(u8 *arg0) {
    u8 *p;
    u8 *s1;

    func_800727AC(arg0);
    p = (u8 *)func_8006EF44(arg0);
    s1 = *(u8 **)(p + 0x10);
    if (*(u32 *)(arg0 + 0xD7C) != 0) {
        *(u32 *)(arg0 + 0xD7C) = 0;
        func_8005844C(s1, func_8002E6B0(func_8001F92C(), 0x200, 0));
    }
}

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D4684);

void func_800D4714(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *p = arg0 + ((arg1 << 3) + 0xD38);
    if (arg2 >= 0) {
        *(s32 *)(p + 4) = arg2;
    }
    func_800D4684(p);
}

