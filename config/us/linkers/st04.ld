SECTIONS
{
    HIDDEN(__romPos = 0);
    st04_ROM_START = __romPos;
    st04_VRAM = ADDR(.st04);
    .st04 0x800D3B00 : AT(st04_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        st04_RODATA_START = .;
        build/us/asm/us/st04/data/0.rodata.s.o(.rodata);
        build/us/src/battle/stages/st04/5864.c.o(.rodata);
        build/us/src/battle/stages/st04/67EC.c.o(.rodata);
        . = ALIGN(., 4);
        st04_RODATA_END = .;
        st04_RODATA_SIZE = ABSOLUTE(st04_RODATA_END - st04_RODATA_START);
        st04_TEXT_START = .;
        build/us/src/battle/stages/st04/2A4.c.o(.text);
        build/us/src/battle/stages/st04/5864.c.o(.text);
        build/us/src/battle/stages/st04/59B0.c.o(.text);
        build/us/src/battle/stages/st04/67EC.c.o(.text);
        build/us/src/battle/stages/st04/6948.c.o(.text);
        . = ALIGN(., 4);
        st04_TEXT_END = .;
        st04_TEXT_SIZE = ABSOLUTE(st04_TEXT_END - st04_TEXT_START);
        st04_DATA_START = .;
        build/us/asm/us/st04/data/0.rodata.s.o(.data);
        build/us/src/battle/stages/st04/2A4.c.o(.data);
        build/us/src/battle/stages/st04/5864.c.o(.data);
        build/us/src/battle/stages/st04/59B0.c.o(.data);
        build/us/src/battle/stages/st04/67EC.c.o(.data);
        build/us/src/battle/stages/st04/6948.c.o(.data);
        . = ALIGN(., 4);
        st04_DATA_END = .;
        st04_DATA_SIZE = ABSOLUTE(st04_DATA_END - st04_DATA_START);
        st04_BSS_START = .;
        build/us/asm/us/st04/data/0.rodata.s.o(.bss);
        build/us/src/battle/stages/st04/2A4.c.o(.bss);
        build/us/src/battle/stages/st04/5864.c.o(.bss);
        build/us/src/battle/stages/st04/59B0.c.o(.bss);
        build/us/src/battle/stages/st04/67EC.c.o(.bss);
        build/us/src/battle/stages/st04/6948.c.o(.bss);
        . = ALIGN(., 4);
        st04_BSS_END = .;
        st04_BSS_SIZE = ABSOLUTE(st04_BSS_END - st04_BSS_START);
    }
    __romPos += SIZEOF(.st04);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    st04_ROM_END = __romPos;
    st04_VRAM_END = .;

    /* C-emitted switch tables for the slot's jtbl owners: each table's retail
       home is inside the committed rodata blob (asm/us/st04/data/0.rodata.s),
       which keeps its bytes (the .L targets resolve via build_dra.symbol_script),
       so the object's .rodata is overlapped onto the same address -- identical
       bytes, --no-check-sections.  Each object is excluded from the aggregate
       rodata list above so the table is not also appended after it (which would
       push .text).  Owners: func_800D52AC/5B8C/7D84. */
    .rodata_52AC 0x800D3B64 : AT(0x64) SUBALIGN(4)
    {
        build/us/src/battle/stages/st04/2A4.c.o(.rodata);
    }
    .rodata_5B8C 0x800D3B7C : AT(0x7C) SUBALIGN(4)
    {
        build/us/src/battle/stages/st04/59B0.c.o(.rodata);
    }
    .rodata_7D84 0x800D3BB4 : AT(0xB4) SUBALIGN(4)
    {
        build/us/src/battle/stages/st04/6948.c.o(.rodata);
    }

    /DISCARD/ :
    {
        *(*);
    }
}
