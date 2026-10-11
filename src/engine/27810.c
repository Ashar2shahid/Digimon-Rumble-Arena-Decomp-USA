#include "common.h"
#include "game_md5.h"
#include "game_random.h"
extern u8 D_8001996C[64];



u32 D_8006439C[2] = {0, 0x9908B0DF};
/* the Mersenne Twister's constants, as in Matsumoto and Nishimura's
 * mt19937.c */
#define MT_MATRIX_A 0x9908B0DF   /* the twist matrix's last row */
#define MT_UPPER_MASK 0x80000000 /* the most significant w-r bits */
#define MT_LOWER_MASK 0x7FFFFFFF /* the least significant r bits */
#define MT_DEFAULT_SEED 4357
#define MT_SEED_MULTIPLIER 69069
#define MT_TEMPERING_MASK_B 0x9D2C5680
#define MT_TEMPERING_MASK_C 0xEFC60000

/* Draws the next random number (genrand); the first time, seeds the
 * generator with the default seed (mersenneTwisterSeed inline). */
u32 func_80037010(RandomState *state) {
    /* The table has only these two words at retail 0x8006439C. */

    s32 mti = state->index;
    u32 y;

    if (mti >= 624) {
        s32 kk;

        if (mti == 624 + 1) {
            /* not seeded yet: seed(state, MT_DEFAULT_SEED) */
            s32 i;

            state->words[0] = MT_DEFAULT_SEED;
            for (i = 1; i < 624; i++) {
                state->words[i] = MT_SEED_MULTIPLIER * state->words[i - 1];
            }
            state->index = i;
        }
        for (kk = 0; kk < 624 - 397; kk++) {
            y = (state->words[kk] & MT_UPPER_MASK) | (state->words[kk + 1] & MT_LOWER_MASK);
            state->words[kk] = state->words[kk + 397] ^ (y >> 1) ^ D_8006439C[y & 1];
        }
        for (; kk < 624 - 1; kk++) {
            y = (state->words[kk] & MT_UPPER_MASK) | (state->words[kk + 1] & MT_LOWER_MASK);
            state->words[kk] = state->words[kk + (397 - 624)] ^ (y >> 1) ^ D_8006439C[y & 1];
        }
        y = (state->words[624 - 1] & MT_UPPER_MASK) | (state->words[0] & MT_LOWER_MASK);
        state->words[624 - 1] = state->words[397 - 1] ^ (y >> 1) ^ D_8006439C[y & 1];
        mti = 0;
    }
    y = state->words[mti++];
    state->index = mti;
    y ^= y >> 11;
    y ^= (y << 7) & MT_TEMPERING_MASK_B;
    y ^= (y << 15) & MT_TEMPERING_MASK_C;
    y ^= y >> 18;
    return y;
}

RandomState *func_800371E8(RandomState *state) {
    state->index = 625;
    return state;
}

void func_800371F8(RandomState *state, u32 seed) {
    u32 *next;
    s32 i;
    state->words[0] = seed;
    next = &state->words[1];
    for (i = 1; i < 624; i++) {
        u32 previous = next[-1];
        *next = 69069u * previous;
        next++;
    }
    state->index = i;
}

/* Continues an MD5 operation with len more bytes of the message; Final
 * has it inline. */
static inline void MD5UpdateInline(Md5Context *ctx, u8 *input, u32 len) {
    u32 i;
    u32 index;
    u32 partLen;

    index = (ctx->count[0] >> 3) & 0x3F;
    if ((ctx->count[0] += len << 3) < (len << 3)) {
        ctx->count[1]++;
    }
    ctx->count[1] += len >> 29;
    partLen = 64 - index;
    if (len >= partLen) {
        func_800385B8(&ctx->buffer[index], input, partLen);
        func_80037458(ctx->state, ctx->buffer);
        for (i = partLen; i + 63 < len; i += 64) {
            func_80037458(ctx->state, &input[i]);
        }
        index = 0;
    } else {
        i = 0;
    }
    func_800385B8(&ctx->buffer[index], &input[i], len - i);
}

/* Ends an MD5 operation: pads the message, appends its length and writes
 * the 16-byte digest, then clears the context. */
void func_80037250(Md5Context *ctx, u8 *digest) {
    u8 bits[8];
    u32 index;
    u32 padLen;

    func_80038510(bits, ctx->count, 8);
    index = (ctx->count[0] >> 3) & 0x3F;
    padLen = (index < 56) ? (56 - index) : (120 - index);
    MD5UpdateInline(ctx, D_8001996C, padLen);
    MD5UpdateInline(ctx, bits, 8);
    func_80038510(digest, ctx->state, 16);
    func_800385E8((u8 *)ctx, 0, sizeof(Md5Context)); /* clears the whole context */
}





INCLUDE_ASM("asm/us/main/nonmatchings/27810", func_80037458);
