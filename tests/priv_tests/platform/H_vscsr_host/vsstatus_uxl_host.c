
#include <test_utils.h>

bool vsstatus_uxl_host(){
    TEST_START();

    const reg_t uxl_32 = 0b01;
    const reg_t uxl_64 = 0b10;

    reg_t reg;
    reg_t uxl;
    reg_t hedeleg_reg;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    
    // delegate illigal instruction exception, because switch_mode_guest() use it to switch to user mode
    CSRW(hedeleg, 1 << CAUSE_ILLEGAL_INSTRUCTION);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 1. Delegation is ON", 1 << CAUSE_ILLEGAL_INSTRUCTION, hedeleg_reg);

    // check that UXL is 64
    uxl = csr_get_field(vsstatus, VSSTATUS_UXL_OFF, VSSTATUS_UXL_LEN);
    TEST_COMPARE("check vsstatus.uxl is 64", uxl_64, uxl);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    switch_mode_guest(MODE_U);
    TEST_COMPARE("switch to U mode and check that currunt mode is U", MODE_U, current_mode);  
    
    // shift 1 left and right. 1 shall stay
    reg = 1;
    reg <<= 32;
    reg >>=32; 
    TEST_COMPARE("check shift left, then right by 32", 1, reg);

    switch_mode_guest(MODE_S);
    TEST_COMPARE("switch to S mode and check that currunt mode is S", MODE_S, current_mode);  

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // try to switch to 32 bit sode, in spike UXL is RO
    csr_set_field(vsstatus, VSSTATUS_UXL_OFF, VSSTATUS_UXL_LEN, uxl_32);
    uxl = csr_get_field(sstatus, VSSTATUS_UXL_OFF, VSSTATUS_UXL_LEN);
    TEST_COMPARE("check try switch to 32, vsstatus.uxl is stay 64", uxl_64, uxl);

    CSRW(hedeleg, 0L);

    TEST_END();
}
