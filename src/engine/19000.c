#include "common.h"
#include "debug_module.h"

extern u8 D_8005F824[];
extern void func_8001BCF8(void *);
extern void func_8001BCC4(void *);
extern void func_8001C09C(void *, s32);
extern u8 D_80018A40[];
extern u8 *func_80028684(s32, s32, s32);
extern void func_8002AAD8(void *, const u8 *, ...);
extern void func_800286F8(void *, s32, s32, s32);



s32 func_80028804(u8 *self, void *context) {
    func_8002A010(context, *(ModuleConstruct *)(self + 0x28), *(const char **)(self + 0x2C));
    return -1;
}

void func_80028834(u8 *self, s32 arg1, s32 arg2) {
    void *packet = func_80028684(arg1, arg2, *(s32 *)(self + 0xC));
    func_8002AAD8(packet, D_80018A40, *(s32 *)(self + 0xC), *(const char **)(self + 0x24));
}


extern u8 D_80018FA4[];

DebugChoice *func_80028880(DebugChoice *self, const char *name, const char **choices, u32 count) {
    func_8002C3CC(&self->base, 0);
    self->name = name;
    self->choices = choices;
    self->base.f1C = D_80018FA4;
    self->base.f18 = count - 1U;
    return self;
}

/* Historical288E8 is the return delay slot of this complete constructor. */
__asm__(".globl func_800288E8\n.set func_800288E8, func_80028880 + 0x68\n.size func_800288E8, 4");

INCLUDE_ASM("asm/us/main/nonmatchings/19000", func_800288EC);

INCLUDE_ASM("asm/us/main/nonmatchings/19000", func_80028954);



INCLUDE_ASM("asm/us/main/nonmatchings/19000", func_800289BC);




INCLUDE_ASM("asm/us/main/nonmatchings/19000", func_80028A10);


INCLUDE_ASM("asm/us/main/nonmatchings/19000", func_80028BE0);





struct DispatchState;
extern void func_8002C9A4(struct DispatchState *state);

s32 func_80028E68(struct DispatchState *state) {
    func_8002C9A4(state);
    return 0;
}

void func_80028E88(u8 *self, s32 arg1, s32 arg2, s32 enabled) {
    if (enabled != 0) {
        func_800286F8(self, arg1, arg2, enabled);
    } else {
        void *packet = func_80028684(arg1, arg2, *(s32 *)(*(u8 **)self + 0xC));
        func_8002AAD8(packet, D_80018A40, *(s32 *)(*(u8 **)self + 0xC), *(const char **)(self + 0x28));
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/19000", func_80028EF0);

s32 func_80028F38(void) {
    func_8001BCF8(D_8005F824);
    func_8001BCC4(D_8005F824);
    return 0;
}

s32 func_80028F70(u8 *self) {
    s32 id = *(s32 *)(self + 0x10);
    func_8001C09C(D_8005F824, id);
    return -1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/19000", func_80028F98);
