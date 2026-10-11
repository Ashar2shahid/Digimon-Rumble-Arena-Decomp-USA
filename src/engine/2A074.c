#include "common.h"
#include "game_resources.h"


extern ResourceNode *D_801166D0;
extern ResourceNode *D_801166CC;

typedef struct ResourceCommand {
    u32 mask;
    u32 command;
    s16 x;
    s16 y;
    s16 z;
    s16 w;
    u8 pad10[4];
    u16 handle;
    u8 payload[0x2A];
} ResourceCommand;

extern void func_8004802C(ResourceCommand *);

extern u8 D_80116BB0;

void func_80039874(u32 value) {
    D_80116BB0 = value;
}

extern s16 (*D_80116698)[4];
extern s32 func_80052EEC(void *, s32);

s32 func_80039880(s32 id, void *resource) {
    s32 index = id & 0xFFFF;
    /* Target address arithmetic stays defined even when the base is null. */
    s16 *entry = (s16 *)((u32)D_80116698 + (u32)index * sizeof(D_80116698[0]));
    s32 result;

    if (D_80116698 == NULL) {
        return -1;
    }
    result = entry[3];
    if (result >= 0) {
        return result;
    }
    result = func_80052EEC(resource, -1);
    if (result >= 0) {
        entry[3] = result;
    }
    return result;
}

extern void func_80048BCC(ResourceCommand *);
extern u32 func_80039AB0(void);
extern void func_800399EC(s32);

INCLUDE_ASM("asm/us/main/nonmatchings/2A074", func_800398DC);

extern u8 D_80116B20[];

INCLUDE_ASM("asm/us/main/nonmatchings/2A074", func_800399EC);

u32 func_80039AB0(void) {
    ResourceNode *node = D_801166D0;
    ResourceNode *next;
    u32 flags = 0;

    while (node != NULL) {
        next = node->next;
        if (node->state != 0) {
            flags |= node->flags;
        }
        node = next;
    }
    return flags;
}

extern s32 func_80039CF8(s32, u8, u8);

s32 func_80039AF4(s32 id) {
    ResourceEntry *entry;

    id &= 0xFFFF;
    if ((u32)id >= D_80116690.entryCount) {
        return -1;
    }
    if (D_80116690.entries == NULL) {
        return -1;
    }
    entry = &D_80116690.entries[id];
    return func_80039CF8(id, entry->bytes[8], entry->bytes[9]);
}

extern u32 func_8003A114(ResourceNode *);

INCLUDE_ASM("asm/us/main/nonmatchings/2A074", func_80039B58);

INCLUDE_ASM("asm/us/main/nonmatchings/2A074", func_80039CF8);

extern void *func_8003A164(s32);
extern void func_80038848(void *, ResourceNode *);

void func_80039E14(ResourceNode *node) {
    ResourceNode **head = &D_801166CC;

    func_8003A164(node->resourceId);
    func_80038848(head + 1, node);
    node->next = *head;
    *head = node;
}

extern void func_80047D0C(s32, u32);

void func_80039E64(ResourceNode *node) {
    ResourceCommand command;

    func_80047D0C(0, node->flags);
    command.mask = node->flags;
    command.command = 3;
    command.x = 0;
    command.y = 0;
    func_8004802C(&command);
}

extern void func_800399EC(s32);
extern void func_80039E64(ResourceNode *);
extern void func_80039E14(ResourceNode *);

void func_80039EB0(ResourceNode *node) {
    func_800399EC(node->flags);
    if (node->state & 0x80) {
        func_80039E64(node);
    }
    func_80039E14(node);
}

extern void func_80039FB0(s32);

s32 func_80039F00(s32 id) {
    s32 index = id & 0xFFFF;
    ResourceState *state = &D_80116690;
    ResourceEntry *entry;
    ResourceNode *node;
    ResourceNode *next;
    u8 tag;

    entry = &state->entries[index];
    if (state->overrideTag != 0) {
        tag = state->overrideTag;
    } else {
        tag = entry->bytes[10];
    }
    func_80039FB0(tag);
    if (entry->bytes[2] & 1) {
        return 1;
    }
    node = D_801166D0;
    while (node != NULL) {
        next = node->next;
        if (node->entryIndex == index && node->state == 0) {
            return 0;
        }
        node = next;
    }
    return 1;
}

void func_80039FB0(s32 tag) {
    ResourceNode *node;
    ResourceNode *next;

    if (tag == 0) {
        return;
    }
    node = D_801166D0;
    if (node == NULL) {
        return;
    }
    do {
        next = node->next;
        if (node->tag == tag) {
            func_80039E64(node);
        }
        node = next;
    } while (node != NULL);
}

/* The old sector boundary names this routine's shared return sequence. */
__asm__(".globl func_8003A000\n.set func_8003A000, func_80039FB0 + 0x50\n.size func_8003A000, 0x14");
