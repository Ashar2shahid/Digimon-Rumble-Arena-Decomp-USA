#include "game_action_api.h"
#include "game_action_update_api.h"
#include "game_velocity_api.h"
#include "game_placement_api.h"
#include "game_collision_api.h"
#include "common.h"
#include "game_actor_queries.h"
#include "game_deferred.h"
#include "game_positions.h"

extern u8 D_80065154[];
extern u8 D_8006529C[];
extern u8 D_800652BC[];
extern u8 D_800652DC[];
extern u8 D_8006568C[];
extern u8 D_8006D4C4[];
extern u8 D_80010814[];
extern s32 func_8007773C(u8 *owner);
extern s32 func_80079040(u8 *actor);

u8 *func_8007A818(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4,
                  s32 arg5) {
    s32 buf[4];

    func_8007A724(arg0, buf, arg2, arg3);
    func_8007A724(arg0, arg1, arg4, arg5);
    arg1[0] = (arg1[0] + buf[0]) / 2;
    arg1[1] = (arg1[1] + buf[1]) / 2;
    arg1[2] = (arg1[2] + buf[2]) / 2;
    return (u8 *)arg1;
}

u8 *func_8007A8D0(u8 *arg0, u8 *arg1) {
    func_8007767C(arg0, (s32 *)arg1);
    *(u32 *)(arg1 + 4) = *(u32 *)(arg1 + 4) - (s32)*(s16 *)((u8 *)func_8007773C(arg0) + 2);
    return arg1;
}

s32 *func_8007A91C(u8 *arg0, s32 *arg1) {
    return func_8007767C(func_8007B16C(arg0), arg1);
}

u8 *func_8007A94C(u8 *arg0, u8 *arg1) {
    return func_8007A8D0(func_8007B16C(arg0), arg1);
}

void func_8007A97C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 > 0) {
        s32 buf[7];
        s32 s0;

        if (arg3 >= 9) {
            arg3 = 8;
        }
        s0 = arg1 * func_8007A084(arg0);
        func_8007767C(arg0, buf);
        buf[5] = -6;
        buf[6] = 0;
        buf[4] = s0 * 14;
        s0 = func_8002BE14(0x48);
        if (s0 != 0) {
            func_800C6090((u8 *)func_8002BD80(0x48, (void *)(u32)s0), 6, buf, buf + 4, arg2, arg3,
                         0xFFFFFF);
        }
        func_8007AFCC(arg0, s0);
    }
}

void func_8007AA5C(u8 *arg0, s32 arg1) {
    s32 buf[4];
    u8 *s1 = func_8002BE14(0x48);

    if (s1 != 0) {
        func_800C357C((u8 *)func_8002BD80(0x48, s1), func_8007ABA0(arg0, buf),
                      D_80010814, arg1, 0x808080);
    }
    func_8007AFCC(arg0, s1);
}

void func_8007AAF4(u8 *arg0, s32 arg1) {
    s32 buf[4];
    u8 *s0;
    u8 *s1 = func_8002BE14(0x58);

    if (s1 != 0) {
        s0 = (u8 *)func_8002BD80(0x58, s1);
        func_800C3258(s0, 8, func_8007ABA0(arg0, buf), D_80010814, arg1,
                      0xA0A0A0, 0);
        *(u8 **)(s0 + 0x14) = D_8006D4C4;
    }
    func_8007AFCC(arg0, s1);
}

u8 *func_8007ABA0(u8 *arg0, s32 *arg1) {
    s32 buf[4];
    s32 x;
    /* PIN $v1 for the first sampled coordinate, as in retail. */
    register s32 value asm("$3");

    func_8007A8D0(arg0, (u8 *)buf);
    func_8007A94C(arg0, (u8 *)arg1);
    value = buf[0];
    x = value - arg1[0];
    if (x < 0) {
        x += 3;
    }
    arg1[0] += x >> 2;
    x = buf[1] - arg1[1];
    if (x < 0) {
        x += 3;
    }
    arg1[1] += x >> 2;
    return (u8 *)arg1;
}

void func_8007AC30(u8 *arg0) {
    if (func_80079040(func_8007B16C(arg0))) {
        func_8007AAF4(arg0, 0x60);
    } else {
        func_8007AA5C(arg0, 0x100);
    }
}

void func_8007AC7C(u8 *self, u8 *owner) {
    struct __attribute__((packed)) Packet8 { u8 a, b; u16 shade; u32 data; };
    extern u8 *func_8002E6B0(const void *, s32, s32);
    extern void func_8005844C(void *, void *);
    u8 *table = *(u8 **)(self + 0x224);
    s32 index;
    u8 *slot;
    u8 *item;
    u8 *end;
    u32 shadeOffset;
    void *context;

    if (table == 0) return;
    index = *(s32 *)(self + 0x444);
    if (index < 0) return;
    slot = table + (u32)index * 8u;
    *(u32 *)(self + 0x444) = ~(u32)index;
    item = *(u8 **)slot;
    end = item + (u32)*(s32 *)(slot + 4) * 8u;
    shadeOffset = (*(s32 *)(self + 0x21C) != 0) << 8;
    context = *(void **)(owner + 0x10);
    while (item != end) {
        struct Packet8 packet;
        u8 *coordinates;
        s16 y;
        s16 x;
        u32 adjustedShade;
        packet = *(struct Packet8 *)*(u8 **)(item + 4);
        adjustedShade = shadeOffset;
        adjustedShade += packet.shade;
        packet.shade = (u16)adjustedShade;
        coordinates = *(u8 **)item;
        item += 8;
        y = *(s16 *)(coordinates + 2);
        x = *(s16 *)coordinates;
        func_8005844C(context, func_8002E6B0(&packet, x, (s32)y + shadeOffset));
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/16458", func_8007AD64);

s32 func_8007AF44(u8 *arg0) {
    return *(s32 *)(arg0 + 0x324);
}

s32 func_8007AF50(u8 *arg0) {
    return *(s32 *)(arg0 + 0x328);
}

s32 func_8007AF5C(u8 *arg0) {
    return *(s32 *)(arg0 + 0x32C);
}

s32 func_8007AF68(u8 *arg0) {
    return *(s32 *)(arg0 + 0x330);
}

void func_8007AF74(u8 *arg0) {
    switch (*(s32 *)(arg0 + 0x21C)) {
    case 0:
        func_8006F02C(*(s32 *)(arg0 + 0x228));
        break;
    case 1:
        func_8006F00C(*(s32 *)(arg0 + 0x228));
        break;
    }
}

void func_8007AFCC(u8 *arg0, u8 *node) {
    func_8006F09C(*(u8 **)(arg0 + 0x228), node);
}

void func_8007AFF0(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *s0;
    u8 *s1 = arg0;
    u8 *base = *(u8 **)(arg1 + 0x3FC);
    u8 **array = *(u8 ***)(base + 0x64);

    s0 = array[arg2];
    func_8007B04C(s1, s0, func_8002BD74(arg1));
}

void func_8007B04C(u8 *arg0, u8 *arg1, s32 arg2) {
    if (*(s32 *)(arg0 + 0x244) == 0) {
        u8 *v0 = *(u8 **)(arg0 + 0x3FC);

        func_8001F9EC(v0 + 8, arg1 != 0 ? arg1 + 8 : 0);
        *(s32 *)(arg0 + 0x244) = arg2;
        *(s32 *)(arg0 + 0x240) = func_8002BDC8(arg2);
    }
}

void func_8007B0B4(u8 *arg0) {
    u8 *s0 = arg0;
    u8 *a0;
    s32 x;

    if (*(s32 *)(s0 + 0x244) != 0) {
        a0 = *(u8 **)(s0 + 0x3FC);
        *(s32 *)(s0 + 0x244) = 0;
        *(s32 *)(s0 + 0x240) = 0;
        func_8001FACC(a0 + 8);
        a0 = *(u8 **)(s0 + 0x3FC);
        *(u32 *)(s0 + 0x384) = *(u32 *)(a0 + 0x40) << 8;
        x = *(s32 *)(a0 + 0x44);
        *(s32 *)(s0 + 0x38C) = 0;
        *(u32 *)(s0 + 0x388) = (u32)x << 8;
        func_80078090(s0);
    }
}

s32 func_8007B128(void) {
    return (u32)(*(s32 *)func_80079500() - 0xB) < 2u;
}

s32 func_8007B150(u8 *arg0) {
    return *(s32 *)(*(u8 **)(arg0 + 0x230)) == 1;
}

u8 *func_8007B16C(u8 *arg0) {
    return func_800732A8(*(u8 **)(arg0 + 0x228), arg0);
}

void func_8007B194(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079964(arg0, 0x12, 2, 0);
    }
}

void func_8007B1C0(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079964(arg0, 1, 4, 0);
        func_80078A64(arg0, 0);
        func_8007A97C(arg0, -1, 0x60, func_80077838(arg0) ? 2 : 3);
    }
    func_800785BC(arg0, -*(s32 *)(func_8007773C(arg0) + 8));
}

void func_8007B23C(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079964(arg0, 1, 4, 0);
        func_80078A7C(arg0, 0);
        func_8007A97C(arg0, -1, 0x60, func_80077838(arg0) ? 2 : 3);
    }
    func_800785BC(arg0, *(s32 *)(func_8007773C(arg0) + 8));
}

void func_8007B2B4(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        s32 buf[4];

        func_80079964(arg0, 2, 1, 0);
        func_8007767C(arg0, buf);
        if (func_8007A660(buf, -0x33, *(s16 *)(func_8007773C(arg0) + 2)) >= 0) {
            *(s32 *)(arg0 + 0x3B4) -=
                (s32)(((s64)*(s32 *)(func_8007773C(arg0) + 0xC) *
                       *(s32 *)(arg0 + 0x3C4)) >> 16);
        }
        func_80078A64(arg0, 0);
        func_8007A97C(arg0, -1, 0x60, func_80077838(arg0) ? 3 : 4);
    }
    *(s32 *)(arg0 + 0x37C) |= 0x100;
}

void func_8007B38C(u8 *arg0, s32 arg1) {
    s32 new_var;

    if (arg1 == 0) {
        s32 buf[4];

        func_80079964(arg0, 2, 1, 0);
        func_8007767C(arg0, buf);
        if (func_8007A660(buf, -0x33,
                          *(s16 *)(func_8007773C(arg0) + 2)) <= 0) {
            new_var = (s32)(((s64)*(s32 *)(func_8007773C(arg0) + 0xC) *
                             *(s32 *)(arg0 + 0x3C4)) >>
                            16);
            *(s32 *)(arg0 + 0x3B4) += new_var;
        }
        func_80078A7C(arg0, 0);
        func_8007A97C(arg0, -1, 0x60, func_80077838(arg0) ? 3 : 4);
    }
    *(s32 *)(arg0 + 0x37C) |= 0x100;
}

void func_8007B464(u8 *arg0) {
    s32 s0 = *(s32 *)(func_8007773C(arg0) + 0x10);
    s32 x = *(s32 *)(arg0 + 0x3C4);

    *(s32 *)(arg0 + 0x3B8) = (s32)(((s64)(-s0) * x) >> 16);
    *(s32 *)(arg0 + 0x3A8) = 0;
    func_80079964(arg0, 3, 1, 0);
    if (func_80077978(arg0)) {
        s32 a3 = func_80077838(arg0) ? 2 : 3;

        func_8007A97C(arg0, 1, 0x60, a3);
        func_8007A97C(arg0, -1, 0x60, a3);
    }
    s0 = *(s32 *)(func_8007773C(arg0) + 8);
    s0 += *(s32 *)(func_8007773C(arg0) + 8) / 2;
    if (s0 < *(s32 *)(arg0 + 0x3A4)) {
        *(s32 *)(arg0 + 0x3A4) = s0;
    } else if (*(s32 *)(arg0 + 0x3A4) < -s0) {
        *(s32 *)(arg0 + 0x3A4) = -s0;
    }
}

void func_8007B570(u8 *arg0) {
    func_80079964(arg0, 0x13, 2, 0);
}

void func_8007B598(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079964(arg0, 0xC, 3, 0);
    }
}

void func_8007B5C4(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079964(arg0, 0x15, 3, 0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/16458", func_8007B5F0);

void func_8007B6F4(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079964(arg0, 0xD, 1, 0);
    }
}

void func_8007B720(u8 *arg0) {
    func_80079964(arg0, 0xE, 1, 0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/16458", func_8007B748);

void func_8007B978(u8 *arg0, s32 arg1) {
    func_80079D58(arg0);
    if (arg1 == 0) {
        func_80079AA4(arg0, 5, 0, 0, -1);
    }
    func_8007B748(arg0, arg1, func_8007773C(arg0) + 0x3C, 1);
}

void func_8007B9E4(u8 *arg0, s32 arg1) {
    func_80079D58(arg0);
    if (arg1 == 0) {
        func_80079AA4(arg0, 6, 0, 0, -1);
        func_800785BC(arg0, 0);
    }
    func_8007B748(arg0, arg1, func_8007773C(arg0) + 0x60, 1);
}

void func_8007BA5C(u8 *arg0, s32 arg1) {
    func_80079D58(arg0);
    if (arg1 == 0) {
        func_80079AA4(arg0, 7, 0, 0, -1);
        *(s32 *)(arg0 + 0x3A4) -= *(s32 *)(arg0 + 0x3A4) / 2;
    }
    func_8007B748(arg0, arg1, func_8007773C(arg0) + 0x84, 2);
}

void func_8007BAE4(u8 *arg0, s32 arg1) {
    func_80079D58(arg0);
    if (arg1 == 0) {
        func_80079AA4(arg0, 0x1F, 0, 0, -1);
        func_800785BC(arg0, 0);
    }
    func_8007B748(arg0, arg1, func_8007773C(arg0) + 0xCC, 1);
}

void func_8007BB5C(u8 *arg0, s32 arg1) {
    func_80079D58(arg0);
    if (arg1 == 0) {
        func_80079964(arg0, -1, 0, 0);
        func_80079AA4(arg0, 8, 2, 0, -1);
        *(s32 *)(arg0 + 0x3A4) = 0;
        *(s32 *)(arg0 + 0x3B4) = 0;
    }
    func_8007B748(arg0, arg1, func_8007773C(arg0) + 0xA8, 2);
}

void func_8007BBE4(u8 *arg0, s32 arg1) {
    func_80079D58(arg0);
    if (arg1 == 0) {
        func_80079AA4(arg0, 0x14, 0, 0, -1);
    }
    func_8007B748(arg0, arg1, func_8007773C(arg0) + 0xF0, 1);
}

void func_8007BC50(u8 *arg0, s32 arg1) {
    func_80079D58(arg0);
    if (arg1 == 0) {
        func_80079AA4(arg0, 0xB, 0, 0, -1);
    }
}

void func_8007BCA0(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079AA4(arg0, 0x16, 0, 0, -1);
    }
}

void func_8007BCD4(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079AA4(arg0, 0x18, 0, 0, -1);
    }
}

void func_8007BD08(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079AA4(arg0, 0x1A, 0, 0, -1);
    }
}

void func_8007BD3C(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079AA4(arg0, 0x1B, 2, 0, -1);
    }
}

void func_8007BD70(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079AA4(arg0, 9, 2, 0, -1);
    }
    func_8007B748(arg0, arg1, func_8007773C(arg0) + 0x15C, 1);
}

void func_8007BDD4(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079AA4(arg0, 0xA, 2, 0, -1);
        *(s32 *)(arg0 + 0x3A8) = 0;
    }
    func_8007B748(arg0, arg1, func_8007773C(arg0) + 0x114, 1);
}

void func_8007BE3C(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079AA4(arg0, *(s32 *)(func_8007773C(arg0) + 0x18), 2, 0, -1);
        *(s32 *)(arg0 + 0x3B4) = 0;
        *(s32 *)(arg0 + 0x3A4) = 0;
        *(s32 *)(arg0 + 0x3A8) = 0;
        *(s32 *)(arg0 + 0x3AC) = 0;
        *(s32 *)(arg0 + 0x3B0) = 0;
    }
    func_8007B748(arg0, arg1, func_8007773C(arg0) + 0x138, 1);
}

void func_8007BEC0(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079AA4(arg0, 0x17, 2, 0, -1);
    }
}

void func_8007BEF4(u8 *arg0, s32 arg1) {
    if (arg1 == 0) {
        func_80079AA4(arg0, 0x19, 2, 0, -1);
    }
}

void func_8007BF28(u8 *arg0, u8 *arg1, u8 *arg2) {
    if (*(s32 *)(arg0 + 0x44C) != 0) {
        u8 *sprites = arg0 + 0x454;
        u8 *address;

        func_80079158(arg1, *(s32 *)(arg0 + 0x44C), sprites,
                      *(s32 *)(arg0 + 0x450));
        if (func_80079068(arg1, *(s32 *)(arg0 + 0x44C)) != 0) {
            u8 *allocation = func_8002BE14(0x58);

            if (allocation != 0) {
                u8 *object = (u8 *)func_8002BD80(0x58, allocation);

                func_800C3258(object, 8, arg2 + 0x14, D_80010814, 0x60,
                              0xA0A0A0, 0);
                *(u8 **)(object + 0x14) = D_8006D4C4;
            }
            address = allocation;
        } else {
            u8 *allocation = func_8002BE14(0x48);

            if (allocation != 0) {
                u8 *object = (u8 *)func_8002BD80(0x48, allocation);

                func_800C357C(object, arg2 + 0x14, sprites, 0xC0, 0x808080);
            }
            address = allocation;
        }
        func_8007AFCC(arg0, address);
        *(s32 *)(arg0 + 0x454) = 0;
        *(s32 *)(arg0 + 0x458) = 0;
        *(s32 *)(arg0 + 0x45C) = 0;
        *(s32 *)(arg0 + 0x460) = 0;
        *(s32 *)(arg0 + 0x44C) = 0;
        *(s32 *)(arg0 + 0x450) = 0;
    }
}

u8 *func_8007C064(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4) {
    s32 x0;
    s32 x1;
    s32 x2;

    *(u8 **)(arg0 + 0) = D_800652DC;
    *(s32 *)(arg0 + 4) = arg1;
    *(s32 *)(arg0 + 8) = arg2;
    *(s32 *)(arg0 + 0xC) = arg4;
    x0 = *(s32 *)(arg3 + 0);
    x1 = *(s32 *)(arg3 + 4);
    x2 = *(s32 *)(arg3 + 8);
    *(s32 *)(arg0 + 0x10) = x0;
    *(s32 *)(arg0 + 0x14) = x1;
    *(s32 *)(arg0 + 0x18) = x2;
    return arg0;
}

void func_8007C0A0(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 8) = arg1;
    *(s32 *)(arg0 + 0xC) = arg2;
}

void func_8007C0AC(u8 *arg0, u8 *arg1) {
    s32 a = *(s32 *)(arg1 + 0);
    s32 b = *(s32 *)(arg1 + 4);
    s32 c = *(s32 *)(arg1 + 8);

    *(s32 *)(arg0 + 0x10) = a;
    *(s32 *)(arg0 + 0x14) = b;
    *(s32 *)(arg0 + 0x18) = c;
}

INCLUDE_ASM("asm/us/game/nonmatchings/16458", func_8007C0C8);

void func_8007C150(u8 *arg0, u8 *arg1) {
    s32 s0;

    func_8007C0C8(arg0, arg1);
    s0 = *(s32 *)(arg1 + 0x14);
    if (s0 != 0) {
        if (func_8002BD68(s0) == 0x10000) {
            *(s32 *)(arg0 + 0x20) |= 1;
        }
        if (func_8002BD68(s0) == 0x30000) {
            *(s32 *)(arg0 + 0x20) |= 2;
        }
    }
}

s32 func_8007C1D8(u8 *arg0) {
    return *(s32 *)(arg0 + 0x20) & 1;
}

s32 func_8007C1E4(u8 *arg0) {
    return (u32)(*(u32 *)(arg0 + 0x20) >> 1) & 1;
}

u8 *func_8007C1F8(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4) {
    func_8007C064(arg0, arg1, arg2, arg3, arg4);
    *(u8 **)(arg0 + 0) = D_800652BC;
    *(s32 *)(arg0 + 0x20) &= -2;
    *(s32 *)(arg0 + 0x20) &= -3;
    return arg0;
}

u8 *func_8007C24C(u8 *arg0) {
    *(u16 *)arg0 = 0;
    *(u16 *)(arg0 + 2) = 0;
    return arg0;
}

void func_8007C25C(u8 *arg0, s16 arg1, s16 arg2) {
    *(s16 *)arg0 = arg1;
    *(s16 *)(arg0 + 2) = arg2;
}

u8 *func_8007C268(u8 *arg0, s32 arg1) {
    u8 *p = arg0;
    s32 t = *(u16 *)p * arg1;
    s32 u = *(u16 *)(p + 2);

    *(u16 *)p = t;
    *(u16 *)(p + 2) = u + (u * (arg1 - 1)) / 100;
    return p;
}

void func_8007C2B8(u8 *arg0, u8 *arg1) {
    func_80077498(arg1, *(u16 *)arg0);
    func_8007C300(arg0, arg1);
    *(u16 *)arg0 = 0;
}

void func_8007C300(u8 *arg0, u8 *arg1) {
    if (func_80077838(arg1) || func_80077860(arg1)) {
        func_800774EC(arg1, *(u16 *)(arg0 + 2));
    }
    *(u16 *)(arg0 + 2) = 0;
}

u8 *func_8007C35C(u8 *arg0, s32 arg1) {
    *(u8 **)(arg0 + 4) = D_8006529C;
    *(s32 *)arg0 = arg1;
    return arg0;
}

void func_8007C374(u8 *arg0, s32 arg1) {
    *(u8 **)(arg0 + 4) = D_8006529C;
    if (arg1 & 1) {
        func_8002B3D0(arg0);
    }
}

void func_8007C3A8(u8 *arg0) {
    u8 *v1 = *(u8 **)(arg0 + 4);
    u8 *a2 = *(u8 **)arg0;
    s32 a3 = *(s16 *)(v1 + 8);
    s32 (*fn)(u8 *, s32) = *(s32 (**)(u8 *, s32))(v1 + 0xC);

    fn(arg0 + a3, *(s32 *)(a2 + 8));
}

void func_8007C3DC(void) {
}

void func_8007C3E4(void) {
}

void func_8007C3EC(u8 *arg0, s32 arg1) {
    *(u8 **)arg0 = D_80065154;
    if (arg1 & 1) {
        func_8002B3D0(arg0);
    }
}

void func_8007C420(u8 *arg0, s32 arg1) {
    *(u8 **)arg0 = D_80065154;
    if (arg1 & 1) {
        func_8002B3D0(arg0);
    }
}

u8 *func_8007C454(u8 *arg0, s32 arg1) {
    func_8007C35C(arg0, arg1);
    *(u8 **)(arg0 + 4) = D_8006568C;
    *(s16 *)(arg0 + 8) = 0;
    *(s16 *)(arg0 + 0xA) = 0;
    *(s32 *)(arg0 + 0x40) = 0;
    *(s16 *)(arg0 + 0x4E) = 0;
    *(s16 *)(arg0 + 0x50) = 0;
    *(s16 *)(arg0 + 0x52) = 0;
    *(s16 *)(arg0 + 0x54) = 0;
    *(s16 *)(arg0 + 0x62) = 0;
    *(s16 *)(arg0 + 0x56) = 0;
    *(s16 *)(arg0 + 0x58) = 0;
    *(s16 *)(arg0 + 0x4C) = 0;
    *(s16 *)(arg0 + 0x5A) = -1;
    *(s16 *)(arg0 + 0x5C) = 0;
    *(s16 *)(arg0 + 0x5E) = 0;
    return arg0;
}
