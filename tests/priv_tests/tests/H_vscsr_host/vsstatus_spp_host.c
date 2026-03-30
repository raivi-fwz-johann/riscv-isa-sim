
#include <test_utils.h>

static reg_t vsstatus_spp_value = 0;

void __attribute__((weak)) vsstatus_spp_handler(){
    // run ecall to jump to Host hamdler and read VS register
    ecall(0,0);
}

void __attribute__((weak)) sstatus_spp_handler(){
    excpt.triggered = true;
    vsstatus_spp_value = csr_get_field(vsstatus, VSSTATUS_SPP_OFF, VSSTATUS_SPP_LEN);
}

bool __attribute__((weak)) vsstatus_spp_host(){
    TEST_START();

    reg_t hedeleg_reg;

    set_shandler(sstatus_spp_handler);                                                                                                                                                                             
    set_vshandler(vsstatus_spp_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    CSRW(hedeleg, 1 << CAUSE_ILLEGAL_INSTRUCTION);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 1. Delegation is ON", 1 << CAUSE_ILLEGAL_INSTRUCTION, hedeleg_reg);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    
    // check spp value when trap from S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    // ecall can't be delegeted, so use illigal instruction exception
    asm volatile ("unimp \n\t");
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that sstatus.spp value is MODE_S", MODE_S, vsstatus_spp_value);


    // check spp value when trap from U mode
    excpt.triggered = false;
    excpt.for_testing = true;

    switch_mode_guest(MODE_U);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is U", MODE_U, current_mode);                                                   

    asm volatile ("unimp \n\t");
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that sstatus.spp value is MODE_U", MODE_U, vsstatus_spp_value);

    // go back to S mode
    switch_mode_guest(MODE_S);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    
    // disable virtualization
    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // clear fields
    CSRW(hedeleg, 0);

    TEST_END();
}
