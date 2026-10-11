#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "common.h"

typedef struct TaskDispatch {
    u8 reserved[8];
    s16 thisOffset;
    u16 reservedA;
    void (*update)(void *adjustedObject, void *pose);
} TaskDispatch;

typedef struct TaskObject {
    u8 reserved[0x3C];
    TaskDispatch *dispatch;
} TaskObject;

typedef struct TaskManager {
    s32 *header;
    TaskObject **tasks;
    u32 reserved8;
    s32 taskCount;
    void *data;
    s32 cursor;
    s32 end;
    u32 reserved1C;
    s32 delay;
    s32 start;
    u32 flags;
} TaskManager;

typedef char TaskDispatch_size_is_0x10[(sizeof(TaskDispatch) == 0x10) ? 1 : -1];
typedef char TaskObject_size_is_0x40[(sizeof(TaskObject) == 0x40) ? 1 : -1];
typedef char TaskManager_size_is_0x2C[(sizeof(TaskManager) == 0x2C) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
s32 func_8003049C(const TaskManager *self, s32 clip);
void func_8003084C(TaskManager *self);
void func_800308DC(TaskManager *self, s32 index);
#ifdef __cplusplus
}
#endif

#endif
