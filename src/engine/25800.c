#include "common.h"
#include "game_vfs.h"

extern u8 D_801153C0[];
extern void func_800388A8(u8 *list, void *nodes, s32 stride, s32 count);
extern s32 func_800359D4(void);

INCLUDE_ASM("asm/us/main/nonmatchings/25800", func_80035000);

void func_80035050(void) {
    func_800388A8(D_801153C0, D_801153C0 + 0x14, 0x80, 4);
}

ResourceReadComplete func_80035080(ResourceReadComplete callback) {
    ResourceReadComplete old = D_80114B80.readComplete;
    D_80114B80.readComplete = callback;
    return old;
}

INCLUDE_ASM("asm/us/main/nonmatchings/25800", func_80035094);

void *func_800350DC(void *user) {
    void *old = D_80114B80.user;
    D_80114B80.user = user;
    return old;
}

INCLUDE_ASM("asm/us/main/nonmatchings/25800", func_800350F0);

INCLUDE_ASM("asm/us/main/nonmatchings/25800", func_80035168);

INCLUDE_ASM("asm/us/main/nonmatchings/25800", func_80035238);

INCLUDE_ASM("asm/us/main/nonmatchings/25800", func_80035358);

INCLUDE_ASM("asm/us/main/nonmatchings/25800", func_80035600);

INCLUDE_ASM("asm/us/main/nonmatchings/25800", func_8003569C);

INCLUDE_ASM("asm/us/main/nonmatchings/25800", func_800356E8);

void func_80035790(void) {
    if (func_800359D4()) {
        D_80116668.flags &= ~4U;
        D_80116668.event(4);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/25800", func_800357DC);
