#ifndef GAME_HEAP_H
#define GAME_HEAP_H

/* Types adapted from ReGame-Labs/dtbe_decomp, a54d64e.
 * Copyright (c) 2026 juandav; MIT notice: docs/licenses/REGAME-DTBE-MIT.txt. */

#include "common.h"

typedef struct HeapBlock {
    struct HeapBlock *next;
    struct HeapBlock *prev;
    s32 size;
} HeapBlock;

typedef struct Heap {
    HeapBlock *rover;
    HeapBlock *first;
    HeapBlock *end;
    s32 count;
} Heap;

#define HEAP_BLOCK_SIZE(size) (((size) + sizeof(HeapBlock) + 3) & ~3)
#define HEAP_MIN_SPLIT ((s32)sizeof(HeapBlock))

#ifdef __cplusplus
extern "C" {
#endif

s32 func_8003A1D4(Heap *heap);
s32 func_8003A210(Heap *heap);
void func_8003A2A4(Heap *heap, void *ptr);
void func_8003A368(Heap *heap, void *base, s32 size);
void *func_8003A3A8(Heap *heap, s32 size);
void *func_8003A490(Heap *heap, s32 size);
void *func_8003A584(Heap *heap, s32 size);
void *func_8003A658(Heap *heap, s32 size);
s32 func_8003A72C(Heap *heap);
void func_8003A764(Heap *heap, void *ptr, s32 size);

#ifdef __cplusplus
}
#endif

#endif
