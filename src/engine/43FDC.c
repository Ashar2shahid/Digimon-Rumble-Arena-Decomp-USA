#include "common.h"
#include "psx.h"
INCLUDE_ASM("asm/us/main/nonmatchings/43FDC", func_800537DC);

extern s32 func_8005389C(s32);
extern s32 func_8005394C(s32);

extern s32 D_800628F8, D_800628A4, D_800628BC, D_800628F0;

INCLUDE_ASM("asm/us/main/nonmatchings/43FDC", func_8005383C);


/* libsnd VRAM 0x8005D9EC (VS_VTC.SsVabTransCompleted): sign-extend the mode
 * and forward, returning the sign-extended 16-bit result. */
INCLUDE_ASM("asm/us/main/nonmatchings/43FDC", func_8005386C);

INCLUDE_ASM("asm/us/main/nonmatchings/43FDC", func_80053894);

/* LIBSPU.LIB SpuIsTransferCompleted: flag selects blocking or one-shot polling. */
INCLUDE_ASM("asm/us/main/nonmatchings/43FDC", func_8005389C);

INCLUDE_ASM("asm/us/main/nonmatchings/43FDC", func_80053940);


INCLUDE_ASM("asm/us/main/nonmatchings/43FDC", func_8005394C);
