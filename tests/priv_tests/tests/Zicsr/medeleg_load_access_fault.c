
#include <test_utils.h>

static reg_t medeleg_mode = 0;
static reg_t medeleg_cause = 32;

static void medeleg_mhandler(){
    excpt.triggered = true;
    medeleg_mode = MODE_M;
    medeleg_cause = CSRR(mcause);
}

static void medeleg_shandler(){
    excpt.triggered = true;
    medeleg_mode = MODE_S;
    medeleg_cause = CSRR(scause);
}

bool __attribute__((weak)) medeleg_load_access_fault(){
    TEST_START();

    reg_t medeleg_reg;
    reg_t temp;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(medeleg_mhandler);                                                                                                                                                                             
    set_shandler(medeleg_shandler);                                                                                                                                                                             

    // check that trap without delegation is handled in M mode
    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(medeleg, 0);
    medeleg_reg = CSRR(medeleg);
    TEST_COMPARE("clear and check that medeleg bit is 0. Delegation is OFF", 0, medeleg_reg);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    
    // access to 0x7FFFFFFF is restricted by pmp in boot.S
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "lb x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in M mode", MODE_M, medeleg_mode);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   


    // check that trap with delegation is handled in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(medeleg, 1 << CAUSE_LOAD_ACCESS);
    medeleg_reg = CSRR(medeleg);
    TEST_COMPARE("clear and check that medeleg bit is 1. Delegation is ON", 1 << CAUSE_LOAD_ACCESS, medeleg_reg);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    
    // access to 0x7FFFFFFF is restricted by pmp in boot.S
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "lb x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in S mode", MODE_S, medeleg_mode);
    TEST_COMPARE("check trap cause",CAUSE_LOAD_ACCESS , medeleg_cause);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    TEST_END();
}
