#ifndef GAME_SORT_H
#define GAME_SORT_H

#include "common.h"

/* All sortable nodes have a forward link. The second word has a role chosen
 * by the owning list: a previous link for doubly linked lists, or a key in
 * the title list. */
typedef struct SortNode {
    struct SortNode *next;
    union {
        struct SortNode *previous;
        s32 key;
    } word4;
} SortNode;

typedef struct SortList {
    SortNode *head;
    SortNode *tail;
} SortList;

typedef struct SortInsertList {
    SortNode *head;
    SortNode *tail;
    u32 count;
} SortInsertList;

typedef s32 (*SortCompare)(SortNode *left, SortNode *right);

typedef char SortNode_size_is_8[(sizeof(SortNode) == 8) ? 1 : -1];
typedef char SortList_size_is_8[(sizeof(SortList) == 8) ? 1 : -1];
typedef char SortInsertList_size_is_12[(sizeof(SortInsertList) == 12) ? 1 : -1];

SortNode *func_80038610(SortNode *head, SortCompare compare);
void func_80038638(SortList *list, SortCompare compare);
SortNode *func_80038690(SortCompare compare, SortNode *head);
SortNode *func_8003873C(SortCompare compare, SortNode *left, SortNode *right);
void func_800387E0(SortInsertList *list, SortNode *anchor, SortNode *node);

#endif
