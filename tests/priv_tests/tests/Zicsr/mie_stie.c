
#include <test_utils.h>

void __attribute__((weak)) mie_stie_handler(){
    excpt.triggered = true;
    csr_set_field(mstatus, SIE_STIE_OFF, SIE_STIE_LEN, 0);
}

bool __attribute__((weak)) mie_stie(){
    TEST_START();

    reg_t stie, stip, sie;

    set_mhandler(mie_stie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that interrupt is not triggered when sie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(mie, MIE_STIE_OFF, MIE_STIE_LEN, 0);
    stie = csr_get_field(mie, MIE_STIE_OFF, MIE_STIE_LEN);
    TEST_COMPARE("check mie.stie is clear", 0, stie);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    csr_set_field(sip, SIP_STIP_OFF, SIP_STIP_LEN, 1);
    stip = csr_get_field(sip, SIP_STIP_OFF, SIP_STIP_LEN);
    TEST_COMPARE("check sip.stip is set", 1, stip);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is clear", 0, sie);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that interrupt is triggered when mie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mie, MIE_STIE_OFF, MIE_STIE_LEN, 1);
    stie = csr_get_field(mie, MIE_STIE_OFF, MIE_STIE_LEN);
    TEST_COMPARE("check mie.stie is set", 1, stie);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    csr_set_field(sip, SIP_STIP_OFF, SIP_STIP_LEN, 1);
    stip = csr_get_field(sip, SIP_STIP_OFF, SIP_STIP_LEN);
    TEST_COMPARE("check sip.stip is set", 1, stip);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear fields
    csr_set_field(mie, MIE_STIE_OFF, MIE_STIE_LEN, 0);
    csr_set_field(sip, SIP_STIP_OFF, SIP_STIP_LEN, 0);
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    
    TEST_END();
}
