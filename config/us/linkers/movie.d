build/us/movie.elf: \
    build/us/asm/us/movie/data/0.rodata.s.o \
    build/us/src/movie/B4.c.o
build/us/asm/us/movie/data/0.rodata.s.o:
build/us/src/movie/B4.c.o:
-include build/us/asm/us/movie/data/0.rodata.s.d build/us/src/movie/B4.c.d
