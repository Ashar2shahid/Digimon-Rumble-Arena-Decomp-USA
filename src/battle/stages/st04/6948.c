#include "game_rotation.h"
#include "game_base_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_random.h"

extern void func_8002B3D0(u8*);
extern void func_8002BCEC(u8*, u32);
extern void func_8002BDA8(u8*);
extern u8 D_80065154[];
extern u8 D_800D3BCC[];
extern u8 D_80065174[];
extern u8 D_800D3CB4[];
extern u8 D_800D3C64[];
extern u8 D_800D3C14[];
extern u8 D_800D3C3C[];
extern u8 D_800D3C8C[];
extern u8 D_800656C4[];
extern u8 D_800D3CDC[];
extern u8 D_800D3BF4[];
extern u8* func_800700B0(u8*, u32);

extern int func_8007760C(u8*);
void func_800D6948(u8* a0, u32 a1) {
    *(u8**)(a0 + 0x14) = D_800D3CDC;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D699C);

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D6C04);

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D6D68);

void func_800D6E30(u8* a0, u32 a1) {
    *(u8**)(a0 + 0x14) = D_800D3CB4;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D6E84);

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D708C);

/* Retail materialises D_800656C4 into $a0 and keeps the +2 as the load
   displacement (`lh $a1,2($v1)`); cc1 folds +2 into the symbol and picks
   $a0/$a1 the other way round for every unpinned source shape.  Pinning the
   base pointer temp to $a0 (last-resort `register asm`, flagged — see
   docs/DIFFICULT_FUNCTIONS.md § Techniques accepted) reproduces it exactly. */
u8* func_800D7268(u8* a0, u8* a1, u32 a2) {
    u16 k = a2 & 0xFFFF;
    s16 t;
    int v;
    int w;
    s32 buf[4];
    register u8* base asm("$4");

    func_8002BC9C(a0, 0);
    *(u8**)(a0 + 0x14) = D_800D3C8C;
    *(u8**)(a0 + 0x18) = a1;
    *(u16*)(a0 + 0x1C) = k;
    *(u32*)(a0 + 0x20) = 0xF08080;
    func_8007A8D0(func_800700B0(a1, k), (u8 *)buf);
    v = func_8007760C(func_800700B0(*(u8**)(a0 + 0x18), *(u16*)(a0 + 0x1C)));
    base = D_800656C4;
    t = *(s16*)(base + v * 384 + 2);
    w = t * 2;
    *(u16*)(a0 + 0x50) = 0;
    *(u16*)(a0 + 0x48) = 0;
    *(u16*)(a0 + 0x40) = 0;
    *(u16*)(a0 + 0x38) = 0;
    *(u16*)(a0 + 0x44) = -w;
    *(u16*)(a0 + 0x34) = -w;
    *(u16*)(a0 + 0x4C) = w;
    *(u16*)(a0 + 0x3C) = w;
    *(u16*)(a0 + 0x3E) = -w;
    *(u16*)(a0 + 0x36) = -w;
    *(u16*)(a0 + 0x4E) = w;
    *(u16*)(a0 + 0x46) = w;
    return a0;
}

void func_800D7350(u8* a0, u32 a1) {
    *(u8**)(a0 + 0x14) = D_800D3C8C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D73A4);

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D749C);

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D75A4);

void func_800D7724(u8* a0, s32 a1) {
    *(u8**)(a0 + 0x14) = D_800D3C64;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D7778);

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D79D8);

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D7BCC);

void func_800D7D30(u8* a0, u32 a1) {
    *(u8**)(a0 + 0x14) = D_800D3C3C;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

/* Stock switch dispatcher (state machine, table jtbl_800D3BB4).  The 16-bit
   updates and the tail sample loop are register/schedule sensitive; the value
   temporaries are pinned (`register asm`) and empty `__asm__("")` barriers hold
   the load/and/add order — last-resort techniques flagged in
   docs/DIFFICULT_FUNCTIONS.md § Techniques accepted.  The emitted switch table
   is placed at its retail address by config/us/linkers/st04.ld (.rodata_7D84). */
void func_800D7D84(u8 *a0)
{
    u8 *s0 = a0;
    register u16 *q asm("$17");
    u16 *dst;
    s32 i;
    register s32 k asm("$5");
    register s32 d asm("$2");
    register s32 tmp asm("$3");
    register u16 x asm("$4");
    register u16 result asm("$2");

    switch (*(u16 *)(s0 + 0x2A)) {
    case 0:
        d = *(s16 *)(s0 + 0x32);
        tmp = *(s16 *)(s0 + 0x42);
        x = *(u16 *)(s0 + 0x32);
        d -= tmp;
        tmp = *(u16 *)(s0 + 0x42);
        dst = (u16 *)(s0 + 0x2E);
        if (d >= 0) {
            result = x - tmp;
        } else {
            result = tmp - x;
        }
        *dst = result;
        tmp = *(u16 *)(s0 + 0x2C);
        d = *(u16 *)(s0 + 0x3A);
        k = tmp << 2;
        tmp = *(u16 *)(s0 + 0x42);
        d -= k;
        *(u16 *)(s0 + 0x3A) = d;
        __asm__ volatile ("" : : : "memory");
        tmp -= k;
        *(u16 *)(s0 + 0x42) = tmp;
        if (*(s16 *)(s0 + 0x2E) < 0x200) {
            break;
        }
        *(u16 *)(s0 + 0x26) = 0;
        *(u16 *)(s0 + 0x2E) = 0x200;
        *(u16 *)(s0 + 0x2A) += 1;
        /* fallthrough */
    case 1:
        *(u16 *)(s0 + 0x26) += 1;
        if (*(u16 *)(s0 + 0x26) < 6) {
            break;
        }
        *(u16 *)(s0 + 0x2A) += 1;
        /* fallthrough */
    case 2:
        d = *(u16 *)(s0 + 0x2C);
        x = *(u16 *)(s0 + 0x32);
        tmp = *(u16 *)(s0 + 0x42);
        k = d >> 1;
        x -= tmp;
        d = *(u16 *)(s0 + 0x3A);
        tmp += k;
        *(u16 *)(s0 + 0x2E) = x;
        *(u16 *)(s0 + 0x42) = tmp;
        tmp = *(u16 *)(s0 + 0x48);
        d += k;
        *(u16 *)(s0 + 0x3A) = d;
        d = *(u16 *)(s0 + 0x38);
        tmp -= k;
        *(u16 *)(s0 + 0x48) = tmp;
        d -= k;
        *(u16 *)(s0 + 0x38) = d;
        tmp = *(u16 *)(s0 + 0x50);
        d = *(u16 *)(s0 + 0x40);
        tmp += k;
        *(u16 *)(s0 + 0x50) = tmp;
        d += k;
        *(u16 *)(s0 + 0x40) = d;
        if (*(s16 *)(s0 + 0x2E) > 0) {
            break;
        }
        *(u16 *)(s0 + 0x2E) = 0;
        *(u16 *)(s0 + 0x2A) += 1;
        /* fallthrough */
    case 3:
        *(u16 *)(s0 + 0x68) -= 8;
        if (*(s16 *)(s0 + 0x68) > 0) {
            break;
        }
        *(u16 *)(s0 + 0x68) = 0;
        *(u16 *)(s0 + 0x2A) += 1;
        /* fallthrough */
    case 4:
        *(u16 *)(s0 + 0x2A) += 1;
        /* fallthrough */
    default:
        if (s0 != 0) {
            u8 *p = *(u8 **)(s0 + 0x14);
            (*(void (**)(u8 *, s32))(p + 0x1C))(s0 + *(s16 *)(p + 0x18), 3);
        }
        return;
    }

    if (*(u16 *)(s0 + 0x2A) < 4) {
        q = (u16 *)(s0 + 0x58);
        i = 1;
        do {
            register s32 value asm("$2");
            register u16 base asm("$3");
            --i;
            value = func_8006EFEC(*(u8 **)(s0 + 0x18));
            base = *(u16 *)(s0 + 0x30);
            __asm__ volatile ("" : "+r"(value));
            value &= 0xFF;
            __asm__ volatile ("" : "+r"(base), "+r"(value));
            base -= 0x80;
            __asm__ volatile ("" : "+r"(base));
            base += value;
            *q = base;
            q += 4;
        } while (i >= 0);
    }
    *(u16 *)(s0 + 0x28) += 1;
}

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D7FB0);

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D823C);

void func_800D8394(u8* a0, s32 a1) {
    *(u8**)(a0 + 0x14) = D_800D3C14;
    func_8002BCEC(a0, 0);
    if (a1 & 1) {
        func_8002BDA8(a0);
    }
}

/* Retail keeps the table base in $a1 and reuses $v0 for both the index and the
   loaded word (`lhu $v0,0x18` / `lhu $v0,2($a1)`), with the counter reload in
   $v1; cc1 rotates the three temps ($a2/$v1/$a1) for every unpinned shape, so
   all three are pinned (last-resort `register asm`, flagged — see
   docs/DIFFICULT_FUNCTIONS.md § Techniques accepted). */
void func_800D83E8(u8* a0) {
    register u8* base asm("$5");  /* PIN $a1 — table base */
    register u16 idx asm("$2");   /* PIN $v0 — index (reused for the load) */
    register u16 cnt asm("$3");   /* PIN $v1 — counter reload */
    register s16 t asm("$2");     /* PIN $v0 — `lhu $v0,2($a1)` */
    u8* p;
    base = ((u8 *)&D_8001093C);
    idx = *(u16*)(a0 + 0x18);
    p = base - (-((idx << 6) & 0x3FC0));
    t = *(u16*)(p + 2);
    a0[0x1A] = ((s8)(t >> 8)) + 0x6F;
    cnt = *(u16*)(a0 + 0x18);
    *(u16*)(a0 + 0x18) = cnt + 1;
}

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D8424);

u8* func_800D8758(u8* a0, u32 a1) {
    u8* p = a0;
    u32 buf[3];
    *(u8**)(p + 0x0) = D_800D3BF4;
    buf[0] = 0x60;
    buf[1] = 0;
    buf[2] = 0;
    *(u32*)(p + 0x4) = a1;
    *(u32*)(p + 0x8) = 0x60;
    *(u32*)(p + 0xC) = 0;
    *(u32*)(p + 0x10) = 0;
    return p;
}

/* Retail keeps the four accumulator loads and their add order in $t0/$a3/$v0
   with $v1 as the shared table value; cc1 reorders them, so the six value
   temps are pinned (last-resort `register asm`, flagged — see
   docs/DIFFICULT_FUNCTIONS.md § Techniques accepted). */
void func_800D8794(u8* a0, u8* a1) {
    register s32 t0 asm("$8");
    register s32 a3 asm("$7");
    register s32 v1 asm("$3");
    register s32 a2 asm("$6");
    register s32 v0 asm("$2");

    t0 = *(s32*)(a1 + 0x20);
    v0 = *(s32*)(a1 + 0x18);
    v1 = *(s32*)(a0 + 0x4);
    a3 = *(s32*)(a1 + 0x24);
    v0 = v0 + v1;
    *(s32*)(a1 + 0x18) = v0;
    v1 = *(s32*)(a0 + 0x8);
    v0 = *(s32*)(a1 + 0x28);
    a2 = *(s32*)(a0 + 0xC);
    t0 = t0 + v1;
    v1 = *(s32*)(a0 + 0x10);
    a3 = a3 + a2;
    *(s32*)(a1 + 0x20) = t0;
    *(s32*)(a1 + 0x24) = a3;
    v0 = v0 + v1;
    *(s32*)(a1 + 0x28) = v0;
}

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D87D8);

/* Doubly-linked-list unlink.  Retail keeps `next` in $a2, `prev` in $v0 and
   the node pointer in $v1; cc1 folds `v1[1]` back to the raw `s1+0x34` address
   and reorders the block for every un-pinned shape.  Pinning the four values
   ($4/$2/$6/$3) plus the `new_var = v1` copy (which stops cc1 re-deriving the
   address from the node base) reproduces retail exactly — last-resort
   `register asm`, flagged (docs/DIFFICULT_FUNCTIONS.md § Techniques accepted). */
void func_800D88E4(u8* a0, u32 a1) {
    u8* s1 = a0;
    u32 f = a1;
    register u32 p0 asm("$4");
    register u32 p1 asm("$2");
    register u32 p2 asm("$6");
    register u32* v1 asm("$3");
    u32* new_var;

    *(u8**)(s1 + 0x14) = D_800D3BCC;
    *(u8**)(s1 + 0x60) = D_80065174;
    v1 = (u32*)(s1 + 0x30);
    p0 = v1[0];
    p1 = v1[1];
    new_var = v1;
    *(u32*)(p0 + 4) = p1;
    p2 = new_var[1];
    *(u32*)p2 = new_var[0];
    v1[0] = (u32)v1;
    v1[1] = (u32)new_var;
    *(u8**)(s1 + 0x18) = D_80065154;
    func_8002BCEC(s1, 0);
    if (f & 1) {
        func_8002BDA8(s1);
    }
}

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D8978);

void func_800D8C04(u8* a0, u32 a1) {
    *(u8**)a0 = D_80065154;
    if (a1 & 1) {
        func_8002B3D0(a0);
    }
}

void func_800D8C38(u8* a0, u8* a1) {
    u32 x0 = *(u32*)(a1 + 0);
    u32 x1 = *(u32*)(a1 + 4);
    u32 x2 = *(u32*)(a1 + 8);

    *(u32*)(a0 + 8) = x0;
    *(u32*)(a0 + 0xC) = x1;
    *(u32*)(a0 + 0x10) = x2;
}

INCLUDE_ASM("asm/us/st04/nonmatchings/6948", func_800D8C54);
