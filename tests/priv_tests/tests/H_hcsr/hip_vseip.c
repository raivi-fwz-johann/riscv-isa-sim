
#include <test_utils.h>

bool __attribute__((weak)) hip_vseip(){
    TEST_START();

    reg_t hip, hvip, hgeip, hstatus;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // check that hip is asserted using hvip and hgeip 


    // check hip.vseip assetion using HVIP
    
    // write zero to hvip
    csr_set_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN, 0);

    hvip = csr_get_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN);
    TEST_COMPARE("set hvip.vseip to 0 and check hvip.vseip is clear", 0, hvip);

    hip = csr_get_field(hip, HIP_VSEIP_OFF, HIP_VSEIP_LEN);
    TEST_COMPARE("check hip.vseip is clear", 0, hip);

    // write one to hvip
    csr_set_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN, 1);

    hvip = csr_get_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN);
    TEST_COMPARE("set hvip.vesip to 1 and check hvip.vseip is set", 1, hvip);

    hip = csr_get_field(hip, HIP_VSEIP_OFF, HIP_VSEIP_LEN);
    TEST_COMPARE("check hip.vseip is set", 1, hip);

    // write zero to hvip
    csr_set_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN, 0);

    hvip = csr_get_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN);
    TEST_COMPARE("set hvip.vseip to 0 and check hvip.vseip is clear", 0, hvip);

    hip = csr_get_field(hip, HIP_VSEIP_OFF, HIP_VSEIP_LEN);
    TEST_COMPARE("check hip.vseip is clear", 0, hip);


    // check hip.vseip assetion using HGEIP
    CSRW(hgeip, 0b10);
    hgeip = CSRR(hgeip);
    TEST_COMPARE("set hgeip to 0b10 and check it's value", 0b10, hgeip);

    csr_set_field(hstatus, HSTATUS_VGEIN_OFF, HSTATUS_VGEIN_LEN, 1);
    hstatus = csr_get_field(hstatus, HSTATUS_VGEIN_OFF, HSTATUS_VGEIN_LEN);
    TEST_COMPARE("set hstatus.vgein to 1 and check its value", 1, hstatus);

    hip = csr_get_field(hip, HIP_VSEIP_OFF, HIP_VSEIP_LEN);
    TEST_COMPARE("check hip.vseip is set", 1, hip);

    // clear state
    CSRW(hgeip, 0);
    hgeip = CSRR(hgeip);
    TEST_COMPARE("set hgeip to 0 and check it's value", 0, hgeip);

    csr_set_field(hstatus, HSTATUS_VGEIN_OFF, HSTATUS_VGEIN_LEN, 0);
    hstatus = csr_get_field(hstatus, HSTATUS_VGEIN_OFF, HSTATUS_VGEIN_LEN);
    TEST_COMPARE("set hstatus.vgein to 0 and check its value", 0, hstatus);

    hip = csr_get_field(hip, HIP_VSEIP_OFF, HIP_VSEIP_LEN);
    TEST_COMPARE("check hip.vseip is clear", 0, hip);



    TEST_END();
}
