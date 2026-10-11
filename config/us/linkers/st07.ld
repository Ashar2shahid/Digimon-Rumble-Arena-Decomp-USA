SECTIONS
{
    HIDDEN(__romPos = 0);
    st07_ROM_START = __romPos;
    st07_VRAM = ADDR(.st07);
    .st07 0x800D3B00 : AT(st07_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        st07_RODATA_START = .;
        build/us/asm/us/st07/data/0.rodata.s.o(.rodata);
        build/us/src/battle/stages/st07/194.c.o(.rodata);
        build/us/src/battle/stages/st07/368.c.o(.rodata);
        build/us/src/battle/stages/st07/390.c.o(.rodata);
        . = ALIGN(., 4);
        st07_RODATA_END = .;
        st07_RODATA_SIZE = ABSOLUTE(st07_RODATA_END - st07_RODATA_START);
        st07_TEXT_START = .;
        build/us/src/battle/stages/st07/194.c.o(.text);
        build/us/src/battle/stages/st07/368.c.o(.text);
        build/us/src/battle/stages/st07/390.c.o(.text);
        . = ALIGN(., 4);
        st07_TEXT_END = .;
        st07_TEXT_SIZE = ABSOLUTE(st07_TEXT_END - st07_TEXT_START);
        st07_DATA_START = .;
        build/us/asm/us/st07/data/0.rodata.s.o(.data);
        build/us/src/battle/stages/st07/194.c.o(.data);
        build/us/src/battle/stages/st07/368.c.o(.data);
        build/us/src/battle/stages/st07/390.c.o(.data);
        . = ALIGN(., 4);
        st07_DATA_END = .;
        st07_DATA_SIZE = ABSOLUTE(st07_DATA_END - st07_DATA_START);
        st07_BSS_START = .;
        build/us/asm/us/st07/data/0.rodata.s.o(.bss);
        build/us/src/battle/stages/st07/194.c.o(.bss);
        build/us/src/battle/stages/st07/368.c.o(.bss);
        build/us/src/battle/stages/st07/390.c.o(.bss);
        . = ALIGN(., 4);
        st07_BSS_END = .;
        st07_BSS_SIZE = ABSOLUTE(st07_BSS_END - st07_BSS_START);
    }
    __romPos += SIZEOF(.st07);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    st07_ROM_END = __romPos;
    st07_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
