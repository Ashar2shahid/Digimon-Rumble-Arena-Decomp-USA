#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/12800", func_80022000);

s32 func_80022008(void *a0, void *a1) {
    return *(u32 *)((u8 *)a0 + 4) - *(u32 *)((u8 *)a1 + 4);
}

s32 func_80022018(void *a0) {
    u32 *words = (u32 *)a0;

    if (words[0] != 0x41) {
        return 0;
    }
    return words[2];
}

typedef struct T24C {
    u32 tag;
    u32 f4;
    u32 count;
    u8 data[1];
} T24C;

void *func_8002203C(T24C *a0, u32 a1) {
    u8 *p = a0->data;

    if (a0->tag != 0x41) {
        return NULL;
    }
    if (a1 >= a0->count) {
        return NULL;
    }
    return p + a1 * 28;
}

INCLUDE_ASM("asm/us/main/nonmatchings/12800", func_80022080);



void func_80022184(u8 *a0, u32 a1) {
    if (a1 == 0) return;
    do {
        a1--;
        *(u16 *)(a0 + 6) |= 0x4000;
        *(u16 *)(a0 + 0xA) |= 0x10;
        a0 += 0x18;
    } while (a1 != 0);
}

void func_800221B8(u8 *a0, u32 a1) {
    if (a1 == 0) return;
    do {
        a1--;
        *(u16 *)(a0 + 6) |= 0x4000;
        *(u16 *)(a0 + 0xA) |= 0x10;
        a0 += 0x1C;
    } while (a1 != 0);
}

void func_800221EC(u8 *a0, u32 a1) {
    if (a1 == 0) return;
    do {
        a1--;
        *(u16 *)(a0 + 6) |= 0x4000;
        *(u16 *)(a0 + 0xA) |= 0x10;
        a0 += 0x20;
    } while (a1 != 0);
}

void func_80022220(u8 *a0, u32 a1) {
    if (a1 == 0) return;
    do {
        a1--;
        *(u16 *)(a0 + 6) |= 0x4000;
        *(u16 *)(a0 + 0xA) |= 0x10;
        a0 += 0x20;
    } while (a1 != 0);
}

void func_80022254(u8 *a0, u32 a1) {
    if (a1 == 0) return;
    do {
        a1--;
        *(u16 *)(a0 + 6) |= 0x4000;
        *(u16 *)(a0 + 0xA) |= 0x10;
        a0 += 0x1C;
    } while (a1 != 0);
}

void func_80022288(u8 *a0, u32 a1) {
    if (a1 == 0) return;
    do {
        a1--;
        *(u16 *)(a0 + 6) |= 0x4000;
        *(u16 *)(a0 + 0xA) |= 0x10;
        a0 += 0x24;
    } while (a1 != 0);
}

void func_800222BC(u8 *a0, u32 a1) {
    if (a1 == 0) return;
    do {
        a1--;
        *(u16 *)(a0 + 6) |= 0x4000;
        *(u16 *)(a0 + 0xA) |= 0x10;
        a0 += 0x24;
    } while (a1 != 0);
}

void func_800222F0(u8 *a0, u32 a1) {
    if (a1 == 0) return;
    do {
        a1--;
        *(u16 *)(a0 + 6) |= 0x4000;
        *(u16 *)(a0 + 0xA) |= 0x10;
        a0 += 0x2C;
    } while (a1 != 0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/12800", func_80022324);

typedef struct TmdF3BoundsPrim {
    u32 header;
    u8 red, green, blue, code;
    u16 normal;
    u16 vertex0, vertex1, vertex2;
} TmdF3BoundsPrim;

typedef struct TmdG3BoundsPrim {
    u32 header;
    u8 red, green, blue, code;
    u16 normal0, vertex0, normal1, vertex1, normal2, vertex2;
} TmdG3BoundsPrim;

typedef struct TmdNG3BoundsPrim {
    u32 header;
    u32 color0, color1, color2;
    u16 vertex0, vertex1, vertex2;
} TmdNG3BoundsPrim;

typedef struct TmdF4BoundsPrim {
    u32 header;
    u8 red, green, blue, code;
    u16 normal;
    u16 vertex0, vertex1, vertex2, vertex3;
} TmdF4BoundsPrim;

typedef struct TmdBoundsVertex {
    s16 x, y, z, pad;
} TmdBoundsVertex;

typedef struct TmdBounds {
    s16 minX, minY, minZ;
    s16 maxX, maxY, maxZ;
} TmdBounds;

extern void func_80022F90(TmdBounds *, const TmdBoundsVertex *);

void func_80022410(const TmdF3BoundsPrim *primitive, u32 count,
                   const TmdBoundsVertex *vertices, TmdBounds *bounds) {
    const TmdBoundsVertex *v0;
    const TmdBoundsVertex *v1;
    const TmdBoundsVertex *v2;
    while (count != 0) {
        v0 = &vertices[primitive->vertex0];
        v1 = &vertices[primitive->vertex1];
        v2 = &vertices[primitive->vertex2];
        func_80022F90(bounds, v0);
        func_80022F90(bounds, v1);
        func_80022F90(bounds, v2);
        count--;
        primitive++;
    }
}
void func_800224B8(const TmdG3BoundsPrim *primitive, u32 count,
                   const TmdBoundsVertex *vertices, TmdBounds *bounds) {
    const TmdBoundsVertex *v0;
    const TmdBoundsVertex *v1;
    const TmdBoundsVertex *v2;
    while (count != 0) {
        v0 = &vertices[primitive->vertex0];
        v1 = &vertices[primitive->vertex1];
        v2 = &vertices[primitive->vertex2];
        func_80022F90(bounds, v0);
        func_80022F90(bounds, v1);
        func_80022F90(bounds, v2);
        count--;
        primitive++;
    }
}

typedef struct TmdNF3BoundsPrim {
    u32 header;
    u8 red, green, blue, code;
    u16 vertex0, vertex1, vertex2;
} TmdNF3BoundsPrim;

void func_80022560(const TmdNF3BoundsPrim *primitive, u32 count,
                   const TmdBoundsVertex *vertices, TmdBounds *bounds) {
    const TmdBoundsVertex *v0;
    const TmdBoundsVertex *v1;
    const TmdBoundsVertex *v2;
    while (count != 0) {
        v0 = &vertices[primitive->vertex0];
        v1 = &vertices[primitive->vertex1];
        v2 = &vertices[primitive->vertex2];
        func_80022F90(bounds, v0);
        func_80022F90(bounds, v1);
        func_80022F90(bounds, v2);
        count--;
        primitive++;
    }
}





void func_80022608(const TmdNG3BoundsPrim *primitive, u32 count,
                   const TmdBoundsVertex *vertices, TmdBounds *bounds) {
    const TmdBoundsVertex *v0;
    const TmdBoundsVertex *v1;
    const TmdBoundsVertex *v2;
    while (count != 0) {
        v0 = &vertices[primitive->vertex0];
        v1 = &vertices[primitive->vertex1];
        v2 = &vertices[primitive->vertex2];
        func_80022F90(bounds, v0);
        func_80022F90(bounds, v1);
        func_80022F90(bounds, v2);
        count--;
        primitive++;
    }
}

void func_800226B0(const TmdF4BoundsPrim *primitive, u32 count,
                   const TmdBoundsVertex *vertices, TmdBounds *bounds) {
    const TmdBoundsVertex *v0;
    const TmdBoundsVertex *v1;
    const TmdBoundsVertex *v2;
    const TmdBoundsVertex *v3;
    while (count != 0) {
        v0 = &vertices[primitive->vertex0];
        v1 = &vertices[primitive->vertex1];
        v2 = &vertices[primitive->vertex2];
        v3 = &vertices[primitive->vertex3];
        func_80022F90(bounds, v0);
        func_80022F90(bounds, v1);
        func_80022F90(bounds, v2);
        func_80022F90(bounds, v3);
        count--;
        primitive++;
    }
}

typedef struct TmdG4BoundsPrim {
    u32 header;
    u8 red, green, blue, code;
    u16 normal0, vertex0, normal1, vertex1, normal2, vertex2, normal3, vertex3;
} TmdG4BoundsPrim;

void func_80022778(const TmdG4BoundsPrim *primitive, u32 count,
                   const TmdBoundsVertex *vertices, TmdBounds *bounds) {
    const TmdBoundsVertex *v0;
    const TmdBoundsVertex *v1;
    const TmdBoundsVertex *v2;
    const TmdBoundsVertex *v3;
    while (count != 0) {
        v0 = &vertices[primitive->vertex0];
        v1 = &vertices[primitive->vertex1];
        v2 = &vertices[primitive->vertex2];
        v3 = &vertices[primitive->vertex3];
        func_80022F90(bounds, v0);
        func_80022F90(bounds, v1);
        func_80022F90(bounds, v2);
        func_80022F90(bounds, v3);
        count--;
        primitive++;
    }
}
