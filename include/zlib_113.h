#ifndef ZLIB_113_H
#define ZLIB_113_H

/* Altered target-layout declarations adapted from zlib 1.1.3 (1998).
 * Copyright (C) 1995-1998 Jean-loup Gailly and Mark Adler.
 * See docs/licenses/ZLIB-1.1.3.txt for the original license notice.
 * These are separate from the Sony SDK.
 */
#include "common.h"

typedef struct ZlibBlockState ZlibBlockState;
typedef struct ZlibInflateState ZlibInflateState;
typedef void *(*ZlibAllocFn)(void *opaque, u32 items, u32 size);
typedef void (*ZlibFreeFn)(void *opaque, void *address);

typedef struct ZlibStream {
    u8 *next_in;
    u32 avail_in;
    u32 total_in;
    u8 *next_out;
    u32 avail_out;
    u32 total_out;
    char *msg;
    ZlibInflateState *state;
    ZlibAllocFn zalloc;
    ZlibFreeFn zfree;
    void *opaque;
    s32 data_type;
    u32 adler;
    u32 reserved;
} ZlibStream;

struct ZlibInflateState {
    s32 mode;
    union {
        u32 method;
        struct { u32 was, need; } check;
        u32 marker;
    } sub;
    s32 nowrap;
    u32 wbits;
    ZlibBlockState *blocks;
};

struct ZlibBlockState {
    s32 mode;
    union {
        u32 left;
        struct {
            u32 table;
            u32 index;
            u32 *blens;
            u32 bb;
            void *tb;
        } trees;
        struct { void *codes; } decode;
    } sub;
    u32 last;
    u32 bitk;
    u32 bitb;
    void *hufts;
    u8 *window;
    u8 *end;
    u8 *read;
    u8 *write;
    u32 (*checkfn)(u32 check, const u8 *buffer, u32 size);
    u32 check;
};

typedef char ZlibStream_size_is_0x38[(sizeof(ZlibStream) == 0x38) ? 1 : -1];
typedef char ZlibInflateState_size_is_0x18[(sizeof(ZlibInflateState) == 0x18) ? 1 : -1];
typedef char ZlibBlockState_size_is_0x40[(sizeof(ZlibBlockState) == 0x40) ? 1 : -1];

#endif
