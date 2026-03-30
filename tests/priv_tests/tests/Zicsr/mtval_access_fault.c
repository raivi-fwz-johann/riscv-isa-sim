
#include <test_utils.h>

static reg_t mtval_tval = 0;

static void mtval_mhandler(){
    excpt.triggered = true;
    mtval_tval = CSRR(mtval);
}

bool __attribute__((weak)) mtval_access_fault(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mtval_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    // access to 0x100000000 is restricted by pmp in boot.S
    asm volatile (
        "li t0, 0x100000000 \n\t"
        "lb x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check ACCESS FAULT tval value", 0x100000000, mtval_tval);

    TEST_END();
}
