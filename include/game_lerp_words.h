#ifndef GAME_LERP_WORDS_H
#define GAME_LERP_WORDS_H
#include "common.h"
#include "object_base.h"
/* 0x20 task base followed by duration,time,value,start,target. */
typedef struct GameFadeControl {
    Func8002C3CCNode task;
    s32 level[5];
} GameFadeControl;
typedef char GameFadeControl_size_is_0x34[(sizeof(GameFadeControl) == 0x34) ? 1 : -1];
#ifdef __cplusplus
extern "C" {
#endif
/* duration,time,value,start,target are five initialized word cells. */
u32 *func_8002D584(u32 *state, u32 value);
s32 func_8002D5B0(s32 *state);
s32 func_8002D678(const s32 *state);
extern GameFadeControl D_8005F884;
void func_8001EAB4(void *object, s32 duration);
void func_8001EAD4(void *object, s32 duration);
void func_8001EAF4(void *object, s32 duration, s32 target);
s32 func_8001EB20(void *object);
void func_8002D64C(u32 *state, u32 target, u32 duration);
#ifdef __cplusplus
}
#endif
#endif
