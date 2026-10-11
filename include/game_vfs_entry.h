#ifndef GAME_VFS_ENTRY_H
#define GAME_VFS_ENTRY_H
#include "common.h"

/* Runtime table: mounted directories replace the on-disc offset by a pointer. */
typedef struct VfsEntry {
    union {
        struct VfsEntry *entries;
        u32 sector;
    } at;
    union {
        s32 children;
        u32 fileBytes;
    } amount;
    u16 nameOffset;
    u16 flags;
} VfsEntry;
typedef char VfsEntry_size_is_12[(sizeof(VfsEntry) == 12) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
VfsEntry *func_80033A20(VfsEntry *directory, const u8 *names,
                      const u8 *name, u32 length);
s32 func_80033B0C(const u8 *left, const u8 *right, u32 count);
#ifdef __cplusplus
}
#endif
#endif
