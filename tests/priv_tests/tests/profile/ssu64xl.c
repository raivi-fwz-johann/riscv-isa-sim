
#include <test_utils.h>

bool __attribute__((weak)) ssu64xl(){
    TEST_START();

    const reg_t uxl_64 = 0b10;

    reg_t reg;
    reg_t uxl;

    // check that UXL is 64
    uxl = csr_get_field(sstatus, SSTATUS_UXL_OFF, SSTATUS_UXL_LEN);
    TEST_COMPARE("check sstatus.uxl is 64", uxl_64, uxl);

    switch_mode(MODE_U);
    TEST_COMPARE("switch to U mode and check that currunt mode is U", MODE_U, current_mode);  
    
    // shift 1 left and right. 1 shall stay
    reg = 1;
    reg <<= 32;
    reg >>=32; 
    TEST_COMPARE("check shift left, then right by 32", 1, reg);

    switch_mode(MODE_M);
    TEST_COMPARE("switch to M mode and check that currunt mode is M", MODE_M, current_mode);  


    TEST_END();
}
