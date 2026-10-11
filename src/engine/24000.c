#include "common.h"
#include "game_vfs_entry.h"

INCLUDE_ASM("asm/us/main/nonmatchings/24000", func_80033800);

INCLUDE_ASM("asm/us/main/nonmatchings/24000", func_800338F4);

VfsEntry *func_80033A20(VfsEntry *directory, const u8 *names,
                      const u8 *name, u32 length) {
    s32 low = 0;
    s32 high = directory->amount.children - 1;
    s32 middle;
    s32 order;
    directory = directory->at.entries;
    middle = (low + high) / 2;
    while ((order = func_80033B0C(names + directory[middle].nameOffset,
                                name, length)) != 0) {
        if (low == high) {
            return NULL;
        }
        if (order > 0) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
        if (high < low) {
            return NULL;
        }
        middle = (low + high) / 2;
    }
    return &directory[middle];
}

s32 func_80033B0C(const u8 *left, const u8 *right, u32 count) {
    u32 remaining = count - 1u;
    if (count != 0) {
        do {
            u8 right_byte = *right++;
            u8 left_byte = *left++;
            s32 difference = (s32)left_byte - (s32)right_byte;
            if (difference != 0) {
                return difference;
            }
            remaining--;
        } while (remaining != 0xFFFFFFFFu);
    }
    return *left;
}

INCLUDE_ASM("asm/us/main/nonmatchings/24000", func_80033B4C);

INCLUDE_ASM("asm/us/main/nonmatchings/24000", func_80033CA0);

INCLUDE_ASM("asm/us/main/nonmatchings/24000", func_80033E20);

INCLUDE_ASM("asm/us/main/nonmatchings/24000", func_80033F2C);
