
#include <test_utils.h>

static reg_t mstatus_mpie_value = 0;

void __attribute__((weak)) mstatus_mpie_handler(){
    excpt.triggered = true;
    mstatus_mpie_value = csr_get_field(mstatus, MSTATUS_MPIE_OFF, MSTATUS_MPIE_LEN);
}

bool __attribute__((weak)) mstatus_mpie(){
    TEST_START();

    reg_t mpie, mie;

    set_mhandler(mstatus_mpie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check mpie value when mstatus.mie is clear
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 0);
    mie = csr_get_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN);
    TEST_COMPARE("check mstatus.mie is clear", 0, mie);

    ecall(0,0);
    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that mpie value is 0", 0, mstatus_mpie_value);

    // check mpie value when mstatus.mie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 1);
    mie = csr_get_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN);
    TEST_COMPARE("check mstatus.mie is set", 1, mie);

    ecall(0,0);
    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    TEST_COMPARE("check that mpie value is 1", 1, mstatus_mpie_value);

    // clear fields
    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 0);
    
    TEST_END();
}
