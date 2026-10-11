#ifndef GAME_ACTION_API_H
#define GAME_ACTION_API_H
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Play actor audio and return the stored playback handle. */
s32 func_80078754(u8 *actor, s32 sound);
/* Start the common action animation only for event zero. */
void func_8007BEF4(u8 *actor, s32 event);
#ifdef __cplusplus
}
#endif
#endif
