
#include <test_utils.h>

static reg_t mstatus_mpp_value = 0;

void __attribute__((weak)) mstatus_mpp_handler(){
    excpt.triggered = true;
    mstatus_mpp_value = csr_get_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN);
}

bool __attribute__((weak)) mstatus_mpp(){
    TEST_START();

    // clear delegation register
    CSRW(medeleg, 0);
    set_mhandler(mstatus_mpp_handler);                                                                                                                                                                             


    // check mpp value when trap from M mode
    excpt.triggered = false;
    excpt.for_testing = true;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that mstatus.mpp value is MODE_M", MODE_M, mstatus_mpp_value);


    // check mpp value when trap from S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that mstatus.mpp value is MODE_S", MODE_S, mstatus_mpp_value);


    // check mpp value when trap from U mode
    excpt.triggered = false;
    excpt.for_testing = true;

    switch_mode(MODE_U);
    TEST_COMPARE("check that currunt mode is U", MODE_U, current_mode);                                                   

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that mstatus.mpp value is MODE_U", MODE_U, mstatus_mpp_value);


    // go back to M mode
    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    
    TEST_END();
}
