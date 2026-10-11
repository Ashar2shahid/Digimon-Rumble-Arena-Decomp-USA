#include "common.h"
#include "game_resources.h"
#include "game_sort.h"

extern void func_800388D4(void *, void *, s32, s32);
extern void func_80038848(void *, void *);
extern void func_800389E8(SortInsertList *, SortNode *, SortNode *);
extern u8 D_801169E8[];
extern u16 D_801166AC;
extern u16 D_801166AE;

INCLUDE_ASM("asm/us/main/nonmatchings/29000", func_80038848);

void func_800388A8(u8 *list, void *nodes, s32 stride, s32 count) {
    *(void **)(list + 0x10) = nodes;
    *(s32 *)(list + 4) = 0;
    *(s32 *)(list + 8) = 0;
    *(s32 *)(list + 0xC) = 0;
    func_800388D4(list, nodes, stride, count);
}

INCLUDE_ASM("asm/us/main/nonmatchings/29000", func_800388D4);

INCLUDE_ASM("asm/us/main/nonmatchings/29000", func_80038910);

/* Peek the list head a0[0] into a1[0], then push a1 onto the head. */
void func_8003893C(s32 **a0, s32 *a1) {
    a1[0] = a0[0];
    a0[0] = a1;
}

void func_80038950(u8 *list, void **node) {
    func_80038848(list + 4, node);
    *node = *(void **)list;
    *(void **)list = node;
}

void func_80038990(u8 *list, void *node) {
    func_800387E0((SortInsertList *)(list + 4), *(SortNode **)(list + 4), (SortNode *)node);
}

void func_800389BC(u8 *list, void *node) {
    func_800389E8((SortInsertList *)(list + 4), *(SortNode **)(list + 8), (SortNode *)node);
}

void func_800389E8(SortInsertList *list, SortNode *previous, SortNode *node) {
    list->count++;
    if (list->head == 0) {
        node->next = 0;
        node->word4.previous = 0;
        list->head = node;
        list->tail = node;
        return;
    }
    node->word4.previous = previous;
    node->next = previous->next;
    if (previous->next == 0) {
        list->tail = node;
    } else {
        previous->next->word4.previous = node;
    }
    previous->next = node;
}

INCLUDE_ASM("asm/us/main/nonmatchings/29000", func_80038A50);

INCLUDE_ASM("asm/us/main/nonmatchings/29000", func_80038B0C);

s32 func_80038B24(u16 index) {
    ResourceState *resource = &D_80116690;
    u8 *entry = resource->entries8;
    u16 handle = *(u16 *)(entry + index * 8);
    u8 *table = resource->table1;
    return *(u16 *)(table + handle * 8 + 2);
}

extern u8 *D_801166A4;

s32 func_80038B58(u16 a0) {
    return *(u16 *)(D_801166A4 + a0 * 8);
}

extern u8 *D_801166A0;

s32 func_80038B78(u16 a0) {
    return *(u16 *)(D_801166A0 + a0 * 16);
}

u8 *func_80038B98(u16 index) {
    ResourceState *resource = &D_80116690;
    u8 *table = (u8 *)resource->handles;
    u16 offset = *(u16 *)(table + index * 8);
    return resource->data + offset;
}

u8 *func_80038BC0(u16 index) {
    ResourceState *resource = &D_80116690;
    u8 *table = resource->table1;
    u16 offset = *(u16 *)(table + index * 8);
    return resource->data + offset;
}

s32 func_80038BE8(void) {
    return D_801166AC;
}

s32 func_80038BF8(void) {
    return D_801166AE;
}

INCLUDE_ASM("asm/us/main/nonmatchings/29000", func_80038C08);

INCLUDE_ASM("asm/us/main/nonmatchings/29000", func_80038D18);

INCLUDE_ASM("asm/us/main/nonmatchings/29000", func_80038D44);

INCLUDE_ASM("asm/us/main/nonmatchings/29000", func_80038D98);

INCLUDE_ASM("asm/us/main/nonmatchings/29000", func_80038E7C);
