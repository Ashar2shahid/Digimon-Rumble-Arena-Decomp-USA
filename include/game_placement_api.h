/* Reviewed placement identity: returns the supplied storage unchanged. */
#ifndef GAME_PLACEMENT_API_H
#define GAME_PLACEMENT_API_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Retail callers supply size in a0; the identity body does not inspect it. */
void *func_8002BD80(u32 size, void *storage);

#ifdef __cplusplus
}
#endif

#endif
