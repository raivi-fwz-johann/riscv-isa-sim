
#include <test_utils.h>

static reg_t mstatus_spp_value = 0;

void __attribute__((weak)) mstatus_spp_shandler(){
    // run ecall to trigger M handler, switch to M mode and read mstatus.spp 
    ecall(0,0);
}

void __attribute__((weak)) mstatus_spp_mhandler(){
    if (!excpt.for_testing){
        ERROR("Unexcpected exception");
        return;
    }
    mstatus_spp_value = csr_get_field(mstatus, MSTATUS_SPP_OFF, MSTATUS_SPP_LEN);
    excpt.triggered = true;
}


bool __attribute__((weak)) mstatus_spp(){
    TEST_START();

    set_mhandler(mstatus_spp_mhandler);                                                                                                                                                                             
    set_shandler(mstatus_spp_shandler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // delegation illigal instruction handle to S mode
    CSRW(medeleg, 1 << CAUSE_ILLEGAL_INSTRUCTION);


    // check spp value when trap from S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    switch_mode(MODE_S);
    TEST_COMPARE("switch to S mode and check that currunt mode is S", MODE_S, current_mode);  
    
    asm volatile ("unimp \n\t"); // run invalid instruction to trigger S handler

    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that mstatus.spp value is MODE_S", MODE_S, mstatus_spp_value);


    // check spp value when trap from U mode
    excpt.triggered = false;
    excpt.for_testing = true;

    switch_mode(MODE_U);
    TEST_COMPARE("switch to U mode and check that currunt mode is U", MODE_U, current_mode);  
    
    asm volatile ("unimp \n\t"); // run invalid instruction to trigger S handler

    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that mstatus.spp value is MODE_U", MODE_U, mstatus_spp_value);


    // go back to M mode
    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    
    TEST_END();
}
