
#include <test_utils.h>

static reg_t stval_tval = 0;

static void vstval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
}

extern reg_t stval_break_addr;

bool __attribute__((weak)) vstval_breakpoint_guest(){
    TEST_START();

    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(vstval_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".globl stval_break_addr\n\t"
        "stval_break_addr: \n\t"
        "ebreak \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check BREAKPOINT ADDRESS tval value", (reg_t)&stval_break_addr, stval_tval);

    TEST_END();
}
