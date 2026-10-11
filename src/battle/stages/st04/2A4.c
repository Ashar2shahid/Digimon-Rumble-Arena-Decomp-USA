#include "game_rotation.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"

extern u8 D_800D3D2C[];
extern u8 D_80065154[];
extern u8 D_800D3BCC[];
extern u8 D_80065174[];
extern void func_8006F23C(u8*);
extern void func_8002B3D0(u8*);
extern void func_80055BC4(u8*, u32, u32);
extern void func_80055B64(u8*, u8*);
extern void func_8002BCEC(u8*, u32);
extern void func_8002BDA8(u8*);
extern int func_8006ED08(u8*);
extern u8 D_800D3CB4[];
extern u8 D_800D3C64[];
extern u8 D_800D3C14[];
extern u8 D_800D3C3C[];
extern u8 D_800D3C8C[];
extern u8 D_800656C4[];

extern int func_8007760C(u8*);
extern u8 D_800D3D04[];
extern u8 D_800D3CDC[];
extern u8 D_800D3BF4[];
extern void func_80071F64(u8*);
extern u8* func_800700B0(u8*, u32);

extern u32 func_8006F18C(u8*);
extern u32 func_8006F12C(u8*);
extern u32 func_8006F178(u8*);
extern void func_800D52AC(u8*);
extern void func_800D5B8C(u8*);
extern void func_800D42A8(u8*);
extern void func_800D43E4(u8*);
extern void func_800D4CB0(u8*);
extern void func_800D4484(u8*);
extern void func_800D49E0(u8*);
extern void func_800D47B4(u8*);

u8* func_800D3DA4(u8* a0) {
    u8* s0 = a0;
    func_8006ED08(a0);
    *(u8**)(s0 + 0xD34) = D_800D3D2C;
    *(u32*)(s0 + 0xD3C) = 0;
    return s0;
}

void func_800D3DDC(u8* a0) {
    *(u8**)(a0 + 0xD34) = D_800D3D2C;
    func_8006F23C(a0);
}

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D3E04);

void func_800D3F98(u8* a0) {
    func_80071F64(a0);
    func_8007767C(func_800700B0(a0, 0), (s32 *)(a0 + 0x1DCC));
    func_8007767C(func_800700B0(a0, 1), (s32 *)(a0 + 0x1DDC));
    if (func_8006F18C(a0)) {
        *(u16*)(a0 + 0x2088) = 1;
    } else {
        *(u16*)(a0 + 0x2088) = 0;
        if (!func_8006F12C(a0) || func_8006F178(a0)) {
            func_800D52AC(a0);
            func_800D5B8C(a0);
            func_800D4184(a0);
            func_800D42A8(a0);
            func_800D43E4(a0);
            func_800D4CB0(a0);
            func_800D4484(a0);
            func_800D49E0(a0);
            func_800D47B4(a0);
            *(u32*)(a0 + 0xD38) += 1;
        }
    }
}

void func_800D4080(void) {
    u16 s[4];
    u16 a = 0x2E0;
    u16 c = 0x10;
    u16 d = 0x20;

    s[0] = a;
    s[1] = 0x80;
    s[2] = c;
    s[3] = d;
    func_80055BC4((u8*)s, 0x2E0, 0xA0);
    s[0] = a;
    s[1] = 0xC0;
    s[2] = c;
    s[3] = d;
    func_80055BC4((u8*)s, 0x2E0, 0xE0);
}

void func_800D4100(void) {
    u16 s[4];
    u16 a = 0x358;
    u16 b = 0x30;
    u16 c = 0x10;
    u16 d = 0x40;

    s[0] = a;
    s[1] = b;
    s[2] = c;
    s[3] = d;
    func_80055BC4((u8*)s, 0x2E0, 0);
    s[0] = a;
    s[1] = b;
    s[2] = c;
    s[3] = d;
    func_80055BC4((u8*)s, 0x2E0, 0x40);
}

void func_800D4184(u8* a0) {
    int v = *(int*)(a0 + 0xD38);
    s16 buf[4];

    if ((v ^ 1) & 1) {
        buf[0] = 0x2E0;
        buf[1] = ~v & 0x3F;
        buf[2] = 0x10;
        buf[3] = 0x40;
        func_80055BC4((u8*)buf, 0x358, 0x30);
    }
}

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D41E4);

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D42A8);

void func_800D439C(u8* a0) {
    *(u16*)(a0 + 0x1D68) = 0x330;
    *(u16*)(a0 + 0x1D6A) = 0xE6;
    *(u16*)(a0 + 0x1D6C) = 0x10;
    *(u16*)(a0 + 0x1D6E) = 1;
    func_80055B64(a0 + 0x1D68, a0 + 0x1D90);
}

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D43E4);

void func_800D4478(u8* a0) {
    *(u32*)(a0 + 0x1E20) = 0;
    *(u32*)(a0 + 0x1E1C) = 0;
}

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D4484);

void func_800D4560(u8* a0) {
    *(u32*)(a0 + 0x1DF0) = 0;
    *(u32*)(a0 + 0x1DEC) = 0;
    *(u32*)(a0 + 0x1DF8) = 0;
    *(u32*)(a0 + 0x1DF4) = 0;
    *(u32*)(a0 + 0x1DFC) = 0;
    *(u32*)(a0 + 0x1E00) = 0;
    *(u32*)(a0 + 0x1E04) = 0;
    *(u32*)(a0 + 0x1E08) = 0;
    *(u32*)(a0 + 0x1E0C) = 0;
    *(u32*)(a0 + 0x1E10) = 0;
    *(u32*)(a0 + 0x1E14) = 0;
    *(u32*)(a0 + 0x1E18) = 0;
}

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D4594);

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D46B4);

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D47B4);

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D49E0);

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D4CB0);

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D4EAC);

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D50B8);

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D5138);

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D52AC);

INCLUDE_ASM("asm/us/st04/nonmatchings/2A4", func_800D56FC);
