#include "common.h"
#include "zlib_113.h"

/* Altered zlib1.1.3 inflate.c, Copyright(C)1995-1998 Mark Adler.
 * Adapted to game symbols; notice docs/licenses/ZLIB-1.1.3.txt. */

extern void *func_8003DD0C(void *opaque, u32 items, u32 size);
extern void func_8003DD30(void *opaque, void *address);
extern s32 func_8003C378(ZlibBlockState *, ZlibStream *);
extern void func_8003C2B8(ZlibBlockState *, ZlibStream *, u32 *);
extern u32 func_8003B3C0(u32, const u8 *, u32);
extern ZlibBlockState *func_8003B588(ZlibStream *, u32 (*)(u32, const u8 *, u32), u32);

static inline s32 inflateResetInline(ZlibStream *z) {
    if (z == NULL || z->state == NULL) {
        return (-2);
    }
    z->total_in = z->total_out = 0;
    z->msg = NULL;
    z->state->mode = z->state->nowrap ? 7 : 0;
    func_8003C2B8(z->state->blocks, z, NULL);
    return 0;
}

/* inflateEnd: frees all the memory of the stream. */
static inline s32 inflateEndInline(ZlibStream *z) {
    if (z == NULL || z->state == NULL || z->zfree == NULL) {
        return (-2);
    }
    if (z->state->blocks != NULL) {
        func_8003C378(z->state->blocks, z);
    }
    z->zfree(z->opaque, z->state);
    z->state = NULL;
    return 0;
}

/* func_8003A834: sets up a stream to decompress with a window of 2^w bytes,
 * or of 2^-w bytes without the zlib header and check when w is negative. */
s32 func_8003A834(ZlibStream *z, s32 w, const char *version, s32 streamSize) {
    if (version == NULL || version[0] != '1' || streamSize != sizeof(ZlibStream)) {
        return (-6);
    }
    if (z == NULL) {
        return (-2);
    }
    z->msg = NULL;
    if (z->zalloc == NULL) {
        z->zalloc = func_8003DD0C;
        z->opaque = NULL;
    }
    if (z->zfree == NULL) {
        z->zfree = func_8003DD30;
    }
    if ((z->state = (ZlibInflateState *)z->zalloc(z->opaque, 1, sizeof(ZlibInflateState))) == NULL) {
        return (-4);
    }
    z->state->blocks = NULL;
    z->state->nowrap = 0;
    if (w < 0) {
        w = (s32)(0U - (u32)w);
        z->state->nowrap = 1;
    }
    if (w < 8 || w > 15) {
        inflateEndInline(z);
        return (-2);
    }
    z->state->wbits = w;
    if ((z->state->blocks = func_8003B588(z, z->state->nowrap ? NULL : func_8003B3C0, 1U << w))
        == NULL) {
        inflateEndInline(z);
        return (-4);
    }
    inflateResetInline(z);
    return 0;
}



extern s32 func_8003B6AC(ZlibBlockState *, ZlibStream *, s32);
extern char D_800199AC[];
extern char D_800199C8[];
extern char D_800199DC[];
extern char D_800199F4[];
extern char D_80019A04[];

/* inflate()'s byte input, which counts what it reads in the stream */
#define NEEDBYTE                \
    {                           \
        if (z->avail_in == 0) {  \
            return r;           \
        }                       \
        r = f;                  \
    }
#define NEXTBYTE (z->avail_in--, z->total_in++, *z->next_in++)

/* inflate: decompresses as much as the input and output allow; f is
 * (4) when all the input is there and the output has room for it all. */
s32 func_8003AA78(ZlibStream *z, s32 f) {
    s32 r;
    u32 b;

    if (z == NULL || z->state == NULL || z->next_in == NULL) {
        return (-2);
    }
    f = f == (4) ? (-5) : (0);
    r = (-5);
    while (1) {
        switch (z->state->mode) {
        case (0):
            NEEDBYTE
            if (((z->state->sub.method = NEXTBYTE) & 0xF) != (8)) {
                z->state->mode = (13);
                z->msg = D_800199AC;
                z->state->sub.marker = (5);
                break;
            }
            if ((z->state->sub.method >> 4) + 8 > z->state->wbits) {
                z->state->mode = (13);
                z->msg = D_800199C8;
                z->state->sub.marker = (5);
                break;
            }
            z->state->mode = (1);
        case (1):
            NEEDBYTE
            b = NEXTBYTE;
            /* the method and flag bytes, as a 16-bit number, are a multiple of 31 */
            if (((z->state->sub.method << 8) + b) % 31) {
                z->state->mode = (13);
                z->msg = D_800199DC;
                z->state->sub.marker = (5);
                break;
            }
            if (!(b & (32))) {
                z->state->mode = (7);
                break;
            }
            z->state->mode = (2);
        case (2):
            NEEDBYTE
            z->state->sub.check.need = (u32)NEXTBYTE << 24;
            z->state->mode = (3);
        case (3):
            NEEDBYTE
            z->state->sub.check.need += (u32)NEXTBYTE << 16;
            z->state->mode = (4);
        case (4):
            NEEDBYTE
            z->state->sub.check.need += (u32)NEXTBYTE << 8;
            z->state->mode = (5);
        case (5):
            NEEDBYTE
            z->state->sub.check.need += (u32)NEXTBYTE;
            z->adler = z->state->sub.check.need;
            z->state->mode = (6);
            return (2);
        case (6):
            z->state->mode = (13);
            z->msg = D_800199F4;
            z->state->sub.marker = 0; /* inflateSync can try */
            return (-2);
        case (7):
            r = func_8003B6AC(z->state->blocks, z, r);
            if (r == (-3)) {
                z->state->mode = (13);
                z->state->sub.marker = 0; /* inflateSync can try */
                break;
            }
            if (r == (0)) {
                r = f;
            }
            if (r != (1)) {
                return r;
            }
            r = f;
            func_8003C2B8(z->state->blocks, z, &z->state->sub.check.was);
            if (z->state->nowrap) {
                z->state->mode = (12);
                break;
            }
            z->state->mode = (8);
        case (8):
            NEEDBYTE
            z->state->sub.check.need = (u32)NEXTBYTE << 24;
            z->state->mode = (9);
        case (9):
            NEEDBYTE
            z->state->sub.check.need += (u32)NEXTBYTE << 16;
            z->state->mode = (10);
        case (10):
            NEEDBYTE
            z->state->sub.check.need += (u32)NEXTBYTE << 8;
            z->state->mode = (11);
        case (11):
            NEEDBYTE
            z->state->sub.check.need += (u32)NEXTBYTE;
            if (z->state->sub.check.was != z->state->sub.check.need) {
                z->state->mode = (13);
                z->msg = D_80019A04;
                z->state->sub.marker = (5);
                break;
            }
            z->state->mode = (12);
        case (12):
            return (1);
        case (13):
            return (-3);
        default:
            return (-2);
        }
    }
}

#undef NEEDBYTE
#undef NEXTBYTE
