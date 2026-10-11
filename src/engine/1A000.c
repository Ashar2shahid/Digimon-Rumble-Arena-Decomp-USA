#include "game_heap_wrappers.h"
#include "render_context.h"
#include "common.h"
#include "game_input.h"
#include "psx.h"
#include "resource_loader.h"

extern u8 D_80019064[];
extern u32 D_8005FC70[];
extern void func_8002A298(void *, s32);
extern void func_8002B770(void *, s32);
extern void func_8002B0CC(void *);
extern void func_8001F260(u32, s32);
extern void func_8001F278(u32, s32, s32, s32);
extern void func_8001F708(u32, s32);
extern void func_8001F678(u32, s32);
extern u8 D_8006430C[];
extern s32 func_8005858C(void *);
extern TIM_IMAGE *func_8005859C(TIM_IMAGE *);

INCLUDE_ASM("asm/us/main/nonmatchings/1A000", func_80029800);

void func_80029BEC(u8 *self, s32 flags) {
    *(void **)(self + 0x1C) = D_80019064;
    func_8002A298(self + 0x70, 2);
    func_8002A298(self + 0x24, 2);
    func_8002B770(self, 0);
    if (flags & 1) {
        func_8002B0CC(self);
    }
}

void func_80029C5C(void) {
    u32 handle = D_8005FC70[0];
    func_80026E0C(D_8005FC70[1], 0x10, 4);
    func_8001F4BC((RenderContext *)handle, 0x200, 0x1E0);
    func_8001F260(handle, 1);
    func_8001F278(handle, 0, 0x40, 0);
    func_8001F708(handle, 1);
    func_8001F678(handle, 0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A000", func_80029CDC);

void func_80029FCC(void) {
    TIM_IMAGE image;
    u8 *data = func_80027C14(D_8006430C);

    func_8005858C(data);
    func_8005859C(&image);
    func_8002B2B4(data);
}
