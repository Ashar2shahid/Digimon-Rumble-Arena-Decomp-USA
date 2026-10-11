#include "game_rotation.h"
#include "common.h"
#include "game_vector_words.h"
#include "game_input.h"

extern void func_8002447C(void *, s32, s32, s32);
void func_80026800(void *target, const s16 *components) {
    func_8002447C(target, components[0], components[1], components[2]);
}

extern void func_800245B8(void *, s32, s32, s32);
void func_80026830(void *target, const s32 *components) {
    func_800245B8(target, components[0], components[1], components[2]);
}

void func_80026860(void *target, const s16 *components) {
    func_800245B8(target, components[0], components[1], components[2]);
}

extern void func_80024CA8(s32, s32);

void func_80026890(s32 a0) {
    func_80024CA8(a0, a0);
}

extern void func_80024D1C(s32, s32);

void func_800268B0(s32 a0) {
    func_80024D1C(a0, a0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/17000", func_800268D0);

MathWords2 *func_80026918(MathWords2 *dst, const MathWords2 *src) {
    u32 first = src->words[0];
    u32 second = src->words[1];
    dst->words[0] = first;
    dst->words[1] = second;
    return dst;
}

typedef struct Pair32 { u32 first; u32 second; } Pair32;
extern Pair32 *func_80025D28(Pair32 *, void *, void *);

void func_80026930(Pair32 *a0, void *a1) {
    func_80025D28(a0, a0, a1);
}

Pair32 *func_80026954(Pair32 *destination, void *second, void *third) {
    Pair32 temporary;
    Pair32 *result = func_80025D28(&temporary, second, third);
    *destination = *result;
    return destination;
}

u32 *func_80026990(u32 *value) {
    value[0] = 0;
    value[1] = 0x10000000;
    return value;
}

extern void func_80025658(void *, void *);
void func_800269A4(void *value) { func_80025658(value, value); }

void func_800269C4(RotationQuaternion *value) { func_80025750(value, value); }

extern void func_80025784(void *, void *, void *, void *);
void func_800269E4(void *value, void *second, void *third) {
    func_80025784(value, value, second, third);
}

s32 func_80026A10(u32 index) { return D_8001093C[index & 0xFFF].cos; }

s16 func_80026A30(u32 index) { return D_8001093C[index & 0xFFF].sin; }

u32 *func_80026A50(u32 *destination, u32 value) {
    *destination = value;
    return destination;
}

INCLUDE_ASM("asm/us/main/nonmatchings/17000", func_80026A5C);

typedef struct ColorTarget ColorTarget;
typedef struct ColorSource { u32 reserved; u32 *color; } ColorSource;
extern void func_80026B4C(ColorTarget *, u32 *);
void func_80026B28(ColorTarget *destination, const ColorSource *source) {
    func_80026B4C(destination, source->color);
}

struct ColorTarget { u32 flags; u32 color; u32 unused; u32 *word; };
void func_80026B4C(ColorTarget *target, u32 *source) {
    u32 *word = target->word;
    u32 sourceWord = *source;
    u32 color = target->color;
    u32 oldWord = *word;
    *word = (oldWord & 0xFF000000) | (sourceWord & 0xFFFFFF);
    *source = (*source & 0xFF000000) | (color & 0xFFFFFF);
}

s32 func_80026B90(u32 *a0) { return a0[1]; }
s32 func_80026B9C(u32 *a0) { return a0[5]; }
s32 func_80026BA8(u32 *a0) { return a0[4]; }
s32 func_80026BB4(u32 *a0) { return a0[2]; }
s32 func_80026BC0(u32 *a0) { return a0[2]; }
s32 func_80026BCC(u32 *a0) { return a0[3]; }
s32 func_80026BD8(u32 *a0) { return ((u32)a0[0]) >> 31; }
s32 func_80026BE4(s32 *a0) { return *a0 < 0 ? (s32)(0u - (u32)*a0) : *a0; }

extern u32 D_800641B0;
extern u32 D_800641B4;
extern u32 D_800641B8;
extern u32 D_800641C0;
extern u32 D_800641BC;
typedef struct EndpointPair { u32 values[2]; } EndpointPair;
extern EndpointPair D_800641C4;
extern EndpointPair D_800641CC;
void func_80026C00(u32 base, u32 length) {
    u32 half = (length & ~3u) >> 1;
    D_800641C4.values[0] = base;
    D_800641B8 = base;
    base += half;
    D_800641C4.values[1] = base;
    D_800641CC.values[0] = base;
    D_800641C0 = base;
    base += half;
    D_800641BC = 0;
    D_800641CC.values[1] = base;
}

s32 func_80026C38(void) {
    u32 index = D_800641BC;
    u32 start = D_800641C4.values[index];
    u32 used = D_800641B8 - start;
    u32 size = D_800641C0 - start;
    index ^= 1;
    D_800641BC = index;
    D_800641B8 = D_800641C4.values[index];
    D_800641C0 = D_800641CC.values[index];
    return (s32)(used * 10000u) / (s32)size;
}

s32 func_80026CBC(void) {
    return D_800641B8 > D_800641C0 ? -1 : 0;
}

s32 func_80026CE0(void) {
    return (s32)(D_800641C0 - D_800641B8) < 0x1000;
}

u32 func_80026CF8(void) {
    return D_800641C4.values[0];
}

u32 func_80026D04(u32 increment) {
    u32 old = D_800641B8;
    D_800641B8 = old + increment;
    return old;
}

void func_80026D1C(u32 value) {
    D_800641B0 = value == 1;
}

void func_80026D30(u32 value) {
    D_800641B4 = value == 1;
}

extern u8 D_80114214[];
extern u32 D_80114344;
extern u32 D_80114210;
extern void func_80027118(void *, s32, s32);
void *func_80026D44(void *context) {
    s32 index = 0;
    u8 *entry = D_80114214;
    D_80114344 = 0;
    D_80114210 = (u32)context;
    do {
        func_80027118(entry, index, 0);
        index++;
        entry += 0x98;
    } while (index < 2);
    return context;
}

extern void func_8002B3D0(void *);
void func_80026DB4(void *value, u32 flags) {
    if (flags & 1) func_8002B3D0(value);
}

extern void func_8005BC9C(void *, void *);
extern void func_8005BB6C(void);
void func_80026DDC(void) {
    func_8005BC9C(D_80114214, D_80114214 + 0x98);
    func_8005BB6C();
}

void func_80026E0C(s32 unused, u32 second, u32 third) {
    u8 *entry = D_80114214;
    s32 remaining = 1;
    do {
        func_80027588(entry, second, third);
        remaining--;
        entry += 0x98;
    } while (remaining >= 0);
}

extern void func_80027170(void *);
void func_80026E70(void) {
    u8 *entry = D_80114214;
    s32 remaining = 1;
    do {
        func_80027170(entry);
        remaining--;
        entry += 0x98;
    } while (remaining >= 0);
}

extern void func_800271BC(void *);
extern void func_80027214(void *);
void func_80026EB4(void *unused_context) {
    if (D_80114344 == 0) {
        u8 *entry = D_80114214;
        s32 remaining = 1;
        do {
            func_800271BC(entry);
            func_80027214(entry);
            remaining--;
            entry += 0x98;
        } while (remaining >= 0);
    }
}

extern u8 D_8011427C[];
extern void func_80027980(u8 *, u32, u8, u8, u32, s32);
void func_80026F0C(void *unused, s32 index, u32 value, u32 firstByte,
                   u8 secondByte, u32 fifth, s32 sixth) {
    func_80027980(D_8011427C + index * 0x98, value, firstByte, secondByte, fifth, sixth);
}

s32 func_80026F68(s32 unused, s32 selector, s32 offset) {
    if (selector < 0) {
        u32 combined = 0;
        u8 *entry = D_80114214 + offset;
        s32 remaining = 1;
        do {
            combined |= *(u32 *)entry;
            entry += 0x98;
            remaining--;
        } while (remaining >= 0);
        return func_800271DC(combined);
    }
    return *(s32 *)(D_80114214 + offset + selector * 0x98);
}

s32 func_80026FE4(s32 unused, s32 selector) {
    return func_80026F68(unused, selector, 60);
}

/* Historical label on the return delay slot at the old source boundary. */
__asm__(".globl func_80027000\n.set func_80027000, func_80026FE4 + 0x1C\n.size func_80027000, 0x4");

