#include "game_action_api.h"
#include "game_action_update_api.h"
#include "game_velocity_api.h"
#include "game_placement_api.h"
#include "game_audio_api.h"
#include "game_collision_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_actor_queries.h"

extern u8 D_8006CF64[];
extern void func_8001BEDC(s32);
extern u8 D_8006CF6C[];
extern u8 D_8006CAC4[];
extern u8 D_8006CAE4[];
extern u8 D_8006C9CC[];
extern u8 D_8006C9EC[];
extern u8 D_8006C97C[];
extern u8 D_8006C99C[];
extern void func_800A96E0(s32, s32);

extern void func_8002BCEC(s32, s32);
extern s32 func_8002BE14(s32);
extern void func_8002BDA8(s32);
extern void func_80077774(s32, s32);
extern void func_8007AFCC(s32, s32);
extern void func_8007B9E4(s32, s32);
extern void func_8007BAE4(s32, s32);
extern void func_8007BB5C(s32, s32);
extern void func_8007BD70(s32, s32);
extern void func_8007BDD4(s32, s32);
extern void func_8007BE3C(s32, s32);
extern void func_800BF3A0(s32, s32, s32, s32, s32);
extern void func_800A9C50(s32, s32);
extern void func_800BEA88(s32, s32);
extern void func_800BECD4(s32, s32);
extern void func_800BF4F0(s32, s32, s32, s32);
extern s32 func_800BF634(void);
extern s32 func_800BF670(s32);
extern void func_800C096C(s32, s32);
extern u8 *func_80078AD8(u8 *);
extern u8 D_8005F8B8[];
extern s32 func_80077618(void);

extern void func_800C6588(s32, s32, u8 *, s32, s32, s32, s32);
extern void func_800C0F5C(s32, s32, u8 *);
extern u8 D_8006CDEC[];
extern u8 D_80065174[];
extern u8 D_80065154[];
extern u8 D_8006CE14[];
extern s32 func_8007A084(u8 *);
extern s32 func_80077730(u8 *);
extern u8 D_8006CDC4[];
extern void func_8007BA5C(s32, s32);
extern u8 *func_8007773C(s32);
typedef struct Node {
    struct Node *next;
    struct Node *prev;
} Node;
typedef struct Object {
    u8 pad[0x38];
    Node head;
} Object;
extern void func_8007BD08(u8 *, s32);
extern s32 func_80078754(u8 *, s32);
extern void func_800774EC(u8 *, s32);
extern void func_800C02FC(s32);
extern void func_800C0364(s32);
extern void func_800C04AC(s32);
extern void func_8007BD3C(u8 *, s32);
typedef struct DispatchState {
    u8 pad[0x498];
    s32 value;
} DispatchState;
extern u8 D_8006CE3C[];
extern u8 *func_80076FD8(u8 *);
typedef struct CallbackObject {
    u8 pad[0x14];
    u8 *vtable;
} CallbackObject;
extern void func_8007BCA0(u8 *, s32);
extern void func_80079D80(u8 *, s32);
typedef struct CleanupState {
    u8 pad[0x448];
    s32 field448;
    s32 field44C;
    s32 field450;
    s32 field454;
    s32 field458;
    s32 field45C;
    s32 field460;
} CleanupState;

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BD5EC);

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BD748);

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BD908);

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BDB94);

extern void func_8007C064(u8 *, s32, s32, u8 *, s32);
extern void func_80075F88(u8 *, u8 *, s32, u8 *);
extern s32 func_8002BD74(s32);
extern u8 D_80010814[];
u8 *func_800BDD08(u8 *a0, u8 *a1, s32 *a2, s32 a3, s32 a4) {
    u8 *resource;
    s32 object;
    s32 field94;
    s32 field98;
    s32 field9C;
    func_8002BC9C(a0, 0x30000);
    resource = a0 + 0x18;
    func_8007C064(resource, (s32)a1, 0x05B04000, D_80010814, 0);
    *(u8 **)(a0 + 0x18) = D_8006C9CC;
    *(u8 **)(a0 + 0x14) = D_8006C9EC;
    func_80075F88(a0 + 0x38, D_80010814, 0, resource);
    *(s32 *)(a0 + 0x4C) = (s32)a0;
    object = func_8002BD74((s32)a1);
    *(s32 *)(a0 + 0x80) = object;
    *(s32 *)(a0 + 0x84) = 0;
    *(s32 *)(a0 + 0x88) = 0;
    *(s32 *)(a0 + 0x8C) = 0;
    *(s32 *)(a0 + 0x90) = 0;
    field94 = a2[0];
    field98 = a2[1];
    field9C = a2[2];
    *(s32 *)(a0 + 0xA4) = 0;
    *(s32 *)(a0 + 0xA8) = 0;
    *(s32 *)(a0 + 0xAC) = 0;
    *(s32 *)(a0 + 0xB0) = 0;
    *(s32 *)(a0 + 0xB4) = 0;
    *(s32 *)(a0 + 0xBC) = 0;
    *(s32 *)(a0 + 0xC0) = 0;
    *(s32 *)(a0 + 0xC4) = 0;
    *(s32 *)(a0 + 0xC8) = a3;
    *(s32 *)(a0 + 0xCC) = 0;
    *(s32 *)(a0 + 0x94) = field94;
    *(s32 *)(a0 + 0x98) = field98;
    *(s32 *)(a0 + 0x9C) = field9C;
    *(s32 *)(a0 + 0xB8) = a4;
    *(s32 *)(a0 + 0xD0) = func_80077730(a1);
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BDE38);

void func_800BE1E0(u8 *a0, u8 *a1) {
    u8 *resource;
    s32 value;
    s32 vtable;
    func_8007C0C8(a0 + 0x18, a1);
    resource = func_80078AD8(a1);
    if (resource != 0) {
        func_8007767C(resource, (s32 *)(a0 + 0xA4));
        *(s32 *)(a0 + 0xC4) = 2;
        value = (s32)func_8007B16C(resource);
        vtable = *(s32 *)(a0 + 0x14);
        ((void (*)(s32, s32))(*(s32 *)(vtable + 0x24)))(a0 + *(s16 *)(vtable + 0x20), value);
        {
            Object *object = (Object *)a0;
            Node *head = &object->head;
            object->head.next->prev = object->head.prev;
            head->prev->next = object->head.next;
            object->head.next = head;
            object->head.prev = head;
        }
    }
}

extern void func_8002BF34(s32, s32);
extern void func_800C6324(s32, s32, u8 *, s32, s32, s32, s32);

extern u8 D_8006C954[];
extern u8 D_8005F824[];
extern u8 *func_800BE654(u8 *, s32, s32, s32, s32, u8 *);
void func_800BE284(s32 a0, s32 a1) {
    s32 object;
    object = func_8002BE14(0xE0);
    if (object != 0) {
        func_800BE654((u8 *)func_8002BD80(0xE0, (void *)(u32)object), a1, (u8 *)(a0 + 0xA4),
                      (u8 *)0x5DB08000, 0x700, D_8006C954);
    }
    func_8002BF34(a0, object);
    object = func_8002BE14(0x3C);
    if (object != 0) {
        func_800C6324((s32)(u32)func_8002BD80(0x3C, (void *)(u32)object), 3, (u8 *)(a0 + 0xA4),
                      0x700, 0x100, 0x30, 0x808080);
    }
    func_8002BF34(a0, object);
    func_8001BE78((s32)(u32)D_8005F824, 0x10A, 0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BE37C);

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BE654);

void func_800BE764(u8 *a0) {
    func_8001BEDC(*(s32 *)(a0 + 0xD4));
    *(s32 *)(a0 + 0xD4) = 0;
}


INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BE794);

void func_800BE9D4(u8 *a0, u8 *a1) {
    func_8007C0C8(a0 + 0x18, a1);
    if (func_80078AD8(a1) != 0) {
        Object *object = (Object *)a0;
        Node *head = &object->head;
        object->head.next->prev = object->head.prev;
        head->prev->next = object->head.next;
        object->head.next = head;
        object->head.prev = head;
    }
}

void func_800BEA40(s32 a0, s32 a1) {
    func_800A9C50(a0, a1);
    func_800BEA88(a0, a1);
    func_800BECD4(a0, a1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BEA88);

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BECD4);

void func_800BF01C(u8 *arg0, s32 arg1) {
    func_80077774((s32)arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8((s32)arg0);
    }
}

void func_800BF064(u8 *arg0, s32 arg1) {
    func_8002BCEC((s32)arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8((s32)arg0);
    }
}

void func_800BF0AC(u8 *a0, s32 a1) {
    Object *object = (Object *)a0;
    Node *head = &object->head;
    *(u8 **)(a0 + 0x18) = D_8006CAC4;
    *(u8 **)(a0 + 0x14) = D_8006CAE4;
    *(u8 **)(a0 + 0x68) = D_80065174;
    object->head.next->prev = object->head.prev;
    head->prev->next = object->head.next;
    object->head.next = head;
    object->head.prev = head;
    *(u8 **)(a0 + 0x18) = D_80065154;
    func_8002BCEC((s32)a0, 0);
    if (a1 & 1) {
        func_8002BDA8((s32)a0);
    }
}

void func_800BF14C(u8 *arg0, s32 arg1) {
    func_8002BCEC((s32)arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8((s32)arg0);
    }
}

void func_800BF194(u8 *arg0, s32 arg1) {
    func_8002BCEC((s32)arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8((s32)arg0);
    }
}

void func_800BF1DC(u8 *arg0, s32 arg1) {
    func_8002BCEC((s32)arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8((s32)arg0);
    }
}

void func_800BF224(u8 *arg0, s32 arg1) {
    func_8002BCEC((s32)arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8((s32)arg0);
    }
}

void func_800BF26C(u8 *a0, s32 a1) {
    Object *object = (Object *)a0;
    Node *head = &object->head;
    *(u8 **)(a0 + 0x18) = D_8006C9CC;
    *(u8 **)(a0 + 0x14) = D_8006C9EC;
    *(u8 **)(a0 + 0x68) = D_80065174;
    object->head.next->prev = object->head.prev;
    head->prev->next = object->head.next;
    object->head.next = head;
    object->head.prev = head;
    *(u8 **)(a0 + 0x18) = D_80065154;
    func_8002BCEC((s32)a0, 0);
    if (a1 & 1) {
        func_8002BDA8((s32)a0);
    }
}

void func_800BF30C(s32 a0, s32 a1) {
    *(u32 *)(a0 + 0x18) = (u32)D_8006C97C;
    *(u32 *)(a0 + 0x14) = (u32)D_8006C99C;
    func_800A96E0(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

u8 *func_800BF36C(u8 *a0) {
    func_80076FD8(a0);
    ((CallbackObject *)a0)->vtable = D_8006CE3C;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BF3A0);

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BF4F0);

s32 func_800BF634(void) {
    s32 *base = (s32 *)D_8005F8B8;
    s32 index = func_80077618();
    base = (s32 *)((s32)base - -(index * 24));
    return base[0xCC];
}

s32 func_800BF670(s32 arg0) {
    s32 *p = (s32 *)D_8006CF64;
    s32 i = func_800BF634() != 0;
    return p[i];
}

s32 func_800BF6A8(void) {
    s32 *p = (s32 *)D_8006CF6C;
    s32 i = func_800BF634() != 0;
    return p[i];
}

void func_800BF6E0(s32 arg0, s32 arg1) {
    func_8007B978((u8 *)(u32)arg0, arg1);
    if (arg1 == 0) {
        func_800BF4F0(arg0, 2, 4, func_800BF670(arg0));
    }
}

void func_800BF734(s32 arg0, s32 arg1) {
    func_8007B9E4(arg0, arg1);
    if (arg1 == 0) {
        func_800BF3A0(arg0, 2, 9, func_800BF670(arg0), 0);
    }
}

void func_800BF78C(s32 a0, s32 a1) {
    func_8007BA5C(a0, a1);
    if (a1 == 2) {
        func_800BF3A0(a0, 4, 0x12, func_800BF670(a0), 0);
    }
    if (a1 == 8) {
        *(u32 *)(a0 + 0x44C) = *(u32 *)(func_8007773C(a0) + 0xA4) | 0x80000000;
    }
}

void func_800BF80C(s32 arg0, s32 arg1) {
    func_8007BAE4(arg0, arg1);
    if (arg1 == 0) {
        func_800BF4F0(arg0, 2, 10, func_800BF670(arg0));
    }
}

void func_800BF860(s32 arg0, s32 arg1) {
    func_8007BB5C(arg0, arg1);
    if (arg1 == 0) {
        func_800BF3A0(arg0, 2, 17, func_800BF670(arg0), 0);
    }
}

void func_800BF8B8(s32 arg0, s32 arg1) {
    func_8007BDD4(arg0, arg1);
    if (arg1 == 2) {
        func_800BF3A0(arg0, 2, 12, func_800BF670(arg0), 1);
    }
}

void func_800BF918(s32 arg0, s32 arg1) {
    func_8007BE3C(arg0, arg1);
    if (arg1 == 2) {
        func_800BF3A0(arg0, 2, 16, func_800BF670(arg0), 0);
    }
}

void func_800BF974(s32 arg0, s32 arg1) {
    func_8007BD70(arg0, arg1);
    if (arg1 == 2) {
        func_800BF3A0(arg0, 2, 8, func_800BF670(arg0), 0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BF9D0);

void func_800BFC88(u8 *a0, s32 a1) {
    CleanupState *object = (CleanupState *)a0;
    func_8007BCA0(a0, a1);
    func_800785BC(a0, 0);
    if (a1 == 0) {
        object->field44C = 0x800000;
        object->field454 = 0;
        object->field458 = 0;
        object->field45C = 0;
        object->field460 = 0;
        object->field450 = 1;
        *(s32 *)(a0 + 0x498) = 4;
        func_80078754(a0, 0x118);
    }
    if (a1 == 4) {
        func_800BFE24((s32)a0);
        func_80079D80(a0, 0x3C);
    }
    if (a1 == 0xE) {
        func_800BF4F0((s32)a0, 8, 0x10, ((s32 (*)(s32))func_800BF6A8)((s32)a0));
    }
    object->field448 = 0x20;
}

extern void func_8007BEC0(u8 *, s32);
void func_800BFD50(u8 *a0, s32 a1) {
    CleanupState *object = (CleanupState *)a0;
    func_8007BEC0(a0, a1);
    if (a1 == 0) {
        object->field44C = 0x800000;
        *(s32 *)(a0 + 0x454) = 0;
        *(s32 *)(a0 + 0x458) = 0;
        *(s32 *)(a0 + 0x45C) = 0;
        *(s32 *)(a0 + 0x460) = 0;
        object->field450 = 1;
        *(s32 *)(a0 + 0x498) = 4;
        func_80078754(a0, 0x118);
    }
    if (a1 == 4) {
        func_800BFE24((s32)a0);
    }
    if (a1 >= 4) {
        *(s32 *)(a0 + 0x3A4) = 0;
        *(s32 *)(a0 + 0x3A8) = 0;
        *(s32 *)(a0 + 0x3B4) = 0;
        *(s32 *)(a0 + 0x3B8) -= 0x71C;
    }
    if (a1 == 0xE) {
        func_800BF4F0((s32)a0, 8, 0x13, ((s32 (*)(s32))func_800BF6A8)((s32)a0));
    }
    object->field448 = 0x20;
}

void func_800BFE24(s32 arg0) {
    s32 s0;
    s0 = func_8002BE14(0xB0);
    if (s0 != 0) {
        func_800C096C((s32)(u32)func_8002BD80(0xB0, (void *)(u32)s0), arg0);
    }
    func_8007AFCC(arg0, s0);
}

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800BFE80);

void func_800C01E0(u8 *a0, s32 a1) {
    func_8007BD08(a0, a1);
    if (a1 == 0) {
        func_80078754(a0, 0x116);
        ((DispatchState *)a0)->value = 10;
        func_800774EC(a0, (s32)0xFFFF0000);
    }
    if (a1 == 4) {
        func_800C02FC((s32)a0);
    }
    if (a1 >= 5) {
        func_800C0364((s32)a0);
    }
    func_800C04AC((s32)a0);
}

void func_800C0268(u8 *a0, s32 a1) {
    func_8007BD3C(a0, a1);
    if (a1 == 0) {
        func_80078754(a0, 0x116);
        ((DispatchState *)a0)->value = 10;
        func_800774EC(a0, (s32)0xFFFF0000);
    }
    if (a1 == 4) {
        func_800C02FC((s32)a0);
    }
    if (a1 >= 5) {
        func_800C0364((s32)a0);
    }
    *(s32 *)((u8 *)a0 + 0x3B8) -= 0x71C;
    func_800C04AC((s32)a0);
}

void func_800C02FC(s32 a0) {
    s32 buffer[4];
    s32 object;
    func_8007767C((u8 *)a0, buffer);
    object = func_8002BE14(0x2AC);
    if (object != 0) {
        func_800C0F5C((s32)(u32)func_8002BD80(0x2AC, (void *)(u32)object), a0, (u8 *)buffer);
    }
    func_8007AFCC(a0, object);
}

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800C0364);

void func_800C04AC(s32 a0) {
    s32 buffer[4];
    s32 object;
    func_8007767C((u8 *)a0, buffer);
    object = func_8002BE14(0x3C);
    if (object != 0) {
        func_800C6588((s32)(u32)func_8002BD80(0x3C, (void *)(u32)object), 3, (u8 *)buffer, 0x50, 0x60, 1, 0x808080);
    }
    func_8007AFCC(a0, object);
}

u8 *func_800C0534(u8 *a0, u8 *a1) {
    s32 buffer[4];
    s32 i;
    s32 *destination;
    func_8002BC9C(a0, 0);
    *(u8 **)(a0 + 0x14) = D_8006CE14;
    *(u8 **)(a0 + 0x18) = a1;
    *(s32 *)(a0 + 0x9C) = 0;
    *(s32 *)(a0 + 0xA0) = 0;
    *(s32 *)(a0 + 0xA4) = 0;
    *(s32 *)(a0 + 0xA8) = func_8007A084(a1) < 1;
    *(s32 *)(a0 + 0xAC) = 0;
    *(s32 *)(a0 + 0xB0) = func_80077730(a1);
    func_8007767C(a1, buffer);
    destination = (s32 *)(a0 + 0x1C);
    for (i = 7; i >= 0; i--) {
        destination[0] = buffer[0];
        destination[1] = buffer[1];
        destination[2] = buffer[2];
        destination += 4;
    }
    return a0;
}

void func_800C05E0(u8 *a0) {
    s32 value;
    /* PIN $v1 for the independent 0xAC counter. */
    register s32 count asm("$3");
    if (*(s32 *)(a0 + 0x9C) == 0) {
        value = *(s32 *)(a0 + 0xA0) + 1;
        *(s32 *)(a0 + 0xA0) = value;
        if (value >= 8) {
            *(s32 *)(a0 + 0xA0) = 0;
        }
        value = *(s32 *)(a0 + 0xA4) + 1;
        *(s32 *)(a0 + 0xA4) = value;
        if (value >= 8) {
            *(s32 *)(a0 + 0xA4) = 8;
        }
        func_8007767C(*(u8 **)(a0 + 0x18), (s32 *)(a0 + ((*(s32 *)(a0 + 0xA0) << 4) + 0x1C)));
        count = *(s32 *)(a0 + 0xAC) + 1;
        *(s32 *)(a0 + 0xAC) = count;
        if (count >= 9) {
            *(s32 *)(a0 + 0x9C) += 1;
        }
    } else {
        value = *(s32 *)(a0 + 0xA4) - 1;
        *(s32 *)(a0 + 0xA4) = value;
        if (value <= 0 && a0 != 0) {
            s32 vtable = *(s32 *)(a0 + 0x14);
            ((void (*)(s32, s32))(*(s32 *)(vtable + 0x1C)))((s32)a0 + *(s16 *)(vtable + 0x18), 3);
        }
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800C06D0);

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800C096C);

void func_800C0ACC(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006CDEC;
    func_8001BEDC(*(s32 *)(a0 + 0xAC));
    *(u8 **)(a0 + 0x68) = D_80065174;
    {
        Object *object = (Object *)a0;
        Node *head = &object->head;
        object->head.next->prev = object->head.prev;
        head->prev->next = object->head.next;
        object->head.next = head;
        object->head.prev = head;
    }
    *(u8 **)(a0 + 0x18) = D_80065154;
    func_8002BCEC((s32)a0, 0);
    if (a1 & 1) {
        func_8002BDA8((s32)a0);
    }
}
INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800C0B68);


INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800C0CFC);

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800C0F5C);

void func_800C11AC(u8 *a0, s32 a1) {
    *(u8 **)(a0 + 0x14) = D_8006CDC4;
    func_8001BEDC(*(s32 *)(a0 + 0x2A8));
    *(u8 **)(a0 + 0x68) = D_80065174;
    {
        Object *object = (Object *)a0;
        Node *head = &object->head;
        object->head.next->prev = object->head.prev;
        head->prev->next = object->head.next;
        object->head.next = head;
        object->head.prev = head;
    }
    *(u8 **)(a0 + 0x18) = D_80065154;
    func_8002BCEC((s32)a0, 0);
    if (a1 & 1) {
        func_8002BDA8((s32)a0);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800C1248);

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800C141C);

INCLUDE_ASM("asm/us/game/nonmatchings/5922C", func_800C1540);
