#ifndef GAME_EFFECT_CONSTRUCTOR_H
#define GAME_EFFECT_CONSTRUCTOR_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Gameplay overlay constructor. Both vectors contain three target words. */
u8 *func_800C3258(u8 *self, s32 kind, s32 *first, s32 *second,
                  s32 value1, s32 value2, s32 option);

#ifdef __cplusplus
}
#endif

#endif
