/*****************************************************************************
 *
 * @brief xkgost intrinsics
 *
 *  Copyright (C) 2021-2022  Mark Fedorov <mark.fedorov@cloudbear.ru>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 ****************************************************************************/

#ifndef RVINTRINXKGOST_H
#define RVINTRINXKGOST_H

#include <stdint.h>
#include <stddef.h>

#if __riscv_xkgost && __riscv_xlen == 64
#define DECLARE_INTRIN_RR(insn) static inline uint64_t __rv_##insn(uint64_t rs1, uint64_t rs2) { uint64_t rd; __asm__(#insn " %0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2)); return rd; }
DECLARE_INTRIN_RR(kuzn64el)
DECLARE_INTRIN_RR(kuzn64dl)
DECLARE_INTRIN_RR(magma64)
DECLARE_INTRIN_RR(kuzn64esx)
DECLARE_INTRIN_RR(kuzn64dsx)
#undef DECLARE_INTRIN_RR
#elif __riscv_xkgost && __riscv_xlen == 32

static inline uint64_t __rv_kuzn64esx(uint64_t rs1, uint64_t rs2) {
    uint64_t rd = 0;
    uint32_t *r = (uint32_t *)(&(rd));
    const uint32_t *r1 = (const uint32_t *)(&(rs1));
    const uint32_t *r2 = (const uint32_t *)(&(rs2));
    __asm__("kuzn32esx %0, %1, %2" : "=r"(r[0]) : "r"(r1[0]), "r"(r2[0]));
    __asm__("kuzn32esx %0, %1, %2" : "=r"(r[1]) : "r"(r1[1]), "r"(r2[1]));
    return rd;
}

static inline uint64_t __rv_kuzn64dsx(uint64_t rs1, uint64_t rs2) {
    uint64_t rd = 0;
    uint32_t *r = (uint32_t *)(&(rd));
    const uint32_t *r1 = (const uint32_t *)(&(rs1));
    const uint32_t *r2 = (const uint32_t *)(&(rs2));
    __asm__("kuzn32dsx %0, %1, %2" : "=r"(r[0]) : "r"(r1[0]), "r"(r2[0]));
    __asm__("kuzn32dsx %0, %1, %2" : "=r"(r[1]) : "r"(r1[1]), "r"(r2[1]));
    return rd;
}

static inline uint64_t __rv_kuzn64dl(uint64_t rs1, uint64_t rs2) {
    uint64_t rd = 0;
    uint32_t *r = (uint32_t *)(&(rd));
    const uint32_t *r1 = (const uint32_t *)(&(rs1));
    const uint32_t *r2 = (const uint32_t *)(&(rs2));
    uint32_t tmp;
    __asm__("kuzn32dl  %0, %1, %2" : "=r"(tmp) : "r"(r2[0]), "r"(r2[1]));
    __asm__("kuzn32dlh %0, %1, %2" : "=r"(r[0]) : "r"(r1[0]), "r"(r1[1]));
    r[0] ^= tmp;
    __asm__("kuzn32dl  %0, %1, %2" : "=r"(tmp) : "r"(r2[1]), "r"(r[0]));
    __asm__("kuzn32dlh %0, %1, %2" : "=r"(r[1]) : "r"(r1[1]), "r"(r2[0]));
    r[1] ^= tmp;
    return rd;
}

static inline uint64_t __rv_kuzn64el(uint64_t rs1, uint64_t rs2) {
    uint64_t rd = 0;
    uint32_t *r = (uint32_t *)(&(rd));
    const uint32_t *r1 = (const uint32_t *)(&(rs1));
    const uint32_t *r2 = (const uint32_t *)(&(rs2));
    uint32_t tmp;
    __asm__("kuzn32el  %0, %1, %2" : "=r"(tmp) : "r"(r2[0]), "r"(r2[1]));
    __asm__("kuzn32elh %0, %1, %2" : "=r"(r[1]) : "r"(r1[0]), "r"(r1[1]));
    r[1] ^= tmp;
    __asm__("kuzn32el  %0, %1, %2" : "=r"(tmp) : "r"(r1[1]), "r"(r2[0]));
    __asm__("kuzn32elh %0, %1, %2" : "=r"(r[0]) : "r"(r[1]), "r"(r1[0]));
    r[0] ^= tmp;
    return rd;
}

static inline uint64_t __rv_magma64(uint64_t rs1, uint32_t rs2) {
    uint64_t rd = 0;
    uint32_t *r = (uint32_t *)(&(rd));
    const uint32_t *r1 = (const uint32_t *)(&(rs1));
    __asm__("magma32g %0, %1, %2" : "=r"(r[1]) : "r"(r1[1]), "r"(rs2));
    r[1] ^= r1[0];
    r[0] = r1[1];
    return rd;
}

#else // ^^^ __riscv_xkgost ^^^ | vvv !__riscv_xkgost vvv

static inline uint64_t __rv_kuzn64esx(uint64_t rs1, uint64_t rs2) {
    rs1 ^= rs2;
    static const uint8_t sbox[256] = {
        252, 238, 221,  17, 207, 110,  49,  22, 251, 196, 250, 218,  35, 197,   4,  77,
        233, 119, 240, 219, 147,  46, 153, 186,  23,  54, 241, 187,  20, 205,  95, 193,
        249,  24, 101,  90, 226,  92, 239,  33, 129,  28,  60,  66, 139,   1, 142,  79,
          5, 132,   2, 174, 227, 106, 143, 160,   6,  11, 237, 152, 127, 212, 211,  31,
        235,  52,  44,  81, 234, 200,  72, 171, 242,  42, 104, 162, 253,  58, 206, 204,
        181, 112,  14,  86,   8,  12, 118,  18, 191, 114,  19,  71, 156, 183,  93, 135,
         21, 161, 150,  41,  16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177,
         50, 117,  25,  61, 255,  53, 138, 126, 109,  84, 198, 128, 195, 189,  13,  87,
        223, 245,  36, 169,  62, 168,  67, 201, 215, 121, 214, 246, 124,  34, 185,   3,
        224,  15, 236, 222, 122, 148, 176, 188, 220, 232,  40,  80,  78,  51,  10,  74,
        167, 151,  96, 115,  30,   0,  98,  68,  26, 184,  56, 130, 100, 159,  38,  65,
        173,  69,  70, 146,  39,  94,  85,  47, 140, 163, 165, 125, 105, 213, 149,  59,
          7,  88, 179,  64, 134, 172,  29, 247,  48,  55, 107, 228, 136, 217, 231, 137,
        225,  27, 131,  73,  76,  63, 248, 254, 141,  83, 170, 144, 202, 216, 133,  97,
         32, 113, 103, 164,  45,  43,   9,  91, 203, 155,  37, 208, 190, 229, 108,  82,
         89, 166, 116, 210, 230, 244, 180, 192, 209, 102, 175, 194,  57,  75,  99, 182,
    };
    uint64_t rd = 0;
    for (size_t i = 0; i < 64; i += 8)
        rd |= (uint64_t)sbox[(rs1 >> i) & 0xFF] << i;
    return rd;
}

static inline uint64_t __rv_kuzn64dsx(uint64_t rs1, uint64_t rs2) {
    static const uint8_t sbox[256] = {
        165,  45,  50, 143,  14,  48,  56, 192,  84, 230, 158,  57,  85, 126,  82, 145,
        100,   3,  87,  90,  28,  96,   7,  24,  33, 114, 168, 209,  41, 198, 164,  63,
        224,  39, 141,  12, 130, 234, 174, 180, 154,  99,  73, 229,  66, 228,  21, 183,
        200,   6, 112, 157,  65, 117,  25, 201, 170, 252,  77, 191,  42, 115, 132, 213,
        195, 175,  43, 134, 167, 177, 178,  91,  70, 211, 159, 253, 212,  15, 156,  47,
        155,  67, 239, 217, 121, 182,  83, 127, 193, 240,  35, 231,  37,  94, 181,  30,
        162, 223, 166, 254, 172,  34, 249, 226,  74, 188,  53, 202, 238, 120,   5, 107,
         81, 225,  89, 163, 242, 113,  86,  17, 106, 137, 148, 101, 140, 187, 119,  60,
        123,  40, 171, 210,  49, 222, 196,  95, 204, 207, 118,  44, 184, 216,  46,  54,
        219, 105, 179,  20, 149, 190,  98, 161,  59,  22, 102, 233,  92, 108, 109, 173,
         55,  97,  75, 185, 227, 186, 241, 160, 133, 131, 218,  71, 197, 176,  51, 250,
        150, 111, 110, 194, 246,  80, 255,  93, 169, 142,  23,  27, 151, 125, 236,  88,
        247,  31, 251, 124,   9,  13, 122, 103,  69, 135, 220, 232,  79,  29,  78,   4,
        235, 248, 243,  62,  61, 189, 138, 136, 221, 205,  11,  19, 152,   2, 147, 128,
        144, 208,  36,  52, 203, 237, 244, 206, 153,  16,  68,  64, 146,  58,   1,  38,
         18,  26,  72, 104, 245, 129, 139, 199, 214,  32,  10,   8,   0,  76, 215, 116,
    };
    uint64_t rd = 0;
    for (size_t i = 0; i < 64; i += 8)
        rd |= (uint64_t)sbox[(rs1 >> i) & 0xFF] << i;
    return rd ^ rs2;
}

// SIMD-like multiplication of GF(2^8) vectors
static inline uint64_t __rv_sbg64_gfmul(uint64_t a, uint64_t b) {
    uint64_t res = 0;
    uint64_t mask_poly = 0xC3C3C3C3C3C3C3C3; // Replicated primitive polynomial p(x) = 1 + x + x^6 + x^7 + x^8 (0xC3)
    uint64_t mask_b = 0x0101010101010101;
    uint64_t mask_a = mask_b << 7; // 0x8080808080808080
    uint64_t bm;
    uint64_t am;
    for (size_t i = 0; i < 8; ++i) {
        // Select LSB in each byte
        bm = (b & mask_b);
        // Extend LSB to all bits in each byte
        bm |= (bm << 1);
        bm |= (bm << 2);
        bm |= (bm << 4);
        // Add "a" to result if corresponding "b" bit is one
        res ^= a & bm;
        // Go to next "b" bit
        b >>= 1;
        // Select MSB in each byte
        am = (a & mask_a);
        // Clear MSB in each byte
        a ^= am;
        // Shift, since MSB is clear already it doesn't propagate to next byte
        a <<= 1;
        // Extend MSB to all bits in each byte
        am |= (am >> 1);
        am |= (am >> 2);
        am |= (am >> 4);
        // Substract minimal polynom from each "a" byte if MSB in corresponding bit is one
        a ^= (am & mask_poly);
    }
    return res;
}

static inline uint64_t __rv_sbg64_kuzn(uint8_t coef[8][16], uint64_t rs1, uint64_t rs2) {
    uint64_t rd = 0;
    uint64_t sum;
    uint64_t *coef1;
    uint64_t *coef2;
    // Multiply 8x16 matrix to 16 element vector represented by rs1, rs2
    for (size_t i = 0; i < 8; ++i) {
        // Pointers to row coefficients
        coef1 = (uint64_t*) &coef[i];
        coef2 = coef1 + 1;
        // SIMD like dot product of two vectors
        sum = __rv_sbg64_gfmul(*coef1, rs1) ^ __rv_sbg64_gfmul(*coef2, rs2);
        sum ^= (sum >> 32);
        sum ^= (sum >> 16);
        sum ^= (sum >> 8);
        sum &= 0xFF;
        // Put result to appropriate position
        rd |= sum << (8 * i);
    }
    return rd;
}

static inline uint64_t __rv_kuzn64dl(uint64_t rs1, uint64_t rs2) {
    static uint8_t coef[8][16] = {
        {  1, 148,  32, 133,  16, 194, 192,   1, 251,   1, 192, 194,  16, 133,  32, 148},
        {148, 165,  60,  68, 209, 141, 180,  84, 222, 111, 119,  93, 150, 116,  45, 132},
        {132, 100,  72, 223, 211,  49, 166,  48, 224,  90,  68, 151, 202, 117, 153, 221},
        {221,  13, 248,  82, 145, 100, 255, 123, 175,  61, 148, 243, 217, 208, 233,  16},
        { 16, 137,  72, 127, 145, 236,  57, 239,  16, 191,  96, 233,  48,  94, 149, 189},
        {189, 162,  72, 198, 254, 235,  47, 132, 201, 173, 124,  26, 104, 190, 159,  39},
        { 39, 127, 200, 152, 243,  15,  84,   8, 246, 238,  18, 141,  47, 184, 212,  93},
        { 93,  75, 142,  96,   1,  42, 108,   9,  73, 171, 141, 203,  20, 135,  73, 184},
    };
    return __rv_sbg64_kuzn(coef, rs1, rs2);
}

static inline uint64_t __rv_kuzn64el(uint64_t rs1, uint64_t rs2) {
    static uint8_t coef[8][16] = {
        {184,  73, 135,  20, 203, 141, 171,  73,   9, 108,  42,   1,  96, 142,  75,  93},
        { 93, 212, 184,  47, 141,  18, 238, 246,   8,  84,  15, 243, 152, 200, 127,  39},
        { 39, 159, 190, 104,  26, 124, 173, 201, 132,  47, 235, 254, 198,  72, 162, 189},
        {189, 149,  94,  48, 233,  96, 191,  16, 239,  57, 236, 145, 127,  72, 137,  16},
        { 16, 233, 208, 217, 243, 148,  61, 175, 123, 255, 100, 145,  82, 248,  13, 221},
        {221, 153, 117, 202, 151,  68,  90, 224,  48, 166,  49, 211, 223,  72, 100, 132},
        {132,  45, 116, 150,  93, 119, 111, 222,  84, 180, 141, 209,  68,  60, 165, 148},
        {148,  32, 133,  16, 194, 192,   1, 251,   1, 192, 194,  16, 133,  32, 148,   1},
    };
    return __rv_sbg64_kuzn(coef, rs1, rs2);
}

static inline uint64_t __rv_magma64(uint64_t rs1, uint64_t rs2) {
#if __riscv_xlen == 64 && (__riscv_zbb || __riscv_zbkb)
    __asm__("rori %0, %0, 32" : "+r"(rs2));
    __asm__("rev8 %0, %0" : "+r"(rs1));
    __asm__("rev8 %0, %0" : "+r"(rs2));
#elif 0 && __riscv_xlen == 32 && (__riscv_zbb || __riscv_zbkb)
    // this xlen=32 solution is less efficient than the compiler's one
    // because of moves instead of just register order handling
    uint32_t *r1 = (uint32_t *)(&(rs1));
    uint32_t *r2 = (uint32_t *)(&(rs2));
    rs1 = (rs1 << 32) | ((uint64_t)rs1 >> 32);
    __asm__("rev8 %0, %0" : "+r"(r1[0]));
    __asm__("rev8 %0, %0" : "+r"(r1[1]));
    __asm__("rev8 %0, %0" : "+r"(r2[0]));
#else // no bitmanip subset
    rs1 = ((rs1 & 0x00FF00FF00FF00FFLL) <<  8) | ((uint64_t)(rs1 & 0xFF00FF00FF00FF00LL) >>  8);
    rs2 = ((rs2 & 0x00FF00FF00FF00FFLL) <<  8) | ((uint64_t)(rs2 & 0xFF00FF00FF00FF00LL) >>  8);
    rs1 = ((rs1 & 0x0000FFFF0000FFFFLL) << 16) | ((uint64_t)(rs1 & 0xFFFF0000FFFF0000LL) >> 16);
    rs2 = ((rs2 & 0x0000FFFF0000FFFFLL) << 16) | ((uint64_t)(rs2 & 0xFFFF0000FFFF0000LL) >> 16);
    rs1 = (rs1 << 32) | ((uint64_t)rs1 >> 32);
#endif
    static uint8_t sbox[8][16] = {
        {12,  4,  6,  2, 10,  5, 11,  9, 14,  8, 13,  7,  0,  3, 15,  1},
        { 6,  8,  2,  3,  9, 10,  5, 12,  1, 14,  4,  7, 11, 13,  0, 15},
        {11,  3,  5,  8,  2, 15, 10, 13, 14,  1,  7,  4, 12,  9,  6,  0},
        {12,  8,  2,  1, 13,  4, 15,  6,  7,  0, 10,  5,  3, 14,  9, 11},
        { 7, 15,  5, 10,  8,  1,  6, 13,  0,  9,  3, 14, 11,  4,  2, 12},
        { 5, 13, 15,  6,  9,  2, 12, 10, 11,  7,  8,  1,  4,  3, 14,  0},
        { 8, 14,  2,  5,  6,  9,  1, 12, 15,  4, 11,  0, 13, 10,  3,  7},
        { 1,  7, 14, 13,  0,  5,  8,  3,  4, 15, 10,  6,  9, 12, 11,  2},
    };
    uint32_t lo_key;
    uint32_t t = 0;
    uint32_t g;
    lo_key = (uint32_t)rs1 + (uint32_t)rs2;
    for (size_t i = 0; i < 32; i += 4)
        t |= (uint32_t)sbox[i >> 2][(lo_key >> i) & 0xF] << i;
    g = (t << 11) | (t >> 21);
    g ^= (uint32_t)(rs1 >> 32);
    rs1 = (rs1 << 32) | g;
#if __riscv_xlen == 64 && (__riscv_zbb || __riscv_zbkb)
    __asm__("rev8 %0, %0" : "+r"(rs1));
#elif 0 && __riscv_xlen == 32 && (__riscv_zbb || __riscv_zbkb)
    // this xlen=32 solution is less efficient than the compiler's one
    // because of moves instead of just register order handling
    rs1 = (rs1 << 32) | ((uint64_t)rs1 >> 32);
    __asm__("rev8 %0, %0" : "+r"(r1[0]));
    __asm__("rev8 %0, %0" : "+r"(r1[1]));
#else // no bitmanip subset
    rs1 = ((rs1 & 0x00FF00FF00FF00FFLL) <<  8) | ((uint64_t)(rs1 & 0xFF00FF00FF00FF00LL) >>  8);
    rs1 = ((rs1 & 0x0000FFFF0000FFFFLL) << 16) | ((uint64_t)(rs1 & 0xFFFF0000FFFF0000LL) >> 16);
    rs1 = (rs1 << 32) | ((uint64_t)rs1 >> 32);
#endif
    return rs1;
}

#endif //!__riscv_xkgost
#endif //RVINTRINXKGOST_H
