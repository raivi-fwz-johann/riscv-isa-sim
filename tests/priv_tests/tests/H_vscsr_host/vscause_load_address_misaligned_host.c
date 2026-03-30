
#include <test_utils.h>

static reg_t scause_cause = 32;

static void vscause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(vscause);
}

static void vscause_vshandler(){
    // run ecall to jump to Host hamdler and read VS register
    ecall(0,0);
}

bool __attribute__((weak)) vscause_load_address_misaligned_host(){
    TEST_START();


    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(vscause_vshandler);                                                                                                                                                                             
    set_shandler(vscause_shandler);                                                                                                                                                                             

    CSRW(hedeleg, ~0L);

    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_host(ON);
    asm volatile (
        ".balign 4 \n\t"
        "scause_misaligned_addr: \n\t"
        "la t0, scause_misaligned_addr \n\t"
        "lw x0, 1(t0) \n\t"
    );
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_MISALIGNED_LOAD", CAUSE_MISALIGNED_LOAD, scause_cause);

    CSRW(hedeleg, 0L);

    TEST_END();
}
