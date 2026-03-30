
#include <test_utils.h>

void __attribute__((weak)) vsie_seie_handler(){
    excpt.triggered = true;
    csr_set_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN, 0);
}

bool __attribute__((weak)) vsie_seie_guest(){
    TEST_START();

    reg_t seie, seip, sie;

    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    set_vshandler(vsie_seie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // check that interrupt is not triggered when sie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN, 0);
    seie = csr_get_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN);
    TEST_COMPARE("check sie.seie is clear", 0, seie);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    csr_set_field(sip, SIP_SEIP_OFF, SIP_SEIP_LEN, 1);
    seip = csr_get_field(sip, SIP_SEIP_OFF, SIP_SEIP_LEN);
    TEST_COMPARE("check sip.seip is set", 1, seip);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);
    
    // check that interrupt is triggered when sie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    csr_set_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN, 1);
    seie = csr_get_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN);
    TEST_COMPARE("check sie.seie is set", 1, seie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    // clear fields
    csr_set_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN, 0);
    csr_set_field(sip, SIP_SEIP_OFF, SIP_SEIP_LEN, 0);
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    
    TEST_END();
}
