#include "game_heap_wrappers.h"
#include "game_thread.h"
#include "game_sprite_cleanup.h"
#include "game_lerp_words.h"
#include "game_audio_api.h"
#include "common.h"
#include "game_printer_storage.h"
#include "iterator_object.h"
#include "game_input.h"
#include "resource_loader.h"
#include "game_formatter.h"

s32  func_80068484();
void  func_80069028();
void  func_80069178();
void  func_80069364();
extern void func_8002B770();
extern s32 D_8007A630;
extern u8 *func_800280A0();
extern u8 *func_80028050();
extern void func_8005848C();
extern void func_8005844C();
extern u8 *func_8002DD5C();
extern u8 D_8005F824[];

extern void func_8002C530();
extern s32 D_8005F928;
extern u8 D_800644DC[];
extern void func_8002C6B0();
extern u8 D_800192A8[];
extern void func_8002B3D0();
extern s32 D_800641A4;
extern u8 D_800645F8[];
extern s32 func_8001F278();
extern s32 func_8001BCF8();
extern s32 func_8001BCC4();
extern void func_80068D8C();
extern s32 func_8006ABAC();
extern s32 D_80114210;
extern u8 D_800645C0[];
extern void func_8003EC6C();
extern u8 D_800645D4[];
extern void func_80068F30(s32 *arg0, void *arg1);
extern void func_80068DB4(s32 *arg0);
extern void func_8007A54C();
extern u8 D_8007A564[];
extern void func_8002B3D0(void);
extern void func_80069614();
extern s32 func_80069994();
extern u8 D_80064780[];
extern u8 D_8006478C[];
extern void func_800694A4();
extern s32 func_80069AD4();
extern s32 D_8005F81C;
extern void func_8006A680();
extern void func_8006A964();
extern void func_80069DA4();
extern void func_8006A5C0();
extern void func_8006A3F8();
extern void func_8006AA34();
extern void func_80069E70();
extern u8 *func_8006940C();
extern u8 D_800647AC[];
extern s32 func_8006AD8C();
extern u8 D_800647A8[];
extern void func_80068570(void *);
extern void func_800686A0(void *);
extern void func_80068B00(void *);
extern void func_8002B82C(void *);

void func_80068384(char *s1)
{
    char *s0 = s1 + 0x38;
    u32 frame;

    if (*(int *)(s1 + 0x38) != 0) {
        func_80069028(s0);
        func_80069178(s0);
        return;
    }
    if (*(int *)(s1 + 0x10C) == 0) {
        if (*(int *)(s1 + 0x3C) != 0) {
            func_80069364(s0, s1 + 0x24);
        }
        func_80068570(s1);
    }
    func_800686A0(s1);
    func_80068B00(s1);

    frame = ++*(u32 *)(s1 + 0x10C);
    if (frame == 0x1CC) {
        func_8001EAB4(((u8 *)&D_8005F884), 0x14);
    }

    frame = *(u32 *)(s1 + 0x10C);
    if ((s32)frame < 0x1E1) {
        if (func_80068484(s1) == 0) {
            return;
        }
    }
    s0 = ((u8 *)&D_8005F884);
    if (func_8001EB20(s0) == 0) {
        return;
    }
    func_8001EAD4(s0, 0x14);
    func_8002B82C(s1);
}
