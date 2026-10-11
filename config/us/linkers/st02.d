build/us/st02.elf: \
    build/us/asm/us/st02/data/0.rodata.s.o \
    build/us/src/battle/stages/st02/944.c.o
build/us/asm/us/st02/data/0.rodata.s.o:
build/us/src/battle/stages/st02/944.c.o:
-include build/us/asm/us/st02/data/0.rodata.s.d build/us/src/battle/stages/st02/944.c.d
