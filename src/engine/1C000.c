#include "game_renew_handle_api.h"
#include "game_placement_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_heap.h"
#include "game_handles.h"
#include "deferred_objects.h"

typedef struct {
    u32 padding0[4];
    u32 count;
    u32 padding14;
    void *field18;
} ManagerEntry;

extern "C" {
extern HandlePool *D_80114768;
extern Heap D_80114770;
extern void func_8002B950(void *);
}


extern "C" {

INCLUDE_ASM("asm/us/main/nonmatchings/1C000", func_8002B800);

s32 func_8002B824(void) {
    return 0;
}

void func_8002B82C(s32 *arg0) {
    arg0[6] = 1;
}

void func_8002B838(s32 arg0) {
    void *object = func_80036F34(D_8005FE04, arg0);

    if (object != NULL) {
        func_8002B82C((s32 *)object);
    }
}

s32 *func_8002B874(u32 *arg0) {
    arg0[0] = (u32)arg0;
    arg0[1] = (u32)arg0;
    arg0[2] = (u32)(arg0 + 2);
    arg0[3] = (u32)(arg0 + 2);
    arg0[4] = 0;
    arg0[5] = 0;
    arg0[6] = (u32)arg0;
    return (s32 *)arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1C000", func_8002B89C);

void func_8002B924(void *arg0) {
    func_8002B950(arg0);
    func_8002B950((u8 *)arg0 + 8);
}

struct DestroyMeta {
    u32 first;
    u32 second;
    s16 adjustment;
    u16 padding;
    void (*destroy)(void *, s32);
};
struct ManagedNode {
    ManagedNode *next;
    u8 unused4[0x18];
    DestroyMeta *meta;
};

void func_8002B950(void *root) {
    ManagedNode *head = (ManagedNode *)root;
    ManagedNode *node = head->next;
    while (node != head) {
        ManagedNode *next = node->next;
        if (node != NULL) {
            DestroyMeta *meta = node->meta;
            void *object = (void *)((u32)node + (u32)(s32)meta->adjustment);
            meta->destroy(object, 3);
        }
        node = next;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1C000", func_8002B9C4);

void func_8002BB00(ManagerEntry *arg0, void *arg1) {
    if (arg1 == arg0->field18) {
        arg0->field18 = *(void **)arg1;
    }
    arg0->count -= 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1C000", func_8002BB30);

void func_8002BBB8(void) {
}

s32 func_8002BBC0(s32 *arg0) {
    return arg0[2];
}

s32 func_8002BBCC(s32 *arg0) {
    return arg0[3];
}

s32 func_8002BBD8(s32 *arg0) {
    return arg0[6];
}

void func_8002BBE4(s32 arg0) {
    func_80036F34(D_8005FE04, arg0);
}

s32 func_8002BC10(s32 *arg0) {
    return arg0[5];
}

extern u8 *func_8002BE14(s32);
extern void func_8002BE3C(void *);

void func_8002BC1C(PriorityList *list, PriorityNode *node) {
    func_8002BB30(list, node);
}

void func_8002BC3C(s32 *arg0) {
    arg0[5] = 1;
}

s32 func_8002BC48(s32 *arg0) {
    return arg0[5];
}

s32 func_8002BC54(s32 *arg0) {
    return arg0[4];
}

void func_8002BC60(s32 size, void *arg1, HandlePool *arg2) {
    func_8003A368(&D_80114770, arg1, size);
    D_80114768 = arg2;
}

}

// Natural C++ base destructor; #pragma interface reuses the retail vtable.
// The asm alias block below binds the old ABI symbols to manifest names.
#pragma interface
struct Node { Node *next; Node *prev; };
class Base {
public:
    Node link;      /* +0x00 */
    int f8;         /* +0x08 */
    int fC;
    int f10;        /* vptr lands at +0x14 */
    Base(int value);
    virtual ~Base();
};
Base::Base(int value) {
    f10 = value;
    link.next = &link;
    link.prev = &link;
    f8 = func_80036DDC(D_80114768, this);
}
Base::~Base() {
    func_80036E88(D_80114768, f8);
    link.next->prev = link.prev;
    link.prev->next = link.next;
    link.next = &link;
    link.prev = &link;
}
// Keep the old GNU C++ ABI names linkable in both build_dra and slotcheck.
__asm__(
    ".globl func_8002BC9C\n"
    ".set func_8002BC9C, __4Basei\n"
    ".globl func_8002BCEC\n"
    ".set func_8002BCEC, _._4Base\n"
    ".set _vt.4Base, D_80019200\n"
    ".set __builtin_delete, func_8002BDA8"
);

extern "C" {

// func_8002BCEC is defined above as the natural C++ Base destructor.

s32 func_8002BD68(s32 *arg0) {
    return arg0[4];
}

s32 func_8002BD74(s32 *arg0) {
    return arg0[2];
}

void *func_8002BD80(u32 size, void *storage) {
    return storage;
}

u8 *func_8002BD88(s32 arg0) {
    return func_8002BE14(arg0);
}

void func_8002BDA8(void *arg0) {
    func_8002BE3C(arg0);
}

u8 *func_8002BDC8(u32 handle) {
    return (u8 *)func_80036F34(D_80114768, handle);
}

DtorList *func_8002BDF4(DtorNode *node) {
    return func_8002BEB4(node);
}

u8 *func_8002BE14(s32 arg0) {
    return (u8 *)func_8003A584(&D_80114770, arg0);
}

void func_8002BE3C(void *arg0) {
    func_8003A2A4(&D_80114770, arg0);
}

struct DisposalVtable {
    u8 reserved[0x18];
    s16 thisOffset;
    s16 padding;
    void (*invoke)(void *, s32);
};
struct DisposalTarget {
    u8 reserved[0x14];
    DisposalVtable *vtable;
};

void func_8002BE64(u32 handle) {
    DisposalTarget *target = (DisposalTarget *)func_8002BDC8(handle);
    if (target != 0) {
        DisposalVtable *vtable = target->vtable;
        vtable->invoke((u8 *)target + vtable->thisOffset, 3);
    }
}

DtorList *func_8002BEB4(DtorNode *node) {
    s32 empty = node->link.next == &node->link && &node->link == node->link.prev;
    if (empty) {
        return 0;
    }
    return node->owner;
}

void func_8002BEE8(void *arg0) {
    u32 *words = (u32 *)arg0;

    func_80036E88(D_80114768, words[2]);
    words[2] = func_80036DDC(D_80114768, arg0);
}

void func_8002BF34(DtorNode *self, DtorNode *allocation) {
    if (allocation != 0) {
        func_8002C210(func_8002BDF4(self), allocation);
    }
}

s32 *func_8002BF6C(u32 *arg0) {
    arg0[0] = (u32)arg0;
    arg0[1] = (u32)arg0;
    arg0[2] = (u32)(arg0 + 2);
    arg0[3] = (u32)(arg0 + 2);
    return (s32 *)arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1C000", func_8002BF88);


}
