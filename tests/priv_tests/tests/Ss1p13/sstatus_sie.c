
#include <test_utils.h>

void __attribute__((weak)) sstatus_sie_handler(){
    excpt.triggered = true;
    csr_set_field(sie, SIE_SSIE_OFF, SIE_SSIE_OFF, 0);
}

bool __attribute__((weak)) sstatus_sie(){
    TEST_START();

    reg_t ssie, ssip, sie;

    set_shandler(sstatus_sie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // check that interrupt is not triggered when sie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is clear", 0, sie);

    csr_set_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN, 1);
    ssie = csr_get_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN);
    TEST_COMPARE("check sie.ssie is set", 1, ssie);

    csr_set_field(sip, SIP_SSIP_OFF, SIP_SSIP_LEN, 1);
    ssip = csr_get_field(sip, SIP_SSIP_OFF, SIP_SSIP_LEN);
    TEST_COMPARE("check sip.ssip is set", 1, ssip);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);
    
    // check that interrupt is triggered when sie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);


    // clear fields
    csr_set_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN, 0);
    csr_set_field(sip, SIP_SSIP_OFF, SIP_SSIP_LEN, 0);
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    
    TEST_END();
}
