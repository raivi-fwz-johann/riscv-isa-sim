
#include <test_utils.h>

bool __attribute__((weak)) misa_mxl(){
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

    // switch to 32 bit mode
    csr_set_field(misa, MISA_MXL_OFF, MISA_MXL_LEN, mxl_32);
    mxl = csr_get_field(misa, MISA_MXL_OFF, MISA_MXL_LEN);
    TEST_COMPARE("check mxl switch to 32", mxl_32, mxl);

    // shift 1 left and right. 1 shall go away
    reg = 1;
    reg <<= 32;
    reg >>=32; 
    TEST_COMPARE("check shift left, then right by 32 again", 0, reg);


    // switch back to 64 bit mode
    csr_set_field(misa, MISA_MXL_OFF, MISA_MXL_LEN, mxl_64);
    mxl = csr_get_field(misa, MISA_MXL_OFF, MISA_MXL_LEN);
    TEST_COMPARE("check mxl switch back to 64", mxl_64, mxl);
    TEST_END();
}
