#include "common.h"
#include "zlib_113.h"
#include "game_sdk_memcpy.h"

/* Altered zlib 1.1.3 routines, adapted to game symbols and target types.
 * inflate_flush: infutil.c, Copyright (C) 1995-1998 Mark Adler.
 * See docs/licenses/ZLIB-1.1.3.txt for the original notice. */
extern const char D_800643B4[];


/* inflate_trees_bits: altered zlib1.1.3 inftrees.c, Mark Adler. */
extern char D_80019DE8[];
extern char D_80019E10[];
extern s32 func_8003D218(u32 *lengths, u32 count, u32 simple,
    const u32 *bases, const u32 *extra, void **table, u32 *bits,
    void *hufts, u32 *used, u32 *work);

s32 func_8003D9F4(u32 *lengths, u32 *bits, void **table,
    void *hufts, ZlibStream *stream) {
    s32 result;
    u32 used = 0;
    u32 *work = (u32 *)stream->zalloc(stream->opaque, 19, sizeof(u32));
    if (work == 0) {
        return -4;
    }
    result = func_8003D218(lengths, 19, 19, 0, 0, table, bits, hufts, &used, work);
    if (result == -3) {
        stream->msg = D_80019DE8;
    } else if (result == -5 || *bits == 0) {
        stream->msg = D_80019E10;
        result = -3;
    }
    stream->zfree(stream->opaque, work);
    return result;
}


/* Actual initialized fixed-table bit limits; separate from the four-byte sync marker. */
u32 D_800643A8 = 9;
u32 D_800643AC = 5;
extern u8 D_8005FE08[0x1000];
extern u8 D_80060E08[0x100];

/* inflate_trees_fixed: altered zlib1.1.3 inftrees.c. */
s32 func_8003DB04(u32 *literalBits, u32 *distanceBits,
    void **literalTable, void **distanceTable, ZlibStream *stream) {
    *literalBits = D_800643A8;
    *distanceBits = D_800643AC;
    *literalTable = D_8005FE08;
    *distanceTable = D_80060E08;
    return 0;
}


s32 func_8003DB38(ZlibBlockState *s, ZlibStream *z, s32 r) {
    u32 n;
    u8 *p;
    u8 *q;

    p = z->next_out;
    q = s->read;

    /* as far as the end of the window */
    n = (q <= s->write ? s->write : s->end) - q;
    if (n > z->avail_out) {
        n = z->avail_out;
    }
    if (n != 0 && r == (-5)) {
        r = 0;
    }
    z->avail_out -= n;
    z->total_out += n;
    if (s->checkfn != NULL) {
        z->adler = s->check = s->checkfn(s->check, q, n);
    }
    func_8003DF5C(p, q, n);
    p += n;
    q += n;

    /* then from the start of the window, when it wrapped */
    if (q == s->end) {
        q = s->window;
        if (s->write == s->end) {
            s->write = s->window;
        }
        n = s->write - q;
        if (n > z->avail_out) {
            n = z->avail_out;
        }
        if (n != 0 && r == (-5)) {
            r = 0;
        }
        z->avail_out -= n;
        z->total_out += n;
        if (s->checkfn != NULL) {
            z->adler = s->check = s->checkfn(s->check, q, n);
        }
        func_8003DF5C(p, q, n);
        p += n;
        q += n;
    }
    z->next_out = p;
    s->read = q;
    return r;
}



const char *func_8003DCDC(void) {
    return D_800643B4;
}

/* zError: altered zlib1.1.3 zutil.c, Gailly/Adler. */
extern const char *D_80060F4C[10];
const char *func_8003DCE8(s32 error) {
    return D_80060F4C[2U - (u32)error];
}

INCLUDE_ASM("asm/us/main/nonmatchings/2E000", func_8003DD0C);

INCLUDE_ASM("asm/us/main/nonmatchings/2E000", func_8003DD30);

INCLUDE_ASM("asm/us/main/nonmatchings/2E000", func_8003DD50);

INCLUDE_ASM("asm/us/main/nonmatchings/2E000", func_8003DE10);
INCLUDE_ASM("asm/us/main/nonmatchings/2E000", func_8003DE68);

INCLUDE_ASM("asm/us/main/nonmatchings/2E000", func_8003DEC4);

void func_8003DEE4(void) {
}

/* libc2 bzero: retail's `if (n <= 0) return 0` jumps to the shared tail
 * .L8003DF14 (0x8003DF14), an epilogue gcc shared across the original libc
 * translation unit; a single-function C compile can only emit a local `j`. */
INCLUDE_ASM("asm/us/main/nonmatchings/2E000", func_8003DEEC);

/* libc bcmp (PSY-Q 4.7; cc1 gcc-2.7.2) */
INCLUDE_ASM("asm/us/main/nonmatchings/2E000", func_8003DF1C);

/* libc2 memcpy (PSY-Q 4.7; cc1 gcc-2.7.2) */
INCLUDE_ASM("asm/us/main/nonmatchings/2E000", func_8003DF5C);
