SECTIONS
{
    HIDDEN(__romPos = 0);
    st08_ROM_START = __romPos;
    st08_VRAM = ADDR(.st08);
    .st08 0x800D3B00 : AT(st08_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        st08_RODATA_START = .;
        build/us/asm/us/st08/data/0.rodata.s.o(.rodata);
        build/us/src/battle/stages/st08/EC.c.o(.rodata);
        . = ALIGN(., 4);
        st08_RODATA_END = .;
        st08_RODATA_SIZE = ABSOLUTE(st08_RODATA_END - st08_RODATA_START);
        st08_TEXT_START = .;
        build/us/src/battle/stages/st08/EC.c.o(.text);
        . = ALIGN(., 4);
        st08_TEXT_END = .;
        st08_TEXT_SIZE = ABSOLUTE(st08_TEXT_END - st08_TEXT_START);
        st08_DATA_START = .;
        build/us/asm/us/st08/data/0.rodata.s.o(.data);
        build/us/src/battle/stages/st08/EC.c.o(.data);
        . = ALIGN(., 4);
        st08_DATA_END = .;
        st08_DATA_SIZE = ABSOLUTE(st08_DATA_END - st08_DATA_START);
        st08_BSS_START = .;
        build/us/asm/us/st08/data/0.rodata.s.o(.bss);
        build/us/src/battle/stages/st08/EC.c.o(.bss);
        . = ALIGN(., 4);
        st08_BSS_END = .;
        st08_BSS_SIZE = ABSOLUTE(st08_BSS_END - st08_BSS_START);
    }
    __romPos += SIZEOF(.st08);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    st08_ROM_END = __romPos;
    st08_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
