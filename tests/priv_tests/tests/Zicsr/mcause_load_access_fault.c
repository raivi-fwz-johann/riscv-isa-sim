
#include <test_utils.h>

static reg_t mcause_cause = 32;

static void mcause_mhandler(){
    excpt.triggered = true;
    mcause_cause = CSRR(mcause);
}

bool __attribute__((weak)) mcause_load_access_fault(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mcause_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;
    
    // access to 0x7FFFFFFF is restricted by pmp in boot.S
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "lb x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_ACCESS", CAUSE_LOAD_ACCESS, mcause_cause);

    TEST_END();
}
