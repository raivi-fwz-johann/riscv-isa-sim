
#include <test_utils.h>

static reg_t stval_tval = 0;

static void stval_vshandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
}

extern reg_t vstval_addr_misaslign_addr;

bool __attribute__((weak)) shvstvala_address_misaligned(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    CSRW(medeleg, 1 << CAUSE_MISALIGNED_LOAD);
    CSRW(hedeleg, 1 << CAUSE_MISALIGNED_LOAD);

    switch_mode_and_vmode(MODE_S, ON);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    set_vshandler(stval_vshandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".balign 4\n\t"
        ".globl vstval_addr_misaslign_addr\n\t"
        "vstval_addr_misaslign_addr: \n\t"
        "la t0, vstval_addr_misaslign_addr \n\t"
        "lw x0, 1(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check MISALGNED ADDRESS tval value", (reg_t)&vstval_addr_misaslign_addr + 1, stval_tval);

    switch_mode_and_vmode(MODE_M, OFF);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    CSRW(medeleg, 0);
    CSRW(hedeleg, 0);

    TEST_END();
}
