#ifndef GAME_LOADING_SCREEN_H
#define GAME_LOADING_SCREEN_H
#include "common.h"
typedef void (*GameLoadingCallback)(u8 *self);
typedef struct GameLoadingDispatchEntry {
    s16 delta;
    u16 reserved;
    GameLoadingCallback call;
} GameLoadingDispatchEntry;
typedef struct GameLoadingVtable {
    GameLoadingDispatchEntry unused;
    GameLoadingDispatchEntry load;
    GameLoadingDispatchEntry draw;
    GameLoadingDispatchEntry unusedTail;
} GameLoadingVtable;
typedef char GameLoadingVtable_size_is_32[(sizeof(GameLoadingVtable) == 32) ? 1 : -1];
/* Complete 20-byte loading picture object. */
typedef struct GameLoadingScreen {
    s16 x, y, width, height;
    u32 tpage;
    s32 first;
    const GameLoadingVtable *vtable;
} GameLoadingScreen;
typedef char GameLoadingScreen_size_is_20[(sizeof(GameLoadingScreen) == 20) ? 1 : -1];
/* Game's overridden load/draw pair initializes and reads this real extra word. */
typedef struct GameLoadingScreenWithCaption {
    GameLoadingScreen base;
    s32 captionVisible;
} GameLoadingScreenWithCaption;
typedef char GameLoadingScreenWithCaption_size_is_24[(sizeof(GameLoadingScreenWithCaption) == 24) ? 1 : -1];
#ifdef __cplusplus
extern "C" {
#endif
GameLoadingScreen *func_8001EC08(GameLoadingScreen *self);
void func_8001EC24(GameLoadingScreen *self);
void func_8001EC8C(u8 *self);
void func_8001ED7C(u8 *self);
extern const GameLoadingVtable D_800103D0;
extern const GameLoadingVtable D_8006DF24;
#ifdef __cplusplus
}
#endif
#endif
