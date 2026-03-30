
#include <test_utils.h>

static reg_t stval_tval = 0;

static void stval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
}

extern reg_t stval_break_addr;
extern reg_t stval_cbreak_addr;

bool __attribute__((weak)) sstvala_breakpoint(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    CSRW(medeleg, 1 << CAUSE_BREAKPOINT);

    switch_mode(MODE_S);

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(stval_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".globl stval_break_addr\n\t"
        "stval_break_addr: \n\t"
        "ebreak \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check BREAKPOINT ADDRESS tval value", (reg_t)&stval_break_addr, stval_tval);


    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".globl stval_cbreak_addr\n\t"
        "stval_cbreak_addr: \n\t"
        "c.ebreak \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check compress BREAKPOINT ADDRESS tval value", (reg_t)&stval_cbreak_addr, stval_tval);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    CSRW(medeleg, 0);
   

    TEST_END();
}
