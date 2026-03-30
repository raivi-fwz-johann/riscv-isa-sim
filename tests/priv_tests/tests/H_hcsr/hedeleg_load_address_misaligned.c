
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

bool __attribute__((weak)) hedeleg_load_address_misaligned(){
    TEST_START();

    reg_t hedeleg_reg;
    reg_t temp;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    set_shandler(hedeleg_shandler);                                                                                                                                                                             
    set_vshandler(hedeleg_vshandler);                                                                                                                                                                             


    // check that trap without delegation is handled in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(hedeleg, 0);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 0. Delegation is OFF", 0, hedeleg_reg);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    asm volatile (
        ".balign 4 \n\t"
        "hcause_misaligned_addr_1: \n\t"
        "la t0, hcause_misaligned_addr_1 \n\t"
        "lw x0, 1(t0) \n\t"
    );

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in S mode", OFF, hedeleg_v_mode);


    // check that trap with delegation is handled in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(hedeleg, 1 << CAUSE_MISALIGNED_LOAD);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 1. Delegation is ON", 1 << CAUSE_MISALIGNED_LOAD, hedeleg_reg);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    asm volatile (
        ".balign 4 \n\t"
        "hcause_misaligned_addr_2: \n\t"
        "la t0, hcause_misaligned_addr_2 \n\t"
        "lw x0, 1(t0) \n\t"
    );

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in VS mode", ON, hedeleg_v_mode);
    TEST_COMPARE("check trap cause", CAUSE_MISALIGNED_LOAD, hedeleg_cause);

    //
    //clear state
    CSRW(hedeleg, 0);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 0. Delegation is OFF", 0, hedeleg_reg);

    TEST_END();
}
