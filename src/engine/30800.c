#include "common.h"

extern u32 D_800621D8;

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_80040000);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_80040008);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_80040188);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_80040234);

/* libetc SetVideoMode: returns the previous value.  Slot 30800 is built with
 * -G8, so cc1 emits the bare symbolic store and maspsx expands it through $at
 * with the store in the `jr` delay slot (external/maspsx-at-store-delay-slot.patch). */
INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_8004025C);

/* libetc GetVideoMode */
INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_80040270);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_8004028C);

/* libapi ExitCriticalSection: enter critical section (syscall 2). */
INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_8004034C);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_8004035C);

/* BIOS syscall stubs (0xB0/0xC0 thunks); the instruction sequence matches
 * inside LIBAPI's SC2B module (SetConf patch blob), so no unique lib symbol
 * owns them. */
INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_8004036C);
INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_800405BC);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_800405D8);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_800405F4);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_80040610);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_8004062C);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_80040648);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_8004067C);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_8004068C);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_80040698);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_800406CC);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_800406FC);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_8004075C);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_800407DC);


INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_80040868);



INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_800408CC);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_8004094C);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_800409DC);

INCLUDE_ASM("asm/us/main/nonmatchings/30800", func_80040A8C);
