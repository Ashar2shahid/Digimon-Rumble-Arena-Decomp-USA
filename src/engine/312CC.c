#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/312CC", func_80040ACC);


/* libcd StSetMask: slot 312CC is built with -G8, so the three constant stores
 * are bare symbolic stores; maspsx expands each through $at and places the
 * last in the `jr` delay slot (external/maspsx-at-store-delay-slot.patch).  The
 * trailing 4-byte pad nop at 0x80040BA8 is carried at the head of the
 * successor asm stub func_80040BAC.s. */
extern u32 D_80116C20;
extern u32 D_80116BFC;
extern u32 D_80116C1C;

INCLUDE_ASM("asm/us/main/nonmatchings/312CC", func_80040B8C);

INCLUDE_ASM("asm/us/main/nonmatchings/312CC", func_80040BAC);

