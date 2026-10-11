#ifndef GAME_SAVE_CONFIG_H
#define GAME_SAVE_CONFIG_H
#include "common.h"
typedef struct {
    s32 mono;
    s32 reserved04[2];
    s32 buttonConfig;
    s32 level;
    s16 screenX, screenY;
    s32 reserved18;
    u32 unlocked, cleared;
    u16 buttons[2][6];
    u8 reserved3C[0x200];
    u8 md5[16];
} SaveConfig;
typedef struct { u16 button, padButton, defaultIndex; } SaveButtonSlot;
typedef char SaveConfig_size_is_0x24C[(sizeof(SaveConfig) == 0x24C) ? 1 : -1];
typedef char SaveButtonSlot_size_is_6[(sizeof(SaveButtonSlot) == 6) ? 1 : -1];
#ifdef __cplusplus
extern "C" {
#endif
extern const SaveButtonSlot D_8001035C[6];
void func_8001E7A4(SaveConfig *self);
void func_8001E924(SaveConfig *self, s32 player, s32 slot, s32 index);
#ifdef __cplusplus
}
#endif
#endif
