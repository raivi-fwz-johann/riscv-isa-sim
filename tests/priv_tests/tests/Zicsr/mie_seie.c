
#include <test_utils.h>

void __attribute__((weak)) mie_seie_handler(){
    excpt.triggered = true;
    csr_set_field(mstatus, SIE_SEIE_OFF, SIE_SEIE_LEN, 0);
}

bool __attribute__((weak)) mie_seie(){
    TEST_START();

    reg_t seie, seip, sie;

    set_mhandler(mie_seie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that interrupt is not triggered when sie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(mie, MIE_SEIE_OFF, MIE_SEIE_LEN, 0);
    seie = csr_get_field(mie, MIE_SEIE_OFF, MIE_SEIE_LEN);
    TEST_COMPARE("check mie.seie is clear", 0, seie);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    csr_set_field(sip, SIP_SEIP_OFF, SIP_SEIP_LEN, 1);
    seip = csr_get_field(sip, SIP_SEIP_OFF, SIP_SEIP_LEN);
    TEST_COMPARE("check sip.seip is set", 1, seip);

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

    csr_set_field(mie, MIE_SEIE_OFF, MIE_SEIE_LEN, 1);
    seie = csr_get_field(mie, MIE_SEIE_OFF, MIE_SEIE_LEN);
    TEST_COMPARE("check mie.seie is set", 1, seie);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    csr_set_field(sip, SIP_SEIP_OFF, SIP_SEIP_LEN, 1);
    seip = csr_get_field(sip, SIP_SEIP_OFF, SIP_SEIP_LEN);
    TEST_COMPARE("check sip.seip is set", 1, seip);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear fields
    csr_set_field(mie, MIE_SEIE_OFF, MIE_SEIE_LEN, 0);
    csr_set_field(sip, SIP_SEIP_OFF, SIP_SEIP_LEN, 0);
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    
    TEST_END();
}
