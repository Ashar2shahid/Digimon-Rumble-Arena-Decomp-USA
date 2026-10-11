#include "common.h"

extern u8 D_800D3BA4[];
extern u8 D_800D3C1C[];
extern u8 D_800D3BF4[];
extern u8 D_800D3BCC[];
extern u8 D_800D3B54[];
extern u8 D_800D3B7C[];
extern u8 D_800D3B34[];
extern void func_8002BCEC(void *a0, s32 a1);
extern void func_8002BDA8(void *a0);
extern void *func_8002B364(s32);
extern void *func_800D3C94(void *, s32);

extern void func_800D05B0(u8 *, s32);

void func_800D3E68(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0xD34) = (s32)D_800D3C1C;
    func_800D05B0(arg0, arg1);
}

