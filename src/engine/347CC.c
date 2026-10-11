#include "common.h"
#include "psx.h"

extern u32 D_80116E30;
extern u32 D_80116E34;
extern u32 D_80116E38;
extern u32 D_80116E3C;
extern s32 D_800626C4;
extern s32 func_800444BC(s32, void *);
INCLUDE_ASM("asm/us/main/nonmatchings/347CC", func_80043FCC);

INCLUDE_ASM("asm/us/main/nonmatchings/347CC", func_8004418C);

INCLUDE_ASM("asm/us/main/nonmatchings/347CC", func_8004422C);

INCLUDE_ASM("asm/us/main/nonmatchings/347CC", func_8004430C);

INCLUDE_ASM("asm/us/main/nonmatchings/347CC", func_8004434C);

/* libds setters: -G8 emits bare symbolic stores; maspsx expands each through
 * $at and places it in the `jr` delay slot. */
INCLUDE_ASM("asm/us/main/nonmatchings/347CC", func_800443C8);

INCLUDE_ASM("asm/us/main/nonmatchings/347CC", func_800443D4);

INCLUDE_ASM("asm/us/main/nonmatchings/347CC", func_800443E0);

INCLUDE_ASM("asm/us/main/nonmatchings/347CC", func_800443EC);
