#include "mesh_scene_visibility.h"
#include "common.h"
#include "game_lists.h"
#include "game_font_cache.h"

typedef struct TaskLink TaskLink;
struct TaskLink {
    TaskLink *next;
    TaskLink *previous;
};

typedef struct TaskResource {
    u32 header[2];
    void *sourceEntries[32];
    u8 *taskEntries[32];
    s16 *metadata;
} TaskResource;
typedef char TaskResource_metadata_is_0x108[((u32)&((TaskResource *)0)->metadata == 0x108) ? 1 : -1];
typedef struct TaskStateRecord {
    TaskLink links;
    void *payload;
    void *slot0C;
    void *slot10;
    u32 enabled;
} TaskStateRecord;
typedef char TaskStateRecord_size_is_24[(sizeof(TaskStateRecord) == 24) ? 1 : -1];



extern void func_80031E04(s32 active, s32 index);
extern void func_8001FD40(ListRoot *root);


INCLUDE_ASM("asm/us/main/nonmatchings/22000", func_80031B4C);

INCLUDE_ASM("asm/us/main/nonmatchings/22000", func_80031BB8);

void *func_80031C20(u8 *manager, u32 index) {
    void **entries = (void **)(manager + 8);
    return entries[index];
}
u8 *func_80031C34(u8 *manager, u32 index) {
    u8 **entries = (u8 **)(manager + 8);
    return entries[index] + 0x2C;
}
INCLUDE_ASM("asm/us/main/nonmatchings/22000", func_80031C48);
extern void func_80076B00(u8 *link);

void func_80031D0C(u8 *manager, s32 index) {
    u32 flagOffset = (u32)index * 2u;
    u32 recordOffset = (flagOffset + (u32)index) * 8u;
    TaskLink *link;
    s32 alone;
    s16 *metadata;
    s16 *flags;
    ((TaskStateRecord *)(recordOffset + (u32)*(u8 **)(manager + 0xA8)))->enabled = 0;
    link = &((TaskStateRecord *)(recordOffset + (u32)*(u8 **)(manager + 0xA8)))->links;
    alone = link->next == link && link == link->previous;
    if (!alone) {
        func_80076B00((u8 *)link);
    }
    metadata = (*(TaskResource **)manager)->metadata;
    flags = metadata + 1;
    flags = (s16 *)((u32)flags + (u32)(s32)*metadata * 6u);
    *(s16 *)(flagOffset + (u32)flags) = 1;
}
void func_80031DB4(u8 *manager, u32 index) {
    s16 *metadata;
    s16 *flags;
    (*(TaskStateRecord **)(manager + 0xA8))[index].enabled = 1;
    metadata = (*(TaskResource **)manager)->metadata;
    flags = metadata + 1;
    flags = (s16 *)((u32)flags + (u32)(s32)*metadata * 6u);
    flags[index] = 0;
}
INCLUDE_ASM("asm/us/main/nonmatchings/22000", func_80031E04);

typedef struct TaskObjectView {
    void *next;
    void *previous;
    void *slot_08;
    void *slot_0C;
    void *slot_10;
    u32 enabled;
} TaskObjectView;
typedef char TaskObjectView_size_is_0x18[(sizeof(TaskObjectView) == 0x18) ? 1 : -1];

u32 func_80031E5C(TaskObjectView *object) {
    return object->enabled ^ 1u;
}

void *func_80031E68(TaskObjectView *object) {
    return object->slot_08;
}

void *func_80031E74(TaskObjectView *object) {
    return object->slot_0C;
}

void *func_80031E80(TaskObjectView *object) {
    return object->slot_10;
}

void func_80031E8C(u8 *object, s32 arg) {
    func_8001FE8C((Entry *)(object + 0xAC), arg);
}
void func_80031EAC(u8 *object, s32 arg) {
    func_8001FE8C((Entry *)(object + 0xAC), arg);
}
void func_80031ECC(u8 *object) {
    func_8001FD40((ListRoot *)(object + 0xAC));
}
void *func_80031EEC(u8 *manager) {
    return *(void **)(manager + 0xA8);
}
ListRoot *func_80031EF8(u8 *object, Entry *entry) {
    return func_8001FD10((ListRoot *)(object + 0xAC), entry);
}
/* Retained physical ABI: incoming a0 is unused; node arrives in a1. */
void func_80031F18(void *owner, TaskLink *node) {
    node->next->previous = node->previous;
    node->previous->next = node->next;
    node->next = node;
    node->previous = node;
}

u32 func_80031F44(u8 *base, u32 index) {
    return *(u32 *)(base + (index << 2) + 8);
}

void func_80031F58(void) {
    func_80031E04(1, 0xFFFF);
}

void func_80031F7C(void) {
    func_80031E04(0, 0xFFFF);
}
extern u8 *func_8002B364(u32 size);
/* Actual resident initialized pointer word at gp+0x244. Parent data split
 * must replace precisely 8006436C..8006436F, preserving adjacent bytes. */
FontCache *D_8006436C = NULL;

FontCache *func_80031FA0(void) {
    if (D_8006436C == NULL) {
        D_8006436C = func_80031FD8((FontCache *)func_8002B364(0x1C));
    }
    return D_8006436C;
}
INCLUDE_ASM("asm/us/main/nonmatchings/22000", func_80031FD8);







