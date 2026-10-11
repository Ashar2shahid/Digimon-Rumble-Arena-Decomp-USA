#include "common.h"

/* The libcd register pointers at 0x800625A4/A8/B0 and 0x800625B4 (splat named
 * the latter `.L800625B4` — it collides with a code label of the same address,
 * so reach it by an assembler alias) plus the 0x800625B8 device pointer. */
extern u8 *D_800625A4;
extern u8 *D_800625A8;
extern u8 *D_800625B0;
extern u8 *D_800625B4 __asm__("D_800625B4");
extern u8 *D_800625B8;

INCLUDE_ASM("asm/us/main/nonmatchings/32948", func_80042148);

/* libcd CD_vol: deposit a 4-byte volume parameter block into the command /
 * parameter registers (each store goes through a pointer held in RAM). */
INCLUDE_ASM("asm/us/main/nonmatchings/32948", func_80042554);

INCLUDE_ASM("asm/us/main/nonmatchings/32948", func_800425DC);

/* libcd CD_initvol: program the CD-DSP volume registers if they are still
 * untouched, then issue the same 4-byte volume block as CD_vol. */
INCLUDE_ASM("asm/us/main/nonmatchings/32948", func_800426B0);

INCLUDE_ASM("asm/us/main/nonmatchings/32948", func_800427A0);
