#ifndef GAME_THREAD_H
#define GAME_THREAD_H
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct GameThread {
    u32 id;
    u8 *stack;
    u32 caller;
} GameThread;
typedef char GameThread_size_is_12[(sizeof(GameThread) == 12) ? 1 : -1];

void func_8001EFB0(GameThread *self, u32 flags);

s32 func_8001F020(GameThread *self, s32 value);
s32 func_8001F04C(GameThread *self, s32 value);
s32 func_8001F070(u32 id, s32 value);

#ifdef __cplusplus
}
#endif
#endif
