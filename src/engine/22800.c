#include "common.h"
#include "game_printer_storage.h"
#include "game_key_lookup.h"
#include "iterator_object.h"
#include "game_font_cache.h"

INCLUDE_ASM("asm/us/main/nonmatchings/22800", func_80032038);

extern void func_8002E024(void *arg0);
extern void func_8002B3D0(void *arg0);

s32 *func_80032194(s32 *arg0, s32 arg1) {
    void *node = func_80031FA0();
    *arg0 = arg1;
    *(s32 *)((u8 *)node + 0x18) = (s32)arg0;
    return arg0;
}

void func_800321D0(void *arg0, s32 arg1) {
    void *node = func_80031FA0();
    *(s32 *)((u8 *)node + 0x18) = 0;
    func_8002E024(node);
    if (arg1 & 1) {
        func_8002B3D0(arg0);
    }
}



u16 *func_80032220(u16 **arg0, s32 arg1) {
    u16 *table = *arg0;
    u16 count = table[0];
    s32 offset = (count << 1) + 2;
    u8 *records = (u8 *)table + offset;
    s32 index = func_800326E8(table + 1, count, arg1 & 0xFFFF);

    if (index < 0) {
        return NULL;
    }
    return (u16 *)(records + index * 30);
}

INCLUDE_ASM("asm/us/main/nonmatchings/22800", func_80032284);

void func_80032304(void *arg0, u32 arg1) {
    *(s32 *)((u8 *)arg0 + 0x14) = arg1 & 0xFFFFFF;
}

void func_80032318(void *arg0, s32 arg1) {
    s32 *field = (s32 *)((u8 *)arg0 + 0x24);
    *field = (*field & ~1) | (arg1 & 1);
}

void func_80032334(void *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0x18) = arg1 & 0xFFFFFF;
}

INCLUDE_ASM("asm/us/main/nonmatchings/22800", func_80032348);

INCLUDE_ASM("asm/us/main/nonmatchings/22800", func_800323E4);

INCLUDE_ASM("asm/us/main/nonmatchings/22800", func_800324E0);

void func_800325EC(void *arg0, s32 arg1, s32 arg2) {
    *(s32 *)((u8 *)arg0 + 0x1C) = arg1;
    *(s32 *)((u8 *)arg0 + 0x20) = arg2;
    *(s32 *)arg0 = arg1;
    *(s32 *)((u8 *)arg0 + 4) = arg2;
}

extern void func_8002E074(void);

void func_80032600(void) {
    func_8002E074();
}

void func_80032620(u8 *self, s32 flags) {
    func_8003277C(self, flags);
}

INCLUDE_ASM("asm/us/main/nonmatchings/22800", func_80032640);

INCLUDE_ASM("asm/us/main/nonmatchings/22800", func_800326E8);

void func_8003277C(u8 *self, s32 flags) {
    ((PrinterPrefix *)self)->table = &D_800193DC;
    if (flags & 1) {
        func_8002B3D0(self);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/22800", func_800327B0);
