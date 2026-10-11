#include "common.h"
#include "game_resources.h"

extern void func_80038848(void *, void *);
extern u8 *D_801166B8;
extern void func_8004D014(s16, s16);

INCLUDE_ASM("asm/us/main/nonmatchings/29800", func_80039000);

extern void func_8004D614(s16, s16, s32, s32);

void func_80039020(void) {
    u8 *node = D_801166B8;
    while (node != 0) {
        u8 *next = *(u8 **)node;
        s16 fade = *(s16 *)(node + 0x12);
        u16 step = *(u16 *)(node + 0x12);
        if (fade != 0) {
            s32 level = *(u16 *)(node + 0x10) - step;
            *(s16 *)(node + 0x10) = level;
            level = (s16)level;
            if (level <= 0) {
                *(s16 *)(node + 0x10) = 0;
                *(s16 *)(node + 0x12) = 0;
            } else if (level >= 0x1000) {
                *(s16 *)(node + 0x10) = 0x1000;
                *(s16 *)(node + 0x12) = 0;
            }
            {
                s32 a = (*(u8 *)(node + 0xE) * *(s16 *)(node + 0x10)) >> 12;
                s32 b = (*(u8 *)(node + 0xF) * *(s16 *)(node + 0x10)) >> 12;
                u8 *resource = (u8 *)&D_80116690;
                u8 *entry = *(u8 **)(resource + 0x14) + (*(u16 *)(node + 0xC) * 8);
                u8 *parent = *(u8 **)(resource + 0xC) + (*(u16 *)entry * 8);
                if ((a | b) == 0) {
                    func_8004D014(*(s16 *)(parent + 6), *(s16 *)(entry + 2));
                    func_80038848(resource + 0x28, node);
                    *(u8 **)node = *(u8 **)(resource + 0x24);
                    *(u8 **)(resource + 0x24) = node;
                } else {
                    func_8004D614(*(s16 *)(parent + 6), *(s16 *)(entry + 2), a, b);
                }
            }
        }
        node = next;
    }
}

extern void func_80038E7C(void);
extern void func_80039020(void);
extern s32 func_8003F4EC(s32);
extern void func_8004EE9C(s16, s16);

void func_8003914C(void) {
    u8 *resource;
    func_80038E7C();
    func_80039020();
    resource = (u8 *)&D_80116690;
    if (*(s16 *)(resource + 0x354) != 0) {
        if ((u16)(func_8003F4EC(-1) - *(u16 *)(resource + 0x356)) >= *(s16 *)(resource + 0x354)) {
            s16 a = *(s16 *)(resource + 0x350);
            s16 b = *(s16 *)(resource + 0x352);
            *(s16 *)(resource + 0x354) = 0;
            func_8004EE9C(a, b);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/29800", func_800391C0);


INCLUDE_ASM("asm/us/main/nonmatchings/29800", func_8003926C);

void func_80039354(s16 value) {
    u8 *node = D_801166B8;
    while (node != 0) {
        *(s16 *)(node + 0x12) = value;
        node = *(u8 **)node;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/29800", func_80039384);

extern void func_8003946C(u16, u8, u8);

void func_80039414(u16 index) {
    u8 *resource = (u8 *)&D_80116690;
    if (index < *(u16 *)(resource + 0x1E)) {
        u8 *table = *(u8 **)(resource + 0x14);
        if (table != 0) {
            u8 *entry = table + index * 8;
            func_8003946C(index, entry[6], entry[7]);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/29800", func_8003946C);

INCLUDE_ASM("asm/us/main/nonmatchings/29800", func_800394CC);

INCLUDE_ASM("asm/us/main/nonmatchings/29800", func_8003955C);


extern s32 func_8004943C(s16, s16);

void func_800395EC(void) {
    u8 *node = D_801166B8;
    while (node != 0) {
        u8 *next = *(u8 **)node;
        if ((*(u32 *)(node + 8) & 1) == 0) {
            u8 *resource = (u8 *)&D_80116690;
            u8 *entry = *(u8 **)(resource + 0x14) + (*(u16 *)(node + 0xC) * 8);
            u8 *parent = *(u8 **)(resource + 0xC) + (*(u16 *)entry * 8);
            if (func_8004943C(*(s16 *)(parent + 6), *(s16 *)(entry + 2)) == 0) {
                func_80038848(resource + 0x28, node);
                *(u8 **)node = *(u8 **)(resource + 0x24);
                *(u8 **)(resource + 0x24) = node;
            }
        }
        node = next;
    }
}

extern void func_800396D8(u8 *);

void func_80039698(void) {
    u8 *node = D_801166B8;
    while (node != 0) {
        u8 *next = *(u8 **)node;
        func_800396D8(node);
        node = next;
    }
}

void func_800396D8(u8 *node) {
    u8 *resource = (u8 *)&D_80116690;
    u8 *entry = *(u8 **)(resource + 0x14) + (*(u16 *)(node + 0xC) * 8);
    u8 *parent = *(u8 **)(resource + 0xC) + (*(u16 *)entry * 8);
    func_8004D014(*(s16 *)(parent + 6), *(s16 *)(entry + 2));
    func_80038848(resource + 0x28, node);
    *(u8 **)node = *(u8 **)(resource + 0x24);
    *(u8 **)(resource + 0x24) = node;
}

INCLUDE_ASM("asm/us/main/nonmatchings/29800", func_80039750);
