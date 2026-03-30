
#include <test_utils.h>

bool __attribute__((weak)) mip_vssip(){
    TEST_START();

    reg_t hip, mip;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that mip is alias for hip


    // write zero to hip
    csr_set_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN, 0);

    hip = csr_get_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN);
    TEST_COMPARE("set hip.vssip to 0 and check hip.vssip is clear", 0, hip);

    mip = csr_get_field(mip, MIP_VSSIP_OFF, MIP_VSSIP_LEN);
    TEST_COMPARE("check mip.vssip is clear", 0, mip);

    // write one to hip
    csr_set_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN, 1);

    hip = csr_get_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN);
    TEST_COMPARE("set hip.vssip to 1 and check hip.vssip is set", 1, hip);

    mip = csr_get_field(mip, MIP_VSSIP_OFF, MIP_VSSIP_LEN);
    TEST_COMPARE("check mip.vssip is set", 1, mip);
    

    // write zero to mip
    csr_set_field(mip, MIP_VSSIP_OFF, MIP_VSSIP_LEN, 0);

    mip = csr_get_field(mip, MIP_VSSIP_OFF, MIP_VSSIP_LEN);
    TEST_COMPARE("set mip.vssip to 0 and check mip.vssip is clear", 0, mip);

    hip = csr_get_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN);
    TEST_COMPARE("check hip.vssip is clear", 0, hip);

    // write one to mip
    csr_set_field(mip, MIP_VSSIP_OFF, MIP_VSSIP_LEN, 1);

    mip = csr_get_field(mip, MIP_VSSIP_OFF, MIP_VSSIP_LEN);
    TEST_COMPARE("set mip.vssip to 1 and check mip.vssip is set", 1, mip);

    hip = csr_get_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN);
    TEST_COMPARE("check hip.vssip is set", 1, hip);


    // clear fields
    csr_set_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN, 0);

    hip = csr_get_field(hip, HIP_VSSIP_OFF, HIP_VSSIP_LEN);
    TEST_COMPARE("set hip.vssip to 0 and check hip.vssip is clear", 0, hip);

    mip = csr_get_field(mip, MIP_VSSIP_OFF, MIP_VSSIP_LEN);
    TEST_COMPARE("check mip.vssip is clear", 0, mip);


    TEST_END();
}
