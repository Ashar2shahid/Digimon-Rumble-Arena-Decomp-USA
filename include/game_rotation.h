#ifndef GAME_ROTATION_H
#define GAME_ROTATION_H
#include "common.h"

typedef struct { s16 x, y, z, w; } RotationQuaternion;
typedef struct { s16 cos, sin; } RotationTrig;
typedef char RotationQuaternion_size_is_8[(sizeof(RotationQuaternion) == 8) ? 1 : -1];
typedef char RotationTrig_size_is_4[(sizeof(RotationTrig) == 4) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
extern RotationTrig D_8001093C[4096];
RotationQuaternion *func_80025598(RotationQuaternion *, s32);
RotationQuaternion *func_800255D8(RotationQuaternion *, s32);
RotationQuaternion *func_80025618(RotationQuaternion *, s32);
RotationQuaternion *func_80025750(RotationQuaternion *, RotationQuaternion *);
void func_800269C4(RotationQuaternion *);
#ifdef __cplusplus
}
#endif
#endif
