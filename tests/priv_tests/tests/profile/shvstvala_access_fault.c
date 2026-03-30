
#include <test_utils.h>

static reg_t stval_tval = 0;

static void stval_vshandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
}

bool __attribute__((weak)) shvstvala_access_fault(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    CSRW(medeleg, 1 << CAUSE_LOAD_ACCESS);
    CSRW(hedeleg, 1 << CAUSE_LOAD_ACCESS);

    switch_mode_and_vmode(MODE_S, ON);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    set_vshandler(stval_vshandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    // access to 0x7FFFFFFF is restricted by pmp in boot.S
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "lb x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check ACCESS FAULT tval value", 0x7FFFFFFF, stval_tval);

    switch_mode_and_vmode(MODE_M, OFF);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    CSRW(medeleg, 0);
    CSRW(hedeleg, 0);

    TEST_END();
}
