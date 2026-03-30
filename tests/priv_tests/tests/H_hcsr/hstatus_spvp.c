
#include <test_utils.h>

static reg_t hstatus_spvp_value = 0;

void __attribute__((weak)) hstatus_spvp_handler(){
    excpt.triggered = true;
    hstatus_spvp_value = csr_get_field(hstatus, HSTATUS_SPVP_OFF, HSTATUS_SPVP_LEN);
}

bool __attribute__((weak)) hstatus_spvp(){
    TEST_START();

    set_shandler(hstatus_spvp_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // need to delegate illigal instruction exception, because switch_mode_guest() need it
    CSRW(hedeleg, 1 << CAUSE_ILLEGAL_INSTRUCTION);
    reg_t hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 1. Delegation is ON", 1 << CAUSE_ILLEGAL_INSTRUCTION, hedeleg_reg);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    
    // check spvp value when trap from S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    TEST_COMPARE("check that hstatus.spvp value is MODE_S", MODE_S, hstatus_spvp_value);


    // check spvp value when trap from U mode
    excpt.triggered = false;
    excpt.for_testing = true;

    switch_mode_guest(MODE_U);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is U", MODE_U, current_mode);                                                   

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    TEST_COMPARE("check that hstatus.spvp value is MODE_U", MODE_U, hstatus_spvp_value);

    // go back to S mode
    switch_mode_guest(MODE_S);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    
    // disable virtualization
    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // clear deegation
    CSRW(hedeleg, 0);

    TEST_END();
}
