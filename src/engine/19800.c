#include "common.h"
#include "object_base.h"
#include "game_resources.h"

extern u32 D_8005FC70[];
extern u32 D_8005FC90;
extern u32 D_8005F84C;
extern u8 D_80018DC4[];
extern u8 D_80018E24[];
extern u8 D_80018B28[];
extern u8 D_80018B0C[];
extern u8 D_80018AF0[];
extern u8 D_80018D04[];
extern u8 D_80018B18[];
extern u8 D_800642C8[];
extern u8 D_800642CC[];
extern void func_8001F628(u32, void *);

extern void func_8002C474(void *);
extern void func_8002C3F8(void *);
extern s32 func_80038BE8(void);
extern void func_8003569C(void);
extern void func_800350F0(s32);
extern void func_80035D28(s32);
extern void func_800356E8(void);
extern void *func_80028684(s32, s32, s32);
extern void func_8002AAD8();
extern s32 func_8003A014(s32);

typedef struct MenuWidget {
    u32 unk0[5];
    u32 unk14;
    u32 unk18;
    void *unk1C;
    void *unk20;
    u32 unk24;
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 unk30;
    u16 unk32;
    u16 boundX;
    u16 boundY;
    u8 active;
    u8 unk39;
} MenuWidget;



INCLUDE_ASM("asm/us/main/nonmatchings/19800", func_8002901C);

extern void func_8001BCC4(u8 *);
extern void func_8001BEC8(s32 *, s32);
extern void func_8001BEDC(s32);
extern u8 D_8005F824[];

s32 func_80029068(void) {
    func_8001BCC4(D_8005F824);
    return 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/19800", func_8002908C);

void func_80029100(u8 *self, s32 arg1, s32 arg2) {
    void *result = func_80028684(arg1, arg2, *(s32 *)(self + 0xC));
    s32 fieldC = *(s32 *)(self + 0xC);
    s32 field10 = *(s32 *)(self + 0x10);
    s32 value = func_8003A014(*(s32 *)(self + 0x24));
    func_8002AAD8(result, D_80018AF0, fieldC, field10, value);
}

INCLUDE_ASM("asm/us/main/nonmatchings/19800", func_8002917C);

extern void func_800357DC(u32 opaqueIncomingWord);

s32 func_800291B8(u32 opaqueIncomingWord) {
    func_800357DC(opaqueIncomingWord);
    return 0;
}

s32 func_800291D8(u8 *self, s32 arg1, u32 flags) {
    if (flags & 8) {
        func_8003569C();
        return -1;
    }
    if (!(flags & 2)) {
        func_800350F0(*(s32 *)(self + 0x10));
        func_80035D28(0);
    }
    func_800356E8();
    return -1;
}

void func_80029234(u8 *self, s32 arg1, s32 arg2) {
    void *result;
    *(s32 *)(self + 0x18) = D_8005F84C - 1;
    result = func_80028684(arg1, arg2, *(s32 *)(self + 0xC));
    func_8002AAD8(result, D_80018B0C, *(s32 *)(self + 0xC), *(s32 *)(self + 0x10));
}

INCLUDE_ASM("asm/us/main/nonmatchings/19800", func_8002928C);

void func_800292DC(u8 *self) {
    func_8002C3F8(self);
    D_8005FC70[8] |= 1 << *(s32 *)(self + 0xC);
}

void func_80029320(u8 *self) {
    func_8002C474(self);
    D_8005FC70[8] &= ~(1 << *(s32 *)(self + 0xC));
}

void func_80029368(u8 *self) {
    if (D_8005FC90 & (1 << *(s32 *)(self + 0xC))) {
        *(s32 *)(self + 0x10) = 1;
    } else {
        *(s32 *)(self + 0x10) = 0;
    }
}

void func_8002939C(u8 *self, s32 arg1, s32 arg2) {
    void *result = func_80028684(arg1, arg2, *(s32 *)(self + 0xC));
    s32 current = *(s32 *)(self + 0x10);
    s32 index = *(s32 *)(self + 0xC);
    void *selection = current ? D_800642C8 : D_800642CC;
    func_8002AAD8(result, D_80018B18, index, *(s32 *)(self + 0x24), selection);
}

INCLUDE_ASM("asm/us/main/nonmatchings/19800", func_80029408);

INCLUDE_ASM("asm/us/main/nonmatchings/19800", func_8002949C);

int func_80029570(u8 *arg0) {
    func_8001F628(D_8005FC70[0], arg0 + 0x28);
    return 0;
}

s32 func_8002959C(void *self, s32 arg1, s32 arg2, s32 flags) {
    if (flags == 0) {
        return 0;
    }
    func_8001F628(D_8005FC70[0], 0);
    return 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/19800", func_800295CC);

INCLUDE_ASM("asm/us/main/nonmatchings/19800", func_800295D0);
