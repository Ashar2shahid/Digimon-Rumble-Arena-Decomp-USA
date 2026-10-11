#include "game_action_api.h"
#include "game_placement_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#include "game_collision_api.h"
#include "game_actor_queries.h"
#include "game_positions.h"
#include "game_effects.h"

extern s32 func_800C72C0(s32, s32, s32 *, s32 *, s32, u32, s32, s32);
s32 func_8009EBB0(s32, s32, s32, s32 *, s32 *);

extern u8 D_8006A4CC;
extern u8 D_8006A4A4;
extern u8 D_8006A47C;
extern u8 D_8006D730;
extern u8 D_8006D750;

extern u8 D_80065154;

extern u8 D_80065174;

extern u8 D_8006A14C;

extern u8 D_8006A174;

extern u8 D_8006A19C;
extern u8 D_8006A1BC;
extern u8 D_8006A1DC;

extern u8 D_8006A42C;
extern u8 D_8006A544;
extern u8 D_8006A5B4;
extern u8 D_8006A6F0[];
extern u8 D_8006A46C[];
extern u8 D_8006A4F4[];
extern u8 D_8006A56C;
extern u8 D_8006A58C;
extern void func_8007C0A0(u8 *, s32, s32);
extern s32 func_8007B150(u8 *);
extern s32 func_80077978(u8 *);
extern s32 func_80077730(u8 *);
extern s32 func_800C2F68(s32, s32, s32);
extern void func_800C3314(u8 *, s32 *, s32 *, s32, s32);
extern u8 *func_8009F78C(u8 *, u8 *);

u8 *func_8009D144(u8 *self, u8 *owner, s32 *position, s32 *vector) {
    func_8009C0C0(self, owner, position, vector);
    *(u8 **)(self + 0x18) = &D_8006A19C;
    *(u8 **)(self + 0x14) = &D_8006A174;
    func_8007C0A0(self + 0x18, 0x06B08000, 7);
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009D198);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009D274);

s32 func_8009D4C4(s32 a0, s32 a1) {
    func_8002BC9C((u8 *)a0, 0);
    *(s32 *)(a0 + 0x18) = a1;
    *(u32 *)(a0 + 0x14) = (u32)&D_8006A14C;
    *(s32 *)(a0 + 0x1C) = 0;
    *(s32 *)(a0 + 0x20) = 0;
    return a0;
}

void func_8009D514(u8 *self) {
    s32 phase;
    if (func_8007B150(*(u8 **)(self + 0x18))) {
        *(s32 *)(self + 0x20) = 0x2D;
    }
    phase = *(s32 *)(self + 0x20);
    if (phase < 0x11) {
        *(s32 *)(self + 0x1C) = phase * 8;
    } else if (phase >= 0x2D) {
        s32 remaining = *(s32 *)(self + 0x1C) - 0x10;
        *(s32 *)(self + 0x1C) = remaining;
        if (remaining <= 0) {
            if (self != 0) {
                u8 *table = *(u8 **)(self + 0x14);
                s32 offset = *(s16 *)(table + 0x18);
                void (*callback)(u8 *, s32) = *(void (**)(u8 *, s32))(table + 0x1C);
                callback(self + offset, 3);
            }
            return;
        }
    }
    *(s32 *)(self + 0x20) += 1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009D5C0);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009D7A4);

void func_8009D88C(u8 *self) {
    s32 elapsed;
    if (*(s32 *)(self + 0x140) == 0) {
        if (func_8007B150(*(u8 **)(self + 0x18)) ||
            !func_80077978(*(u8 **)(self + 0x18))) {
            *(s32 *)(self + 0x140) += 1;
        } else {
            func_8007767C(*(u8 **)(self + 0x18), (s32 *)(self + 0x12C));
        }
    }
    elapsed = *(s32 *)(self + 0x13C) + 0x15;
    *(s32 *)(self + 0x13C) = elapsed;
    if (elapsed >= 0x200 && self != 0) {
        u8 *table = *(u8 **)(self + 0x14);
        s32 offset = *(s16 *)(table + 0x18);
        void (*callback)(u8 *, s32) = *(void (**)(u8 *, s32))(table + 0x1C);
        callback(self + offset, 3);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009D944);

void func_8009DB2C(u8 *a0, s32 a1) {
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_8009DB74(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_8009DBBC(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_8009DC04(s32 a0, s32 a1) {
    register s32 object asm("$17") = a0; /* PIN $s1: keep the object across helpers. */
    register s32 flags asm("$16") = a1; /* PIN $s0: preserve the flags across helpers. */
    register s32 temp asm("$2"); /* PIN $v0: global addresses and field values. */
    register s32 temp2 asm("$3"); /* PIN $v1: global address and embedded link. */
    register s32 slot asm("$4"); /* PIN $a0: embedded link target and call argument. */
    register s32 head asm("$6"); /* PIN $a2: pointer stored through the embedded link. */
    __asm__("" : "+r"(object));

    temp = (s32)&D_8006D730;
    *(s32 *)(object + 0x18) = temp;
    temp2 = (s32)&D_8006D750;
    *(s32 *)(object + 0x14) = temp2;
    temp = (s32)&D_80065174;
    temp2 = object + 0x38;
    head = *(volatile s32 *)(object + 0x38);
    slot = *(volatile s32 *)(object + 0x3C);
    *(s32 *)(object + 0x68) = temp;
    *(s32 *)(head + 4) = slot;
    head = *(volatile s32 *)(temp2 + 4);
    temp = *(volatile s32 *)(object + 0x38);
    slot = object;
    *(s32 *)head = temp;
    *(s32 *)(object + 0x38) = temp2;
    *(s32 *)(object + 0x3C) = temp2;
    temp = (s32)&D_80065154;
    *(s32 *)(object + 0x18) = temp;
    func_8002BCEC(slot, 0);
    if (flags & 1) {
        func_8002BDA8(object);
    }
}

void func_8009DCA4(s32 a0, s32 a1) {
    register s32 object asm("$17") = a0; /* PIN $s1: keep the object across helpers. */
    register s32 flags asm("$16") = a1; /* PIN $s0: preserve the flags across helpers. */
    register s32 temp asm("$2"); /* PIN $v0: global addresses and field values. */
    register s32 temp2 asm("$3"); /* PIN $v1: global address and embedded link. */
    register s32 slot asm("$4"); /* PIN $a0: embedded link target and call argument. */
    register s32 head asm("$6"); /* PIN $a2: pointer stored through the embedded link. */
    __asm__("" : "+r"(object));

    temp = (s32)&D_8006A1BC;
    *(s32 *)(object + 0x18) = temp;
    temp2 = (s32)&D_8006A1DC;
    *(s32 *)(object + 0x14) = temp2;
    temp = (s32)&D_80065174;
    temp2 = object + 0x38;
    head = *(volatile s32 *)(object + 0x38);
    slot = *(volatile s32 *)(object + 0x3C);
    *(s32 *)(object + 0x68) = temp;
    *(s32 *)(head + 4) = slot;
    head = *(volatile s32 *)(temp2 + 4);
    temp = *(volatile s32 *)(object + 0x38);
    slot = object;
    *(s32 *)head = temp;
    *(s32 *)(object + 0x38) = temp2;
    *(s32 *)(object + 0x3C) = temp2;
    temp = (s32)&D_80065154;
    *(s32 *)(object + 0x18) = temp;
    func_8002BCEC(slot, 0);
    if (flags & 1) {
        func_8002BDA8(object);
    }
}

void func_8009DD44(s32 a0, s32 a1) {
    register s32 object asm("$17") = a0; /* PIN $s1: keep the object across helpers. */
    register s32 flags asm("$16") = a1; /* PIN $s0: preserve the flags across helpers. */
    register s32 temp asm("$2"); /* PIN $v0: global addresses and field values. */
    register s32 temp2 asm("$3"); /* PIN $v1: global address and embedded link. */
    register s32 slot asm("$4"); /* PIN $a0: embedded link target and call argument. */
    register s32 head asm("$6"); /* PIN $a2: pointer stored through the embedded link. */
    __asm__("" : "+r"(object));

    temp = (s32)&D_8006D730;
    *(s32 *)(object + 0x18) = temp;
    temp2 = (s32)&D_8006D750;
    *(s32 *)(object + 0x14) = temp2;
    temp = (s32)&D_80065174;
    temp2 = object + 0x38;
    head = *(volatile s32 *)(object + 0x38);
    slot = *(volatile s32 *)(object + 0x3C);
    *(s32 *)(object + 0x68) = temp;
    *(s32 *)(head + 4) = slot;
    head = *(volatile s32 *)(temp2 + 4);
    temp = *(volatile s32 *)(object + 0x38);
    slot = object;
    *(s32 *)head = temp;
    *(s32 *)(object + 0x38) = temp2;
    *(s32 *)(object + 0x3C) = temp2;
    temp = (s32)&D_80065154;
    *(s32 *)(object + 0x18) = temp;
    func_8002BCEC(slot, 0);
    if (flags & 1) {
        func_8002BDA8(object);
    }
}

void func_8009DDE4(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_8009DE2C(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

s32 func_8009DE74(s32 a0) {
    func_80076FD8(a0);
    *(u32 *)(a0 + 0x14) = (u32)&D_8006A5B4;
    return a0;
}

void func_8009DEA8(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)&D_8006A5B4;
    func_80077774(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_8009DEFC(u8 *owner) {
    func_8007B0B4(func_8007B16C(owner));
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009DF24);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009E0C8);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009E308);

void func_8009E4FC(u8 *a0, s32 a1) {
    register u8 *object asm("$17") = a0; /* PIN $s1: keep object live across helpers. */
    register s32 mode asm("$16") = a1; /* PIN $s0: preserve the mode argument. */

    func_8007BCA0(object);
    if (mode == 0) {
        func_80078754(object, 0xC3);
    }
    if (mode == 8) {
        func_8009E6DC(object);
    }
    if (mode == 9) {
        func_8009E738(object);
        func_8009E61C((s32)object);
    }
}

void func_8009E570(u8 *a0, s32 a1) {
    func_8007BEC0(a0);
    if (a1 == 0) {
        func_80078754(a0, 0xC3);
    }
    if (a1 == 8) {
        func_8009E6DC(a0);
    }
    if (a1 == 9) {
        func_8009E738(a0);
        func_8009E61C(a0);
    }
    if (a1 < 0xA) {
        *(s32 *)(a0 + 0x3B4) = *(s32 *)(a0 + 0x3B4) - (*(s32 *)(a0 + 0x3A4) >> 4);
        if (*(s32 *)(a0 + 0x3A8) > 0) {
            *(s32 *)(a0 + 0x3B8) = *(s32 *)(a0 + 0x3B8) - *(s32 *)(a0 + 0x3A8);
        }
    }
}

void func_8009E61C(s32 a0) {
    s32 buf[4];
    s32 tmp[3];
    s32 s0;
    s32 s2;
    s32 v;
    func_8007A724((u8 *)a0, (u8 *)buf, 4, &D_8006A42C);
    v = func_8007A084(a0);
    tmp[0] = v * 3 * 0x40;
    tmp[1] = 0;
    tmp[2] = 0;
    s2 = (s32)(u32)func_80077624((u8 *)(u32)a0);
    s0 = func_8002BE14(0xE4);
    if (s0) {
        func_8009EBB0((s32)(u32)func_8002BD80(0xE4, (void *)(u32)s0), a0, s2, buf, tmp);
    }
    func_8007AFCC(a0, s0);
    func_800787A0(a0, 0xBE);
}

void func_8009E6DC(u8 *a0) {
    u8 *s0 = func_8002BE14(0x5C);
    if (s0) {
        func_8009F500((u8 *)func_8002BD80(0x5C, s0), a0);
    }
    func_8007AFCC(a0, s0);
}

void func_8009E738(u8 *a0) {
    u8 *s0 = func_8002BE14(0x5C);
    if (s0) {
        func_8009F78C((u8 *)func_8002BD80(0x5C, s0), a0);
    }
    func_8007AFCC(a0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009E794);

void func_8009E8A4(u8 *self, s32 color) {
    s32 position[4];
    s32 scale = func_8007A084(self);
    s32 id;
    u8 *allocated;
    func_8007767C(self, position);
    position[0] = (s32)((u32)position[0] + (u32)scale * 0x180u);
    position[1] = (s32)((u32)position[1] - 0x133u);
    id = (s32)(u32)func_80077624(self);
    allocated = func_8002BE14(0xC0);
    if (allocated != 0) {
        func_8009FA24((u8 *)func_8002BD80(0xC0, allocated), self, id,
                       position, scale, color);
    }
    func_8007AFCC(self, allocated);
    func_800787A0(self, 0xBF);
}

void func_8009E97C(u8 *a0, s32 a1) {
    func_8007BD08(a0);
    if (a1 == 0) {
        *(s32 *)(a0 + 0x498) = 0xC;
        func_800774EC(a0, 0xFFFF0000);
        func_80078754(a0, 0xC5);
    }
    if (a1 == 0x12) {
        func_8009E9FC(a0);
    }
    if (a1 == 0x26) {
        func_8009EACC(a0);
    }
}

void func_8009E9FC(s32 a0) {
    s32 buf[4];
    s32 tmp[3];
    s32 s0;
    s32 s2;
    s32 v;
    *(s32 *)(a0 + 0x4A8) = 0;
    v = func_8007A084(a0);
    func_8007767C(a0, buf);
    s0 = v;
    tmp[0] = s0 << 7;
    tmp[1] = 0;
    tmp[2] = 0;
    buf[0] = buf[0] + (((s0 << 3) + s0) << 5);
    s2 = (s32)(u32)func_80077624((u8 *)(u32)a0);
    s0 = func_8002BE14(0xD8);
    if (s0) {
        func_800A030C((u8 *)func_8002BD80(0xD8, (void *)(u32)s0), a0, s2, buf, tmp, 0);
    }
    func_8007AFCC(a0, s0);
    func_800787A0(a0, 0xC0);
}

void func_8009EACC(u8 *self) {
    s32 position[4];
    s32 velocity[3];
    s32 scale;
    s32 id;
    u8 *allocated;
    *(s32 *)(self + 0x4AC) = 0;
    scale = func_8007A084(self);
    func_8007767C(self, position);
    velocity[0] = (s32)((u32)scale * 160u);
    velocity[1] = 0;
    velocity[2] = 0;
    position[0] = (s32)((u32)position[0] + (u32)scale * 384u);
    position[1] = (s32)((u32)position[1] - 0x180u);
    id = (s32)(u32)func_80077624(self);
    allocated = func_8002BE14(0xD4);
    if (allocated != 0) {
        func_800A0AE8((u8 *)func_8002BD80(0xD4, allocated), self, id,
                       position, velocity, 0);
    }
    func_8007AFCC(self, allocated);
    func_800787A0(self, 0xC0);
}

s32 func_8009EBB0(s32 self, s32 first, s32 second, s32 *position, s32 *fifth) {
    s32 x, y, z;
    func_800C72C0(self, first, position, fifth, 0x80, 0x06A82400, 0x1000, 3);
    *(u32 *)(self + 0x18) = (u32)&D_8006A56C;
    *(u32 *)(self + 0x14) = (u32)&D_8006A58C;
    *(s32 *)(self + 0xC0) = first;
    *(s32 *)(self + 0xC4) = second;
    x = position[0];
    y = position[1];
    z = position[2];
    *(s32 *)(self + 0xE0) = 0x80;
    *(s32 *)(self + 0xD8) = 0;
    *(s32 *)(self + 0xDC) = 0;
    *(s32 *)(self + 0xC8) = x;
    *(s32 *)(self + 0xCC) = y;
    *(s32 *)(self + 0xD0) = z;
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009EC74);


extern void func_800C7644(u8 *self, s32 kind);

void func_8009EDD8(u8 *self, u8 *action) {
    func_8007C0C8(self + 0x18, action);
    *(u32 *)(self + 0xDC) = 1;
    *(u32 *)(self + 0x44) |= 1u;
    func_800C7644(self, 4);
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009EE20);

void func_8009F21C(u8 *self) {
    s32 params[4];
    u8 *allocated;
    params[0] = *(s32 *)(self + 0x90);
    params[1] = *(s32 *)(self + 0x94);
    params[2] = *(s32 *)(self + 0x98);
    params[3] = *(s32 *)(self + 0x9C);
    params[1] = ((s32)func_80037010((RandomState *)(*(u32 *)(self + 0xC4) + 0x360U)) & 7) - 0x14;
    params[2] = 0;
    params[0] = -*(s32 *)(self + 0x90) >> 4;
    allocated = func_8002BE14(0x58);
    if (allocated != 0) {
        func_8009F2CC((u8 *)func_8002BD80(0x58, allocated), *(s32 *)(self + 0xC0), self + 0x80, params);
    }
    func_8002BF34(self, allocated);
}

u8 *func_8009F2CC(u8 *a0, s32 a1, s32 a2, s32 a3) {
    func_800C3258(a0, 9, a2, a3, 25, (void *)0x802020, 0);
    *(u8 **)(a0 + 0x14) = &D_8006A544;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009F31C);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009F3D8);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009F500);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009F5C4);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009F64C);

u8 *func_8009F78C(u8 *self, u8 *owner) {
    s32 image[4];
    u8 *resource;
    u8 *image_resource;
    s32 kind = func_80077730(owner);
    image_resource = D_8006A6F0;
    func_8002BC9C(self, 0);
    func_800C2F68((s32)(self + 0x18), (s32)image_resource, kind);
    resource = D_8006A46C;
    *(u8 **)(self + 0x14) = D_8006A4F4;
    *(u8 **)(self + 0x58) = owner;
    func_8007A724(owner, (u8 *)image, 4, resource);
    func_800C3314(self, image, (s32 *)((u32)resource - 0x10u), 0x80, 0x808080);
    *(s32 *)(self + 0x20) = 0x33;
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009F850);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009F8E4);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009FA24);

void func_8009FB98(s32 a0, s32 a1) {
    register s32 object asm("$17") = a0; /* PIN $s1: keep the object across helpers. */
    register s32 flags asm("$16") = a1; /* PIN $s0: preserve the flags across helpers. */
    register s32 temp asm("$2"); /* PIN $v0: global addresses and field values. */
    register s32 temp2 asm("$3"); /* PIN $v1: global address and embedded link. */
    register s32 slot asm("$4"); /* PIN $a0: embedded link target and call argument. */
    register s32 head asm("$6"); /* PIN $a2: pointer stored through the embedded link. */

    temp = (s32)&D_8006A4CC;
    temp2 = (s32)&D_80065174;
    *(s32 *)(object + 0x6C) = temp2;
    temp2 = object + 0x3C;
    slot = *(volatile s32 *)(object + 0x3C);
    *(s32 *)(object + 0x14) = temp;
    temp = *(volatile s32 *)(object + 0x40);
    *(s32 *)(slot + 4) = temp;
    head = *(volatile s32 *)(temp2 + 4);
    temp = *(volatile s32 *)(object + 0x3C);
    slot = object;
    *(s32 *)head = temp;
    *(s32 *)(object + 0x3C) = temp2;
    *(s32 *)(object + 0x40) = temp2;
    temp = (s32)&D_80065154;
    *(s32 *)(object + 0x18) = temp;
    func_8002BCEC(slot, 0);
    if (flags & 1) {
        func_8002BDA8(object);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009FC2C);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_8009FF38);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_800A030C);

void func_800A04CC(s32 a0, s32 a1) {
    register s32 object asm("$17") = a0; /* PIN $s1: keep the object across helpers. */
    register s32 flags asm("$16") = a1; /* PIN $s0: preserve the flags across helpers. */
    register s32 temp asm("$2"); /* PIN $v0: global addresses and field values. */
    register s32 temp2 asm("$3"); /* PIN $v1: global address and embedded link. */
    register s32 slot asm("$4"); /* PIN $a0: embedded link target and call argument. */
    register s32 head asm("$6"); /* PIN $a2: pointer stored through the embedded link. */

    temp = (s32)&D_8006A4A4;
    temp2 = (s32)&D_80065174;
    *(s32 *)(object + 0x6C) = temp2;
    temp2 = object + 0x3C;
    slot = *(volatile s32 *)(object + 0x3C);
    *(s32 *)(object + 0x14) = temp;
    temp = *(volatile s32 *)(object + 0x40);
    *(s32 *)(slot + 4) = temp;
    head = *(volatile s32 *)(temp2 + 4);
    temp = *(volatile s32 *)(object + 0x3C);
    slot = object;
    *(s32 *)head = temp;
    *(s32 *)(object + 0x3C) = temp2;
    *(s32 *)(object + 0x40) = temp2;
    temp = (s32)&D_80065154;
    *(s32 *)(object + 0x18) = temp;
    func_8002BCEC(slot, 0);
    if (flags & 1) {
        func_8002BDA8(object);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_800A0560);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_800A0774);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_800A0938);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_800A0A2C);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_800A0AE8);

void func_800A0CA8(s32 a0, s32 a1) {
    register s32 object asm("$17") = a0; /* PIN $s1: keep the object across helpers. */
    register s32 flags asm("$16") = a1; /* PIN $s0: preserve the flags across helpers. */
    register s32 temp asm("$2"); /* PIN $v0: global addresses and field values. */
    register s32 temp2 asm("$3"); /* PIN $v1: global address and embedded link. */
    register s32 slot asm("$4"); /* PIN $a0: embedded link target and call argument. */
    register s32 head asm("$6"); /* PIN $a2: pointer stored through the embedded link. */

    temp = (s32)&D_8006A47C;
    temp2 = (s32)&D_80065174;
    *(s32 *)(object + 0x6C) = temp2;
    temp2 = object + 0x3C;
    slot = *(volatile s32 *)(object + 0x3C);
    *(s32 *)(object + 0x14) = temp;
    temp = *(volatile s32 *)(object + 0x40);
    *(s32 *)(slot + 4) = temp;
    head = *(volatile s32 *)(temp2 + 4);
    temp = *(volatile s32 *)(object + 0x3C);
    slot = object;
    *(s32 *)head = temp;
    *(s32 *)(object + 0x3C) = temp2;
    *(s32 *)(object + 0x40) = temp2;
    temp = (s32)&D_80065154;
    *(s32 *)(object + 0x18) = temp;
    func_8002BCEC(slot, 0);
    if (flags & 1) {
        func_8002BDA8(object);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_800A0D3C);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_800A0E88);

INCLUDE_ASM("asm/us/game/nonmatchings/38D84", func_800A104C);

void func_800A1110(s32 a0, s32 a1) {
    register s32 object asm("$17") = a0; /* PIN $s1: keep the object across helpers. */
    register s32 flags asm("$16") = a1; /* PIN $s0: preserve the flags across helpers. */
    register s32 temp asm("$2"); /* PIN $v0: global addresses and field values. */
    register s32 temp2 asm("$3"); /* PIN $v1: global address and embedded link. */
    register s32 slot asm("$4"); /* PIN $a0: embedded link target and call argument. */
    register s32 head asm("$6"); /* PIN $a2: pointer stored through the embedded link. */
    __asm__("" : "+r"(object));

    temp = (s32)&D_8006D730;
    *(s32 *)(object + 0x18) = temp;
    temp2 = (s32)&D_8006D750;
    *(s32 *)(object + 0x14) = temp2;
    temp = (s32)&D_80065174;
    temp2 = object + 0x38;
    head = *(volatile s32 *)(object + 0x38);
    slot = *(volatile s32 *)(object + 0x3C);
    *(s32 *)(object + 0x68) = temp;
    *(s32 *)(head + 4) = slot;
    head = *(volatile s32 *)(temp2 + 4);
    temp = *(volatile s32 *)(object + 0x38);
    slot = object;
    *(s32 *)head = temp;
    *(s32 *)(object + 0x38) = temp2;
    *(s32 *)(object + 0x3C) = temp2;
    temp = (s32)&D_80065154;
    *(s32 *)(object + 0x18) = temp;
    func_8002BCEC(slot, 0);
    if (flags & 1) {
        func_8002BDA8(object);
    }
}
