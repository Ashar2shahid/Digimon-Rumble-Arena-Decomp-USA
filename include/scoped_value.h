#ifndef SCOPED_VALUE_H
#define SCOPED_VALUE_H

#include "common.h"

typedef struct {
    u8 reserved[0x30];
    s32 value;
} ScopedValueObject;

typedef struct {
    ScopedValueObject *object;
    s32 previous;
} ScopedValueBackup;

typedef char ScopedValueBackup_size_is_8[(sizeof(ScopedValueBackup) == 8) ? 1 : -1];
typedef char ScopedValueObject_size_is_0x34[(sizeof(ScopedValueObject) == 0x34) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
ScopedValueBackup *func_80021B74(ScopedValueBackup *, ScopedValueObject *, s32);
void func_80021BB4(ScopedValueBackup *, u32);
#ifdef __cplusplus
}
#endif

#endif
