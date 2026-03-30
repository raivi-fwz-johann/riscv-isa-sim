
#include <test_utils.h>

bool hstatus_vsxl(){
    TEST_START();

    const reg_t vsxl_32 = 0b01;
    const reg_t vsxl_64 = 0b10;

    reg_t reg;
    reg_t vsxl;

    TEST_COMPARE("switch to S mode and check that currunt mode is S", MODE_S, current_mode);  
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // check that VSXL is 64
    vsxl = csr_get_field(hstatus, HSTATUS_VSXL_OFF, HSTATUS_VSXL_LEN);
    TEST_COMPARE("check hstatus.vsxl is 64", vsxl_64, vsxl);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    
    // shift 1 left and right. 1 shall stay
    reg = 1;
    reg <<= 32;
    reg >>=32; 
    TEST_COMPARE("check shift left, then right by 32", 1, reg);

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // try to switch to 32 bit sode, in spike VSXL is RO
    csr_set_field(hstatus, HSTATUS_VSXL_OFF, HSTATUS_VSXL_LEN, vsxl_32);
    vsxl = csr_get_field(hstatus, HSTATUS_VSXL_OFF, HSTATUS_VSXL_LEN);
    TEST_COMPARE("check try switch to 32, hstatus.vsxl is stay 64", vsxl_64, vsxl);


    TEST_END();
}
