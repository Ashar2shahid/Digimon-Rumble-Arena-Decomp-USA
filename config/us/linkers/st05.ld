SECTIONS
{
    HIDDEN(__romPos = 0);
    st05_ROM_START = __romPos;
    st05_VRAM = ADDR(.st05);
    .st05 0x800D3B00 : AT(st05_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        st05_RODATA_START = .;
        build/us/asm/us/st05/data/0.rodata.s.o(.rodata);
        build/us/src/battle/stages/st05/4CC.c.o(.rodata);
        build/us/src/battle/stages/st05/2A5C.c.o(.rodata);
        build/us/src/battle/stages/st05/2D64.c.o(.rodata);
        . = ALIGN(., 4);
        st05_RODATA_END = .;
        st05_RODATA_SIZE = ABSOLUTE(st05_RODATA_END - st05_RODATA_START);
        st05_TEXT_START = .;
        build/us/src/battle/stages/st05/4CC.c.o(.text);
        build/us/src/battle/stages/st05/2A5C.c.o(.text);
        build/us/src/battle/stages/st05/2D64.c.o(.text);
        . = ALIGN(., 4);
        st05_TEXT_END = .;
        st05_TEXT_SIZE = ABSOLUTE(st05_TEXT_END - st05_TEXT_START);
        st05_DATA_START = .;
        build/us/asm/us/st05/data/0.rodata.s.o(.data);
        build/us/src/battle/stages/st05/4CC.c.o(.data);
        build/us/src/battle/stages/st05/2A5C.c.o(.data);
        build/us/src/battle/stages/st05/2D64.c.o(.data);
        . = ALIGN(., 4);
        st05_DATA_END = .;
        st05_DATA_SIZE = ABSOLUTE(st05_DATA_END - st05_DATA_START);
        st05_BSS_START = .;
        build/us/asm/us/st05/data/0.rodata.s.o(.bss);
        build/us/src/battle/stages/st05/4CC.c.o(.bss);
        build/us/src/battle/stages/st05/2A5C.c.o(.bss);
        build/us/src/battle/stages/st05/2D64.c.o(.bss);
        . = ALIGN(., 4);
        st05_BSS_END = .;
        st05_BSS_SIZE = ABSOLUTE(st05_BSS_END - st05_BSS_START);
    }
    __romPos += SIZEOF(.st05);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    st05_ROM_END = __romPos;
    st05_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
