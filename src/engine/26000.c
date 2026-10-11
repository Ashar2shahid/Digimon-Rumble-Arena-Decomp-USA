#include "common.h"
#include "game_vfs.h"
extern s32 D_80116650[];
extern s32 D_8011665C;
extern s32 func_8003F4EC(s32 arg0);
extern void func_80046D9C(void (*arg0)(void));
extern void func_80035238(void);
extern void func_80035CB8(u16 arg0);



extern s32 func_8004690C(void *buffer, s32 sectorWords);

void func_80035878(s32 arg0) {
    s32 result;
    if ((arg0 & 0xFF) == 2) {
        func_8004690C(&result, 1);
        D_80116668.flags |= 2;
    }
}

extern s32 func_80046C4C(s32 *arg0);
extern void func_80043974(u8 arg0, void *arg1, s32 arg2, void (*arg3)(s32), s32 arg4);
void func_80035924(s32 arg0);

void func_800358BC(void) {
    D_80116668.flags |= 4;
    D_80116650[4] = func_80046C4C(D_80116650);
    func_80043974(*(u8 *)((u8 *)D_80116650[2] + 0xC), D_80116650, 0x1B, func_80035924, -1);
}

void func_80035924(s32 arg0) {
    s32 state = arg0 & 0xFF;
    D_8011665C = func_8003F4EC(-1);
    if (state == 2) {
        D_80116668.flags &= ~0x14;
        D_80116668.flags |= 8;
        func_80046D9C(func_80035238);
        func_80035CB8(0x80);
    }
}

void func_80035994(s32 arg0) {
    if ((arg0 & 0xFF) == 2) {
        func_80046D9C(func_80035238);
        D_8011665C = func_8003F4EC(-1);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/26000", func_800359D4);

s32 func_80035A7C(void) {
    s32 v1;
    s32 v0 = func_8003F4EC(-1);
    s32 *p = D_80116650;
    s32 a0 = v0 - p[3];
    int new_var;

    if (a0 < 0) {
        a0 = 0;
    }
    if ((*(u8 *)(p[2] + 0xC)) & 0x80) {
        a0 = a0 << 1;
        new_var = 2;
        v1 = a0 << new_var;
    }
    v1 = a0 << 2;
    v1 = v1 + a0;
    a0 = (v1 << 4) - v1;
    return func_80046B3C(p[4] + (a0 / p[5]), p);
}

s32 func_80035B18(void) {
    return ((D_80116668.flags >> 1) ^ 1) & 1;
}

s32 func_80035B34(void) {
    if (D_80116668.flags & 0x10) {
        return 0;
    }
    return (D_80116668.flags & 0x100C) != 0;
}

void func_80035B8C(u32 opaqueIncomingWord);

VfsNotificationFn func_80035B68(VfsNotificationFn arg0) {
    VfsNotificationFn old = D_80116668.event;
    if (arg0 == NULL) {
        arg0 = func_80035B8C;
    }
    D_80116668.event = arg0;
    return old;
}

void func_80035B8C(u32 opaqueIncomingWord) {
}

INCLUDE_ASM("asm/us/main/nonmatchings/26000", func_80035B94);

INCLUDE_ASM("asm/us/main/nonmatchings/26000", func_80035C10);

INCLUDE_ASM("asm/us/main/nonmatchings/26000", func_80035C68);

INCLUDE_ASM("asm/us/main/nonmatchings/26000", func_80035CB8);

u16 func_80035D28(s32 arg0) {
    u16 old;
    arg0 &= 0xFFFF;
    old = D_80116668.previous;
    D_80116668.previous = arg0 - 1;
    return old;
}

void func_80035D44(void) {
    if (D_80116668.flags & 1) {
        while (!(D_80116668.flags & 2)) {
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/26000", func_80035D78);

void func_80035E9C(void *arg0, s32 arg1) {
    D_80116668.pointer = arg0;
    D_80116668.mode = arg1;
}

extern void func_80035F10(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);

u8 *func_80035EB0(u8 *arg0, u8 *arg1) {
    func_80035F10(arg0, arg1, 1, 0x20);
    return arg0;
}

u8 *func_80035EE0(u8 *arg0, u8 *arg1) {
    func_80035F10(arg0, arg1, 2, -0x20);
    return arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/26000", func_80035F10);

#define IS_SJIS_LEAD(c) ((u8)(((c) ^ 0x20) - 0xA1) < 0x3C)
extern const u8 D_80019548[];
u8 *func_80035F94(u8 *dst, u8 *src) {
    u8 *out = dst;
    u8 c;

    while (*src != '\0') {
        c = *src++;
        if (IS_SJIS_LEAD(c)) {
            *out++ = c;
            *out = *src++;
        } else if (c < ' ') {
            *out = c;
        } else {
            /* the table has the characters 0x20-0x7F, then 0xA0-0xDF */
            if (c >= 0xE0) {
                c = 0;
            } else {
                c = (c >= 0xA0) ? c - 0x40 : c - 0x20;
            }
            c *= 2;
            *out++ = D_80019548[c];
            *out = D_80019548[c + 1];
        }
        out++;
    }
    *out = '\0';
    return dst;
}


__asm__(".globl func_80036000\n.set func_80036000, func_80035F94 + 0x6c\n.size func_80036000, 0");
