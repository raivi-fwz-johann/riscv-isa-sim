
#include <test_utils.h>

void __attribute__((weak)) vsstatus_sie_handler(){
    excpt.triggered = true;
    csr_set_field(sie, SIE_SSIE_OFF, SIE_SSIE_OFF, 0);
}

bool __attribute__((weak)) vsstatus_sie_host(){
    TEST_START();

    reg_t ssie, ssip, sie, hideleg_vssi;

    set_vshandler(vsstatus_sie_handler);                                                                                                                                                                             
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    csr_set_field(hideleg, HIDELEG_VSSI_OFF, HIDELEG_VSSI_LEN, 1);
    hideleg_vssi = csr_get_field(hideleg, HIDELEG_VSSI_OFF, HIDELEG_VSSI_LEN);
    TEST_COMPARE("set and check that hideleg VSSI is 1. Delegation is ON", 1, hideleg_vssi);

    csr_set_field(vsip, VSIP_SSIP_OFF, VSIP_SSIP_LEN, 1);
    ssip = csr_get_field(vsip, VSIP_SSIP_OFF, VSIP_SSIP_LEN);
    TEST_COMPARE("check vsip.ssip is set", 1, ssip);
    
    // check that interrupt is not triggered when sie is clear
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 0);
    sie = csr_get_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN);
    TEST_COMPARE("check vsstatus.sie is clear", 0, sie);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    csr_set_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN, 1);
    ssie = csr_get_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN);
    TEST_COMPARE("check sie.ssie is set", 1, ssie);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    csr_set_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN, 0);
    ssie = csr_get_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN);
    TEST_COMPARE("check sie.ssie is clear", 0, ssie);

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    
    // check that interrupt is triggered when sie is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 1);
    sie = csr_get_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN);
    TEST_COMPARE("check vsstatus.sie is set", 1, sie);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    csr_set_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN, 1);
    // sstatus.sie is imediatly cleared in interrupt routine
    ssie = csr_get_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN);
    TEST_COMPARE("check sie.ssie is clear", 0, ssie);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   


    // clear fields
    csr_set_field(hideleg, HIDELEG_VSSI_OFF, HIDELEG_VSSI_LEN, 0);
    csr_set_field(vsie, VSIE_SSIE_OFF, VSIE_SSIE_LEN, 0);
    csr_set_field(vsip, VSIP_SSIP_OFF, VSIP_SSIP_LEN, 0);
    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 0);
    csr_set_field(vsstatus, VSSTATUS_SPIE_OFF, VSSTATUS_SPIE_LEN, 0);
    
    TEST_END();
}
