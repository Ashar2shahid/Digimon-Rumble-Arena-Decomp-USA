#include "game_heap_wrappers.h"
#include "common.h"
#include "game_printer_storage.h"
#include "game_key_lookup.h"
#include "iterator_object.h"

extern u8 *func_800280A0();
extern u8 *func_80028050();
extern void func_8005844C();
extern void func_80079348(s32 *, s16 *, s32, s32);
extern void func_800207A0();
extern void func_8001FE8C();
extern u8 D_80066740[];
extern void func_8002E074();
extern u8 D_80066790[];

extern void func_8007A4A0(GlyphPrinterRecord *, s32, s32, s32);
extern s32 func_8007A364(s32);
extern u8 *func_8002E688();
extern void func_800799BC();
extern u8 *func_8002E160();

typedef struct { u8 _[8]; } Unk8;
typedef struct { u8 v; } Unk1;


INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80076EB0);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80077034);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_8007715C);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80077434);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80077630);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_800777F8);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_800779C4);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80077B80);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80077D4C);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80077E68);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80077F80);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80078364);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80078424);

void func_80078704(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 coords[2];

    coords[0] = arg1;
    coords[1] = arg2;
    func_80079348(arg0, coords, 7, 0);
    if (arg3 != 0) {
        coords[0] = arg1 + 0x3A;
        coords[1] = arg2 + 0x30;
        func_80079348(arg0, coords, 0xE, 0);
    }
    coords[0] = arg1 + 0xA;
    coords[1] = arg2 + 8;
    func_80079348(arg0, coords, 0x10, 0);
}

void func_800787AC(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 coords[2];

    coords[0] = arg1;
    coords[1] = arg2;
    func_80079348(arg0, coords, 8, 0);
    if (arg3 != 0) {
        coords[0] = arg1 + 0xF;
        coords[1] = arg2 + 0x30;
        func_80079348(arg0, coords, 0xF, 0);
    }
    coords[0] = arg1 + 0xF;
    coords[1] = arg2 + 8;
    func_80079348(arg0, coords, 0x11, 0);
}

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80078854);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80078F68);

void func_800792EC(u8 *arg0, u8 *arg1) {
    u8 *s0 = *(u8 **)(arg0 + 0x84);
    u8 *v0;

    func_800207A0(s0);
    v0 = *(u8 **)(s0 + 0x54);
    (*(void (**)(u8 *))(v0 + 0xC))(s0 + *(s16 *)(v0 + 0x8));
    func_8001FE8C(s0, arg1);
}

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80079348);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80079534);

u32 func_80079728(s32 count) {
    s32 i = 0;
    u32 sum = 0;
    if (count > 0) {
        do {
            sum += (u32)i;
            i++;
        } while (i < count);
    }
    return sum;
}

void func_80079754(s32 a0, s32 a1) {
    u32 table = *(u32 *)((u32)a0 + 0x1Cu);
    *(u32 *)((u32)a0 + 0x20u) = (u32)a1;
    (*(void (**)(s32, s32))(table + 0x24u))(
        (s32)((u32)a0 + (u32)(s32)*(s16 *)(table + 0x20u)), a1);
}

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80079788);

void func_80079850(s32 a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_80066740;
    func_8002B2B4((void *)(u32)*(s32 *)(a0 + 0x18));
    func_8002E074(a0, a1);
}

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_8007989C);

void func_800799BC(s32 a0, s32 a1) {
    register s32 v0 asm("$2");
    s32 v1 = func_800326E8(*(u16 **)(a0 + 0x20), *(s32 *)(a0 + 0x1C), (u16)a1) * 192;
    v0 = *(s32 *)(a0 + 0x24) + v1;
    *(s32 *)(a0 + 0x28) = v0;
}

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80079A08);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80079B48);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80079BE0);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80079CE4);

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_80079ECC);

void func_8007A2A4(u8 *arg0, u8 *arg1) {
    *(Unk8 *)(arg1 + 0x0) = *(Unk8 *)(arg0 + 0x34);
}

void func_8007A2CC(u8 *arg0, s32 arg1, s32 arg2) {
    *(s16 *)(arg0 + 0x40) = arg1;
    *(s16 *)(arg0 + 0x42) = arg2;
}

void func_8007A2D8(u8 *arg0, s16 arg1, s16 arg2) {
    s32 x = arg1;
    s32 y = arg2;

    *(s16 *)(arg0 + 0x44) = x - 1;
    *(s16 *)(arg0 + 0x46) = y - 1;
}

void func_8007A2FC(u8 *arg0, u8 *arg1) {
    *(Unk8 *)(arg0 + 0x40) = *(Unk8 *)(arg1 + 0x0);
}

void func_8007A324(u8 *arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0[0x48] = arg1;
    arg0[0x49] = arg2;
    arg0[0x4A] = arg3;
    arg0[0x4B] = 0x80;
}

void func_8007A33C(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, Unk1 arg4) {
    arg0[0x48] = arg1;
    arg0[0x49] = arg2;
    arg0[0x4A] = arg3;
    arg0[0x4B] = arg4.v;
}

void func_8007A354(u8 *arg0, s32 arg1) {
    arg0[0x4B] = arg1;
}

void func_8007A35C(s32 *arg0, s32 arg1) {
    arg0[0xF] = arg1;
}

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_8007A364);

void *func_8007A3BC(u8 *arg0, u8 *arg1) {
    GlyphPrinterRecord *self = (GlyphPrinterRecord *)arg0;
    self->base.table = &D_80066760;
    self->drawMode = func_80032640(arg1, func_800280A0(0x3B));
    self->color = 0x2808080;
    return arg0;
}

void func_8007A41C(void *arg0, u32 arg1) {
    ((GlyphPrinterRecord *)arg0)->color = (arg1 & 0xFFFFFF) | 0x2000000;
}

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_8007A438);

extern s32 func_8007A364(s32);

void func_8007A4A0(GlyphPrinterRecord *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 s2 = func_8007A364(arg3 & 0xFFFF);
    u8 *p = func_8002E688();
    u32 color = arg0->color;

    *(u32 *)(p + 8) = ((u32)arg1 & 0xFFFFu) | ((u32)arg2 << 16);
    *(u32 *)(p + 0xC) = (u32)s2 | 0x742C0000u;
    *(u32 *)(p + 4) = color | ((u32)p[7] << 24);
    func_8005844C(arg0->drawMode, p);
}

void func_8007A52C(u8 *self, s32 flags) {
    func_8003277C(self, flags);
}

INCLUDE_ASM("asm/us/title/nonmatchings/12AF0", func_8007A54C);
