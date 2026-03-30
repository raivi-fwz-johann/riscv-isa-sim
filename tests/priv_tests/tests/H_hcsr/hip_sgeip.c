
#include <test_utils.h>

bool __attribute__((weak)) hip_vseip(){
    TEST_START();

    reg_t hgeip, hgeie, hip;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   


    // check hip.vseip assetion using HGEIP
    CSRW(hgeip, 0b10);
    hgeip = CSRR(hgeip);
    TEST_COMPARE("set hgeip to 0b10 and check it's value", 0b10, hgeip);

    CSRW(hgeie, 0b10);
    hgeie = CSRR(hgeie);
    TEST_COMPARE("set hgeie to 0b10 and check it's value", 0b10, hgeie);

    hip = csr_get_field(hip, HIP_SGEIP_OFF, HIP_SGEIP_LEN);
    TEST_COMPARE("check hip.sgeip is set", 1, hip);

    // clear state
    CSRW(hgeip, 0);
    hgeip = CSRR(hgeip);
    TEST_COMPARE("set hgeip to 0 and check it's value", 0, hgeip);

    CSRW(hgeie, 0);
    hgeie = CSRR(hgeie);
    TEST_COMPARE("set hgeie to 0 and check it's value", 0, hgeie);

    hip = csr_get_field(hip, HIP_SGEIP_OFF, HIP_SGEIP_LEN);
    TEST_COMPARE("check hip.sgeip is clear", 0, hip);



    TEST_END();
}
