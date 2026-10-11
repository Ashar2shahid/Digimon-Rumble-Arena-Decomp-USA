/* Reviewed base-constructor and priority-list interfaces. */
#ifndef GAME_BASE_API_H
#define GAME_BASE_API_H

#include "common.h"

/* Distinct from the eight-byte SortList and SortNode in game_sort.h. */
typedef struct PriorityList PriorityList;
typedef struct PriorityNode PriorityNode;

#ifdef __cplusplus
extern "C" {
#endif

u8 *func_8002BC9C(u8 *self, s32 value);
PriorityList *func_8002BB30(PriorityList *list, PriorityNode *node);
void func_8002BC1C(PriorityList *list, PriorityNode *node);

#ifdef __cplusplus
}
#endif

#endif
