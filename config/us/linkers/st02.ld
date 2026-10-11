SECTIONS
{
    HIDDEN(__romPos = 0);
    st02_ROM_START = __romPos;
    st02_VRAM = ADDR(.st02);
    .st02 0x800D3B00 : AT(st02_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        st02_RODATA_START = .;
        build/us/asm/us/st02/data/0.rodata.s.o(.rodata);
        build/us/src/battle/stages/st02/944.c.o(.rodata);
        . = ALIGN(., 4);
        st02_RODATA_END = .;
        st02_RODATA_SIZE = ABSOLUTE(st02_RODATA_END - st02_RODATA_START);
        st02_TEXT_START = .;
        build/us/src/battle/stages/st02/944.c.o(.text);
        . = ALIGN(., 4);
        st02_TEXT_END = .;
        st02_TEXT_SIZE = ABSOLUTE(st02_TEXT_END - st02_TEXT_START);
        st02_DATA_START = .;
        build/us/asm/us/st02/data/0.rodata.s.o(.data);
        build/us/src/battle/stages/st02/944.c.o(.data);
        . = ALIGN(., 4);
        st02_DATA_END = .;
        st02_DATA_SIZE = ABSOLUTE(st02_DATA_END - st02_DATA_START);
        st02_BSS_START = .;
        build/us/asm/us/st02/data/0.rodata.s.o(.bss);
        build/us/src/battle/stages/st02/944.c.o(.bss);
        . = ALIGN(., 4);
        st02_BSS_END = .;
        st02_BSS_SIZE = ABSOLUTE(st02_BSS_END - st02_BSS_START);
    }
    __romPos += SIZEOF(.st02);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    st02_ROM_END = __romPos;
    st02_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
