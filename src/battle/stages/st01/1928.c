#include "mesh_scene_visibility.h"
#include "game_rotation.h"
#include "game_audio_api.h"
#include "common.h"
#include "game_positions.h"
#include "game_random.h"
#include "game_lists.h"

void func_8001BEDC(void *a0);
void func_8001FC58(void *a0, s32 a1);
void func_8001FD40(void *a0);

void func_80020BFC(void *a0, s32 a1);
void func_80021080(void *a0, void *a1);
void func_8002189C(void *a0);
s32 func_80026B4C(void *a0, s32 a1);
void func_8002B3D0(void);
s32 func_8002EF48(void *a0, void *a1);
void *func_8006EF44(void *a0);
void *func_8006EF4C(void *a0);
void *func_800700B0(void *a0, s32 a1);
void func_80070300(void *a0);
void func_800727AC(void *a0);

void func_800D4B00(void *a0);
void func_800D5818(u8 *a0);

extern u8 D_80065154[];
extern u8 D_800D4004[];
extern u8 D_800D3FB4[];
extern u8 D_800D3F8C[];
extern u8 D_800D3F64[];
extern u8 D_800D3F3C[];
extern u8 D_800D3F14[];
extern u8 D_800D3EEC[];
extern u8 D_800D3EC4[];
extern u8 D_800D3E9C[];
extern u8 D_800D3E74[];
extern u8 D_800D3E4C[];
extern u8 D_800D3E24[];
extern u8 D_800D3DFC[];
extern u8 D_800D4024[];
extern void func_8002BCEC(void *a0, s32 a1);
extern void func_8002BDA8(void *a0);
extern void func_800720EC(void *a0);

extern void func_8006F23C(void *a0, void *a1);
extern s32 D_800D3D10[];
typedef struct StageNode { struct StageNode *next, *prev; } StageNode;
extern void func_80055BC4(s16 *rect, s32 x, s32 y);
extern void func_80071F64(void *self);
extern s32 func_8006F18C(void *self);
extern s32 func_8006F12C(void *self);
extern s32 func_8006F178(void *self);
extern void func_800D4CA0(void *self);
extern void func_800D5C0C(void *self);
extern void func_800D521C(void *self);
extern void func_800D5428(void *self);
extern void func_800D55C4(void *self);
extern void func_800D59A0(void *self);
extern void func_800D5DA0(void *self);
extern void func_800D5884(void *self);
extern void func_800D513C(void *self);
extern void func_800D4FA4(void *self);

extern u8 D_8005F824[];

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D5428);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D547C);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D55C4);

void func_800D5818(u8 *a0) {
  u8 *s0 = a0;
  u8 *s1 = s0 + 0xD4C;
  u8 buf[0x20];
  func_8002189C(s1);
  func_8002EF48(func_8006EF4C(s0), buf);
  func_80021080(s1, buf);
  s0 += 0xD88;
  func_8001FE8C((Entry *)s0, (s32)s1);
  func_8001FD40(s0);
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D5884);

void func_800D5964(u8 *a0) {
  s32 t = *(s32 *)(a0 + 0xD48);
  *(u16 *)(a0 + 0xF7E) = 0;
  *(s32 *)(a0 + 0xF80) = 0;
  if (t != 0) {
    func_8001BEDC(t);
    *(s32 *)(a0 + 0xD48) = 0;
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D59A0);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D5C0C);

void func_800D5CC4(u8 *a0) {
  register u8 *v1 asm("$3");
  register u8 *v0 asm("$2");
  register u8 *a1 asm("$5");
  register u8 *a2 asm("$6");
  v1 = *(u8 **)(a0 + 0xD38);
  v0 = *(u8 **)(v1 + 0x2C);
  a1 = *(u8 **)(v0 + 0);
  *(u8 **)(a1 + 4) = *(u8 **)(v0 + 4);
  a2 = *(u8 **)(v0 + 4);
  *(u8 **)(a2 + 0) = *(u8 **)(v0 + 0);
  *(u8 **)(v0 + 0) = v0;
  *(u8 **)(v0 + 4) = v0;
  func_80031D0C(*(u8 **)(a0 + 0xD38), 9);
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D5D20);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D5DA0);

u8 *func_800D5ED0(u8 *a0, s32 a1) {
  *(u8 **)a0 = D_800D4004;
  *(s32 *)(a0 + 4) = a1;
  return a0;
}

void func_800D5EE8(void) {
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D5EF0);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D6000);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D6100);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D61D4);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D63CC);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D6748);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D6820);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D687C);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D6B48);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D6CE4);

s32 func_800D6FE4(u8 *a0) {
  return *(s32 *)(a0 + 0x20) + 0x2C;
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D6FF0);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D7058);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D7144(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3FB4;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D7198);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D71F4);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D73A8);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D7474(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3F8C;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

/* volatile reads defeat cc1's CSE of the twice-read counter (retail emits two
   `lhu $v0/$v1,0x18(a0)`); the asm barrier keeps the table base as the first
   `addu` operand, matching retail's `addu $a1,$a1,$v0`. */
void func_800D74C8(u8 *a0) {
  u8 *a1 = ((u8 *)&D_8001093C);
  u16 idx = *(volatile u16 *)(a0 + 0x18);
  u16 cur = *(volatile u16 *)(a0 + 0x18);
  u16 t;
  __asm__("" : "+r"(a1));
  a1 += (idx << 6) & 0x3FC0;
  t = *(u16 *)(a1 + 2);
  *(u16 *)(a0 + 0x18) = cur + 1;
  *(u16 *)(a0 + 0x1A) = (((s16)t >> 7) + 0xA0) >> 1;
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D7508);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D76CC);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D7758(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3F64;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D77AC);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D77FC);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D79C0);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D7AA0(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3F3C;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D7AF4);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D7BD0);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D7DE4);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D7EDC(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3F14;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D7F30);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D8038);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D8214);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D82E8);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D83D8(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3EEC;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D842C);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D8658);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D8808);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D894C(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3EC4;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D89A0);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D8B58);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D8CE4);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D8DF0(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3E9C;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D8E44);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D8FC0);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D916C);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D9204(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3E74;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D9258);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D9324);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D94A8);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D95CC(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3E4C;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D9620);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D97A8);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D9A94);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D9B48(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3E24;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D9B9C);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D9DE8);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D9F44);

/* Pin $s0 ($16) to reproduce retail's hoisted vtable lui/addiu schedule. */
void func_800D9FE0(u8 *a0, s32 a1) {
  register s32 f asm("$16");
  f = a1;
  *(u8 **)(a0 + 0x14) = D_800D3DFC;
  func_8002BCEC(a0, 0);
  if (f & 1) {
    func_8002BDA8(a0);
  }
}

void func_800DA034(u8 *a0) {
  u16 v = *(u16 *)(a0 + 0x1C) + 1;
  *(u16 *)(a0 + 0x1C) = v;
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800DA048);

void func_800DA2C4(u8 *a0, u32 a1) {
  *(u8 **)a0 = D_80065154;
  if (a1 & 1) {
    func_8002B3D0();
  }
}

void func_800DA2F8(u8 *a0, u8 *a1) {
  s32 v0 = *(s32 *)(a1 + 0);
  s32 v1 = *(s32 *)(a1 + 4);
  /* Pin the third load to $a2 so it does not reuse the $a1 base register. */
  register s32 v2 asm("$6");
  v2 = *(s32 *)(a1 + 8);
  *(s32 *)(a0 + 8) = v0;
  *(s32 *)(a0 + 0xC) = v1;
  *(s32 *)(a0 + 0x10) = v2;
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800DA314);
