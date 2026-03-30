
#include <test_utils.h>

bool __attribute__((weak)) hip_vstip(){
    TEST_START();

    reg_t hip, hvip, hgeip, hstatus;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    
    // write zero to hvip
    csr_set_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN, 0);

    hvip = csr_get_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN);
    TEST_COMPARE("set hvip.vstip to 0 and check hvip.vstip is clear", 0, hvip);

    hip = csr_get_field(hip, HIP_VSTIP_OFF, HIP_VSTIP_LEN);
    TEST_COMPARE("check hip.vstip is clear", 0, hip);

    // write one to hvip
    csr_set_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN, 1);

    hvip = csr_get_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN);
    TEST_COMPARE("set hvip.vesip to 1 and check hvip.vstip is set", 1, hvip);

    hip = csr_get_field(hip, HIP_VSTIP_OFF, HIP_VSTIP_LEN);
    TEST_COMPARE("check hip.vstip is set", 1, hip);

    // write zero to hvip
    csr_set_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN, 0);

    hvip = csr_get_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN);
    TEST_COMPARE("set hvip.vstip to 0 and check hvip.vstip is clear", 0, hvip);

    hip = csr_get_field(hip, HIP_VSTIP_OFF, HIP_VSTIP_LEN);
    TEST_COMPARE("check hip.vstip is clear", 0, hip);



    TEST_END();
}
