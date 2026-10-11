#include "common.h"

typedef struct TmdBoundsVertex { s16 x, y, z, pad; } TmdBoundsVertex;
typedef struct TmdBounds { s16 minX, minY, minZ, maxX, maxY, maxZ; } TmdBounds;

typedef struct TmdNF4BoundsPrim {
    u32 header; u32 color; u16 vertex0, vertex1, vertex2, vertex3;
} TmdNF4BoundsPrim;

typedef struct TmdNG4BoundsPrim {
    u32 header; u32 color0, color1, color2, color3; u16 vertex0, vertex1, vertex2, vertex3;
} TmdNG4BoundsPrim;

typedef struct TmdTF3BoundsPrim {
    u32 header; u32 texture0, texture1, texture2; u16 normal; u16 vertex0, vertex1, vertex2;
} TmdTF3BoundsPrim;

typedef struct TmdTG3BoundsPrim {
    u32 header; u32 texture0, texture1, texture2; u16 normal0, vertex0, normal1, vertex1, normal2, vertex2;
} TmdTG3BoundsPrim;

typedef struct TmdTNF3BoundsPrim {
    u32 header; u32 color; u32 texture0, texture1, texture2; u16 vertex0, vertex1, vertex2;
} TmdTNF3BoundsPrim;

typedef struct TmdTNG3BoundsPrim {
    u32 header; u32 color0, color1, color2; u32 texture0, texture1, texture2; u16 vertex0, vertex1, vertex2;
} TmdTNG3BoundsPrim;

typedef struct TmdTF4BoundsPrim {
    u32 header; u32 texture0, texture1, texture2, texture3; u16 normal; u16 vertex0, vertex1, vertex2, vertex3;
} TmdTF4BoundsPrim;

typedef struct TmdTG4BoundsPrim {
    u32 header; u32 texture0, texture1, texture2, texture3; u16 normal0, vertex0, normal1, vertex1, normal2, vertex2, normal3, vertex3;
} TmdTG4BoundsPrim;

typedef struct TmdTNF4BoundsPrim {
    u32 header; u32 color; u32 texture0, texture1, texture2, texture3; u16 vertex0, vertex1, vertex2, vertex3;
} TmdTNF4BoundsPrim;

typedef struct TmdTNG4BoundsPrim {
    u32 header; u32 color0, color1, color2, color3; u32 texture0, texture1, texture2, texture3; u16 vertex0, vertex1, vertex2, vertex3;
} TmdTNG4BoundsPrim;

void func_80022F90(TmdBounds *bounds, const TmdBoundsVertex *vertex);

void func_80022840(const TmdNF4BoundsPrim *primitive, u32 count,
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

void func_80022908(const TmdNG4BoundsPrim *primitive, u32 count,
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

void func_800229D0(const TmdTF3BoundsPrim *primitive, u32 count,
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

void func_80022A78(const TmdTG3BoundsPrim *primitive, u32 count,
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

void func_80022B20(const TmdTNF3BoundsPrim *primitive, u32 count,
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

void func_80022BC8(const TmdTNG3BoundsPrim *primitive, u32 count,
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

void func_80022C70(const TmdTF4BoundsPrim *primitive, u32 count,
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

void func_80022D38(const TmdTG4BoundsPrim *primitive, u32 count,
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

void func_80022E00(const TmdTNF4BoundsPrim *primitive, u32 count,
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

void func_80022EC8(const TmdTNG4BoundsPrim *primitive, u32 count,
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

void func_80022F90(TmdBounds *bounds, const TmdBoundsVertex *vertex) {
    s16 coordinate;
    coordinate = vertex->x;
    if (coordinate < bounds->minX) { bounds->minX = coordinate; }
    if (bounds->maxX < coordinate) { bounds->maxX = coordinate; }
    coordinate = vertex->y;
    if (coordinate < bounds->minY) { bounds->minY = coordinate; }
    if (bounds->maxY < coordinate) { bounds->maxY = coordinate; }
    coordinate = vertex->z;
    if (coordinate < bounds->minZ) { bounds->minZ = coordinate; }
    if (bounds->maxZ < coordinate) { bounds->maxZ = coordinate; }
}
