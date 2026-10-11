#include "common.h"
#include "game_md5.h"
#include "game_save_config.h"

typedef struct {
    s32 fields[6];
} E800Record;

typedef union {
    E800Record records[4];
    s32 words[24];
} E800SlotStorage;

typedef struct {
    u8 reserved_000[0x2D0];
    s32 selected;
    u8 reserved_2D4[0x50];
    E800SlotStorage slots;
} E800State;

INCLUDE_ASM("asm/us/main/nonmatchings/E800", func_8001E000);

INCLUDE_ASM("asm/us/main/nonmatchings/E800", func_8001E0B4);

extern void func_8001E184(u8 *self, s32 slotIndex);
INCLUDE_ASM("asm/us/main/nonmatchings/E800", func_8001E184);

void func_8001E20C(E800State *self, s32 value) {
    s32 i = 0;
    s32 *state = &self->slots.words[4];
    while (i < 2) {
        if (state[-3] != 0) {
            state[-4] = value;
            state[0] = 0;
            func_8001E184((u8 *)self, i);
            break;
        }
        state += 6;
        i++;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/E800", func_8001E264);

s32 func_8001E380(E800State *self) {
    if (self->slots.records[0].fields[1] != 0) {
        if (self->slots.records[1].fields[1] != 0) {
            return -1;
        }
    }
    return self->slots.records[0].fields[1] != 0;
}

s32 func_8001E3B4(E800State *self) {
    s32 index = self->selected;
    if (index < 0) {
        return 0;
    }
    return self->slots.records[index].fields[1] ^ 1;
}

s32 func_8001E3E4(E800State *self) {
    s32 index = func_8001E380(self);
    if (index < 0) {
        return 0;
    }
    return self->slots.records[index].fields[4];
}

void func_8001E42C(s32 *self) {
    s32 flags = self[0];
    flags &= ~1;
    flags &= ~2;
    flags &= ~4;
    flags &= ~8;
    flags &= ~0x10;
    flags &= ~0x20;
    self[0] = flags;
}

void func_8001E468(s32 *self) {
    func_8001E42C(self);
    self[0] |= 0x20;
}

INCLUDE_ASM("asm/us/main/nonmatchings/E800", func_8001E498);

s32 func_8001E688(u8 *self) {
    u8 buffer[0x10];
    func_8001E6E4(self, buffer);
    return func_8003DF1C(buffer, self + 0x23C, 0x10) == 0;
}

void func_8001E6C4(s32 *self) {
    func_8001E6E4(self, (u8 *)self + 0x23C);
}

void func_8001E6E4(u8 *self, void *output) {
    Md5Context context;
    func_800383B4(&context);
    func_80038418(&context, self, 0x23C);
    func_80037250(&context, output);
}

INCLUDE_ASM("asm/us/main/nonmatchings/E800", func_8001E734);

void func_8001E7A4(SaveConfig *self) {
    s32 i;
    for (i = 0; i < 6; i++) {
        u16 index = D_8001035C[i].defaultIndex;
        self->buttons[0][i] = index;
        self->buttons[1][i] = index;
    }
    self->buttonConfig = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/E800", func_8001E7DC);
