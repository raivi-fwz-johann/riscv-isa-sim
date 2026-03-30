
#include <test_utils.h>

static reg_t hideleg_sti_v_mode = 0;

void hideleg_sti_shandler(){
    excpt.triggered = true;
    csr_set_field(vsip, VSIP_STIP_OFF, VSIP_STIP_OFF, 0);
    hideleg_sti_v_mode = OFF;
}

void hideleg_sti_vshandler(){
    excpt.triggered = true;
    csr_set_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN, 0);
    hideleg_sti_v_mode = ON;
}

bool __attribute__((weak)) hideleg_vsti(){
    TEST_START();

    reg_t hideleg_vsti;
    reg_t temp;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    set_shandler(hideleg_sti_shandler);                                                                                                                                                                             
    set_vshandler(hideleg_sti_vshandler);                                                                                                                                                                             

    // set iterrupt in vs mode always pending
    csr_set_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN, 1);
    
    // check that trap with delegation is handled in VS mode
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(hideleg, HIDELEG_VSTI_OFF, HIDELEG_VSTI_LEN, 1);
    hideleg_vsti = csr_get_field(hideleg, HIDELEG_VSTI_OFF, HIDELEG_VSTI_LEN);
    TEST_COMPARE("clear and check that hideleg STI is 1. Delegation is ON", 1, hideleg_vsti);

    csr_set_field(vsie, VSIE_STIE_OFF, VSIE_STIE_LEN, 1);
    temp = csr_get_field(vsie, VSIE_STIE_OFF, VSIE_STIE_LEN);
    TEST_COMPARE("enable STI. vsie.stie is 1", 1, temp);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    temp = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("enable STI. vsstatus.sie is 0", 0, temp); // interrupt enable resets in handler

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in VS mode", ON, hideleg_sti_v_mode);

    // clear state
    csr_set_field(hideleg, HIDELEG_VSTI_OFF, HIDELEG_VSTI_LEN, 0);
    hideleg_vsti = csr_get_field(hideleg, HIDELEG_VSTI_OFF, HIDELEG_VSTI_LEN);
    TEST_COMPARE("clear and check that hideleg STI is 0. Delegation is OFF", 0, hideleg_vsti);

    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 0);
    temp = csr_get_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN);
    TEST_COMPARE("disable STI. vsstatus.sie is 0", 0, temp);

    csr_set_field(vsie, VSIE_STIE_OFF, VSIE_STIE_LEN, 0);
    temp = csr_get_field(vsie, VSIE_STIE_OFF, VSIE_STIE_LEN);
    TEST_COMPARE("disable STI. vsie.stie is 0", 0, temp);

    TEST_END();
}
