#include "common.h"
#include "game_stepper_state.h"

#pragma interface
class Handler {
    s32 fields[7]; // Legacy layout places the vptr at +0x1C.
public:
    virtual void fallback(s32, s32, s32) = 0;
    virtual s32 check(s32, s32, s32) = 0;
    virtual int method2() = 0;
    virtual int method3() = 0;
    virtual void callback8() = 0;
    virtual void callbackA() = 0;
    virtual bool test() = 0;
};

struct HandlerThunkTable {
    u8 reserved[0x38];
    s16 thisOffset38;
    s16 padding38;
    s32 (*invoke38)(void *, s32, s32, s32);
    s16 thisOffset40;
    s16 padding40;
    void (*invoke40)(void *, s32, s32, s32);
    s16 thisOffset;
    s16 padding;
    s32 (*invoke48)(void *, s32);
    s16 thisOffset50;
    s16 padding50;
    void (*invoke50)(void *, s32);
};
struct HandlerThunk {
    s32 fields[7];
    HandlerThunkTable *vtable;
};


extern "C" {
INCLUDE_ASM("asm/us/main/nonmatchings/1D000", func_8002C800);
s32 func_8002C810(DispatchState *state, s32 arg1) {
    HandlerThunk *handler = (HandlerThunk *)state->first;
    state->flags.closed = 0;
    return handler->vtable->invoke48((u8 *)handler + handler->vtable->thisOffset, arg1);
}
extern s32 func_8002D298(DispatchState *);
s32 func_8002C858(DispatchState *state, s32 arg1, s32 arg2, s32 arg3) {
    HandlerThunk *handler;

    if (func_8002D298(state) != 0) {
        return 0;
    }
    handler = (HandlerThunk *)state->first;
    return handler->vtable->invoke38((u8 *)handler + handler->vtable->thisOffset38,
                                    arg1, arg2, arg3);
}
void func_8002C8D4(DispatchState *state, s32 arg1) {
    HandlerThunk *handler;

    if (func_8002D298(state) == 0) {
        handler = (HandlerThunk *)state->first;
        handler->vtable->invoke40((u8 *)handler + handler->vtable->thisOffset40,
                                 arg1, 1, state->flags.childActive ^ 1);
    }
}
INCLUDE_ASM("asm/us/main/nonmatchings/1D000", func_8002C93C);
void func_8002C9A4(DispatchState *state) {
    DispatchListNode *node = state->f4;
    DispatchListNode *sentinel = (DispatchListNode *)&state->f4;

    while (node != sentinel) {
        DispatchListNode *next = node->next;
        if (node != 0) {
            HandlerThunk *handler = (HandlerThunk *)node;
            handler->vtable->invoke50((u8 *)handler + handler->vtable->thisOffset50, 3);
        }
        node = next;
    }
    state->handler = (Handler *)((u8 *)state + 4);
}
int func_8002CA28(void *arg0) {
    DispatchState *state = (DispatchState *)arg0;
    if (stepperChildActive(state) || stepperChildWasActive(state)) {
        return -1;
    }
    return 0;
}
INCLUDE_ASM("asm/us/main/nonmatchings/1D000", func_8002CA5C);
INCLUDE_ASM("asm/us/main/nonmatchings/1D000", func_8002CBC8);
int func_8002CD24(DispatchState *state, s32 arg1, s32 arg2) {
    state->handler->check(arg1, arg2, 0);
    if (state->first->check(arg1, arg2, 1)) {
        return 1;
    }
    state->flags.closed = 1;
    return 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1D000", func_8002CDC0);
INCLUDE_ASM("asm/us/main/nonmatchings/1D000", func_8002CEB4);
INCLUDE_ASM("asm/us/main/nonmatchings/1D000", func_8002CFB0);
}
