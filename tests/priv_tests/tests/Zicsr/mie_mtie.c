
#include <test_utils.h>

void __attribute__((weak)) mie_mtie_handler(){
    excpt.triggered = true;
    csr_set_field(mstatus, MSTATUS_MPIE_OFF, MSTATUS_MPIE_LEN, 0);
}

bool __attribute__((weak)) mie_mtie(){
    TEST_START();

    reg_t mtie, mtip, mie;

    set_mhandler(mie_mtie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that interrupt is not triggered when mie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(mie, MIE_MTIE_OFF, MIE_MTIE_LEN, 0);
    mtie = csr_get_field(mie, MIE_MTIE_OFF, MIE_MTIE_LEN);
    TEST_COMPARE("check mie.mtie is clear", 0, mtie);

    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 1);
    mie = csr_get_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN);
    TEST_COMPARE("check mstatus.mie is set", 1, mie);

    csr_set_field(mip, MIP_MTIP_OFF, MIP_MTIP_LEN, 1);
    mtip = csr_get_field(mip, MIP_MTIP_OFF, MIP_MTIP_LEN);
    TEST_COMPARE("check mip.mtip is set", 1, mtip);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);
    
    // check that interrupt is triggered when mie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 1);
    mie = csr_get_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN);
    TEST_COMPARE("check mstatus.mie is set", 1, mie);

    csr_set_field(mie, MIE_MTIE_OFF, MIE_MTIE_LEN, 1);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    mtie = csr_get_field(mie, MIE_MTIE_OFF, MIE_MTIE_LEN);
    TEST_COMPARE("check mie.mtie is set", 1, mtie);

    // clear fields
    csr_set_field(mie, MIE_MTIE_OFF, MIE_MTIE_LEN, 0);
    csr_set_field(mip, MIP_MTIP_OFF, MIP_MTIP_LEN, 0);
    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 0);
    
    TEST_END();
}
