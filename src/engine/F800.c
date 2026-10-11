#include "common.h"
#include "render_context.h"
#include "game_thread.h"

extern RECT D_800103F0[2];
extern s32 func_800554DC(s32 mode);
extern s32 func_80055858(s32 mode);
extern s32 func_800565B4(void);
extern s32 func_8003F4EC(s32 mode);
extern s32 func_800557C0(s32 enabled);
extern s32 func_80055A6C(RECT *area, s32 red, s32 green, s32 blue);
extern void func_8003F7EC(void (*callback)(void));
typedef void (*GraphicsCallback)(void);
extern GraphicsCallback func_80055760(GraphicsCallback callback);
void func_8001F2A8(void);
void func_8001F424(void);



u32 D_800641A0 = 0xFF000000U;

s32 func_8001F020(GameThread *self, s32 value) {
    self->caller = D_800641A0;
    return func_8001F070(self->id, value);
}

s32 func_8001F04C(GameThread *self, s32 value) {
    return func_8001F070(self->caller, value);
}

INCLUDE_ASM("asm/us/main/nonmatchings/F800", func_8001F070);

s32 func_8001F0B0(s32 *arg0) {
    return *arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/F800", func_8001F0BC);

void func_8001F1A0(RenderContext *self) {
    func_800554DC(0);
    func_8003F4EC(2);
    func_800557C0(0);
    func_80055A6C(&D_800103F0[0], 0, 0, 0);
    func_80055A6C(&D_800103F0[1], 0, 0, 0);
    func_80055858(0);
    func_8003F4EC(2);
    func_800557C0(1);
    func_8003F4EC(0);
    self->state104 = func_800565B4() == 0;
    func_8003F7EC(func_8001F2A8);
    func_80055760(func_8001F424);
    self->state114 = 1;
}

void func_8001F260(RenderContext *self, s32 value) {
    if (value < 2) {
        value = 0;
    }
    self->stateF8 = value;
}

void func_8001F278(RenderContext *self, s32 red, s32 green, s32 blue) {
    red &= 0xFF;
    green &= 0xFF;
    blue &= 0xFF;
    self->draw[0].r0 = red;
    self->draw[0].g0 = green;
    self->draw[0].b0 = blue;
    self->draw[1].r0 = red;
    self->draw[1].g0 = green;
    self->draw[1].b0 = blue;
}

void func_8001F2A0(RenderContext *self, s32 value) {
    self->state118 = value;
}

INCLUDE_ASM("asm/us/main/nonmatchings/F800", func_8001F2A8);

/* Counter addressed through the resident small-data base. */
extern u32 D_800641A8;

void func_8001F424(void) {
    D_800641A8 += 1u;
}

u32 func_8001F43C(void) {
    return D_800641A8;
}

s32 func_8001F448(RenderContext *self) {
    if (!self->state108 && !self->state10C) {
        func_80055858(0);
        self->state114 = 1;
    }
    self->state100 = func_8003F4EC(self->stateF8);
    self->stateFC = self->stateF8 > 0 ? self->stateF8 - 1 : 0;
    return self->state100;
}

extern u32 D_800641B0;

void func_8001F4BC(RenderContext *self, s32 width, s32 height) {
    s32 drawOnDisplay;
    if (height >= 256) {
        drawOnDisplay = 0;
        self->display[0].disp.x = 0;
        self->display[0].disp.y = 0;
        self->display[0].disp.w = width;
        self->display[0].disp.h = height;
        self->display[1].disp.x = 0;
        self->display[1].disp.y = 0;
        self->display[1].disp.w = width;
        self->display[1].disp.h = height;
        self->state108 = 1;
        self->display[0].isinter = 1;
        self->display[1].isinter = 1;
    } else {
        self->display[0].disp.x = 0;
        self->display[0].disp.y = 0;
        self->display[0].disp.w = width;
        self->display[0].disp.h = height;
        self->display[1].disp.x = 0;
        self->display[1].disp.y = height;
        self->display[1].disp.w = width;
        self->display[1].disp.h = height;
        self->state108 = 0;
        if (self->state110) {
            self->display[0].isinter = 1;
            self->display[1].isinter = 1;
        } else {
            self->display[0].isinter = 0;
            self->display[1].isinter = 0;
        }
        drawOnDisplay = 1;
    }
    D_800641B0 = drawOnDisplay;
    self->draw[0].clip = self->display[1].disp;
    self->draw[0].dfe = drawOnDisplay;
    self->draw[0].tw.x = 0;
    self->draw[0].tw.y = 0;
    self->draw[0].tw.w = 256;
    self->draw[0].tw.h = 256;
    self->draw[0].tpage = 0;
    self->draw[0].ofs[0] = self->display[1].disp.x;
    self->draw[0].ofs[1] = self->display[1].disp.y;
    self->draw[1].clip = self->display[0].disp;
    self->draw[1].dfe = drawOnDisplay;
    self->draw[1].tw.x = 0;
    self->draw[1].tw.y = 0;
    self->draw[1].tw.w = 256;
    self->draw[1].tw.h = 256;
    self->draw[1].tpage = 0;
    self->draw[1].ofs[0] = self->display[0].disp.x;
    self->draw[1].ofs[1] = self->display[0].disp.y;
}

void func_8001F5E8(RenderContext *self, s16 *out) {
    out[0] = self->display[0].disp.w;
    out[1] = self->display[0].disp.h;
}

void func_8001F600(RenderContext *self, s32 x, s32 y) {
    self->display[0].screen.x = x;
    self->display[0].screen.y = y;
    self->display[1].screen.x = x;
    self->display[1].screen.y = y;
}

void func_8001F614(RenderContext *self, s32 width, s32 height) {
    self->display[0].screen.w = width;
    self->display[0].screen.h = height;
    self->display[1].screen.w = width;
    self->display[1].screen.h = height;
}

void func_8001F628(RenderContext *self, DISPENV *target) {
    if (target == 0) {
        self->displayCurrent[0] = &self->display[0];
        self->displayCurrent[1] = &self->display[1];
        return;
    }
    self->displayCurrent[0] = target;
    self->displayCurrent[1] = target;
}

void func_8001F648(RenderContext *self, DISPENV *target) {
    self->displayOverride = target;
    if (target != 0) {
        target->screen = self->display[0].screen;
    }
}

extern u32 D_800641B4;

void func_8001F678(RenderContext *self, u32 mode) {
    switch (mode) {
    case 0:
        self->draw[0].isbg = 1;
        self->draw[1].isbg = 1;
        break;
    case 1:
        self->state110 = 1;
        self->display[0].isinter = 1;
        self->display[1].isinter = 1;
        break;
    case 2:
        self->display[0].isrgb24 = 1;
        self->display[1].isrgb24 = 1;
        break;
    case 3:
        self->draw[0].dtd = 1;
        self->draw[1].dtd = 1;
        D_800641B4 = 1;
        break;
    case 4:
        self->state10C = 1;
        break;
    }
}

/* Historical case-4 target inside the five-case switch. */
__asm__(".globl func_8001F6F8\n.set func_8001F6F8, func_8001F678 + 0x80\n.size func_8001F6F8, 0x10");

void func_8001F708(RenderContext *self, u32 mode) {
    switch (mode) {
    case 0:
        self->draw[0].isbg = 0;
        self->draw[1].isbg = 0;
        break;
    case 1:
        self->state110 = 0;
        if (self->state108 != 0) {
            self->display[0].isinter = 1;
            self->display[1].isinter = 1;
        } else {
            self->display[0].isinter = 0;
            self->display[1].isinter = 0;
        }
        break;
    case 2:
        self->display[0].isrgb24 = 0;
        self->display[1].isrgb24 = 0;
        break;
    case 3:
        self->draw[0].dtd = 0;
        self->draw[1].dtd = 0;
        D_800641B4 = 0;
        break;
    case 4:
        self->state10C = 0;
        break;
    }
}

/* Historical case-4 target inside the five-case switch. */
__asm__(".globl func_8001F790\n.set func_8001F790, func_8001F708 + 0x88\n.size func_8001F790, 0xC");

extern s32 func_8003F4EC(s32 mode);
extern s32 func_800557C0(s32 enabled);
extern s32 func_80055A6C(RECT *area, s32 red, s32 green, s32 blue);

void func_8001F79C(RenderContext *self) {
    func_8003F4EC(0);
    func_800557C0(0);
    func_80055A6C(&self->display[0].disp, 0, 0, 0);
    func_80055A6C(&self->display[1].disp, 0, 0, 0);
    func_8003F4EC(0);
    func_800557C0(1);
}

/* Historical label at the return delay slot, not a callable entry. */
__asm__(".globl func_8001F800\n.set func_8001F800, func_8001F79C + 0x64\n.size func_8001F800, 4");

