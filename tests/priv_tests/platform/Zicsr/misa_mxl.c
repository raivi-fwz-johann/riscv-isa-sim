
#include <test_utils.h>

bool misa_mxl(){
    TEST_START();

    const reg_t mxl_32 = 0b01;
    const reg_t mxl_64 = 0b10;

    reg_t reg;
    reg_t mxl;

    // check that MXL is 64
    mxl = csr_get_field(misa, MISA_MXL_OFF, MISA_MXL_LEN);
    TEST_COMPARE("check mxl is 64", mxl_64, mxl);

    // shift 1 left and right. 1 shall stay
    reg = 1;
    reg <<= 32;
    reg >>=32; 
    TEST_COMPARE("check shift left, then right by 32", 1, reg);

    // try to switch to 32 bit mode, in spike MXL is RO
    csr_set_field(misa, MISA_MXL_OFF, MISA_MXL_LEN, mxl_32);
    mxl = csr_get_field(misa, MISA_MXL_OFF, MISA_MXL_LEN);
    TEST_COMPARE("check try switch to 32, mxl is stay 64", mxl_64, mxl);

    TEST_END();
}
