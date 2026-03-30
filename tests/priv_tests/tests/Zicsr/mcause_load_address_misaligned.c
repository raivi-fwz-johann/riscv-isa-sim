
#include <test_utils.h>

static reg_t mcause_cause = 32;

static void mcause_mhandler(){
    excpt.triggered = true;
    mcause_cause = CSRR(mcause);
}

bool __attribute__((weak)) mcause_load_address_misaligned(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mcause_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".balign 4 \n\t"
        "mcause_misaligned_addr: \n\t"
        "la t0, mcause_misaligned_addr \n\t"
        "lw x0, 1(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_MISALIGNED_LOAD", CAUSE_MISALIGNED_LOAD, mcause_cause);

    TEST_END();
}
