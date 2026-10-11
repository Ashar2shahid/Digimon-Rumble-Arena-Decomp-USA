#include "common.h"
#include "zlib_113.h"

/* Altered zlib1.1.3 inftrees.c, Copyright (C)1995-1998 Mark Adler.
 * Adapted to game symbols; original notice docs/licenses/ZLIB-1.1.3.txt. */


INCLUDE_ASM("asm/us/main/nonmatchings/2D800", func_8003D218);

extern const u32 D_80019C00[], D_80019C7C[], D_80019CF8[], D_80019D70[];
extern char D_80019E34[], D_80019E58[], D_80019E78[], D_80019E98[], D_80019EB4[];
extern s32 func_8003D218(u32 *, u32, u32, const u32 *, const u32 *, void **, u32 *, void *, u32 *, u32 *);

s32 func_8003D7F0(u32 nl, u32 nd, u32 *c, u32 *bl, u32 *bd, void **tl, void **td,
                  void *hp, ZlibStream *z) {
    s32 r;
    u32 hn = 0; /* hufts used in hp */
    u32 *v; /* work area for func_8003D218 */

    if ((v = (u32 *)z->zalloc(z->opaque, 288, sizeof(u32))) == NULL) {
        return (-4);
    }
    r = func_8003D218(c, nl, 257, D_80019C00, D_80019C7C, tl, bl, hp, &hn, v);
    if (r != 0 || *bl == 0) {
        if (r == (-3)) {
            z->msg = D_80019E34;
        } else if (r != (-4)) {
            z->msg = D_80019E58;
            r = (-3);
        }
        z->zfree(z->opaque, v);
        return r;
    }
    r = func_8003D218(c + nl, nd, 0, D_80019CF8, D_80019D70, td, bd, hp, &hn, v);
    if (r != 0 || (*bd == 0 && nl > 257)) {
        if (r == (-3)) {
            z->msg = D_80019E78;
        } else if (r == (-5)) {
            z->msg = D_80019E98;
            r = (-3);
        } else if (r != (-4)) {
            z->msg = D_80019EB4;
            r = (-3);
        }
        z->zfree(z->opaque, v);
        return r;
    }
    z->zfree(z->opaque, v);
    return 0;
}
