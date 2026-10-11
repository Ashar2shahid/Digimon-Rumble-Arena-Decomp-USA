build/us/st01.elf: \
    build/us/asm/us/st01/data/0.rodata.s.o \
    build/us/src/battle/stages/st01/59C.c.o
build/us/asm/us/st01/data/0.rodata.s.o:
build/us/src/battle/stages/st01/59C.c.o:
-include build/us/asm/us/st01/data/0.rodata.s.d build/us/src/battle/stages/st01/59C.c.d
