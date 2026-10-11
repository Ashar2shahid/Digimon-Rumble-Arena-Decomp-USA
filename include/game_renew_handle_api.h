#ifndef GAME_RENEW_HANDLE_API_H
#define GAME_RENEW_HANDLE_API_H
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Remove the entity's old handle, then register the same entity again. */
void func_8002BEE8(void *entity);
/* Renew the active entity handle and mark the owning state for update. */
void func_8007F9D4(u8 *state);
#ifdef __cplusplus
}
#endif
#endif
