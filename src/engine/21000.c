#include "game_heap_wrappers.h"
#include "common.h"
#include "task_manager.h"
#include "resource_loader.h"






void func_8003084C(TaskManager *self) {
    s32 count = self->header[1];
    s32 i;
    for (i = 0; i < count; i++) {
        TaskObject *task = self->tasks[i];
        if (task != 0) {
            TaskDispatch *dispatch = task->dispatch;
            void *adjusted = (void *)((u32)task + (u32)(s32)dispatch->thisOffset);
            dispatch->update(adjusted, task);
        }
    }
}

/* Original symbol is an internal fall-through position in func_8003084C. */
__asm__(".globl func_80030888\n.set func_80030888, func_8003084C + 0x3C\n.size func_80030888, 0x54");

INCLUDE_ASM("asm/us/main/nonmatchings/21000", func_800308DC);





void func_80030AC8(void *arg0, s32 arg1);
void func_80030BB0(void *arg0, void *arg1, void *arg2, s32 arg3);
extern void func_80030B2C(void *arg0, void *arg1, void *arg2, s32 arg3);

void func_80030A10(s32 *a0, s32 a1) {
    s32 s0 = a1 - (a0[6] - a0[7]);
    s32 s3 = ((s0 + 1) << 12) / (a0[7] + 1);
    s32 *p = (s32 *)a0[0];
    s32 s1 = p[1];

    for (s0 = 0; s0 < s1; s0++) {
        s32 v = ((s32 *)a0[1])[s0];

        if (v != 0) {
            func_80030AC8(v, s3);
        }
    }
}

void func_80030AC8(void *arg0, s32 arg1) {
    func_80030BB0(arg0, (u8 *)arg0 + 0x14, (u8 *)arg0 + 0x28, arg1);
    func_80030B2C((u8 *)arg0 + 8, (u8 *)arg0 + 0x1C, (u8 *)arg0 + 0x30, arg1);
    func_80030B2C((u8 *)arg0 + 0xE, (u8 *)arg0 + 0x22, (u8 *)arg0 + 0x36, arg1);
}

INCLUDE_ASM("asm/us/main/nonmatchings/21000", func_80030B2C);

extern void func_80025784(void);

void func_80030BB0(void *arg0, void *arg1, void *arg2, s32 arg3) {
    func_80025784();
}

u32 *func_80030BD0(u32 *arg0, u32 arg1) {
    arg0[0] = arg1 != 0;
    arg0[1] = arg1;
    return arg0;
}

extern void func_8002B3D0(s32 arg0);

void func_80030BE4(s32 *arg0, s32 arg1) {
    if (arg0[0] != 0) {
        func_8002B2B4((void *)(u32)arg0[1]);
    }
    if (arg1 & 1) {
        func_8002B3D0((s32)arg0);
    }
}

u32 *func_80030C3C(u32 *arg0, u32 *arg1) {
    arg0[0] = 0;
    arg0[1] = arg1[1];
    return arg0;
}

u32 *func_80030C50(u32 *arg0, u32 arg1) {
    arg0[0] = 1;
    arg0[1] = arg1;
    return arg0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/21000", func_80030C64);

typedef struct Func80030CF8Link {
    struct Func80030CF8Link *next;
    struct Func80030CF8Link *prev;
} Func80030CF8Link;

typedef struct Func80030CF8Object {
    Func80030CF8Link link;
    u32 unk8;
    Func80030CF8Link listC;
    Func80030CF8Link list14;
    Func80030CF8Link list1C;
    s32 object24;
} Func80030CF8Object;

void func_80030CF8(Func80030CF8Object *arg0, s32 arg1) {
    func_8002B2B4((void *)(u32)arg0->object24);
    func_80030BE4((s32 *)&arg0->list1C, 2);
    func_80030BE4((s32 *)&arg0->list14, 2);
    func_80030BE4((s32 *)&arg0->listC, 2);
    arg0->link.next->prev = arg0->link.prev;
    arg0->link.prev->next = arg0->link.next;
    arg0->link.next = &arg0->link;
    arg0->link.prev = &arg0->link;
    if (arg1 & 1) {
        func_8002B3D0((s32)arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/21000", func_80030D84);

INCLUDE_ASM("asm/us/main/nonmatchings/21000", func_80030DB0);

INCLUDE_ASM("asm/us/main/nonmatchings/21000", func_80030DF8);

extern char D_8001935C[];
extern void func_8003EC6C(char *buffer, char *format, ...);

void func_80030F0C(s32 *arg0, s32 arg1) {
    char buffer[0x20];
    func_8003EC6C(buffer, D_8001935C, arg0[2], arg1);
    func_80027C14(buffer);
}

void func_80030F48(s32 *arg0, s32 arg1) {
    char buffer[0x20];
    func_8003EC6C(buffer, D_8001935C, arg0[2], arg1);
    func_80027C6C(buffer);
}

INCLUDE_ASM("asm/us/main/nonmatchings/21000", func_80030F84);


