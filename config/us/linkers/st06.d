build/us/st06.elf: \
    build/us/asm/us/st06/data/0.rodata.s.o \
    build/us/src/battle/stages/st06/3F0.c.o \
    build/us/src/battle/stages/st06/1FA4.c.o \
    build/us/src/battle/stages/st06/22F4.c.o
build/us/asm/us/st06/data/0.rodata.s.o:
build/us/src/battle/stages/st06/3F0.c.o:
build/us/src/battle/stages/st06/1FA4.c.o:
build/us/src/battle/stages/st06/22F4.c.o:
-include build/us/asm/us/st06/data/0.rodata.s.d build/us/src/battle/stages/st06/3F0.c.d build/us/src/battle/stages/st06/1FA4.c.d build/us/src/battle/stages/st06/22F4.c.d
