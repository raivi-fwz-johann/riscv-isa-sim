
#include <test_utils.h>

bool __attribute__((weak)) mie_vseie(){
    TEST_START();

    reg_t hie, mie;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that mie is alias for hie


    // write zero to hie
    csr_set_field(hie, HIE_VSEIE_OFF, HIE_VSEIE_LEN, 0);

    hie = csr_get_field(hie, HIE_VSEIE_OFF, HIE_VSEIE_LEN);
    TEST_COMPARE("set hie.vseie to 0 and check hie.vseie is clear", 0, hie);

    mie = csr_get_field(mie, MIE_VSEIE_OFF, MIE_VSEIE_LEN);
    TEST_COMPARE("check mie.vseie is clear", 0, mie);

    // write one to hie
    csr_set_field(hie, HIE_VSEIE_OFF, HIE_VSEIE_LEN, 1);

    hie = csr_get_field(hie, HIE_VSEIE_OFF, HIE_VSEIE_LEN);
    TEST_COMPARE("set hie.vseie to 1 and check hie.vseie is set", 1, hie);

    mie = csr_get_field(mie, MIE_VSEIE_OFF, MIE_VSEIE_LEN);
    TEST_COMPARE("check mie.vseie is set", 1, mie);
    

    // write zero to mie
    csr_set_field(mie, MIE_VSEIE_OFF, MIE_VSEIE_LEN, 0);

    mie = csr_get_field(mie, MIE_VSEIE_OFF, MIE_VSEIE_LEN);
    TEST_COMPARE("set mie.vseie to 0 and check mie.vseie is clear", 0, mie);

    hie = csr_get_field(hie, HIE_VSEIE_OFF, HIE_VSEIE_LEN);
    TEST_COMPARE("check hie.vseie is clear", 0, hie);

    // write one to mie
    csr_set_field(mie, MIE_VSEIE_OFF, MIE_VSEIE_LEN, 1);

    mie = csr_get_field(mie, MIE_VSEIE_OFF, MIE_VSEIE_LEN);
    TEST_COMPARE("set mie.vseie to 1 and check mie.vseie is set", 1, mie);

    hie = csr_get_field(hie, HIE_VSEIE_OFF, HIE_VSEIE_LEN);
    TEST_COMPARE("check hie.vseie is set", 1, hie);


    // clear fields
    csr_set_field(hie, HIE_VSEIE_OFF, HIE_VSEIE_LEN, 0);

    hie = csr_get_field(hie, HIE_VSEIE_OFF, HIE_VSEIE_LEN);
    TEST_COMPARE("set hie.vseie to 0 and check hie.vseie is clear", 0, hie);

    mie = csr_get_field(mie, MIE_VSEIE_OFF, MIE_VSEIE_LEN);
    TEST_COMPARE("check mie.vseie is clear", 0, mie);


    TEST_END();
}
