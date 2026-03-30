
#include <test_utils.h>

static reg_t scause_cause = 32;

static void vscause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(scause);
}

bool __attribute__((weak)) vscause_load_address_misaligned_guest(){
    TEST_START();

    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(vscause_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".balign 4 \n\t"
        "scause_misaligned_addr: \n\t"
        "la t0, scause_misaligned_addr \n\t"
        "lw x0, 1(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_MISALIGNED_LOAD", CAUSE_MISALIGNED_LOAD, scause_cause);

    TEST_END();
}
