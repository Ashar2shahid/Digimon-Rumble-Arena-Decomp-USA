#include "common.h"
#include "game_printer_storage.h"

/* These helpers manipulate the raw 16-bit words of a GPU rectangle. */
typedef struct RectWords {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} RectWords;

typedef struct TilePacket {
    u32 tag;
    u8 red, green, blue, code;
    u16 x, y, width, height;
} TilePacket;

typedef struct LinePacket {
    u32 tag;
    u8 red, green, blue, code;
    s16 x0, y0, x1, y1, x2, y2;
    u32 pad;
} LinePacket;
extern u8 *func_80032D3C(void);

extern u32 D_800641B8;
extern u8 *func_80028078(void);
extern u8 *func_800280A0(u32);
extern void func_8005844C(u8 *, u8 *);
extern void func_8005851C(u8 *, const RectWords *);
extern void func_80032934(u8 *, RectWords *, s32, s32);
extern void func_80032A9C(u8 *, RectWords *, s32);
extern void func_80032A24(u8 *, RectWords *);


void func_80032870(void *self, u32 color) {
}

void func_80032878(void *self, s32 value) {
}

void func_80032880(u32 *self, u32 first, u32 second) {
    self[0] = first;
    self[1] = second;
}

INCLUDE_ASM("asm/us/main/nonmatchings/23000", func_8003288C);

void func_800328CC(void *object, u32 color) {
    PrinterPrefix *self = object;
    const PrinterCallbackTable *table = self->table;
    s32 adjustment = table->colorAdjustment;
    void (*callback)(void *, u32) = table->setColor;
    callback((u8 *)object + adjustment, color);
}

void func_80032900(void *object, s32 value) {
    PrinterPrefix *self = object;
    const PrinterCallbackTable *table = self->table;
    s32 adjustment = table->valueAdjustment;
    void (*callback)(void *, s32) = table->setValue;
    callback((u8 *)object + adjustment, value);
}

void func_80032934(u8 *ordering, RectWords *rect, s32 light, s32 dark) {
    LinePacket *topLeft = (LinePacket *)func_80032D3C();
    LinePacket *bottomRight = (LinePacket *)func_80032D3C();
    s16 x = rect->x;
    s16 y = rect->y;
    s16 right = rect->x + rect->width - 1;
    s16 bottom = rect->y + rect->height - 1;
    topLeft->red = light;
    topLeft->green = light;
    topLeft->blue = light;
    topLeft->x0 = right;
    topLeft->y0 = y;
    topLeft->x1 = x;
    topLeft->y1 = y;
    topLeft->x2 = x;
    topLeft->y2 = bottom;
    bottomRight->red = dark;
    bottomRight->green = dark;
    bottomRight->blue = dark;
    bottomRight->x0 = x;
    bottomRight->y0 = bottom;
    bottomRight->x1 = right;
    bottomRight->y1 = bottom;
    bottomRight->x2 = right;
    bottomRight->y2 = y;
    func_8005844C(ordering, (u8 *)bottomRight);
    func_8005844C(ordering, (u8 *)topLeft);
}

INCLUDE_ASM("asm/us/main/nonmatchings/23000", func_80032A24);

void func_80032A9C(u8 *ordering, RectWords *rect, s32 grey) {
    TilePacket *tile = (TilePacket *)func_80028078();
    tile->red = grey;
    tile->green = grey;
    tile->blue = grey;
    tile->x = rect->x;
    tile->y = rect->y;
    tile->width = rect->width;
    tile->height = rect->height;
    func_8005844C(ordering, (u8 *)tile);
}

void func_80032B1C(RectWords *rect) {
    rect->x++;
    rect->y++;
    rect->width -= 2;
    rect->height -= 2;
}

void func_80032B50(RectWords *rect) {
    rect->x--;
    rect->y--;
    rect->width += 2;
    rect->height += 2;
}

void func_80032B84(u8 *ordering, RectWords *rect) {
    func_80032934(ordering, rect, 0xFF, 0);
    func_80032B1C(rect);
    func_80032934(ordering, rect, 0xDF, 0x80);
    func_80032A9C(ordering, rect, 0xC0);
}

void func_80032BE8(u8 *ordering, RectWords *rect) {
    func_80032934(ordering, rect, 0, 0xFF);
    func_80032B1C(rect);
    func_80032934(ordering, rect, 0x80, 0xDF);
    func_80032A9C(ordering, rect, 0xC0);
}

void func_80032C4C(u8 *ordering, RectWords *rect) {
    RectWords frame = *rect;
    func_80032B50(&frame);
    func_80032934(ordering, &frame, 0, 0xDF);
    func_80032B50(&frame);
    func_80032934(ordering, &frame, 0xC0, 0xC0);
    func_80032B50(&frame);
    func_80032934(ordering, &frame, 0xC0, 0xC0);
    func_80032B50(&frame);
    func_80032934(ordering, &frame, 0xFF, 0x80);
    func_80032B50(&frame);
    func_80032934(ordering, &frame, 0xDF, 0);
    func_80032A24(ordering, rect);
}

INCLUDE_ASM("asm/us/main/nonmatchings/23000", func_80032D3C);

INCLUDE_ASM("asm/us/main/nonmatchings/23000", func_80032D70);

INCLUDE_ASM("asm/us/main/nonmatchings/23000", func_80032EE8);

INCLUDE_ASM("asm/us/main/nonmatchings/23000", func_80032F28);
