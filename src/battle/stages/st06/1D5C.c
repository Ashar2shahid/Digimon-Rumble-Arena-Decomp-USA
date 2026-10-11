#include "game_base_api.h"
#include "common.h"

extern u8 D_800D3D04[];

u8 *func_800D585C(u8 *arg0) {
    func_8002BC9C(arg0, 0);
    *(u32 *)(arg0 + 0x14) = (u32)D_800D3D04;
    *(s32 *)(arg0 + 0x18) = 0;
    *(s32 *)(arg0 + 0x1C) = -0x200;
    *(s32 *)(arg0 + 0x20) = 0x4000;
    *(s32 *)(arg0 + 0x28) = 0;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s32 *)(arg0 + 0x30) = 0;
    return arg0;
}

