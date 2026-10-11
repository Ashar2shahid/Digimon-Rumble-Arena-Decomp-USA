#include "game_base_api.h"
#include "common.h"
#include "game_actor_queries.h"
#include "game_formatter.h"

extern u8 D_80065154[];
extern u8 D_80065174[];
extern u8 D_8006512C[];
extern s32 D_800D3A5C;
extern s32 func_800237A0(s32);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800726E4);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800727AC);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800728D0);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800729A0);

void func_80072B40(void *arg0, u16 *arg1, s32 arg2) {
    extern u8 *func_80028078(void);
    extern u8 *func_800280A0(s32 arg0);
    extern void func_8005844C(void *arg0, void *arg1);
    u8 *primitive = func_80028078();
    *(u32 *)(primitive + 4) = (((*(u8 *)(primitive + 7) | 2) << 24) | arg2);
    *(u32 *)(primitive + 8) = *(u32 *)arg1;
    *(u16 *)(primitive + 0xC) = (u16)(*(u16 *)(arg1 + 2) - 1);
    *(u16 *)(primitive + 0xE) = (u16)(*(u16 *)(arg1 + 3) - 1);
    func_8005844C(arg0, primitive);
    func_8005844C(arg0, func_800280A0(0x5F));
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80072BD8);

void func_80072CD0(u8 *a0, const u8 *a1, s32 a2, s32 a3) {
    *(s32 *)a0 = (s32)(0x140u - ((u32)a2 << 3)) >> 1;
    *(s32 *)(a0 + 4) = a3;
    func_800327B0(a0, a1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80072D04);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80072EB0);

void func_80072FBC(u8 *a0) {
    u8 buf[0x20];
    func_8002EF48(a0 + 0x12C, buf);
    func_80021080(a0 + 0x1B0, buf);
    func_8001FD40(a0 + 0xCC);
    func_8001FD40(a0 + 0x6C);
    func_8001FD40(*(s32 *)(a0 + 0x10) + 0xAC);
}

s32 func_80073010(u8 *a0, u8 *a1) {
    u8 buf[0x80];
    func_800764E8(buf);
    if (func_80076518(buf, a1, a0) != 0) {
        func_80076658(buf, a0);
        return 1;
    }
    return 0;
}

void func_80073070(u8 *a0, u8 *a1) {
    u8 buf[0x80];
    func_800764E8(buf);
    func_80076518(buf, a0, a1);
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800730B4);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800731C0);

u8 *func_800732A8(u8 *resource, u8 *owner) {
    register u8 *selected asm("$3");  /* preexisting retail register choice */
    if (func_80077618(owner) != 0) {
        selected = *(u8 **)(resource + 0x2C);
    } else {
        selected = *(u8 **)(resource + 0x30);
    }
    return *(u8 **)(selected + 8);
}

s32 func_800732F0(u8 *a0, s32 a1) {
    u8 *p = a0 + a1 * 4;
    return *(s32 *)(p + 0x24);
}

s32 func_80073304(u8 *a0, s32 a1) {
    u8 *p = a0 + a1 * 4;
    return *(s32 *)(p + 0x2C);
}

void func_80073318(u8 *a0) {
    *(s32 *)(a0 + 0x2C8) |= 0x20;
}

void func_8007332C(u8 *a0) {
    *(s32 *)(a0 + 0x2C8) &= ~0x20;
}

void func_80073340(u8 *a0) {
    *(s32 *)(a0 + 0x2C8) |= 0x40;
}

void func_80073354(u8 *a0) {
    *(s32 *)(a0 + 0x2C8) &= ~0x40;
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80073368);

void func_8007341C(void) {
}

void func_80073424(void) {
}

s32 func_8007342C(u8 *a0) {
    return *(s32 *)(a0 + 0x314);
}

s32 func_80073438(u8 *a0) {
    return *(s32 *)(a0 + 0x258);
}

s32 func_80073444(void) {
    return D_800D3A5C;
}

extern u8 D_800650BC;
extern s32 func_8007760C(u8 *);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80073454);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_8007353C);

void func_80073678(u8 *a0, s32 a1, s32 a2) {
    *(s32 *)a0 = a1;
    *(s32 *)(a0 + 4) = 0;
    *(s32 *)(a0 + 8) = 0;
    *(s32 *)(a0 + 0xC) = a2;
}

void func_8007368C(u8 *a0, s32 a1) {
    s32 v = a1 * *(s32 *)(a0 + 0) / 0x10000;
    s32 v1 = *(s32 *)(a0 + 8);
    s32 a2;
    *(s32 *)(a0 + 4) = v;
    if (v1 != v) {
        a2 = v1 - 1;
        if (v1 < v)
            a2 = v1 + 1;
        *(s32 *)(a0 + 8) = a2;
    }
    if (*(s32 *)(a0 + 0) > 0) {
        if (*(s32 *)(a0 + 4) < 2)
            *(s32 *)(a0 + 4) = 2;
        if (*(s32 *)(a0 + 8) < 2)
            *(s32 *)(a0 + 8) = 2;
    }
}

void func_80073714(u8 *a0) {
    *(s32 *)a0 = 0;
    *(s32 *)(a0 + 4) = 0;
    *(s32 *)(a0 + 8) = 0;
}

void func_80073724(u8 *a0) {
    s32 *p = (s32 *)(a0 + 8);
    s32 v1 = *p;
    s32 v0;
    if (v1 >= 0x101)
        v0 = v1 - (v1 >> 3);
    else
        v0 = v1 - 4;
    *p = v0;
    if (*(s32 *)(a0 + 8) <= 0)
        *(s32 *)(a0 + 8) = 0;
}

void func_80073768(u8 *a0, s32 a1) {
    if (a1 >= 2) {
        if (*(s32 *)(a0 + 4) < a1) {
            *(s32 *)(a0 + 8) = 0x200;
            *(s32 *)a0 = a1;
        }
    }
    *(s32 *)(a0 + 4) = a1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80073798);

void func_80073AD4(u8 *a0, u8 *a1) {
    if (*(u32 *)(a0 + 0x70) != 0) {
        u8 *next = *(u8 **)(a1 + 0x14) + 4;
        if (*(u32 *)(a0 + 0x50) == 0)
            func_80073B50(a0, next);
        else
            func_80073C44(a0);
        if (*(u32 *)(a0 + 0x70) != 0)
            func_80074B18(a0, a1);
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80073B50);

void func_80073C44(u8 *arg0, u8 *arg1) {
    extern void func_800742E0(void *, void *, s32, s32);
    extern void func_800745B8(void *, void *, s32, s32);
    extern void func_80073F64(void *, void *, s32, s32);
    extern void func_80074180(void *, void *, s32, s32);
    extern void func_80074A4C(void *, void *, s32, s32);
    extern void *func_8002AFFC(s32, s32, s32);
    extern void func_8005844C(void *, void *);
    extern void func_80073798(void *, void *, s32, s32);
    extern void func_80073D10(void *, void *, s32, s32);

    func_800742E0(arg0, arg1, 0xB9, 0xD8);
    func_800745B8(arg0, arg1, 0xB9, 0xCC);
    func_80073F64(arg0, arg1, 0xBF, 0xBE);
    func_80074180(arg0, arg1, 0xCD, 0xBE);
    func_80074A4C(arg0, arg1, 0xA0, 0xB8);
    func_8005844C(arg1, func_8002AFFC(0, 0, 0xF));
    func_80073798(arg0 + 0x64, arg1 + 8, 0x1C, 0x30);
    func_80073D10(arg0, arg1, 0x102, 0xBD);
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80073D10);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80073E08);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80073F64);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80074048);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80074180);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800742E0);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800745B8);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80074888);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80074A4C);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80074B18);

void func_8007503C(u8 *a0, s32 a1) {
    func_8002BCEC(a0, 0);
    if (a1 & 1)
        func_8002BDA8(a0);
}

s32 func_80075084(u8 *a0) {
    return *(s32 *)a0;
}

u8 *func_80075090(u8 *a0) {
    func_80075120(a0);
    func_800750C4(a0, 0);
    return a0;
}

void func_800750C4(u8 *a0, s32 a1) {
    *(s32 *)(a0 + 0x214) = a1 ? 0xA000 : 0;
}

void func_800750DC(u8 *a0, s32 a1) {
    register u32 index asm("$3"); /* PIN $v1 - ring index */
    u32 *slot;
    register u32 result asm("$2"); /* PIN $v0 - combined flag result */
    register u32 value asm("$6"); /* PIN $a2 - old and changed bits */

    index = *(u32 *)(a0 + 0x208);
    slot = (u32 *)(a0 + (index << 1));
    index = index + 1;
    *(u16 *)slot = a1;
    value = *(u16 *)(a0 + 0x200);
    index &= 0xFF;
    *(u32 *)(a0 + 0x208) = index;
    *(u16 *)(a0 + 0x200) = a1;
    value = a1 ^ value;
    result = a1 & value;
    *(u16 *)(a0 + 0x202) = result;
    a1 = ~a1;
    a1 &= value;
    *(u16 *)(a0 + 0x204) = a1;
}

void func_80075120(u8 *a0) {
    u8 *p = a0;
    u8 *end = a0 + 0x200;
    do {
        *(s32 *)p = 0;
        p += 4;
    } while (p != end);
    *(u16 *)(a0 + 0x200) = 0;
    *(u16 *)(a0 + 0x202) = 0;
    *(u16 *)(a0 + 0x204) = 0;
    *(s32 *)(a0 + 0x208) = 0;
    *(s32 *)(a0 + 0x20C) = 0;
    *(s32 *)(a0 + 0x210) = 0;
}

s32 func_80075154(u8 *a0) {
    u32 v0 = (*(u8 *)(a0 + 0x208) - 1) & 0xFF;
    return func_80075604(a0, *(u16 *)(a0 + (v0 << 1)));
}

s32 func_80075190(u8 *a0) {
    return func_80075604(a0, *(u16 *)(a0 + 0x202));
}

s32 func_800751B4(u8 *a0) {
    return func_80075604(a0, *(u16 *)(a0 + 0x204));
}

u32 func_800751D8(u8 *a0, s32 a1) {
    a1 -= 1;
    return *(u16 *)(a0 + (((*(u8 *)(a0 + 0x208) - a1) & 0xFF) << 1));
}

void func_800751FC(u8 *a0, s32 a1) {
    s32 v1;
    s32 v0;
    *(s32 *)(a0 + 0x20C) = (*(u8 *)(a0 + 0x208) - 1) & 0xFF;
    a1 = a1 + 1;
    if (a1 < 0x100)
        v1 = a1;
    else
        v1 = 0x100;
    v0 = v1;
    if (v0 <= 0)
        v0 = 1;
    *(s32 *)(a0 + 0x210) = v0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80075238);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_8007530C);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800753FC);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800754E4);

s32 func_80075604(u8 *a0, s32 a1) {
    s32 mask = *(s32 *)(a0 + 0x214);
    s32 v0 = a1;
    s32 x = v0 & mask;
    if (x != 0 && x != mask)
        v0 ^= mask;
    return v0;
}

s32 func_8007562C(u16 a0) {
    if ((a0 & 0xF000) != 0)
        return 0xF000;
    return 0xFF;
}

s32 func_80075644(u32 a0, u32 a1, s32 a2) {
    if (a2 != 0)
        return (a0 & a1) != 0;
    return (a0 ^ a1) == 0;
}

void *func_80075664(s32 *arg0, s32 *arg1) {
    if ((arg0[0] > arg1[4]) || (arg0[4] < arg1[0]) ||
        (arg0[1] > arg1[5]) || (arg0[5] < arg1[1]) ||
        (arg0[2] > arg1[6]) || (arg0[6] < arg1[2])) {
        return NULL;
    }
    return arg1;
}

u8 *func_80075704(u8 *a0, u8 *a1, s32 a2) {
    s32 i = 0;

    if (a2 <= 0)
        return 0;
    do {
        if (func_80075664(a0, a1))
            return a1;
        i += 1;
        a1 += 0x24;
    } while (i < a2);
    return 0;
}

u8 *func_80075774(u8 *a0, s32 a1, u8 *a2, s32 a3) {
    u8 *end = (u8 *)((u32)a0 + (u32)a1 * 0x24u);
    u8 *result;
    u8 *ret;

    result = 0;
    if (a0 != end) {
        do {
            ret = func_80075704(a0, a2, a3);
            result = ret;
            a0 += 0x24;
            if (result != 0) {
                return ret;
            }
        } while (a0 != end);
    }
    return result;
}

void func_800757F4(u8 *a0, s32 a1, s32 a2) {
    *(s32 *)(a0 + 0x20) = a2;
    func_80075814(a0, a1);
}

void func_80075814(s32 *arg0, s32 *arg1) {
    s32 maxX = arg1[0];
    s32 minX = maxX;
    s32 maxY = arg1[1];
    s32 minY = maxY;
    s32 maxZ = arg1[2];
    s32 minZ = maxZ;
    s32 *point = (s32 *)((u8 *)arg1 + 0x10);
    s32 *end = (s32 *)((u8 *)arg1 + 0x80);
    do {
        s32 value = point[0];
        if (maxX < value)
            maxX = value;
        else if (value < minX)
            minX = value;
        value = point[1];
        if (maxY < value)
            maxY = value;
        else if (value < minY)
            minY = value;
        value = point[2];
        if (maxZ < value)
            maxZ = value;
        else if (value < minZ)
            minZ = value;
        point += 4;
    } while ((s32)point < (s32)end);
    arg0[0] = minX;
    arg0[1] = minY;
    arg0[2] = minZ;
    arg0[4] = maxX;
    arg0[5] = maxY;
    arg0[6] = maxZ;
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800758D8);

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_800759F8);

u8 *func_80075B70(u8 *a0, u8 *a1) {
    register u32 *source asm("$6"); /* PIN $a2 - source block */
    register u32 *destination asm("$2"); /* PIN $v0 - returned destination */
    register u32 word0 asm("$5"); /* PIN $a1 - first copied word */
    register u32 wordOdd asm("$3"); /* PIN $v1 - odd copied word */
    register u32 wordEven asm("$4"); /* PIN $a0 - even copied word */

    source = *(u32 **)(a1 + 0x20);
    word0 = source[0];
    destination = (u32 *)a0;
    destination[0] = word0;
    wordOdd = source[1];
    destination[1] = wordOdd;
    wordEven = source[2];
    destination[2] = wordEven;
    wordOdd = source[3];
    destination[3] = wordOdd;
    wordEven = source[4];
    destination[4] = wordEven;
    wordOdd = source[5];
    destination[5] = wordOdd;
    wordEven = source[6];
    destination[6] = wordEven;
    wordOdd = source[7];
    destination[7] = wordOdd;
    return (u8 *)destination;
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80075BD8);

u8 *func_80075D08(u8 *a0, u8 *a1) {
    u8 *v0 = a0;
    u8 *a2 = *(u8 **)(v0 + 4);
    *(u8 **)(a1 + 4) = a2;
    *(u8 **)(a1 + 0) = *(u8 **)(a2 + 0);
    *(u8 **)(*(u8 **)(a2 + 0) + 4) = a1;
    *(u8 **)(a2 + 0) = a1;
    return v0;
}

void func_80075D38(u8 *a0, u8 *a1) {
    u8 *s0 = *(u8 **)a1;
    if (s0 == a1)
        return;
    do {
        u8 *cur = s0;
        s0 = *(u8 **)s0;
        func_80075D90(a0, cur);
    } while (s0 != a1);
}

void func_80075D90(s32 a0, s32 a1) {
    s32 s2 = a1;
    s32 cur = *(s32 *)a0;
    while (cur != a0) {
        s32 s0 = *(s32 *)cur;
        func_80075BD8(cur, s2);
        cur = s0;
    }
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80075DE8);

void func_80075F20(u8 *a0, u8 *a1) {
    u8 *s0 = *(u8 **)a0;
    if (s0 == a0)
        return;
    do {
        u8 *v1 = *(u8 **)(s0 + 0x30);
        s32 off = *(s16 *)(v1 + 0x18);
        void (*fn)(u8 *, u8 *) = *(void (**)(u8 *, u8 *))(v1 + 0x1C);
        u8 *next = *(u8 **)s0;
        fn(s0 + off, a1);
        s0 = next;
    } while (s0 != a0);
}

u8 *func_80075F88(u8 *a0, u8 *a1, s32 a2, s32 a3) {
    register u8 *base asm("$2"); /* PIN $v0 - returned object */
    register u32 flags asm("$4"); /* PIN $a0 - saved flags / second copied word */
    register u32 temp asm("$3"); /* PIN $v1 - vtable, mask, first copied word */
    register u32 word2 asm("$7"); /* PIN $a3 - third copied word */

    base = a0;
    temp = (u32)D_8006512C;
    flags = *(u32 *)(base + 0xC);
    *(u32 *)(base + 0x30) = temp;
    temp = -2;
    *(u32 *)(base + 8) = a3;
    word2 = -3;
    *(u32 *)base = (u32)base;
    *(u32 *)(base + 4) = (u32)base;
    *(u32 *)(base + 0x10) = 0;
    *(u32 *)(base + 0x14) = 0;
    *(u32 *)(base + 0x18) = 0;
    *(u32 *)(base + 0x1C) = 0;
    *(u32 *)(base + 0x20) = 0;
    *(u32 *)(base + 0x24) = 0;
    *(u32 *)(base + 0x28) = 0;
    *(u32 *)(base + 0x2C) = 0;
    flags &= temp;
    flags &= word2;
    *(u32 *)(base + 0xC) = flags;
    temp = *(u32 *)(a1 + 0);
    flags = *(u32 *)(a1 + 4);
    word2 = *(u32 *)(a1 + 8);
    *(u32 *)(base + 0x44) = a2;
    *(u32 *)(base + 0x34) = temp;
    *(u32 *)(base + 0x38) = flags;
    *(u32 *)(base + 0x3C) = word2;
    return base;
}

s32 func_80075FFC(u8 *a0, u8 *a1) {
    register u8 *s0 asm("$16"); /* PIN $s0 - primary object */
    register u8 *s1 asm("$17"); /* PIN $s1 - secondary object */
    register s32 valueV0 asm("$2"); /* PIN $v0 - state, first offset, helper result */
    register s32 valueA1 asm("$5"); /* PIN $a1 - first offset */
    register s32 valueA2 asm("$6"); /* PIN $a2 - second offset */
    register s32 valueV1 asm("$3"); /* PIN $v1 - third offset / radius */
    register s32 valueA0 asm("$4"); /* PIN $a0 - fourth offset / radius */
    s32 delta[3];

    s0 = a1;
    valueV0 = *(s32 *)(s0 + 0x10);
    if (valueV0 != 0) {
        return 0;
    }
    s1 = a0;
    valueA1 = *(s32 *)(s1 + 0x34);
    valueA2 = *(s32 *)(s1 + 0x38);
    valueV0 = *(s32 *)(s0 + 0x34);
    valueV1 = *(s32 *)(s1 + 0x3C);
    valueA0 = *(s32 *)(s0 + 0x38);
    valueA1 -= valueV0;
    valueA2 -= valueA0;
    valueV0 = *(s32 *)(s0 + 0x3C);
    delta[0] = valueA1;
    delta[1] = valueA2;
    valueV1 -= valueV0;
    delta[2] = valueV1;
    valueV0 = func_800237A0((s32)delta);
    valueV1 = *(s32 *)(s1 + 0x44);
    valueA0 = *(s32 *)(s0 + 0x44);
    valueV1 += valueA0;
    return valueV0 < valueV1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80076088);

u8 *func_80076250(u8 *arg0, s32 arg1, s32 arg2) {
    /* PIN $v0/$v1/$a0/$a1: keep the base, flags, and masks in retail registers. */
    register u8 *base asm("$2");
    register u32 flags asm("$3");
    register s32 maskA asm("$4");
    register s32 maskB asm("$5");

    base = arg0;
    __asm__ volatile ("" : "+r"(base));
    flags = (u32)D_80065174;
    *(u32 *)(base + 0x30) = flags;
    flags = *(u32 *)(base + 0xC);
    maskA = -2;
    *(u32 *)(base + 0x10) = arg1;
    maskB = -3;
    *(u32 *)base = (u32)base;
    *(u32 *)(base + 4) = (u32)base;
    *(u32 *)(base + 8) = arg2;
    *(u32 *)(base + 0x14) = 0;
    *(u32 *)(base + 0x18) = 0;
    *(u32 *)(base + 0x1C) = 0;
    *(u32 *)(base + 0x20) = 0;
    *(u32 *)(base + 0x24) = 0;
    *(u32 *)(base + 0x28) = 0;
    *(u32 *)(base + 0x2C) = 0;
    flags &= maskA;
    flags &= maskB;
    *(u32 *)(base + 0xC) = flags;
    return base;
}

s32 func_800762A8(u8 *a0) {
    return *(s32 *)(a0 + 0x10);
}

s32 func_800762B4(u8 *a0) {
    return *(s32 *)(a0 + 0x14);
}

void func_800762C0(u8 *a3, s32 a1) {
    u8 *a2 = *(u8 **)(a3 + 0);
    u8 *a0 = *(u8 **)(a3 + 4);
    *(u8 **)(a3 + 0x30) = D_80065174;
    *(u8 **)(a2 + 4) = a0;
    *(u8 **)(*(u8 **)(a3 + 4) + 0) = *(u8 **)(a3 + 0);
    *(u8 **)(a3 + 0) = a3;
    *(u8 **)(a3 + 4) = a3;
    if (a1 & 1)
        func_8002B3D0(a3);
}

void func_80076318(u8 *a0, s32 a1) {
    *(s32 *)(a0 + 8) = a1;
}

void func_80076320(u8 *a0, s32 a1) {
    *(s32 *)(a0 + 0x14) = a1;
}

void func_80076328(u8 *a0, s32 a1) {
    *(s32 *)(a0 + 0xC) = (*(s32 *)(a0 + 0xC) & ~1) | (a1 & 1);
}

s32 func_80076344(u8 *a0) {
    return *(s32 *)(a0 + 0xC) & 1;
}

s32 func_80076350(u8 *a0) {
    return (u32)(*(u32 *)(a0 + 0xC) >> 1) & 1;
}

void func_80076364(u8 *a0) {
    *(s32 *)(a0 + 0xC) &= ~2;
}

void func_80076378(u8 *a0, u8 *a1) {
    func_80075D08(a0, a1);
}

u8 *func_80076398(u8 *a0) {
    *(u8 **)a0 = D_80065154;
    return a0;
}

void func_800763AC(u8 *a0, s32 a1) {
    *(u8 **)a0 = D_80065154;
    if (a1 & 1)
        func_8002B3D0();
}

void func_800763E0(u8 *a3, s32 a1) {
    u8 *a2 = *(u8 **)(a3 + 0);
    u8 *a0 = *(u8 **)(a3 + 4);
    *(u8 **)(a3 + 0x30) = D_80065174;
    *(u8 **)(a2 + 4) = a0;
    *(u8 **)(*(u8 **)(a3 + 4) + 0) = *(u8 **)(a3 + 0);
    *(u8 **)(a3 + 0) = a3;
    *(u8 **)(a3 + 4) = a3;
    if (a1 & 1)
        func_8002B3D0(a3);
}

u8 *func_80076438(u8 *a0, s32 a1) {
    register u8 *base asm("$2");   /* PIN $v0 - returned object */
    register u32 flags asm("$3"); /* PIN $v1 - saved flag word */
    register s32 maskA asm("$5"); /* PIN $a1 - first flag mask */
    register s32 temp asm("$4");  /* PIN $a0 - vtable / second mask */
    s32 *new_var;

    base = a0;
    temp = (u32)D_8006512C;
    flags = *(u32 *)(base + 0xC);
    *(u32 *)(base + 8) = a1;
    maskA = -2;
    *(u32 *)(base + 0x30) = temp;
    temp = -3;
    *(u32 *)base = (u32)base;
    *(u32 *)(base + 4) = (u32)base;
    *(u32 *)(base + 0x10) = 0;
    *(u32 *)(base + 0x14) = 0;
    *(u32 *)(base + 0x18) = 0;
    *(u32 *)(base + 0x1C) = 0;
    *(u32 *)(base + 0x20) = 0;
    *(u32 *)(base + 0x24) = 0;
    *(u32 *)(base + 0x28) = 0;
    *(u32 *)(base + 0x2C) = 0;
    flags &= maskA;
    new_var = &temp;
    flags &= *new_var;
    flags &= maskA;
    flags |= 1;
    *(u32 *)(base + 0xC) = flags;
    return base;
}

u8 *func_80076498(u8 *a0, u8 *a1) {
    s32 v1 = *(s32 *)(a0 + 0x34);
    s32 v2 = *(s32 *)(a0 + 0x38);
    s32 v3 = *(s32 *)(a0 + 0x3C);
    *(s32 *)(a1 + 0x0) = v1;
    *(s32 *)(a1 + 0x4) = v2;
    *(s32 *)(a1 + 0x8) = v3;
    return a1;
}

void func_800764B8(u8 *a0, u8 *a1) {
    s32 v0 = *(s32 *)(a1 + 0x0);
    s32 v1 = *(s32 *)(a1 + 0x4);
    s32 v2 = *(s32 *)(a1 + 0x8);
    *(s32 *)(a0 + 0x34) = v0;
    *(s32 *)(a0 + 0x38) = v1;
    *(s32 *)(a0 + 0x3C) = v2;
}

void func_800764D4(u8 *a0, s32 a1) {
    *(s32 *)(a0 + 0x44) = a1;
}

s32 func_800764DC(u8 *a0) {
    return *(s32 *)(a0 + 0x44);
}

u8 *func_800764E8(u8 *a0) {
    u8 *v0 = func_80076AA4(a0);
    *(s32 *)(a0 + 0x78) = *(s32 *)v0;
    return a0;
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80076518);

s32 func_80076628(u8 *a0) {
    return *(s32 *)(a0 + 0x78);
}

s32 func_80076634(s32 a0) {
    return a0;
}

s32 func_8007663C(u8 *a0) {
    s32 v1 = *(s32 *)(a0 + 0x78);
    return *(s32 *)(v1 + 0xC);
}

u8 *func_80076650(u8 *a0) {
    return a0 + 0x68;
}

u8 *func_80076658(u8 *a0, u8 *a1) {
    func_80076694(a1, a0 + 0x48, *(s32 *)(a0 + 0x10), *(s32 *)(a0 + 0x14));
    return a1;
}

INCLUDE_ASM("asm/us/game/nonmatchings/E324", func_80076694);
