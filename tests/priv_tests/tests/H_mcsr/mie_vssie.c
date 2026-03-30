
#include <test_utils.h>

bool __attribute__((weak)) mie_vssie(){
    TEST_START();

    reg_t hie, mie;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that mie is alias for hie


    // write zero to hie
    csr_set_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN, 0);

    hie = csr_get_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN);
    TEST_COMPARE("set hie.vssie to 0 and check hie.vssie is clear", 0, hie);

    mie = csr_get_field(mie, MIE_VSSIE_OFF, MIE_VSSIE_LEN);
    TEST_COMPARE("check mie.vssie is clear", 0, mie);

    // write one to hie
    csr_set_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN, 1);

    hie = csr_get_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN);
    TEST_COMPARE("set hie.vssie to 1 and check hie.vssie is set", 1, hie);

    mie = csr_get_field(mie, MIE_VSSIE_OFF, MIE_VSSIE_LEN);
    TEST_COMPARE("check mie.vssie is set", 1, mie);
    

    // write zero to mie
    csr_set_field(mie, MIE_VSSIE_OFF, MIE_VSSIE_LEN, 0);

    mie = csr_get_field(mie, MIE_VSSIE_OFF, MIE_VSSIE_LEN);
    TEST_COMPARE("set mie.vssie to 0 and check mie.vssie is clear", 0, mie);

    hie = csr_get_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN);
    TEST_COMPARE("check hie.vssie is clear", 0, hie);

    // write one to mie
    csr_set_field(mie, MIE_VSSIE_OFF, MIE_VSSIE_LEN, 1);

    mie = csr_get_field(mie, MIE_VSSIE_OFF, MIE_VSSIE_LEN);
    TEST_COMPARE("set mie.vssie to 1 and check mie.vssie is set", 1, mie);

    hie = csr_get_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN);
    TEST_COMPARE("check hie.vssie is set", 1, hie);


    // clear fields
    csr_set_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN, 0);

    hie = csr_get_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN);
    TEST_COMPARE("set hie.vssie to 0 and check hie.vssie is clear", 0, hie);

    mie = csr_get_field(mie, MIE_VSSIE_OFF, MIE_VSSIE_LEN);
    TEST_COMPARE("check mie.vssie is clear", 0, mie);


    TEST_END();
}
