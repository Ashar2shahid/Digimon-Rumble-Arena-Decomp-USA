#include "common.h"
#include "game_vfs.h"
#include "game_cd_read_state.h"

INCLUDE_ASM("asm/us/main/nonmatchings/24800", func_80034010);

INCLUDE_ASM("asm/us/main/nonmatchings/24800", func_800340A0);

INCLUDE_ASM("asm/us/main/nonmatchings/24800", func_80034158);

INCLUDE_ASM("asm/us/main/nonmatchings/24800", func_800341F8);

INCLUDE_ASM("asm/us/main/nonmatchings/24800", func_80034330);

INCLUDE_ASM("asm/us/main/nonmatchings/24800", func_80034464);

INCLUDE_ASM("asm/us/main/nonmatchings/24800", func_80034550);

extern void func_800349A8(void);
void func_8003463C(void) {
    D_80114B80.flags |= 4;
    func_800349A8();
}

extern s32 func_80034550(s32);
void func_8003466C(void) {
    D_80114B80.flags &= ~4u;
    func_80034550(0);
}

extern void func_80034F80(void);
void func_800346A4(void) {
    if (D_80114B80.flags & 0x40000000u) {
        func_80034F80();
    }
    if (D_80114B80.flags & 1u) {
        D_80114B80.flags &= ~1u;
        D_80116620.finish();
    }
}

extern void func_80034FE8(u32 completionWord);
void func_8003470C(VfsNotificationFn callback, void *user) {
    if (callback == 0) {
        callback = func_80034FE8;
    }
    D_80114B80.completion = callback;
    D_80114B80.completionUser = user;
}

extern char *func_80036118(char *out, const char *in);
extern char *func_8003E15C(char *out, const char *in);
extern char *func_8003E03C(char *out, const char *in);
extern char D_801155D4[];
void func_80034730(char *out, const char *path) {
    char normalized[0x60];
    func_80036118(normalized, path);
    if (normalized[0] == '/') {
        func_8003E15C(out, normalized);
    } else {
        func_8003E15C(out, D_801155D4);
        func_8003E03C(out, normalized);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/24800", func_80034790);
