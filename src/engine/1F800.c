#include "common.h"


void func_8002F038(void) {
}

void func_8002F040(void) {
}

void func_8002F048(void) {
}

INCLUDE_ASM("asm/us/main/nonmatchings/1F800", func_8002F050);

void func_8002F140(int *a0, int *a1) {
    int x, y, z;
    a0[20] = 1;
    x = a1[0];
    y = a1[1];
    z = a1[2];
    a0[0] = x;
    a0[1] = y;
    a0[2] = z;
}

void func_8002F164(int *a0, int *a1) {
    int x, y, z;
    a0[20] = 1;
    x = a1[0];
    y = a1[1];
    z = a1[2];
    a0[4] = x;
    a0[5] = y;
    a0[6] = z;
}

void func_8002F188(int *a0, int *a1) {
    int x, y, z;
    a0[20] = 1;
    x = a1[0];
    y = a1[1];
    z = a1[2];
    a0[8] = x;
    a0[9] = y;
    a0[10] = z;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1F800", func_8002F1AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1F800", func_8002F304);

INCLUDE_ASM("asm/us/main/nonmatchings/1F800", func_8002F478);

/* Callers supply RGB components in0..255 and a halfword-aligned four-byte output. */
void func_8002F5B4(u8 *out, s32 red, s32 green, s32 blue) {
    s32 maximum = blue;
    s32 sector = 0;
    s32 minimum;
    s32 saturation;
    s32 hue;

    if (blue < red) {
        maximum = red;
        sector = 1;
    }
    if (maximum < green) {
        maximum = green;
        sector = 2;
    }
    minimum = blue;
    out[3] = maximum;
    if (red < minimum) {
        minimum = red;
    }
    if (green < minimum) {
        minimum = green;
    }
    minimum = maximum - minimum;
    saturation = 0;
    if (maximum != 0) {
        saturation = (minimum * 255) / maximum;
    }
    out[2] = saturation;
    if (saturation == 0) {
        *(s16 *)out = -1;
        return;
    }
    switch (sector) {
    case 0:
    default:
        hue = ((red - green) * 256) / minimum + 0x400;
        break;
    case 1:
        hue = ((green - blue) * 256) / minimum;
        break;
    case 2:
        hue = ((blue - red) * 256) / minimum + 0x200;
        break;
    }
    if (hue < 0) {
        hue += 0x600;
    }
    *(s16 *)out = hue;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1F800", func_8002F6D0);
