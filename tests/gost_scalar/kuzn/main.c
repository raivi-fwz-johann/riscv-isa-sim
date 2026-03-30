/*****************************************************************************
*
* @brief Test performance of GOST R 34.12-2015 Kuznechik
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

#include <stddef.h> // size_t
#include <stdint.h> // uintX_t
#include <stdio.h> // printf
#include <string.h> // memset

#include "bear_crypto_gost.h"
#include "util.h"

#define FREQ 1000000000ull
#define KK 1000000ull
#define MESSAGE_SIZE 1024 // 1 KiB
#define BLOCK_SIZE 16

// How many iterations will be performed between clock checks
#ifndef STRIDE
#define STRIDE 1024
#endif

// How long will run one test.
// NB: This is the duration of the first test (enc).
//     Decryption performes just as many iterations
//     as encryption irrespective of this parameter.
#ifndef SECONDS
#define SECONDS 1 / 4
#endif

__attribute__((aligned(4)))
int main()
{
    // Test master key for Kuznechik from A.1.4 in GOST R 34.12-2015
    uint8_t kuzn_mkey[32] __attribute__((aligned(8))) = {
        0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
    };

    // Test text for Kuznechik from A.1.5 in GOST R 34.12-2015
    uint8_t pt[BLOCK_SIZE] __attribute__((aligned(8))) = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00,
        0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88
    };

    // Test encrypted text for Kuznechik from A.1.5 in GOST R 34.12-2015
    uint8_t ct[BLOCK_SIZE] __attribute__((aligned(8))) = {
        0x7F, 0x67, 0x9D, 0x90, 0xBE, 0xBC, 0x24, 0x30,
        0x5A, 0x46, 0x8D, 0x42, 0xB9, 0xD4, 0xED, 0xCD
    };

    uint8_t keys[160] __attribute__((aligned(8)));
    uint8_t text[MESSAGE_SIZE] __attribute__((aligned(8))) = {};
    kuzn_expand_key((uint64_t*)kuzn_mkey, (uint64_t*)keys);

    memcpy(text, pt, BLOCK_SIZE);
    kuzn_encrypt((uint64_t*)(text), (uint64_t*)keys);
    for (size_t i = 0; i < BLOCK_SIZE; ++i) {
        if (text[i] != ct[i]) return i | 0xe0;
    }
    kuzn_decrypt((uint64_t*)(text), (uint64_t*)keys);
    for (size_t i = 0; i < BLOCK_SIZE; ++i) {
        if (text[i] != pt[i]) return i | 0xd0;
    }
    memset(text, 0, BLOCK_SIZE);

    size_t t = 0, it_total = 0;
    do {
        t -= read_csr(mcycle);
        for (size_t it = 0; it < STRIDE; ++it) {
            for (size_t i = 0; i < MESSAGE_SIZE; i += BLOCK_SIZE) {
                kuzn_encrypt((uint64_t*)(text + i), (uint64_t*)keys);
            }
        }
        t += read_csr(mcycle);
        it_total += STRIDE;
        printf("\rt = %010llu", t);
    } while (t < FREQ * SECONDS);
    printf("\rEnc: %lluM bit/sec @ %llu MHz CPU\n", (it_total * MESSAGE_SIZE * 8ULL * (FREQ / KK) / t), (FREQ / KK));

    t = 0;
    size_t it_limit = it_total;
    it_total = 0;
    do {
        t -= read_csr(mcycle);
        for (size_t it = 0; it < STRIDE; ++it) {
            for (size_t i = 0; i < MESSAGE_SIZE; i += BLOCK_SIZE) {
                kuzn_decrypt((uint64_t*)(text + i), (uint64_t*)keys);
            }
        }
        t += read_csr(mcycle);
        it_total += STRIDE;
        printf("\rt = %010llu", t);
    } while (it_total < it_limit);
    printf("\rDec: %lluM bit/sec @ %llu MHz CPU\n", (it_total * MESSAGE_SIZE * 8ULL * (FREQ / KK) / t), (FREQ / KK));

    for (size_t i = 0; i < MESSAGE_SIZE; ++i)
        if (text[i] != 0) return i;
    return 0;
}
