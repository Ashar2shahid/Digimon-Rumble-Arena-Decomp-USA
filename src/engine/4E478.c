#include "common.h"
#include "psx.h"
INCLUDE_ASM("asm/us/main/nonmatchings/4E478", func_8005DC78);





extern u32 D_80064118;
extern void func_8005EB7C(void);
extern void func_8005EDAC(void);
extern s32 func_8004033C(void);
extern void func_8004037C(s32);
extern void func_8004034C(void);
extern void func_8005EB6C(void);
extern void func_8003F4EC(s32);
extern void func_8005EB5C(s32);
extern void func_8005ED6C(void);
extern void func_8005EC68(void);
extern void func_8005ECFC(void);
extern void func_8005EB8C(void);


INCLUDE_ASM("asm/us/main/nonmatchings/4E478", func_8005E5FC);

INCLUDE_ASM("asm/us/main/nonmatchings/4E478", func_8005E60C);
INCLUDE_ASM("asm/us/main/nonmatchings/4E478", func_8005E67C);

/* Card setup helper; retains its entry argument for InitCARD2 when enabled. */
INCLUDE_ASM("asm/us/main/nonmatchings/4E478", func_8005E68C);

/* libcard StartCARD. */
INCLUDE_ASM("asm/us/main/nonmatchings/4E478", func_8005E71C);

/* libcard StopCARD: shut the card driver down and report success. */
INCLUDE_ASM("asm/us/main/nonmatchings/4E478", func_8005E764);

/* libapi SetInitPadFlag: slot 4E800 is built with -G8, so the bare symbolic
 * store is expanded through $at by maspsx, with the store in the `jr` delay
 * slot (external/maspsx-at-store-delay-slot.patch). */
INCLUDE_ASM("asm/us/main/nonmatchings/4E478", func_8005E78C);

/* libapi ReadInitPadFlag */
INCLUDE_ASM("asm/us/main/nonmatchings/4E478", func_8005E798);
