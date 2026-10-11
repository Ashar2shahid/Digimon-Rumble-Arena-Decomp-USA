SECTIONS
{
    HIDDEN(__romPos = 0);
    title_ROM_START = __romPos;
    title_VRAM = ADDR(.title);
    .title 0x800643C0 : AT(title_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        title_RODATA_START = .;
        build/us/asm/us/title/data/0.rodata.s.o(.rodata);
        build/us/src/title/2570.c.o(.rodata);
        build/us/src/title/3FC4.c.o(.rodata);
        build/us/src/title/40C4.c.o(.rodata);
        build/us/src/title/65A4.c.o(.rodata);
        build/us/src/title/A660.c.o(.rodata);
        build/us/src/title/E6AC.c.o(.rodata);
        build/us/src/title/12AF0.c.o(.rodata);
        . = ALIGN(., 4);
        title_RODATA_END = .;
        title_RODATA_SIZE = ABSOLUTE(title_RODATA_END - title_RODATA_START);
        title_TEXT_START = .;
        build/us/src/title/2570.c.o(.text);
        build/us/src/title/3FC4.c.o(.text);
        build/us/src/title/40C4.c.o(.text);
        build/us/src/title/65A4.c.o(.text);
        build/us/src/title/A660.c.o(.text);
        build/us/src/title/E6AC.c.o(.text);
        build/us/src/title/12AF0.c.o(.text);
        . = ALIGN(., 4);
        title_TEXT_END = .;
        title_TEXT_SIZE = ABSOLUTE(title_TEXT_END - title_TEXT_START);
        title_DATA_START = .;
        build/us/asm/us/title/data/0.rodata.s.o(.data);
        build/us/src/title/2570.c.o(.data);
        build/us/src/title/3FC4.c.o(.data);
        build/us/src/title/40C4.c.o(.data);
        build/us/src/title/65A4.c.o(.data);
        build/us/src/title/A660.c.o(.data);
        build/us/src/title/E6AC.c.o(.data);
        build/us/src/title/12AF0.c.o(.data);
        . = ALIGN(., 4);
        title_DATA_END = .;
        title_DATA_SIZE = ABSOLUTE(title_DATA_END - title_DATA_START);
        title_BSS_START = .;
        build/us/asm/us/title/data/0.rodata.s.o(.bss);
        build/us/src/title/2570.c.o(.bss);
        build/us/src/title/3FC4.c.o(.bss);
        build/us/src/title/40C4.c.o(.bss);
        build/us/src/title/65A4.c.o(.bss);
        build/us/src/title/A660.c.o(.bss);
        build/us/src/title/E6AC.c.o(.bss);
        build/us/src/title/12AF0.c.o(.bss);
        . = ALIGN(., 4);
        title_BSS_END = .;
        title_BSS_SIZE = ABSOLUTE(title_BSS_END - title_BSS_START);
    }
    __romPos += SIZEOF(.title);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    title_ROM_END = __romPos;
    title_VRAM_END = .;

    /* Generated switch tables occupy their existing retail data ranges,
       following the established game/6568C placement scheme. */
    .rodata_ba9c 0x800648B8 : AT(0x4F8) SUBALIGN(4)
    {
        build/us/src/title/65A4.c.o(.rodata.ba9c);
    }
    .rodata_f7f4 0x800650FC : AT(0xD3C) SUBALIGN(4)
    {
        build/us/src/title/A660.c.o(.rodata.f7f4);
    }

    /DISCARD/ :
    {
        *(*);
    }
}
