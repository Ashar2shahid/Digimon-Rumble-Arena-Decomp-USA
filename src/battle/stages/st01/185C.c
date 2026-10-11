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

void func_800D535C(u8 *self) {
    s16 rect[4];
    StageNode *node;
    rect[0] = 0x338;
    rect[1] = 0x80;
    rect[2] = 8;
    rect[3] = 0x40;
    func_80055BC4(rect, 0x2E0, 0);
    rect[0] = 0x338;
    rect[1] = 0x80;
    rect[2] = 8;
    rect[3] = 0x40;
    func_80055BC4(rect, 0x2E0, 0x40);
    node = *(StageNode **)(*(u8 **)(self + 0xD38) + 0x48);
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = node;
    node->prev = node;
    func_8001FD10((ListRoot *)(self + 0xD88), (Entry *)node);
}

