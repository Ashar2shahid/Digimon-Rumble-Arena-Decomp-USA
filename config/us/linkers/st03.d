build/us/st03.elf: \
    build/us/asm/us/st03/data/0.rodata.s.o \
    build/us/src/battle/stages/st03/5F8.c.o
build/us/asm/us/st03/data/0.rodata.s.o:
build/us/src/battle/stages/st03/5F8.c.o:
-include build/us/asm/us/st03/data/0.rodata.s.d build/us/src/battle/stages/st03/5F8.c.d
