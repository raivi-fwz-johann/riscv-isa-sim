
#include <test_utils.h>

bool __attribute__((weak)) mip_vseip(){
    TEST_START();

    reg_t mip, hvip, hgeip, hstatus;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that mip is asserted using hvip and hgeip 


    // check mip.vseip assetion using HVIP
    
    // write zero to hvip
    csr_set_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN, 0);

    hvip = csr_get_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN);
    TEST_COMPARE("set hvip.vseip to 0 and check hvip.vseip is clear", 0, hvip);

    mip = csr_get_field(mip, MIP_VSEIP_OFF, MIP_VSEIP_LEN);
    TEST_COMPARE("check mip.vseip is clear", 0, mip);

    // write one to hvip
    csr_set_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN, 1);

    hvip = csr_get_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN);
    TEST_COMPARE("set hvip.vesip to 1 and check hvip.vseip is set", 1, hvip);

    mip = csr_get_field(mip, MIP_VSEIP_OFF, MIP_VSEIP_LEN);
    TEST_COMPARE("check mip.vseip is set", 1, mip);

    // write zero to hvip
    csr_set_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN, 0);

    hvip = csr_get_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN);
    TEST_COMPARE("set hvip.vseip to 0 and check hvip.vseip is clear", 0, hvip);

    mip = csr_get_field(mip, MIP_VSEIP_OFF, MIP_VSEIP_LEN);
    TEST_COMPARE("check mip.vseip is clear", 0, mip);


    // check mip.vseip assetion using HGEIP
    CSRW(hgeip, 0b10);
    hgeip = CSRR(hgeip);
    TEST_COMPARE("set hgeip to 0b10 and check it's value", 0b10, hgeip);

    csr_set_field(hstatus, HSTATUS_VGEIN_OFF, HSTATUS_VGEIN_LEN, 1);
    hstatus = csr_get_field(hstatus, HSTATUS_VGEIN_OFF, HSTATUS_VGEIN_LEN);
    TEST_COMPARE("set hstatus.vgein to 1 and check its value", 1, hstatus);

    mip = csr_get_field(mip, MIP_VSEIP_OFF, MIP_VSEIP_LEN);
    TEST_COMPARE("check mip.vseip is set", 1, mip);

    // clear state
    CSRW(hgeip, 0);
    hgeip = CSRR(hgeip);
    TEST_COMPARE("set hgeip to 0 and check it's value", 0, hgeip);

    csr_set_field(hstatus, HSTATUS_VGEIN_OFF, HSTATUS_VGEIN_LEN, 0);
    hstatus = csr_get_field(hstatus, HSTATUS_VGEIN_OFF, HSTATUS_VGEIN_LEN);
    TEST_COMPARE("set hstatus.vgein to 0 and check its value", 0, hstatus);

    mip = csr_get_field(mip, MIP_VSEIP_OFF, MIP_VSEIP_LEN);
    TEST_COMPARE("check mip.vseip is clear", 0, mip);



    TEST_END();
}
