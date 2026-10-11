#include "common.h"
#include "title_factories.h"
#include "object_factory_api.h"

extern s32 func_8001CE40(void *owner, u8 *(*factory)(void), void *context, s32 mode);
extern s32 func_8001DED8(void *state);
extern u8 D_80064174[];
extern u8 D_8005F8B8[];

INCLUDE_ASM("asm/us/main/nonmatchings/D000", func_8001C800);

INCLUDE_ASM("asm/us/main/nonmatchings/D000", func_8001C8A8);
INCLUDE_ASM("asm/us/main/nonmatchings/D000", func_8001CAA8);


extern void func_8001D4F0(void *state);
extern void func_8001DF70(void *state);
extern u8 D_80064184[];

s32 func_8001CBE4(void *owner) {
    s32 result;
    for (;;) {
        u8 *state = D_8005F8B8;
        u8 *context;
        u8 *(*factory)(void);
        func_8001D4F0(state);
        factory = func_8001C3CC;
        context = D_80064174;
        result = func_8001CE40(owner, factory, context, 1);
        if (result < 0) {
            break;
        }
        if (result == 1) {
            func_8001DF70(state);
        }
        *(u32 *)(state + 0x50) = *(u32 *)D_8005F8B8 - 7U;
        func_8001CE40(owner, func_8001C434, context, 1);
        func_8001CE40(owner, func_8001C404, D_80064184, 0);
    }
    return 3;
}


INCLUDE_ASM("asm/us/main/nonmatchings/D000", func_8001CCC0);

INCLUDE_ASM("asm/us/main/nonmatchings/D000", func_8001CD28);


s32 func_8001CD84(void *owner) {
    func_8001CE40(owner, func_8001C52C, D_80064174, 0);
    if (func_8001DED8(D_8005F8B8) != 0) {
        func_8001CE40(owner, func_8001C580, D_80064174, 0);
    }
    return 3;
}

extern void func_8001D5C4(s32 *state);

void func_8001CDF4(void *owner) {
    for (;;) {
        func_8001D5C4((s32 *)D_8005F8B8);
        func_8001CE40(owner, func_8001C404, D_80064184, 0);
    }
}
INCLUDE_ASM("asm/us/main/nonmatchings/D000", func_8001CE40);

