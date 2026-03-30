
#include <test_utils.h>

void __attribute__((weak)) hie_sgeip_handler(){
    excpt.triggered = true;
    csr_set_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN, 0);
}

bool __attribute__((weak)) hie_sgeie(){
    TEST_START();

    reg_t hie, hip, hgeip, hgeie, sie;

    set_shandler(hie_sgeip_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   


    CSRW(hgeip, 0b10);
    hgeip = CSRR(hgeip);
    TEST_COMPARE("set hgeip to 0b10 and check it's value", 0b10, hgeip);

    CSRW(hgeie, 0b10);
    hgeie = CSRR(hgeie);
    TEST_COMPARE("set hgeie to 0b10 and check it's value", 0b10, hgeie);

    hip = csr_get_field(hip, HIP_SGEIP_OFF, HIP_SGEIP_LEN);
    TEST_COMPARE("check hip.sgeip is set", 1, hip);

    // check that interrupt is not triggered when hie.sgeie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN, 0);
    hie = csr_get_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN);
    TEST_COMPARE("check hie.sgeie is clear", 0, hie);
    
    // try to trigger interrupt
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is clear", 0, sie);
    

    
    // check that interrupt is triggered when sie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN, 1);
    hie = csr_get_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN);
    TEST_COMPARE("check hie.sgeie is set", 1, hie);

    // try to trigger interrupt
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is clear", 0, sie);
    
    // clear fields
    CSRW(hgeip, 0);
    hgeip = CSRR(hgeip);
    TEST_COMPARE("set hgeip to 0 and check it's value", 0, hgeip);

    CSRW(hgeie, 0);
    hgeie = CSRR(hgeie);
    TEST_COMPARE("set hgeie to 0 and check it's value", 0, hgeie);

    hip = csr_get_field(hip, HIP_SGEIP_OFF, HIP_SGEIP_LEN);
    TEST_COMPARE("check hip.sgeip is clear", 0, hip);

    csr_set_field(hie, HIE_SGEIE_OFF, HIE_SGEIE_LEN, 0);
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    
    TEST_END();
}
