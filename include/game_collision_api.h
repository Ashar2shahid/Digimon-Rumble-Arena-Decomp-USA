#ifndef GAME_COLLISION_API_H
#define GAME_COLLISION_API_H
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Apply effect words at +8..+18 to the collider words at +18..+28. */
void func_8007C0C8(u8 *effect, u8 *collider);
#ifdef __cplusplus
}
#endif
#endif
