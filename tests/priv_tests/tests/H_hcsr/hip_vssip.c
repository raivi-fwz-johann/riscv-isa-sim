
#include <test_utils.h>

bool __attribute__((weak)) hip_vssip(){
    TEST_START();

    reg_t hip, hvip;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // check that hip is alias for hvip


    // write zero to hip
    csr_set_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN, 0);

    hip = csr_get_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN);
    TEST_COMPARE("set hip.vssip to 0 and check hip.vssip is clear", 0, hip);

    hvip = csr_get_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN);
    TEST_COMPARE("check hvip.vssip is clear", 0, hvip);

    // write one to hip
    csr_set_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN, 1);

    hip = csr_get_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN);
    TEST_COMPARE("set hip.vssip to 1 and check hip.vssip is set", 1, hip);

    hvip = csr_get_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN);
    TEST_COMPARE("check hvip.vssip is set", 1, hvip);
    

    // write zero to hvip
    csr_set_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN, 0);

    hvip = csr_get_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN);
    TEST_COMPARE("set hvip.vssip to 0 and check hvip.vssip is clear", 0, hvip);

    hip = csr_get_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN);
    TEST_COMPARE("check hip.vssip is clear", 0, hip);

    // write one to hvip
    csr_set_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN, 1);

    hvip = csr_get_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN);
    TEST_COMPARE("set hvip.vssip to 1 and check hvip.vssip is set", 1, hvip);

    hip = csr_get_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN);
    TEST_COMPARE("check hip.vssip is set", 1, hip);


    // clear fields
    csr_set_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN, 0);

    hip = csr_get_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN);
    TEST_COMPARE("set hip.vssip to 0 and check hip.vssip is clear", 0, hip);

    hvip = csr_get_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN);
    TEST_COMPARE("check hvip.vssip is clear", 0, hvip);


    TEST_END();
}
