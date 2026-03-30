/*****************************************************************************
*
* @brief Test performance of GOST R 34.12-2015 Magma
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
#define BLOCK_SIZE 8

// How many iterations will be performed between clock checks
#ifndef STRIDE
#define STRIDE 1024
#endif

// How long will run one test.
// NB: This is the duration of the first test (enc).
//     Decryption performes just as many iterations
//     as encryption irrespective of this parameter.
#ifndef SECONDS
#define SECONDS 1
#endif

__attribute__((aligned(4)))
int main()
{
    // Test master key for Magma from A.2.3 in GOST R 34.12-2015
    uint8_t magma_mkey[32] __attribute__((aligned(8))) = {
        0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
        0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
        0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
    };

    // Test test for Magma from A.2.4 in GOST R 34.12-2015
    uint8_t pt[BLOCK_SIZE] __attribute__((aligned(8))) = {
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10
    };

    // Test encrypted text for Magma from A.2.4 in GOST R 34.12-2015
    uint8_t ct[BLOCK_SIZE] __attribute__((aligned(8))) = {
        0x4e, 0xe9, 0x01, 0xe5, 0xc2, 0xd8, 0xca, 0x3d
    };

    uint8_t text[MESSAGE_SIZE] __attribute__((aligned(8))) = {};

    memcpy(text, pt, BLOCK_SIZE);
    magma_encrypt((uint8_t*)(text), (uint32_t*)magma_mkey);
    for (size_t i = 0; i < BLOCK_SIZE; ++i) {
        if (text[i] != ct[i]) return i | 0xe0;
    }
    magma_decrypt((uint8_t*)(text), (uint32_t*)magma_mkey);
    for (size_t i = 0; i < BLOCK_SIZE; ++i) {
        if (text[i] != pt[i]) return i | 0xd0;
    }
    memset(text, 0, BLOCK_SIZE);

    size_t t = 0, it_total = 0;
    do {
        t -= read_csr(mcycle);
        for (size_t it = 0; it < STRIDE; ++it) {
            for (size_t i = 0; i < MESSAGE_SIZE; i += BLOCK_SIZE) {
                magma_encrypt((uint8_t*)(text + i), (uint32_t*)magma_mkey);
            }
        }
        t += read_csr(mcycle);
        it_total += STRIDE;
        printf("\rt = %010llu", t);
    } while (t < FREQ * SECONDS);
    printf("\rDec: %lluM bit/sec @ %llu MHz CPU\n", (it_total * MESSAGE_SIZE * 8ULL * (FREQ / KK) / t), (FREQ / KK));

    t = 0;
    size_t it_limit = it_total;
    it_total = 0;
    do {
        t -= read_csr(mcycle);
        for (size_t it = 0; it < STRIDE; ++it) {
            for (size_t i = 0; i < MESSAGE_SIZE; i += BLOCK_SIZE) {
                magma_decrypt((uint8_t*)(text + i), (uint32_t*)magma_mkey);
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
