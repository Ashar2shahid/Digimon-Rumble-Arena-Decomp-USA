#include "common.h"
#include "zlib_113.h"

extern void func_8003C2B8(ZlibBlockState *blocks, ZlibStream *stream, u32 *check);

/* Altered zlib 1.1.3 routines, adapted to the game's symbols.
 * Copyright (C) 1995-1998 Mark Adler; license in docs/licenses/ZLIB-1.1.3.txt.
 */

extern s32 func_8003A834(ZlibStream *stream, s32 windowBits, const char *version, s32 streamSize);

/* inflateSync: altered zlib1.1.3, Gailly/Adler; initialized four-byte sync marker. */
u8 D_800643A4[4] = {0, 0, 0xFF, 0xFF};
s32 func_8003AFF8(ZlibStream *z) {
    u32 n, m, inputTotal, outputTotal;
    u8 *p;
    if (z == 0 || z->state == 0) return -2;
    if (z->state->mode != 13) {
        z->state->mode = 13;
        z->state->sub.marker = 0;
    }
    if ((n = z->avail_in) == 0) return -5;
    p = z->next_in;
    m = z->state->sub.marker;
    while (n != 0 && m < 4) {
        if (*p == D_800643A4[m]) ++m;
        else if (*p != 0) m = 0;
        else m = 4 - m;
        ++p;
        --n;
    }
    z->total_in += (u32)(p - z->next_in);
    z->next_in = p;
    z->avail_in = n;
    z->state->sub.marker = m;
    if (m != 4) return -3;
    inputTotal = z->total_in;
    outputTotal = z->total_out;
    if (z != 0 && z->state != 0) {
        z->total_in = z->total_out = 0;
        z->msg = 0;
        z->state->mode = z->state->nowrap ? 7 : 0;
        func_8003C2B8(z->state->blocks, z, 0);
    }
    z->total_in = inputTotal;
    z->total_out = outputTotal;
    z->state->mode = 7;
    return 0;
}


extern s32 func_8003C378(ZlibBlockState *blocks, ZlibStream *stream);
extern s32 func_8003C4B0(ZlibBlockState *blocks);

/* inflateEnd */
s32 func_8003B17C(ZlibStream *stream) {
    if (stream == 0 || stream->state == 0 || stream->zfree == 0) {
        return -2;
    }
    if (stream->state->blocks != 0) {
        func_8003C378(stream->state->blocks, stream);
    }
    stream->zfree(stream->opaque, stream->state);
    stream->state = 0;
    return 0;
}

extern u32 func_8003B3C0(u32 check, const u8 *buffer, u32 size);
extern void func_8003C46C(ZlibBlockState *blocks, const u8 *dictionary, u32 size);

/* inflateSetDictionary */
s32 func_8003B200(ZlibStream *stream, const u8 *dictionary, u32 dictionarySize) {
    u32 length = dictionarySize;
    if (stream == 0 || stream->state == 0 || stream->state->mode != 6) {
        return -2;
    }
    if (func_8003B3C0(1, dictionary, dictionarySize) != stream->adler) {
        return -3;
    }
    stream->adler = 1;
    if (length >= (1u << stream->state->wbits)) {
        length = (1u << stream->state->wbits) - 1;
        dictionary += dictionarySize - length;
    }
    func_8003C46C(stream->state->blocks, dictionary, length);
    stream->state->mode = 7;
    return 0;
}

/* inflateReset */
s32 func_8003B2D8(ZlibStream *stream) {
    ZlibInflateState *state;
    if (stream == 0 || (state = stream->state) == 0) {
        return -2;
    }
    stream->total_in = stream->total_out = 0;
    stream->msg = 0;
    state->mode = state->nowrap ? 7 : 0;
    func_8003C2B8(stream->state->blocks, stream, 0);
    return 0;
}

/* inflateInit_ */
s32 func_8003B348(ZlibStream *stream, const char *version, s32 streamSize) {
    return func_8003A834(stream, 0xF, version, streamSize);
}

/* inflateSyncPoint */
s32 func_8003B374(ZlibStream *stream) {
    if (stream == 0 || stream->state == 0 || stream->state->blocks == 0) {
        return -2;
    }
    return func_8003C4B0(stream->state->blocks);
}

/* adler32: altered zlib 1.1.3 adler32.c, Mark Adler's original unrolling. */
#define ZLIB_ADLER_BASE 65521U
#define ZLIB_ADLER_NMAX 5552U
#define ZLIB_ADLER_DO1(buffer, i) { s1 += (buffer)[i]; s2 += s1; }
#define ZLIB_ADLER_DO2(buffer, i) ZLIB_ADLER_DO1(buffer, i); ZLIB_ADLER_DO1(buffer, (i) + 1)
#define ZLIB_ADLER_DO4(buffer, i) ZLIB_ADLER_DO2(buffer, i); ZLIB_ADLER_DO2(buffer, (i) + 2)
#define ZLIB_ADLER_DO8(buffer, i) ZLIB_ADLER_DO4(buffer, i); ZLIB_ADLER_DO4(buffer, (i) + 4)
#define ZLIB_ADLER_DO16(buffer) ZLIB_ADLER_DO8(buffer, 0); ZLIB_ADLER_DO8(buffer, 8)

u32 func_8003B3C0(u32 check, const u8 *buffer, u32 length) {
    u32 s1 = check & 0xFFFFU;
    u32 s2 = (check >> 16) & 0xFFFFU;
    s32 k;
    if (buffer == 0) {
        return 1U;
    }
    while (length > 0) {
        k = length < ZLIB_ADLER_NMAX ? length : ZLIB_ADLER_NMAX;
        length -= k;
        while (k >= 16) {
            ZLIB_ADLER_DO16(buffer);
            buffer += 16;
            k -= 16;
        }
        if (k != 0) {
            do {
                s1 += *buffer++;
                s2 += s1;
            } while (--k);
        }
        s1 %= ZLIB_ADLER_BASE;
        s2 %= ZLIB_ADLER_BASE;
    }
    return (s2 << 16) | s1;
}

#undef ZLIB_ADLER_DO16
#undef ZLIB_ADLER_DO8
#undef ZLIB_ADLER_DO4
#undef ZLIB_ADLER_DO2
#undef ZLIB_ADLER_DO1
#undef ZLIB_ADLER_NMAX
#undef ZLIB_ADLER_BASE

/* inflate_blocks_new: adapted from zlib 1.1.3 infblock.c. */
typedef u32 (*ZlibCheckFn)(u32, const u8 *, u32);
extern void func_8003CD7C(void *, ZlibStream *);

static inline void zlib_blocks_reset_local(ZlibBlockState *blocks, ZlibStream *stream, u32 *check) {
    if (check != 0) {
        *check = blocks->check;
    }
    if (blocks->mode == 4 || blocks->mode == 5) {
        stream->zfree(stream->opaque, blocks->sub.trees.blens);
    }
    if (blocks->mode == 6) {
        func_8003CD7C(blocks->sub.decode.codes, stream);
    }
    blocks->mode = 0;
    blocks->bitk = 0;
    blocks->bitb = 0;
    blocks->read = blocks->write = blocks->window;
    if (blocks->checkfn != 0) {
        stream->adler = blocks->check = blocks->checkfn(0, 0, 0);
    }
}

ZlibBlockState *func_8003B588(ZlibStream *stream, ZlibCheckFn checkfn, u32 windowSize) {
    ZlibBlockState *blocks = (ZlibBlockState *)stream->zalloc(stream->opaque, 1, sizeof(ZlibBlockState));
    if (blocks == 0) {
        return 0;
    }
    blocks->hufts = stream->zalloc(stream->opaque, 8, 0x5A0);
    if (blocks->hufts == 0) {
        stream->zfree(stream->opaque, blocks);
        return 0;
    }
    blocks->window = (u8 *)stream->zalloc(stream->opaque, 1, windowSize);
    if (blocks->window == 0) {
        stream->zfree(stream->opaque, blocks->hufts);
        stream->zfree(stream->opaque, blocks);
        return 0;
    }
    blocks->end = blocks->window + windowSize;
    blocks->checkfn = checkfn;
    blocks->mode = 0;
    zlib_blocks_reset_local(blocks, stream, 0);
    return blocks;
}

INCLUDE_ASM("asm/us/main/nonmatchings/2B800", func_8003B6AC);
