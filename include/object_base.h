#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H
#include "common.h"

typedef struct Func8002C3CCNode {
    struct Func8002C3CCNode *next;
    struct Func8002C3CCNode *prev;
    u32 f8;
    u32 fC;
    s32 f10;
    u32 f14;
    u32 f18;
    void *f1C;
} Func8002C3CCNode;

typedef char ObjectBase_size_is_0x20[(sizeof(Func8002C3CCNode) == 0x20) ? 1 : -1];
#ifdef __cplusplus
extern "C" {
#endif
Func8002C3CCNode *func_8002C3CC(Func8002C3CCNode *self, s32 value);
#ifdef __cplusplus
}
#endif
#endif
