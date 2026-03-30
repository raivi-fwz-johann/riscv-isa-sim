
#include <test_utils.h>

static reg_t sstatus_spp_value = 0;

void __attribute__((weak)) sstatus_spp_handler(){
    excpt.triggered = true;
    sstatus_spp_value = csr_get_field(sstatus, SSTATUS_SPP_OFF, SSTATUS_SPP_LEN);
}

bool __attribute__((weak)) sstatus_spp(){
    TEST_START();

    // clear delegation register
    set_shandler(sstatus_spp_handler);                                                                                                                                                                             

    // check spp value when trap from S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that sstatus.spp value is MODE_S", MODE_S, sstatus_spp_value);


    // check spp value when trap from U mode
    excpt.triggered = false;
    excpt.for_testing = true;

    switch_mode_supervisor(MODE_U);
    TEST_COMPARE("check that currunt mode is U", MODE_U, current_mode);                                                   

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that sstatus.spp value is MODE_U", MODE_U, sstatus_spp_value);


    // go back to S mode
    switch_mode_supervisor(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    
    TEST_END();
}
