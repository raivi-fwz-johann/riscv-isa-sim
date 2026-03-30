
#include <test_utils.h>

static reg_t mtval_tval = 0;

static void mtval_mhandler(){
    excpt.triggered = true;
    mtval_tval = CSRR(mtval);
}

extern reg_t mtval_break_addr;

bool __attribute__((weak)) mtval_breakpoint(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mtval_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".globl mtval_break_addr\n\t"
        "mtval_break_addr: \n\t"
        "ebreak \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check BREAKPOINT ADDRESS tval value", (reg_t)&mtval_break_addr, mtval_tval);

    TEST_END();
}
