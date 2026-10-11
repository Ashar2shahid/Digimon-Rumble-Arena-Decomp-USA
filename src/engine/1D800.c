#include "common.h"
#include "game_stepper_state.h"
#include "game_lerp_words.h"

#pragma interface
struct ItemLink {
    ItemLink *next;
    ItemLink *prev;
};

class Item {
public:
    ItemLink link;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    virtual void method0();
    virtual void method1();
    virtual void method2();
    virtual void method3();
    virtual void method4();
    virtual void method5();
    virtual void method6();
    virtual void method7();
    virtual void method8(s32);
    virtual ~Item();
};
struct ItemList {
    s32 f0;
    ItemLink sentinel;
    s32 fC;
    s32 f10;
    Item *current;
};

class Resource {
public:
    void *resource;
    ~Resource();
};

extern "C" void func_8002B3F8(void *);


__asm__(
    ".globl func_8002D308\n"
    ".set func_8002D308, _._4Item\n"
    ".globl func_8002D518\n"
    ".set func_8002D518, _._8Resource\n"
    ".set _vt.4Item, D_800192A8\n"
    ".set __builtin_delete, func_8002B3D0"
);


extern "C" {

void func_8002D64C(u32 *arg0, u32 arg1, u32 arg2);


void func_8002D0A0(ItemList *a0, s32 a1) {
    ItemLink *sentinel = &a0->sentinel;
    ItemLink *node;
    for (node = sentinel->next; node != sentinel; node = node->next) {
        ((Item *)node)->method8(a1);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1D800", func_8002D108);

u32 func_8002D1CC(ItemList *list) {
    ItemLink *sentinel = &list->sentinel;
    ItemLink *node;
    u32 count = 0;
    for (node = sentinel->next; node != sentinel; node = node->next) {
        count++;
    }
    return count;
}

void func_8002D1F4(ItemList *list) {
    ItemLink *sentinel = &list->sentinel;
    ItemLink *node = sentinel->next;
    u32 count = 0;
    while (node != sentinel) {
        ((s32 *)node)[3] = count;
        node = node->next;
        count++;
    }
}

ItemLink *func_8002D220(ItemList *list, u32 index) {
    ItemLink *sentinel = &list->sentinel;
    ItemLink *node;
    for (node = sentinel->next; node != sentinel; node = node->next) {
        if (index-- == 0) {
            return node;
        }
    }
    return 0;
}

void func_8002D258(s32 *arg0, s32 arg1) {
    arg0[6] = arg1;
}

void func_8002D260(DispatchState *state, s32 keepOpen) {
    state->flags.keepOpen = keepOpen == 1;
}

s32 func_8002D284(DispatchState *state) {
    return state->flags.childActive;
}

s32 func_8002D298(DispatchState *state) {
    return stepperClosed(state) && !stepperKeptOpen(state);
}

s32 func_8002D2C4(s32 *arg0) {
    return arg0[7];
}

s32 func_8002D2D0(void) {
    return -1;
}

s32 func_8002D2D8(void) {
    return 0;
}

void func_8002D2E0(void) {
}

void func_8002D2E8(void) {
}

s32 func_8002D2F0(void) {
    return 1;
}

void func_8002D2F8(void) {
}

void func_8002D300(void) {
}
}
Item::~Item() {
    link.next->prev = link.prev;
    link.prev->next = link.next;
    link.next = &link;
    link.prev = &link;
}
extern "C" {


s32 func_8002D360(s32 *arg0) {
    return arg0[4];
}

void func_8002D36C(s32 *arg0, s32 arg1) {
    arg0[4] = arg1;
}

void func_8002D374(s32 *arg0, s32 arg1) {
    arg0[5] = arg1;
}

void func_8002D37C(s32 *arg0, s32 arg1) {
    arg0[6] = arg1;
}

s32 func_8002D384(s32 *arg0) {
    return arg0[3];
}

void func_8002D390(void) {
}

void func_8002D398(void) {
}

extern ItemList *func_8002C93C(ItemList *list, ItemLink *node);

void func_8002D3A0(ItemList *list, ItemLink *node) {
    func_8002C93C(list, node);
}

extern void func_8002D108(ItemList *list, Item *item);

void func_8002D3C0(ItemList *list, Item *item) {
    func_8002D108(list, item);
}

void func_8002D3E0(DispatchState *state, s32 arg1) {
    state->flags.wraps = arg1 == 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1D800", func_8002D400);
}
Resource::~Resource() {
    if (resource != 0) {
        func_8002B3F8(resource);
    }
}
extern "C" {


u8 func_8002D56C(u8 **arg0, u32 arg1) {
    return arg0[0][arg1];
}

u32 *func_8002D584(u32 *arg0, u32 arg1) {
    func_8002D64C(arg0, arg1, 0);
    return arg0;
}

s32 func_8002D5B0(s32 *a0) {
    s32 s0 = a0[2];
    s32 v1;
    s32 a1;

    if (func_8002D678(a0) == 0) {
        v1 = (a0[1] = (s32)((u32)a0[1] + 1u));
        a1 = (s32)((u32)v1 << 12) / (s32)((u32)a0[0] + 1u);
        do {
            s0 = (s32)((u32)((s64)a0[4] * a1) +
                      (u32)((s64)a0[3] * (s32)(0x1000u - (u32)a1))) >> 12;
        } while (0);
        a0[2] = s0;
    }
    return s0;
}

void func_8002D64C(u32 *arg0, u32 arg1, u32 arg2) {
    arg0[0] = arg2;
    arg0[1] = 0;
    if (arg2 == 0) {
        arg0[2] = arg1;
        arg0[3] = arg1;
        arg0[4] = arg1;
    } else {
        arg0[3] = arg0[2];
        arg0[4] = arg1;
    }
}

s32 func_8002D678(const s32 *state) {
    return state[1] > state[0];
}

s32 func_8002D688(s32 *arg0) {
    return arg0[2];
}

u8 *func_8002D694(u8 *arg0) {
    *(u32 *)(arg0 + 8) = 0;
    *(u16 *)(arg0 + 0x12) = 0;
    *(u16 *)(arg0 + 0x14) = 0;
    *(u32 *)(arg0 + 0xC) = 0x808080;
    arg0[0x11] = 0;
    return arg0;
}

extern void func_8002D6FC(void *self, void *image, s32 mode);

void *func_8002D6B8(void *self, void *image, s32 mode) {
    u8 *bytes = (u8 *)self;
    *(u16 *)(bytes + 0x12) = 0;
    *(u16 *)(bytes + 0x14) = 0;
    ((u32 *)self)[3] = 0x808080;
    bytes[0x11] = 0;
    ((u32 *)self)[2] = 0;
    func_8002D6FC(self, image, mode);
    return self;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1D800", func_8002D6FC);
}
