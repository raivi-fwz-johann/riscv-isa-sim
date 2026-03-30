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

#ifndef BEAR_CRYPTO_GOST_H
#define BEAR_CRYPTO_GOST_H

#include <stddef.h>
#include <stdint.h>
#include "rvxkgostintrin.h"

// Expand master key 256 bit to 10x 128 bit round keys (160 bytes)
void kuzn_expand_key(const uint64_t* master_key, uint64_t* keys);

// Encrypt in place 128-bit block using GOST R 34.12-2015 Kuznechik algorithm
// keys is array of round keys 160 bytes (10x 128 bit)
static inline void kuzn_encrypt(uint64_t* text, const uint64_t* keys)
{
    const uint64_t* lastkey = keys + 18;

    int64_t text_lo = text[0];
    int64_t text_hi = text[1];

    while (keys != lastkey) {
        text_hi = __rv_kuzn64esx(text_hi, keys[1]);
        text_lo = __rv_kuzn64esx(text_lo, keys[0]);

        text_hi = __rv_kuzn64el(text_lo, text_hi);
        text_lo = __rv_kuzn64el(text_hi, text_lo);

        keys += 2;
    }

    // Last round
    text[0] = text_lo ^ keys[0];
    text[1] = text_hi ^ keys[1];
}

// Decrypt in place 128-bit block using GOST R 34.12-2015 Kuznechik algorithm
// keys is array of round keys 160 bytes (10x 128 bit)
static inline void kuzn_decrypt(uint64_t* text, const uint64_t* keys)
{
    const uint64_t* lastkey = keys;

    int64_t text_lo = text[0];
    int64_t text_hi = text[1];

    keys += 18; // Move to the end of keys array

    text_lo ^= keys[0];
    text_hi ^= keys[1];

    while (keys != lastkey) {
        text_lo = __rv_kuzn64dl(text_lo, text_hi);
        text_hi = __rv_kuzn64dl(text_hi, text_lo);

        keys -= 2;

        text_lo = __rv_kuzn64dsx(text_lo, keys[0]);
        text_hi = __rv_kuzn64dsx(text_hi, keys[1]);
    }

    text[0] = text_lo;
    text[1] = text_hi;
}

// Encrypt in place 64-bit block using GOST R 34.12-2015 Magma algorithm
// master_key is 256-bit
static inline void magma_encrypt(uint8_t* text, const uint32_t* key)
{
    uint64_t txt = *((int64_t*)text);

    for (size_t j = 0; j < 3; ++j)
        for (size_t i = 0; i < 8; ++i)
            txt = __rv_magma64(txt, (int64_t)key[i]);

    for (int i = 7; i >= 0; --i)
        txt = __rv_magma64(txt, (int64_t)key[i]);

    txt = ((txt & 0x00000000FFFFFFFFLL) << 32) | ((txt & 0xFFFFFFFF00000000LL) >> 32);

    *((int64_t*)text) = txt;
}

// Decrypt in place 64-bit block using GOST R 34.12-2015 Magma algorithm
// master_key is 256-bit
static inline void magma_decrypt(uint8_t* text, const uint32_t* key)
{
    uint64_t txt = *((int64_t*)text);

    for (size_t i = 0; i < 8; ++i)
        txt = __rv_magma64(txt, (int64_t)key[i]);

    for (size_t j = 0; j < 3; ++j)
        for (int i = 7; i >= 0; --i)
            txt = __rv_magma64(txt, (int64_t)key[i]);

    txt = ((txt & 0x00000000FFFFFFFFLL) << 32) | ((txt & 0xFFFFFFFF00000000LL) >> 32);

    *((int64_t*)text) = txt;
}

// Compute hash using GOST R 34.11-2012 Streebog algorithm
// len is text length in bytes, hash_size is 256 or 512 in bits
void streebog_hash(const uint8_t* text, uint32_t len, uint32_t hash_size, uint8_t* hash);

#endif // BEAR_CRYPTO_GOST_H
