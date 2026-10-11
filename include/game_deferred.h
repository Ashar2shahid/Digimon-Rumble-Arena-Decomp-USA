#ifndef GAME_DEFERRED_H
#define GAME_DEFERRED_H

#include "deferred_objects.h"

/* Gameplay-overlay wrappers; same-address title symbols have separate ABIs. */
#ifdef __cplusplus
extern "C" {
#endif

u8 *func_8006F06C(u8 *owner, u8 *node);
u8 *func_8006F09C(u8 *owner, u8 *node);
void func_8006F0CC(u8 *owner, u8 *node);
void func_8007AFCC(u8 *owner, u8 *node);

#ifdef __cplusplus
}
#endif

#endif
