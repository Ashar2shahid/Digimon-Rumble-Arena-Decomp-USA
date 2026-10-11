#include "game_destructor_api.h"
#include "common.h"
#include "game_random.h"

extern u8 D_800D3B74[];
extern u8 D_800D3B54[];

extern u8 *func_800D3BEC();
extern u8 *func_8002B364();
extern void func_80055B64();

extern void func_800D0618(void);
extern void func_800D0984(void);
extern void func_800D3EEC(u8 *);
extern void func_800700CC(u8 *, s32, s32, s32, s32, s32);
extern s32 func_8006F1A0(u8 *);
extern void func_800D439C(u8 *);
extern void func_800D4670(u8 *);
extern void func_800D4A84(u8 *);
extern void func_800D4294(u8 *);
extern void func_800D43BC(u8 *);
extern void func_800D4870(u8 *);
extern void func_800D42F8(u8 *);
extern void func_800D4AAC(u8 *);
extern void func_800D40D8(u8 *);

u8 *func_800D3BEC(arg0)
u8 *arg0;
{
    func_8007C35C();
    *(u8 **)(arg0 + 0x4) = D_800D3B54;
    *(s32 *)(arg0 + 0x8) = 0;
    *(s32 *)(arg0 + 0xC) = 0;
    *(s32 *)(arg0 + 0x10) = 0;
    return arg0;
}

extern s32 D_8005FB60;
s32 func_800D3C2C(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x8) == 0) {
        switch (D_8005FB60) {
        case 0: {
            s32 t = (s32)func_80037010(&D_8005EE48);
            t = t % 10;
            *(s32 *)(arg0 + 0x10) = (t < 0 ? -t : t) + 1;
            break;
        }
        case 1: {
            s32 t = (s32)func_80037010(&D_8005EE48);
            t = t % 6;
            *(s32 *)(arg0 + 0x10) = (t < 0 ? -t : t) + 2;
            break;
        }
        case 2:
            *(s32 *)(arg0 + 0x10) = ((s32)func_80037010(&D_8005EE48) & 3) + 3;
            break;
        }
        *(s32 *)(arg0 + 0xC) = 0;
        *(s32 *)(arg0 + 0x8) = *(s32 *)(arg0 + 0x8) + 1;
    }
    {
        s32 c = *(s32 *)(arg0 + 0xC);
        *(s32 *)(arg0 + 0xC) = c + 1;
        if ((c + 2) % *(s32 *)(arg0 + 0x10) != 0) {
            return 0;
        }
    }
    *(s32 *)(arg0 + 0x8) = 0;
    return 0x80;
}

u8 *func_800D3D88(u8 *arg0) {
    func_800D057C();
    *(u8 **)(arg0 + 0xD34) = D_800D3B74;
    *(s32 *)(arg0 + 0xD38) = 9;
    *(s32 *)(arg0 + 0xD3C) = 0xA;
    *(s32 *)(arg0 + 0xD40) = 0xE;
    *(s32 *)(arg0 + 0xD44) = 0xB;
    *(s32 *)(arg0 + 0xD48) = 0xC;
    *(s32 *)(arg0 + 0xD4C) = 8;
    *(s32 *)(arg0 + 0xD50) = 0xF;
    *(s32 *)(arg0 + 0xD54) = 0x10;
    *(s32 *)(arg0 + 0xFD4) = 0;
    *(s32 *)(arg0 + 0xFD0) = 0;
    return arg0;
}

void func_800D3E04(u8 *arg0) {
    *(s32 *)(arg0 + 0xD34) = (s32)D_800D3B74;
    func_800D05B0();
}

void func_800D3E2C(u8 *arg0) {
    func_800D0618();
    func_800D3EEC(arg0);
    func_800700CC(arg0, -0x500, 0x500, -0xC80, 0x400, 0);
    *(s32 *)(arg0 + 0xFD8) = func_8006F1A0(arg0);
    func_800D439C(arg0);
    func_800D4670(arg0);
    func_800D4A84(arg0);
    func_800D4294(arg0);
    *(s16 *)(arg0 + 0xF68) = 0x78;
    *(s16 *)(arg0 + 0xFBA) = -1;
    *(s16 *)(arg0 + 0xFBC) = -1;
}

void func_800D3EB8(u8 *arg0, u8 *arg1, u8 *arg2) {
    func_800D3BEC(func_8002B364(0x14), arg2);
}

void func_800D3EEC(u8 *arg0) {
    *(u16 *)(arg0 + 0xFB8) = 0;
    *(u16 *)(arg0 + 0xF6A) = 0;
    *(u16 *)(arg0 + 0xFBE) = 0;
}

INCLUDE_ASM("asm/us/st08/nonmatchings/EC", func_800D3EFC);

void func_800D4080(u8 *arg0) {
    func_800D0984();
    func_800D43BC(arg0);
    func_800D4870(arg0);
    func_800D42F8(arg0);
    func_800D4AAC(arg0);
    func_800D40D8(arg0);
    *(u16 *)(arg0 + 0xFB8) = *(u16 *)(arg0 + 0xFB8) + 1;
}

extern u16 D_800656C4[];
extern void *func_800700B0(u8 *, s32);
extern s32 func_8007760C(void *);
extern void func_800795B0(void *);
extern void func_800774EC(void *, s32);
extern void func_800D0E50(u8 *);

void func_800D40D8(u8 *arg0) {
    s16 completed = 0;
    u16 first, second;

    if (*(u16 *)(arg0 + 0xF6A) != 0) {
        return;
    }
    first = D_800656C4[func_8007760C(func_800700B0(arg0, 0)) * 0xC0];
    second = D_800656C4[func_8007760C(func_800700B0(arg0, 1)) * 0xC0];
    if (*(s16 *)(arg0 + 0xFE0) == 0) {
        *(s16 *)(arg0 + 0xFBC) = 0;
        if ((first ^ 1) & 1) {
            func_800795B0(func_800700B0(arg0, 0));
            *(u16 *)(arg0 + 0xFBE) = *(u16 *)(arg0 + 0xFBE) + 1;
        }
        func_800774EC(func_800700B0(arg0, 0), 0x10000);
        *(u16 *)(arg0 + 0xF6A) = 1;
        completed = 1;
    }
    if (*(s16 *)(arg0 + 0xFE2) == 0) {
        *(s16 *)(arg0 + 0xFBC) = 1;
        if ((second ^ 1) & 1) {
            func_800795B0(func_800700B0(arg0, 1));
            *(u16 *)(arg0 + 0xFBE) = *(u16 *)(arg0 + 0xFBE) + 1;
        }
        func_800774EC(func_800700B0(arg0, 1), 0x10000);
        *(u16 *)(arg0 + 0xF6A) = 1;
        completed++;
    }
    if (completed == 2) {
        *(u16 *)(arg0 + 0xF6A) = 1;
        *(s16 *)(arg0 + 0xFBC) = -1;
        *(s16 *)(arg0 + 0xFBA) = -1;
    }
    if (*(s32 *)(arg0 + 0xD28) == 1) {
        func_800D0E50(arg0);
        *(u16 *)(arg0 + 0xF6A) = 1;
        *(s16 *)(arg0 + 0xFBC) = -1;
        *(s16 *)(arg0 + 0xFBA) = 0xAA;
    }
}

void func_800D4294(u8 *arg0) {
    s16 *p = (s16 *)(arg0 + 0xF70);

    *(s16 *)(arg0 + 0xF70) = 0x300;
    *(s16 *)(arg0 + 0xF72) = 0xFC;
    *(s16 *)(arg0 + 0xF74) = 0x10;
    *(s16 *)(arg0 + 0xF76) = 1;
    func_80055B64((u8 *)p, arg0 + 0xF78);
    func_80055B64((u8 *)p, arg0 + 0xF98);
}

INCLUDE_ASM("asm/us/st08/nonmatchings/EC", func_800D42F8);

void func_800D439C(u8 *arg0) {
    *(s16 *)(arg0 + 0xFDC) = 0;
    *(s16 *)(arg0 + 0xFDE) = 0;
    *(s16 *)(arg0 + 0xFC8) = 0;
    *(s16 *)(arg0 + 0xFCC) = 0;
    *(s16 *)(arg0 + 0xFCA) = 0;
    *(s16 *)(arg0 + 0xF34) = 0xF;
}

INCLUDE_ASM("asm/us/st08/nonmatchings/EC", func_800D43BC);

INCLUDE_ASM("asm/us/st08/nonmatchings/EC", func_800D4670);

INCLUDE_ASM("asm/us/st08/nonmatchings/EC", func_800D4870);

void func_800D4A84(u8 *arg0) {
    s16 c = 0x78;
    s32 i;

    for (i = 1; i >= 0; i--) {
        *(s16 *)(arg0 + 0xFE0 + i * 2) = c;
    }
    *(s16 *)(arg0 + 0xF36) = 0x78;
}

void func_800D4AAC(u8 *arg0) {
    s32 i, v;
    s16 *p = (s16 *)(arg0 + 0xFE0);

    for (i = 1; i >= 0; i--) {
        v = *p;
        p[-0x58] = v;
        p++;
    }
}

void func_800D4AD0(u8 *self, s32 flags) {
    func_8007C374(self, flags);
}
