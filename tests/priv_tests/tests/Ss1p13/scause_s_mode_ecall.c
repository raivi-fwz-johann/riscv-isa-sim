
#include <test_utils.h>

static reg_t scause_cause = 32;

static void scause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(scause);
}

bool __attribute__((weak)) scause_s_mode_ecall(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    set_shandler(scause_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    ecall(0, 0);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_SUPERVISOR_ECALL", CAUSE_SUPERVISOR_ECALL, scause_cause);

    TEST_END();
}
