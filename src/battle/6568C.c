#include "game_rotation.h"
#include "game_collision_forwarders.h"
#include "game_placement_api.h"
#include "game_audio_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#include "game_actor_queries.h"
#include "deferred_objects.h"
#include "game_positions.h"

extern u8 D_80065154[];
extern u8 D_8006DB70[];
extern u8 D_8006DB10[];
extern u8 D_8006DAE0[];
extern u8 D_8006DAB0[];
extern u8 D_8006DA80[];
extern u8 D_8006DD84[];
extern u32 D_8005FB74;

extern void func_8002B3D0();
extern void func_800C8C70();
extern s32 func_800C8A34();
extern void func_800C933C();
extern void func_800C937C();
extern void func_800C7EA4();
extern void func_800C7F38();
extern void func_800C80B8();
extern void func_800C83D8();
extern void func_8007754C();
extern void func_800775AC();
extern s32 func_8006F178();
extern s32 func_8007A0A0();
extern s32 func_800C91C0();
extern s32 func_800C9238();
extern s32 func_80078AD8();
extern void func_8002BCEC();
extern void func_8002BDA8();
extern u8 D_8006DA58[];
extern u8 D_8006DA30[];
extern u8 D_8006DA08[];
extern u8 D_8006D9E0[];
extern u8 D_8006D9B8[];
extern u8 D_8006D998[];
extern u8 D_8006DBB8[];
typedef struct { u8 bytes[0x14]; } ShapeRecord;
extern ShapeRecord D_8006D930[];
extern u8 D_8006D970[];
extern u8 D_800108B4[];
extern u8 D_800641B8[];
extern s32 func_8002BDC8();
extern s32 func_8002BD74();
extern u8 *func_8002BE14(s32);
extern s32 func_8002DD5C();
extern s32 func_8002EC04();
extern s32 func_8002E860();
extern s32 func_800213C4();
extern s32 func_800245B8();
extern s32 func_80024340();
extern s32 func_800C339C();
extern s32 func_8005844C();
extern s32 func_80077498();
extern s32 func_800C3F98();
extern s32 func_800C31B0();
extern s32 func_800C339C();
extern s32 func_800C72C0();
extern s32 func_800C7478();
extern s32 func_800C75F4();
extern s32 func_800C7644();
extern s32 func_800C7710();
extern s32 func_800C8BDC();
extern s32 func_80077618();
extern void func_800CB518();
extern void func_8006F06C();

extern void func_800C6588();
extern void func_800C89A0();
extern void func_800C9258();
extern void func_80079158();
extern s32 func_8007A084();
extern u8 D_8005F824[];
extern u8 D_80065174;
extern u8 D_8006D730;
extern u8 D_8006D750;
extern u8 D_8006D58C;
extern u8 D_8006DDAC[];
extern u8 D_8006DDD4[];
extern u8 D_8006DE8C[];
extern u8 D_800D3984[];
extern u8 D_800D39EC[];
extern u8 D_8006DBC4[];
extern u8 D_8006DBCC[];
extern void func_8001C1C0();
extern void func_8001BF20();
extern void func_8001C0FC();
extern void func_8001C148();
extern void func_800CF7DC();
extern void func_800CF558();
extern void func_800D0340();
extern void func_800CD820();
extern void func_800CD3F4();
extern void func_800CD4FC();
extern void func_800CD65C();
extern void func_800CD728();
extern void func_800CD764();
extern void func_800CD6CC();
extern void func_800CD60C();
extern void func_800CD798();
extern void func_800CD4C4();
extern void func_800CD550();
extern void func_800CD5D8();
extern s32 func_800CF714();

void func_800C9A4C(u8 *arg0) {
    u8 *s0 = arg0;
    s32 v;

    v = *(s32 *)(s0 + 0x468);
    if (v != 0) {
        v -= 1;
        *(s32 *)(s0 + 0x468) = v;
        if (v == 0) {
            func_8007754C();
        } else if (func_8006F178((s32)(u32)func_80077624((u8 *)(u32)s0)) == 0) {
            switch (*(s32 *)(s0 + 0x464) - 1) {
            case 0:
                if ((*(s32 *)(s0 + 0x468) & 0xF) == 0) {
                    func_800C7EA4(s0, 0, 0x80, 0x80, 0x80);
                }
                break;
            case 1:
                if ((*(s32 *)(s0 + 0x468) & 0xF) == 0) {
                    func_800C7EA4(s0, 1, 0x20, 0x20, 0x80);
                }
                break;
            case 2:
                if ((*(s32 *)(s0 + 0x468) & 0x3) == 0) {
                    func_800C80B8(s0, 0, 1, 0x808080);
                }
                break;
            case 3:
                if ((*(s32 *)(s0 + 0x468) & 0x1) == 0) {
                    func_800C7F38(s0, 0, 0x2020FF);
                }
                break;
            case 4:
                if ((*(s32 *)(s0 + 0x468) & 0x1) == 0) {
                    func_800C7F38(s0, 0, 0xFF2020);
                }
                break;
            case 5:
                if ((*(s32 *)(s0 + 0x468) & 0x1) == 0) {
                    func_800C7F38(s0, 0, 0x20FF20);
                }
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800C9BF4);

void func_800C9C6C(u8 *arg0) {
    u8 *s0 = arg0;
    s32 v0;
    s32 v1;

    v0 = *(s32 *)(s0 + 0x47C);
    if (v0 != 0) {
        v0 -= 1;
        *(s32 *)(s0 + 0x47C) = v0;
        if (v0 == 0) {
            func_800775AC(s0);
            return;
        }
        if (func_8006F178((s32)(u32)func_80077624((u8 *)(u32)s0)) != 0) {
            return;
        }
        v1 = func_8007A0A0(s0);
        if (v1 < 0xD) {
            goto cec;
        }
        if (v1 < 0xF) {
            goto cfc;
        }
        if (v1 >= 0x12) {
            goto cec;
        }
        if (v1 >= 0x10) {
            goto cfc;
        }
    cec:
        func_800775AC(s0);
        return;
    cfc:
        v1 = *(s32 *)(s0 + 0x478);
        if (v1 < 4) {
            if (v1 > 0) {
                if ((*(s32 *)(s0 + 0x47C) & 1) == 0) {
                    func_800C83D8(s0);
                }
            }
        }
    }
}

u8 *func_800C9D44(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_800C8A34(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    *(u8 **)(arg0 + 0x14) = D_8006DB10;
    return arg0;
}

void func_800C9D90(void) {
    func_800C8C70();
}

u8 *func_800C9DB0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_800C8A34(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    *(u8 **)(arg0 + 0x14) = D_8006DAE0;
    *(s32 *)(arg0 + 0xC4) = 0;
    *(s32 *)(arg0 + 0xB8) += 0x800;
    func_800C933C(arg0, 2);
    return arg0;
}

void func_800C9E18(u8 *arg0) {
    if (*(s32 *)(arg0 + 0xC4) != 0) {
        if (*(s32 *)(arg0 + 0xB8) != 0) {
            *(s32 *)(arg0 + 0xB8) = (*(s32 *)(arg0 + 0xB8) + 0x200) & 0xFFF;
        }
    }
    func_800C8C70();
}

void func_800C9E60(u8 *arg0, s32 arg1) {
    s32 v;

    if (*(s32 *)(arg0 + 0xC4) == 0 && *(s32 *)(arg0 + 0xB4) == 0) {
        v = func_800C91C0(arg0, arg1);
        if (v != 0x20000) {
            if (v > 0x20000) {
                func_800C9F14(arg0);
            } else if (v != 0x10000 || func_800C9238(arg0, func_80078AD8(arg1)) != 0) {
                func_800C9F14(arg0);
            }
        }
    } else {
        if (*(s32 *)(arg0 + 0xB8) == 0) {
            func_800C90EC(arg0, (u8 *)(u32)arg1);
        }
    }
}

void func_800C9F14(u8 *arg0) {
    *(s32 *)(arg0 + 0xC4) = 1;
    *(s32 *)(arg0 + 0xB0) = 0x1E;
    *(s32 *)(arg0 + 0x24) |= 1;
    *(s32 *)(arg0 + 0xAC) += 0x96;
    func_800C937C(arg0, 2);
}

u8 *func_800C9F5C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_800C8A34(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    *(u8 **)(arg0 + 0x14) = D_8006DAB0;
    return arg0;
}

void func_800C9FA8(void) {
    func_800C8C70();
}

u8 *func_800C9FC8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 i;
    u8 *p;

    func_800C8A34(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    *(u8 **)(arg0 + 0x14) = D_8006DA80;
    *(s32 *)(arg0 + 0xC4) = 0;
    for (i = 3, p = arg0 + 0x134; i >= 0; i--) {
        *(u16 *)p = 0;
        p -= 0x24;
    }
    return arg0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CA030);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CA2E4);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CA470);

u8 *func_800CA6EC(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *s2 = arg0;
    u8 *s0 = arg1;
    s32 s1 = arg2;
    s32 v0;
    s32 v1;

    func_8002BC9C(s2, 0);
    *(u8 **)(s2 + 0x14) = D_8006DA58;
    *(s32 *)(s2 + 0x18) = s1;
    v0 = func_80077618(s0);
    if (v0 == 0) {
        v1 = 0x30;
    } else {
        v1 = 0x110;
    }
    *(s16 *)(s2 + 0x1C) = v1;
    *(s16 *)(s2 + 0x1E) = 0x130;
    *(s32 *)(s2 + 0x20) = 0;
    return s2;
}

void func_800CA764(u8 *arg0, s32 arg1) {
    *(u8 **)(arg0 + 0x14) = D_8006DA58;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800CA7B8(u8 *arg0) {
    u8 *v0;

    if (*(s16 *)(arg0 + 0x1E) >= 0x79) {
        *(u16 *)(arg0 + 0x1E) = *(u16 *)(arg0 + 0x1E) - 0x30;
    }
    if (*(s32 *)(arg0 + 0x20) >= 0xD) {
        *(u16 *)(arg0 + 0x1E) -= 0x30;
    }
    if (*(s16 *)(arg0 + 0x1E) < -0x30) {
        if (arg0 != 0) {
            v0 = *(u8 **)(arg0 + 0x14);
            ((void (*)(u8 *, s32))*(void **)(v0 + 0x1C))(arg0 + *(s16 *)(v0 + 0x18), 3);
        }
    } else {
        *(s32 *)(arg0 + 0x20) += 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CA868);

u8 *func_800CAA24(u8 *self, u8 *owner, s32 value) {
    s32 state;
    func_8002BC9C(self, 0);
    *(u8 **)(self + 0x14) = D_8006DA30;
    *(s32 *)(self + 0x18) = func_8002BD74(owner);
    *(s32 *)(self + 0x1C) = value;
    state = func_80077618(owner);
    {
        s32 width = 0x114;
        if (state == 0) {
            width = 0x2C;
        }
        *(s16 *)(self + 0x20) = width;
    }
    *(s16 *)(self + 0x22) = 0xAC;
    *(s32 *)(self + 0x24) = 0;
    *(s32 *)(self + 0x28) = *(s32 *)(owner + 0x464);
    *(s32 *)(self + 0x2C) = 0;
    return self;
}

void func_800CAAB4(u8 *arg0, s32 arg1) {
    *(u8 **)(arg0 + 0x14) = D_8006DA30;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CAB08);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CABDC);

u8 *func_800CAD88(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_8006DA08;
    *(s32 *)(arg0 + 0x18) = func_8002BD74(arg1);
    *(s32 *)(arg0 + 0x1C) = arg2;
    *(s32 *)(arg0 + 0x20) = arg3;
    *(s32 *)(arg0 + 0x24) = arg4;
    *(s32 *)(arg0 + 0x28) = arg5;
    func_8007A8D0((u8 *)arg1, arg0 + 0x2C);
    *(s32 *)(arg0 + 0x44) = 0;
    if (*(s32 *)(arg0 + 0x1C) == 0) {
        *(s32 *)(arg0 + 0x3C) = 0;
        *(s32 *)(arg0 + 0x40) = 0x80;
    } else {
        *(s32 *)(arg0 + 0x3C) = 0x140;
        *(s32 *)(arg0 + 0x40) = 0;
    }
    return arg0;
}

void func_800CAE50(u8 *arg0, s32 arg1) {
    *(u8 **)(arg0 + 0x14) = D_8006DA08;
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800CAEA4(u8 *arg0) {
    u8 *s0 = arg0;
    u8 *p;

    p = (u8 *)func_8002BDC8(*(s32 *)(s0 + 0x18));
    if (p == 0 || *(s32 *)(s0 + 0x44) >= 8) {
        if (s0 != 0) {
            u8 *vtab = *(u8 **)(s0 + 0x14);
            ((void (*)(u8 *, s32)) * (void **)(vtab + 0x1C))(s0 + *(s16 *)(vtab + 0x18), 3);
        }
    } else {
        if (*(s32 *)(s0 + 0x1C) == 0) {
            *(s32 *)(s0 + 0x3C) = *(s32 *)(s0 + 0x3C) + 0x28;
            *(s32 *)(s0 + 0x40) = *(s32 *)(s0 + 0x40) - 0x10;
        } else {
            *(s32 *)(s0 + 0x3C) = *(s32 *)(s0 + 0x3C) - 0x28;
            *(s32 *)(s0 + 0x40) = *(s32 *)(s0 + 0x40) + 0x10;
        }
        func_8007A8D0(p, s0 + 0x2C);
        *(s32 *)(s0 + 0x44) = *(s32 *)(s0 + 0x44) + 1;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CAF70);

u8 *func_800CB1AC(u8 *arg0) {
    func_800C3F98(arg0);
    *(u8 **)(arg0 + 0x14) = D_8006D9E0;
    *(s32 *)(arg0 + 0x50) = 8;
    return arg0;
}

u8 *func_800CB1E8(u8 *self, s32 a1, s32 a2, s32 a3, s32 index, s32 angle) {
    func_800C72C0(self, a1, a2, a3, 0xC0,
                  *(s32 *)(D_8006DBB8 + index * 4), 0xA00, 2);
    *(u8 **)(self + 0x18) = D_8006D998;
    *(u8 **)(self + 0x14) = D_8006D9B8;
    *(s32 *)(self + 0xC0) = index;
    *(s32 *)(self + 0xC4) = angle & 0xFFF;
    *(s32 *)(self + 0xC8) = 0;
    return self;
}

void func_800CB280(u8 *arg0, s32 arg1) {
    s32 v;

    func_800CB518(arg0);
    v = *(s32 *)(arg0 + 0xC8);
    v = (v + 1) & 3;
    *(s32 *)(arg0 + 0xC8) = v;
    func_800C7478(arg0, arg1);
}

void func_800CB2CC(u8 *arg0, s32 arg1) {
    u8 *s1 = arg0;
    u8 *s0;

    func_8007C0C8(s1 + 0x18, (u8 *)(u32)arg1);
    func_800C7644(s1, func_800C75F4(s1));
    s0 = (u8 *)func_80078AD8(arg1);
    if (s0 != 0) {
        func_80077498((s32)func_8007B16C(s0), 0x32);
        func_800C7710(s1, s0);
    }
    if (s1 != 0) {
        u8 *vtab = *(u8 **)(s1 + 0x14);
        ((void (*)(u8 *, s32)) * (void **)(vtab + 0x1C))(s1 + *(s16 *)(vtab + 0x18), 3);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CB36C);

void func_800CB518(u8 *self) {
    s32 velocity[4];
    s32 x;
    u8 *allocation;

    x = *(s32 *)(self + 0x90);
    velocity[2] = *(s32 *)(self + 0x98);
    velocity[3] = *(s32 *)(self + 0x9C);
    velocity[0] = (s32)(0U - (u32)x) >> 2;
    velocity[1] = (s32)(0U - (u32)*(s32 *)(self + 0x94)) >> 2;
    {
        u32 random = func_80037010(&D_8005EE48);
        u32 base = (u32)velocity[0] - 8U;
        velocity[0] = (s32)(base + (u32)(random & 0xF));
    }
    {
        u32 random = func_80037010(&D_8005EE48);
        u32 base = (u32)velocity[1] - 8U;
        velocity[1] = (s32)(base + (u32)(random & 0xF));
    }

    allocation = (u8 *)func_8002BE14(0x60);
    if (allocation != 0) {
        u8 *object = (u8 *)func_8002BD80(0x60, allocation);
        func_800CB5F4(object, (s32 *)(self + 0x80), velocity,
                      *(s32 *)(self + 0xC0), *(s32 *)(self + 0xC4));
    }
    func_8002BF34((DtorNode *)self, (DtorNode *)allocation);
}

u8 *func_800CB5F4(u8 *self, s32 *position, s32 *velocity, s32 index, s32 angle) {
    ShapeRecord *table = D_8006D930;
    ShapeRecord *shape = table + index;
    func_800C31B0(self, shape, position, velocity,
                  0x80, 0x404040, 0);
    *(u8 **)(self + 0x14) = D_8006D970;
    *(s32 *)(self + 0x58) = index;
    *(s32 *)(self + 0x5C) = angle;
    return self;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CB688);

void func_800CB7C4(u8 *arg0, s32 arg1) {
    *(u8 **)arg0 = D_80065154;
    if (arg1 & 1) {
        func_8002B3D0(arg0);
    }
}

u8 *func_800CB7F8(u8 *arg0, s32 arg1) {
    *(u8 **)arg0 = D_8006DB70;
    *(s32 *)(arg0 + 4) = arg1;
    return arg0;
}

void func_800CB810(u8 *arg0, s32 arg1) {
    func_800C8BDC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800CB858(u8 *arg0, s32 arg1) {
    func_800C8BDC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800CB8A0(u8 *arg0, s32 arg1) {
    func_800C8BDC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800CB8E8(u8 *arg0, s32 arg1) {
    u8 *s1 = arg0;
    s32 s0 = arg1;

    func_800C8BDC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800CB930(u8 *arg0, s32 arg1) {
    u8 *s1 = arg0;
    s32 s0 = arg1;

    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800CB978(u8 *arg0, s32 arg1) {
    s32 s1 = (s32)arg0;
    s32 s0 = arg1;
    s32 p;
    s32 a2;
    s32 a0v;

    p = s1 + 0x38;
    a2 = *(s32 *)(s1 + 0x38);
    a0v = *(s32 *)(s1 + 0x3C);
    *(s32 *)(s1 + 0x18) = (s32)&D_8006D730;
    *(s32 *)(s1 + 0x14) = (s32)&D_8006D750;
    *(s32 *)(s1 + 0x68) = (s32)&D_80065174;
    *(s32 *)(a2 + 4) = a0v;
    a2 = *(s32 *)(p + 4);
    *(s32 *)(a2 + 0) = *(s32 *)(s1 + 0x38);
    *(s32 *)(s1 + 0x38) = p;
    *(s32 *)(s1 + 0x3C) = p;
    *(s32 *)(s1 + 0x18) = (s32)&D_80065154;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

void func_800CBA18(u8 *arg0, s32 arg1) {
    u8 *s1 = arg0;
    s32 s0 = arg1;

    *(s32 *)(s1 + 0x14) = (s32)&D_8006D58C;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CBA6C);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CBC44);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CBCC0);

void func_800CBD3C(u8 *arg0) {
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");

    v0 = *(s32 *)(arg0 + 0x30);
    v1 = *(s32 *)(arg0 + 0x3C);
    v0 += 1;
    v1 += 1;
    *(s32 *)(arg0 + 0x3C) = v1;
    *(s32 *)(arg0 + 0x30) = v0;
    if (v1 >= 0x5B) {
        if (arg0 != 0) {
            u8 *p = *(u8 **)(arg0 + 0x14);
            ((void (*)(u8 *, s32)) * (void **)(p + 0x1C))(arg0 + *(s16 *)(p + 0x18), 3);
        }
    }
}

void func_800CBD9C(u8 *arg0, s32 arg1) {
    u8 *s2 = arg0;
    s32 s3 = arg1;
    s32 s1 = *(s32 *)(s2 + 0x30);
    u8 *s0 = *(u8 **)(s2 + 0x1C);
    u8 tmp[8];

    __builtin_memcpy(tmp, s2 + 0x28, 8);
    while (s1 > 0) {
        if (*(u8 *)s0 == 0) {
            break;
        }
        func_800CF7DC(s3, tmp, (u8 *)(s2 + 0x20), *(u8 *)s0, *(s32 *)(s2 + 0x34));
        s0 += 1;
        s1 -= 1;
    }
    func_800D0340(s3);
}

void func_800CBE44(u8 *arg0, s32 arg1) {
    s32 v0 = (*(s32 *)(arg0 + 0x580) - 1) * *(s32 *)(arg0 + 0x584);

    func_800CD820(arg0 + 0x40, arg1, (0x140 - v0) / 2, 0x50);
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CBE90);

void func_800CC108(u8 *arg0, s32 arg1) {
    func_800CBD9C(arg0, arg1);
    func_800CF558(arg1 + 4, 0x5A - *(s32 *)(arg0 + 0x3C));
}

void func_800CC14C(u8 *arg0) {
    s32 v1 = *(s16 *)(arg0 + 0x1A) / *(s16 *)(arg0 + 0x18);

    switch (*(s32 *)(arg0 + 0x38)) {
    case 0:
        v1 -= 1;
        if ((*(s32 *)(arg0 + 0x3C) ^ 1) & 1) {
            s32 v0 = *(s32 *)(arg0 + 0x30) + 1;
            *(s32 *)(arg0 + 0x30) = v0;
            if (!(v0 < v1)) {
                *(s32 *)(arg0 + 0x38) = 1;
            }
        }
        break;
    case 1:
        if (*(s32 *)(arg0 + 0x3C) & 2) {
            v1 -= 1;
        }
        *(s32 *)(arg0 + 0x30) = v1;
        break;
    }
    {
        s32 v0 = *(s32 *)(arg0 + 0x3C) + 1;
        *(s32 *)(arg0 + 0x3C) = v0;
        if (v0 >= 0x2E) {
            if (arg0 != 0) {
                u8 *p = *(u8 **)(arg0 + 0x14);
                ((void (*)(u8 *, s32)) * (void **)(p + 0x1C))(arg0 + *(s16 *)(p + 0x18), 3);
            }
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CC240);

void func_800CC2C4(u8 *arg0) {
    u8 *s1 = arg0;
    u8 *s2 = s1 + 0x40;
    s32 a1;
    u8 *a0;
    s32 a2;
    s32 v0;
    s32 v1;

    switch (*(s32 *)(s1 + 0x38)) {
    case 0:
        func_800CD3F4(s2, *(s32 *)(s1 + 0x1C));
        func_800CD4FC(s2, 0x58, -0xB0, 0, 1);
        func_800CD4FC(s2, -0x58, 0xB0, 1, 1);
        func_800CD65C(s2, 0x30);
        *(s32 *)(s1 + 0x38) += 1;
        break;
    case 1:
        a0 = s2;
        a1 = 1;
        do {
            a1 -= 1;
            v0 = *(u16 *)a0;
            v1 = *(u16 *)(a0 + 2);
            v0 = (s16)v0 >> 2;
            v1 = (s16)v1 >> 2;
            *(u16 *)a0 = v0;
            *(u16 *)(a0 + 2) = v1;
            a0 += 0x14;
        } while (a1 >= 0);
        func_800CD728(s2, (s32)(((u32)*(s32 *)(s1 + 0x3C) << 5) + 0x7FU));
        if (!(*(s32 *)(s1 + 0x3C) < 4)) {
            *(s32 *)(s1 + 0x3C) = 0;
            *(s32 *)(s1 + 0x38) += 1;
        }
        break;
    case 2:
        func_800CD728(s2, (s32)(0xFFU - ((u32)*(s32 *)(s1 + 0x3C) << 4)));
        if (*(s32 *)(s1 + 0x3C) >= 8) {
            func_800CD728(s2, 0x80);
            *(s32 *)(s1 + 0x38) += 1;
        }
        break;
    case 3:
        if (*(s32 *)(s1 + 0x3C) >= 0x11) {
            *(s32 *)(s1 + 0x3C) = 0;
            *(s32 *)(s1 + 0x38) += 1;
        }
        break;
    case 4:
        func_800CD728(s2, (s32)(0x80U - ((u32)*(s32 *)(s1 + 0x3C) << 3)));
        a2 = 0;
        a0 = s2;
        do {
            a1 = -1;
            if (a2 == 0) {
                a1 = 1;
            }
            v1 = (s32)((u32)a1 * (u32)*(s32 *)(s1 + 0x3C));
            *(u16 *)a0 = (u16)((u32)*(u16 *)a0 - (u32)v1);
            v1 = (s32)((u32)a1 * ((u32)*(s32 *)(s1 + 0x3C) << 1));
            *(u16 *)(a0 + 2) = (u16)((u32)*(u16 *)(a0 + 2) + (u32)v1);
            a2 += 1;
            a0 += 0x14;
        } while (a2 < 2);
        if (*(s32 *)(s1 + 0x3C) >= 0x11) {
            if (s1 != 0) {
                u8 *p = *(u8 **)(s1 + 0x14);
                ((void (*)(u8 *, s32)) * (void **)(p + 0x1C))(s1 + *(s16 *)(p + 0x18), 3);
            }
            return;
        }
        break;
    }
    *(s32 *)(s1 + 0x3C) = (s32)((u32)*(s32 *)(s1 + 0x3C) + 1U);
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CC504);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CC6B8);

void func_800CC9B0(u8 *arg0) {
    u8 *sub;
    s32 state;

    func_800CC6B8(arg0);
    sub = arg0 + 0x40;
    state = *(s32 *)(arg0 + 0x38);
    switch (state) {
    case 1:
        if (*(s32 *)(arg0 + 0x3C) == state) {
            func_800CD60C(sub, 2, 4, 4);
        }
        break;
    case 3:
        func_800CD728(sub, 0x80);
        break;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CCA24);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CCC10);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CCD64);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CCEE0);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CD0CC);

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CD31C);

void func_800CD3A8(u8 *arg0) {
    s32 v1;
    s32 v0;
    u32 mask;


    if (*(s32 *)(arg0 + 0x38) == 0) {
        *(s32 *)(arg0 + 0x38) = 1;
        *(s16 *)(arg0 + 0x28) = 0x20;
        *(s16 *)(arg0 + 0x20) = 0x20;
        *(s16 *)(arg0 + 0x2A) = 0x20;
        *(s16 *)(arg0 + 0x22) = 0x20;
    }
    v1 = *(s32 *)(arg0 + 0x3C);
    mask = (u32)v1 & 0x10U;
    v0 = mask < 1U;
    *(s32 *)(arg0 + 0x30) = v0 << 2;
    *(s32 *)(arg0 + 0x3C) = v1 + 1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CD3F4);

void func_800CD4C4(u8 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    if (*(s32 *)(arg0 + 0x540) > 0) {
        i = 0;
        do {
            *(u16 *)(arg0 + i * 0x14 + 0) = arg1;
            *(u16 *)(arg0 + i * 0x14 + 2) = arg2;
            i++;
        } while (i < *(s32 *)(arg0 + 0x540));
    }
}

void func_800CD4FC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 t0 = *(s32 *)(arg0 + 0x540);
    s32 v1 = arg3 + arg4;
    s32 p;
    s32 n;

    if (v1 < t0) {
        t0 = v1;
    }
    if (arg3 < t0) {
        p = arg3 * 0x14 + (s32)arg0;
        n = t0 - arg3;
        do {
            *(u16 *)p = arg1;
            *(u16 *)(p + 2) = arg2;
            p += 0x14;
        } while (--n != 0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CD550);

void func_800CD5D8(u8 *arg0, s32 arg1) {
    s32 i;
    u8 *p;
    if (*(s32 *)(arg0 + 0x540) > 0) {
        i = 0;
        p = arg0 + 0xC;
        do {
            *(s32 *)p = arg1;
            p += 0x14;
        } while (++i < *(s32 *)(arg0 + 0x540));
    }
}

void func_800CD60C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 t0 = *(s32 *)(arg0 + 0x540);
    s32 v1 = arg2 + arg3;
    s32 p;
    s32 n;

    if (v1 < t0) {
        t0 = v1;
    }
    if (arg2 < t0) {
        p = arg2 * 0x14 + 0xC;
        p += (s32)arg0;
        n = t0 - arg2;
        do {
            *(s32 *)p = arg1;
            p += 0x14;
        } while (--n != 0);
    }
}

void func_800CD65C(u8 *arg0, s32 arg1) {
    s32 i;
    if (*(s32 *)(arg0 + 0x540) > 0) {
        i = 0;
        do {
            *(u16 *)(arg0 + i * 0x14 + 4) = arg1;
            *(u16 *)(arg0 + i * 0x14 + 6) = arg1;
            i++;
        } while (i < *(s32 *)(arg0 + 0x540));
    }
}

void func_800CD694(u8 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    if (*(s32 *)(arg0 + 0x540) > 0) {
        i = 0;
        do {
            *(u16 *)(arg0 + i * 0x14 + 4) = arg1;
            *(u16 *)(arg0 + i * 0x14 + 6) = arg2;
            i++;
        } while (i < *(s32 *)(arg0 + 0x540));
    }
}

void func_800CD6CC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 t0 = *(s32 *)(arg0 + 0x540);
    s32 v1 = arg3 + arg4;
    s32 p;
    s32 n;

    if (v1 < t0) {
        t0 = v1;
    }
    if (arg3 < t0) {
        p = arg3 * 0x14 + (s32)arg0;
        n = t0 - arg3;
        do {
            *(u16 *)(p + 4) = arg1;
            *(u16 *)(p + 6) = arg2;
            p += 0x14;
        } while (--n != 0);
    }
}

void func_800CD720(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x548) = arg1;
}

void func_800CD728(u8 *arg0, s32 arg1) {
    s32 i;
    if (*(s32 *)(arg0 + 0x540) > 0) {
        i = 0;
        do {
            *(u8 *)(arg0 + i * 0x14 + 0xA) = arg1;
            *(u8 *)(arg0 + i * 0x14 + 9) = arg1;
            *(u8 *)(arg0 + i * 0x14 + 8) = arg1;
            i++;
        } while (i < *(s32 *)(arg0 + 0x540));
    }
}

void func_800CD764(u8 *arg0, s32 arg1) {
    s32 i;
    u8 *p;
    if (*(s32 *)(arg0 + 0x540) > 0) {
        i = 0;
        p = arg0 + 0xB;
        do {
            *(u8 *)p = arg1;
            p += 0x14;
        } while (++i < *(s32 *)(arg0 + 0x540));
    }
}

void func_800CD798(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 t0 = *(s32 *)(arg0 + 0x540);
    s32 v1 = arg2 + arg3;
    s32 p;
    s32 n;

    if (v1 < t0) {
        t0 = v1;
    }
    if (arg2 < t0) {
        p = arg2 * 0x14 + 0xB;
        p += (s32)arg0;
        n = t0 - arg2;
        do {
            *(u8 *)p = arg1;
            p += 0x14;
        } while (--n != 0);
    }
}

void func_800CD7E8(u8 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    u8 *p;
    if (*(s32 *)(arg0 + 0x540) > 0) {
        i = 0;
        p = arg0 + 0x10;
        do {
            *(s32 *)p = arg1;
            arg1 += arg2;
            p += 0x14;
        } while (++i < *(s32 *)(arg0 + 0x540));
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CD820);

u8 *func_800CD988(u8 *arg0, s32 arg1) {
    u8 *s0 = arg0;
    s32 s1 = arg1;
    u8 *v1;

    func_8002BC9C(s0, 0);
    v1 = D_8006DD84;
    *(u8 **)(s0 + 0x14) = v1;
    *(s32 *)(s0 + 0x24) = 0x149;
    *(s32 *)(s0 + 0x18) = s1;
    *(s32 *)(s0 + 0x20) = 0;
    *(s32 *)(s0 + 0x28) = 0;
    *(s32 *)(s0 + 0x1C) = 0;
    D_8005FB74 = 0;
    func_8001C1C0();
    func_8001C0FC(0x11, 1);
    func_8001C148(D_8005F824);
    return s0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/6568C", func_800CDA08);
