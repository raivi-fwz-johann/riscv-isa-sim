/*****************************************************************************
*
* @brief GOST crypto algorithms
*
* @author alexander.kozlov@cloudbear.ru
*
* Copyright (c) 2021-2022 CloudBEAR LLC - http://www.cloudbear.ru/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
*   Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
*   Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the
*   distribution.
*
*   Neither the name of CloudBEAR nor the names of
*   its contributors may be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

#include <bear_crypto_gost.h>
#include <stddef.h>
#include <string.h>

typedef struct uint512_t {
    uint64_t arr[8];
} uint512_t;

void kuzn_expand_key(const uint64_t* master_key, uint64_t* keys)
{
    int64_t t_lo;
    int64_t t_hi;

    int64_t round = 0;

    keys[0] = master_key[0];
    keys[1] = master_key[1];
    keys[2] = master_key[2];
    keys[3] = master_key[3];

    for (size_t k = 4; k < 20; k += 4) {
        keys[k+0] = keys[k-4+0];
        keys[k+1] = keys[k-4+1];
        keys[k+2] = keys[k-4+2];
        keys[k+3] = keys[k-4+3];

        for (size_t i = 0; i < 8; ++i) {
            round += 0x0100000000000000LL;

            t_hi = __rv_kuzn64el(0, round);
            t_lo = __rv_kuzn64el(t_hi, 0);

            t_hi = __rv_kuzn64esx(t_hi, keys[k+1]);
            t_lo = __rv_kuzn64esx(t_lo, keys[k+0]);

            t_hi = __rv_kuzn64el(t_lo, t_hi);
            t_lo = __rv_kuzn64el(t_hi, t_lo);

            t_hi ^= keys[k+3];
            t_lo ^= keys[k+2];

            keys[k+2] = keys[k+0];
            keys[k+3] = keys[k+1];

            keys[k+0] = t_lo;
            keys[k+1] = t_hi;
        }
    }
}

// Apply X, S, P, L transforms
static inline void streebog_xlps(const uint512_t* x, const uint512_t* y, uint512_t* data)
{
    uint64_t r[16];

    // X and S-transform
    for (size_t i = 0; i < 8; ++i)
        r[i] = __rv_kuzn64esx(x->arr[i], y->arr[i]);


#if __riscv_xkgost && __riscv_xlen == 64
    __asm__("sbg64tau1 %0, %1, %2" : "=r"(r[8+0]) : "r"(r[0]), "r"(r[4]));
    __asm__("sbg64tau2 %0, %1, %2" : "=r"(r[8+1]) : "r"(r[0]), "r"(r[4]));
    __asm__("sbg64tau1 %0, %1, %2" : "=r"(r[8+2]) : "r"(r[1]), "r"(r[5]));
    __asm__("sbg64tau2 %0, %1, %2" : "=r"(r[8+3]) : "r"(r[1]), "r"(r[5]));
    __asm__("sbg64tau1 %0, %1, %2" : "=r"(r[8+4]) : "r"(r[2]), "r"(r[6]));
    __asm__("sbg64tau2 %0, %1, %2" : "=r"(r[8+5]) : "r"(r[2]), "r"(r[6]));
    __asm__("sbg64tau1 %0, %1, %2" : "=r"(r[8+6]) : "r"(r[3]), "r"(r[7]));
    __asm__("sbg64tau2 %0, %1, %2" : "=r"(r[8+7]) : "r"(r[3]), "r"(r[7]));

    __asm__("sbg64tau1 %0, %1, %2" : "=r"(r[0]) : "r"(r[8+0]), "r"(r[8+4]));
    __asm__("sbg64tau2 %0, %1, %2" : "=r"(r[1]) : "r"(r[8+0]), "r"(r[8+4]));
    __asm__("sbg64tau1 %0, %1, %2" : "=r"(r[2]) : "r"(r[8+1]), "r"(r[8+5]));
    __asm__("sbg64tau2 %0, %1, %2" : "=r"(r[3]) : "r"(r[8+1]), "r"(r[8+5]));
    __asm__("sbg64tau1 %0, %1, %2" : "=r"(r[4]) : "r"(r[8+2]), "r"(r[8+6]));
    __asm__("sbg64tau2 %0, %1, %2" : "=r"(r[5]) : "r"(r[8+2]), "r"(r[8+6]));
    __asm__("sbg64tau1 %0, %1, %2" : "=r"(r[6]) : "r"(r[8+3]), "r"(r[8+7]));
    __asm__("sbg64tau2 %0, %1, %2" : "=r"(r[7]) : "r"(r[8+3]), "r"(r[8+7]));

    __asm__("sbg64lin1 %0, %1, %2" : "=r"(data->arr[0]) : "r"(r[0]), "r"(r[4]));
    __asm__("sbg64lin2 %0, %1, %2" : "=r"(data->arr[1]) : "r"(r[0]), "r"(r[4]));
    __asm__("sbg64lin1 %0, %1, %2" : "=r"(data->arr[2]) : "r"(r[1]), "r"(r[5]));
    __asm__("sbg64lin2 %0, %1, %2" : "=r"(data->arr[3]) : "r"(r[1]), "r"(r[5]));
    __asm__("sbg64lin1 %0, %1, %2" : "=r"(data->arr[4]) : "r"(r[2]), "r"(r[6]));
    __asm__("sbg64lin2 %0, %1, %2" : "=r"(data->arr[5]) : "r"(r[2]), "r"(r[6]));
    __asm__("sbg64lin1 %0, %1, %2" : "=r"(data->arr[6]) : "r"(r[3]), "r"(r[7]));
    __asm__("sbg64lin2 %0, %1, %2" : "=r"(data->arr[7]) : "r"(r[3]), "r"(r[7]));
#elif __riscv_xkgost && __riscv_xlen == 32
    uint32_t *r32 = (uint32_t*)r;

    //  Tau transform (byte transpose)
    for (size_t i = 0; i < 4; i++) {
        __asm__("sbg32tau1 %0, %1, %2" : "=r"(r32[16 + 2 * i + 0]) : "r"(r32[i + 0]), "r"(r32[i +  4]));
        __asm__("sbg32tau2 %0, %1, %2" : "=r"(r32[16 + 2 * i + 1]) : "r"(r32[i + 0]), "r"(r32[i +  4]));
        __asm__("sbg32tau1 %0, %1, %2" : "=r"(r32[16 + 2 * i + 8]) : "r"(r32[i + 8]), "r"(r32[i + 12]));
        __asm__("sbg32tau2 %0, %1, %2" : "=r"(r32[16 + 2 * i + 9]) : "r"(r32[i + 8]), "r"(r32[i + 12]));
    }

    for (size_t i = 0; i < 4; i++) {
        __asm__("sbg32tau1 %0, %1, %2" : "=r"(r32[2 * i + 0]) : "r"(r32[16 + i + 0]), "r"(r32[16 + i +  4]));
        __asm__("sbg32tau2 %0, %1, %2" : "=r"(r32[2 * i + 1]) : "r"(r32[16 + i + 0]), "r"(r32[16 + i +  4]));
        __asm__("sbg32tau1 %0, %1, %2" : "=r"(r32[2 * i + 8]) : "r"(r32[16 + i + 8]), "r"(r32[16 + i + 12]));
        __asm__("sbg32tau2 %0, %1, %2" : "=r"(r32[2 * i + 9]) : "r"(r32[16 + i + 8]), "r"(r32[16 + i + 12]));
    }

    //  Linear transformation "L"
    for (size_t i = 0; i < 8; i++) {
    uint32_t *d32 = (uint32_t*)data;
        __asm__("sbg32lin1 %0, %1, %2" : "=r"(d32[2 * i + 0]) : "r"(r32[i + 0]), "r"(r32[i + 8]));
        __asm__("sbg32lin2 %0, %1, %2" : "=r"(d32[2 * i + 1]) : "r"(r32[i + 0]), "r"(r32[i + 8]));
    }
#else
    for (size_t i = 0; i < 8; ++i) {
        r[i + 8] = 0;
        for (size_t j = 0; j < 8; ++j) {
            r[i + 8] |= (r[j] & 0xFF) << (j * 8);
            r[j] >>= 8;
        }
    }

    static uint64_t mat[64] = {
        0x8e20faa72ba0b470ull, 0x47107ddd9b505a38ull, 0xad08b0e0c3282d1cull, 0xd8045870ef14980eull,
        0x6c022c38f90a4c07ull, 0x3601161cf205268dull, 0x1b8e0b0e798c13c8ull, 0x83478b07b2468764ull,
        0xa011d380818e8f40ull, 0x5086e740ce47c920ull, 0x2843fd2067adea10ull, 0x14aff010bdd87508ull,
        0x0ad97808d06cb404ull, 0x05e23c0468365a02ull, 0x8c711e02341b2d01ull, 0x46b60f011a83988eull,
        0x90dab52a387ae76full, 0x486dd4151c3dfdb9ull, 0x24b86a840e90f0d2ull, 0x125c354207487869ull,
        0x092e94218d243cbaull, 0x8a174a9ec8121e5dull, 0x4585254f64090fa0ull, 0xaccc9ca9328a8950ull,
        0x9d4df05d5f661451ull, 0xc0a878a0a1330aa6ull, 0x60543c50de970553ull, 0x302a1e286fc58ca7ull,
        0x18150f14b9ec46ddull, 0x0c84890ad27623e0ull, 0x0642ca05693b9f70ull, 0x0321658cba93c138ull,
        0x86275df09ce8aaa8ull, 0x439da0784e745554ull, 0xafc0503c273aa42aull, 0xd960281e9d1d5215ull,
        0xe230140fc0802984ull, 0x71180a8960409a42ull, 0xb60c05ca30204d21ull, 0x5b068c651810a89eull,
        0x456c34887a3805b9ull, 0xac361a443d1c8cd2ull, 0x561b0d22900e4669ull, 0x2b838811480723baull,
        0x9bcf4486248d9f5dull, 0xc3e9224312c8c1a0ull, 0xeffa11af0964ee50ull, 0xf97d86d98a327728ull,
        0xe4fa2054a80b329cull, 0x727d102a548b194eull, 0x39b008152acb8227ull, 0x9258048415eb419dull,
        0x492c024284fbaec0ull, 0xaa16012142f35760ull, 0x550b8e9e21f7a530ull, 0xa48b474f9ef5dc18ull,
        0x70a6a56e2440598eull, 0x3853dc371220a247ull, 0x1ca76e95091051adull, 0x0edd37c48a08a6d8ull,
        0x07e095624504536cull, 0x8d70c431ac02a736ull, 0xc83862965601dd1bull, 0x641c314b2b8ee083ull,
    };

    for (size_t i = 0; i < 8; ++i) {
        data->arr[i] = 0;
        for (size_t j = 0; j < 64; ++j) {
            if ((r[i+8] >> (63 - j)) & 1) {
                data->arr[i] ^= mat[j];
            }
        }
    }
#endif
}

// Apply X transform
static inline void streebog_x(const uint512_t* x, const uint512_t* y, uint512_t* r)
{
    for (size_t i = 0; i < 8; ++i)
        r->arr[i] = x->arr[i] ^ y->arr[i];
}

// Compute h = g(N,m) according to GOST R 34.11-2012
static inline void streebog_g(uint512_t* h, const uint512_t* N, const uint512_t* m)
{
    static const uint512_t C[12] = {
        {{
            0xdd806559f2a64507, 0x05767436cc744d23, 0xa2422a08a460d315, 0x4b7ce09192676901,
            0x714eb88d7585c4fc, 0x2f6a76432e45d016, 0xebcb2f81c0657c1f, 0xb1085bda1ecadae9
        }},
        {{
            0xe679047021b19bb7, 0x55dda21bd7cbcd56, 0x5cb561c2db0aa7ca, 0x9ab5176b12d69958,
            0x61d55e0f16b50131, 0xf3feea720a232b98, 0x4fe39d460f70b5d7, 0x6fa3b58aa99d2f1a
        }},
        {{
            0x991e96f50aba0ab2, 0xc2b6f443867adb31, 0xc1c93a376062db09, 0xd3e20fe490359eb1,
            0xf2ea7514b1297b7b, 0x06f15e5f529c1f8b, 0x0a39fc286a3d8435, 0xf574dcac2bce2fc7
        }},
        {{
            0x220cbebc84e3d12e, 0x3453eaa193e837f1, 0xd8b71333935203be, 0xa9d72c82ed03d675,
            0x9d721cad685e353f, 0x488e857e335c3c7d, 0xf948e1a05d71e4dd, 0xef1fdfb3e81566d2
        }},
        {{
            0x601758fd7c6cfe57, 0x7a56a27ea9ea63f5, 0xdfff00b723271a16, 0xbfcd1747253af5a3,
            0x359e35d7800fffbd, 0x7f151c1f1686104a, 0x9a3f410c6ca92363, 0x4bea6bacad474799
        }},
        {{
            0xfa68407a46647d6e, 0xbf71c57236904f35, 0x0af21f66c2bec6b6, 0xcffaa6b71c9ab7b4,
            0x187f9ab49af08ec6, 0x2d66c4f95142a46c, 0x6fa4c33b7a3039c0, 0xae4faeae1d3ad3d9
        }},
        {{
            0x8886564d3a14d493, 0x3517454ca23c4af3, 0x06476983284a0504, 0x0992abc52d822c37,
            0xd3473e33197a93c9, 0x399ec6c7e6bf87c9, 0x51ac86febf240954, 0xf4c70e16eeaac5ec
        }},
        {{
            0xa47f0dd4bf02e71e, 0x36acc2355951a8d9, 0x69d18d2bd1a5c42f, 0xf4892bcb929b0690,
            0x89b4443b4ddbc49a, 0x4eb7f8719c36de1e, 0x03e7aa020c6e4141, 0x9b1f5b424d93c9a7
        }},
        {{
            0x7261445183235adb, 0x0e38dc92cb1f2a60, 0x7b2b8a9aa6079c54, 0x800a440bdbb2ceb1,
            0x3cd955b7e00d0984, 0x3a7d3a1b25894224, 0x944c9ad8ec165fde, 0x378f5a541631229b
        }},
        {{
            0x74b4c7fb98459ced, 0x3698fad1153bb6c3, 0x7a1e6c303b7652f4, 0x9fe76702af69334b,
            0x1fffe18a1b336103, 0x8941e71cff8a78db, 0x382ae548b2e4f3f3, 0xabbedea680056f52
        }},
        {{
            0x6bcaa4cd81f32d1b, 0xdea2594ac06fd85d, 0xefbacd1d7d476e98, 0x8a1d71efea48b9ca,
            0x2001802114846679, 0xd8fa6bbbebab0761, 0x3002c6cd635afe94, 0x7bcd9ed0efc889fb
        }},
        {{
            0x48bc924af11bd720, 0xfaf417d5d9b21b99, 0xe71da4aa88e12852, 0x5d80ef9d1891cc86,
            0xf82012d430219f9b, 0xcda43c32bcdf1d77, 0xd21380b00449b17a, 0x378ee767f11631ba
        }}
    };

    uint512_t Ki, data;

    streebog_xlps(h, N, &data);

    //[ E calculation
    Ki.arr[0] = data.arr[0];
    Ki.arr[1] = data.arr[1];
    Ki.arr[2] = data.arr[2];
    Ki.arr[3] = data.arr[3];
    Ki.arr[4] = data.arr[4];
    Ki.arr[5] = data.arr[5];
    Ki.arr[6] = data.arr[6];
    Ki.arr[7] = data.arr[7];

    streebog_xlps(&Ki, m, &data);

    for (size_t i = 0; i < 11; ++i) {
        streebog_xlps(&Ki, &C[i], &Ki);
        streebog_xlps(&Ki, &data, &data);
    }
    //]

    streebog_xlps(&Ki, &C[11], &Ki);
    streebog_x(&Ki, &data, &data);

    streebog_x(&data, h, &data);
    streebog_x(&data, m, h);
}

// Adds 512-bit integers r += x
static inline void streebog_add512(const uint512_t* x, uint512_t* r)
{
    uint64_t sum;
    uint64_t left;
    uint32_t carry = 0;

    for (size_t i = 0; i < 8; ++i) {
        left = r->arr[i];
        sum = left + x->arr[i] + carry;
        if (sum != left)
            carry = (sum < left);
        r->arr[i] = sum;
    }
}

void streebog_hash(const uint8_t* text, uint32_t len, uint32_t hash_size, uint8_t* hash)
{
    static uint512_t buf = {{}};

    uint512_t N;
    uint512_t sigma;
    uint512_t h;
    uint512_t m;

    uint8_t* m8;

    // Stage 1: Initialization
    for (size_t i = 0; i < 8; ++i) {
        N.arr[i] = 0;
        sigma.arr[i] = 0;
        h.arr[i] = (hash_size == 256) ? 0x0101010101010101 : 0x00;
    }
    buf.arr[0] = 512;

    // Stage 2: Main
    while (len > 63) {
        memcpy(&m, text, sizeof(uint512_t));
        streebog_g(&h, &N, &m);

        streebog_add512(&buf, &N);
        streebog_add512(&m, &sigma);

        text += 64;
        len -= 64;
    }

    // Stage 3: Last stage
    //[ Padding
    m8 = (uint8_t*)&m;
    memcpy(m8, text, len);
    m8[len] = 0x01;
    memset(m8 + len + 1, 0, 63 - len);
    //]

    streebog_g(&h, &N, &m);

    buf.arr[0] = len << 3; // Left text length in bits
    streebog_add512(&buf, &N);
    streebog_add512(&m, &sigma);

    buf.arr[0] = 0; // Zero
    streebog_g(&h, &buf, &N);

    streebog_g(&h, &buf, &sigma);

    // Copy result of hash function
    if (hash_size == 256)
        memcpy(hash, &h.arr[4], 32);
    else
        memcpy(hash, &h, 64);
}
