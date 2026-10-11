#ifndef GAME_MD5_H
#define GAME_MD5_H
#include "common.h"
typedef struct Md5Context {
    u32 state[4];
    u32 count[2];
    u8 buffer[64];
} Md5Context;
typedef char Md5Context_size_is_88[(sizeof(Md5Context) == 88) ? 1 : -1];
Md5Context *func_800383B4(Md5Context *ctx);
void func_800383DC(Md5Context *ctx);
void func_80038418(Md5Context *ctx, u8 *input, u32 length);
void func_80037250(Md5Context *ctx, u8 *digest);
void func_80037458(u32 *state, u8 *block);
void func_80038510(u8 *output, const u32 *input, u32 length);
void func_80038560(u32 *output, const u8 *input, u32 length);
void func_800385B8(u8 *destination, u8 *source, u32 length);
void func_800385E8(u8 *destination, s32 value, u32 length);
#endif
