
#include <test_utils.h>

static reg_t sstatus_spie_value = 0;

void __attribute__((weak)) sstatus_spie_handler(){
    excpt.triggered = true;
    sstatus_spie_value = csr_get_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN);
}

bool __attribute__((weak)) sstatus_spie(){
    TEST_START();

    reg_t spie, sie;

    set_shandler(sstatus_spie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // check spie value when sstatus.sie is clear
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is clear", 0, sie);

    ecall(0,0);
    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that spie value is 0", 0, sstatus_spie_value);

    // check spie value when sstatus.sie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    ecall(0,0);
    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that spie value is 1", 1, sstatus_spie_value);

    // clear fields
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    
    TEST_END();
}
