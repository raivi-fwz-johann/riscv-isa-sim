
#include <test_utils.h>

void __attribute__((weak)) vsie_stie_handler(){
    excpt.triggered = true;
    csr_set_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN, 0);
}

bool __attribute__((weak)) vsie_stie_host(){
    TEST_START();

    reg_t stie, stip, sie;

    set_vshandler(vsie_stie_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // delegate all interrupts to VS mode
    CSRW(hideleg, ~0L);

    csr_set_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN, 1);

    // check that interrupt is not triggered when sie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    //vsip.stip is alias of hip.vstip which is not writable
    stip = csr_get_field(vsip, VSIP_STIP_OFF, VSIP_STIP_LEN);
    TEST_COMPARE("check vsip.stip is set", 1, stip);

    csr_set_field(vsie, VSIE_STIE_OFF, VSIE_STIE_LEN, 0);
    stie = csr_get_field(vsie, VSIE_STIE_OFF, VSIE_STIE_LEN);
    TEST_COMPARE("check vsie.stie is clear", 0, stie);

    // try to trigger interrupt
    set_virtial_mode_host(ON);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check vsstatus.sie is set", 1, sie);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check vsstatus.sie is clear", 0, sie);
    
    set_virtial_mode_host(OFF);

    
    // check that interrupt is triggered when sie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(vsie, VSIE_STIE_OFF, VSIE_STIE_LEN, 1);
    stie = csr_get_field(vsie, VSIE_STIE_OFF, VSIE_STIE_LEN);
    TEST_COMPARE("check vsie.stie is set", 1, stie);

    // try to trigger interrupt
    set_virtial_mode_host(ON);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    // sstatus.sie is imediatly cleared in interrupt routine
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check vsstatus.sie is clear", 0, sie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    set_virtial_mode_host(OFF);
    
    // clear fields
    csr_set_field(vsie, VSIE_STIE_OFF, VSIE_STIE_LEN, 0);
    csr_set_field(vsip, VSIP_STIP_OFF, VSIP_STIP_LEN, 0);
    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 0);
    CSRW(hideleg, 0L);
    
    TEST_END();
}
