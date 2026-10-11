#ifndef GAME_KEY_LOOKUP_H
#define GAME_KEY_LOOKUP_H
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Sorted halfword keys, signed full-word count, halfword key; index or -1.
 * Retail reads keys[0] even for count zero. Resource extents remain caller-owned. */
s32 func_800326E8(u16 *keys, s32 count, u16 key);
#ifdef __cplusplus
}
#endif
#endif
