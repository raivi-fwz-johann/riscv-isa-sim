
#include <test_utils.h>

static reg_t scause_cause = 32;

static void vscause_vshandler(){
    // run ecall to jump to Host hamdler and read VS register
    ecall(0,0);
}

static void vscause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(vscause);
    csr_set_field(vsstatus, VSSTATUS_SPIE_OFF, VSSTATUS_SPIE_LEN, 0);
}

bool __attribute__((weak)) vscause_supervisor_timer_interrupt_host(){
    TEST_START();

    reg_t temp;
    reg_t cause, interrupt_bit;

    set_vshandler(vscause_vshandler);                                                                                                                                                                             
    set_shandler(vscause_shandler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = true;

    // delegate all interrupts to VS mode
    CSRW(hideleg, ~0L);

    csr_set_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN, 1);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    temp = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, temp);

    temp = csr_get_field(sip, SIP_STIP_OFF, SIP_STIP_LEN);
    TEST_COMPARE("check sip.stip is set", 1, temp);

    csr_set_field(sie, SIE_STIE_OFF, SIE_STIE_LEN, 1);
    temp = csr_get_field(sie, SIE_STIE_OFF, SIE_STIE_LEN);
    TEST_COMPARE("check sie.stie is set", 1, temp);

    cause = scause_cause & ~(1L << (XLEN_BYTES * 8 - 1));

    interrupt_bit = scause_cause | (1L << (XLEN_BYTES * 8 - 1));
    interrupt_bit >>= (XLEN_BYTES * 8 - 1);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause SUPERVISOR TIMER INTERRUPT", SIE_STIE_OFF, cause);
    TEST_COMPARE("check scause interrupt bit is set", 1, interrupt_bit);

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // clear fields
    csr_set_field(vsie, VSIE_STIE_OFF, VSIE_STIE_LEN, 0);
    csr_set_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN, 0);
    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 0);

    CSRW(hideleg, 0L);

    TEST_END();
}
