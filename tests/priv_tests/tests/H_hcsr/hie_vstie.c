
#include <test_utils.h>

void __attribute__((weak)) hie_vstip_handler(){
    excpt.triggered = true;
    csr_set_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN, 0);
}

bool __attribute__((weak)) hie_vstie(){
    TEST_START();

    reg_t temp;

    set_shandler(hie_vstip_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   


    csr_set_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN, 1);
    temp = csr_get_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN);
    TEST_COMPARE("check hvip.vstip is set", 1, temp);

    // check that interrupt is not triggered when hie.vstie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(hie, HIE_VSTIE_OFF, HIE_VSTIE_LEN, 0);
    temp = csr_get_field(hie, HIE_VSTIE_OFF, HIE_VSTIE_LEN);
    TEST_COMPARE("check hie.vstie is clear", 0, temp);
    
    // try to trigger interrupt
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    temp = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, temp);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    temp = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is clear", 0, temp);
    
    
    // check that interrupt is triggered when sie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(hie, HIE_VSTIE_OFF, HIE_VSTIE_LEN, 1);
    temp = csr_get_field(hie, HIE_VSTIE_OFF, HIE_VSTIE_LEN);
    TEST_COMPARE("check hie.vstie is set", 1, temp);

    // try to trigger interrupt
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    // sstatus.sie is imediatly cleared in interrupt routine
    temp = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is clear", 0, temp);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    // clear fields
    csr_set_field(hie, HIE_VSTIE_OFF, HIE_VSTIE_LEN, 0);
    csr_set_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN, 0);
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    
    TEST_END();
}
