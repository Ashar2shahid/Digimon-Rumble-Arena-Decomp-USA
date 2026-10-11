#include "common.h"
#pragma interface
struct TreeLink {
    TreeLink *next;
    TreeLink *prev;
};
struct TreeNode {
    TreeLink link;
    TreeNode *f8;
    TreeNode *fC;
    u32 key;
    s16 x;
    s16 y;
};
class TreeRoot {
public:
    TreeNode *f0;
    TreeNode *f4;
    u32 f8;
    TreeLink recency;
public:
    virtual void update(s32, s32, s32) = 0;
};
extern "C" {
extern TreeNode *func_8002E1F4(TreeRoot *, s32);
extern void func_8002E2EC(TreeRoot *, TreeNode *);
extern void func_8002E248(TreeRoot *, TreeNode *);
extern void func_8002E2A4(TreeRoot *, TreeNode *, s32);




INCLUDE_ASM("asm/us/main/nonmatchings/1E800", func_8002E024);

extern u8 D_80019308[];
extern void func_8002B3F8(void *);
extern void func_8002B3D0(void *);

void func_8002E074(TreeRoot *root, u32 flags) {
    *(void **)((u8 *)root + 0x14) = D_80019308;
    if (root->f4 != 0) {
        func_8002B3F8(root->f4);
    }
    if (flags & 1) {
        func_8002B3D0(root);
    }
}

TreeNode *func_8002E160(TreeRoot *root, s32 key);

void func_8002E0D0(TreeRoot *root, u32 low, u32 high) {
    if (high < low) {
        return;
    }
    if (low == high) {
        func_8002E160(root, high);
        return;
    }
    u32 mid = (low + high) >> 1;
    func_8002E160(root, mid);
    func_8002E0D0(root, low, mid - 1);
    func_8002E0D0(root, mid + 1, high);
}

TreeNode *func_8002E160(TreeRoot *root, s32 key) {
    TreeNode *node = func_8002E1F4(root, key);
    if (!node) {
        node = (TreeNode *)root->recency.prev;
        func_8002E2EC(root, node);
        func_8002E2A4(root, node, key);
        root->update(node->x, node->y, key);
    }
    func_8002E248(root, node);
    return node;
}


TreeNode *func_8002E1F4(TreeRoot *root, s32 key) {
    TreeNode *node = root->f0;
    u32 node_key;
    while (node != 0) {
        node_key = node->key;
        if (node_key == (u32)key) {
            return node;
        }
        if (node_key < (u32)key) {
            node = node->f8;
        } else {
            node = node->fC;
        }
    }
    return node;
}

void func_8002E248(TreeRoot *root, TreeNode *node) {
    TreeLink *sentinel = &root->recency;
    TreeLink *entry = &node->link;
    if (root->recency.next != entry) {
        entry->prev->next = entry->next;
        entry->next->prev = entry->prev;
        entry->prev = sentinel;
        entry->next = root->recency.next;
        root->recency.next->prev = entry;
        root->recency.next = entry;
    }
}

void func_8002E2A4(TreeRoot *root, TreeNode *node, s32 key) {
    node->f8 = 0;
    node->fC = 0;
    node->key = (u32)key;
    TreeNode **link = &root->f0;
    while (*link != 0) {
        TreeNode *current = *link;
        if (current->key < (u32)key) {
            link = &current->f8;
        } else {
            link = &current->fC;
        }
    }
    *link = node;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1E800", func_8002E2EC);

TreeNode *func_8002E3E4(TreeNode **link) {
    TreeNode *node;
    while ((*link)->f8 != 0) {
        link = &(*link)->f8;
    }
    node = *link;
    *link = node->fC;
    return node;
}

s32 func_8002E434(s16 *a0, s32 a1, s32 a2) {
    s32 t1;
    s32 t2;
    s32 r1;
    s32 r2;

    t1 = 1 << a1;
    t2 = 1 << a2;
    r1 = (((-t1) & (a0[0] + a0[2] + t1 - 1)) - ((-t1) & a0[0])) >> a1;
    r2 = (((-t2) & (a0[1] + a0[3] + t2 - 1)) - ((-t2) & a0[1])) >> a2;
    return r1 * r2;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1E800", func_8002E4A0);

s16 func_8002E5A8(s16 *arg0) {
    return arg0[0xA];
}

s16 func_8002E5B4(s16 *arg0) {
    return arg0[0xB];
}

INCLUDE_ASM("asm/us/main/nonmatchings/1E800", func_8002E5C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1E800", func_8002E688);

INCLUDE_ASM("asm/us/main/nonmatchings/1E800", func_8002E6B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1E800", func_8002E700);
}
