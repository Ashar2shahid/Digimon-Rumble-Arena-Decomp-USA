build/us/st04.elf: \
    build/us/asm/us/st04/data/0.rodata.s.o \
    build/us/src/battle/stages/st04/2A4.c.o
build/us/asm/us/st04/data/0.rodata.s.o:
build/us/src/battle/stages/st04/2A4.c.o:
-include build/us/asm/us/st04/data/0.rodata.s.d build/us/src/battle/stages/st04/2A4.c.d
