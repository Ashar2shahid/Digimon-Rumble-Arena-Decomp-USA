#include "game_base_api.h"
#include "common.h"

extern u8 D_800D3E0C[];

u8 *func_800D4748(u8 *arg0, u8 *arg1) {
    func_8002BC9C(arg0, 0);
    *(s32 *)(arg0 + 0x18) = 0;
    *(u32 *)(arg0 + 0x14) = (u32)D_800D3E0C;
    *(s16 *)(arg0 + 0x1C) = 0;
    *(u8 *)(arg0 + 0x1E) = 0;
    *(u8 *)(arg0 + 0x1F) = 0;
    *(u32 *)(arg0 + 0x20) = (u32)arg1;
    *(s32 *)(arg0 + 0x24) = 0;
    return arg0;
}

