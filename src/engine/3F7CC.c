#include "common.h"
#include "psx.h"
extern u16 D_8011A368;
INCLUDE_ASM("asm/us/main/nonmatchings/3F7CC", func_8004EFCC);


extern void func_8004EFCC(s32);



INCLUDE_ASM("asm/us/main/nonmatchings/3F7CC", func_8004F0BC);

/* libsnd VRAM 0x800587CC (SsUtReverbOff) / 0x800587EC (SsUtReverbOn). */
INCLUDE_ASM("asm/us/main/nonmatchings/3F7CC", func_8004F0FC);

INCLUDE_ASM("asm/us/main/nonmatchings/3F7CC", func_8004F11C);

INCLUDE_ASM("asm/us/main/nonmatchings/3F7CC", func_8004F13C);

INCLUDE_ASM("asm/us/main/nonmatchings/3F7CC", func_8004F30C);

INCLUDE_ASM("asm/us/main/nonmatchings/3F7CC", func_8004F39C);

INCLUDE_ASM("asm/us/main/nonmatchings/3F7CC", func_8004F60C);

/* The trailing pad nop here keeps func_8004F7EC at its retail boundary. */
INCLUDE_ASM("asm/us/main/nonmatchings/3F7CC", func_8004F7DC);


INCLUDE_ASM("asm/us/main/nonmatchings/3F7CC", func_8004F7EC);
