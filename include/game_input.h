#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The first word is the preserved controller-manager context argument.
 * Negative selectors combine both controller entries. */
s32 func_80026F68(s32 context, s32 selector, s32 fieldOffset);
s32 func_80026FE4(s32 context, s32 selector);
s32 func_80027004(s32 context, s32 selector);
s32 func_80027024(s32 context, s32 selector);
s32 func_80027044(s32 context, s32 selector);
s32 func_800271DC(u32 buttons);
void func_80027588(void *controller, u32 delay, u32 interval);
void func_80026E0C(s32 context, u32 delay, u32 interval);

#ifdef __cplusplus
}
#endif

#endif
