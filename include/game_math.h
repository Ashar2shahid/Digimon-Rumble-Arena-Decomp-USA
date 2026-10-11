#ifndef GAME_MATH_H
#define GAME_MATH_H
#include "psx.h"
/* MATRIX: 18 rotation bytes, 2 ABI padding bytes, three translation words.
 * VECTOR: three component words and one pad word. */
typedef char GameMath_matrix_size_is_32[(sizeof(MATRIX) == 32) ? 1 : -1];
typedef char GameMath_vector_size_is_16[(sizeof(VECTOR) == 16) ? 1 : -1];
#ifdef __cplusplus
extern "C" {
#endif
s32 func_8002384C(const VECTOR *vector);
s32 func_800239CC(const VECTOR *left, const VECTOR *right);
s32 func_80023A14(const VECTOR *left, const VECTOR *right);
MATRIX *func_800249E8(MATRIX *matrix, s32 angle);
MATRIX *func_80024A1C(MATRIX *matrix, s32 angle);
MATRIX *func_80024A50(MATRIX *matrix, s32 angle);
#ifdef __cplusplus
}
#endif
#endif
