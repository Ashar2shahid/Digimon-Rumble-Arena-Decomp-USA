build/us/st05.elf: \
    build/us/asm/us/st05/data/0.rodata.s.o \
    build/us/src/battle/stages/st05/4CC.c.o
build/us/asm/us/st05/data/0.rodata.s.o:
build/us/src/battle/stages/st05/4CC.c.o:
-include build/us/asm/us/st05/data/0.rodata.s.d build/us/src/battle/stages/st05/4CC.c.d
