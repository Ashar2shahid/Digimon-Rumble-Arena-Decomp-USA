build/us/st08.elf: \
    build/us/asm/us/st08/data/0.rodata.s.o \
    build/us/src/battle/stages/st08/EC.c.o
build/us/asm/us/st08/data/0.rodata.s.o:
build/us/src/battle/stages/st08/EC.c.o:
-include build/us/asm/us/st08/data/0.rodata.s.d build/us/src/battle/stages/st08/EC.c.d
