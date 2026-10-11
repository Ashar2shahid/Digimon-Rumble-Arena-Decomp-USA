#ifndef GAME_ACTOR_QUERIES_H
#define GAME_ACTOR_QUERIES_H
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif

/* Select the live actor through the owner's resource descriptor. */
u8 *func_800732A8(u8 *resource, u8 *owner);
u8 *func_8007B16C(u8 *owner);

#ifdef __cplusplus
}
#endif
#endif
