#include "game_stepper_child_api.h"
#include "common.h"
#include "game_stepper_state.h"
#include "object_base.h"
#include "deferred_objects.h"
#pragma interface

class DtorObject {
public:
    DtorLink link;
    int f8;
    int fC;
    int f10;
    /* Retail's deleting-destructor entry follows two virtual slots. */
    virtual void vfunc0(s32 arg);
    virtual void vfunc1();
    virtual ~DtorObject();
};

extern "C" {

INCLUDE_ASM("asm/us/main/nonmatchings/1C800", func_8002C000);

INCLUDE_ASM("asm/us/main/nonmatchings/1C800", func_8002C010);

INCLUDE_ASM("asm/us/main/nonmatchings/1C800", func_8002C19C);

INCLUDE_ASM("asm/us/main/nonmatchings/1C800", func_8002C1CC);

DtorList *func_8002C210(DtorList *arg0, DtorNode *arg1) {
    DtorLink *head = arg0->second.prev;
    arg1->link.prev = head;
    arg1->link.next = head->next;
    head->next->prev = &arg1->link;
    head->next = &arg1->link;
    arg1->owner = arg0;
    return arg0;
}

void func_8002C244(DtorList *a0) {
    DtorLink *head = &a0->first;
    DtorLink *node = head->next;
    while (node != head) {
        DtorLink *next = node->next;
        delete reinterpret_cast<DtorObject *>(node);
        node = next;
    }

    head = &a0->second;
    node = head->next;
    while (node != head) {
        DtorLink *next = node->next;
        delete reinterpret_cast<DtorObject *>(node);
        node = next;
    }
}

typedef struct N306 {
    struct N306 *next;
    struct N306 *unk4;
    struct N306 *head8;
} N306;

s32 func_8002C2FC(N306 *a0) {
    s32 n = 0;
    N306 *p = a0;
    N306 *q = a0->next;

    while (q != a0) {
        q = q->next;
        n++;
    }
    p = (N306 *)&a0->head8;
    q = a0->head8;
    while (q != p) {
        q = q->next;
        n++;
    }
    return n;
}

void func_8002C348(void) {
}

void func_8002C350(void) {
}

extern DtorList *func_8002C210(DtorList *arg0, DtorNode *arg1);

void func_8002C358(DtorList *arg0, DtorNode *arg1) {
    func_8002C210(arg0, arg1);
}

void *func_8002C378(void **arg0, void *arg1) {
    *arg0 = arg1;
    return arg0;
}

void *func_8002C384(void **arg0, void *arg1) {
    *arg0 = arg1;
    return arg0;
}

s32 func_8002C390(s32 *arg0) {
    return arg0[0];
}

s32 func_8002C39C(s32 *state) {
    s32 reached_zero = 0;
    if (*state > 0) {
        reached_zero = --*state == 0;
    }
    return reached_zero;
}

s32 func_8002C3C0(const s32 *state) {
    return *state <= 0;
}


extern char D_800192A8[];

Func8002C3CCNode *func_8002C3CC(Func8002C3CCNode *arg0, s32 arg1) {
    arg0->next = arg0;
    arg0->prev = arg0;
    arg0->f1C = D_800192A8;
    arg0->f10 = arg1;
    arg0->f14 = 0;
    arg0->f18 = 0;
    arg0->f8 = 0;
    return arg0;
}

extern void func_8002C448(void *arg0);

void func_8002C3F8(void *arg0) {
    func_8002C448(arg0);
}

/* Use unsigned updates so the counter's 32-bit wrap is defined in C. */
typedef struct Func8002C418State {
    u8 pad[0x10];
    u32 current;
    s32 lower;
    s32 upper;
} Func8002C418State;

s32 func_8002C418(Func8002C418State *arg0) {
    u32 next = arg0->current + 1;
    arg0->current = next;
    if ((s32)next > arg0->upper) {
        arg0->current = (u32)arg0->upper;
        return -1;
    }
    return 0;
}

void func_8002C448(void *arg0Raw) {
    Func8002C418State *arg0 = (Func8002C418State *)arg0Raw;
    u32 next = arg0->current + 1;
    arg0->current = next;
    if ((s32)next > arg0->upper) {
        arg0->current = (u32)arg0->lower;
    }
}

extern void func_8002C4C4(void *arg0);

void func_8002C474(void *arg0) {
    func_8002C4C4(arg0);
}

s32 func_8002C494(Func8002C418State *arg0) {
    u32 next = arg0->current - 1;
    arg0->current = next;
    if ((s32)next < arg0->lower) {
        arg0->current = (u32)arg0->lower;
        return -1;
    }
    return 0;
}

void func_8002C4C4(void *arg0Raw) {
    Func8002C418State *arg0 = (Func8002C418State *)arg0Raw;
    u32 next = arg0->current - 1;
    arg0->current = next;
    if ((s32)next < arg0->lower) {
        arg0->current = (u32)arg0->upper;
    }
}

s32 func_8002C4F4(s32 *arg0) {
    return arg0[2];
}

void func_8002C500(void *child, s32 clear) {
    u32 groupAddress = *(u32 *)((u8 *)child + 8);
    DispatchState *group = (DispatchState *)groupAddress;
    if (group != 0) {
        group->flags.currentOnly = !clear;
    }
}

void func_8002C530(void **arg0, s32 arg1) {
    ((DispatchState *)arg0[2])->flags.closed = 1;
    ((DispatchState *)arg0[2])->closeValue = arg1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1C800", func_8002C554);

INCLUDE_ASM("asm/us/main/nonmatchings/1C800", func_8002C6B0);
}
