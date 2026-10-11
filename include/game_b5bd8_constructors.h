#ifndef GAME_B5BD8_CONSTRUCTORS_H
#define GAME_B5BD8_CONSTRUCTORS_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Both constructors read exactly three position words and return self. */
u8 *func_800B5BD8(u8 *self, u8 *owner, u8 *context, const s32 *position);
u8 *func_800B61CC(u8 *self, u8 *owner, const s32 *position);

#ifdef __cplusplus
}
#endif

#endif
