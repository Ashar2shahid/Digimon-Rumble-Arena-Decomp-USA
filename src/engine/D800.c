#include "game_thread.h"
#include "common.h"
#include "game_save_config.h"
#include "game_random.h"



INCLUDE_ASM("asm/us/main/nonmatchings/D800", func_8001D024);



s32 func_8001D114(s32 *self) {
    if (self[0x2C / 4] != 0) {
        func_8002B838((void *)self[0x2C / 4]);
        return -1;
    }
    return 0;
}

void func_8001D148(u8 *self, s32 value) {
    func_8001EFB0((GameThread *)(self + 0x20), 2);
    func_8002B770(self, value);
}

void *func_8001D18C(u8 *self) {
    func_8001E98C(self + 0x2D4);
    func_8001E98C(self + 0x2F4);
    func_8001E7A4((SaveConfig *)(self + 0x58));
    return self;
}


void func_8001D1C8(s32 *self) {
    self[0x318 / 4] = 0x13;
    self[0x314 / 4] = 0;
    self[0x31C / 4] = 0;
    self[0x320 / 4] = 7;
}

INCLUDE_ASM("asm/us/main/nonmatchings/D800", func_8001D1E4);

INCLUDE_ASM("asm/us/main/nonmatchings/D800", func_8001D250);

INCLUDE_ASM("asm/us/main/nonmatchings/D800", func_8001D268);


extern const u8 D_80010218[];
extern const s8 D_80010294[];

u32 func_8001D2A4(u32 *self) {
    u32 result = 0;
    u32 flags = self[0x78 / 4];
    u32 other;
    u32 unitBit;
    const s8 *pair;
    s32 i;
    for (i = 0; i < 9; i++) {
        result |= 1u << D_80010218[i];
    }
    if (flags != 0) {
        result |= 0x400000;
    }
    if ((flags & 5) == 5) {
        result |= 0x400;
    }
    if ((flags & 0x180000) == 0x180000) {
        result |= 0x40;
    }
    if ((flags & 0x41008) == 0x41008) {
        result |= 0x80;
    }
    other = self[0x74 / 4];
    unitBit = 1;
    pair = D_80010294;
    for (i = 9; i >= 0; i--) {
        if (flags & (unitBit << pair[0])) {
            result |= unitBit << pair[1];
        }
        pair += 2;
    }
    return result | other;
}

INCLUDE_ASM("asm/us/main/nonmatchings/D800", func_8001D36C);

void func_8001D3D0(s32 *self) {
    s32 value = self[0x68 / 4];
    self[0x2AC / 4] = 0;
    self[0x2B0 / 4] = 0;
    self[0x2B4 / 4] = 0;
    self[0x2B8 / 4] = 0;
    self[0x2BC / 4] = 0;
    self[0x2C0 / 4] = 0;
    self[0x2C8 / 4] = 0;
    self[0x2A8 / 4] = value;
    func_8003DEEC((u8 *)self + 0x324, 0x30);
    self[0x338 / 4] = 7;
    self[0x350 / 4] = 7;
}

void func_8001D42C(s32 *self) {
    func_8001D3D0(self);
    self[0x2A4 / 4] = 1;
    self[0x340 / 4] = 1;
}


void func_8001D45C(s32 *self) {
    self[1] = -1;
    self[0x2AC / 4] = 0;
    func_8001DAA8(self);
    func_8001DBDC(self);
    func_8001DD30(self);
}

void func_8001D49C(s32 *self, s32 value) {
    func_8001D3D0(self);
    self[0x2A4 / 4] = 5;
    self[0x2A4 / 4] = value ? 0x25 : 7;
    self[0x340 / 4] = value;
    self[0x2B0 / 4] = 1;
}


INCLUDE_ASM("asm/us/main/nonmatchings/D800", func_8001D4F0);

void func_8001D530(s32 *self) {
    func_8001D3D0(self);
    self[0x2A4 / 4] = 0xB;
    self[0x2B0 / 4] = 1;
}

u32 func_8001D564(s32 a0, u32 a1) {
    RandomState *p = &D_8005EE48;
    register u32 v asm("$2"); /* PIN $v0 */

    do {
        v = (s32)func_80037010(p);
        v %= a1;
    } while (v == a0);
    return v;
}

void func_8001D5C4(s32 *self) {
    u32 first;
    u32 second;
    u32 current;
    func_8001D3D0(self);
    self[0x328 / 4] = 1;
    self[0x340 / 4] = 1;
    first = func_8001D564(self[0x324 / 4], 0x18);
    self[0x324 / 4] = first;
    second = func_8001D564(self[0x33C / 4], 0x18);
    self[0x33C / 4] = second;
    current = func_8001D564(second, 7);
    self[0] = current;
    self[0x2B0 / 4] = 1;
    self[0x2A8 / 4] = 2;
    self[0x2AC / 4] = 6;
}

INCLUDE_ASM("asm/us/main/nonmatchings/D800", func_8001D640);





INCLUDE_ASM("asm/us/main/nonmatchings/D800", func_8001D750);

INCLUDE_ASM("asm/us/main/nonmatchings/D800", func_8001D7BC);
