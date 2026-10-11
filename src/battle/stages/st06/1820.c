#include "game_base_api.h"
#include "common.h"

extern u8 D_800D3D54[];

u8 *func_800D5320(u8 *arg0) {
    func_8002BC9C(arg0, 0);
    *(u32 *)(arg0 + 0x14) = (u32)D_800D3D54;
    *(s32 *)(arg0 + 0x18) = 0;
    *(s32 *)(arg0 + 0x1C) = 0;
    *(s32 *)(arg0 + 0x20) = 0;
    *(s32 *)(arg0 + 0x24) = 0x100;
    return arg0;
}

