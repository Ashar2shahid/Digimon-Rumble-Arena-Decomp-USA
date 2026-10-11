SECTIONS
{
    HIDDEN(__romPos = 0);
    st01_ROM_START = __romPos;
    st01_VRAM = ADDR(.st01);
    .st01 0x800D3B00 : AT(st01_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        st01_RODATA_START = .;
        build/us/asm/us/st01/data/0.rodata.s.o(.rodata);
        build/us/src/battle/stages/st01/59C.c.o(.rodata);
        build/us/src/battle/stages/st01/185C.c.o(.rodata);
        build/us/src/battle/stages/st01/1928.c.o(.rodata);
        . = ALIGN(., 4);
        st01_RODATA_END = .;
        st01_RODATA_SIZE = ABSOLUTE(st01_RODATA_END - st01_RODATA_START);
        st01_TEXT_START = .;
        build/us/src/battle/stages/st01/59C.c.o(.text);
        build/us/src/battle/stages/st01/185C.c.o(.text);
        build/us/src/battle/stages/st01/1928.c.o(.text);
        . = ALIGN(., 4);
        st01_TEXT_END = .;
        st01_TEXT_SIZE = ABSOLUTE(st01_TEXT_END - st01_TEXT_START);
        st01_DATA_START = .;
        build/us/asm/us/st01/data/0.rodata.s.o(.data);
        build/us/src/battle/stages/st01/59C.c.o(.data);
        build/us/src/battle/stages/st01/185C.c.o(.data);
        build/us/src/battle/stages/st01/1928.c.o(.data);
        . = ALIGN(., 4);
        st01_DATA_END = .;
        st01_DATA_SIZE = ABSOLUTE(st01_DATA_END - st01_DATA_START);
        st01_BSS_START = .;
        build/us/asm/us/st01/data/0.rodata.s.o(.bss);
        build/us/src/battle/stages/st01/59C.c.o(.bss);
        build/us/src/battle/stages/st01/185C.c.o(.bss);
        build/us/src/battle/stages/st01/1928.c.o(.bss);
        . = ALIGN(., 4);
        st01_BSS_END = .;
        st01_BSS_SIZE = ABSOLUTE(st01_BSS_END - st01_BSS_START);
    }
    __romPos += SIZEOF(.st01);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    st01_ROM_END = __romPos;
    st01_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
