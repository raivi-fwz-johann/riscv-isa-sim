
#include <test_utils.h>

static reg_t stval_tval = 0;

static void vstval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
}

extern reg_t stval_addr_misaslign_addr;

bool __attribute__((weak)) vstval_address_misaligned_guest(){
    TEST_START();

    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(vstval_shandler);                                                                                                                                                                             

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

    TEST_END();
}
