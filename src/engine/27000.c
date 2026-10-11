#include "common.h"
#include "game_handles.h"

typedef struct {
    u8 *begin;
    u8 *cursor;
    u32 flags;
    s32 width;
    u32 unknown10;
    u32 unknown14;
    s32 conversion;
    u32 unknown1C;
} TextFormatContext;

extern s32 func_80036204(TextFormatContext *, void *, const char *, void *);
extern void func_80036738(TextFormatContext *, u8 *, s32);
extern void func_8002B3F8(void *);
extern void func_8002B3D0(void *);
extern u32 func_8003E1AC(const u8 *);
extern u8 D_8001978C[];
extern u8 D_800197A0[];


s32 func_800368EC(void *out, const char *format, void *arguments) {
    TextFormatContext context;
    return func_80036204(&context, out, format, arguments);
}

void func_80036920(TextFormatContext *context, u32 character) {
    *context->cursor++ = character;
}

void func_80036938(TextFormatContext *context, const u8 *text) {
    u8 *cursor = context->cursor;
    s32 padding = 0;
    if (context->width > 0) {
        padding = (s32)((u32)context->width - func_8003E1AC(text));
    }
    if (context->flags & 2) {
        while (*text != 0) {
            *cursor++ = *text++;
        }
        while (padding > 0) {
            *cursor++ = ' ';
            padding--;
        }
    } else {
        while (padding > 0) {
            *cursor++ = ' ';
            padding--;
        }
        while (*text != 0) {
            *cursor++ = *text++;
        }
    }
    context->cursor = cursor;
}

void func_80036A34(TextFormatContext *context, u32 value) {
    u8 *cursor = context->cursor;
    u8 a = D_8001978C[value >> 28];
    u8 b = D_8001978C[(value >> 24) & 15];
    u8 c = D_8001978C[(value >> 20) & 15];
    u8 d = D_8001978C[(value >> 16) & 15];
    u8 e = D_8001978C[(value >> 12) & 15];
    u8 f = D_8001978C[(value >> 8) & 15];
    u8 g = D_8001978C[(value >> 4) & 15];
    u8 h = D_8001978C[value & 15];
    context->cursor = cursor + 8;
    cursor[0] = a;
    cursor[1] = b;
    cursor[2] = c;
    cursor[3] = d;
    cursor[4] = e;
    cursor[5] = f;
    cursor[6] = g;
    cursor[7] = h;
}

INCLUDE_ASM("asm/us/main/nonmatchings/27000", func_80036AE4);

void func_80036B70(TextFormatContext *context, u32 value) {
    u8 *cursor = context->cursor;
    do {
        *cursor++ = D_8001978C[value & 7];
        value >>= 3;
    } while (value != 0);
    func_80036738(context, cursor, 0);
}

void func_80036BBC(TextFormatContext *context, u32 value) {
    u8 *cursor = context->cursor;
    u8 *digits;
    switch (context->conversion) {
    case 'X':
    default:
        digits = D_8001978C;
        break;
    case 'x':
        digits = D_800197A0;
        break;
    }
    do {
        *cursor++ = digits[value & 15];
        value >>= 4;
    } while (value != 0);
    func_80036738(context, cursor, 0);
}

void func_80036C28(TextFormatContext *context, u8 *end) {
    u8 *begin = context->cursor;
    while (begin < end) {
        u8 last = *--end;
        u8 first = *begin;
        *begin++ = last;
        *end = first;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/27000", func_80036C64);

void func_80036D88(HandlePool *pool, u32 flags) {
    if (pool->records != NULL) {
        func_8002B3F8(pool->records);
    }
    if (flags & 1) {
        func_8002B3D0(pool);
    }
}

u32 func_80036DDC(HandlePool *pool, void *value) {
    HandleNode *node = pool->records->next;
    if (node == pool->records) {
        return 0;
    }
    node->next->previous = node->previous;
    node->previous->next = node->next;
    node->next = pool->active->next;
    node->previous = pool->active;
    pool->active->next->previous = node;
    pool->active->next = node;
    node->value = value;
    node->id.fields.generation++;
    return node->id.value;
}

void *func_80036E88(HandlePool *pool, u32 handle) {
    HandleNode *node;
    void *value;
    if (handle == 0 || (handle & 0xFFF) >= pool->capacity) {
        return NULL;
    }
    node = &pool->records[handle & 0xFFF];
    if (node->id.value != handle) {
        return NULL;
    }
    value = node->value;
    node->value = NULL;
    node->next->previous = node->previous;
    node->previous->next = node->next;
    node->next = pool->records;
    node->previous = pool->records->previous;
    pool->records->previous->next = node;
    pool->records->previous = node;
    return value;
}

void *func_80036F34(HandlePool *pool, u32 handle) {
    HandleNode *node;
    if (handle == 0 || (handle & 0xFFF) >= pool->capacity) {
        return NULL;
    }
    node = &pool->records[handle & 0xFFF];
    if (node->id.value != handle) {
        return NULL;
    }
    return node->value;
}

u32 func_80036F88(HandlePool *pool, HandleNode *head) {
    HandleNode *node = head->next;
    u32 count = 0;
    while (node != head) {
        node = node->next;
        count++;
    }
    return count;
}

u32 func_80036FB0(HandlePool *pool) {
    HandleNode *head = pool->active;
    HandleNode *node = head->next;
    u32 count = 0;
    while (node != head) {
        node = node->next;
        count++;
    }
    return count;
}

u32 func_80036FE0(HandlePool *pool) {
    HandleNode *head = pool->records;
    HandleNode *node = head->next;
    u32 count = 0;
    while (node != head) {
        node = node->next;
        count++;
    }
    return count;
}

/* Preserve the historical sector-tail symbol without emitting instructions. */
__asm__(".globl func_80037000\n.set func_80037000, func_80036FE0 + 0x20\n.size func_80037000, 0x10");
