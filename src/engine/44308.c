#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053B08);

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053B4C);

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053B7C);

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053C3C);

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053D2C);

/* libgte ApplyMatrix: load the matrix, multiply vector by matrix, store the
 * result (GTE coprocessor instructions; handwritten library asm). */
INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053DCC);

/* libgte SetBackColor (GTE registers 13..15). */
INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053E1C);

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053E3C);

/* libgte SetFarColor, tail (GTE registers 21..23); the split carved the two
 * leading `sll` into func_80053E3C, which stays an INCLUDE_ASM fragment. */
INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053E44);

/* libgte SetGeomOffset (GTE registers 24..25). */
INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053E5C);

/* libgte SetGeomScreen (GTE register 26). */
INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053E7C);

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053E8C);

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053EBC);

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80053EFC);


INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_8005407C);

INCLUDE_ASM("asm/us/main/nonmatchings/44308", func_80054128);
