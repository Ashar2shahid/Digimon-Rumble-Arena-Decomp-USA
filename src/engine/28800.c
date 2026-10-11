#include "common.h"
#include "game_sort.h"
#include "game_md5.h"

/* Game-side crypto/memory helpers.  The MD5 block (transform at 0x8003D228,
 * wrappers here) is byte-exact under the psyq 4.6 (2.95.2) cc1 for the loop
 * helpers; see UNIT_CC1_EXE["main/2E830.c"]. */

INCLUDE_ASM("asm/us/main/nonmatchings/28800", func_80038000);







Md5Context *func_800383B4(Md5Context *ctx) {
    func_800383DC(ctx);
    return ctx;
}

/* MD5Init: initialize the four state words and zero the bit counter. */
void func_800383DC(Md5Context *ctx) {
    ctx->count[1] = 0;
    ctx->count[0] = 0;
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xefcdab89;
    ctx->state[2] = 0x98badcfe;
    ctx->state[3] = 0x10325476;
}

void func_80038418(Md5Context *ctx, u8 *input, u32 length) {
    u32 i;
    u32 index;
    u32 partLength;
    index = (ctx->count[0] >> 3) & 0x3F;
    if ((ctx->count[0] += length << 3) < (length << 3)) {
        ctx->count[1]++;
    }
    ctx->count[1] += length >> 29;
    partLength = 64 - index;
    if (length >= partLength) {
        func_800385B8(&ctx->buffer[index], input, partLength);
        func_80037458(ctx->state, ctx->buffer);
        for (i = partLength; i + 63 < length; i += 64) {
            func_80037458(ctx->state, &input[i]);
        }
        index = 0;
    } else {
        i = 0;
    }
    func_800385B8(&ctx->buffer[index], &input[i], length - i);
}

void func_80038510(u8 *output, const u32 *input, u32 length) {
    u32 i;
    for (i = 0; i < length; i += 4) {
        output[0] = (u8)input[0];
        output[1] = (u8)(input[0] >> 8);
        output[2] = (u8)(input[0] >> 16);
        output[3] = (u8)(input[0] >> 24);
        output += 4;
        input++;
    }
}

void func_80038560(u32 *output, const u8 *input, u32 length) {
    if (length != 0) {
        u32 i = 0;
        const u8 *src = input;
        u32 *dst = output;
        do {
            *dst = (u32)src[0] | ((u32)src[1] << 8) |
                   ((u32)src[2] << 16) | ((u32)src[3] << 24);
            dst++;
            src += 4;
            i += 4;
        } while (i < length);
    }
}

/* Byte copy loop (src -> dst). */
void func_800385B8(u8 *d, u8 *s, u32 n) {
    u32 i = 0;
    if (n != 0) {
        do {
            d[i] = s[i];
            i++;
        } while (i < n);
    }
}

/* Byte fill loop. */
void func_800385E8(u8 *d, s32 c, u32 n) {
    u32 i = 0;
    if (n != 0) {
        do {
            d[i] = c;
            i++;
        } while (i < n);
    }
}

SortNode *func_80038610(SortNode *head, SortCompare compare) {
    return func_80038690(compare, head);
}

void func_80038638(SortList *list, SortCompare compare) {
    SortNode *node = func_80038690(compare, list->head);
    SortNode *previous = 0;
    list->head = node;
    while (node != 0) {
        node->word4.previous = previous;
        previous = node;
        node = node->next;
    }
    list->tail = previous;
}

SortNode *func_80038690(SortCompare compare, SortNode *nodes) {
    SortNode *middle;
    SortNode *second;
    if (nodes == 0) return 0;
    if (nodes->next == 0) return nodes;
    middle = nodes;
    second = nodes->next->next;
    while (second != 0) {
        second = second->next;
        middle = middle->next;
        if (second != 0) second = second->next;
    }
    second = middle->next;
    middle->next = 0;
    return func_8003873C(compare, func_80038690(compare, nodes), func_80038690(compare, second));
}

SortNode *func_8003873C(SortCompare compare, SortNode *left, SortNode *right) {
    SortNode head;
    SortNode *tail = &head;
    while (left != 0 && right != 0) {
        if (compare(left, right) <= 0) {
            tail->next = left;
            tail = left;
            left = left->next;
        } else {
            tail->next = right;
            tail = right;
            right = right->next;
        }
    }
    if (left == 0) tail->next = right;
    else tail->next = left;
    return head.next;
}

void func_800387E0(SortInsertList *list, SortNode *anchor, SortNode *node) {
    list->count++;
    if (list->head == 0) {
        node->next = 0;
        node->word4.previous = 0;
        list->head = node;
        list->tail = node;
    } else {
        node->next = anchor;
        node->word4.previous = anchor->word4.previous;
        if (anchor->word4.previous == 0) {
            list->head = node;
        } else {
            anchor->word4.previous->next = node;
        }
        anchor->word4.previous = node;
    }
}

__asm__(".globl func_80038800\n.set func_80038800, func_800387E0 + 0x20\n.size func_80038800, 0x48");
__asm__(".globl func_80038814\n.set func_80038814, func_800387E0 + 0x34\n.size func_80038814, 0x34");
