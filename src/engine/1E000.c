#include "game_sprite_cleanup.h"
#include "common.h"

typedef struct {
    u8 reserved[8];
    u32 buffer;
} PacketOwner;

typedef struct PacketRect {
    s16 x, y, width, height;
} PacketRect;

extern void func_8002B3F8(void *buffer);
void func_8002D830(void *sprite) {
    PacketOwner *owner = sprite;
    u32 buffer = owner->buffer;
    if (buffer != 0) {
        func_8002B3F8((void *)buffer);
    }
    owner->buffer = 0;
}

extern void func_8002B3D0(void *);
void func_8002D86C(void *owner, u32 destroyFlags) {
    func_8002D830(owner);
    if (destroyFlags & 1) {
        func_8002B3D0(owner);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1E000", func_8002D8B0);

s32 func_8002DB54(const PacketRect *rect, s32 xShift, s32 yShift) {
    s32 xSize = 1 << xShift;
    s32 ySize = 1 << yShift;
    s32 x = rect->x;
    s32 xMask = -xSize;
    s32 columns = ((xMask & (x + rect->width + xSize - 1)) -
                   (xMask & x)) >> xShift;
    s32 y = rect->y;
    s32 yMask = -ySize;
    s32 rows = ((yMask & (y + rect->height + ySize - 1)) -
                (yMask & y)) >> yShift;
    return (s32)((u32)columns * (u32)rows);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1E000", func_8002DBC0);

void func_8002DCC8(u8 *packet, u32 flags) {
    packet[0x11] = (packet[0x11] & 0xFC) | 8 | flags;
}

void func_8002DCE4(u8 *packet) {
    *(u32 *)(packet + 0xC) = 0x808080;
}

void func_8002DCF4(u8 *packet, u32 red, u32 green, u32 blue) {
    u32 packedRed = red & 0xFF;
    u32 packedGreen = green & 0xFF;
    u32 packedBlue = blue & 0xFF;
    packedGreen <<= 8;
    packedRed |= packedGreen;
    packedBlue <<= 16;
    *(u32 *)(packet + 0xC) = packedRed | packedBlue;
}

void func_8002DD18(u8 *packet, u32 shade) {
    u32 component = shade & 0xFF;
    *(u32 *)(packet + 0xC) = component | (component << 8) | (component << 16);
}

void func_8002DD34(u8 *packet, u32 flags) {
    packet[0x11] |= flags;
}

void func_8002DD48(u8 *packet, u32 flags) {
    packet[0x11] &= ~flags;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1E000", func_8002DD5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1E000", func_8002DD84);

INCLUDE_ASM("asm/us/main/nonmatchings/1E000", func_8002DDC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1E000", func_8002DDEC);
