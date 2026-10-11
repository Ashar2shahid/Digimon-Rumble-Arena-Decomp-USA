#include "common.h"
#include "psx.h"
INCLUDE_ASM("asm/us/main/nonmatchings/32FEC", func_800427EC);

extern void func_8003F7BC(s32, s32);



INCLUDE_ASM("asm/us/main/nonmatchings/32FEC", func_800429CC);

/* libapi SetInitPadFlag: slot 33000 is built with -G8 (keeping its 2.7.2 cc1),
 * so the bare symbolic store is expanded through $at by maspsx with the store
 * in the `jr` delay slot (external/maspsx-at-store-delay-slot.patch). */
extern u32 D_80062588;

INCLUDE_ASM("asm/us/main/nonmatchings/32FEC", func_80042B34);

INCLUDE_ASM("asm/us/main/nonmatchings/32FEC", func_80042B40);

INCLUDE_ASM("asm/us/main/nonmatchings/32FEC", func_80042C1C);

extern void func_80041E80();

/* Thin wrapper: jal CD_ready (func_80041E80) with no argument setup. */
INCLUDE_ASM("asm/us/main/nonmatchings/32FEC", func_80042D2C);
