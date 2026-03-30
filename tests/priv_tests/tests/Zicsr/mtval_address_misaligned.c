
#include <test_utils.h>

static reg_t mtval_tval = 0;

static void mtval_mhandler(){
    excpt.triggered = true;
    mtval_tval = CSRR(mtval);
}

extern reg_t mtval_addr_misaslign_addr;

bool __attribute__((weak)) mtval_address_misaligned(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mtval_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".balign 4\n\t"
        ".globl mtval_addr_misaslign_addr\n\t"
        "mtval_addr_misaslign_addr: \n\t"
        "la t0, mtval_addr_misaslign_addr \n\t"
        "lw x0, 1(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check MISALGNED ADDRESS tval value", (reg_t)&mtval_addr_misaslign_addr + 1, mtval_tval);

    TEST_END();
}
