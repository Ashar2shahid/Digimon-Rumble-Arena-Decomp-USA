#ifndef GAME_RANDOM_H
#define GAME_RANDOM_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RandomState {
    u32 words[624];
    s32 index;
} RandomState;

/* Compile-time layout checks for the pre-C99 target compiler. */
typedef char RandomState_size_is_2500[(sizeof(RandomState) == 2500) ? 1 : -1];
#define RANDOM_STATE_OFFSET(field) ((u32)&((RandomState *)0)->field)
typedef char RandomState_index_offset_is_0x9C0[
    (RANDOM_STATE_OFFSET(index) == 0x9C0) ? 1 : -1];
#undef RANDOM_STATE_OFFSET


extern RandomState D_8005EE48;
u32 func_80037010(RandomState *state);
RandomState *func_800371E8(RandomState *state);
void func_800371F8(RandomState *state, u32 seed);

/* Advances the generator state held at owner + 0x360 and returns its result. */
s32 func_8006EFEC(u8 *owner);

#ifdef __cplusplus
}
#endif

#endif
