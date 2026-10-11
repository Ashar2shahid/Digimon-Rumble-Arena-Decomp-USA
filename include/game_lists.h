#ifndef GAME_LISTS_H
#define GAME_LISTS_H

#ifdef __cplusplus
class Entry;
class ListRoot;
extern "C" {
#else
typedef struct Entry Entry;
typedef struct ListRoot ListRoot;
#endif

ListRoot *func_8001FD10(ListRoot *root, Entry *entry);
void func_8001FE8C(Entry *entry, int argument);

#ifdef __cplusplus
}
#endif

#endif
