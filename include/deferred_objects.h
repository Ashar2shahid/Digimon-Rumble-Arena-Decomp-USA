#ifndef DEFERRED_OBJECTS_H
#define DEFERRED_OBJECTS_H

#include "common.h"

typedef struct DtorLink {
    struct DtorLink *next;
    struct DtorLink *prev;
} DtorLink;

typedef struct DtorList {
    DtorLink first;
    DtorLink second;
} DtorList;

typedef struct DtorNode {
    DtorLink link;
    s32 f8;
    DtorList *owner;
} DtorNode;

typedef char DtorNode_size_is_0x10[(sizeof(DtorNode) == 0x10) ? 1 : -1];
typedef char DtorList_size_is_0x10[(sizeof(DtorList) == 0x10) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif

DtorList *func_8002BDF4(DtorNode *node);
DtorList *func_8002BEB4(DtorNode *node);
void func_8002BF34(DtorNode *self, DtorNode *allocation);
DtorList *func_8002C210(DtorList *list, DtorNode *node);

#ifdef __cplusplus
}
#endif

#endif
