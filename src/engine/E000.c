#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/E000", func_8001D800);
s16 func_8001D874(s16 *self, s32 index) {
    self += index;
    return self[0x388 / 2];
}
INCLUDE_ASM("asm/us/main/nonmatchings/E000", func_8001D888);
s32 func_8001D97C(s16 *self, s32 index) {
    s32 value;
    self += index;
    value = self[0x384 / 2];
    if (value == 0) {
        value = 0x12;
    }
    return value;
}
INCLUDE_ASM("asm/us/main/nonmatchings/E000", func_8001D9A0);
s32 func_8001DA64(s32 *left, s32 *right) {
    return left[0xC / 4] - right[0xC / 4];
}
INCLUDE_ASM("asm/us/main/nonmatchings/E000", func_8001DA74);
