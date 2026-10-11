#include "common.h"

extern u32 D_80062158;
extern u32 D_80062160;
extern u16 D_800610D2;

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F800);

/* libetc VRAM 0x80046A20 (INTR.VSyncCallbacks): call the 6th callback slot
 * (offset 0x14) of the interrupt-handler table pointed at by D_80062158.  */
INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F820);

/* libetc VRAM 0x80046A50 (INTR.StopCallback): table slot 4 (offset 0x10). */
INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F850);

/* libetc VRAM 0x80046A80 (INTR.RestartCallback): table slot 6 (offset 0x18). */
INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F880);

/* libetc VRAM 0x80046AB0 (INTR.CheckCallback): read the interrupt-active flag. */
INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F8B0);

/* libetc VRAM 0x80046AC0 (INTR.GetIntrMask): read the 16-bit interrupt mask
 * at the head of the handler table pointed at by D_80062160. */
INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F8C0);

/* libetc VRAM 0x80046AD8 (16-bit SetIntrMask): store mask, return old value. */
INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F8D8);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F8F0);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F93C);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003F9C8);


INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003FB98);


INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003FCE0);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003FD80);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003FDF8);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003FE1C);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003FE58);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003FE9C);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003FEF4);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003FF60);

INCLUDE_ASM("asm/us/main/nonmatchings/30000", func_8003FF8C);
