#ifndef GAME_DESTRUCTOR_API_H
#define GAME_DESTRUCTOR_API_H
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Base destructor: self+4 receives the base dispatch table; flags&1 frees self. */
void func_8007C374(u8 *self, s32 flags);
#ifdef __cplusplus
}
#endif
#endif
