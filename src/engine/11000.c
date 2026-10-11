#include "common.h"
#include "scoped_value.h"
#pragma interface

class Component {
public:
    void *field0;
    char padding[0x20];
    int field24;
    int field28;
    int field2C;
    int field30;
    int field34;
    int field38;
    int field3C;
    int field40;
    int field44;
    Component();
};

struct Node {
    Node *next;
    Node *prev;
    Node() : next(this), prev(this) {}
};

class ListEntry : public Node, public Component {
public:
    unsigned int flags;
    virtual void first() const;
    virtual unsigned int second(int);
    virtual void third(int);
    virtual ~ListEntry();
    ListEntry();
};

class Entry {
public:
    Entry *next;
    Entry *prev;
    int field8;
    char data[0x44];
    unsigned int flags;
    virtual void first() const;
    virtual unsigned int second(int);
    virtual void third(int);
    virtual ~Entry();
};

class Derived : public Entry {
public:
    virtual ~Derived();
};
struct Gap {
    char padding[0x18];
};

struct MatrixOwner {
    u8 reserved[0x30];
    void *matrix;
    void *otherAllocation;
    u32 ownsStorage;
};

class Secondary {
public:
    char padding[0x3C];
    virtual void method();
};

class Multi : public Entry, public Component, public Gap, public Secondary {
public:
    virtual ~Multi();
};



INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_80020800);

class ListRoot;
extern "C" void func_8001FEF8(ListRoot *, s32);
extern "C" void func_80020808(u8 *self, s32 argument) {
    if (*(u32 *)(self + 0x94) != 0) {
        ScopedValueBackup state;
        func_80021B74(&state, (ScopedValueObject *)argument, *(s32 *)(self + 0x94));
        func_8001FEF8((ListRoot *)self, argument);
        func_80021BB4(&state, 2);
    } else {
        func_8001FEF8((ListRoot *)self, argument);
    }
}

void func_80020874(u8 *arg0, u32 arg1) {
    *(u32 *)(arg0 + 0x94) = arg1;
}
__asm__(
    ".globl func_80020874\n"
    ".set func_80020874, func_80020874__FPUcUi"
);

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_8002087C);

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_800208AC);

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_800208D0);
INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_800208F4);


u8 *func_80020938(u8 *arg0) {
    *(u32 *)arg0 = 0;
    return arg0 + 0x24;
}
__asm__(
    ".globl func_80020938\n"
    ".set func_80020938, func_80020938__FPUc"
);

u8 *func_80020944(u8 *arg0) {
    return arg0 + 0x24;
}
__asm__(
    ".globl func_80020944\n"
    ".set func_80020944, func_80020944__FPUc"
);

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_8002094C);


INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_8002099C);


void func_800209EC(u8 *arg0, u32 arg1) {
    *(u32 *)arg0 = 0;
    *(u32 *)(arg0 + 0x44) = arg1;
}
__asm__(
    ".globl func_800209EC\n"
    ".set func_800209EC, func_800209EC__FPUcUi"
);

void func_800209F8(u8 *arg0) {
    *(u32 *)(arg0 + 8) = 0;
}
__asm__(
    ".globl func_800209F8\n"
    ".set func_800209F8, func_800209F8__FPUc"
);

ListEntry::ListEntry() : Node(), Component() {
    flags &= ~1u;
}
__asm__(
    ".globl func_80020A00\n"
    ".set func_80020A00, __9ListEntry\n"
    ".set __9Component, func_8001F9B8\n"
    ".set _vt.9ListEntry, D_80010564"
);


void func_80020A50(u8 *arg0, u32 arg1) {
    u32 *flags = (u32 *)(arg0 + 0x50);
    *flags = (*flags & ~1u) | (arg1 & 1);
}
__asm__(
    ".globl func_80020A50\n"
    ".set func_80020A50, func_80020A50__FPUcUi"
);

u8 *func_80020A6C(u8 *arg0) {
    return arg0 + 0x58;
}
__asm__(
    ".globl func_80020A6C\n"
    ".set func_80020A6C, func_80020A6C__FPUc"
);

extern "C" void func_8001FD10(void);

void func_80020A74(void) {
    func_8001FD10();
}
__asm__(
    ".globl func_80020A74\n"
    ".set func_80020A74, func_80020A74__Fv"
);

Derived::~Derived() {
}
__asm__(
    ".globl func_80020A94\n"
    ".set func_80020A94, _._7Derived\n"
    ".set _._5Entry, func_8001FBA4\n"
    ".set _vt.7Derived, D_80010504"
);

u32 func_80020ABC(u8 *arg0, u32 arg1) {
    return ((u32 *)*(u32 **)(arg0 + 0x64))[arg1];
}
__asm__(
    ".globl func_80020ABC\n"
    ".set func_80020ABC, func_80020ABC__FPUcUi"
);

u8 *func_80020AD4(u8 *arg0) {
    return arg0 + 0x68;
}
__asm__(
    ".globl func_80020AD4\n"
    ".set func_80020AD4, func_80020AD4__FPUc"
);

Multi::~Multi() {
}
__asm__(
    ".globl func_80020ADC\n"
    ".set func_80020ADC, _._5Multi\n"
    ".set _vt.5Multi, D_80010504\n"
    ".set _vt.9Secondary, D_800104BC"
);

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_80020B10);

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_80020B90);

extern "C" void func_8002B3D0(void *);

extern "C" void func_80020BFC(MatrixOwner *self, u32 destroyFlags) {
    if (self->ownsStorage != 0) {
        func_8002B3D0(self->otherAllocation);
        func_8002B3D0(self->matrix);
    }
    if (destroyFlags & 1) {
        func_8002B3D0(self);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_80020C60);

extern "C" void func_8002310C(void *matrix, const u16 *values);
extern "C" void func_80023130(void *matrix, const u16 *values);
extern "C" void func_800231B0(void *matrix, const u32 *values);

extern "C" void func_80020D9C(MatrixOwner *self, const u16 *values) {
    func_8002310C(self->matrix, values);
}

extern "C" void func_80020DC0(MatrixOwner *self, const u16 *values) {
    func_80023130(self->matrix, values);
}

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_80020DE4);

extern "C" void func_80020E60(MatrixOwner *self, const u32 *values) {
    func_800231B0(self->matrix, values);
}

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_80020E84);

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_80020F00);

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_80020F7C);

INCLUDE_ASM("asm/us/main/nonmatchings/11000", func_80020FF8);
