#include "common.h"

extern s32 D_800622E4;

/* libds DsQueueLen: return the queue length and set it to the new value.  The
 * bare symbolic store is expanded through $at by maspsx with the store in the
 * `jr` delay slot (external/maspsx-at-store-delay-slot.patch); shipped 2.8.1
 * reproduces it where the slot's 2.7.2 cc1 does not. */
INCLUDE_ASM("asm/us/main/nonmatchings/3354C", func_80042D4C);
