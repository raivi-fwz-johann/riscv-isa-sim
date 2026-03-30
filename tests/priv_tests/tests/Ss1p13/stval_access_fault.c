
#include <test_utils.h>

static reg_t stval_tval = 0;

static void stval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
}

bool __attribute__((weak)) stval_access_fault(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(stval_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    // access to 0x7FFFFFFF is restricted by pmp in boot.S
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "lb x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check PAGE FAULT tval value", 0x7FFFFFFF, stval_tval);

    TEST_END();
}
