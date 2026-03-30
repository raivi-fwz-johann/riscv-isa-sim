
#include <test_utils.h>

void __attribute__((weak)) vsie_seie_handler(){
    excpt.triggered = true;
    csr_set_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN, 0);
}

bool __attribute__((weak)) vsie_seie_host(){
    TEST_START();

    reg_t seie, seip, sie;

    set_vshandler(vsie_seie_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // delegate all interrupts to VS mode
    CSRW(hideleg, ~0L);

    csr_set_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN, 1);

    // check that interrupt is not triggered when sie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    //vsip.seip is alias of hip.vseip which is not writable
    seip = csr_get_field(vsip, VSIP_SEIP_OFF, VSIP_SEIP_LEN);
    TEST_COMPARE("check vsip.seip is set", 1, seip);

    csr_set_field(vsie, VSIE_SEIE_OFF, VSIE_SEIE_LEN, 0);
    seie = csr_get_field(vsie, VSIE_SEIE_OFF, VSIE_SEIE_LEN);
    TEST_COMPARE("check vsie.seie is clear", 0, seie);

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

    csr_set_field(vsie, VSIE_SEIE_OFF, VSIE_SEIE_LEN, 1);
    seie = csr_get_field(vsie, VSIE_SEIE_OFF, VSIE_SEIE_LEN);
    TEST_COMPARE("check vsie.seie is set", 1, seie);

    // try to trigger interrupt
    set_virtial_mode_host(ON);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    // sstatus.sie is imediatly cleared in interrupt routine
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check vsstatus.sie is clear", 0, sie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    set_virtial_mode_host(OFF);
    
    // clear fields
    csr_set_field(vsie, VSIE_SEIE_OFF, VSIE_SEIE_LEN, 0);
    csr_set_field(vsip, VSIP_SEIP_OFF, VSIP_SEIP_LEN, 0);
    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 0);
    CSRW(hideleg, 0L);
    
    TEST_END();
}
