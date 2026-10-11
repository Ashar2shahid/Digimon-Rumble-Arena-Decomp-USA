#include "common.h"
#include "zlib_113.h"

/* Altered zlib 1.1.3 routine adapted to target symbols and stream layout.
 * Copyright (C) 1995-1998 Jean-loup Gailly and Mark Adler.
 * See docs/licenses/ZLIB-1.1.3.txt for the original license notice.
 */





typedef struct ZlibCodesState {
    s32 mode;
    u32 len;
    union {
        struct { void *tree; u32 need; } code;
        u32 lit;
        struct { u32 get; u32 dist; } copy;
    } sub;
    u8 lbits;
    u8 dbits;
    u16 padding;
    void *ltree;
    void *dtree;
} ZlibCodesState;

typedef char ZlibCodesState_size_is_0x1C[(sizeof(ZlibCodesState) == 0x1C) ? 1 : -1];

/* inflate_codes_new */
ZlibCodesState *func_8003CD04(u32 lbits, u32 dbits, void *ltree, void *dtree, ZlibStream *stream) {
    ZlibCodesState *codes = (ZlibCodesState *)stream->zalloc(stream->opaque, 1, sizeof(ZlibCodesState));
    if (codes != 0) {
        codes->mode = 0;
        codes->lbits = (u8)lbits;
        codes->dbits = (u8)dbits;
        codes->ltree = ltree;
        codes->dtree = dtree;
    }
    return codes;
}

/* inflate_codes_free */
void func_8003CD7C(void *codes, ZlibStream *stream) {
    stream->zfree(stream->opaque, codes);
}

INCLUDE_ASM("asm/us/main/nonmatchings/2D000", func_8003CDA8);

