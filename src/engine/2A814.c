#include "common.h"
#include "game_resources.h"
#include "game_heap.h"
#include "game_handles.h"

/* Heap algorithms adapted from ReGame-Labs/dtbe_decomp, a54d64e.
 * Copyright (c) 2026 juandav; MIT notice: docs/licenses/REGAME-DTBE-MIT.txt.
 * Addresses and declarations adjusted for the USA executable. */


extern void *func_8003A13C(s32);

s32 func_8003A014(s32 id) {
    u8 *ptr = func_8003A13C(id);
    s32 result;
    if (ptr != NULL) {
        result = ptr[0x13] & 0x1F;
    } else {
        result = -1;
    }
    return result;
}


void func_8003A04C(s32 id) {
    void *ptr = func_8003A13C(id);
    if (ptr != NULL) {
        func_80039EB0(ptr);
    }
}

extern s16 (*D_80116698)[4];
extern s32 func_800536BC(void *, s16);
extern s16 func_8005386C(s16);

s32 func_8003A07C(s32 id, void *destination) {
    s32 result = func_800536BC(destination, D_80116698[(u16)id][3]);
    func_8005386C(1);
    return result;
}

extern HandlePool *func_80036C64(HandlePool *, s32);
extern HandlePool D_80116BB8;

void func_8003A0CC(s32 mode, s32 id) {
    if (id == 0xFFFF) {
        if (mode != 0) {
            func_80036C64(&D_80116BB8, 0x30);
        } else {
            func_80036D88(&D_80116BB8, 2);
        }
    }
}

u32 func_8003A114(void *value) {
    return func_80036DDC(&D_80116BB8, value);
}

void *func_8003A13C(s32 id) {
    return func_80036F34(&D_80116BB8, id);
}

void *func_8003A164(s32 id) {
    return func_80036E88(&D_80116BB8, id);
}

void func_8003A18C(void) {
    func_8003A0CC(1, 0xFFFF);
}

void func_8003A1B0(void) {
    func_8003A0CC(0, 0xFFFF);
}

s32 func_8003A1D4(Heap *heap) {
    HeapBlock *block = heap->rover;
    s32 largest = 0;

    do {
        if (largest < block->size) {
            largest = block->size;
        }
        block = block->next;
    } while (block != heap->rover);
    return largest - sizeof(HeapBlock);
}

s32 func_8003A210(Heap *heap) {
    HeapBlock *block = heap->rover;
    s32 count = heap->count;
    HeapBlock *first = heap->first;
    HeapBlock *end = heap->end;
    HeapBlock *next;

    do {
        if (block < first || block >= end || ((u32)block & 3)) {
            return -1;
        }
        next = block->next;
        if (next < first || next >= end || ((u32)next & 3)) {
            return -1;
        }
        if (next->prev != block) {
            return -1;
        }
        block = next;
        count--;
    } while (block != heap->rover);
    if (count != 0) {
        return -1;
    }
    return 0;
}

void func_8003A2A4(Heap *heap, void *ptr) {
    HeapBlock *block = ptr;
    HeapBlock *neighbor;
    HeapBlock *next;
    HeapBlock *rover;
    s32 size;

    if (block != NULL) {
        block--;
        neighbor = block->next;
        size = -block->size;
        block->size = size;
        rover = heap->rover;
        if (neighbor->size > 0 && (HeapBlock *)((u8 *)block + size) == neighbor) {
            block->size = size + neighbor->size;
            block->next = neighbor->next;
            neighbor->next->prev = block;
            if (rover == neighbor) {
                rover = block;
            }
            heap->count--;
        }
        neighbor = block->prev;
        if (neighbor->size > 0 && (HeapBlock *)((u8 *)block - neighbor->size) == neighbor) {
            neighbor->size += block->size;
            next = block->next;
            neighbor->next = next;
            next->prev = neighbor;
            if (rover == block) {
                rover = neighbor;
            }
            heap->count--;
        }
        heap->rover = rover;
    }
}

void func_8003A368(Heap *heap, void *base, s32 size) {
    HeapBlock *first = (HeapBlock *)(((u32)base + 3) & ~3);

    size -= (u32)first - (u32)base;
    size &= ~3;
    heap->count = 1;
    heap->rover = first;
    heap->first = first;
    heap->end = (HeapBlock *)((u8 *)first + size);
    first->size = size;
    first->next = first;
    first->prev = first;
}

void *func_8003A3A8(Heap *heap, s32 size) {
    HeapBlock *block = heap->first;
    HeapBlock *best = NULL;
    s32 bestLeft = 0x7FFFFFFF;
    s32 left;

    size = HEAP_BLOCK_SIZE(size);
    do {
        left = block->size - size;
        if (left == 0) {
            goto exact;
        }
        if (left > 0 && left < bestLeft) {
            bestLeft = left;
            best = block;
        }
        block = block->next;
    } while (block != heap->first);
    if (best == NULL) {
        return NULL;
    }
    if (bestLeft <= HEAP_MIN_SPLIT) {
        goto whole;
    }
    /* the rest of the block becomes a free block after it */
    block = (HeapBlock *)((u8 *)best + size);
    heap->rover = block;
    heap->count++;
    block->size = bestLeft;
    best->size = -size;
    best->next->prev = block;
    block->next = best->next;
    block->prev = best;
    best->next = block;
    return best + 1;
exact:
    heap->rover = block->next;
    block->size = -block->size;
    return block + 1;
whole:
    best->size = -best->size;
    return best + 1;
}

void *func_8003A490(Heap *heap, s32 size) {
    HeapBlock *block;
    HeapBlock *best = NULL;
    s32 bestLeft = 0;
    s32 left;

    size = HEAP_BLOCK_SIZE(size);
    block = heap->first->prev;
    do {
        left = block->size - size;
        if (left == 0) {
            goto exact;
        }
        if (left > 0 && bestLeft < left) {
            bestLeft = left;
            best = block;
        }
        block = block->prev;
    } while (block != heap->first->prev);
    if (best == NULL) {
        return NULL;
    }
    if (bestLeft <= HEAP_MIN_SPLIT) {
        goto whole;
    }
    /* the block keeps its start, free, and hands out its end */
    block = (HeapBlock *)((u8 *)best + bestLeft);
    heap->rover = best;
    heap->count++;
    best->size = bestLeft;
    block->size = -size;
    best->next->prev = block;
    block->next = best->next;
    best->next = block;
    block->prev = best;
    return block + 1;
exact:
    heap->rover = block->prev;
    block->size = -block->size;
    return block + 1;
whole:
    best->size = -best->size;
    return best + 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/2A800", func_8003A584);

INCLUDE_ASM("asm/us/main/nonmatchings/2A800", func_8003A658);

s32 func_8003A72C(Heap *heap) {
    HeapBlock *block = heap->rover;
    s32 total = 0;

    do {
        if (block->size > 0) {
            total += block->size;
        }
        block = block->next;
    } while (block != heap->rover);
    return total;
}

void func_8003A764(Heap *heap, void *ptr, s32 size) {
    HeapBlock *allocation = ptr;
    HeapBlock *block = allocation - 1;
    HeapBlock *remainder;
    HeapBlock *next;
    s32 left;

    size = HEAP_BLOCK_SIZE(size);
    remainder = (HeapBlock *)((u8 *)block + size);
    left = -allocation[-1].size - size;
    next = allocation[-1].next;
    if (block < next && next->size > 0) {
        if (heap->rover == next) {
            heap->rover = remainder;
        }
        allocation[-1].size = -size;
        remainder->size = left + allocation[-1].next->size;
        remainder->next = allocation[-1].next->next;
        remainder->next->prev = remainder;
        remainder->prev = block;
        allocation[-1].next = remainder;
    } else if (left > HEAP_MIN_SPLIT) {
        block->size = -size;
        remainder->next = block->next;
        remainder->next->prev = remainder;
        remainder->prev = block;
        block->next = remainder;
        remainder->size = left;
        heap->count++;
    }
}

/* Preserve the old sector label inside the complete shrink routine. */
__asm__(".globl func_8003A800\n.set func_8003A800, func_8003A764 + 0x9C\n.size func_8003A800, 0x34");
