#ifndef GAME_POSITIONS_H
#define GAME_POSITIONS_H

#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif

u8 *func_80077624(u8 *owner);
u8 *func_80077630(u8 *owner);
s32 *func_8007767C(u8 *owner, s32 *position);
/* Transform three position words using the selected resource descriptor. */
void *func_8007A724(u8 *owner, void *position, s32 index, const u8 *descriptor);
/* Read or transform three position words from the selected actor. */
u8 *func_8007A8D0(u8 *actor, u8 *position);
s32 *func_8007A91C(u8 *owner, s32 *position);
u8 *func_8007A94C(u8 *owner, u8 *position);

#ifdef __cplusplus
}
#endif
#endif
