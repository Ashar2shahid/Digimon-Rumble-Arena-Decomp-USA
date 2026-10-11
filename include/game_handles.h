#ifndef GAME_HANDLES_H
#define GAME_HANDLES_H

#include "common.h"

typedef struct HandleNode {
    struct HandleNode *next;
    struct HandleNode *previous;
    void *value;
    union {
        u32 value;
        struct {
            u32 index : 12;
            u32 generation : 20;
        } fields;
    } id;
} HandleNode;

typedef struct HandlePool {
    HandleNode *records;
    HandleNode *active;
    u32 capacity;
} HandlePool;

#ifdef __cplusplus
extern "C" {
#endif

extern HandlePool *D_8005FE04;
void func_8002B6C8(HandlePool *pool);

void func_80036D88(HandlePool *pool, u32 flags);
u32 func_80036DDC(HandlePool *pool, void *value);
void *func_80036E88(HandlePool *pool, u32 handle);
void *func_80036F34(HandlePool *pool, u32 handle);
u32 func_80036F88(HandlePool *pool, HandleNode *head);
u32 func_80036FB0(HandlePool *pool);
u32 func_80036FE0(HandlePool *pool);

/* Resolve a handle and dispatch the signed-adjustment disposal callback. */
void func_8002BE64(u32 handle);

#ifdef __cplusplus
}
#endif

#endif
