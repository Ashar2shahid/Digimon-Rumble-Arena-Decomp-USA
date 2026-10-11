#include "common.h"
#include "debug_module.h"
extern u8 func_8005FC70[];
extern u8 D_80018A24[];
extern u8 D_8005F824[];
extern u8 *D_8005FC78;
extern u8 D_80018A34[];


u8 *func_80028684(s32 arg0, s32 arg1, s32 arg2) {
    u8 *ptr = D_8005FC78;

    func_8002AA24(ptr, 2, arg2 + 1);
    if (arg1 != 0) {
        func_8002AA78(ptr, 0x80, 0x80, 0x80);
    } else {
        func_8002AA78(ptr, 0x40, 0x40, 0x40);
    }
    return ptr;
}

void func_800286F8(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 != 0) {
        u8 *ptr = D_8005FC78;

        func_8002AA78(ptr, 0xFF, 0xFF, 0);
        func_8002AA24(ptr, 0, 0);
        func_8002AAD8(ptr, D_80018A34, arg0[10]);
    }
    func_8002CFB0(arg0, arg1, arg2, arg3);
}

extern u8 D_80019004[];

DebugModule *func_8002879C(DebugModule *self, const char *name, ModuleConstruct construct, const char *overlayPath) {
    func_8002C3CC(&self->base, 0);
    self->name = name;
    self->construct = construct;
    self->overlayPath = overlayPath;
    self->base.f1C = D_80019004;
    return self;
}

/* Retail28800 is the return delay slot, not a separate function. */
__asm__(".globl func_80028800\n.set func_80028800, func_8002879C + 0x64\n.size func_80028800, 4");

