#include "game_heap_wrappers.h"
#include "common.h"
#include "resource_loader.h"
#include "psx.h"

extern u8 *func_8002B170(u32);
extern u8 *func_8002B1DC(u32);
extern void *func_8003DEEC(void *, s32);
extern u32 D_80114210;
extern s32 func_8005858C(void *);
extern TIM_IMAGE *func_8005859C(TIM_IMAGE *);
extern s32 func_80055B04(RECT *, u32 *);
extern s32 func_80055858(s32);






void func_80027858(u8 *state) {
    func_8003DEEC(state, 0x30);
    *(s32 *)(state + 0xC) = -1;
}


void func_80027888(u8 *state) {
    *(u32 *)(state + 0x14) -= 1U;
    if (*(s32 *)(state + 0x14) < 0) {
        *(s32 *)(state + 0x14) = 0;
        *(s32 *)(state + 0xC) = -1;
    }
    switch (*(s32 *)(state + 0xC)) {
    case 0:
        break;
    case 1:
        state[0x24] = (s32)((s64)*(s32 *)(state + 0x1C) * *(s32 *)(state + 0x14)) / *(s32 *)(state + 0x18);
        state[0x25] = (s32)((s64)*(s32 *)(state + 0x20) * *(s32 *)(state + 0x14)) / *(s32 *)(state + 0x18);
        break;
    case 2: {
        s32 factor = (s32)(*(u32 *)(state + 0x18) - *(u32 *)(state + 0x14));
        state[0x24] = (s32)((s64)*(s32 *)(state + 0x1C) * factor) / *(s32 *)(state + 0x18);
        state[0x25] = (s32)((s64)*(s32 *)(state + 0x20) * factor) / *(s32 *)(state + 0x18);
        break;
    }
    default:
        state[0x24] = 0;
        state[0x25] = 0;
        break;
    }
}

__asm__(".globl func_800278DC\n.set func_800278DC, func_80027888 + 0x54\n.size func_800278DC, 0x6C");
__asm__(".globl func_80027948\n.set func_80027948, func_80027888 + 0xC0\n.size func_80027948, 0x38");






void func_80027980(u8 *state, u32 mode, u8 first, u8 second, u32 frames, s32 priority) {
    if (*(s32 *)(state + 0x14) != 0 && priority < *(s32 *)(state + 0x10)) {
        return;
    }
    *(s32 *)(state + 0x10) = priority;
    *(u32 *)(state + 0xC) = mode;
    if (mode < 2) {
        state[0x24] = first;
        state[0x25] = second;
    } else {
        state[0x24] = 0;
        state[0x25] = 0;
    }
    *(u32 *)(state + 0x1C) = first;
    *(u32 *)(state + 0x20) = second;
    *(u32 *)(state + 0x14) = frames;
    *(u32 *)(state + 0x18) = frames;
}

__asm__(".globl func_800279B4\n.set func_800279B4, func_80027980 + 0x34\n.size func_800279B4, 0x34");


void func_800279E8(u8 *state) {
    *(s32 *)(state + 0xC) = -1;
    state[0x24] = 0;
    state[0x25] = 0;
}
u32 func_800279FC(void) {
    return D_80114210;
}

extern char D_1[];
extern s8 D_8005FD18[];
extern s32 func_8003E0EC(s8 *, s8 *);
extern s8 *func_8003E15C(s8 *, s8 *);
extern u32 func_80035094(s8 *);
extern u8 *func_8002B1DC(u32);
extern s32 func_80034330(u8 *, s8 *, s32, u32);
extern void func_8004028C(void);

void func_80027A0C(void *arg0, s8 *arg1) {
    u8 *temp_v0;

    if ((D_1 != (char *)0) && (func_8003E0EC(D_8005FD18, arg1) != 0)) {
        func_8003E15C(D_8005FD18, arg1);
        temp_v0 = func_8002B1DC(func_80035094(arg1));
        func_80034330(temp_v0, arg1, 0, 0U);
        func_80028004(arg0, temp_v0 + 8);
        func_8002B2B4(temp_v0);
        func_8004028C();
    }
}

void func_80027AB0(void *data) {
    TIM_IMAGE image;
    func_8005858C(data);
    if (func_8005859C(&image) != NULL) {
        if (image.caddr != NULL) {
            func_80055B04(image.crect, image.caddr);
        }
        if (image.paddr != NULL) {
            func_80055B04(image.prect, image.paddr);
        }
        func_80055858(0);
    }
}

__asm__(".globl func_80027AD0\n.set func_80027AD0, func_80027AB0 + 0x20\n.size func_80027AD0, 0x28");
__asm__(".globl func_80027AF8\n.set func_80027AF8, func_80027AB0 + 0x48\n.size func_80027AF8, 0x28");





void func_80027B20(void *data) {
    TIM_IMAGE image;
    func_8005858C(data);
    while (func_8005859C(&image) != NULL) {
        if (image.caddr != NULL) {
            func_80055B04(image.crect, image.caddr);
        }
        if (image.paddr != NULL) {
            func_80055B04(image.prect, image.paddr);
        }
        func_80055858(0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/18000", func_80027B98);

u8 *func_80027C14(void *path) {
    return func_80027CB4(path, func_8002B1DC, func_8002B170);
}

u8 *func_80027C40(void *path) {
    return func_80027CB4(path, func_8002B170, func_8002B1DC);
}

u8 *func_80027C6C(void *path) {
    return func_80027D70(path, func_8002B170);
}

u8 *func_80027C90(void *path) {
    return func_80027D70(path, func_8002B1DC);
}

extern u8 D_800641D4[4];
extern s32 func_8003DF1C(const void *, const void *, u32);
extern void func_8003DF9C(void *, const void *, u32);

u8 *func_80027CB4(s8 *path, ResourceAllocate temporary, ResourceAllocate result) {
    u32 bytes = func_80035094(path);
    u8 *packed = func_80027D70(path, temporary);
    u8 *output;
    if (func_8003DF1C(packed, D_800641D4, 4) == 0) {
        output = result(*(u32 *)(packed + 4));
        func_80028004(output, packed + 8);
    } else {
        output = result(bytes);
        func_8003DF9C(output, packed, bytes);
    }
    func_8002B2B4(packed);
    return output;
}

u8 *func_80027D70(s8 *path, ResourceAllocate allocate) {
    u32 bytes = func_80035094(path);
    u8 *buffer = allocate(bytes);
    func_80034330(buffer, path, 0, bytes);
    return buffer;
}

/* Former split symbol is the return's stack-restoration delay slot. */
__asm__(".globl func_80027DD4\n.set func_80027DD4, func_80027D70 + 0x64\n.size func_80027DD4, 4");

extern s32 func_80034464(u8 *, s8 *, u32, u32);

s32 func_80027DD8(s8 *path, u8 **result) {
    u32 bytes = func_80035094(path);
    u8 *buffer = func_8002B1DC(bytes);
    s32 status;
    func_80035080(func_80027E6C);
    func_800350DC(result);
    status = func_80034464(buffer, path, 0, bytes);
    func_80035080(NULL);
    *result = NULL;
    if (status >= 0) {
        return 0;
    }
    return -1;
}

void func_80027E6C(u8 *packed, u32 bytes, s8 *path, void *user) {
    u8 *output;
    if (func_8003DF1C(packed, D_800641D4, 4) == 0) {
        output = func_8002B170(*(u32 *)(packed + 4));
        func_80028004(output, packed + 8);
    } else {
        output = func_8002B170(bytes);
        func_8003DF9C(output, packed, bytes);
    }
    func_8002B2B4(packed);
    *(u8 **)user = output;
}


INCLUDE_ASM("asm/us/main/nonmatchings/18000", func_80027F0C);





u8 *func_80027FB0(u8 *packed) {
    u8 *output;
    func_8003DF1C(packed, D_800641D4, 4);
    output = func_8002B170(*(u32 *)(packed + 4));
    func_80028004(output, packed + 8);
    return output;
}

/* Former sector split is this function's stack-restoration delay slot. */
__asm__(".globl func_80028000\n.set func_80028000, func_80027FB0 + 0x50\n.size func_80028000, 4");

