
#include <test_utils.h>

static reg_t stval_tval = 0;

static void vstval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(vstval);
}

static void vstval_vshandler(){
    // run ecall to jump to Host hamdler and read VS register
    ecall(0,0);
}

bool __attribute__((weak)) vstval_access_fault_host(){
    TEST_START();

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(vstval_shandler);                                                                                                                                                                             
    set_vshandler(vstval_vshandler);                                                                                                                                                                             

    CSRW(hedeleg, ~0L);

    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_host(ON);

    // access to 0x7FFFFFFF is restricted by pmp in boot.S
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "lb x0, 0(t0) \n\t"
    );
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check ACCESS FAULT tval value", 0x7FFFFFFF, stval_tval);

    CSRW(hedeleg, 0L);

    TEST_END();
}
