#include "common.h"
#include "game_math.h"

MATRIX *func_8002542C(MATRIX *matrix, s32 angle);
MATRIX *func_80025480(MATRIX *matrix, s32 angle);
MATRIX *func_800254CC(MATRIX *matrix, s32 angle);

INCLUDE_ASM("asm/us/main/nonmatchings/15000", func_80024800);


INCLUDE_ASM("asm/us/main/nonmatchings/15000", func_80024844);



MATRIX *func_800249E8(MATRIX *matrix, s32 angle) {
    func_8002542C(matrix, angle);
    matrix->t[0] = 0;
    matrix->t[1] = 0;
    matrix->t[2] = 0;
    return matrix;
}

MATRIX *func_80024A1C(MATRIX *matrix, s32 angle) {
    func_80025480(matrix, angle);
    matrix->t[0] = 0;
    matrix->t[1] = 0;
    matrix->t[2] = 0;
    return matrix;
}


MATRIX *func_80024A50(MATRIX *matrix, s32 angle) {
    func_800254CC(matrix, angle);
    matrix->t[0] = 0;
    matrix->t[1] = 0;
    matrix->t[2] = 0;
    return matrix;
}

INCLUDE_ASM("asm/us/main/nonmatchings/15000", func_80024A84);

INCLUDE_ASM("asm/us/main/nonmatchings/15000", func_80024CA8);

INCLUDE_ASM("asm/us/main/nonmatchings/15000", func_80024D1C);

INCLUDE_ASM("asm/us/main/nonmatchings/15000", func_80024DD0);

INCLUDE_ASM("asm/us/main/nonmatchings/15000", func_80024E4C);

INCLUDE_ASM("asm/us/main/nonmatchings/15000", func_80024E70);

INCLUDE_ASM("asm/us/main/nonmatchings/15000", func_80024E98);

INCLUDE_ASM("asm/us/main/nonmatchings/15000", func_80024EC0);

