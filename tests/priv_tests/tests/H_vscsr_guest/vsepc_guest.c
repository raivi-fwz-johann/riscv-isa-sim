
#include <test_utils.h>

static reg_t sepc_addr = 0;

static void vsepc_shandler(){
    excpt.triggered = true;
    sepc_addr = CSRR(sepc);
}

extern reg_t sepc_gold_addr;

bool __attribute__((weak)) vsepc_guest(){
    TEST_START();

    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(vsepc_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".globl sepc_gold_addr\n\t"
        "sepc_gold_addr: \n\t"
        "unimp \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap intruction address", (reg_t)&sepc_gold_addr, sepc_addr);

    TEST_END();
}
