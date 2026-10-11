#include "mesh_scene_visibility.h"
#include "game_math.h"
#include "game_placement_api.h"
#include "game_audio_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#pragma interface
extern "C" {

extern u8 D_800D42C4[];
extern u8 D_80065154[];

extern void func_8006F23C(void);
extern void func_8001FACC(u8*);
extern void func_8002BCEC(u8*, u32);
extern void func_8002BDA8(u8*);
extern s32 func_8002BDC8(s32);
extern s32 func_80031C20(s32, s32);
extern void func_8001F9EC(u8*, s32);
extern u8 D_8005F824[];
extern u8 D_800D3F4C[];
extern u8 D_800D3F5C[];
extern u8 D_800D4164[];
extern u8 D_800D418C[];
extern u8 D_800D41B4[];
extern u8 D_800D41DC[];
extern u8 D_800D422C[];
extern u8 D_800D4254[];
extern u8 D_800D42E4[];
extern u8 D_800D430C[];
extern u8 D_800D4384[];
extern u8 D_800D43F4[];

extern void func_80023B10(u8 *, u8 *, u8 *);
extern s32 func_800254CC(u8 *, s32);
extern u8 *func_8002BE14(s32);
extern void func_8002BF34(u8 *, u8 *);

extern void func_80031DB4(u32, u32);
extern void func_8003EC6C(u8 *, u8 *, u8 *);
extern s32 func_8006ED08(u8 *);
extern u8 *func_800700B0(u8 *, s32);
extern void func_80077654(u8 *, u8 *);
extern u8 *func_8007773C(u8 *);
extern void func_800C6588(u8 *, s32, u8 *, s32, s32, s32, s32);
extern void func_800D57B0(u8 *, u8 *);
extern s32 func_800D6588(u8 *, u32);
extern void func_800D6F7C(u8 *);
extern void func_800D70DC(u8 *);
extern void func_800D7100(u8 *);
extern void func_800D7278(s32, u8 *, u8 *, u8 *);
extern void func_800D7C08(u8 *, u8 *, s32);
extern void func_800D7E9C(u8 *, u8 *, s32);
extern void func_8002B3D0(u8 *);
extern void func_800D5D54(u8 *);
extern void func_800D7224(u8 *, u8 *);

void func_800D4444(u8 *a0) {
    u8 *s0 = D_800D43F4;
    u8 *s2 = D_800D4384;
    u16 buf[8];
    s32 i;
    for (i = 6; i >= 0; i--) {
        func_80023B10(a0, (u8 *)buf, s2);
        s2 += 0x10;
        *(u16 *)(s0 + 4) = buf[0];
        *(u16 *)(s0 + 6) = buf[2];
        s0 += 0xA;
    }
}

u8 *func_800D44C0(u8 *a0) {
    u8 *r = a0;
    s32 t = func_8006ED08(a0);
    (void)t;
    *(u8 **)(r + 0xD34) = D_800D430C;
    *(s32 *)(r + 0xD44) = 0;
    return r;
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D44F8);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D46BC);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D48A0);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D4CD8);

s32 func_800D4DA4(s32 a0, s32 *a1) {
    return (a1[1] < 0x1201) ^ 1;
}

extern s32 func_8006F18C(u8 *);
extern void func_800720EC(u8 *);
extern void func_800238C4(u8 *, u8 *, u8 *, s32);
extern u8 *func_8006EF4C(u8 *);
extern u8 D_800D3D1C[];
extern u8 D_800D3D0C[];


void func_800D4DB8(u8 *a0)
{
  s32 state;
  /* The two compiler temporaries occupy retail stack offsets 0x10 and 0x20. */
  s32 scratch[8];
  if (func_8006F18C(a0) != 0)
  {
    func_800720EC(a0);
    return;
  }
  state = *((s32 *) (a0 + 0xD30));
  if (state < 3)
  {
    if (state > 0)
    {
      goto Ldefault_944;
    }
    if (state == 0)
    {
      goto Lcase0_944;
    }
    goto Ldefault_944;
  }
  else
  {
    if (state == 3)
    {
      goto Lcase3_944;
    }
    goto Ldefault_944;
  }
  Lcase0_944:
  {
    /* pinned: $16/$17 hold the two pointers live across func_800720EC
       (register-allocation tie-break; see docs/DIFFICULT_FUNCTIONS.md). */
    register u8 *p asm("$16");
    register u8 *tp asm("$17");
    s32 t;
    t = (*((s32 *) (a0 + 0xD78))) - 0x16;
    *((s32 *) (a0 + 0xD78)) = t;
    if (t < 0)
    {
      *((s32 *) (a0 + 0xD78)) = 0;
    }
    tp = (u8 *)scratch;
    p = a0 + 0x31C;
    scratch[0] = *((s32 *) (a0 + 0x31C));
    scratch[1] = *((s32 *) (a0 + 0x320));
    scratch[2] = *((s32 *) (a0 + 0x324));
    func_800720EC(a0);
    func_800238C4(p, p, (u8 *) tp, *((s32 *) (a0 + 0xD78)));
  }

  goto Ltail_944;
  Ldefault_944:
  func_800720EC(a0);

  goto Ltail_944;
  Lcase3_944:
  {
    s32 t = (*((s32 *) (a0 + 0xD78))) - 0x44;
    *((s32 *) (a0 + 0xD78)) = t;
    if (t < 0)
    {
      *((s32 *) (a0 + 0xD78)) = 0;
    }
    func_800238C4(a0 + 0x32C, D_800D3D1C, a0 + 0x32C, *((s32 *) (a0 + 0xD78)));
    func_800238C4(a0 + 0x31C, D_800D3D0C, a0 + 0x31C, *((s32 *) (a0 + 0xD78)));
  }

  Ltail_944:
  {
    s32 cnt = *((s32 *) (a0 + 0xD74));
    if (cnt > 0)
    {
      s32 a;
      /* pinned: retail keeps the second modulo result in $6. */
      register s32 b asm("$6");
      s32 d = cnt * 2;
      a = func_8006EFEC(a0) % d;
      b = func_8006EFEC(a0) % d;
      {
        s32 x = *((s32 *) (a0 + 0x32C));
        s32 y = *((s32 *) (a0 + 0x330));
        s32 nc;
        scratch[4] = a;
        scratch[5] = b;
        scratch[6] = 0;
        /* empty statement: prevents the 0xD74 load from being hoisted
           above the temporary stores (scheduling tie-break). */
        do { } while (0);
        nc = *((s32 *) (a0 + 0xD74));
        x += a;
        y += b;
        nc -= 1;
        *((s32 *) (a0 + 0x32C)) = x;
        *((s32 *) (a0 + 0x330)) = y;
        *((s32 *) (a0 + 0xD74)) = nc;
      }
    }
  }

  {
    u8 *r = func_8006EF4C(a0);
    /* pinned: retail loads/stores the first triple through $4/$5/$6. */
    register s32 x1 asm("$4");
    register s32 y1 asm("$5");
    register s32 z1 asm("$6");
    s32 x2;
    s32 y2;
    s32 z2;
    *((s32 *) (r + 0x50)) = 1;
    x1 = *((s32 *) (a0 + 0x32C));
    y1 = *((s32 *) (a0 + 0x330));
    z1 = *((s32 *) (a0 + 0x334));
    *((s32 *) (r + 0x10)) = x1;
    *((s32 *) (r + 0x14)) = y1;
    *((s32 *) (r + 0x18)) = z1;
    x2 = *((s32 *) (a0 + 0x31C));
    y2 = *((s32 *) (a0 + 0x320));
    z2 = *((s32 *) (a0 + 0x324));
    *((s32 *) (r + 0x0)) = x2;
    *((s32 *) (r + 0x4)) = y2;
    *((s32 *) (r + 0x8)) = z2;
  }
}


void func_800D4FB0(u8 *a0) {
    if (*(s32 *)(a0 + 0xD30) != 3) {
        *(s32 *)(a0 + 0xD30) = 3;
        *(s32 *)(a0 + 0xD78) = 0x1000;
    }
}

void func_800D4FD0(u8 *a0, u8 *a1) {
    s32 v = func_8002BDC8(*(s32 *)(a0 + 0xD50));
    if (v != 0) {
        func_800D7224((u8 *)v, a1);
    } else {
        *(s32 *)(a0 + 0xD50) = 0;
    }
}

void func_800D5020(u8 *a0, u8 *a1, u8 *a2, u8 *a3) {
    s32 v = func_8002BDC8(*(s32 *)(a0 + 0xD50));
    if (v != 0) {
        func_800D7278(v, a1, a2, a3);
    } else {
        *(s32 *)(a0 + 0xD50) = 0;
    }
}

void func_800D5090(u8 *a0) {
    s32 v = func_8002BDC8(*(s32 *)(a0 + 0xD50));
    if (v != 0) {
        *(s32 *)(v + 0x1C) = 1;
    } else {
        *(s32 *)(a0 + 0xD50) = 0;
    }
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D50D4);

void func_800D51FC(u8 *a0) {
    struct { MATRIX matrix; VECTOR vector; } buf;
    u8 *s3;
    u8 *s1;
    s32 i;

    func_80024A50(&buf.matrix, *(s32 *)(a0 + 0xD3C));
    s3 = (u8 *)&buf + 0x20;
    s1 = a0 + 0xD54;

    for (i = 0; i < 2; i++) {
        u8 *obj = func_800700B0(a0, i);
        func_80023B10((u8 *)&buf, s3, s1);
        buf.vector.vy = (s32)((u32)buf.vector.vy +
                                (u32)(s32)((s16 *)func_8007773C(obj))[1]);
        func_80077654(obj, s3);
        *(s32 *)(obj + 0x3A4) = 0;
        *(s32 *)(obj + 0x3A8) = 0;
        *(s32 *)(obj + 0x3AC) = 0;
        *(s32 *)(obj + 0x3B0) = 0;
        s1 += 0x10;
    }
}

u8 *func_800D52B8(u8 *a0) {
    u8 *r = a0;
    func_8002BC9C(a0, 0);
    *(u8 **)(r + 0x14) = D_800D42E4;
    *(s32 *)(r + 0x18) = 0;
    return r;
}

void func_800D52F4(u8 *a0) {
    *(s32 *)(a0 + 0x18) += 0x40;
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D5308);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D57B0);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D583C);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D599C);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D5A90);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D5C54);

void func_800D5D0C(u8 *a0, u8 *a1) {
    func_800D57B0(a0 + 0x18, a1);
    if (*(s32 *)(a0 + 0xAC) == 0) {
        func_800D5D54(a0);
    }
    *(s32 *)(a0 + 0xAC) = 1;
}

void func_800D5D54(u8 *a0) {
    u8 *s0 = func_8002BE14(0x3C);
    if (s0 != 0) {
        u8 *v0 = (u8 *)func_8002BD80(0x3C, s0);
        func_800C6588(v0, 3, a0 + 0x84, 0x30, 0x80, -0x18, 0x808080);
    }
    func_8002BF34(a0, s0);
    func_8001BE78((s32)(u32)D_8005F824, 0x4D, 0);
}

void func_800D5DE8(u8 *a0) {
    s32 v1 = *(s32 *)(a0 + 0xB8) + *(s32 *)(a0 + 0xBC);
    *(s32 *)(a0 + 0xB8) = v1;
    if (v1 >= 0x100) {
        *(s32 *)(a0 + 0xB8) = v1 - 0x100;
        *(s32 *)(a0 + 0xB4) = 1;
    } else {
        *(s32 *)(a0 + 0xB4) = 0;
    }
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D5E20);

void func_800D5EB4(u8 *a0) {
    s32 v = func_80031C20(*(s32 *)(a0 + 0x7C), 0xF);
    func_8001F9EC((u8 *)(*(s32 *)(a0 + 0x80) + 8), v + 8);
}

void func_800D5EF0(u8 *a0) {
    func_8001FACC((u8 *)(*(s32 *)(a0 + 0x80) + 8));
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D5F14);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D5FF4);

extern void func_800D6148(u8 *);
void func_800D60E0(u8 *a0) {
    s32 *p;
    s32 value;

    if (*(s32 *)(a0 + 0xA8) > 0) {
        return;
    }
    if (*(s32 *)(a0 + 0xB4) == 0) {
        func_800D6148(a0);
    }
    p = *(s32 **)(a0 + 0x80);
    value = *(s32 *)((u8 *)p + 0x50);
    *(s32 *)((u8 *)p + 0x50) = (value & -2) | (*(s32 *)(a0 + 0xB4) == 0);
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D6148);

u8 *func_800D6334(u8 *a0, u8 *a1, u8 *a2, s32 a3) {
    u8 *s0 = a0;
    u8 *s3 = a1;
    u8 *s2 = a2;
    s32 s1 = a3;
    func_8002BC9C(a0, 0);
    *(u8 **)(s0 + 0x14) = D_800D4254;
    *(u8 **)(s0 + 0x18) = s3;
    *(u8 **)(s0 + 0x1C) = (u8 *)func_80031C20((s32)s3, (s32)s2);
    *(u8 **)(s0 + 0x20) = s2;
    *(s32 *)(s0 + 0x24) = s1 & 1;
    *(s32 *)(s0 + 0x28) = 0;
    *(s32 *)(s0 + 0x2C) = 0x80;
    *(s32 *)(s0 + 0x30) = 0x1000;
    *(s32 *)(s0 + 0x34) = 0;
    func_8003EC6C(s0 + 0x38, D_800D3F4C, s2);
    func_8003EC6C(s0 + 0x58, D_800D3F5C, s2);
    return s0;
}

void func_800D63F0(u8 *a0, u32 a1) {
    switch (*(s32 *)(a0 + 0x28)) {
    case 0:
        if (func_800D6588(a0, a1)) {
            *(s32 *)(a0 + 0x34) += 1;
            if (*(s32 *)(a0 + 0x34) >= 0x3D) {
                func_80031D0C(*(u8 **)(a0 + 0x18), *(s32 *)(a0 + 0x20));
                *(s32 *)(a0 + 0x2C) = 0x400;
                func_800D4FD0((u8 *)a1, a0 + 0x38);
                func_8001BE78((s32)(u32)D_8005F824, 0x60, 0);
                *(s32 *)(a0 + 0x28) += 1;
            }
        } else {
            *(s32 *)(a0 + 0x34) -= 1;
            if (*(s32 *)(a0 + 0x34) < 0) {
                *(s32 *)(a0 + 0x34) = 0;
            }
        }
        break;
    case 1:
        *(s32 *)(a0 + 0x30) += (0x2000 - *(s32 *)(a0 + 0x30)) >> 2;
        *(s32 *)(a0 + 0x2C) += (-*(s32 *)(a0 + 0x2C)) >> 2;
        *(s32 *)(a0 + 0x34) -= 1;
        if (*(s32 *)(a0 + 0x34) <= 0) {
            *(s32 *)(a0 + 0x30) = 0x1000;
            *(s32 *)(a0 + 0x2C) = 0;
            func_800D4FD0((u8 *)a1, a0 + 0x58);
            func_8001BE78((s32)(u32)D_8005F824, 0x5F, 0);
            *(s32 *)(a0 + 0x28) += 1;
        }
        break;
    case 2:
        *(s32 *)(a0 + 0x2C) += 4;
        if (*(s32 *)(a0 + 0x2C) >= 0x81) {
            func_80031DB4(*(u32 *)(a0 + 0x18), *(u32 *)(a0 + 0x20));
            *(s32 *)(a0 + 0x2C) = 0x80;
            *(s32 *)(a0 + 0x28) = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D6588);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D6694);

u8 *func_800D6AFC(u8 *a0, u32 a1, u32 *a2) {
    u32 x;
    u32 y;
    u32 z;
    func_8002BC9C(a0, 0);
    *(u32 *)(a0 + 0x14) = (u32)D_800D422C;
    *(u32 *)(a0 + 0x18) = a1;
    x = a2[0];
    y = a2[1];
    z = a2[2];
    *(u32 *)(a0 + 0x2C) = 0;
    *(u32 *)(a0 + 0x30) = 0;
    *(u32 *)(a0 + 0x1C) = x;
    *(u32 *)(a0 + 0x20) = y;
    *(u32 *)(a0 + 0x24) = z;
    return a0;
}

void func_800D6B70(u8 *a0, u32 a1) {
    *(u32 *)(a0 + 0x14) = (u32)D_800D422C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800D6BC4(u8 *a0) {
    u8 *t;
    s32 r;
    t = *(u8 **)(a0 + 0x18);
    *(s32 *)(t + 8) = 0;
    r = func_800254CC(t + 0x2C, *(s32 *)(a0 + 0x2C));
    *(s32 *)(a0 + 0x2C) += 0xC0;
    *(s32 *)(a0 + 0x30) += 1;
    (void)r;
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D6C14);

void func_800D6C98(u8 *a0) {
    s32 a = *(s32 *)(a0 + 0x28);
    s32 b = *(s32 *)(a0 + 0x2C);
    *(s32 *)(a0 + 0x28) = (a + 1) & 3;
    *(s32 *)(a0 + 0x2C) = b + 0x10;
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D6CB8);

u8 *func_800D6E6C(u8 *a0, u8 *a1) {
    func_8002BC9C(a0, 0);
    *(u8 **)(a0 + 0x14) = D_800D41DC;
    *(u8 **)(a0 + 0x18) = a1;
    *(s32 *)(a0 + 0x1C) = 0;
    *(s32 *)(a0 + 0x20) = 0;
    func_800D70DC(a0);
    func_800D7100(a0);
    return a0;
}

void func_800D6ECC(u8 *a0) {
    s32 i;
    s32 idx;
    s32 off;
    u8 *g;

    for (i = 1; i >= 0; i--) {
        func_800D6F7C(a0);
    }
    idx = (*(s32 *)(a0 + 0x134) + *(s32 *)(a0 + 0x130)) % 12;
    off = *(s32 *)(a0 + 0x12C) + idx * 16;
    g = a0 + 0x138;
    *(u8 *)(g + off) = (*(s32 *)(a0 + 0x20) & 4) ? 0x20 : 0x5F;
    *(s32 *)(a0 + 0x20) = *(s32 *)(a0 + 0x20) + 1;
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D6F7C);

void func_800D70DC(u8 *a0) {
    s32 i = 0xFF;
    u8 *p = a0 + 0x12B;
    for (; i >= 0; i--) {
        *p-- = 0;
    }
    *(s32 *)(a0 + 0x24) = 0;
    *(s32 *)(a0 + 0x28) = 0;
}

void func_800D7100(u8 *a0) {
    /* Pins preserve the retail loop index, next index, count, pointer, and base. */
    register s32 i asm("$5");
    register s32 next asm("$6");
    register s32 j asm("$3");
    register u8 *base asm("$7");
    register u32 p asm("$2");

    i = 0;
    base = a0 + 0x138;
    do {
        next = i + 1;
        j = 15;
        p = i << 4;
        p += (u32)base;
        p += 0xF;
        do {
            *(u8 *)p = 0;
            p--;
            j--;
        } while (j >= 0);
        i = next;
    } while (i < 12);
    *(s32 *)(a0 + 0x12C) = 0;
    *(s32 *)(a0 + 0x130) = 0;
    *(s32 *)(a0 + 0x134) = 0;
}

void func_800D714C(u8 *a0, s32 a1) {
    s32 i = 0xF;
    u8 *p = a0 + (a1 << 4) + 0x147;
    for (; i >= 0; i--) {
        *p-- = 0;
    }
}

void func_800D7174(u8 *a0, s32 a1, s32 a2) {
    s32 idx;
    s32 off;
    u8 *new_var2;
    u8 *g;
    s32 *p;
    s32 *new_var;

    idx = (*(s32 *)(a0 + 0x134) + *(s32 *)(a0 + 0x130)) % 12;
    off = *(s32 *)(a0 + 0x12C) + idx * 16;
    g = a0 + 0x138;
    *(u8 *)(g + off) = 0;
    p = (s32 *)(a0 + 0x12C);
    *p = a1;
    *(s32 *)(a0 + 0x130) = a2;
    a1 = (a1 < 0) ? 0 : ((a1 >= 16) ? 15 : a1);
    *p = a1;
    new_var = (s32 *)(a0 + 0x130);
    new_var2 = a0 + 0x130;
    *(s32 *)new_var2 = (*(s32 *)new_var < 0) ? 0
                       : ((*(s32 *)new_var2 >= 12) ? 11 : *(s32 *)new_var2);
}

void func_800D7224(u8 *a0, u8 *a1) {
    u8 *p;
    s32 i;

    if (*(s32 *)(a0 + 0x1C) == 0) {
        p = a0 + 0x2C;
        i = *(s32 *)(a0 + 0x28);
        do {
            p[i] = *a1;
            i++;
            if (i >= 0x100) {
                i = 0;
            }
        } while (*a1++ != 0);
        *(s32 *)(a0 + 0x28) = i;
    }
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D7278);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D7314);

u8 *func_800D76D8(u8 *arg0, u32 arg1, u32 arg2) {
    func_8002BC9C(arg0, 0);
    *(u32 *)(arg0 + 0x14) = (u32)D_800D41B4;
    *(u32 *)(arg0 + 0x18) = arg1;
    *(u32 *)(arg0 + 0x1C) = arg2 & 3;
    *(u32 *)(arg0 + 0x20) = 0x990;
    *(u32 *)(arg0 + 0x24) = 0x990;
    *(u32 *)(arg0 + 0x28) = 0;
    *(u32 *)(arg0 + 0x2C) = 0;
    *(u32 *)(arg0 + 0x30) = (arg2 & 2) ? 0x7C : 0x5C;
    return arg0;
}

void func_800D775C(u8 *arg0) {
    *(s32 *)(arg0 + 0x20) += (0x264 - *(s32 *)(arg0 + 0x20)) >> 2;
    *(s32 *)(arg0 + 0x24) += (0x264 - *(s32 *)(arg0 + 0x24)) >> 2;
    switch (*(s32 *)(arg0 + 0x2C)) {
    case 0: {
        s32 t = *(s32 *)(arg0 + 0x28) + 8;
        *(s32 *)(arg0 + 0x28) = t;
        if (t >= 0x80) {
            *(s32 *)(arg0 + 0x2C) = 1;
        }
    } break;
    case 1: {
        s32 t = *(s32 *)(arg0 + 0x30) - 1;
        *(s32 *)(arg0 + 0x30) = t;
        if (t < 0) {
            *(s32 *)(arg0 + 0x2C) = 2;
        }
    } break;
    case 2: {
        s32 t;
        *(s32 *)(arg0 + 0x20) = *(s32 *)(arg0 + 0x20) + 0x40;
        *(s32 *)(arg0 + 0x24) = *(s32 *)(arg0 + 0x24) + 0x20;
        t = *(s32 *)(arg0 + 0x28) - 8;
        *(s32 *)(arg0 + 0x28) = t;
        if (t <= 0) {
            if (arg0 != 0) {
                u8 *v = *(u8 **)(arg0 + 0x14);
                ((void (*)(u8 *, s32))(*(s32 *)(v + 0x1C)))(arg0 + *(s16 *)(v + 0x18), 3);
            }
        }
    } break;
    }
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D7864);

u8 *func_800D7AF0(u8 *a0, s32 a1) {
    s32 i;
    u8 *p;
    u8 *end;
    u8 *q;
    s32 v;

    func_8002BC9C(a0, 0);
    end = a0 + 0x20;
    i = 8;
    p = a0 + 0x40;
    *(u8 **)(a0 + 0x14) = D_800D418C;
    *(s32 *)(a0 + 0x18) = a1;
    *(s32 *)(a0 + 0x1C) = 0x1000;
    do {
        *(s32 *)p = i;
        i--;
        p -= 4;
    } while (i >= 0);
    v = -1;
    q = end + 0x24;
    i = 0x16;
    do {
        *(s32 *)q = v;
        i--;
        q += 4;
    } while (i >= 0);
    return a0;
}

void func_800D7B78(u8 *a0) {
    s32 v = *(s32 *)(a0 + 0x1C) - 0x10;
    *(s32 *)(a0 + 0x1C) = v;
    if (v < -0x1200) {
        *(s32 *)(a0 + 0x1C) = 0x1000;
    }
}

void func_800D7BA0(u8 *a0, u8 *a1) {
    u8 *t0 = a0;
    u8 *t1 = a1;
    s32 s0;

    s0 = 0;
    do {
        func_800D7E9C(t0, t1, s0);
        func_800D7C08(t0, t1, s0);
        s0 += 0x400;
    } while (s0 < 0x1000);
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D7C08);

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D7E9C);

s32 func_800D8228(u8 *a0, u8 *a1, u8 *a2) {
    u32 raw;
    s32 shifted;
    s32 b;
    s32 a3;

    raw = *(u16 *)(a0 + 8);
    shifted = (s32)(raw << 16);
    b = shifted >> 16;
    if (b <= 0) {
        return -1;
    }
    a3 = *(s16 *)a0;
    if (a3 >= 0x1000) {
        return -1;
    }
    if (a3 < 0) {
        *(s16 *)(a0 + 0x10) = 0;
        *(s16 *)a0 = 0;
        a1[0] = a2[0] - (shifted >> 20);
    } else if (b >= 0x1001) {
        *(s16 *)(a0 + 0x18) = 0x1000;
        *(s16 *)(a0 + 8) = 0x1000;
        a2[0] = a1[0] + ((0x1000 - a3) >> 4);
    }
    return 0;
}

u8 *func_800D82B0(u8 *a0, u32 a1, u32 a2) {
    u8 *s0;
    u32 s1;
    u32 s2;

    s0 = a0;
    s1 = a1;
    s2 = a2;
    func_8002BC9C(s0, 0);
    *(u32 *)(s0 + 0x18) = s1;
    *(u32 *)(s0 + 0x1C) = s2;
    *(u32 *)(s0 + 0x14) = (u32)D_800D4164;
    return s0;
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D8308);

void func_800D8500(void) {
    func_8006F23C();
}

void func_800D8520(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800D8568(u8 *a0, s32 a1) {
    *(u8 **)a0 = D_80065154;
    if (a1 & 1) {
        func_8002B3D0(a0);
    }
}

u8 *func_800D859C(u8 *a0, s32 a1, u8 *a2, s32 a3) {
    u8 *v0 = a0;
    s32 v1;
    s32 v2;
    s32 v3;
    *(u8 **)v0 = D_800D42C4;
    *(s32 *)(v0 + 4) = a1;
    *(s32 *)(v0 + 8) = a3;
    v1 = *(s32 *)(a2 + 0);
    v2 = *(s32 *)(a2 + 4);
    v3 = *(s32 *)(a2 + 8);
    *(s32 *)(v0 + 0xC) = v1;
    *(s32 *)(v0 + 0x10) = v2;
    *(s32 *)(v0 + 0x14) = v3;
    return v0;
}

void func_800D85D0(u8 *a0, u8 *a1) {
    u32 v0 = *(u32 *)(a1 + 0);
    u32 v1 = *(u32 *)(a1 + 4);
    u32 v2 = *(u32 *)(a1 + 8);
    *(u32 *)(a0 + 0xC) = v0;
    *(u32 *)(a0 + 0x10) = v1;
    *(u32 *)(a0 + 0x14) = v2;
}

void func_800D85EC(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800D8634(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800D867C(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800D86C4(u8 *a0) {
    *(s32 *)(a0 + 0x1C) = 1;
}

void func_800D86D0(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800D8718(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

void func_800D8760(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st02/nonmatchings/944", func_800D87A8);
}
