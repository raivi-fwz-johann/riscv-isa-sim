
#include <test_utils.h>

void __attribute__((weak)) hie_vssip_handler(){
    excpt.triggered = true;
    csr_set_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN, 0);
}

bool __attribute__((weak)) hie_vssie(){
    TEST_START();

    reg_t hie, hvip, sie;

    set_shandler(hie_vssip_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   


    csr_set_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN, 1);
    hvip = csr_get_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN);
    TEST_COMPARE("check hvip.vssip is set", 1, hvip);

    // check that interrupt is not triggered when hie.vssie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN, 0);
    hie = csr_get_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN);
    TEST_COMPARE("check hie.vssie is clear", 0, hie);
    
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

    csr_set_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN, 1);
    hie = csr_get_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN);
    TEST_COMPARE("check hie.vssie is set", 1, hie);

    // try to trigger interrupt
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    // sstatus.sie is imediatly cleared in interrupt routine
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is clear", 0, sie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    // clear fields
    csr_set_field(hie, HIE_VSSIE_OFF, HIE_VSSIE_LEN, 0);
    csr_set_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN, 0);
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    
    TEST_END();
}
