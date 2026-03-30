
#include <test_utils.h>

extern reg_t scause_access_fault_handler_return_addr;

static reg_t scause_cause = 32;

static void vscause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(vscause);
}

static void vscause_vshandler(){
    // run ecall to jump to Host hamdler and read VS register
    ecall(0,0);

    CSRW(sepc, (reg_t)(&scause_access_fault_handler_return_addr));
}

bool __attribute__((weak)) vscause_instruction_access_fault_host(){
    TEST_START();

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(vscause_vshandler);                                                                                                                                                                             
    set_shandler(vscause_shandler);                                                                                                                                                                             

    CSRW(hedeleg, ~0L);

    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_host(ON);
    
    // access to 0x7FFFFFFF is restricted by pmp in boot.S
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "jr t0 \n\t"

        ".globl scause_access_fault_handler_return_addr\n\t"
        "scause_access_fault_handler_return_addr: \n\t"
        "nop \n\t"

    );

    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_FETCH_ACCESS", CAUSE_FETCH_ACCESS, scause_cause);

    CSRW(hedeleg, 0L);

    TEST_END();
}
