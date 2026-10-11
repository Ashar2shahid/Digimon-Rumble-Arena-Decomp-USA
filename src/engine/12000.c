#include "common.h"
#include "scoped_value.h"

INCLUDE_ASM("asm/us/main/nonmatchings/12000", func_80021800);

INCLUDE_ASM("asm/us/main/nonmatchings/12000", func_8002184C);

extern void func_80026A5C(void *orderingTable);
void func_8002189C(void *camera) {
    u8 *bytes = (u8 *)camera;
    u32 table;
    func_80026A5C(camera);
    table = *(u32 *)(bytes + 8);
    *(u32 *)(bytes + 0x24) = 0;
    *(u32 *)(bytes + 0x20) = 0;
    *(u32 *)(bytes + 0x1C) = table;
    *(u32 *)(bytes + 0x28) = table;
}

INCLUDE_ASM("asm/us/main/nonmatchings/12000", func_800218D4);

INCLUDE_ASM("asm/us/main/nonmatchings/12000", func_80021958);


void func_80021B04(void *a0, s32 a1) {
    void *buffer = *(void **)((u8 *)a0 + 0x34);
    s32 limit = (s16)*(u16 *)((u8 *)buffer + 0xA);

    limit /= 2;
    if (a1 < limit) {
        a1 = limit;
    }
    *(s32 *)((u8 *)buffer + 0xC) = a1;
}

void func_80021B40(void *a0, s32 a1) {
    void *buffer = *(void **)((u8 *)a0 + 0x34);
    *(s32 *)((u8 *)buffer + 0x10) = a1;
}

s32 func_80021B4C(void *camera) {
    void *view = *(void **)((u8 *)camera + 0x34);
    return *(s16 *)((u8 *)view + 0xA);
}

s32 func_80021B60(void *camera) {
    void *view = *(void **)((u8 *)camera + 0x34);
    return *(s16 *)((u8 *)view + 0x8);
}

extern void func_80020FF8(void *);
ScopedValueBackup *func_80021B74(ScopedValueBackup *a0, ScopedValueObject *a1, s32 a2) {
    a0->object = a1;
    a0->previous = a1->value;
    a1->value = a2;
    func_80020FF8(a1);
    return a0;
}

extern void func_8002B3D0(void *);
void func_80021BB4(ScopedValueBackup *self, u32 flags) {
    ((ScopedValueObject *)self->object)->value = self->previous;
    func_80020FF8(self->object);
    if (flags & 1) {
        func_8002B3D0(self);
    }
}


INCLUDE_ASM("asm/us/main/nonmatchings/12000", func_80021C0C);

void *func_80021C58(void *a0) {
    return *(u8 **)((u8 *)a0 + 0x34) + 0xF4;
}

INCLUDE_ASM("asm/us/main/nonmatchings/12000", func_80021C64);

INCLUDE_ASM("asm/us/main/nonmatchings/12000", func_80021D98);

INCLUDE_ASM("asm/us/main/nonmatchings/12000", func_80021E38);

INCLUDE_ASM("asm/us/main/nonmatchings/12000", func_80021EEC);

