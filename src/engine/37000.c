#include "common.h"

extern s32 func_800443F8(s32);
extern s32 func_80043FCC(void);
extern s32 func_8004692C(void);
extern s32 func_80046A4C(void);
extern void func_80045198(void);
extern void func_80042EB8(void);
extern void func_800462E0(void);
extern void func_80045210(void);
extern void func_80041E80(s32, s32);
extern void func_8003F7BC(s32, s32);
extern void func_8004446C(void);
extern s32 D_80119244;
extern s32 D_80119248;

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046800);

/* libds DS_sync: flush the drive path with sync mode 1. */
INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_8004682C);

/* libds: call func_8004446C. */
INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_8004685C);

/* libds DsFlush: flush every pending drive channel. */
INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_8004687C);

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_800468BC);

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_8004690C);

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_8004692C);

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046A2C);

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046A4C);

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046B3C);

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046BFC);

/* libds DsPosToInt = libcd CdPosToInt; join the 0x40-byte fragment with its
 * continuation to form the 0x80-byte function at 0x80046C4C. */
INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046C4C);


INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046D2C);

/* libds callback setters: store the handler, returning the previous one.
 * The address is materialised once into a base register, matching retail. */
INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046D9C);

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046DBC);

/* libds DsDataCallback: install the data callback (slot 3). */
INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046E0C);


INCLUDE_ASM("asm/us/main/nonmatchings/37000", func_80046E6C);

