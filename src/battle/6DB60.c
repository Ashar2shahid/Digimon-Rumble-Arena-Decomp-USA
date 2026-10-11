#include "game_base_api.h"
#include "common.h"

#pragma interface
class D1 {
    s32 fields[5];
public:
    virtual ~D1();
};
class D2 {
    s32 fields[5];
public:
    virtual ~D2();
};
class D3 {
    s32 fields[5];
public:
    virtual ~D3();
};
class D4 {
    s32 fields[5];
public:
    virtual ~D4();
};
class D5 {
    s32 fields[5];
public:
    virtual ~D5();
};
class D6 {
    s32 fields[5];
public:
    virtual ~D6();
};

extern "C" {

extern void func_80055B64(s32, s32);
extern void func_8002BCEC(s32, s32);
extern void func_8002BDA8(s32);

extern u8 D_8006E04C;
extern u8 D_8006E074;
extern u8 D_8006E09C[];
extern u8 D_8006E0C4[];
extern u8 D_8006E024[];
extern u8 D_8006DFFC[];

u8 *func_800D1F20(u8 *a0, s32 a1) {
    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    *(s32 *)(a0 + 0x18) = a1;
    *(u8 **)(a0 + 0x14) = D_8006E09C;
    *(s16 *)(a0 + 0x1C) = 0;
    return a0;
}
}
D1::~D1() {
    func_8002BCEC((s32)this, 0);
}
__asm__(
    ".globl func_800D1F6C\n"
    ".set func_800D1F6C, _._2D1\n"
    ".set _vt.2D1, D_8006E09C\n"
    ".set __builtin_delete, func_8002BDA8"
);
extern "C" {

s32 func_800D1FC0(s32 a0) {
    s32 v = *(u16 *)(a0 + 0x1C);
    v = v + 1;
    *(u16 *)(a0 + 0x1C) = v;
    return v;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6DB60", func_800D1FD4);

u8 *func_800D225C(s32 a0, s32 a1) {
    func_8002BC9C((u8 *)(u32)a0, 0);
    *(u32 *)(a0 + 0x14) = (u32)&D_8006E074;
    *(s32 *)(a0 + 0x6C) = a1;
    *(u16 *)(a0 + 0x68) = 0;
    *(u16 *)(a0 + 0x18) = 0x280;
    *(u16 *)(a0 + 0x1A) = 0xF5;
    *(u16 *)(a0 + 0x1C) = 0x10;
    *(u16 *)(a0 + 0x1E) = 1;
    func_80055B64(a0 + 0x18, a0 + 0x28);
    *(u16 *)(a0 + 0x20) = 0x280;
    *(u16 *)(a0 + 0x22) = 0xF4;
    *(u16 *)(a0 + 0x24) = 0x10;
    *(u16 *)(a0 + 0x26) = 1;
    func_80055B64(a0 + 0x20, a0 + 0x48);
    return (u8 *)a0;
}
}
D2::~D2() {
    func_8002BCEC((s32)this, 0);
}
__asm__(
    ".globl func_800D2304\n"
    ".set func_800D2304, _._2D2\n"
    ".set _vt.2D2, D_8006E074"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/6DB60", func_800D2358);

u8 *func_800D2694(s32 a0, s32 a1) {
    func_8002BC9C((u8 *)(u32)a0, 0);
    *(u32 *)(a0 + 0x14) = (u32)&D_8006E04C;
    *(s32 *)(a0 + 0x6C) = a1;
    *(u16 *)(a0 + 0x68) = 0;
    *(u16 *)(a0 + 0x18) = 0x280;
    *(u16 *)(a0 + 0x1A) = 0xFA;
    *(u16 *)(a0 + 0x1C) = 0x10;
    *(u16 *)(a0 + 0x1E) = 1;
    func_80055B64(a0 + 0x18, a0 + 0x28);
    *(u16 *)(a0 + 0x20) = 0x280;
    *(u16 *)(a0 + 0x22) = 0xF8;
    *(u16 *)(a0 + 0x24) = 0x10;
    *(u16 *)(a0 + 0x26) = 1;
    func_80055B64(a0 + 0x20, a0 + 0x48);
    return (u8 *)a0;
}

}
D3::~D3() {
    func_8002BCEC((s32)this, 0);
}
__asm__(
    ".globl func_800D273C\n"
    ".set func_800D273C, _._2D3\n"
    ".set _vt.2D3, D_8006E04C"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/6DB60", func_800D2790);

u8 *func_800D2AB0(u8 *a0, s32 a1) {
    func_8002BC9C((u8 *)(u32)(s32)a0, 0);
    *(s32 *)(a0 + 0x18) = a1;
    *(u8 **)(a0 + 0x14) = D_8006E0C4;
    return a0;
}

}
D4::~D4() {
    func_8002BCEC((s32)this, 0);
}
__asm__(
    ".globl func_800D2AF8\n"
    ".set func_800D2AF8, _._2D4\n"
    ".set _vt.2D4, D_8006E0C4"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/6DB60", func_800D2B4C);

INCLUDE_ASM("asm/us/game/nonmatchings/6DB60", func_800D2C98);

}
D5::~D5() {
    func_8002BCEC((s32)this, 0);
}
__asm__(
    ".globl func_800D2E64\n"
    ".set func_800D2E64, _._2D5\n"
    ".set _vt.2D5, D_8006E024"
);
extern "C" {

INCLUDE_ASM("asm/us/game/nonmatchings/6DB60", func_800D2EB8);

INCLUDE_ASM("asm/us/game/nonmatchings/6DB60", func_800D2F34);

INCLUDE_ASM("asm/us/game/nonmatchings/6DB60", func_800D3168);

}
D6::~D6() {
    func_8002BCEC((s32)this, 0);
}
__asm__(
    ".globl func_800D325C\n"
    ".set func_800D325C, _._2D6\n"
    ".set _vt.2D6, D_8006DFFC"
);
extern "C" {

void func_800D32B0(void) {
}

INCLUDE_ASM("asm/us/game/nonmatchings/6DB60", func_800D32B8);

s32 func_800D353C(s32 a0, u16 a1) {
    s16 *p = (s16 *)(a0 + 0xD98);
    return p[a1];
}

void func_800D3554(s32 a0, s32 a1, s16 a2) {
    s16 *p = (s16 *)(a0 + 0xF2C);
    p[a1] = a2;
}

void func_800D3564(s32 a0, s32 a1, s16 a2) {
    s16 *p = (s16 *)(a0 + 0xF30);
    p[a1] = a2;
}

void func_800D3574(s32 a0, s16 a1) {
    *(s16 *)(a0 + 0xF34) = a1;
}

void func_800D357C(s32 a0, s16 a1) {
    *(s16 *)(a0 + 0xF36) = a1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6DB60", func_800D3584);
}
