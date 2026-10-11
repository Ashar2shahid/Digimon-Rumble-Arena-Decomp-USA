SECTIONS
{
    HIDDEN(__romPos = 0);
    st06_ROM_START = __romPos;
    st06_VRAM = ADDR(.st06);
    .st06 0x800D3B00 : AT(st06_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        st06_RODATA_START = .;
        build/us/asm/us/st06/data/0.rodata.s.o(.rodata);
        build/us/src/battle/stages/st06/3F0.c.o(.rodata);
        build/us/src/battle/stages/st06/C48.c.o(.rodata);
        build/us/src/battle/stages/st06/CA4.c.o(.rodata);
        build/us/src/battle/stages/st06/1820.c.o(.rodata);
        build/us/src/battle/stages/st06/186C.c.o(.rodata);
        build/us/src/battle/stages/st06/1D5C.c.o(.rodata);
        build/us/src/battle/stages/st06/1DB4.c.o(.rodata);
        build/us/src/battle/stages/st06/1FA4.c.o(.rodata);
        build/us/src/battle/stages/st06/22F4.c.o(.rodata);
        . = ALIGN(., 4);
        st06_RODATA_END = .;
        st06_RODATA_SIZE = ABSOLUTE(st06_RODATA_END - st06_RODATA_START);
        st06_TEXT_START = .;
        build/us/src/battle/stages/st06/3F0.c.o(.text);
        build/us/src/battle/stages/st06/C48.c.o(.text);
        build/us/src/battle/stages/st06/CA4.c.o(.text);
        build/us/src/battle/stages/st06/1820.c.o(.text);
        build/us/src/battle/stages/st06/186C.c.o(.text);
        build/us/src/battle/stages/st06/1D5C.c.o(.text);
        build/us/src/battle/stages/st06/1DB4.c.o(.text);
        build/us/src/battle/stages/st06/1FA4.c.o(.text);
        build/us/src/battle/stages/st06/22F4.c.o(.text);
        . = ALIGN(., 4);
        st06_TEXT_END = .;
        st06_TEXT_SIZE = ABSOLUTE(st06_TEXT_END - st06_TEXT_START);
        st06_DATA_START = .;
        build/us/asm/us/st06/data/0.rodata.s.o(.data);
        build/us/src/battle/stages/st06/3F0.c.o(.data);
        build/us/src/battle/stages/st06/C48.c.o(.data);
        build/us/src/battle/stages/st06/CA4.c.o(.data);
        build/us/src/battle/stages/st06/1820.c.o(.data);
        build/us/src/battle/stages/st06/186C.c.o(.data);
        build/us/src/battle/stages/st06/1D5C.c.o(.data);
        build/us/src/battle/stages/st06/1DB4.c.o(.data);
        build/us/src/battle/stages/st06/1FA4.c.o(.data);
        build/us/src/battle/stages/st06/22F4.c.o(.data);
        . = ALIGN(., 4);
        st06_DATA_END = .;
        st06_DATA_SIZE = ABSOLUTE(st06_DATA_END - st06_DATA_START);
        st06_BSS_START = .;
        build/us/asm/us/st06/data/0.rodata.s.o(.bss);
        build/us/src/battle/stages/st06/3F0.c.o(.bss);
        build/us/src/battle/stages/st06/C48.c.o(.bss);
        build/us/src/battle/stages/st06/CA4.c.o(.bss);
        build/us/src/battle/stages/st06/1820.c.o(.bss);
        build/us/src/battle/stages/st06/186C.c.o(.bss);
        build/us/src/battle/stages/st06/1D5C.c.o(.bss);
        build/us/src/battle/stages/st06/1DB4.c.o(.bss);
        build/us/src/battle/stages/st06/1FA4.c.o(.bss);
        build/us/src/battle/stages/st06/22F4.c.o(.bss);
        . = ALIGN(., 4);
        st06_BSS_END = .;
        st06_BSS_SIZE = ABSOLUTE(st06_BSS_END - st06_BSS_START);
    }
    __romPos += SIZEOF(.st06);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    st06_ROM_END = __romPos;
    st06_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
