
#include <test_utils.h>

void __attribute__((weak)) sie_stie_handler(){
    excpt.triggered = true;
    csr_set_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN, 0);
}

bool __attribute__((weak)) sie_stie(){
    TEST_START();

    reg_t stie, stip, sie;

    set_shandler(sie_stie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // check that interrupt is not triggered when sie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(sie, SIE_STIE_OFF, SIE_STIE_LEN, 0);
    stie = csr_get_field(sie, SIE_STIE_OFF, SIE_STIE_LEN);
    TEST_COMPARE("check sie.stie is clear", 0, stie);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    csr_set_field(sip, SIP_STIP_OFF, SIP_STIP_LEN, 1);
    stip = csr_get_field(sip, SIP_STIP_OFF, SIP_STIP_LEN);
    TEST_COMPARE("check sip.stip is set", 1, stip);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);
    
    // check that interrupt is triggered when sie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    csr_set_field(sie, SIE_STIE_OFF, SIE_STIE_LEN, 1);
    stie = csr_get_field(sie, SIE_STIE_OFF, SIE_STIE_LEN);
    TEST_COMPARE("check sie.stie is set", 1, stie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    // clear fields
    csr_set_field(sie, SIE_STIE_OFF, SIE_STIE_LEN, 0);
    csr_set_field(sip, SIP_STIP_OFF, SIP_STIP_LEN, 0);
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    
    TEST_END();
}
