#include "common.h"

#define IS_SJIS_LEAD(c) ((u8)(((c) ^ 0x20) - 0xA1) < 0x3C)
#define CTYPE_SEPARATOR 8
extern const u8 D_8001968C[256];
extern void func_80036144(char *out, const char *input, u8 delimiter);

s32 func_80036064(u8 *path) {
    s32 length = 0;
    u8 c;

    while (*path != '\0') {
        c = *path++;
        if (D_8001968C[c] & CTYPE_SEPARATOR) {
            break;
        }
        if (IS_SJIS_LEAD(c)) {
            path++;
            length++;
        }
        length++;
    }
    return length;
}



char *func_800360EC(char *out, const char *input) {
    func_80036144(out, input, 0x5C);
    return out;
}

char *func_80036118(char *out, const char *input) {
    func_80036144(out, input, 0x2F);
    return out;
}

void func_80036144(char *dst, const char *src, u8 separator) {
    u8 c;

    while (*src != '\0') {
        c = *src++;
        if (IS_SJIS_LEAD(c)) {
            *dst++ = c;
            *dst = *src++;
        } else if (D_8001968C[c] & CTYPE_SEPARATOR) {
            *dst++ = separator;
            for (;;) {
                c = *src;
                if (c != '\0' && (D_8001968C[c] & CTYPE_SEPARATOR)) {
                    src++;
                } else {
                    break;
                }
            }
            continue;
        } else {
            *dst = c;
        }
        dst++;
    }
    *dst = '\0';
}



INCLUDE_ASM("asm/us/main/nonmatchings/26800", func_80036204);

INCLUDE_ASM("asm/us/main/nonmatchings/26800", func_80036518);

INCLUDE_ASM("asm/us/main/nonmatchings/26800", func_80036738);

