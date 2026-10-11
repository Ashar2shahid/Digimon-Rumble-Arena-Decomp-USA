#include "common.h"
#include "render_context.h"
#include "game_lists.h"

#pragma interface
class Component {
public:
    void *field0;
    char padding[0x20];
    int field24;
    int field28;
    int field2C;
    int field30;
    int field34;
    int field38;
    int field3C;
    int field40;
    int field44;
    Component();
};


class Entry {
public:
    Entry *next;
    Entry *prev;
    int field8;
    char data[0x44];
    unsigned int field50;
    virtual void first() const;
    virtual unsigned int second(int);
    virtual void third(int);
    virtual ~Entry();
};

class ListRoot : public Entry {
public:
    Entry *first;
    Entry *last;
    virtual ~ListRoot();
};

extern "C" {

void func_8001F8E4(RECT *target);

/* Clip a rectangle within the inactive display buffer. */
void func_8001F804(RECT *target, s32 x, s32 y, s32 width, s32 height) {
    s32 bufferWidth;
    s32 bufferHeight;
    func_8001F8E4(target);
    bufferWidth = target->w;
    bufferHeight = target->h;
    if (x < 0) {
        x = 0;
    } else if (x > bufferWidth - 1) {
        x = bufferWidth - 1;
    }
    if (y < 0) {
        y = 0;
    } else if (y > bufferHeight - 1) {
        y = bufferHeight - 1;
    }
    if (bufferWidth < (s32)((u32)x + (u32)width)) {
        width = bufferWidth - x;
    }
    if (bufferHeight < (s32)((u32)y + (u32)height)) {
        height = bufferHeight - y;
    }
    target->w = width;
    target->h = height;
    target->x += x;
    target->y += y;
}

extern RenderContext *D_800641A4;

void func_8001F8E4(RECT *target) {
    RenderContext *state = D_800641A4;
    *target = state->display[state->active ^ 1u].disp;
}

DISPENV *func_8001F92C(void) {
    RenderContext *state = D_800641A4;
    return &state->display[state->active];
}

extern void func_80058060(RECT *area, void *arg);

void func_8001F950(RenderContext *state, RECT *target, void *arg) {
    *target = state->display[state->active].disp;
    func_80058060(target, arg);
}

RenderContext *func_8001F9AC(void) {
    return D_800641A4;
}


}

Component::Component() {
    field24 = 0x1000;
    field28 = 0;
    field2C = 0x1000;
    field30 = 0;
    field34 = 0x1000;
    field38 = 0;
    field3C = 0;
    field40 = 0;
    field0 = 0;
    field44 = 0;
}
__asm__(
    ".globl func_8001F9B8\n"
    ".set func_8001F9B8, __9Component"
);

extern "C" {
INCLUDE_ASM("asm/us/main/nonmatchings/10004", func_8001F9EC);

INCLUDE_ASM("asm/us/main/nonmatchings/10004", func_8001FACC);

}

Entry::~Entry() {
    next->prev = prev;
    prev->next = next;
    next = this;
    prev = this;
}
__asm__(
    ".globl func_8001FBA4\n"
    ".set func_8001FBA4, _._5Entry\n"
    ".set _vt.5Entry, D_80010564\n"
    ".set __builtin_delete, func_8002B3D0"
);

extern "C" {
INCLUDE_ASM("asm/us/main/nonmatchings/10004", func_8001FBFC);
}

ListRoot::~ListRoot() {
    Entry *node = first;
    Entry *end = (Entry *) ((char *) this + 0x58);
    while (node != end) {
        Entry *next = node->next;
        if (node) {
            delete node;
        }
        node = next;
    }
    Entry *firstNode = first;
    firstNode->prev = last;
    Entry *sentinel = (Entry *) ((char *) this + 0x58);
    sentinel->prev->next = first;
    first = sentinel;
    last = sentinel;
}
__asm__(
    ".globl func_8001FC58\n"
    ".set func_8001FC58, _._8ListRoot\n"
    ".set _vt.8ListRoot, D_80010534"
);

extern "C" {

ListRoot *func_8001FD10(ListRoot *root, Entry *entry) {
    Entry *last = root->last;
    entry->prev = last;
    entry->next = last->next;
    last->next->prev = entry;
    last->next = entry;
    return root;
}

void func_8001FD40(ListRoot *root) {
    Entry *node = (Entry *) root->first;
    Entry *end = (Entry *) ((char *) root + 0x58);
    root->field8 = 0;
    while (node != end) {
        Entry *next = node->next;
        node->first();
        node = next;
    }
}

unsigned int func_8001FD9C(ListRoot *root, unsigned int arg) {
    Entry *node = root->first;
    Entry *end = (Entry *) ((char *) root + 0x58);
    unsigned int anyZero = 0;
    while (node != end) {
        Entry *next = node->next;
        unsigned int value = node->second(arg);
        unsigned int zero = 0;
        if (root->field50 & 1) {
            goto flags;
        }
        zero = value < 1;
    flags:
        anyZero |= zero;
        unsigned int flags = node->field50;
        node->field50 = (flags & ~2u) | (((flags & 1u) | (value != 0)) << 1);
        node = next;
        anyZero = anyZero != 0;
    }
    unsigned int result = (anyZero ^ 1u) & 1u;
    root->field50 = (root->field50 & ~2u) | (result << 1);
    return result;
}

void func_8001FE8C(Entry *entry, int arg) {
    if (!entry->second(arg)) {
        entry->third(arg);
    }
}

int func_80026CE0(void);

void func_8001FEF8(ListRoot *root, int arg) {
    Entry *node = root->first;
    Entry *end = (Entry *) ((char *) root + 0x58);
    while (node != end) {
        if (func_80026CE0() != 0) {
            break;
        }
        unsigned int flags = node->field50;
        Entry *next = node->next;
        if (((flags >> 1) & 1) == 0) {
            node->third(arg);
        }
        node = next;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/10004", func_8001FF8C);
}
