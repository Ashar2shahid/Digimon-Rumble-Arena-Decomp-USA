#include "game_audio_api.h"
#include "common.h"
#include "resource_loader.h"
#include "object_factory_api.h"

/* These factories return the constructed pointer consumed by2A010. */
extern u8 *func_8002B364(u32 size);
extern u8 *func_8001C5AC(u8 *self, s32 mode);
extern u8 *func_80071F20(u8 *self, u8 *context);
extern u8 *func_8006D684(u8 *self);
extern u8 *func_80067764(u8 *self, s32 mode);

extern u8 func_8005FC70[];
extern u8 D_80018A24[];
extern u8 D_8005F824[];
extern u8 *D_8005FC78;
extern u8 D_80018A34[];




extern s32 func_80033498(u8 *, u8 *);
extern s32 func_8003DF1C(const void *, const void *, u32);
extern u8 D_800641D4[4];

u8 *func_80028004(u8 *arg0, u8 *compressed) {
    func_80033498(arg0, compressed);
    return arg0;
}
s32 func_8002802C(u8 *arg0) {
    return func_8003DF1C(arg0, D_800641D4, 4) == 0;
}

extern u32 D_800641B8;

u8 *func_80028050(void) {
    u8 *command = (u8 *)D_800641B8;
    D_800641B8 = (u32)command + 0x14U;
    command[3] = 4;
    command[7] = 0x64;
    return command;
}

u8 *func_80028078(void) {
    u8 *command = (u8 *)D_800641B8;
    D_800641B8 = (u32)command + 0x10U;
    command[3] = 3;
    command[7] = 0x60;
    return command;
}

INCLUDE_ASM("asm/us/main/nonmatchings/18800", func_800280A0);


INCLUDE_ASM("asm/us/main/nonmatchings/18800", func_80028108);

INCLUDE_ASM("asm/us/main/nonmatchings/18800", func_80028230);

void *func_80028258(void) {
    return func_8001C5AC(func_8002B364(0x34), 0);
}

void *func_80028284(void) {
    return func_8001C5AC(func_8002B364(0x34), 1);
}

void *func_800282B0(void) {
    return func_80071F20(func_8002B364(0x113C), func_8005FC70);
}

u8 *func_800282E0(void) {
    return func_80070240(func_8002B364(0xA90), func_8005FC70, 0);
}

void func_80028314(void) {
    func_80068178(func_8002B364(0x474), func_8005FC70, 1);
}

void func_80028348(void) {
    func_8006B070(func_8002B364(0x44), func_8005FC70);
}


u8 *func_80028378(void) {
    return func_80073F88(func_8002B364(0x234), func_8005FC70, 0x25);
}

u8 *func_800283AC(void) {
    return func_8006E1B4(func_8002B364(0x64), func_8005FC70);
}

void func_800283DC(void) {
    func_80065AC4(func_8002B364(0xF4C), func_8005FC70);
}

void func_8002840C(void) {
    func_80066064(func_8002B364(0x14C), func_8005FC70);
}

void func_8002843C(void) {
    func_80067384(func_8002B364(0xA1C), func_8005FC70);
}

void func_8002846C(void) {
    func_80066F54(func_8002B364(0xA5C), func_8005FC70);
}

void func_8002849C(void) {
    func_80068184(func_8002B364(0x30), func_8005FC70);
}

void func_800284CC(void) {
    func_8006A41C(func_8002B364(0x30), func_8005FC70);
}

u32 func_800284FC(void) {
    func_8002A810(D_80018A24);
    return 0;
}

void *func_80028520(void) {
    return func_8006D684(func_8002B364(0x8C));
}

void *func_80028548(void) {
    return func_80067764(func_8002B364(0x90), 0);
}

void func_80028574(s32 arg0, s32 arg1, s32 flags) {
    s32 count = 1;

    if (flags & 4) {
        count = 16;
    }
    if (flags & 1) {
        count = 128;
    }

    count--;
    if (count != -1) {
        do {
            func_8002C448(arg0);
            count--;
        } while (count != -1);
    }

    func_8001BE78((s32)(u32)D_8005F824, 0x13, 0);
}

void func_800285FC(s32 arg0, s32 arg1, s32 flags) {
    s32 count = 1;

    if (flags & 4) {
        count = 16;
    }
    if (flags & 1) {
        count = 128;
    }

    count--;
    if (count != -1) {
        do {
            func_8002C4C4(arg0);
            count--;
        } while (count != -1);
    }

    func_8001BE78((s32)(u32)D_8005F824, 0x13, 0);
}

