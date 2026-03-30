
#include <test_utils.h>

extern reg_t scause_access_fault_handler_return_addr;

static reg_t scause_cause = 32;

static void scause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(scause);
    CSRW(sepc, (reg_t)(&scause_access_fault_handler_return_addr));
}

bool __attribute__((weak)) vscause_instruction_access_fault_guest(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(scause_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;
    
    // access to 0x7FFFFFFF is restricted by pmp in boot.S
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "jr t0 \n\t"

        ".globl scause_access_fault_handler_return_addr\n\t"
        "scause_access_fault_handler_return_addr: \n\t"
        "nop \n\t"

    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_FETCH_ACCESS", CAUSE_FETCH_ACCESS, scause_cause);

    TEST_END();
}
