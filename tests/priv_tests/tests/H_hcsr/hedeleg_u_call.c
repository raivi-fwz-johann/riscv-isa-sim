
#include <test_utils.h>

static reg_t hedeleg_v_mode = 0;
static reg_t hedeleg_cause = 32;

static void hedeleg_shandler(){
    excpt.triggered = true;
    hedeleg_v_mode = OFF;
    hedeleg_cause = CSRR(scause);
}

static void hedeleg_vshandler(){
    excpt.triggered = true;
    hedeleg_v_mode = ON;
    hedeleg_cause = CSRR(scause);
}

bool __attribute__((weak)) hedeleg_u_call(){
    TEST_START();

    reg_t hedeleg_reg;
    reg_t temp;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    set_shandler(hedeleg_shandler);                                                                                                                                                                             
    set_vshandler(hedeleg_vshandler);                                                                                                                                                                             

    // need to delegate illigal instruction exception, because switch_mode_guest() need it
    CSRW(hedeleg, 1 << CAUSE_ILLEGAL_INSTRUCTION);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 1. Delegation is ON", 1 << CAUSE_ILLEGAL_INSTRUCTION, hedeleg_reg);

    // check that trap without delegation is handled in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    switch_mode_guest(MODE_U);
    TEST_COMPARE("check that currunt mode is U", MODE_U, current_mode);                                                   

    ecall(0,0);

    switch_mode_guest(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in S mode", OFF, hedeleg_v_mode);

    // check that trap with delegation is handled in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(hedeleg, 1 << CAUSE_USER_ECALL | 1 << CAUSE_ILLEGAL_INSTRUCTION);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 1. Delegation is ON", 1 << CAUSE_USER_ECALL | 1 << CAUSE_ILLEGAL_INSTRUCTION, hedeleg_reg);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    switch_mode_guest(MODE_U);
    TEST_COMPARE("check that currunt mode is U", MODE_U, current_mode);                                                   

    ecall(0,0);

    switch_mode_guest(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in VS mode", ON, hedeleg_v_mode);
    TEST_COMPARE("check trap cause", CAUSE_USER_ECALL, hedeleg_cause);
    
    //clear state
    CSRW(hedeleg, 0);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 0. Delegation is OFF", 0, hedeleg_reg);

    TEST_END();
}
