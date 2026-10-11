#ifndef GAME_PRINTER_STORAGE_H
#define GAME_PRINTER_STORAGE_H

#include "common.h"

/* Complete 0x30-byte ASM tables; only these two entries are typed here. */
typedef struct PrinterCallbackTable {
    u8 otherEntries[0x10];
    s16 colorAdjustment;
    u16 colorReserved;
    void (*setColor)(void *, u32);
    s16 valueAdjustment;
    u16 valueReserved;
    void (*setValue)(void *, s32);
    u8 otherTail[0x10];
} PrinterCallbackTable;

/* Initial subobject shared by the 0x28-byte text and 0x14-byte glyph printers. */
typedef struct PrinterPrefix {
    u32 cursor[2];
    const PrinterCallbackTable *table;
} PrinterPrefix;

typedef struct TextPrinterRecord {
    PrinterPrefix base;
    void *drawMode;
    void *fontCache;
    s32 textColor;
    s32 backgroundColor;
    s32 origin[2];
    u32 flags;
} TextPrinterRecord;

typedef struct GlyphPrinterRecord {
    PrinterPrefix base;
    void *drawMode;
    u32 color;
} GlyphPrinterRecord;

typedef char PrinterTableSizeCheck[sizeof(PrinterCallbackTable) == 0x30 ? 1 : -1];
typedef char PrinterPrefixSizeCheck[sizeof(PrinterPrefix) == 0xC ? 1 : -1];
typedef char TextPrinterSizeCheck[sizeof(TextPrinterRecord) == 0x28 ? 1 : -1];
typedef char GlyphPrinterSizeCheck[sizeof(GlyphPrinterRecord) == 0x14 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif

extern const PrinterCallbackTable D_8001936C;
extern const PrinterCallbackTable D_800193DC;
extern const PrinterCallbackTable D_80066760;

void func_80032304(void *, u32);
void func_8007A41C(void *, u32);
void *func_8007A3BC(u8 *, u8 *);
u8 *func_80032640(u8 *, u8 *);

#ifdef __cplusplus
}
#endif

#endif
