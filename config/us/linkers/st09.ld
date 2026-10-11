SECTIONS
{
    HIDDEN(__romPos = 0);
    st09_ROM_START = __romPos;
    st09_VRAM = ADDR(.st09);
    .st09 0x800D3B00 : AT(st09_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        st09_RODATA_START = .;
        build/us/asm/us/st09/data/0.rodata.s.o(.rodata);
        build/us/src/battle/stages/st09/244.c.o(.rodata);
        . = ALIGN(., 4);
        st09_RODATA_END = .;
        st09_RODATA_SIZE = ABSOLUTE(st09_RODATA_END - st09_RODATA_START);
        st09_TEXT_START = .;
        build/us/src/battle/stages/st09/244.c.o(.text);
        . = ALIGN(., 4);
        st09_TEXT_END = .;
        st09_TEXT_SIZE = ABSOLUTE(st09_TEXT_END - st09_TEXT_START);
        st09_DATA_START = .;
        build/us/asm/us/st09/data/0.rodata.s.o(.data);
        build/us/src/battle/stages/st09/244.c.o(.data);
        . = ALIGN(., 4);
        st09_DATA_END = .;
        st09_DATA_SIZE = ABSOLUTE(st09_DATA_END - st09_DATA_START);
        st09_BSS_START = .;
        build/us/asm/us/st09/data/0.rodata.s.o(.bss);
        build/us/src/battle/stages/st09/244.c.o(.bss);
        . = ALIGN(., 4);
        st09_BSS_END = .;
        st09_BSS_SIZE = ABSOLUTE(st09_BSS_END - st09_BSS_START);
    }
    __romPos += SIZEOF(.st09);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    st09_ROM_END = __romPos;
    st09_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
