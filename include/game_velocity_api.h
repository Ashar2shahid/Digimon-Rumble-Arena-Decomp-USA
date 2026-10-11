#ifndef GAME_VELOCITY_API_H
#define GAME_VELOCITY_API_H
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Adjust the actor position using signed fixed-point velocity correction. */
void func_800785BC(u8 *actor, s32 velocity);
#ifdef __cplusplus
}
#endif
#endif
