
#include <test_utils.h>

void __attribute__((weak)) hvip_ssip_handler(){
    excpt.triggered = true;
    csr_set_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN, 0);
}

bool __attribute__((weak)) hvip_vssip(){
    TEST_START();

    reg_t ssie, hvip, sie;

    set_vshandler(hvip_ssip_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   


    // delegate all interrupts to VS mode
    CSRW(hideleg, ~0L);

    csr_set_field(vsie, VSIE_SSIE_OFF, VSIE_SSIE_LEN, 1);
    ssie = csr_get_field(vsie, VSIE_SSIE_OFF, VSIE_SSIE_LEN);
    TEST_COMPARE("check vsie.ssie is set", 1, ssie);

    // check that interrupt is not triggered when hvip.vssip is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN, 0);
    hvip = csr_get_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN);
    TEST_COMPARE("check hvip.vssip is clear", 0, hvip);
    
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

    csr_set_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN, 1);
    hvip = csr_get_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN);
    TEST_COMPARE("check hvip.vssip is set", 1, hvip);

    // try to trigger interrupt
    set_virtial_mode_host(ON);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    // sstatus.sie is imediatly cleared in interrupt routine
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check vsstatus.sie is clear", 0, sie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    set_virtial_mode_host(OFF);
    
    // clear fields
    csr_set_field(vsie, VSIE_SSIE_OFF, VSIE_SSIE_LEN, 0);
    csr_set_field(hvip, HVIP_VSSIP_OFF, HVIP_VSSIP_LEN, 0);
    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 0);
    CSRW(hideleg, 0L);
    
    TEST_END();
}
