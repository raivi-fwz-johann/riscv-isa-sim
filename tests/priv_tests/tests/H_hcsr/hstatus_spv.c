
#include <test_utils.h>

static reg_t hstatus_spv_value = 0;

void __attribute__((weak)) hstatus_spv_handler(){
    excpt.triggered = true;
    hstatus_spv_value = csr_get_field(hstatus, HSTATUS_SPV_OFF, HSTATUS_SPV_LEN);
}

bool __attribute__((weak)) hstatus_spv(){
    TEST_START();

    set_shandler(hstatus_spv_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   


    // check that  SPV is not set in HS mode
    excpt.triggered = false;
    excpt.for_testing = true;

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    TEST_COMPARE("check that hstatus.spv value is clear", 0, hstatus_spv_value);

    
    // check that SPV is set in VS mode
    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    TEST_COMPARE("check that hstatus.spv value is set", 1, hstatus_spv_value);

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    TEST_END();
}
