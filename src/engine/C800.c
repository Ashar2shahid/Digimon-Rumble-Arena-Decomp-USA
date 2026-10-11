#include "game_lerp_words.h"
#include "game_audio_api.h"
#include "common.h"
#include "title_factories.h"
#include "object_factory_api.h"
extern u8 *func_8006D684(u8 *self);
extern u8 *func_8006ECC8(u8 *self, s32 mode);
#include "game_resources.h"

/* VRAM 0x8005FC70 is libgpu's DrawSyncCallback, an own manifest entry since
 * the library carve; the game passes its address to the helpers below. */
extern u8 func_8005FC70[];
extern s32 D_8005FB5C;
extern u16 D_8005F908;
extern s32 D_8005FB6C;
extern u8 *func_8002B364(u32 size);
extern u8 *func_80068178(u8 *self, u8 *context, s32 mode);
extern void func_8001C2BC(s32 *object, s32 enabled);

INCLUDE_ASM("asm/us/main/nonmatchings/C800", func_8001C000);

INCLUDE_ASM("asm/us/main/nonmatchings/C800", func_8001C008);

void func_8001C09C(s32 arg0, s32 arg1) {
    func_8001BF40(arg0, arg1, 1);
    func_80039414(arg1 & 0xFFFF);
}

s32 func_8001C0CC(void *arg0, s32 arg1) {
    func_8001C008(arg0, arg1, 1);
    return func_80039AF4(arg1 & 0xFFFF);
}

void func_8001C0FC(s32 arg0, s32 arg1) {
    func_800350F0(arg0, arg1);
    func_80035D28(arg1 & 0xFFFF);
}

void func_8001C128(void) {
    func_80035D44();
}

void func_8001C148(u8 *arg0) {
    func_8001C1E0(arg0, 0);
    func_800356E8();
}

void func_8001C170(u8 *arg0) {
    func_8002D64C((u32 *)(arg0 + 0x3C), 0x7F, 0);
    func_800356E8();
}

void func_8001C1A0(void) {
    func_8003569C();
}

void func_8001C1C0(void) {
    func_80035790();
}

void func_8001C1E0(u8 *arg0, s32 arg1) {
    func_8002D64C((u32 *)(arg0 + 0x3C), 0x50, (u32)arg1);
}

void func_8001C208(u8 *arg0, s32 arg1) {
    func_8002D64C((u32 *)(arg0 + 0x3C), 0, (u32)arg1);
}

void func_8001C230(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg1 >= 0x51) {
        arg1 = 0x50;
    }
    func_8002D64C((u32 *)(arg0 + 0x3C), (u32)arg1, (u32)arg2);
}

void func_8001C25C(s32 *object, s32 enabled) {
    func_8001C2BC(object, enabled);
    if (enabled) {
        func_8001C1A0();
        func_8001BE78((s32)(u32)object, 0x14, 0);
    } else {
        func_8001C148((u8 *)object);
    }
}

void func_8001C2BC(s32 *arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0[0x17] = arg0[0x17] + 1;
    } else if (arg0[0x17] > 0) {
        arg0[0x17] = arg0[0x17] - 1;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C800", func_8001C2F4);

s32 func_8001C360(u8 *arg0) {
    return *(s32 *)(arg0 + 0x28);
}

void func_8001C36C(void) {
    func_80066930(func_8002B364(0x34), func_8005FC70);
}

void func_8001C39C(void) {
    func_80071F20(func_8002B364(0x113C), func_8005FC70);
}

u8 *func_8001C3CC(void) {
    return func_80073F88(func_8002B364(0x234), func_8005FC70, D_8005FB5C);
}

u8 *func_8001C404(void) {
    return func_8006E1B4(func_8002B364(0x64), func_8005FC70);
}

u8 *func_8001C434(void) {
    return func_80070240(func_8002B364(0xA90), func_8005FC70, D_8005F908);
}

void func_8001C46C(void) {
    func_8006B070(func_8002B364(0x44), func_8005FC70);
}

u8 *func_8001C49C(void) {
    u8 *self = func_8002B364(0x474);
    return func_80068178(self, func_8005FC70, D_8005FB6C == 0);
}


void func_8001C4D8(void) {
    func_80064474(func_8002B364(0x28));
}

void func_8001C500(void) {
    func_80067764(func_8002B364(0x90), 0);
}

u8 *func_8001C52C(void) {
    return func_8006D684(func_8002B364(0x8C));
}

void func_8001C554(void) {
    func_8006ECC8(func_8002B364(0x58), 2);
}

u8 *func_8001C580(void) {
    return func_8006ECC8(func_8002B364(0x58), 3);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C800", func_8001C5AC);

void func_8001C638(s32 arg0, s32 arg1) {
    func_8001C658(arg1);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C800", func_8001C658);
