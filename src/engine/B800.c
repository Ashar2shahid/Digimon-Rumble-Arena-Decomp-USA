#include "game_heap_wrappers.h"
#include "common.h"
#include "render_context.h"
#include "game_handles.h"

INCLUDE_ASM("asm/us/main/nonmatchings/B800", func_8001B000);

extern RenderContext D_800DA608;
extern u8 D_800DA724[];
extern u8 D_8005F80C[];
extern u8 D_8005EE2C[];
extern u32 D_8005FC70[];
extern s32 func_8001F448(RenderContext *);
extern s32 func_80026C38(void);
extern void func_80026A5C(void *);
extern void func_80026EB4(void *);
extern void func_800346A4(void);
extern void func_80035358(void);
extern void func_8002B9C4(void *, void *);
extern void func_8001F2A0(RenderContext *, s32);
void func_8001B104(void) {
    D_8005FC70[9] = func_8001F448(&D_800DA608);
    func_80026C38();
    func_80026A5C(D_8005F80C);
    func_80026EB4(D_800DA724);
    func_800346A4();
    func_80035358();
    func_8002B9C4(D_8005EE2C, D_8005FC70);
    func_8001F2A0(&D_800DA608, *(s32 *)(D_8005F80C + 4));
}
INCLUDE_ASM("asm/us/main/nonmatchings/B800", func_8001B198);

INCLUDE_ASM("asm/us/main/nonmatchings/B800", func_8001B210);

void func_8001B314(void) {
}

void *func_8001B31C(void *opaque, u32 items, u32 size) {
    return func_8002B248((s32)(size * items));
}

void func_8001B344(void *opaque, void *address) {
    func_8002B2B4(address);
}

extern HandlePool D_800DA728;
extern RenderContext *func_8001F0BC(RenderContext *, s32, s32, s32);
extern void *func_80026D44(void *);
extern HandlePool *func_80036C64(HandlePool *, s32);
extern void func_80026DB4(void *, u32);
void func_8001B364(s32 enable, u32 selection) {
    if (selection == 0xFFFF) {
        if (enable) {
            func_8001F0BC(&D_800DA608, 0x140, 0xF0, 1);
            func_80026D44(D_800DA724);
            func_80036C64(&D_800DA728, 0x200);
        } else {
            func_80036D88(&D_800DA728, 2);
            func_80026DB4(D_800DA724, 2);
        }
    }
}

extern void func_8001B364(s32, u32);
void func_8001B3E4(void) {
    func_8001B364(1, 0xFFFF);
}

void func_8001B408(void) {
    func_8001B364(0, 0xFFFF);
}

INCLUDE_ASM("asm/us/main/nonmatchings/B800", func_8001B42C);

extern s32 D_800100C0[];
s32 *func_8001B488(s32 *arg0, s32 arg1) {
    arg0[0] = (s32)arg0;
    arg0[1] = (s32)arg0;
    arg0[5] = (s32)D_800100C0;
    arg0[2] = arg1;
    arg0[3] = 0;
    arg0[4] = 0;
    return arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/B800", func_8001B4B0);

void func_8001B524(s32 *arg0) {
    arg0[4] = 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/B800", func_8001B530);

INCLUDE_ASM("asm/us/main/nonmatchings/B800", func_8001B5D4);

INCLUDE_ASM("asm/us/main/nonmatchings/B800", func_8001B63C);

extern s32 D_800100A0;
extern u8 D_80064158[];
extern u8 *func_80038BC0(u16);
extern void func_8001B530(u8 *, u8 *, u8 *);
u8 *func_8001B698(u8 *arg0, s32 arg1) {
    u8 *filename;
    func_8001B488((s32 *)arg0, arg1);
    *(u32 *)(arg0 + 0x14) = (u32)&D_800100A0;
    filename = func_80038BC0((u16)arg1);
    func_8001B530(arg0, filename, D_80064158);
    return arg0;
}

extern void func_8003926C(u16);
extern void func_8001B4B0(u8 *, s32);
void func_8001B6F4(u8 *arg0, s32 arg1) {
    *(u32 *)(arg0 + 0x14) = (u32)&D_800100A0;
    func_8003926C(*(u16 *)(arg0 + 8));
    func_8001B4B0(arg0, arg1);
}

/* This retained sound-file family represents its six fields as address words. */
extern s32 func_80039384(u16 index, void *data);
void func_8001B740(void *object, void *data) {
    s32 *words = object;
    func_80039384((u16)words[2], data);
    words[3] = (s32)(u32)data;
}

INCLUDE_ASM("asm/us/main/nonmatchings/B800", func_8001B778);

INCLUDE_ASM("asm/us/main/nonmatchings/B800", func_8001B7EC);
