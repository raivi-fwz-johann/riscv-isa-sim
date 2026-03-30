
#include <test_utils.h>

void __attribute__((weak)) mie_msie_handler(){
    excpt.triggered = true;
    csr_set_field(mstatus, MSTATUS_MPIE_OFF, MSTATUS_MPIE_LEN, 0);
}

bool __attribute__((weak)) mie_msie(){
    TEST_START();

    reg_t msie, msip, mie;

    set_mhandler(mie_msie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that interrupt is not triggered when mie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(mie, MIE_MSIE_OFF, MIE_MSIE_LEN, 0);
    msie = csr_get_field(mie, MIE_MSIE_OFF, MIE_MSIE_LEN);
    TEST_COMPARE("check mie.msie is clear", 0, msie);

    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 1);
    mie = csr_get_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN);
    TEST_COMPARE("check mstatus.mie is set", 1, mie);

    csr_set_field(mip, MIP_MSIP_OFF, MIP_MSIP_LEN, 1);
    msip = csr_get_field(mip, MIP_MSIP_OFF, MIP_MSIP_LEN);
    TEST_COMPARE("check mip.msip is set", 1, msip);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);
    
    // check that interrupt is triggered when mie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 1);
    mie = csr_get_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN);
    TEST_COMPARE("check mstatus.mie is set", 1, mie);

    csr_set_field(mie, MIE_MSIE_OFF, MIE_MSIE_LEN, 1);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    msie = csr_get_field(mie, MIE_MSIE_OFF, MIE_MSIE_LEN);
    TEST_COMPARE("check mie.msie is set", 1, msie);

    // clear fields
    csr_set_field(mie, MIE_MSIE_OFF, MIE_MSIE_LEN, 0);
    csr_set_field(mip, MIP_MSIP_OFF, MIP_MSIP_LEN, 0);
    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 0);
    
    TEST_END();
}
