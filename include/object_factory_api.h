#ifndef OBJECT_FACTORY_API_H
#define OBJECT_FACTORY_API_H
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif

/* Explicit caller a1 setup establishes the opaque context even where unused. */
u8 *func_80073F88(u8 *self, u8 *opaqueContext, s32 mode);
u8 *func_8006E1B4(u8 *self, u8 *opaqueContext);
u8 *func_80070240(u8 *self, u8 *context, u16 mode);
u8 *func_8001C3CC(void);
u8 *func_8001C404(void);
u8 *func_8001C434(void);
u8 *func_800282E0(void);
u8 *func_80028378(void);
u8 *func_800283AC(void);

#ifdef __cplusplus
}
#endif
#endif
