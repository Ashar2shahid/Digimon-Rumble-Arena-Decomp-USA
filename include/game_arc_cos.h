#ifndef GAME_ARC_COS_H
#define GAME_ARC_COS_H
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Signed 4.12 cosine values -4096..4096 map to angles0..2048. */
extern s16 D_8001493C[8193];
s32 func_80026168(s32 cosine);
#ifdef __cplusplus
}
#endif
#endif
