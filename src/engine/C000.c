#include "game_heap_wrappers.h"
#include "game_lerp_words.h"
#include "game_audio_api.h"
#include "common.h"
#include "game_resources.h"

extern u8 *func_8002B6D4(u8 *self, s32 flags, const void *vtable);
extern u8 D_80010058[];
extern u8 D_800100E0[];
u32 *func_8001B898(u32 *arg0);
extern s32 func_80039880(s32 id, void *resource);
extern s32 func_8003A07C(s32 id, void *resource);

INCLUDE_ASM("asm/us/main/nonmatchings/C000", func_8001B800);

void func_8001B838(u8 *self, void *resource) {
    if (*(void **)(self + 0xC) == NULL) {
        func_80039880(*(u16 *)(self + 8), resource);
        *(void **)(self + 0xC) = resource;
    } else {
        func_8003A07C(*(u16 *)(self + 8), resource);
        func_8002B2B4(resource);
    }
}

/* Store the pointer twice (at +0x0 and +0x4) and return it; the second store
 * rides the return delay slot. */
u32 *func_8001B898(u32 *arg0) {
    arg0[0] = (u32)arg0;
    arg0[1] = (u32)arg0;
    return arg0;
}

typedef struct CleanupVtable {
    u8 reserved[0x10];
    s16 this_adjustment;
    s16 reserved_12;
    void (*destroy)(void *, s32);
} CleanupVtable;

typedef struct CleanupNode {
    struct CleanupNode *next;
    u8 reserved[0xC];
    u32 keep_alive;
    CleanupVtable *vtable;
} CleanupNode;

void func_8001B8A8(void *head) {
    CleanupNode *node = *(CleanupNode **)head;

    while (head != node) {
        CleanupNode *next = node->next;
        if (node->keep_alive == 0 && node != NULL) {
            CleanupVtable *vtable = node->vtable;
            vtable->destroy((void *)((u32)node + (u32)(s32)vtable->this_adjustment), 3);
        }
        node = next;
    }
}

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *previous;
} ListNode;

ListNode *func_8001B928(ListNode *self, ListNode *node) {
    ListNode *previous;
    node->next = self;
    previous = self->previous;
    node->previous = previous;
    self->previous->next = node;
    self->previous = node;
    return previous;
}

s32 func_8001B94C(ListNode *self) {
    s32 count = 0;
    ListNode *node = self->next;
    while (self != node) {
        node = node->next;
        count++;
    }
    return count;
}

typedef struct N1D5 {
    struct N1D5 *next;
    s32 unk4;
    s32 field8;
} N1D5;

N1D5 *func_8001B974(N1D5 *a0, s32 a1) {
    N1D5 *p = a0->next;

    while (a0 != p) {
        if (p->field8 == a1) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void func_8001B9B4(N1D5 *self, s32 value) {
    N1D5 *node = func_8001B974(self, value);
    if (node != NULL && *(u32 *)((u8 *)node + 0x10) == 0) {
        u8 *vtable = *(u8 **)((u8 *)node + 0x14);
        s16 adjustment = *(s16 *)(vtable + 0x10);
        void (*callback)(void *, s32) = *(void (**)(void *, s32))(vtable + 0x14);
        callback((void *)((u32)node + (u32)(s32)adjustment), 3);
    }
}

u8 *func_8001BA0C(u8 *self) {
    func_8002B6D4(self, 0x1000, D_80010058);
    *(u8 **)(self + 0x1C) = D_800100E0;
    func_8001B898((u32 *)(self + 0x2C));
    func_8001B898((u32 *)(self + 0x34));
    func_8002D584((u32 *)(self + 0x3C), 0x50);
    *(u32 *)(self + 0x54) = 0;
    *(u32 *)(self + 0x5C) = 0;
    return self;
}

INCLUDE_ASM("asm/us/main/nonmatchings/C000", func_8001BA70);

extern void func_800398DC(s32);
void func_8001BCC4(u8 *self);
extern void *func_8002B364(u32 size);
extern N1D5 *func_8001B778(void *storage, s32 index);

N1D5 *func_8001BB48(u8 *self, s32 index) {
    N1D5 *node = NULL;
    if (index < 0) {
        *(u32 *)(self + 0x5C) = 0;
        func_800398DC(0);
        func_8001B9B4((N1D5 *)(self + 0x2C), (s32)(0U - (u32)index));
    } else {
        N1D5 *head = (N1D5 *)(self + 0x2C);
        node = func_8001B974(head, index);
        if (node != NULL) {
            return node;
        }
        if (func_8001B94C((ListNode *)head) >= 16) {
            func_8001BCC4(self);
        }
        node = func_8001B778(func_8002B364(0x18), index);
        func_8001B928((ListNode *)head, (ListNode *)node);
    }
    return node;
}

extern u8 *func_8001B698(u8 *storage, s32 index);
void func_8001BCF8(u8 *self);

N1D5 *func_8001BC0C(u8 *self, s32 index) {
    N1D5 *node = NULL;
    if (index < 0) {
        func_8001B9B4((N1D5 *)(self + 0x34), (s32)(0U - (u32)index));
    } else {
        N1D5 *head = (N1D5 *)(self + 0x34);
        node = func_8001B974(head, index);
        if (node != NULL) {
            return node;
        }
        if (func_8001B94C((ListNode *)head) >= 8) {
            func_8001BCF8(self);
        }
        node = (N1D5 *)func_8001B698(func_8002B364(0x18), index);
        func_8001B928((ListNode *)head, (ListNode *)node);
    }
    return node;
}

extern void func_800398DC(s32);

void func_8001BCC4(u8 *self) {
    *(s32 *)(self + 0x5C) = 0;
    func_800398DC(0);
    func_8001B8A8(self + 0x2C);
}

extern void func_8001B8A8(void *);

void func_8001BCF8(u8 *arg0) {
    func_8001B8A8(arg0 + 0x34);
}

extern void func_8003914C(void);
extern void func_8004D04C(s32 mode, s16 left, s16 right);
extern s32 func_80039CF8(s32 index, u8 left, u8 right);

void func_8001BD18(u8 *self) {
    s16 volume;
    s32 level;
    func_800398DC(*(u32 *)(self + 0x5C) != 0);
    func_8003914C();
    volume = func_8002D5B0((s32 *)(self + 0x3C));
    func_8004D04C(0, volume, volume);
    level = *(s32 *)(self + 0x54);
    if (level > 16) {
        s32 counter = (s32)(*(u32 *)(self + 0x58))++;
        if (counter % 15 == 0) {
            func_80039CF8(*(u16 *)(self + 0x50), (u8)level, (u8)level);
            *(u32 *)(self + 0x54) -= (u32)(level >> 1);
        }
    }
}

extern void func_8001BF40();
extern void func_8001C008();

void func_8001BDDC(void *arg0, u32 arg1, s32 update) {
    if (arg1 & 0x8000) {
        func_8001BF40(arg0, arg1 & 0x7FFF, update);
    } else {
        func_8001C008(arg0, arg1, update);
    }
}

extern s32 func_80034550(s32);

s32 func_8001BE14(void) {
    return func_80034550(-1) == 0;
}

void func_8001BE34(void *arg0, u32 arg1) {
    if (arg1 & 0x8000) {
        func_8001BF40(arg0, -(s32)(arg1 & 0x7FFF), 1);
    } else {
        func_8001C008(arg0, -(s32)arg1, 1);
    }
}


s32 func_8001BE78(s32 arg0, u32 arg1, u8 arg2) {
    if (arg1 & 0x8000) {
        func_80039414(arg1 & 0x7FFF);
        return 0;
    }
    func_80039874(arg2);
    return func_80039AF4(arg1 & 0xFFFF);
}

void func_8001BEC8(s32 *self, s32 value) {
    self[0x50 / 4] = value;
    self[0x54 / 4] = 0x7F;
    self[0x58 / 4] = 0;
}

extern void func_8003A04C(s32);

void func_8001BEDC(s32 id) {
    func_8003A04C(id);
}

extern s32 func_8003A014(s32);

s32 func_8001BEFC(s32 id) {
    return func_8003A014(id) >= 0;
}

extern void func_80039698(void);

void func_8001BF20(void) {
    func_80039698();
}

INCLUDE_ASM("asm/us/main/nonmatchings/C000", func_8001BF40);
