
#include <test_utils.h>

static reg_t scause_cause = 32;

static void scause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(scause);
}

bool __attribute__((weak)) scause_store_address_misaligned(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(scause_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".balign 4 \n\t"
        "scause_misaligned_addr: \n\t"
        "la t0, scause_misaligned_addr \n\t"
        "sw x0, 1(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_MISALIGNED_STORE", CAUSE_MISALIGNED_STORE, scause_cause);

    TEST_END();
}
