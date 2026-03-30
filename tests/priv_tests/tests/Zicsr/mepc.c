
#include <test_utils.h>

static reg_t mepc_addr = 0;

static void mepc_mhandler(){
    excpt.triggered = true;
    mepc_addr = CSRR(mepc);
}

extern reg_t mepc_gold_addr;

bool __attribute__((weak)) mepc(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mepc_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".globl mepc_gold_addr\n\t"
        "mepc_gold_addr: \n\t"
        "unimp \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap intruction address", (reg_t)&mepc_gold_addr, mepc_addr);

    TEST_END();
}
