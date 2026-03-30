
#include <test_utils.h>

static reg_t sepc_addr = 0;

static void vsepc_shandler(){
    excpt.triggered = true;
    sepc_addr = CSRR(vsepc);
}

static void vsepc_vshandler(){
    // run ecall to jump to Host hamdler and read VS register
    ecall(0,0);
}

extern reg_t sepc_gold_addr;

bool __attribute__((weak)) vsepc_host(){
    TEST_START();

    set_vshandler(vsepc_vshandler);                                                                                                                                                                             
    set_shandler(vsepc_shandler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    reg_t hedeleg_reg;
    CSRW(hedeleg, 1 << CAUSE_ILLEGAL_INSTRUCTION);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 1. Delegation is ON", 1 << CAUSE_ILLEGAL_INSTRUCTION, hedeleg_reg);

    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_host(ON);
    asm volatile (
        ".globl sepc_gold_addr\n\t"
        "sepc_gold_addr: \n\t"
        "unimp \n\t"
    );
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap intruction address", (reg_t)&sepc_gold_addr, sepc_addr);

    CSRW(hedeleg, 0L);

    TEST_END();
}
