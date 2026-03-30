
#include <test_utils.h>

static reg_t hideleg_ssi_v_mode = 0;

void hideleg_ssi_shandler(){
    excpt.triggered = true;
    csr_set_field(vsip, VSIP_SSIP_OFF, VSIP_SSIP_OFF, 0);
    hideleg_ssi_v_mode = OFF;
}

void hideleg_ssi_vshandler(){
    excpt.triggered = true;
    csr_set_field(sip, SIP_SSIP_OFF, SIP_SSIP_OFF, 0);
    hideleg_ssi_v_mode = ON;
}

bool __attribute__((weak)) hideleg_vssi(){
    TEST_START();

    reg_t hideleg_vssi;
    reg_t temp;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    set_shandler(hideleg_ssi_shandler);                                                                                                                                                                             
    set_vshandler(hideleg_ssi_vshandler);                                                                                                                                                                             

    
    // check that trap with delegation is handled in VS mode
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(hideleg, HIDELEG_VSSI_OFF, HIDELEG_VSSI_LEN, 1);
    hideleg_vssi = csr_get_field(hideleg, HIDELEG_VSSI_OFF, HIDELEG_VSSI_LEN);
    TEST_COMPARE("clear and check that hideleg SSI is 1. Delegation is ON", 1, hideleg_vssi);

    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 1);
    temp = csr_get_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN);
    TEST_COMPARE("enable SSI. vsstatus.sie is 1", 1, temp);

    csr_set_field(vsie, VSIE_SSIE_OFF, VSIE_SSIE_LEN, 1);
    temp = csr_get_field(vsie, VSIE_SSIE_OFF, VSIE_SSIE_LEN);
    TEST_COMPARE("enable SSI. vsie.ssie is 1", 1, temp);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    csr_set_field(sip, SIP_SSIP_OFF, SIP_SSIP_LEN, 1);
    temp = csr_get_field(sip, SIP_SSIP_OFF, SIP_SSIP_LEN);
    TEST_COMPARE("set and check that sip.ssip is 0", 0, temp); // interrupt resets in handler

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in VS mode", ON, hideleg_ssi_v_mode);

    // clear state
    csr_set_field(hideleg, HIDELEG_VSSI_OFF, HIDELEG_VSSI_LEN, 0);
    hideleg_vssi = csr_get_field(hideleg, HIDELEG_VSSI_OFF, HIDELEG_VSSI_LEN);
    TEST_COMPARE("clear and check that hideleg SSI is 0. Delegation is OFF", 0, hideleg_vssi);

    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 0);
    temp = csr_get_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN);
    TEST_COMPARE("disable SSI. vsstatus.sie is 0", 0, temp);

    csr_set_field(vsie, VSIE_SSIE_OFF, VSIE_SSIE_LEN, 0);
    temp = csr_get_field(vsie, VSIE_SSIE_OFF, VSIE_SSIE_LEN);
    TEST_COMPARE("disable SSI. vsie.ssie is 0", 0, temp);

    TEST_END();
}
