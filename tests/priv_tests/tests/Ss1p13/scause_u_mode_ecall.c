
#include <test_utils.h>

static reg_t scause_cause = 32;

static void scause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(scause);
}

bool __attribute__((weak)) scause_u_mode_ecall(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    set_shandler(scause_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    switch_mode_supervisor(MODE_U);
    TEST_COMPARE("check that currunt mode is U", MODE_U, current_mode);                                                   

    ecall(0, 0);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_USER_ECALL", CAUSE_USER_ECALL, scause_cause);

    switch_mode_supervisor(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    TEST_END();
}
