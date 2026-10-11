SECTIONS
{
    HIDDEN(__romPos = 0);
    st00_ROM_START = __romPos;
    st00_VRAM = ADDR(.st00);
    .st00 0x800D3B00 : AT(st00_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        st00_RODATA_START = .;
        build/us/asm/us/st00/data/0.rodata.s.o(.rodata);
        build/us/src/battle/stages/st00/354.c.o(.rodata);
        build/us/src/battle/stages/st00/4768.c.o(.rodata);
        build/us/src/battle/stages/st00/47BC.c.o(.rodata);
        build/us/src/battle/stages/st00/54D4.c.o(.rodata);
        build/us/src/battle/stages/st00/5528.c.o(.rodata);
        build/us/src/battle/stages/st00/6150.c.o(.rodata);
        build/us/src/battle/stages/st00/618C.c.o(.rodata);
        . = ALIGN(., 4);
        st00_RODATA_END = .;
        st00_RODATA_SIZE = ABSOLUTE(st00_RODATA_END - st00_RODATA_START);
        st00_TEXT_START = .;
        build/us/src/battle/stages/st00/354.c.o(.text);
        build/us/src/battle/stages/st00/4768.c.o(.text);
        build/us/src/battle/stages/st00/47BC.c.o(.text);
        build/us/src/battle/stages/st00/54D4.c.o(.text);
        build/us/src/battle/stages/st00/5528.c.o(.text);
        build/us/src/battle/stages/st00/6150.c.o(.text);
        build/us/src/battle/stages/st00/618C.c.o(.text);
        . = ALIGN(., 4);
        st00_TEXT_END = .;
        st00_TEXT_SIZE = ABSOLUTE(st00_TEXT_END - st00_TEXT_START);
        st00_DATA_START = .;
        build/us/asm/us/st00/data/0.rodata.s.o(.data);
        build/us/src/battle/stages/st00/354.c.o(.data);
        build/us/src/battle/stages/st00/4768.c.o(.data);
        build/us/src/battle/stages/st00/47BC.c.o(.data);
        build/us/src/battle/stages/st00/54D4.c.o(.data);
        build/us/src/battle/stages/st00/5528.c.o(.data);
        build/us/src/battle/stages/st00/6150.c.o(.data);
        build/us/src/battle/stages/st00/618C.c.o(.data);
        . = ALIGN(., 4);
        st00_DATA_END = .;
        st00_DATA_SIZE = ABSOLUTE(st00_DATA_END - st00_DATA_START);
        st00_BSS_START = .;
        build/us/asm/us/st00/data/0.rodata.s.o(.bss);
        build/us/src/battle/stages/st00/354.c.o(.bss);
        build/us/src/battle/stages/st00/4768.c.o(.bss);
        build/us/src/battle/stages/st00/47BC.c.o(.bss);
        build/us/src/battle/stages/st00/54D4.c.o(.bss);
        build/us/src/battle/stages/st00/5528.c.o(.bss);
        build/us/src/battle/stages/st00/6150.c.o(.bss);
        build/us/src/battle/stages/st00/618C.c.o(.bss);
        . = ALIGN(., 4);
        st00_BSS_END = .;
        st00_BSS_SIZE = ABSOLUTE(st00_BSS_END - st00_BSS_START);
    }
    __romPos += SIZEOF(.st00);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    st00_ROM_END = __romPos;
    st00_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
