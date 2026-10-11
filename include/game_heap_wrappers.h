#ifndef GAME_HEAP_WRAPPERS_H
#define GAME_HEAP_WRAPPERS_H
#include "game_heap.h"
#ifdef __cplusplus
extern "C" {
#endif
extern Heap D_80114748;
extern Heap D_80114758;
void func_8002B118(void *base, u32 size);
s32 func_8002B300(void);
void *func_8002B248(s32 size);
void func_8002B2B4(void *address);
/* VFS installs these as the genuine zlib allocation/free callbacks. */
void *func_8001B31C(void *opaque, u32 items, u32 size);
void func_8001B344(void *opaque, void *address);
#ifdef __cplusplus
}
#endif
#endif
