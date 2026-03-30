
#include <test_utils.h>

bool sstatus_uxl(){
    TEST_START();

    const reg_t uxl_32 = 0b01;
    const reg_t uxl_64 = 0b10;

    reg_t reg;
    reg_t uxl;

    // check that UXL is 64
    uxl = csr_get_field(sstatus, SSTATUS_UXL_OFF, SSTATUS_UXL_LEN);
    TEST_COMPARE("check sstatus.uxl is 64", uxl_64, uxl);

    switch_mode_supervisor(MODE_U);
    TEST_COMPARE("switch to U mode and check that currunt mode is U", MODE_U, current_mode);  
    
    // shift 1 left and right. 1 shall stay
    reg = 1;
    reg <<= 32;
    reg >>=32; 
    TEST_COMPARE("check shift left, then right by 32", 1, reg);

    switch_mode_supervisor(MODE_S);
    TEST_COMPARE("switch to S mode and check that currunt mode is S", MODE_S, current_mode);  

    // try to switch to 32 bit sode, in spike UXL is RO
    csr_set_field(sstatus, SSTATUS_UXL_OFF, SSTATUS_UXL_LEN, uxl_32);
    uxl = csr_get_field(sstatus, SSTATUS_UXL_OFF, SSTATUS_UXL_LEN);
    TEST_COMPARE("check try switch to 32, sstatus.uxl is stay 64", uxl_64, uxl);

    TEST_END();
}
