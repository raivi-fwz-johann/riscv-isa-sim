
#include <test_utils.h>

bool __attribute__((weak)) mstatus_uxl(){
    TEST_START();

    const reg_t uxl_32 = 0b01;
    const reg_t uxl_64 = 0b10;

    reg_t reg;
    reg_t uxl;

    // clear delegation register
    CSRW(medeleg, 0);

    // check that UXL is 64
    uxl = csr_get_field(mstatus, MSTATUS_UXL_OFF, MSTATUS_UXL_LEN);
    TEST_COMPARE("check mstatus.uxl is 64", uxl_64, uxl);

    switch_mode(MODE_U);
    TEST_COMPARE("switch to U mode and check that currunt mode is U", MODE_U, current_mode);  
    
    // shift 1 left and right. 1 shall stay
    reg = 1;
    reg <<= 32;
    reg >>=32; 
    TEST_COMPARE("check shift left, then right by 32", 1, reg);

    switch_mode(MODE_M);
    TEST_COMPARE("switch to M mode and check that currunt mode is M", MODE_M, current_mode);  

    // try to switch to 32 bit mode, in spike UXL is RO
    csr_set_field(mstatus, MSTATUS_UXL_OFF, MSTATUS_UXL_LEN, uxl_32);
    uxl = csr_get_field(mstatus, MSTATUS_UXL_OFF, MSTATUS_UXL_LEN);
    TEST_COMPARE("check try switch to 32, mstatus.uxl is stay 64", uxl_64, uxl);

    TEST_END();
}
