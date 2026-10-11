#include "common.h"
#include "game_vfs.h"


INCLUDE_ASM("asm/us/main/nonmatchings/23800", func_800330C8);

INCLUDE_ASM("asm/us/main/nonmatchings/23800", func_800331C0);

extern void *func_8003DEEC(void *, s32);
extern void func_80035050(void);
extern void func_800388A8(u8 *, void *, s32, s32);
extern s32 func_800434B0(void);
void func_80033290(u32);
extern s32 func_80033788(u8 *, const char *);

s32 func_800331F8(s32 skipFinalInit) {
    VfsRuntime *runtime = &D_80114B80;
    func_8003DEEC(runtime, sizeof(*runtime));
    func_80035050();
    func_800388A8((u8 *)runtime + 0x2C, (u8 *)runtime + 0x40, 0x80, 0x10);
    runtime->notification = func_80033290;
    runtime->pathLookup = func_80033788;
    runtime->completion = func_80033290;
    runtime->flags |= 6;
    if (skipFinalInit == 0) {
        return func_800434B0();
    }
    return 0;
}

void func_80033290(u32 argument) {
}

INCLUDE_ASM("asm/us/main/nonmatchings/23800", func_80033298);

typedef struct {
    u32 magic;
    u32 entryCount;
    u32 dataOffset;
    u32 directoryEndOffset;
} VfsHeader;

typedef struct {
    u16 entryCount;
    u16 reserved;
    u32 directorySector;
    u32 dataSector;
} VfsMount;

extern char D_8001940C[];
extern s32 (*D_8006438C)(const char *, ...);
extern s32 func_80034330(VfsHeader *, void *, s32, s32);
extern s32 func_80046C4C(void *);

s32 func_800333CC(VfsMount *self, void *name) {
    VfsHeader header;
    s32 sector;
    D_80114B80.flags |= 0x20;
    if (func_80034330(&header, name, 0, sizeof(header)) != 0) {
        if (header.magic != 0x32534656) {
            const char *message = D_8001940C;
            s32 (*callback)(const char *, ...) = D_8006438C;
            callback(message);
        } else {
            sector = func_80046C4C((u8 *)&D_80114B80 + 0x1C);
            self->directorySector = sector + 1;
            self->entryCount = header.entryCount;
            self->dataSector = sector + header.dataOffset;
            return header.entryCount << 5;
        }
    }
    return 0;
}

/* Historical internal error-path label within func_800333CC. */
__asm__(".globl func_80033458\n.set func_80033458, func_800333CC + 0x8C\n.size func_80033458, 0x28");


void func_80033480(ZlibAllocFn alloc, ZlibFreeFn release, void *opaque) {
    VfsRuntime *runtime = &D_80114B80;
    runtime->alloc = alloc;
    runtime->release = release;
    runtime->opaque = opaque;
}

INCLUDE_ASM("asm/us/main/nonmatchings/23800", func_80033498);

INCLUDE_ASM("asm/us/main/nonmatchings/23800", func_80033558);

INCLUDE_ASM("asm/us/main/nonmatchings/23800", func_800336A0);

void func_800336CC(void) {
}

INCLUDE_ASM("asm/us/main/nonmatchings/23800", func_800336D4);

INCLUDE_ASM("asm/us/main/nonmatchings/23800", func_80033788);

INCLUDE_ASM("asm/us/main/nonmatchings/23800", func_800337E4);
