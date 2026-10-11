#include "common.h"

extern u32 D_800641B8;





/* Independent shaded packet constructor; cursor addresses are target words. */
u8 *func_8002F8A4(void)
{
    u8 *packet = (u8 *)D_800641B8;
    D_800641B8 = (u32)packet + 0x1CU;
    packet[3] = 6;
    packet[7] = 0x4C;
    *(u32 *)(packet + 0x18) = 0x55555555U;
    return packet;
}

u8 *func_8002F8D8(void)
{
    u8 *packet = (u8 *)D_800641B8;
    D_800641B8 = (u32)packet + 0x1CU;
    packet[3] = 6;
    packet[7] = 0x30;
    return packet;
}

INCLUDE_ASM("asm/us/main/nonmatchings/20000", func_8002F900);

INCLUDE_ASM("asm/us/main/nonmatchings/20000", func_8002FA80);

u8 *func_8002FC00(void)
{
    u8 *packet = (u8 *)D_800641B8;
    D_800641B8 = (u32)packet + 0x14U;
    packet[3] = 4;
    packet[7] = 0x20;
    return packet;
}

u8 *func_8002FC28(void)
{
    u8 *packet = (u8 *)D_800641B8;
    D_800641B8 = (u32)packet + 0x24U;
    packet[3] = 8;
    packet[7] = 0x38;
    return packet;
}

u8 *func_8002FC50(void)
{
    u8 *packet = (u8 *)D_800641B8;
    D_800641B8 = (u32)packet + 0x34U;
    packet[3] = 12;
    packet[7] = 0x3C;
    return packet;
}

INCLUDE_ASM("asm/us/main/nonmatchings/20000", func_8002FC78);

INCLUDE_ASM("asm/us/main/nonmatchings/20000", func_8002FDDC);

INCLUDE_ASM("asm/us/main/nonmatchings/20000", func_8002FF80);
