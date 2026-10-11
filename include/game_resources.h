#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H

#include "common.h"

typedef struct ResourceNode {
    struct ResourceNode *next;
    u8 pad04[4];
    u32 resourceId;
    s32 status;
    u16 entryIndex;
    u8 resourceByte;
    u8 state;
    u32 flags;
    u8 priority;
    u8 byte19;
    u8 byte1A;
    u8 byte1B;
    u8 byte1C;
    u8 argument1;
    u8 argument2;
    u8 tag;
} ResourceNode;

typedef char ResourceNode_size_is_0x20[(sizeof(ResourceNode) == 0x20) ? 1 : -1];

/* One resident object; interior address labels name fields of this state. */
typedef union ResourceEntry {
    u8 bytes[16];
    u16 handleIndex;
} ResourceEntry;

typedef struct ResourcePosition {
    s16 x;
    s16 y;
} ResourcePosition;

typedef struct ResourceSlots {
    s16 handles[24];
    ResourcePosition positions[24];
} ResourceSlots;

typedef struct ResourceState {
    s32 mode;                       /* 0x000 */
    u8 *data;                       /* 0x004 */
    s16 (*handles)[4];              /* 0x008, eight-byte records */
    u8 *table1;                     /* 0x00C, eight-byte records */
    ResourceEntry *entries;         /* 0x010, sixteen-byte records */
    u8 *entries8;                   /* 0x014, eight-byte records */
    u16 count18;                    /* 0x018, role under review */
    u16 count1A;                    /* 0x01A, role under review */
    u16 entryCount;                 /* 0x01C */
    u16 entry8Count;                /* 0x01E */
    u16 currentCapacity;            /* 0x020 */
    u8 pad22[0x44 - 0x22];
    ResourceNode *current;          /* 0x044 */
    s32 currentIndex;               /* 0x048 */
    u8 pad4C[0x490 - 0x4C];
    ResourceSlots slots;            /* 0x490 */
    u8 overrideTag;                 /* 0x520 */
} ResourceState;

typedef char ResourceEntry_size_is_0x10[(sizeof(ResourceEntry) == 0x10) ? 1 : -1];
typedef char ResourceSlots_size_is_0x90[(sizeof(ResourceSlots) == 0x90) ? 1 : -1];
typedef char ResourceState_size_is_0x524[(sizeof(ResourceState) == 0x524) ? 1 : -1];

/* Traditional compile-time offsetof form for the pre-C99 target compiler. */
#define RESOURCE_OFFSET(field) ((u32)&((ResourceState *)0)->field)
#define RESOURCE_OFFSET_CHECK(field, offset) \
    typedef char ResourceState_##field##_offset[(RESOURCE_OFFSET(field) == (offset)) ? 1 : -1]
RESOURCE_OFFSET_CHECK(data, 0x004);
RESOURCE_OFFSET_CHECK(handles, 0x008);
RESOURCE_OFFSET_CHECK(table1, 0x00C);
RESOURCE_OFFSET_CHECK(entries, 0x010);
RESOURCE_OFFSET_CHECK(entries8, 0x014);
RESOURCE_OFFSET_CHECK(entryCount, 0x01C);
RESOURCE_OFFSET_CHECK(entry8Count, 0x01E);
RESOURCE_OFFSET_CHECK(currentCapacity, 0x020);
RESOURCE_OFFSET_CHECK(current, 0x044);
RESOURCE_OFFSET_CHECK(currentIndex, 0x048);
RESOURCE_OFFSET_CHECK(slots, 0x490);
RESOURCE_OFFSET_CHECK(overrideTag, 0x520);
#undef RESOURCE_OFFSET_CHECK
#undef RESOURCE_OFFSET

#ifdef __cplusplus
extern "C" {
#endif

extern ResourceState D_80116690;

void func_80039354(s16 value);
void func_80039414(u16 index);
void func_80039874(u32 value);
s32 func_80039AF4(s32 id);
void func_8001C008(void *owner, s32 index, s32 update);
s32 func_8001C0CC(void *owner, s32 id);
void func_8001BF40(void *owner, s32 index, s32 update);
void func_8001BDDC(void *owner, u32 index, s32 update);
s32 func_80038B24(u16 index);
s32 func_80038B58(u16 index);
s32 func_80038B78(u16 index);
s32 func_80038BE8(void);
s32 func_80038BF8(void);
void func_80039EB0(ResourceNode *node);

#ifdef __cplusplus
}
#endif

#endif
