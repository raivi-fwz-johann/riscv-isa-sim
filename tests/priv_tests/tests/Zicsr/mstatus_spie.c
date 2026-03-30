
#include <test_utils.h>

static reg_t mstatus_spie_value = 0;

void __attribute__((weak)) mstatus_spie_shandler(){
    // run ecall to trigger M handler, switch to M mode and read mstatus.spie 
    ecall(0,0);
}

void __attribute__((weak)) mstatus_spie_mhandler(){
    if (!excpt.for_testing){
        ERROR("Unexcpected exception");
        return;
    }
    mstatus_spie_value = csr_get_field(mstatus, MSTATUS_SPIE_OFF, MSTATUS_SPIE_LEN);
    excpt.triggered = true;
}

bool __attribute__((weak)) mstatus_spie(){
    TEST_START();

    reg_t spie, sie;

    set_mhandler(mstatus_spie_mhandler);                                                                                                                                                                             
    set_shandler(mstatus_spie_shandler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // delegation illigal instruction handle to S mode
    CSRW(medeleg, 1 << CAUSE_ILLEGAL_INSTRUCTION);

    // check spie value when mstatus.sie is clear
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN, 0);
    sie = csr_get_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN);
    TEST_COMPARE("check mstatus.sie is clear", 0, sie);

    switch_mode(MODE_S);
    TEST_COMPARE("switch to S mode and check that currunt mode is S", MODE_S, current_mode);  
    
    asm volatile ("unimp \n\t"); // run invalid instruction to trigger S handler
    
    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that spie value is 0", 0, mstatus_spie_value);

    switch_mode(MODE_M);
    TEST_COMPARE("Switch to M and check that currunt mode is M", MODE_M, current_mode);                                                   

    // check spie value when mstatus.sie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN, 1);
    sie = csr_get_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN);
    TEST_COMPARE("check mstatus.sie is set", 1, sie);

    switch_mode(MODE_S);
    TEST_COMPARE("switch to S mode and check that currunt mode is S", MODE_S, current_mode);  
    
    asm volatile ("unimp \n\t"); // run invalid instruction to trigger S handler
    
    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that spie value is 1", 1, mstatus_spie_value);

    switch_mode(MODE_M);
    TEST_COMPARE("Switch to M and check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear fields
    csr_set_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN, 0);
    CSRW(medeleg, 0);
    
    TEST_END();
}
