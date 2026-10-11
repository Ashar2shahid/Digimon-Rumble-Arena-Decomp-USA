#ifndef GAME_VECTOR_WORDS_H
#define GAME_VECTOR_WORDS_H
#include "common.h"
typedef struct MathWords2 { u32 words[2]; } MathWords2;
typedef struct MathVector3 { s32 x; s32 y; s32 z; } MathVector3;
MathWords2 *func_800261B8(MathWords2 *, const MathWords2 *);
MathVector3 *func_800262AC(MathVector3 *, const MathVector3 *);
MathVector3 *func_800262FC(MathVector3 *, const MathVector3 *);
MathVector3 *func_80026334(MathVector3 *, const MathVector3 *, const MathVector3 *);
MathVector3 *func_8002636C(MathVector3 *, const MathVector3 *);
MathVector3 *func_800263A4(MathVector3 *, const MathVector3 *, const MathVector3 *);
s32 func_800263FC(const MathVector3 *);
u32 func_80026438(const MathVector3 *);
MathWords2 *func_80026918(MathWords2 *, const MathWords2 *);
s16 func_80026A30(u32);
#endif
