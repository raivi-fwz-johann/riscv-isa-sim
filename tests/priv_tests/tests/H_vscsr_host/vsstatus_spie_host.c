
#include <test_utils.h>

static reg_t vsstatus_spie_value = 0;

void __attribute__((weak)) vsstatus_spie_handler(){
    // run ecall to jump to Host hamdler and read VS register
    ecall(0,0);
}

void __attribute__((weak)) sstatus_spie_handler(){
    excpt.triggered = true;
    vsstatus_spie_value = csr_get_field(vsstatus, VSSTATUS_SPIE_OFF, VSSTATUS_SPIE_LEN);
}

bool __attribute__((weak)) vsstatus_spie_host(){
    TEST_START();

    reg_t spie, sie, hedeleg_reg;

    set_vshandler(vsstatus_spie_handler);                                                                                                                                                                             
    set_shandler(sstatus_spie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    CSRW(hedeleg, 1 << CAUSE_ILLEGAL_INSTRUCTION);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 1. Delegation is ON", 1 << CAUSE_ILLEGAL_INSTRUCTION, hedeleg_reg);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    // check spie value when sstatus.sie is clear
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is clear", 0, sie);

    // ecall can't be delegeted, so use illigal instruction exception
    asm volatile ("unimp \n\t");
    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that spie value is 0", 0, vsstatus_spie_value);

    // check spie value when sstatus.sie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    asm volatile ("unimp \n\t");
    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that spie value is 1", 1, vsstatus_spie_value);

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // clear fields
    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 0);
    CSRW(hedeleg, 0);

    TEST_END();
}
