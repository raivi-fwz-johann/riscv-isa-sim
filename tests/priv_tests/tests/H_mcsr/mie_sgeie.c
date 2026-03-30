
#include <test_utils.h>

bool __attribute__((weak)) mie_sgeie(){
    TEST_START();

    reg_t hie, mie;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that mie is alias for hie


    // write zero to hie
    csr_set_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN, 0);

    hie = csr_get_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN);
    TEST_COMPARE("set hie.sgeie to 0 and check hie.sgeie is clear", 0, hie);

    mie = csr_get_field(mie, MIE_SGEIE_OFF, MIE_SGEIE_LEN);
    TEST_COMPARE("check mie.sgeie is clear", 0, mie);

    // write one to hie
    csr_set_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN, 1);

    hie = csr_get_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN);
    TEST_COMPARE("set hie.sgeie to 1 and check hie.sgeie is set", 1, hie);

    mie = csr_get_field(mie, MIE_SGEIE_OFF, MIE_SGEIE_LEN);
    TEST_COMPARE("check mie.sgeie is set", 1, mie);
    

    // write zero to mie
    csr_set_field(mie, MIE_SGEIE_OFF, MIE_SGEIE_LEN, 0);

    mie = csr_get_field(mie, MIE_SGEIE_OFF, MIE_SGEIE_LEN);
    TEST_COMPARE("set mie.sgeie to 0 and check mie.sgeie is clear", 0, mie);

    hie = csr_get_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN);
    TEST_COMPARE("check hie.sgeie is clear", 0, hie);

    // write one to mie
    csr_set_field(mie, MIE_SGEIE_OFF, MIE_SGEIE_LEN, 1);

    mie = csr_get_field(mie, MIE_SGEIE_OFF, MIE_SGEIE_LEN);
    TEST_COMPARE("set mie.sgeie to 1 and check mie.sgeie is set", 1, mie);

    hie = csr_get_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN);
    TEST_COMPARE("check hie.sgeie is set", 1, hie);


    // clear fields
    csr_set_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN, 0);

    hie = csr_get_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN);
    TEST_COMPARE("set hie.sgeie to 0 and check hie.sgeie is clear", 0, hie);

    mie = csr_get_field(mie, MIE_SGEIE_OFF, MIE_SGEIE_LEN);
    TEST_COMPARE("check mie.sgeie is clear", 0, mie);


    TEST_END();
}
