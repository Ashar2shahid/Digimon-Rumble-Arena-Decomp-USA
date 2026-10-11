#include "common.h"
#include "game_heap.h"
#include "game_heap_wrappers.h"
#include "game_handles.h"
#include "game_sdk_printf.h"

INCLUDE_ASM("asm/us/main/nonmatchings/1B800", func_8002B000);

extern u8 **D_8005FDEC;
extern void func_8002B420(u8 **, u32);

void func_8002B044(void *a0, u32 a1) {
    func_8003A368(&D_80114748, a0, a1);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1B800", func_8002B074);

void func_8002B0CC(void *a0) {
    func_8003A210(&D_80114748);
    func_8003A2A4(&D_80114748, a0);
    func_8003A210(&D_80114748);
}

extern const char D_80019194[];

void func_8002B118(void *base, u32 size) {
    func_8003A368(&D_80114758, base, (s32)size);
    func_8003E2DC(D_80019194, (s32)(size >> 10),
                  (u32)base, (u32)base + size);
}

u8 *func_8002B170(u32 a0) {
    u8 *v0 = func_8003A3A8(&D_80114758, a0);

    if (v0 == NULL) {
        func_8002B420(D_8005FDEC, (u32)func_8003A1D4(&D_80114758) - a0);
    }
    return v0;
}

u8 *func_8002B1DC(u32 a0) {
    u8 *v0 = func_8003A490(&D_80114758, a0);

    if (v0 == NULL) {
        func_8002B420(D_8005FDEC, (u32)func_8003A1D4(&D_80114758) - a0);
    }
    return v0;
}

void *func_8002B248(s32 a0) {
    void *v0 = func_8003A658(&D_80114758, a0);

    if (v0 == NULL) {
        func_8002B420(D_8005FDEC, (u32)func_8003A1D4(&D_80114758) - (u32)a0);
    }
    return v0;
}

void func_8002B2B4(void *a0) {
    func_8003A2A4(&D_80114758, a0);
}

s32 func_8002B2DC(void) {
    return func_8003A1D4(&D_80114758);
}

s32 func_8002B300(void) {
    return D_80114758.count;
}

s32 func_8002B310(void) {
    return func_8003A72C(&D_80114758);
}

void func_8002B334(void *ptr, s32 size) {
    func_8003A764(&D_80114758, ptr, size);
}

u8 *func_8002B364(u32 a0) {
    u8 *v0 = func_8003A3A8(&D_80114758, a0);

    if (v0 == NULL) {
        func_8002B420(D_8005FDEC, (u32)func_8003A1D4(&D_80114758) - a0);
    }
    return v0;
}

void func_8002B3D0(void *a0) {
    func_8003A2A4(&D_80114758, a0);
}

void func_8002B3F8(void *a0) {
    func_8003A2A4(&D_80114758, a0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1B800", func_8002B420);

INCLUDE_ASM("asm/us/main/nonmatchings/1B800", func_8002B4C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1B800", func_8002B4F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1B800", func_8002B5D8);

void func_8002B6C8(HandlePool *pool) {
    D_8005FE04 = pool;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1B800", func_8002B6D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1B800", func_8002B770);

INCLUDE_ASM("asm/us/main/nonmatchings/1B800", func_8002B7F4);
