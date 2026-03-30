
#include <test_utils.h>

bool __attribute__((weak)) mstatus_sxl(){
    TEST_START();

    const reg_t sxl_32 = 0b01;
    const reg_t sxl_64 = 0b10;

    reg_t reg;
    reg_t sxl;

    // clear delegation register
    CSRW(medeleg, 0);

    // check that SXL is 64
    sxl = csr_get_field(mstatus, MSTATUS_SXL_OFF, MSTATUS_SXL_LEN);
    TEST_COMPARE("check mstatus.sxl is 64", sxl_64, sxl);

    switch_mode(MODE_S);
    TEST_COMPARE("switch to S mode and check that currunt mode is S", MODE_S, current_mode);  
    
    // shift 1 left and right. 1 shall stay
    reg = 1;
    reg <<= 32;
    reg >>=32; 
    TEST_COMPARE("check shift left, then right by 32", 1, reg);

    switch_mode(MODE_M);
    TEST_COMPARE("switch to M mode and check that currunt mode is M", MODE_M, current_mode);  

    // try to switch to 32 bit mode, in spike SXL is RO
    csr_set_field(mstatus, MSTATUS_SXL_OFF, MSTATUS_SXL_LEN, sxl_32);
    sxl = csr_get_field(mstatus, MSTATUS_SXL_OFF, MSTATUS_SXL_LEN);
    TEST_COMPARE("check try switch to 32, mstatus.sxl is stay 64", sxl_64, sxl);

    TEST_END();
}
