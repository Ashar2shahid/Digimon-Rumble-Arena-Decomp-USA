#include "game_sdk_memcpy.h"
#include "common.h"
#include "zlib_113.h"

/* Altered zlib 1.1.3 routines, adapted to the game's symbols.
 * Copyright (C) 1995-1998 Mark Adler; license in docs/licenses/ZLIB-1.1.3.txt.
 */


extern void func_8003CD7C(void *codes, ZlibStream *stream);

/* inflate_blocks_reset */
void func_8003C2B8(ZlibBlockState *blocks, ZlibStream *stream, u32 *check) {
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

/* inflate_blocks_free */
s32 func_8003C378(ZlibBlockState *blocks, ZlibStream *stream) {
    func_8003C2B8(blocks, stream, 0);
    stream->zfree(stream->opaque, blocks->window);
    stream->zfree(stream->opaque, blocks->hufts);
    stream->zfree(stream->opaque, blocks);
    return 0;
}


/* inflate_set_dictionary */
/* Truthful SDK return declaration changes allocation; retain retail ASM pending recovery. */
INCLUDE_ASM("asm/us/main/nonmatchings/2C800", func_8003C46C);

/* inflate_blocks_sync_point */
s32 func_8003C4B0(ZlibBlockState *blocks) {
    return blocks->mode == 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/2C800", func_8003C4C4);
