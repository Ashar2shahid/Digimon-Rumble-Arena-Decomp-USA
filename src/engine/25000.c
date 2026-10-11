#include "common.h"
#include "game_vfs.h"
#include "game_cd_callbacks.h"
#include "game_cd_read_state.h"
#include "game_sdk_memcpy.h"

extern void func_800349A8(void);
extern s32 func_80034550(s32);
extern char D_800194BC[];
extern s32 (*D_8006438C)(const char *, ...);
extern void func_800462E0(void);
extern s32 func_8004690C(void *buffer, s32 sectorWords);
extern void func_80034EF8(void);
extern void func_80034F38(s32 error);
extern u8 D_80115620[];







INCLUDE_ASM("asm/us/main/nonmatchings/25000", func_80034880);

void func_80034940(void) {
    D_80114B80.flags |= 2;
    func_800349A8();
}

void func_80034970(void) {
    D_80114B80.flags &= ~2u;
    func_80034550(0);
}

extern s32 func_80033B4C(VfsReadRequest *request);
void func_800349A8(void) {
    SortInsertList *queue = &D_80114B80.pending;
    if (queue->count != 0 && !(D_80114B80.flags & 0x20000000u) &&
        (D_80114B80.flags & 6u) == 6u) {
        func_80033B4C((VfsReadRequest *)queue->head);
    }
}

/* func_800349F4 is an internal call/epilogue label of func_800349A8. */

INCLUDE_ASM("asm/us/main/nonmatchings/25000", func_80034A0C);

INCLUDE_ASM("asm/us/main/nonmatchings/25000", func_80034A9C);

void func_80034AEC(u32 event, u8 *result) {
    if ((event & 0xFF) != 2) {
        func_80034F38(0x211);
        return;
    }
    func_80046DDC(0);
    func_8004625C(D_80116620.ready, -1);
}

void func_80034B38(u32 event, u32 opaque, u8 *result) {
    if ((event & 0xFFu) != 1) {
        func_80034F38(0x224);
        return;
    }
    if (--D_80116620.sectors == 0) {
        func_80046DDC(func_80034EF8);
    }
    func_8004690C(D_80116620.destination, 0x200);
    if (D_80116620.sectors == 0) {
        func_800462E0();
    } else {
        D_80116620.destination += 0x800;
    }
}

extern u8 D_80115E20[0x800];

void func_80034BE0(u32 event, u32 opaque, u8 *result) {
    if ((event & 0xFFu) != 1) {
        func_80034F38(0x23D);
        return;
    }
    if (--D_80116620.sectors != 0) {
        func_8004690C(D_80116620.destination, 0x200);
        D_80116620.destination += 0x800;
    } else {
        func_80046DDC(func_80034EF8);
        func_8004690C(D_80115E20, (D_80116620.tailBytes + 3) / 4);
        func_800462E0();
    }
}

extern u8 D_80115E20[0x800];
extern void func_800341F8(void);

void func_80034C94(void) {
    func_8003DF5C(D_80116620.destination, D_80115E20, D_80116620.tailBytes);
    func_800341F8();
}

INCLUDE_ASM("asm/us/main/nonmatchings/25000", func_80034CD0);

INCLUDE_ASM("asm/us/main/nonmatchings/25000", func_80034DA4);

INCLUDE_ASM("asm/us/main/nonmatchings/25000", func_80034DD4);

void func_80034E5C(u32 event, u32 opaque, u8 *result) {
    if ((event & 0xFF) != 1) {
        func_80034F38(0x2C7);
        return;
    }
    func_80046DDC(func_80034EF8);
    func_8004690C(D_80115620, 0x200);
    func_800462E0();
}

extern void func_800341F8(void);

void func_80034EB4(void) {
    func_8003DF5C(D_80114B80.current->buffer, D_80116620.head, D_80116620.headBytes);
    func_800341F8();
}

void func_80034EF8(void) {
    func_80046DDC(0);
    D_80114B80.flags |= 1u;
    D_80114B80.flags &= 0x7FFFFFFFu;
}

void func_80034F38(s32 error) {
    D_8006438C(D_800194BC, error);
    func_800462E0();
    D_80114B80.flags |= 0x40000000u;
}

INCLUDE_ASM("asm/us/main/nonmatchings/25000", func_80034F80);

void func_80034FE8(u32 opaqueIncomingWord) {
}

INCLUDE_ASM("asm/us/main/nonmatchings/25000", func_80034FF0);
