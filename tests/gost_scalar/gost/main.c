/*****************************************************************************
*
* @brief Test GOST functions and intrinsics
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

#include "bear_crypto_gost.h"

int main()
{
    int ret = 0;

    // Test vectors for L-trasform from A.1.3 in GOST R 34.12-2015
    uint8_t lin[64] __attribute__((aligned(16))) = {
        0x64, 0xa5, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

        0xd4, 0x56, 0x58, 0x4d, 0xd0, 0xe3, 0xe8, 0x4c,
        0xc3, 0x16, 0x6e, 0x4b, 0x7f, 0xa2, 0x89, 0x0d,

        0x79, 0xd2, 0x62, 0x21, 0xb8, 0x7b, 0x58, 0x4c,
        0xd4, 0x2f, 0xbc, 0x4f, 0xfe, 0xa5, 0xde, 0x9a,

        0x0e, 0x93, 0x69, 0x1a, 0x0c, 0xfc, 0x60, 0x40,
        0x8b, 0x7b, 0x68, 0xf6, 0x6b, 0x51, 0x3c, 0x13
    };

    uint8_t lou[64] __attribute__((aligned(16))) = {
        0xd4, 0x56, 0x58, 0x4d, 0xd0, 0xe3, 0xe8, 0x4c,
        0xc3, 0x16, 0x6e, 0x4b, 0x7f, 0xa2, 0x89, 0x0d,

        0x79, 0xd2, 0x62, 0x21, 0xb8, 0x7b, 0x58, 0x4c,
        0xd4, 0x2f, 0xbc, 0x4f, 0xfe, 0xa5, 0xde, 0x9a,

        0x0e, 0x93, 0x69, 0x1a, 0x0c, 0xfc, 0x60, 0x40,
        0x8b, 0x7b, 0x68, 0xf6, 0x6b, 0x51, 0x3c, 0x13,

        0xe6, 0xa8, 0x09, 0x4f, 0xee, 0x0a, 0xa2, 0x04,
        0xfd, 0x97, 0xbc, 0xb0, 0xb4, 0x4b, 0x85, 0x80
    };

    // Test master key for Magma from A.2.3 in GOST R 34.12-2015
    uint8_t mkey[32] __attribute__((aligned(8))) = {
        0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
        0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
        0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
    };

    // Test vectors for Magma rounds from A.2.4 in GOST R 34.12-2015
    uint8_t magma_in[64] __attribute__((aligned(8))) = {
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
        0x76, 0x54, 0x32, 0x10, 0x28, 0xda, 0x3b, 0x14,
        0x28, 0xda, 0x3b, 0x14, 0xb1, 0x43, 0x37, 0xa5,
        0xb1, 0x43, 0x37, 0xa5, 0x63, 0x3a, 0x7c, 0x68,
        0x63, 0x3a, 0x7c, 0x68, 0xea, 0x89, 0xc0, 0x2c,
        0xea, 0x89, 0xc0, 0x2c, 0x11, 0xfe, 0x72, 0x6d,
        0x11, 0xfe, 0x72, 0x6d, 0xad, 0x03, 0x10, 0xa4,
        0xad, 0x03, 0x10, 0xa4, 0x37, 0xd9, 0x7f, 0x25
    };

    uint8_t magma_ou[64] __attribute__((aligned(8))) = {
        0x76, 0x54, 0x32, 0x10, 0x28, 0xda, 0x3b, 0x14,
        0x28, 0xda, 0x3b, 0x14, 0xb1, 0x43, 0x37, 0xa5,
        0xb1, 0x43, 0x37, 0xa5, 0x63, 0x3a, 0x7c, 0x68,
        0x63, 0x3a, 0x7c, 0x68, 0xea, 0x89, 0xc0, 0x2c,
        0xea, 0x89, 0xc0, 0x2c, 0x11, 0xfe, 0x72, 0x6d,
        0x11, 0xfe, 0x72, 0x6d, 0xad, 0x03, 0x10, 0xa4,
        0xad, 0x03, 0x10, 0xa4, 0x37, 0xd9, 0x7f, 0x25,
        0x37, 0xd9, 0x7f, 0x25, 0x46, 0x32, 0x46, 0x15
    };

    uint64_t *ilo = (uint64_t*) lin;
    uint64_t *ihi = (uint64_t*) (lin + 8);

    uint64_t *olo = (uint64_t*) lou;
    uint64_t *ohi = (uint64_t*) (lou + 8);

    uint32_t *mkey32 = (uint32_t*)mkey;
    uint64_t *magma_in64 = (uint64_t*)magma_in;
    uint64_t *magma_ou64 = (uint64_t*)magma_ou;

    // Test S-transform of GOST R 34.12-2015 Kuznechik
    // Use test vectors from A.1.1 in GOST R 34.12-2015
    ret |= (__rv_kuzn64esx(0x1122334455667700, 0) != 0x7765aeea0c9a7efc);
    ret |= (__rv_kuzn64esx(0xffeeddccbbaa9988, 0) != 0xb66cd8887d38e8d7);

    ret |= (__rv_kuzn64esx(0x7765aeea0c9a7efc, 0) != 0x7e7b262523280d39);
    ret |= (__rv_kuzn64esx(0xb66cd8887d38e8d7, 0) != 0x559d8dd7bd06cbfe);

    ret |= (__rv_kuzn64esx(0x7e7b262523280d39, 0) != 0x0d80ef5c5a81c50b);
    ret |= (__rv_kuzn64esx(0x559d8dd7bd06cbfe, 0) != 0x0c3322fed531e463);

    ret |= (__rv_kuzn64esx(0x0d80ef5c5a81c50b, 0) != 0xc5df529c13f5acda);
    ret |= (__rv_kuzn64esx(0x0c3322fed531e463, 0) != 0x23ae65633f842d29);

    // Test Inverse S-transform of GOST R 34.12-2015 Kuznechik
    // Use test vectors from A.1.1 in GOST R 34.12-2015
    ret |= (__rv_kuzn64dsx(0x7765aeea0c9a7efc, 0) != 0x1122334455667700);
    ret |= (__rv_kuzn64dsx(0xb66cd8887d38e8d7, 0) != 0xffeeddccbbaa9988);

    ret |= (__rv_kuzn64dsx(0x7e7b262523280d39, 0) != 0x7765aeea0c9a7efc);
    ret |= (__rv_kuzn64dsx(0x559d8dd7bd06cbfe, 0) != 0xb66cd8887d38e8d7);

    ret |= (__rv_kuzn64dsx(0x0d80ef5c5a81c50b, 0) != 0x7e7b262523280d39);
    ret |= (__rv_kuzn64dsx(0x0c3322fed531e463, 0) != 0x559d8dd7bd06cbfe);

    ret |= (__rv_kuzn64dsx(0xc5df529c13f5acda, 0) != 0x0d80ef5c5a81c50b);
    ret |= (__rv_kuzn64dsx(0x23ae65633f842d29, 0) != 0x0c3322fed531e463);

    // Test L-transform of GOST R 34.12-2015 Kuznechik
    // Use test vectors from A.1.3 in GOST R 34.12-2015
    for (size_t i = 0; i < 4; ++i) {
        ret |= (__rv_kuzn64el(*ilo, *ihi) != *ohi);
        ret |= (__rv_kuzn64dl(*olo, *ohi) != *ilo);

        ilo += 2;
        ihi += 2;
        olo += 2;
        ohi += 2;
    }

    // Test G-transform GOST R 34.12-2015 Magma
    // Use test vectors from A.2.4 in GOST R 34.12-2015
    for (size_t i = 0; i < 8; ++i)
        ret |= (__rv_magma64(magma_in64[i], mkey32[i]) != magma_ou64[i]);

    return ret;
}
