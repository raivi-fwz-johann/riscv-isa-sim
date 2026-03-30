
#include <test_utils.h>

static reg_t stval_tval = 0;

static void stval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
}

extern reg_t stval_addr_misaslign_addr;

bool __attribute__((weak)) sstvala_address_misaligned(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    CSRW(medeleg, 1 << CAUSE_MISALIGNED_LOAD);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(stval_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".balign 4\n\t"
        ".globl stval_addr_misaslign_addr\n\t"
        "stval_addr_misaslign_addr: \n\t"
        "la t0, stval_addr_misaslign_addr \n\t"
        "lw x0, 1(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check MISALGNED ADDRESS tval value", (reg_t)&stval_addr_misaslign_addr + 1, stval_tval);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    CSRW(medeleg, 0);

    TEST_END();
}
