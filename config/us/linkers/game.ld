SECTIONS
{
    HIDDEN(__romPos = 0);
    game_ROM_START = __romPos;
    game_VRAM = ADDR(.game);
    .game 0x800643C0 : AT(game_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        game_RODATA_START = .;
        build/us/asm/us/game/data/0.rodata.s.o(.rodata);
        build/us/src/battle/E324.c.o(.rodata);
        build/us/src/battle/12398.c.o(.rodata);
        build/us/src/battle/16458.c.o(.rodata);
        build/us/src/battle/18104.c.o(.rodata);
        build/us/src/battle/1C120.c.o(.rodata);
        build/us/src/battle/202B4.c.o(.rodata);
        build/us/src/battle/243F0.c.o(.rodata);
        build/us/src/battle/28514.c.o(.rodata);
        build/us/src/battle/2C7C4.c.o(.rodata);
        build/us/src/battle/309F0.c.o(.rodata);
        build/us/src/battle/38D84.c.o(.rodata);
        build/us/src/battle/3CDF0.c.o(.rodata);
        build/us/src/battle/40E5C.c.o(.rodata);
        build/us/src/battle/44E78.c.o(.rodata);
        build/us/src/battle/48F48.c.o(.rodata);
        build/us/src/battle/4CF7C.c.o(.rodata);
        build/us/src/battle/50FE4.c.o(.rodata);
        build/us/src/battle/55164.c.o(.rodata);
        build/us/src/battle/5922C.c.o(.rodata);
        build/us/src/battle/5D3CC.c.o(.rodata);
        build/us/src/battle/6155C.c.o(.rodata);
        build/us/src/battle/697BC.c.o(.rodata);
        build/us/src/battle/6DB60.c.o(.rodata);
        . = ALIGN(., 4);
        game_RODATA_END = .;
        game_RODATA_SIZE = ABSOLUTE(game_RODATA_END - game_RODATA_START);
        game_TEXT_START = .;
        build/us/src/battle/9DF4.c.o(.text);
        build/us/src/battle/E324.c.o(.text);
        build/us/src/battle/12398.c.o(.text);
        build/us/src/battle/16458.c.o(.text);
        build/us/src/battle/18104.c.o(.text);
        build/us/src/battle/1C120.c.o(.text);
        build/us/src/battle/202B4.c.o(.text);
        build/us/src/battle/243F0.c.o(.text);
        build/us/src/battle/28514.c.o(.text);
        build/us/src/battle/2C7C4.c.o(.text);
        build/us/src/battle/309F0.c.o(.text);
        build/us/src/battle/34AFC.c.o(.text);
        build/us/src/battle/38D84.c.o(.text);
        build/us/src/battle/3CDF0.c.o(.text);
        build/us/src/battle/40E5C.c.o(.text);
        build/us/src/battle/44E78.c.o(.text);
        build/us/src/battle/48F48.c.o(.text);
        build/us/src/battle/4CF7C.c.o(.text);
        build/us/src/battle/50FE4.c.o(.text);
        build/us/src/battle/55164.c.o(.text);
        build/us/src/battle/5922C.c.o(.text);
        build/us/src/battle/5D3CC.c.o(.text);
        build/us/src/battle/6155C.c.o(.text);
        build/us/src/battle/6568C.c.o(.text);
        build/us/src/battle/697BC.c.o(.text);
        build/us/src/battle/6DB60.c.o(.text);
        . = ALIGN(., 4);
        game_TEXT_END = .;
        game_TEXT_SIZE = ABSOLUTE(game_TEXT_END - game_TEXT_START);
        game_DATA_START = .;
        build/us/asm/us/game/data/0.rodata.s.o(.data);
        build/us/src/battle/9DF4.c.o(.data);
        build/us/src/battle/E324.c.o(.data);
        build/us/src/battle/12398.c.o(.data);
        build/us/src/battle/16458.c.o(.data);
        build/us/src/battle/18104.c.o(.data);
        build/us/src/battle/1C120.c.o(.data);
        build/us/src/battle/202B4.c.o(.data);
        build/us/src/battle/243F0.c.o(.data);
        build/us/src/battle/28514.c.o(.data);
        build/us/src/battle/2C7C4.c.o(.data);
        build/us/src/battle/309F0.c.o(.data);
        build/us/src/battle/34AFC.c.o(.data);
        build/us/src/battle/38D84.c.o(.data);
        build/us/src/battle/3CDF0.c.o(.data);
        build/us/src/battle/40E5C.c.o(.data);
        build/us/src/battle/44E78.c.o(.data);
        build/us/src/battle/48F48.c.o(.data);
        build/us/src/battle/4CF7C.c.o(.data);
        build/us/src/battle/50FE4.c.o(.data);
        build/us/src/battle/55164.c.o(.data);
        build/us/src/battle/5922C.c.o(.data);
        build/us/src/battle/5D3CC.c.o(.data);
        build/us/src/battle/6155C.c.o(.data);
        build/us/src/battle/6568C.c.o(.data);
        build/us/src/battle/697BC.c.o(.data);
        build/us/src/battle/6DB60.c.o(.data);
        . = ALIGN(., 4);
        game_DATA_END = .;
        game_DATA_SIZE = ABSOLUTE(game_DATA_END - game_DATA_START);
        game_BSS_START = .;
        build/us/asm/us/game/data/0.rodata.s.o(.bss);
        build/us/src/battle/9DF4.c.o(.bss);
        build/us/src/battle/E324.c.o(.bss);
        build/us/src/battle/12398.c.o(.bss);
        build/us/src/battle/16458.c.o(.bss);
        build/us/src/battle/18104.c.o(.bss);
        build/us/src/battle/1C120.c.o(.bss);
        build/us/src/battle/202B4.c.o(.bss);
        build/us/src/battle/243F0.c.o(.bss);
        build/us/src/battle/28514.c.o(.bss);
        build/us/src/battle/2C7C4.c.o(.bss);
        build/us/src/battle/309F0.c.o(.bss);
        build/us/src/battle/34AFC.c.o(.bss);
        build/us/src/battle/38D84.c.o(.bss);
        build/us/src/battle/3CDF0.c.o(.bss);
        build/us/src/battle/40E5C.c.o(.bss);
        build/us/src/battle/44E78.c.o(.bss);
        build/us/src/battle/48F48.c.o(.bss);
        build/us/src/battle/4CF7C.c.o(.bss);
        build/us/src/battle/50FE4.c.o(.bss);
        build/us/src/battle/55164.c.o(.bss);
        build/us/src/battle/5922C.c.o(.bss);
        build/us/src/battle/5D3CC.c.o(.bss);
        build/us/src/battle/6155C.c.o(.bss);
        build/us/src/battle/6568C.c.o(.bss);
        build/us/src/battle/697BC.c.o(.bss);
        build/us/src/battle/6DB60.c.o(.bss);
        . = ALIGN(., 4);
        game_BSS_END = .;
        game_BSS_SIZE = ABSOLUTE(game_BSS_END - game_BSS_START);
    }
    __romPos += SIZEOF(.game);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    game_ROM_END = __romPos;
    game_VRAM_END = .;

    /* C-emitted switch tables whose retail home is inside the committed
       rodata slot: overlapped onto it (identical bytes) so .text is not
       pushed past 0x9DF4.  --no-check-sections permits the overlap. */
    .rodata_34AFC 0x80069E54 : AT(0x5A94) SUBALIGN(4)
    {
        build/us/src/battle/34AFC.c.o(.rodata);
    }

    /* game/9DF4 func_80070F2C's switch table is retail's committed
       jtbl_80064DD0 (5 words, byte-identical); overlapped onto its retail
       home so the slot does not push .text past 0x8006E1B4. */
    .rodata_9DF4 0x80064DD0 : AT(0xA10) SUBALIGN(4)
    {
        build/us/src/battle/9DF4.c.o(.rodata);
    }

    /* game/6568C emits two switch tables 0x2C4 bytes apart in retail; each
       .rdata block is named (UNIT_RODATA_SECTIONS) and placed on its retail
       home in the committed slot. */
    .rodata_6568C_a 0x8006D918 : AT(0x9558) SUBALIGN(4)
    {
        build/us/src/battle/6568C.c.o(.rodata.a);
    }
    .rodata_6568C_b 0x8006DBF4 : AT(0x9834) SUBALIGN(4)
    {
        build/us/src/battle/6568C.c.o(.rodata.b);
    }

    /* Generated 21-word switch table retained at jtbl_8006520C's retail home. */
    .rodata_79680 0x8006520C : AT(0xE4C) SUBALIGN(4)
    {
        build/us/src/battle/12398.c.o(.rodata.79680);
    }

    /DISCARD/ :
    {
        *(*);
    }
}
