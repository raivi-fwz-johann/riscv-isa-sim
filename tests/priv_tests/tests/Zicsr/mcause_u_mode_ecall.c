
#include <test_utils.h>

static reg_t mcause_cause = 32;

static void mcause_mhandler(){
    excpt.triggered = true;
    mcause_cause = CSRR(mcause);
}

bool __attribute__((weak)) mcause_u_mode_ecall(){
    TEST_START();

    reg_t medeleg_reg;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mcause_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(medeleg, 0);
    medeleg_reg = CSRR(medeleg);
    TEST_COMPARE("clear and check that delegation is OFF", 0, medeleg_reg);

    switch_mode(MODE_U);
    TEST_COMPARE("check that currunt mode is U", MODE_U, current_mode);                                                   

    ecall(0, 0);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_USER_ECALL", CAUSE_USER_ECALL, mcause_cause);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    TEST_END();
}
