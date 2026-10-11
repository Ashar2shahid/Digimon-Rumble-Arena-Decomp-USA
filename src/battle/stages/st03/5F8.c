#include "game_sprite_cleanup.h"
#include "mesh_scene_visibility.h"
#include "game_rotation.h"
#include "game_placement_api.h"
#include "game_audio_api.h"
#include "game_base_api.h"
#include "common.h"
#include "game_random.h"
#include "game_positions.h"

extern u8 D_80065154[];
extern u8 D_800D3F04[];
extern u8 D_800D3FD4[];
extern u8 D_800D3DC4[];
extern u8 D_800D3D9C[];
extern u8 D_800D3E3C[];
extern u8 D_800D3E64[];
extern u8 D_800D3EDC[];
extern u8 D_800D3F2C[];
extern u8 D_800D3F54[];
extern u8 D_800D3FA4[];
extern u8 D_800D3F74[];
extern u8 D_800D3FF4[];
extern u8 D_800D401C[];
extern u8 D_80065174[];
extern u8 D_8005F824[];
extern u8 *D_800D3A5C;
extern u8 D_800D3EB4[];
extern u8 D_800D3CAC[];
extern u8 D_800D3E8C[];
extern u8 D_80010814[];
typedef struct { s32 a; s32 b; s32 c; } Ent;
extern Ent D_800D3C44[];
typedef struct { s32 x; s32 y; s32 z; s32 w; } Vec;
typedef struct { s32 x; s32 y; s32 z; } V3;

u8 *func_8002BD74(u8 *);

u8 *func_8007773C(u8 *);
u8 *func_8002BDC8(u8 *);
void func_80071F64(void);
s32 func_8006F12C(u8 *);
s32 func_8006F178(u8 *);
void func_8006F06C(u8 *, void *);
void func_8003E00C(void *, s32, s32);
void *func_8002BE14(s32);
void func_800D7E38(void *, u8 *, s32 *);
s32 func_8006F18C(u8 *);
u8 *func_80031C20(u8 *, u8 *);
void func_800245B8(u8 *, s32, s32, s32);
s32 func_80073010(u8 *, u8 *);
void func_800D68B4(u8 *, u8 *);
void func_800D5550(u8 *, u8 *);

void func_80031DB4(u8 *, u8 *);
s32 func_800D6594(u8 *);
s32 func_800D6720(u8 *, s32);
void func_800D6A18(u8 *, u8 *);
void func_800D6830(u8 *, s32);
void func_800D6994(u8 *);
u8 *func_80031C48(u8 *, u8 *);
u8 *func_800700B0(u8 *, s32);
u8 *func_800783AC(u8 *, u8 *);
void func_8006F00C();
void func_8006F02C();
void func_8006F04C();
void func_800D6B54(u8 *);
void func_80079E90(s32 *, s32 *, s32 *, u32);
void func_800240C8(u8 *, s32);
u8 *func_80032EE8(s32);
void func_8005844C(s32);
s32 func_800237A0(u8 *);
void func_80075F88(u8 *, u8 *, s32, u8 *);
void func_800D739C(u8 *, s32, u8 *, u8 *, s32);
void func_800238C4(Vec *, Vec *, Vec *, s32);

void func_8001FC58(s32, s32);
void func_8006F23C(s32, s32);
void func_8002BCEC(u8 *, s32);
void func_8002BDA8(u8 *);
void func_8002B3D0();
void func_800727AC();
void func_8001FE8C();
void func_8001FD40();

void func_800D75A8();
void func_800D7738();
void func_800D4920();

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D40F8);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D41FC);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D43F0);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D4708);

void func_800D48F4(u8 *arg0) {
    func_800727AC(arg0);
    func_800D4920(arg0);
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D4920);

void func_800D4B84(u8 *arg0, s32 arg1) {
    func_8001FE8C(arg0 + 0xD78);
    func_8001FD40(arg0 + 0xD78);
}

u8 *func_800D4BB4(u8 *arg0) {
    s32 i;
    u8 *p;

    func_8002BC9C(arg0, 0);
    *(void **)(arg0 + 0x14) = D_800D401C;
    i = 0x13;
    p = arg0 + 0x64;
    for (; i >= 0; i--) {
        *(int *)p = 0;
        p -= 4;
    }
    *(int *)(arg0 + 0x68) = 0;
    return arg0;
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D4C08);

/* Register pins: `base`->$s2 and `v`->$s3 match retail's loop-carried base
 * and per-iteration argument; the inner `d`->$a2 pin fixes the copy dest. */
void func_800D4F8C(u8 *a0, u8 *a1)
{
  Ent *e;
  Ent *end;
  register u8 *base asm("$18"); /* PIN $s2 */
  register s32 v asm("$19");    /* PIN $s3 */
  base = a0 + 0x18;
  e = D_800D3C44;
  end = D_800D3C44 + 6;
  v = *((s32 *) (a1 + 0x10));
  do
  {
    u8 *r = func_80032EE8(e->a);
    register s32 *d asm("$6") = (s32 *) (r + 0x10); /* PIN $a2 */
    s32 *s = (s32 *) ((e->b * 2) + (s32) base);
    s32 *se = s + e->c;
    do
    {
      if (r)
      {
        *(d++) = *(s++);
      }
      else
      {
        *(d++) = *(s++);
      }
    }
    while (s != se);
    func_8005844C(v);
    e++;
  }
  while (e != end);
}

u8 *func_800D5030(u8 *arg0, u8 *arg1) {
    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x18) = arg1;
    *(u8 **)(arg0 + 0x14) = D_800D3FF4;
    return arg0;
}

void func_800D5078(u8 *arg0, s32 arg1) {
    if (func_8006F18C(*(u8 **)(arg0 + 0x18)) == 0) {
        func_800D4B84(*(u8 **)(arg0 + 0x18), arg1);
    }
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D50C0);

u8 *func_800D51C8(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    s32 x;
    s32 y;
    s32 z;

    func_8002BC9C(arg0, 0x40000);
    *(u8 **)(arg0 + 0x14) = D_800D3FA4;
    *(u8 **)(arg0 + 0x18) = arg1;
    *(u8 **)(arg0 + 0x3C) = arg2;
    x = *(s32 *)(arg3 + 0);
    y = *(s32 *)(arg3 + 4);
    z = *(s32 *)(arg3 + 8);
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x38) = 0;
    *(s32 *)(arg0 + 0x1C) = x;
    *(s32 *)(arg0 + 0x20) = y;
    *(s32 *)(arg0 + 0x24) = z;
    return arg0;
}

void func_800D5254(u8 *arg0) {
    u8 *vt = *(u8 **)(arg0 + 0x14);
    u8 *r;
    s32 *p;
    s32 a;
    s32 b;
    s32 c;
    void (*f)(u8 *) = *(void (**)(u8 *))(vt + 0x24);

    f(arg0 + *(s16 *)(vt + 0x20));
    r = func_80031C20(*(u8 **)(arg0 + 0x18), *(u8 **)(arg0 + 0x3C));
    p = (s32 *)(arg0 + 0x1C);
    *(s32 *)(r + 8) = 0;
    a = p[0];
    b = p[1];
    c = p[2];
    *(s32 *)(r + 0x2C) = 0x1000;
    *(s32 *)(r + 0x30) = 0;
    *(s32 *)(r + 0x34) = 0x1000;
    *(s32 *)(r + 0x38) = 0;
    *(s32 *)(r + 0x3C) = 0x1000;
    *(s32 *)(r + 0x40) = a;
    *(s32 *)(r + 0x44) = b;
    *(s32 *)(r + 0x48) = c;
    func_800245B8(r + 0x2C, *(s32 *)(arg0 + 0x2C), *(s32 *)(arg0 + 0x30), *(s32 *)(arg0 + 0x34));
}

void func_800D52EC(u8 *arg0, u8 *arg1) {
    s32 v;

    if (*(s32 *)(arg1 + 0xD50) == 0) {
        *(s32 *)(arg0 + 0x30) += 8;
        if (*(s32 *)(arg0 + 0x30) >= 0) {
            *(s32 *)(arg0 + 0x30) = 0;
        }
    } else {
        v = *(s32 *)(arg0 + 0x30) - 8;
        *(s32 *)(arg0 + 0x30) = v;
        if (v < -0xEF) {
            *(s32 *)(arg0 + 0x30) = -0xF0;
        }
    }
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D5340);

void func_800D542C(u8 *arg0, u8 *arg1) {
    s32 f = *(s32 *)(arg1 + 0xD50);
    s32 v;
    s32 e;
    u8 *head;

    if (f == 0) {
        *(s32 *)(arg0 + 0x30) -= 8;
        if (*(s32 *)(arg0 + 0x30) <= 0) {
            *(s32 *)(arg0 + 0x30) = 0;
        }
    } else {
        *(s32 *)(arg0 + 0x30) += 8;
        if (*(s32 *)(arg0 + 0x30) >= 0xF0) {
            *(s32 *)(arg0 + 0x30) = 0xF0;
        }
    }
    v = *(s32 *)(arg0 + 0x30);
    if ((u32)(v - 9) < 0x77) {
        *(s32 *)(arg0 + 0xA4) = v;
        if (f == 0) {
            func_800D5550(arg0, arg1);
        }
    } else {
        head = arg0 + 0x60;
        e = 0;
        if (*(u8 **)(arg0 + 0x60) == head) {
            e = (head == *(u8 **)(arg0 + 0x64));
        }
        if (e == 0) {
            *(u8 **)(*(u8 **)(arg0 + 0x60) + 4) = *(u8 **)(arg0 + 0x64);
            *(u8 **)(*(u8 **)(head + 4)) = *(u8 **)(arg0 + 0x60);
            *(u8 **)(arg0 + 0x60) = head;
            *(u8 **)(arg0 + 0x64) = head;
            func_8001BE78((s32)(u32)D_8005F824, 0x62, 0);
        }
    }
    if (*(s32 *)(arg0 + 0x30) == 0) {
        func_80031D0C(*(u8 **)(arg0 + 0x18), *(s32 *)(arg0 + 0x3C));
    } else {
        func_80031DB4(*(u8 **)(arg0 + 0x18), *(u8 **)(arg0 + 0x3C));
    }
}

/* Register pin: `t` fixed to $a0 so cc1 keeps the unlink temp there
 * (retail reuses the a0 argument register for both list-fixup temps). */
void func_800D5550(u8 *a0, u8 *a1)
{
    u8 *x = func_80031C48(*(u8 **)(a0 + 0x18), *(u8 **)(a0 + 0x3C));
    u8 *r0 = func_800783AC(func_800700B0(a1, 0), x);
    u8 *r1 = func_800783AC(func_800700B0(a1, 1), x);
    register u8 *t asm("$4"); /* PIN $a0 */
    u8 *head = a0 + 0x60;

    t = *(u8 **)(a0 + 0x60);
    *(u8 **)(t + 4) = *(u8 **)(a0 + 0x64);
    t = *(u8 **)(head + 4);
    *(u8 **)(t) = *(u8 **)(a0 + 0x60);
    *(u8 **)(a0 + 0x60) = head;
    *(u8 **)(a0 + 0x64) = head;
    if (r0 != 0) {
        if (r1 != 0) goto LD;
        func_8006F00C(a1);
        goto Ld5550done;
    }
    if (r1 != 0) {
        func_8006F02C(a1);
        goto Ld5550done;
    }
    goto Ld5550done;
LD:
    func_8006F04C(a1);
Ld5550done:
    ;
}

u8 *func_800D5638(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 t0;
    s32 t1;
    s32 t2;

    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_800D3F2C;
    *(u8 **)(arg0 + 0x18) = arg1;
    t0 = *(s32 *)(arg2 + 0x0);
    t1 = *(s32 *)(arg2 + 0x4);
    t2 = *(s32 *)(arg2 + 0x8);
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x1C) = t0;
    *(s32 *)(arg0 + 0x20) = t1;
    *(s32 *)(arg0 + 0x24) = t2;
    return arg0;
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D56AC);

u8 *func_800D5744(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 t0, t1, t2;
    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_800D3F04;
    *(u8 **)(arg0 + 0x18) = arg1;
    *(s16 *)(arg0 + 0x1C) = 0x2C0;
    *(u8 *)(arg0 + 0x1E) = 0x40;
    *(u8 *)(arg0 + 0x1F) = 0x80;
    t0 = *(s32 *)(arg2 + 0x0);
    t1 = *(s32 *)(arg2 + 0x4);
    t2 = *(s32 *)(arg2 + 0x8);
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x20) = t0;
    *(s32 *)(arg0 + 0x24) = t1;
    *(s32 *)(arg0 + 0x28) = t2;
    return arg0;
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D57D0);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D5874);

u8 *func_800D5AE4(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 t0;
    s32 t1;
    s32 t2;

    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_800D3EDC;
    *(u8 **)(arg0 + 0x18) = arg1;
    t0 = *(s32 *)(arg2 + 0x0);
    t1 = *(s32 *)(arg2 + 0x4);
    t2 = *(s32 *)(arg2 + 0x8);
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x34) = 0x10;
    *(s32 *)(arg0 + 0x1C) = t0;
    *(s32 *)(arg0 + 0x20) = t1;
    *(s32 *)(arg0 + 0x24) = t2;
    return arg0;
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D5B60);

/* Register pin: `dx` fixed to $a2 so cc1 keeps the first vector component
 * there (retail uses $a2 for the x delta). */
u8 *func_800D5CA8(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *a4)
{
    u8 *p;
    s32 v0;
    s32 v1;
    s32 x;
    s32 y;
    s32 z;
    register s32 dx asm("$6"); /* PIN $a2 */
    s32 dy;
    s32 dz;

    func_8002BC9C(a0, 0);
    *(u8 **)(a0 + 0x14) = D_800D3EB4;
    *(u8 **)(a0 + 0x18) = a1;
    *(s32 *)(a0 + 0x1C) = a2;
    *(s32 *)(a0 + 0x20) = a3;
    x = *(s32 *)(a4 + 0x0);
    y = *(s32 *)(a4 + 0x4);
    z = *(s32 *)(a4 + 0x8);
    *(s32 *)(a0 + 0x24) = x;
    *(s32 *)(a0 + 0x28) = y;
    *(s32 *)(a0 + 0x2C) = z;
    switch (a2) {
    case 0:
    default: *(s32 *)(a0 + 0x44) = 0; *(s32 *)(a0 + 0x58) = 0; break;
    case 5: *(s32 *)(a0 + 0x44) = 2; *(s32 *)(a0 + 0x58) = 1; break;
    case 6: *(s32 *)(a0 + 0x44) = 4; *(s32 *)(a0 + 0x58) = 2; break;
    }
    p = D_800D3CAC + (*(s32 *)(a0 + 0x44) << 4);
    dx = *(s32 *)(p + 0x0);
    dy = *(s32 *)(p + 0x4);
    dz = *(s32 *)(p + 0x8);
    *(s32 *)(a0 + 0x48) = 0;
    *(s32 *)(a0 + 0x4C) = 0;
    *(s32 *)(a0 + 0x50) = 0;
    *(s32 *)(a0 + 0x54) = 0;
    *(s32 *)(a0 + 0x34) = dx;
    *(s32 *)(a0 + 0x38) = dy;
    *(s32 *)(a0 + 0x3C) = dz;
    func_80031D0C(a1, *(s32 *)(a0 + 0x1C));
    return a0;
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D5DBC);

/* Register pins: `s3`->$s3 (this pointer) and `s2`->$s2 (loop index) match
 * retail's callee-save assignment. */
void func_800D6128(u8 *a0)
{
    u8 *s5 = D_800D3A5C;
    register u8 *s3 asm("$19") = a0; /* PIN $s3 */
    register s32 s2 asm("$18") = 0;  /* PIN $s2 */
    s32 buf[4];
    u8 *s4 = (u8 *)buf;
    u8 *s0;
    s32 s1;

    do {
        s0 = func_800700B0(s5, s2);
        s1 = *(short *)(func_8007773C(s0) + 2) + 0xC0;
        func_8007A8D0(s0, (u8 *)buf);
        {
            s32 t0 = buf[0];
            s32 t1 = buf[1];
            s32 t2 = buf[2];
            t0 -= *(s32 *)(s3 + 0x24);
            t1 -= *(s32 *)(s3 + 0x28);
            t2 -= *(s32 *)(s3 + 0x2C);
            buf[0] = t0;
            buf[1] = t1;
            buf[2] = t2;
        }
        if (func_800237A0(s4) < s1) {
            goto done;
        }
        s2 += 1;
    } while (s2 < 2);
    func_80031DB4(*(s32 *)(s3 + 0x18), *(s32 *)(s3 + 0x1C));
done:
}

void func_800D620C(u8 *arg0) {
    func_80031D0C(*(u8 **)(arg0 + 0x18), *(s32 *)(arg0 + 0x1C));
}

/* No pins: the near-miss seed's shapes were already byte-exact. */
u8 *func_800D6238(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *a4)
{
    u8 *s0 = a0;
    u8 *s4 = a1;
    u8 *s3 = a2;
    u8 *s2 = a3;
    u8 *s1 = a4;
    s32 x;
    s32 y;
    s32 t0;
    s32 t1;
    s32 t2;

    func_8002BC9C(s0, 0x40000);
    *(u8 **)(s0 + 0x14) = D_800D3E8C;
    *(s32 *)(s0 + 0x18) = (s32)D_800D3FD4;
    *(s32 *)(s0 + 0x1C) = (s32)0x80001000;
    *(s32 *)(s0 + 0x20) = 6;
    *(s32 *)(s0 + 0x24) = 0;
    t0 = *(s32 *)(D_80010814 + 0);
    t1 = *(s32 *)(D_80010814 + 4);
    t2 = *(s32 *)(D_80010814 + 8);
    *(s32 *)(s0 + 0x28) = t0;
    *(s32 *)(s0 + 0x2C) = t1;
    *(s32 *)(s0 + 0x30) = t2;
    func_80075F88(s0 + 0x38, s1, 0x70, s0 + 0x18);
    *(s32 *)(s0 + 0x4C) = (s32)s0;
    *(s32 *)(s0 + 0x80) = (s32)s2;
    *(s32 *)(s0 + 0x84) = (s32)s4;
    *(s32 *)(s0 + 0x88) = (s32)s3;
    x = *(s32 *)(s1 + 0);
    y = *(s32 *)(s1 + 4);
    *(s32 *)(s0 + 0x94) = 0;
    *(s32 *)(s0 + 0xA4) = 0;
    *(s32 *)(s0 + 0xAC) = 0;
    *(s32 *)(s0 + 0xB0) = 0;
    *(s32 *)(s0 + 0xB4) = 0;
    *(s32 *)(s0 + 0xB8) = 0;
    *(s32 *)(s0 + 0xBC) = 0;
    *(s32 *)(s0 + 0xC0) = 0;
    *(s32 *)(s0 + 0xC4) = 0;
    *(s32 *)(s0 + 0x8C) = x << 8;
    *(s32 *)(s0 + 0x90) = y << 8;
    *(s32 *)(s0 + 0x9C) = x << 8;
    *(s32 *)(s0 + 0xA0) = y << 8;
    *(s32 *)(s0 + 0xC8) = (s32)func_80037010(&D_8005EE48);
    *(s32 *)(s0 + 0xCC) = 0;
    return s0;
}

/* Register pin: `v1` fixed to $v1 so cc1 keeps the 0x80 struct pointer there
 * (retail reuses $v1). */
void func_800D6360(s32 a0, s32 a1)
{
    s32 s1 = a0;
    s32 s0 = a1;
    register s32 v1 asm("$3"); /* PIN $v1 */
    s32 p;
    s32 a2;
    s32 a0v;
    s32 t0;
    s32 t1;

    *(s32 *)(s1 + 0x14) = (s32)D_800D3E8C;
    v1 = *(s32 *)(s1 + 0x80);
    *(s32 *)(v1 + 8) = 0;
    t0 = *(s32 *)(s1 + 0x9C);
    t1 = *(s32 *)(s1 + 0xA0);
    *(s32 *)(v1 + 0x2C) = 0x1000;
    *(s32 *)(v1 + 0x34) = 0x1000;
    *(s32 *)(v1 + 0x3C) = 0x1000;
    *(s32 *)(v1 + 0x30) = 0;
    *(s32 *)(v1 + 0x38) = 0;
    *(s32 *)(v1 + 0x48) = 0;
    *(s32 *)(v1 + 0x40) = t0 >> 8;
    *(s32 *)(v1 + 0x44) = t1 >> 8;
    p = s1 + 0x38;
    a2 = *(s32 *)(s1 + 0x38);
    a0v = *(s32 *)(s1 + 0x3C);
    *(s32 *)(s1 + 0x68) = (s32)D_80065174;
    *(s32 *)(a2 + 4) = a0v;
    a2 = *(s32 *)(p + 4);
    *(s32 *)(a2 + 0) = *(s32 *)(s1 + 0x38);
    *(s32 *)(s1 + 0x38) = p;
    *(s32 *)(s1 + 0x3C) = p;
    *(s32 *)(s1 + 0x18) = (s32)D_80065154;
    func_8002BCEC(s1, 0);
    if (s0 & 1) {
        func_8002BDA8(s1);
    }
}

/* Register pin: $s1 fixed so cc1 keeps the a1 copy there (retail s1=a1),
 * and the 0x90+0x100 sum split into a distinct local `t` so cc1 materialises
 * it in $v0 before the 0xA0 load (retail order). */
void func_800D6430(u8 *a0, u8 *a1)
{
    u8 *s0 = a0;
    register u8 *s1 asm("$17") = a1; /* PIN $s1 */
    s32 s2 = func_800D6594(s0);
    s32 p;
    s32 v;

    switch (*(s32 *)(s0 + 0xCC)) {
    case 0:
        *(s32 *)(s0 + 0xBC) = 0;
        { s32 t = *(s32 *)(s0 + 0x90) + 0x100; func_800D6720(s0, (*(s32 *)(s0 + 0xA0) - t) >> 3); }
        if (*(s32 *)(s0 + 0xC0) >= 9) {
            *(s32 *)(s0 + 0xBC) = 0;
            *(s32 *)(s0 + 0xCC) += 1;
        }
        break;
    case 1:
        func_800D6A18(s0, s1);
        if (func_800D6720(s0, 0x71C) != 0) {
            p = (s32)(s0 + 0x38);
            *(s32 *)(*(s32 *)(s0 + 0x38) + 4) = *(s32 *)(s0 + 0x3C);
            *(s32 *)(*(s32 *)(p + 4)) = *(s32 *)(s0 + 0x38);
            *(s32 *)(s0 + 0x38) = p;
            *(s32 *)(s0 + 0x3C) = p;
            *(s32 *)(s0 + 0xB8) = 0;
            *(s32 *)(s0 + 0xB4) = 0;
            *(s32 *)(s0 + 0xC4) = 0x1E;
            *(s32 *)(s0 + 0xCC) += 1;
        }
        break;
    case 2:
        func_800D6830(s0, (s32)s1);
        v = *(s32 *)(s0 + 0xC4);
        *(s32 *)(s0 + 0xC8) = 0;
        v -= 1;
        *(s32 *)(s0 + 0xC4) = v;
        if (v > 0) {
            break;
        }
        if (s2 != 0) {
            break;
        }
        func_80031DB4(*(s32 *)(s0 + 0x84), *(s32 *)(s0 + 0x88));
        *(s32 *)(s0 + 0xCC) = 0;
        break;
    default:
        break;
    }
    func_800D6994(s0);
    *(s32 *)(s0 + 0xC8) += 1;
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D6594);

/* No pins: the near-miss seed passed the local `v` array to func_800D68B4;
 * retail passes the untouched a1 argument, and func_800D6B54 takes one arg
 * (retail never sets a1 before that call). */
s32 func_800D6720(u8 *a0, s32 a1)
{
    s32 v[4];
    s32 w[4];
    s32 x;
    s32 x2;
    s32 y;
    s32 t;
    s32 lim;

    x = *(s32 *)(a0 + 0x8C) >> 8;
    y = *(s32 *)(a0 + 0x90) >> 8;
    v[2] = 0;
    v[0] = x + 0x40;
    v[1] = y - 0x10;
    func_800D68B4(a0, (u8 *)a1);
    t = *(s32 *)(a0 + 0x90);
    x2 = *(s32 *)(a0 + 0x8C) >> 8;
    w[2] = 0;
    w[0] = x2 + 0x40;
    w[1] = (t >> 8) - 0x10;
    lim = *(s32 *)(a0 + 0xA0);
    if (t < lim) {
        *(s32 *)(a0 + 0x90) = lim;
        *(s32 *)(a0 + 0xBC) = 0;
        return (s32)((u32)a1 >> 31);
    }
    if (0x40000 < t) {
        *(s32 *)(a0 + 0x90) = 0x40000;
        *(s32 *)(a0 + 0xBC) = 0;
        if (a1 < 0) {
            return 0;
        }
        func_80031D0C(*(u8 **)(a0 + 0x84), *(s32 *)(a0 + 0x88));
        return 1;
    }
    if (func_80073010((u8 *)w, (u8 *)v) != 0) {
        *(s32 *)(a0 + 0xBC) = 0;
        *(s32 *)(a0 + 0x90) = w[1] << 8;
        func_800D6B54(a0);
        func_8001BE78((s32)(u32)D_8005F824, 0x62, 0);
        return (s32)((u32)(~a1) >> 31);
    }
    return 0;
}

void func_800D6830(u8 *arg0, s32 arg1) {
    s32 v[4];
    s32 w[4];
    s32 x;
    s32 y;

    x = (*(s32 *)(arg0 + 0x8C) >> 8) + 0x40;
    y = *(s32 *)(arg0 + 0x90) >> 8;
    v[0] = x;
    v[1] = y - 0x10;
    v[2] = 0;
    w[0] = x;
    w[1] = y + 0xF0;
    w[2] = 0;
    if (func_80073010((u8 *)w, (u8 *)v) != 0) {
        *(s32 *)(arg0 + 0xBC) = 0;
        *(s32 *)(arg0 + 0x90) = w[1] << 8;
    } else {
        func_800D68B4(arg0, (u8 *)0x71C);
    }
}

/* No pins: the near-miss needed the x/y pointer hoists (xp/yp locals) to fix
 * the register tie-break. */
void func_800D68B4(u8 *a0, u8 *a1)
{
    u32 acc;
    s32 i;
    u8 *p;
    s32 out[4];
    s32 x[3];
    s32 y[3];
    s32 *yp;
    s32 *xp;

    acc = 0x20000;
    xp = x;
    yp = y;

    p = a0 + 0xAC;
    for (i = 1; i >= 0; i--)
    {
        u8 *q = *(u8 **)p;
        if (q != 0)
        {
            acc += *(u32 *)(func_8007773C(q) + 4);
        }
        p += 4;
    }
    x[0] = 0;
    x[1] = *(s32 *)(a0 + 0xBC);
    x[2] = 0;
    y[0] = 0;
    y[1] = (s32)a1;
    y[2] = 0;
    func_80079E90(out, xp, yp, acc);
    *(s32 *)(a0 + 0xBC) = x[1];
    *(s32 *)(a0 + 0x90) += out[1];
}

/* Register pin: `v0` fixed to $v0 so cc1 keeps the 0x1000 constant / squashed
 * index materialisation in the return-value register (retail reuses $v0). */
void func_800D6994(u8 *a0)
{
    u8 *p;
    s32 t1;
    s32 t2;
    register s32 v0 asm("$2"); /* PIN $v0 */
    u16 s;
    u8 *base;

    p = *(u8 **)(a0 + 0x80);
    *(s32 *)(p + 0x8) = 0;
    t1 = *(s32 *)(a0 + 0x8C);
    t2 = *(s32 *)(a0 + 0x90);
    v0 = 0x1000;
    *(s32 *)(p + 0x2C) = v0;
    *(s32 *)(p + 0x30) = 0;
    *(s32 *)(p + 0x34) = v0;
    *(s32 *)(p + 0x38) = 0;
    *(s32 *)(p + 0x3C) = v0;
    *(s32 *)(p + 0x48) = 0;
    *(s32 *)(p + 0x40) = t1 >> 8;
    *(s32 *)(p + 0x44) = t2 >> 8;
    v0 = *(s32 *)(a0 + 0xC8);
    v0 = (v0 << 8) & 0x3F00;
    base = ((u8 *)&D_8001093C);
    base = base - (0 - v0);
    s = ((u16 *)base)[1];
    func_800240C8(p + 0x2C, (s << 16) >> 21);
}

/* Register pin: `v0` fixed to $v0 so cc1 uses the return register for the
 * func_80037010 result arithmetic (retail reuses $v0). */
void func_800D6A18(u8 *a0, u8 *a1)
{
    u8 *s0;
    u8 *s1;
    u8 *s2;
    register s32 v0 asm("$2"); /* PIN $v0 */
    s32 v2;
    s32 t[3];
    s32 c1;
    s32 c2;

    s0 = a0;
    s2 = a1;
    t[2] = 0;
    t[0] = *(s32 *)(s0 + 0x8C);
    t[1] = *(s32 *)(s0 + 0x90);
    s1 = s0 + 0x38;
    *(s32 *)(s0 + 0x74) = 0;
    t[0] = t[0] >> 8;
    t[1] = (t[1] >> 8) + 0x70;
    *(s32 *)(s0 + 0x6C) = t[0];
    *(s32 *)(s0 + 0x70) = t[1];
    v2 = (s32)func_80037010(&D_8005EE48);
    v0 = v0 >> 12;
    if (v2 < 0)
    {
        v0 = (v2 + 0xFFF) >> 12;
    }
    t[0] = v2 - (v0 << 12);
    t[1] = -0x38E0;
    t[2] = 0;
    *(s32 *)(s0 + 0x2C) = t[1];
    *(s32 *)(s0 + 0x28) = t[0];
    *(s32 *)(s0 + 0x30) = t[2];
    c2 = *(s32 *)(s0 + 0xB4) > 0;
    c1 = *(s32 *)(s0 + 0xB8) > 0;
    if (*(s32 *)(s0 + 0xB4) > 0)
    {
        *(s32 *)(s0 + 0xB4) -= 1;
    }
    if (*(s32 *)(s0 + 0xB8) > 0)
    {
        *(s32 *)(s0 + 0xB8) -= 1;
    }
    *(s32 *)(*(s32 *)(s0 + 0x38) + 4) = *(s32 *)(s0 + 0x3C);
    *(s32 *)(*(s32 *)(s1 + 4)) = *(s32 *)(s0 + 0x38);
    *(s32 *)(s0 + 0x38) = (s32)s1;
    *(s32 *)(s0 + 0x3C) = (s32)s1;
    if (c2 == 0)
    {
        if (c1 != 0)
        {
            goto tail;
        }
        func_8006F04C(s2, s1);
        goto done;
    }
    if (c1 == 0)
    {
        func_8006F02C(s2, s1);
    }
    goto done;
tail:
    func_8006F00C(s2, s1);
done:
    ;
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D6B54);

u8 *func_800D6CA4(u8 *arg0, u8 *arg1) {
    s32 x;
    s32 y;
    s32 z;

    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_800D3E64;
    x = *(s32 *)(arg1 + 0);
    y = *(s32 *)(arg1 + 4);
    z = *(s32 *)(arg1 + 8);
    *(s32 *)(arg0 + 0x18) = x;
    *(s32 *)(arg0 + 0x1C) = y;
    *(s32 *)(arg0 + 0x20) = z;
    *(s32 *)(arg0 + 0x2C) = ((0x1000 - *(s32 *)(arg1 + 8)) >> 8) + 4;
    return arg0;
}

void func_800D6D18(u8 *arg0, u8 *arg1) {
    s32 v;
    v = *(s32 *)(arg0 + 0x18) - *(s32 *)(arg0 + 0x2C);
    *(u8 *)(arg0 + 0x30) = *(u8 *)(arg1 + 0xD58);
    *(s32 *)(arg0 + 0x18) = v;
    if (v < -0x2FF) {
        *(s32 *)(arg0 + 0x18) = v + 0x600;
    }
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D6D4C);

/* Register pin: `v0` fixed to $a0 so cc1 keeps the 0x18-0x2C difference in the
 * argument register (retail reuses $a0). */
void func_800D6F74(u8 *a0, u8 *a1)
{
    register s32 v0 asm("$4"); /* PIN $a0 */
    s32 t;
    s32 r;
    s32 n;
    u8 b;
    RandomState *p;

    v0 = *(s32 *)(a0 + 0x18);
    t = *(s32 *)(a0 + 0x2C);
    b = *(u8 *)(a1 + 0xD58);
    v0 = v0 - t;
    p = &D_8005EE48;
    *(u8 *)(a0 + 0x30) = b;
    *(s32 *)(a0 + 0x18) = v0;
    if (v0 < -0x17FF) {
        n = v0 + 0x3000;
        *(s32 *)(a0 + 0x18) = n;
        r = (s32)func_80037010(p);
        r = r & 0x7FF;
        r = r + 0x200;
        *(s32 *)(a0 + 0x20) = r;
        *(s32 *)(a0 + 0x2C) = ((0x1000 - r) >> 8) + 4;
    }
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D6FEC);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D7118);

/* Register pins: `cur`->$s2, `base`->$s3, `d`->$s1, `r1`->$s0, `r2`->$a0
 * match retail's allocation (all flagged). */
void func_800D7210(u8 *a0) {
    register Vec *cur asm("$18");  /* PIN $s2 */
    register Vec *base asm("$19"); /* PIN $s3 */
    RandomState *rnd;
    s32 i;
    register s32 d asm("$17");   /* PIN $s1 */
    register s32 r1 asm("$16");  /* PIN $s0 */
    register s32 r2 asm("$4");   /* PIN $a0 */
    s32 n;
    cur = (Vec *)(a0 + 0x80);
    base = (Vec *)a0;
    d = *(s32 *)(a0 + 0x144);
    n = *(s32 *)(a0 + 0x140);
    rnd = &D_8005EE48;
    if (d <= 0) {
        d = 1;
    }
    if (n > 0) {
        i = n;
        do {
            r1 = (s32)func_80037010(rnd) % d;
            r2 = (s32)func_80037010(rnd) % d;
            cur->x = cur->x + ((base->x + r1 - cur->x) >> 4);
            cur->y = cur->y + ((base->y + r2 - cur->y) >> 4);
            base++;
            cur++;
            i--;
        } while (i != 0);
    }
}

/* Register pins: `n`->$v1 and `m`->$v0 match retail's countdown setup; the
 * "+r"(i) asm barrier keeps the loop counter in $s0. */
void func_800D72FC(u8 *a0, s32 a1) {
    register s32 n asm("$3");  /* PIN $v1 */
    register s32 m asm("$2");  /* PIN $v0 */
    s32 i;
    u8 *p1;
    u8 *p2;
    u8 *p3;

    n = *(s32 *)(a0 + 0x140);
    m = n - 1;
    p1 = a0 + 0x80;
    p2 = a0 + 0x100;
    p3 = a0 + 0x120;
    if (m > 0) {
        i = m;
        __asm__ volatile("" : "+r"(i));
        i = i - 1;
        do {
            func_800D739C(a0, a1, p1, p3, *(s32 *)p2);
            p1 += 0x10;
            p2 += 4;
            p3 += 4;
        } while (i != 0 ? (i--, 1) : 0);
    }
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D739C);

/* Register pins: `p2`->$s5, `p1`->$s4, t0-t4->$a2,$a3,$v0,$v1,$a1 match
 * retail's two vec-argument pointers and six diff temporaries. `g` is left
 * UNPINNED (pinning it breaks the strength-reduced pointer induction). */
void func_800D75A8(u8 *a0, s32 *a1, s32 *a2) {
    register s32 *p2 asm("$21"); /* PIN $s5 */
    register s32 *p1 asm("$20"); /* PIN $s4 */
    register s32 t0 asm("$6");   /* PIN $a2 */
    register s32 t1 asm("$7");   /* PIN $a3 */
    register s32 t2 asm("$2");   /* PIN $v0 */
    register s32 t3 asm("$3");   /* PIN $v1 */
    register s32 t4 asm("$5");   /* PIN $a1 */
    u8 *g;
    s32 vec[3];
    s32 n;
    s32 i;
    s32 v;

    g = a0;
    p2 = a2;
    p1 = a1;
    t0 = p2[0];
    t1 = p2[1];
    t2 = p1[0];
    t3 = p2[2];
    t4 = p1[1];
    t0 = t0 - t2;
    t2 = p1[2];
    t1 = t1 - t4;
    vec[0] = t0;
    vec[1] = t1;
    t3 = t3 - t2;
    vec[2] = t3;
    v = func_800237A0(vec);
    if (v < 0) {
        v += 0x7F;
    }
    n = (v >> 7) + 1;
    if (n >= 9) {
        n = 8;
    }
    if (n < 3) {
        n = 3;
    }
    for (i = 0; i < n; i++) {
        func_800238C4((Vec *)(g + i * 0x10), p1, p2, (i << 12) / (n - 1));
    }
    if (*(s32 *)(g + 0x140) != n && n > 0) {
        u8 *r = g + 0x80;
        for (i = n; i != 0; i--) {
            *(V3 *)r = *(V3 *)((u8 *)r - 0x80);
            r += 0x10;
        }
    }
    *(s32 *)(g + 0x140) = n;
}

void func_800D76F8(u8 *arg0, s32 arg1) {
    s32 n;
    s32 m;
    s32 i;
    s32 *p;
    s32 *q;

    n = *(s32 *)(arg0 + 0x140);
    m = n - 1;
    p = (s32 *)(arg0 + 0x124);
    i = 1;
    if (i < m) {
        i = m - 1;
        do {
            *p++ = arg1;
        } while (--i);
    }
    q = (s32 *)arg0;
    q += m;
    *(s32 *)((u8 *)q + 0x120) = 0;
    *(s32 *)(arg0 + 0x120) = 0;
}

/* No pins: the argument-byte unpack and lerp loop reproduce retail directly. */
void func_800D7738(u8 *a0, u32 a1, u32 a2) {
    Vec va;
    Vec vb;
    Vec out;
    s32 n;
    s32 m;
    s32 i;
    u8 *pa;
    u8 *pb;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 t5;

    pa = (u8 *)&a1;
    pb = (u8 *)&a2;
    t0 = pa[0];
    t1 = pa[1];
    t2 = pa[2];
    t3 = pb[0];
    t4 = pb[1];
    t5 = pb[2];
    va.x = t0;
    va.y = t1;
    va.z = t2;
    vb.x = t3;
    vb.y = t4;
    vb.z = t5;
    n = *(s32 *)(a0 + 0x140);
    m = n - 1;
    for (i = 0; i <= m; i++) {
        func_800238C4(&out, &va, &vb, (i << 12) / m);
        *(s32 *)(a0 + 0x120 + (i << 2)) = out.x | (out.y << 8) | (out.z << 16);
    }
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D7814);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D7A44);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D7DA4);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D7E38);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D8068);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D8200);

u8 *func_800D83BC(u8 *arg0, u8 *arg1) {
    s32 v;

    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_800D3DC4;
    *(s32 *)(arg0 + 0x18) = (s32)func_8002BD74(arg1);
    func_8007A8D0(arg1, arg0 + 0x1C);
    v = *(s16 *)(func_8007773C(arg1) + 2);
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x38) = 0xFF;
    *(s32 *)(arg0 + 0x2C) = v;
    return arg0;
}

void func_800D8438(u8 *arg0) {
    u8 *v;

    v = func_8002BDC8(*(u8 **)(arg0 + 0x18));
    if (v == 0) {
        if (arg0 != 0) {
            u8 *p = *(u8 **)(arg0 + 0x14);
            ((void (*)(s32, s32)) * (s32 *)(p + 0x1C))((s32)(arg0 + *(s16 *)(p + 0x18)), 3);
        }
    } else {
        func_8007A8D0(v, arg0 + 0x1C);
        *(s32 *)(arg0 + 0x34) = (s32)func_80037010(&D_8005EE48);
        *(s32 *)(arg0 + 0x30) = *(s32 *)(arg0 + 0x30) + 1;
        if (*(s32 *)(arg0 + 0x30) >= 3) {
            *(s32 *)(arg0 + 0x30) = 0;
        }
        *(s32 *)(arg0 + 0x38) = *(s32 *)(arg0 + 0x38) - 4;
        if (*(s32 *)(arg0 + 0x38) <= 0) {
            if (arg0 != 0) {
                u8 *p = *(u8 **)(arg0 + 0x14);
                ((void (*)(s32, s32)) * (s32 *)(p + 0x1C))((s32)(arg0 + *(s16 *)(p + 0x18)), 3);
            }
        }
    }
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D8504);

u8 *func_800D8654(u8 *arg0) {
    func_8002BC9C(arg0, 0);
    *(u8 **)(arg0 + 0x14) = D_800D3D9C;
    *(s32 *)(arg0 + 0x114) = 0x200;
    *(s32 *)(arg0 + 0x118) = 0;
    *(s32 *)(arg0 + 0x11C) = 0;
    *(s32 *)(arg0 + 0x120) = 0;
    return arg0;
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D86A0);

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D877C);

void func_800D89F8(s32 arg0, s32 arg1) {
    s32 s0 = arg0;
    s32 s1 = arg1;
    s32 p;
    s32 t1, t2, t3;

    func_8001FC58(s0 + 0xD78, 2);
    func_8002D86C((void *)((u32)s0 + 0xD60U), 2);
    p = s0 + 0xD38;
    t1 = *(s32 *)(s0 + 0xD38);
    t2 = *(s32 *)(s0 + 0xD3C);
    *(s32 *)(t1 + 4) = t2;
    t3 = *(s32 *)(p + 4);
    *(s32 *)(t3 + 0) = *(s32 *)(s0 + 0xD38);
    *(s32 *)(s0 + 0xD38) = p;
    *(s32 *)(s0 + 0xD3C) = p;
    func_8006F23C(s0, s1);
}

s32 func_800D8A6C(u8 *arg0) {
    return *(s32 *)(arg0 + 0xD50);
}

void func_800D8A78(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D8AC0(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D8B08(u8 *arg0, s32 arg1) {
    *(u32 *)arg0 = (u32)D_80065154;
    if (arg1 & 1) {
        func_8002B3D0(arg0);
    }
}

u8 *func_800D8B3C(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4) {
    s32 a;
    s32 b;
    s32 c;
    *(s32 *)(arg0 + 0x0) = (s32)D_800D3FD4;
    *(s32 *)(arg0 + 0x4) = arg1;
    *(s32 *)(arg0 + 0x8) = arg3;
    *(s32 *)(arg0 + 0xC) = arg4;
    a = arg2[0];
    b = arg2[1];
    c = arg2[2];
    *(s32 *)(arg0 + 0x10) = a;
    *(s32 *)(arg0 + 0x14) = b;
    *(s32 *)(arg0 + 0x18) = c;
    return arg0;
}

void func_800D8B78(u8 *arg0, u8 *arg1) {
    u32 v0;
    u32 v1;
    u32 v2;

    v0 = *(u32 *)(arg1 + 0);
    v1 = *(u32 *)(arg1 + 4);
    v2 = *(u32 *)(arg1 + 8);
    *(u32 *)(arg0 + 0x10) = v0;
    *(u32 *)(arg0 + 0x14) = v1;
    *(u32 *)(arg0 + 0x18) = v2;
}

void func_800D8B94(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D8BDC(s32 arg0, s32 arg1) {
    s32 s1;
    s32 s0;
    s32 p;
    s32 a2;
    s32 a0v;

    s1 = arg0;
    s0 = arg1;
    *(s32 *)(s1 + 0x40) = (s32)&D_800D3F54;
    *(s32 *)(s1 + 0x14) = (s32)&D_800D3F74;
    p = s1 + 0x60;
    a2 = *(s32 *)(s1 + 0x60);
    a0v = *(s32 *)(s1 + 0x64);
    *(s32 *)(s1 + 0x90) = (s32)&D_80065174;
    *(s32 *)(a2 + 4) = a0v;
    a2 = *(s32 *)(p + 4);
    *(s32 *)(a2 + 0) = *(s32 *)(s1 + 0x60);
    *(s32 *)(s1 + 0x60) = p;
    *(s32 *)(s1 + 0x64) = p;
    *(s32 *)(s1 + 0x40) = (s32)&D_80065154;
    func_8002BCEC((u8 *)s1, 0);
    if (s0 & 1) {
        func_8002BDA8((u8 *)s1);
    }
}

void func_800D8C7C(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D8CC4(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D8D0C(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D8D54(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D8D9C(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D8DE4(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

u8 *func_800D8E2C(u8 *arg0, u8 *arg1) {
    u8 *p = arg0;

    func_800D6CA4(p, arg1);
    *(u8 **)(p + 0x14) = D_800D3E3C;
    *(s32 *)(p + 0x2C) *= 2;
    return p;
}

void func_800D8E6C(u8 *arg0, s32 arg1) {
    func_800D75A8(arg0, arg1, arg0 + 0x70 + (*(s32 *)(arg0 + 0x140) << 4));
}

void func_800D8E9C(u8 *arg0, u8 *arg1) {
    s32 x = *(s32 *)(arg0 + 0x140);
    s32 y = (x << 4) + 0x70;

    func_800D75A8(arg0, arg0 + y, arg1);
}

void func_800D8ECC(u8 *arg0, s32 arg1) {
    s32 off;
    off = (*(s32 *)(arg0 + 0x140) - 1) * 4;
    func_800D7738(arg0, arg1, *(s32 *)(arg0 + off + 0x120));
}

void func_800D8F04(u8 *arg0, s32 arg1) {
    s32 off;
    off = (*(s32 *)(arg0 + 0x140) - 1) * 4;
    func_800D7738(arg0, *(s32 *)(arg0 + off + 0x120), arg1);
}

void func_800D8F3C(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x144) = arg1;
}

void func_800D8F44(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x148) = arg1;
}

void *func_800D8F4C(void *arg0) {
    return arg0;
}

void func_800D8F54(s32 arg0, s32 arg1) {
    s32 s1;
    s32 s0;
    s32 p;
    s32 a2;
    s32 a3;

    s1 = arg0;
    s0 = arg1;
    p = s1 + 0x5B0;
    *(s32 *)(s1 + 0x5E0) = (s32)&D_80065174;
    *(s32 *)(*(s32 *)(s1 + 0x5B0) + 4) = *(s32 *)(s1 + 0x5B4);
    *(s32 *)(*(s32 *)(p + 4) + 0) = *(s32 *)(s1 + 0x5B0);
    *(s32 *)(s1 + 0x5B0) = p;
    *(s32 *)(s1 + 0x5B4) = p;
    a3 = s1 + 0x568;
    *(s32 *)(s1 + 0x598) = (s32)&D_80065174;
    *(s32 *)(*(s32 *)(s1 + 0x568) + 4) = *(s32 *)(s1 + 0x56C);
    *(s32 *)(*(s32 *)(a3 + 4) + 0) = *(s32 *)(s1 + 0x568);
    *(s32 *)(s1 + 0x568) = a3;
    *(s32 *)(s1 + 0x56C) = a3;
    *(s32 *)(s1 + 0x548) = (s32)&D_80065154;
    func_8002BCEC((u8 *)s1, 0);
    if (s0 & 1) {
        func_8002BDA8((u8 *)s1);
    }
}

void func_800D9004(s32 arg0, s32 arg1) {
    s32 s1;
    s32 s0;
    s32 p;
    s32 a2;
    s32 a0v;

    s1 = arg0;
    s0 = arg1;
    p = s1 + 0x38;
    a2 = *(s32 *)(s1 + 0x38);
    a0v = *(s32 *)(s1 + 0x3C);
    *(s32 *)(s1 + 0x68) = (s32)&D_80065174;
    *(s32 *)(a2 + 4) = a0v;
    a2 = *(s32 *)(p + 4);
    *(s32 *)(a2 + 0) = *(s32 *)(s1 + 0x38);
    *(s32 *)(s1 + 0x38) = p;
    *(s32 *)(s1 + 0x3C) = p;
    *(s32 *)(s1 + 0x18) = (s32)&D_80065154;
    func_8002BCEC((u8 *)s1, 0);
    if (s0 & 1) {
        func_8002BDA8((u8 *)s1);
    }
}

void func_800D908C(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

void func_800D90D4(u8 *arg0, s32 arg1) {
    func_8002BCEC(arg0, 0);
    if (arg1 & 1) {
        func_8002BDA8(arg0);
    }
}

INCLUDE_ASM("asm/us/st03/nonmatchings/5F8", func_800D911C);
