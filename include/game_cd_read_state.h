#ifndef GAME_CD_READ_STATE_H
#define GAME_CD_READ_STATE_H
#include "common.h"
#include "game_cd_callbacks.h"
typedef struct VfsReadState {
    u8 *destination;
    u8 reserved004[4];
    u16 sectors;
    u8 reserved00A[4];
    u16 headBytes;
    u8 reserved010[4];
    u16 tailBytes;
    u8 reserved016[2];
    u8 *head;
    u8 reserved01C[8];
    VfsReadyCallback ready;
    VfsDeviceCallback finish;
    u32 mode;
} VfsReadState;
typedef char VfsReadState_span_is_0x30[(sizeof(VfsReadState) == 0x30) ? 1 : -1];
#ifdef __cplusplus
extern "C" {
#endif
extern VfsReadState D_80116620;
#ifdef __cplusplus
}
#endif
#endif
