#ifndef GAME_CD_CALLBACKS_H
#define GAME_CD_CALLBACKS_H
#include "common.h"
/* Actual retained SDK dispatcher interfaces; routines stay assembly. */
typedef void (*VfsDeviceCallback)(void);
typedef void (*VfsReadyCallback)(u32 event, u32 opaque, u8 *result);
#ifdef __cplusplus
extern "C" {
#endif
VfsDeviceCallback func_80046DDC(VfsDeviceCallback callback);
s32 func_8004625C(VfsReadyCallback callback, s32 mode);
#ifdef __cplusplus
}
#endif
#endif
