#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include "psx.h"

/* Resident game renderer. Its first two buffers use the SDK GPU layouts. */
typedef struct RenderContext {
    DISPENV display[2];
    DRAWENV draw[2];
    DISPENV *displayCurrent[2];
    DRAWENV *drawCurrent[2];
    DISPENV *displayOverride;
    s32 active;
    s32 stateF8;
    s32 stateFC;
    s32 state100;
    s32 state104;
    s32 state108;
    s32 state10C;
    s32 state110;
    s32 state114;
    s32 state118;
} RenderContext;

typedef char RenderContext_size_is_0x11c[(sizeof(RenderContext) == 0x11C) ? 1 : -1];

void func_8001F4BC(RenderContext *self, s32 width, s32 height);

#endif /* RENDER_CONTEXT_H */
