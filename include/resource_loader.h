#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 *(*ResourceAllocate)(u32 bytes);
typedef void (*ResourceReadComplete)(u8 *buffer, u32 bytes, s8 *path, void *user);

u8 *func_80027CB4(s8 *path, ResourceAllocate temporary, ResourceAllocate result);
u8 *func_80027D70(s8 *path, ResourceAllocate allocate);
u8 *func_80027C14(void *path);
u8 *func_80027C40(void *path);
u8 *func_80027C6C(void *path);
u8 *func_80027C90(void *path);
void func_80027AB0(void *tim_data);
void func_80027B20(void *tim_data);
s32 func_80027DD8(s8 *path, u8 **result);
void func_80027E6C(u8 *buffer, u32 bytes, s8 *path, void *user);
u8 *func_80027FB0(u8 *packed);
u8 *func_80028004(u8 *destination, u8 *compressed);
s32 func_8002802C(u8 *data);
ResourceReadComplete func_80035080(ResourceReadComplete callback);
void *func_800350DC(void *user);

#ifdef __cplusplus
}
#endif

#endif
