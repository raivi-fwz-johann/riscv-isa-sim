
#include <test_utils.h>

static reg_t mstatus_mpv_value = 0;

void __attribute__((weak)) mstatus_mpv_handler(){
    excpt.triggered = true;
    mstatus_mpv_value = csr_get_field(mstatus, MSTATUS_MPV_OFF, MSTATUS_MPV_LEN);
}

bool __attribute__((weak)) mstatus_mpv(){
    TEST_START();

    set_mhandler(mstatus_mpv_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // check that  MPV is not set in HS mode
    excpt.triggered = false;
    excpt.for_testing = true;

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    TEST_COMPARE("check that mstatus.mpv value is clear", 0, mstatus_mpv_value);

    
    // check that MPV is set in VS mode
    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_machine(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    ecall(0,0);
    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);
    TEST_COMPARE("check that mstatus.mpv value is set", 1, mstatus_mpv_value);

    set_virtial_mode_machine(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    TEST_END();
}
