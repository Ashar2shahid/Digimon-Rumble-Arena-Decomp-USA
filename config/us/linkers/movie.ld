SECTIONS
{
    HIDDEN(__romPos = 0);
    movie_ROM_START = __romPos;
    movie_VRAM = ADDR(.movie);
    .movie 0x800643C0 : AT(movie_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        movie_RODATA_START = .;
        build/us/asm/us/movie/data/0.rodata.s.o(.rodata);
        build/us/src/movie/B4.c.o(.rodata);
        . = ALIGN(., 4);
        movie_RODATA_END = .;
        movie_RODATA_SIZE = ABSOLUTE(movie_RODATA_END - movie_RODATA_START);
        movie_TEXT_START = .;
        build/us/src/movie/B4.c.o(.text);
        . = ALIGN(., 4);
        movie_TEXT_END = .;
        movie_TEXT_SIZE = ABSOLUTE(movie_TEXT_END - movie_TEXT_START);
        movie_DATA_START = .;
        build/us/asm/us/movie/data/0.rodata.s.o(.data);
        build/us/src/movie/B4.c.o(.data);
        . = ALIGN(., 4);
        movie_DATA_END = .;
        movie_DATA_SIZE = ABSOLUTE(movie_DATA_END - movie_DATA_START);
        movie_BSS_START = .;
        build/us/asm/us/movie/data/0.rodata.s.o(.bss);
        build/us/src/movie/B4.c.o(.bss);
        . = ALIGN(., 4);
        movie_BSS_END = .;
        movie_BSS_SIZE = ABSOLUTE(movie_BSS_END - movie_BSS_START);
    }
    __romPos += SIZEOF(.movie);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    movie_ROM_END = __romPos;
    movie_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
