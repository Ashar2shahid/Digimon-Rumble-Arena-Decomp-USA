SECTIONS
{
    HIDDEN(__romPos = 0);
    st03_ROM_START = __romPos;
    st03_VRAM = ADDR(.st03);
    .st03 0x800D3B00 : AT(st03_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        st03_RODATA_START = .;
        build/us/asm/us/st03/data/0.rodata.s.o(.rodata);
        build/us/src/battle/stages/st03/5F8.c.o(.rodata);
        . = ALIGN(., 4);
        st03_RODATA_END = .;
        st03_RODATA_SIZE = ABSOLUTE(st03_RODATA_END - st03_RODATA_START);
        st03_TEXT_START = .;
        build/us/src/battle/stages/st03/5F8.c.o(.text);
        . = ALIGN(., 4);
        st03_TEXT_END = .;
        st03_TEXT_SIZE = ABSOLUTE(st03_TEXT_END - st03_TEXT_START);
        st03_DATA_START = .;
        build/us/asm/us/st03/data/0.rodata.s.o(.data);
        build/us/src/battle/stages/st03/5F8.c.o(.data);
        . = ALIGN(., 4);
        st03_DATA_END = .;
        st03_DATA_SIZE = ABSOLUTE(st03_DATA_END - st03_DATA_START);
        st03_BSS_START = .;
        build/us/asm/us/st03/data/0.rodata.s.o(.bss);
        build/us/src/battle/stages/st03/5F8.c.o(.bss);
        . = ALIGN(., 4);
        st03_BSS_END = .;
        st03_BSS_SIZE = ABSOLUTE(st03_BSS_END - st03_BSS_START);
    }
    __romPos += SIZEOF(.st03);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    st03_ROM_END = __romPos;
    st03_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
