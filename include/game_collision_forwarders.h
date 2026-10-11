#ifndef GAME_COLLISION_FORWARDERS_H
#define GAME_COLLISION_FORWARDERS_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward the other collision node through the adapter and adjusted callback. */
void func_800C8A10(u8 *adapter, u8 *collider);
void func_800C90B8(u8 *self, u8 *collider);
void func_800C90EC(u8 *self, u8 *collider);

#ifdef __cplusplus
}
#endif

#endif
