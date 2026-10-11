#include "character_getters.h"
#include "common.h"

extern void func_800313DC(s32 active, s32 index);

INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_80031054);
u8 *func_80031208(u8 *self) {
    u8 *override = *(u8 **)(self + 0x24);
    if (override != NULL) {
        return *(u8 **)(override + 0x14);
    }
    return *(u8 **)(self + 0x10);
}
u8 *func_80031230(u8 *self) {
    u8 *override = *(u8 **)(self + 0x24);
    if (override != NULL) {
        return *(u8 **)(override + 8);
    }
    return *(u8 **)(self + 0x18);
}
typedef struct CharacterLoop {
    u16 loopFrame;
    u16 plays;
} CharacterLoop;

s32 func_80031258(u8 *self, s32 clip) {
    u8 *override = *(u8 **)(self + 0x24);
    if (override != NULL) {
        return (*(CharacterLoop **)(override + 0x1C))[clip].loopFrame;
    }
    return (*(CharacterLoop **)(self + 0x20))[clip].loopFrame;
}

s32 func_80031298(u8 *self, s32 clip) {
    u8 *override = *(u8 **)(self + 0x24);
    if (override != NULL) {
        return (*(CharacterLoop **)(override + 0x1C))[clip].plays;
    }
    return (*(CharacterLoop **)(self + 0x20))[clip].plays;
}
extern s32 func_80022018(void *data);

s32 func_800312D8(u8 *self) {
    return func_80022018(func_80031208(self));
}
INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_80031300);
INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_80031308);
INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_80031310);
INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_800313DC);

void func_80031434(void) {
    func_800313DC(1, 0xFFFF);
}

void func_80031458(void) {
    func_800313DC(0, 0xFFFF);
}

INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_8003147C);
INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_800314C4);

INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_800315DC);

INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_800318AC);

void func_80031A18(u8 *object, s32 value) {
    u32 flagsAddress = (u32)*(s16 **)(*(u8 **)object + 0x108);
    s32 count = *(s16 *)flagsAddress;
    flagsAddress += 2u;
    flagsAddress += (u32)count * 2u;
    if (count > 0) {
        s16 *flags = (s16 *)flagsAddress;
        u8 *slots = object + 8;
        do {
            if (*flags < 0) {
                u8 *item = *(u8 **)slots;
                *(u32 *)(item + 8) = 0;
                *(s32 *)(item + 0x4C) = value;
            }
            slots += 4;
            count--;
            flags++;
        } while (count != 0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_80031A78);

INCLUDE_ASM("asm/us/main/nonmatchings/21800", func_80031AE8);

u32 func_80031B40(u8 *object) {
    return *(u32 *)(object + 4);
}
