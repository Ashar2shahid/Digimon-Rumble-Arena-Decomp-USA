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

/* Pinned: retail computes the `t < 1` flag into $v1; pinning the comparison
   result (the loaded value is copy-propagated, so the load pin is ignored —
   pin the *result* instead) reproduces the allocator's choice.  See
   docs/DIFFICULT_FUNCTIONS.md, register pinning last resort. */
void func_800D536C(u8 *arg0, u8 *arg1) {
    u8 *p = arg0;
    u8 *s1;
    s32 v;
    v = *(s32 *)(p + 0x20) + *(s32 *)(p + 0x24);
    *(s32 *)(p + 0x20) = v;
    if (v >= 0x800) {
        *(s32 *)(p + 0x20) = v - 0x800;
        s1 = (u8 *)func_8002BE14(0x28);
        if (s1 != 0) {
            func_800D5444((u8 *)func_8002BD80(0x28, s1), *(s32 *)(p + 0x1C));
        }
        func_8006F06C(arg1, s1);
        {
            register u32 t asm("$3");
            t = *(u32 *)(p + 0x1C) < 1;
            *(u32 *)(p + 0x1C) = t;
        }
    }
    {
        s32 w = *(s32 *)(p + 0x24) - 1;
        *(s32 *)(p + 0x24) = w;
        if (w <= 0) {
            if (p != 0) {
                u8 *o = *(u8 **)(p + 0x14);
                s16 x = *(s16 *)(o + 0x18);
                register void (*fn)(u8 *, s32) asm("$3");
                fn = *(void (**)(u8 *, s32))(o + 0x1C);
                fn(p + x, 3);
            }
        }
    }
}

void func_800D543C(void) {
}

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D5444);

/* Retail computes the half-rate term in $v1 and keeps the vtable callback in
   $v1 too; pinning both temps reproduces the allocator's choice (see
   docs/DIFFICULT_FUNCTIONS.md, register pinning last resort). */
void func_800D549C(u8 *arg0) {
    register s32 t asm("$3");
    s32 v;

    v = *(s32 *)(arg0 + 0x18) + 0x30;
    *(s32 *)(arg0 + 0x18) = v;
    if (v >= 0x281) {
        *(s32 *)(arg0 + 0x18) = 0x280;
    }
    t = *(s32 *)(arg0 + 0x24) >> 1;
    v = *(s32 *)(arg0 + 0x1C) + t;
    *(s32 *)(arg0 + 0x1C) = v;
    if (v >= 0x118) {
        if (arg0 != 0) {
            u8 *o = *(u8 **)(arg0 + 0x14);
            register void (*fn)(u8 *, s32) asm("$3");
            fn = *(void (**)(u8 *, s32))(o + 0x1C);
            fn(arg0 + *(s16 *)(o + 0x18), 3);
        }
    } else {
        *(s32 *)(arg0 + 0x24) = *(s32 *)(arg0 + 0x24) + 1;
    }
}

INCLUDE_ASM("asm/us/st06/nonmatchings/3F0", func_800D5534);

