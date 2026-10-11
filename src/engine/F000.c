#include "game_thread.h"
#include "common.h"
#include "game_lerp_words.h"
#include "game_save_config.h"
#include "game_loading_screen.h"

INCLUDE_ASM("asm/us/main/nonmatchings/F000", func_8001E800);

u16 func_8001E900(u16 *arg0, u32 arg1, u32 arg2) {
    u32 offset = arg2 << 1;
    u32 row = arg1 << 1;
    row += arg1;
    row <<= 2;
    offset += row;
    return *(u16 *)((u8 *)arg0 + offset + 0x24);
}

void func_8001E924(SaveConfig *self, s32 player, s32 slot, s32 index) {
    u16 old = self->buttons[player][slot];
    s32 i;
    self->buttons[player][slot] = (u16)index;
    for (i = 0; i < 6; i++) {
        if (i == slot) continue;
        if (self->buttons[player][i] == index) {
            self->buttons[player][i] = old;
            break;
        }
    }
}

u16 *func_8001E98C(u16 *arg0) {
    func_8001E9B4(arg0);
    return arg0;
}

void func_8001E9B4(u16 *arg0) {
    s32 i;
    for (i = 0; i < 16; i++) {
        arg0[i] = (u16)(1u << i);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/F000", func_8001E9DC);

u16 func_8001EA30(u16 *arg0, u32 arg1) {
    u32 result = 0;
    u32 mask = arg1 & 0xFFFF;
    while (mask != 0) {
        if (mask & 1) {
            result |= *arg0;
        }
        mask >>= 1;
        arg0++;
    }
    return (u16)result;
}

INCLUDE_ASM("asm/us/main/nonmatchings/F000", func_8001EA68);

extern void func_8001EAF4(void *arg0, s32 arg1, s32 arg2);

void func_8001EAB4(void *arg0, s32 arg1) {
    func_8001EAF4(arg0, arg1, 0xFF);
}

void func_8001EAD4(void *arg0, s32 arg1) {
    func_8001EAF4(arg0, arg1, 0);
}


void func_8001EAF4(void *arg0, s32 arg1, s32 arg2) {
    func_8002D64C((u32 *)((GameFadeControl *)arg0)->level, (u32)arg2, (u32)arg1);
}



s32 func_8001EB20(void *arg0) {
    return func_8002D678(((const GameFadeControl *)arg0)->level);
}

INCLUDE_ASM("asm/us/main/nonmatchings/F000", func_8001EB40);

extern void func_8002B770(void *arg0);

void func_8001EBE8(void *arg0) {
    func_8002B770(arg0);
}

GameLoadingScreen *func_8001EC08(GameLoadingScreen *self) {
    self->vtable = &D_800103D0;
    self->first = 1;
    return self;
}

void func_8001EC24(GameLoadingScreen *self) {
    if (self->first) {
        self->first = 0;
        self->vtable->load.call((u8 *)self + self->vtable->load.delta);
    }
    self->vtable->draw.call((u8 *)self + self->vtable->draw.delta);
}

extern void func_8001ECB0(void *arg0, void *arg1);
extern char D_800103B8[];

void func_8001EC8C(u8 *arg0) {
    func_8001ECB0(arg0, D_800103B8);
}

INCLUDE_ASM("asm/us/main/nonmatchings/F000", func_8001ECB0);

INCLUDE_ASM("asm/us/main/nonmatchings/F000", func_8001ED7C);

INCLUDE_ASM("asm/us/main/nonmatchings/F000", func_8001EEF4);

extern s32 func_8004033C(void);
extern s32 func_800402EC(u32 thread);
extern void func_8004034C(void);
extern void func_8002B3F8(void *address);
extern void func_8002B3D0(void *address);

void func_8001EFB0(GameThread *self, u32 flags) {
    func_8004033C();
    func_800402EC(self->id);
    func_8004034C();
    if (self->stack != NULL) {
        func_8002B3F8(self->stack);
    }
    if (flags & 1U) {
        func_8002B3D0(self);
    }
}
