#ifndef GAME_MATRIX_COMPONENTS_H
#define GAME_MATRIX_COMPONENTS_H
#include "game_vector_words.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Word-backed destination storage: at least eight words for init/translation,
 * at least five for scale. Exactly three source components are read. */
u32 *func_800266A8(u32 *, const MathVector3 *);
u32 *func_8002671C(u32 *, const MathVector3 *);
u32 *func_8002674C(u32 *, const s16 *);
s32 *func_8002677C(s32 *, const MathVector3 *);
s32 *func_8002679C(s32 *, const s16 *);
#ifdef __cplusplus
}
#endif
#endif
