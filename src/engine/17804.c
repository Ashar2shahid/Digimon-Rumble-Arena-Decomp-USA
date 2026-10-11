#include "common.h"
#include "game_input.h"


extern u8 D_80114214[];
extern u32 D_80114344;
extern void func_80026E70(void);
extern void func_80027858(u8 *);
extern void func_800279E8(u8 *);
extern void func_80027214(void *);
extern s32 func_8005B8BC(s32);
extern s32 func_8005B5EC(s32, u8 *);
extern s32 func_8005B98C(s32, s32, s32);
extern s32 func_8005B75C(s32, s32, s32);
extern s32 func_8005BA8C(s32, s32, s32);

s32 func_80027004(s32 a0, s32 a1) {
    return func_80026F68(a0, a1, 0x40);
}
s32 func_80027024(s32 a0, s32 a1) {
    return func_80026F68(a0, a1, 0x44);
}

s32 func_80027044(s32 a0, s32 a1) {
    return func_80026F68(a0, a1, 0x48);
}

INCLUDE_ASM("asm/us/main/nonmatchings/17804", func_80027064);

void func_800270B4(s32 unused, u32 value) {
    s32 remaining = 1;
    u8 *entry = D_80114214;
    do {
        *(u32 *)(entry + remaining * 0x98 + 0x34) = value;
        remaining--;
    } while (remaining >= 0);
}

void func_800270DC(s32 unused, u32 value) {
    if (D_80114344 != value) func_80026E70();
    D_80114344 = value;
}

void func_80027118(void *value, s32 port, s32 slot) {
    u8 *self = value;
    *(u32 *)(self + 0x24) = ((u32)port << 4) | (u32)slot;
    *(u32 *)(self + 0x2C) = 0;
    *(u32 *)(self + 0x28) = 5;
    *(u32 *)(self + 0x34) = 0x25;
    func_80027858(self + 0x68);
    func_80027588(self, 0x10, 4);
}

void func_80027170(void *value) {
    u8 *self = value;
    func_80027214(self);
    func_800279E8(self + 0x68);
    *(u32 *)(self + 0x40) = 0;
    *(u32 *)(self + 0x44) = 0;
    *(u32 *)(self + 0x48) = 0;
    *(u32 *)(self + 0x4C) = 0;
    func_80027588(self, 0x10, 4);
}

extern void func_80027888(u8 *);

void func_800271BC(u8 *a0) {
    func_80027888(a0 + 0x68);
}

s32 func_800271DC(u32 buttons) {
    if ((buttons & 0x5000) == 0x5000) buttons &= ~0x5000u;
    if ((buttons & 0xA000) == 0xA000) buttons &= ~0xA000u;
    return (s32)buttons;
}

INCLUDE_ASM("asm/us/main/nonmatchings/17804", func_80027214);

void func_80027530(u8 *self) {
    u32 pressed = *(u32 *)(self + 0x40);
    u32 held;
    *(u32 *)(self + 0x48) = 0;
    if (pressed != 0) {
        *(u32 *)(self + 0x48) = pressed;
        *(u32 *)(self + 0x4C) = 0;
        return;
    }
    held = *(u32 *)(self + 0x38);
    if (held != 0) {
        u32 counter = *(u32 *)(self + 0x4C) + 1u;
        *(u32 *)(self + 0x4C) = counter;
        if ((s32)counter > *(s32 *)(self + 0x50)) {
            *(u32 *)(self + 0x48) = held;
            *(u32 *)(self + 0x4C) = *(u32 *)(self + 0x54);
        }
    }
}

void func_80027588(void *value, u32 delay, u32 interval) {
    u8 *self = value;
    *(u32 *)(self + 0x50) = delay;
    *(u32 *)(self + 0x54) = delay - interval;
}

s32 func_80027598(u8 *self) {
    s32 state = func_8005B8BC(*(s32 *)(self + 0x24));
    s32 active = 0;
    if (state == 2 || state == 6) active = 1;
    if (state == 0) *(u32 *)(self + 0x68) = 0;
    *(s32 *)(self + 0x28) = state;
    *(s32 *)(self + 0x2C) = active;
    return active;
}

s32 func_800275FC(u8 *self) {
    s32 mode;
    s32 result;
    s32 i;
    u8 *alignment;
    if (*(s32 *)(self + 0x6C) != 0 && *(s32 *)(self + 0x68) != 0) {
        s32 phase = *(s32 *)(self + 0x70);
        switch (phase) {
        case 0:
            break;
        case 1:
            self[0x92] = 0;
            self[0x93] = (u8)phase;
            i = 2;
            alignment = self + 0x92;
            for (; i < 6; i++) alignment[i] = 0xFF;
            if (func_8005B5EC(*(s32 *)(self + 0x24), self + 0x92) == 1)
                *(u32 *)(self + 0x70) += 1u;
            return 0;
        case 2:
            if (*(s32 *)(self + 0x28) == 6)
                *(u32 *)(self + 0x70) = 3;
            return 0;
        }
    }
    switch (*(s32 *)(self + 0x68)) {
    case 0:
        *(u32 *)(self + 0x30) = 0;
        *(u32 *)(self + 0x6C) = 0;
        *(u32 *)(self + 0x70) = 0;
        mode = func_8005B98C(*(s32 *)(self + 0x24), 1, 0);
        if (mode == 0) break;
        result = func_8005B98C(*(s32 *)(self + 0x24), 2, 0);
        if (result > 0) mode = result;
        switch (mode) {
        case 4: *(u32 *)(self + 0x68) = 40; break;
        case 7: *(u32 *)(self + 0x68) = 70; break;
        default: *(s32 *)(self + 0x68) = -1; break;
        }
        break;
    case 40:
        if (func_8005B98C(*(s32 *)(self + 0x24), 4, -1) == 0) {
            *(u32 *)(self + 0x68) = 99;
            break;
        }
        *(u32 *)(self + 0x68) += 1u;
        /* Fall through after the analog-mode capability check. */
    case 41:
        result = func_8005B98C(*(s32 *)(self + 0x24), 3, 0);
        if (func_8005B75C(*(s32 *)(self + 0x24), (s32)((u32)result + 1u), 1) == 1)
            *(u32 *)(self + 0x68) += 1u;
        break;
    case 42:
        if (*(s32 *)(self + 0x28) == 6) *(u32 *)(self + 0x68) = 70;
        break;
    case 70:
        if (*(s32 *)(self + 0x2C) == 0) break;
        if (func_8005BA8C(*(s32 *)(self + 0x24), -1, 0) == 0) {
            *(u32 *)(self + 0x68) = 99;
            break;
        }
        *(u32 *)(self + 0x6C) = 1;
        *(u32 *)(self + 0x68) += 1u;
        break;
    default:
        return 1;
    }
    return 0;
}

/* Historical sector label inside the complete controller state machine. */
__asm__(".globl func_80027800\n.set func_80027800, func_800275FC + 0x204\n.size func_80027800, 0x58");
