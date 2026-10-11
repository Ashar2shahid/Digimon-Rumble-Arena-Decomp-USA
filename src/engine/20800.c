#include "common.h"
#include "task_manager.h"

typedef struct AnimatorClipView {
    s32 frameCount;
    u32 *keys;
} AnimatorClipView;

typedef struct TaskHeaderView {
    s32 word0;
    s32 word4;
    const s16 *values8;
    const s16 *valuesC;
    s32 word10;
    AnimatorClipView *clips;
} TaskHeaderView;



INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_800300B0);

INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_80030228);

INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_80030250);

INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_80030278);

INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_80030350);

INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_80030364);

INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_80030388);

INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_800303AC);

INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_800303C0);

s32 func_800303DC(const TaskManager *self) {
    const TaskHeaderView *header = (const TaskHeaderView *)self->header;
    return header->word10;
}

s32 func_800303F0(const TaskManager *self) {
    const TaskHeaderView *header = (const TaskHeaderView *)self->header;
    return header->word4;
}

void func_80030404(u32 **arg0, s32 arg1, u32 arg2) {
    arg0[1][arg1] = arg2;
}

s32 func_80030418(const TaskManager *self, s32 index) {
    const TaskHeaderView *header = (const TaskHeaderView *)self->header;
    return header->values8[index];
}

s32 func_80030438(const TaskManager *self, s32 index) {
    const TaskHeaderView *header = (const TaskHeaderView *)self->header;
    return header->valuesC[index];
}

s32 func_80030458(s32 *arg0) {
    return arg0[3];
}

s32 func_80030464(s32 *arg0) {
    return arg0[5];
}

s32 func_80030470(s32 *arg0) {
    return arg0[2];
}

s32 func_8003047C(u32 *arg0) {
    return arg0[10] & 1;
}

s32 func_80030488(u32 *arg0) {
    return (arg0[10] >> 1) & 1;
}

s32 func_8003049C(const TaskManager *self, s32 clip) {
    const TaskHeaderView *header = (const TaskHeaderView *)self->header;
    const AnimatorClipView *entry = &header->clips[clip];
    return entry->frameCount == 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_800304BC);

extern s32 func_80030584(void *arg0, s32 arg1, s32 count);

void func_8003053C(void *arg0, s32 arg1, s32 count) {
    u32 *object = (u32 *)arg0;
    if ((object[10] & 1) == 0) {
        object[5] = func_80030584(arg0, arg1, count);
    }
}

void func_8003057C(u32 *arg0, u32 arg1) {
    arg0[9] = arg1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/20800", func_80030584);




extern void func_80030A10(s32 *self, s32 index);
extern void func_800308DC(TaskManager *self, s32 index);
extern void func_8003084C(TaskManager *self);

void func_80030760(TaskManager *self) {
    u32 oldFlags = self->flags;
    s32 index;
    self->flags = oldFlags & ~2u;
    if ((oldFlags & 1) != 0) {
        return;
    }

    index = self->cursor;
    if (index < self->end) {
        func_80030A10((s32 *)self, index);
    } else {
        func_800308DC(self, index);
    }
    func_8003084C(self);
    index = (s32)((u32)index + 1U);
    if (index >= self->taskCount) {
        s32 delay = self->delay;
        u32 hasDelay = (u32)delay > 0u;
        if (delay > 0) {
            self->delay = delay - 1;
        }
        if (hasDelay) {
            index = func_80030584(self, self->start, 0);
        } else {
            index = (s32)((u32)self->taskCount - 1U);
            self->flags |= 1;
        }
        self->flags |= 2;
    }
    self->cursor = index;
}

/* Two historical labels fall inside the complete 0xEC-byte body. */
__asm__(".globl func_80030800\n.set func_80030800, func_80030760 + 0xA0\n.size func_80030800, 0x4C");
__asm__(".globl func_80030810\n.set func_80030810, func_80030760 + 0xB0\n.size func_80030810, 0x3C");

