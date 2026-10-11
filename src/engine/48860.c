#include "common.h"
#include "psx.h"

extern void func_8003F7BC(s32 mode, void (*func)(void));
extern void func_80057884(void);
extern void func_8005E764(void);
extern void func_8005E68C(void);
extern void func_8005E71C(void);
extern void func_8005876C(void);
extern void func_80059C50(u32);
extern u32 *D_8011BE30;
extern u32 D_8011BEC8;

INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_80058060);

INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005814C);

INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_80058290);

/* libgpu _GPU_ResetCallback */
INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005838C);

INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_800583B4);

INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_800583DC);

/* libgpu SetDefDispEnv */
INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_800583EC);

/* libgpu GetClut */
INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005842C);

/* libgpu AddPrim */
INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005844C);

INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005848C);

/* libgpu SetDrawMove */
INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_800584BC);

/* libgpu SetDrawLoad */
INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005851C);

/* libgpu OpenTIM */
INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005858C);

INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005859C);

INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_80058600);

/* libmcrd MemCardInit */
INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005871C);

/* wrapper: call func_8005E764. */
INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005874C);

INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_8005876C);

/* libmcrd PullCallbackFunc: hand the saved callback to the event handler. */
INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_800587A4);

INCLUDE_ASM("asm/us/main/nonmatchings/48860", func_800587CC);
