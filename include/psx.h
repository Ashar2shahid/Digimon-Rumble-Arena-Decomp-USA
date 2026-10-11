#ifndef PSX_H
#define PSX_H

/*
 * PlayStation GPU primitive / packet and GTE geometry types, reconstructed from the
 * PSY-Q 4.7 SDK headers (GTEREG.H, LIBGPU.H, LIBGTE.H) in
 * bin/cc1_revisions/rl47/INCLUDE/.  Field names and layout follow those headers
 * exactly (the retail game's packet builders depend on the byte offsets), but the
 * declarations are written in this repo's style (u8/s16/u32 from common.h).
 */

#include "common.h"

/* ------------------------------------------------------------------ GTE */

typedef struct {
    s16 m[3][3]; /* 3x3 rotation matrix */
    s32 t[3];    /* translation vector   */
} MATRIX;

typedef struct {
    s32 vx, vy;
    s32 vz, pad;
} VECTOR;

typedef struct {
    s16 vx, vy;
    s16 vz, pad;
} SVECTOR;

typedef struct {
    u8 r, g, b, cd;
} CVECTOR;

typedef struct {
    s16 vx, vy;
} DVECTOR;

/* -------------------------------------------------------------- libgpu */

typedef struct {
    s16 x, y; /* offset point on VRAM */
    s16 w, h; /* width and height     */
} RECT;

typedef struct {
    s32 x, y;
    s32 w, h;
} RECT32;

/* Ordering-table / primitive header tag (addr:24, len:8, then colour+code). */
typedef struct {
    unsigned addr : 24;
    unsigned len : 8;
    u8 r0, g0, b0, code;
} P_TAG;

typedef struct {
    u8 r0, g0, b0, code;
} P_CODE;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
} POLY_F3;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} POLY_F4;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad1;
} POLY_FT3;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad1;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad2;
} POLY_FT4;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 r1, g1, b1, pad1;
    s16 x1, y1;
    u8 r2, g2, b2, pad2;
    s16 x2, y2;
} POLY_G3;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 r1, g1, b1, pad1;
    s16 x1, y1;
    u8 r2, g2, b2, pad2;
    s16 x2, y2;
    u8 r3, g3, b3, pad3;
    s16 x3, y3;
} POLY_G4;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    u8 r1, g1, b1, p1;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    u8 r2, g2, b2, p2;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad2;
} POLY_GT3;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    u8 r1, g1, b1, p1;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    u8 r2, g2, b2, p2;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad2;
    u8 r3, g3, b3, p3;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad3;
} POLY_GT4;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
} LINE_F2;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 r1, g1, b1, p1;
    s16 x1, y1;
} LINE_G2;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    u32 pad;
} LINE_F3;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 r1, g1, b1, p1;
    s16 x1, y1;
    u8 r2, g2, b2, p2;
    s16 x2, y2;
    u32 pad;
} LINE_G3;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
    u32 pad;
} LINE_F4;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 r1, g1, b1, p1;
    s16 x1, y1;
    u8 r2, g2, b2, p2;
    s16 x2, y2;
    u8 r3, g3, b3, p3;
    s16 x3, y3;
    u32 pad;
} LINE_G4;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 w, h;
} SPRT;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
} SPRT_16;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
} SPRT_8;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
} TILE_16;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
} TILE_8;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
} TILE_1;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 w, h;
} TILE;

/* Drawing-environment / packet-control primitives. */
typedef struct {
    u32 tag;
    u32 code[15];
} DR_ENV;

typedef struct {
    u32 tag;
    u32 code[2];
} DR_MODE;

typedef struct {
    u32 tag;
    u32 code[2];
} DR_TWIN;

typedef struct {
    u32 tag;
    u32 code[2];
} DR_AREA;

typedef struct {
    u32 tag;
    u32 code[2];
} DR_TPAGE;

typedef struct {
    u32 tag;
    u32 code[5];
} DR_MOVE;

typedef struct {
    u32 tag;
    u32 code[3];
    u32 p[13];
} DR_LOAD;

/* TIM texture descriptor (libgpu.h). */
typedef struct {
    u32 mode;
    RECT *crect;
    u32 *caddr;
    RECT *prect;
    u32 *paddr;
} TIM_IMAGE;

typedef struct {
    RECT clip;
    s16 ofs[2];
    RECT tw;
    u16 tpage;
    u8 dtd;
    u8 dfe;
    u8 isbg;
    u8 r0, g0, b0;
    DR_ENV dr_env;
} DRAWENV;

typedef struct {
    RECT disp;
    RECT screen;
    u8 isinter;
    u8 isrgb24;
    u8 pad0, pad1;
} DISPENV;

#endif /* PSX_H */
