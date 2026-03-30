
#include <test_utils.h>

void __attribute__((weak)) mie_meie_handler(){
    excpt.triggered = true;
    csr_set_field(mstatus, MSTATUS_MPIE_OFF, MSTATUS_MPIE_LEN, 0);
}

bool __attribute__((weak)) mie_meie(){
    TEST_START();

    reg_t meie, meip, mie;

    set_mhandler(mie_meie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that interrupt is not triggered when mie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(mie, MIE_MEIE_OFF, MIE_MEIE_LEN, 0);
    meie = csr_get_field(mie, MIE_MEIE_OFF, MIE_MEIE_LEN);
    TEST_COMPARE("check mie.meie is clear", 0, meie);

    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 1);
    mie = csr_get_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN);
    TEST_COMPARE("check mstatus.mie is set", 1, mie);

    csr_set_field(mip, MIP_MEIP_OFF, MIP_MEIP_LEN, 1);
    meip = csr_get_field(mip, MIP_MEIP_OFF, MIP_MEIP_LEN);
    TEST_COMPARE("check mip.meip is set", 1, meip);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);
    
    // check that interrupt is triggered when mie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 1);
    mie = csr_get_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN);
    TEST_COMPARE("check mstatus.mie is set", 1, mie);

    csr_set_field(mie, MIE_MEIE_OFF, MIE_MEIE_LEN, 1);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    meie = csr_get_field(mie, MIE_MEIE_OFF, MIE_MEIE_LEN);
    TEST_COMPARE("check mie.meie is set", 1, meie);

    // clear fields
    csr_set_field(mie, MIE_MEIE_OFF, MIE_MEIE_LEN, 0);
    csr_set_field(mip, MIP_MEIP_OFF, MIP_MEIP_LEN, 0);
    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 0);
    
    TEST_END();
}
