#ifndef GAME_STEPPER_STATE_H
#define GAME_STEPPER_STATE_H
#include "common.h"
class Handler;
struct DispatchRecord {
    unsigned short f0, f2, f4, f6, f8, fa;
};
struct DispatchListNode {
    DispatchListNode *next;
    DispatchListNode *prev;
};
/* The group constructor initializes all six members. Remaining allocation
 * unit bits are unnamed padding, preserved by target bitfield writes. */
struct StepperGroupFlags {
    u32 wraps : 1;
    u32 childActive : 1;
    u32 childWasActive : 1;
    u32 currentOnly : 1;
    u32 closed : 1;
    u32 keepOpen : 1;
};
struct DispatchState {
    Handler *first;
    DispatchListNode *f4;
    s32 f8;
    DispatchRecord *record;
    StepperGroupFlags flags;
    Handler *handler;
    s32 value18;
    s32 closeValue;
};
typedef char StepperGroupFlags_size[(sizeof(StepperGroupFlags)==4)?1:-1];
static inline u8 stepperChildActive(DispatchState *state) {
    return state->flags.childActive;
}
static inline u8 stepperChildWasActive(DispatchState *state) {
    return state->flags.childWasActive;
}
static inline u8 stepperClosed(DispatchState *state) {
    return state->flags.closed;
}
static inline u8 stepperKeptOpen(DispatchState *state) {
    return state->flags.keepOpen;
}
#endif
