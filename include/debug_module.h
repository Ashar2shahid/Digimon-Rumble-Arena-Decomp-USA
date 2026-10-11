#ifndef DEBUG_MODULE_H
#define DEBUG_MODULE_H
#include "object_base.h"

typedef void *(*ModuleConstruct)(void);
typedef struct DebugModule {
    Func8002C3CCNode base;
    u32 reserved20;
    const char *name;
    ModuleConstruct construct;
    const char *overlayPath;
} DebugModule;
typedef char DebugModule_size_is_0x30[(sizeof(DebugModule) == 0x30) ? 1 : -1];

typedef struct DebugChoice {
    Func8002C3CCNode base;
    u32 reserved20;
    const char *name;
    const char **choices;
} DebugChoice;
typedef char DebugChoice_size_is_0x2C[(sizeof(DebugChoice) == 0x2C) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
void func_8002A010(void *context, ModuleConstruct construct, const char *overlayPath);
DebugModule *func_8002879C(DebugModule *self, const char *name, ModuleConstruct construct, const char *overlayPath);
#ifdef __cplusplus
}
#endif
#endif
