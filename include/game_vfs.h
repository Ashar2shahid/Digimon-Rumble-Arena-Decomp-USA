#ifndef GAME_VFS_H
#define GAME_VFS_H

#include "resource_loader.h"
#include "zlib_113.h"
#include "game_sort.h"

/* Notification callbacks receive one target-width word. Depending on the
 * site it is a user pointer, an event code, or an opaque forwarded value. */
typedef void (*VfsNotificationFn)(u32);
typedef s32 (*VfsPathLookupFn)(u8 *output, const char *path);

/* Reviewed 12-byte prefix of an allocated 0x80-byte CD request, not its full size. */
typedef struct VfsReadRequest {
    SortNode link;
    u8 *buffer;
} VfsReadRequest;
typedef char VfsReadRequest_prefix_is_12[(sizeof(VfsReadRequest) == 12) ? 1 : -1];

/* Resident VFS state; retain unreviewed fields as opaque storage. */
typedef struct VfsRuntime {
    volatile u32 flags;                 /* 0x000 */
    VfsReadRequest *current;            /* 0x004 */
    ResourceReadComplete readComplete;  /* 0x008 */
    void *user;                        /* 0x00C */
    VfsNotificationFn completion;      /* 0x010 */
    void *completionUser;              /* 0x014 */
    u8 reserved_018[8];
    VfsNotificationFn notification;    /* 0x020 */
    u8 reserved_024[4];
    VfsPathLookupFn pathLookup;        /* 0x028 */
    SortNode *freeHead;                 /* 0x02C */
    SortInsertList pending;             /* 0x030 */
    u8 reserved_03C[0xA58];
    ZlibAllocFn alloc;                  /* 0xA94 */
    ZlibFreeFn release;                 /* 0xA98 */
    void *opaque;                      /* 0xA9C */
} VfsRuntime;

typedef char VfsRuntime_size_is_0xAA0[(sizeof(VfsRuntime) == 0xAA0) ? 1 : -1];

typedef struct VfsDeviceState {
    volatile u32 flags;                /* 0x000 */
    VfsNotificationFn previousRuntimeNotification; /* 0x004 */
    u8 reserved_008[4];
    u16 previous;                      /* 0x00C */
    u16 reserved_00E;
    volatile u16 volume;               /* 0x010 */
    u16 mode;                          /* 0x012 */
    void *pointer;                     /* 0x014 */
    u32 reserved_018;
    s32 savedMode;                     /* 0x01C */
    VfsNotificationFn event;          /* 0x020 */
} VfsDeviceState;
typedef char VfsDeviceState_size_is_0x24[(sizeof(VfsDeviceState) == 0x24) ? 1 : -1];
typedef char VfsDeviceState_previous_is_0x04[((u32)&((VfsDeviceState *)0)->previousRuntimeNotification == 0x04) ? 1 : -1];
typedef char VfsDeviceState_event_is_0x20[((u32)&((VfsDeviceState *)0)->event == 0x20) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif

extern VfsRuntime D_80114B80;
extern VfsDeviceState D_80116668;

#ifdef __cplusplus
}
#endif

#endif
