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

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D409C);

void func_800D42D0(u8 *a0, s32 a1) {
  register u8 *s0 asm("$16");
  register s32 s1 asm("$17");
  s0 = a0;
  s1 = a1;
  *(u8 **)(s0 + 0xD34) = D_800D4024;
  func_8001BEDC(*(u8 **)(s0 + 0xD44));
  func_8001BEDC(*(u8 **)(s0 + 0xD48));
  func_8001FC58(s0 + 0xD88, 2);
  func_80020BFC(s0 + 0xD4C, 2);
  func_8006F23C(s0, s1);
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D4340);

void func_800D4954(u8 *a0) {
  u8 *s0 = a0;
  func_80070300(a0);
  func_800D4B00(s0);
  func_8007767C(func_800700B0(s0, 0), (s32 *)(s0 + 0xF94));
  func_8007767C(func_800700B0(s0, 1), (s32 *)(s0 + 0xFA4));
}

s32 func_800D49B0(u8 *a0, u8 *a1) {
  return (*(s32 *)(a0 + 0x350) + 0x200) < *(s32 *)(a1 + 4);
}

/* Pins keep the three copied words in $a0/$v1/$a1 (retail's load order). */
void func_800D49C4(u8 *a0) {
  u8 *v0;
  register s32 x asm("$4");
  register s32 y asm("$3");
  register s32 z asm("$5");
  func_800720EC(a0);
  if (*(s32 *)(a0 + 0x320) > 0) {
    *(s32 *)(a0 + 0x320) = 0;
    v0 = func_8006EF4C(a0);
    *(s32 *)(v0 + 0x50) = 1;
    x = *(s32 *)(a0 + 0x31C);
    y = *(s32 *)(a0 + 0x320);
    z = *(s32 *)(a0 + 0x324);
    *(s32 *)(v0 + 0) = x;
    *(s32 *)(v0 + 4) = y;
    *(s32 *)(v0 + 8) = z;
  }
}

void func_800D4A20(u8 *self) {
    func_80071F64(self);
    if (func_8006F18C(self) != 0) {
        *(s16 *)(self + 0xFD4) = 1;
        return;
    }
    *(s16 *)(self + 0xFD4) = 0;
    if (func_8006F12C(self) != 0 && func_8006F178(self) == 0)
        return;
    func_800D4CA0(self);
    func_800D5C0C(self);
    func_800D521C(self);
    func_800D5428(self);
    func_800D55C4(self);
    func_800D59A0(self);
    func_800D5DA0(self);
    func_800D5884(self);
    func_800D513C(self);
    func_800D4FA4(self);
    if (*(u8 *)(self + 0xD3C) == 0)
        func_8001BE78((s32)(u32)D_8005F824, 0x5A, 0);
    *(u32 *)(self + 0xD3C) += 1;
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D4B00);

void func_800D4C38(u8 *a0) {
  u8 *s1;
  func_800D5818(a0);
  s1 = (u8 *)func_8006EF44(a0);
  func_800727AC(a0);
  func_80026B4C(a0 + 0xD4C, *(s32 *)(s1 + 0x10));
}

void func_800D4C84(u8 *a0) {
  *(u16 *)(a0 + 0xF84) = 0;
  *(u16 *)(a0 + 0xF86) = 0;
  *(u16 *)(a0 + 0xF88) = 0;
  *(u16 *)(a0 + 0xF8A) = 0;
  *(u16 *)(a0 + 0xE24) = 0;
  *(u16 *)(a0 + 0xE26) = 0;
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D4CA0);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D4E64);

void func_800D4F4C(u8 *a0) {
  s32 values[3];
  /* Pin the copy pointers, counter, and source words to retail's register map. */
  register u8 *t0 asm("$8");
  register s32 *src asm("$6");
  register s32 *dst asm("$7");
  register s32 i asm("$3");
  register s32 a asm("$4");
  register s32 b asm("$5");
  register s32 c asm("$2");
  t0 = a0;
  dst = (s32 *)(t0 + 0xF70);
  src = values;
  a = D_800D3D10[0];
  b = D_800D3D10[1];
  c = D_800D3D10[2];
  i = 2;
  values[0] = a;
  values[1] = b;
  values[2] = c;
  do {
    *dst++ = *src++;
  } while (--i >= 0);
  *(u16 *)(t0 + 0xF60) = 0;
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D4FA4);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D50D8);

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D513C);

void func_800D51D0(u8 *a0) {
  func_8007767C(func_800700B0(a0, 0), (s32 *)(a0 + 0xFB4));
  func_8007767C(func_800700B0(a0, 1), (s32 *)(a0 + 0xFC4));
}

INCLUDE_ASM("asm/us/st01/nonmatchings/59C", func_800D521C);

