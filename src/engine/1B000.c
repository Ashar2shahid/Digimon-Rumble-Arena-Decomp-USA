#include "common.h"

typedef struct H2EA {
    u32 f0;
    u32 f4;
    u32 f8;
    s32 n;
    u8 reserved10[0x20];
    u8 text[0x1000];
} H2EA;

extern H2EA **D_80064314;
extern void func_8002AA24(H2EA **, s32, s32);
extern void func_8002AA78(H2EA **, s32, s32, s32);
extern void func_8002B0CC(void *);
extern void func_8002B3D0(void *);
extern s32 func_8002AF18(u8);
extern void *func_8002B074(s32);


INCLUDE_ASM("asm/us/main/nonmatchings/1B000", func_8002A810);

void func_8002A8A0(s32 a0, s32 a1) {
    if (D_80064314 != NULL) {
        func_8002AA24(D_80064314, a0, a1);
    }
}

void func_8002A8D0(s32 a0, s32 a1, s32 a2) {
    a0 &= 0xFF;
    a1 &= 0xFF;
    a2 &= 0xFF;
    if (D_80064314 != NULL) {
        func_8002AA78(D_80064314, a0, a1, a2);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1B000", func_8002A908);

H2EA **func_8002A94C(H2EA **self, s32 x, s32 y) {
    *self = func_8002B074(sizeof(H2EA));
    (*self)->f4 = x;
    (*self)->f8 = y;
    (*self)->n = 0;
    (*self)->text[0] = 0;
    if (D_80064314 == NULL) {
        D_80064314 = self;
    }
    return self;
}

void func_8002A9CC(H2EA **a0, s32 a1) {
    if (D_80064314 == a0) {
        D_80064314 = NULL;
    }
    func_8002B0CC(*a0);
    if (a1 & 1) {
        func_8002B3D0(a0);
    }
}

void func_8002AA24(H2EA **a0, s32 a1, s32 a2) {
    H2EA *p = *a0;
    s32 n = p->n;

    if (n < 0xF9D) {
        u8 *q = (u8 *)p + (n + 0x30);

        q[0] = 0x1F;
        q[1] = a1;
        q[2] = a2;
        q[3] = 0;
        (*a0)->n += 3;
    }
}

void func_8002AA78(H2EA **a0, s32 a1, s32 a2, s32 a3) {
    H2EA *p;
    s32 n;
    u8 *q;

    a1 &= 0xFF;
    a2 &= 0xFF;
    a3 &= 0xFF;
    p = *a0;
    n = p->n;

    if (n < 0xF9D) {
        q = (u8 *)p + (n + 0x30);

        q[0] = 0x1E;
        q[1] = a1;
        q[2] = a2;
        q[3] = a3;
        q[4] = 0;
        (*a0)->n = (*a0)->n + 4;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1B000", func_8002AAD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1B000", func_8002AB08);

INCLUDE_ASM("asm/us/main/nonmatchings/1B000", func_8002ABD4);

void func_8002AE80(H2EA **self) {
    (*self)->n = 0;
    (*self)->text[0] = 0;
}

u8 *func_8002AE98(u8 *out, u8 *in) {
    s32 i;
    s32 byte;

    for (i = 0; i < 3; i++) {
        byte = func_8002AF18(*in++);
        if (byte >= 0) {
            byte = (byte << 4) + func_8002AF18(*in++);
            *out++ = byte;
        }
    }
    return in;
}

s32 func_8002AF18(u8 a0) {
    s32 temp_a0 = a0 & 0xFF;
    s32 temp_v1 = temp_a0 - 0x30;

    if ((u32)(temp_v1 & 0xFF) < 10) {
        return temp_v1;
    }
    if ((u32)(temp_a0 - 0x61) < 6U) {
        return temp_a0 - 0x57;
    }
    if ((u32)(temp_a0 - 0x41) < 6U) {
        return temp_a0 - 0x37;
    }
    return -1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1B000", func_8002AF68);

INCLUDE_ASM("asm/us/main/nonmatchings/1B000", func_8002AFFC);
