
#include <test_utils.h>

static reg_t mcause_cause = 32;

static void mcause_mhandler(){
    excpt.triggered = true;
    mcause_cause = CSRR(mcause);
}

bool __attribute__((weak)) mcause_breakpoint(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mcause_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile ("ebreak \n\t");

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_BREAKPOINT", CAUSE_BREAKPOINT, mcause_cause);

    TEST_END();
}
