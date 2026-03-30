
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

bool __attribute__((weak)) vscause_supervisor_software_interrupt_host(){
    TEST_START();

    reg_t ssie, ssip, sie;

    reg_t cause, interrupt_bit;

    set_vshandler(vscause_vshandler);                                                                                                                                                                             
    set_shandler(vscause_shandler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = true;

    // delegate all interrupts to VS mode
    CSRW(hideleg, ~0L);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    sie = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, sie);

    csr_set_field(sip, SIP_SSIP_OFF, SIP_SSIP_LEN, 1);
    ssip = csr_get_field(sip, SIP_SSIP_OFF, SIP_SSIP_LEN);
    TEST_COMPARE("check sip.ssip is set", 1, ssip);

    csr_set_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN, 1);

    asm volatile ("nop \n\t");
    asm volatile ("nop \n\t");
    asm volatile ("nop \n\t");
    
    ssie = csr_get_field(sie, SIE_SSIE_OFF, SIE_SSIE_LEN);
    TEST_COMPARE("check sie.ssie is set", 1, ssie);

    cause = scause_cause & ~(1L << (XLEN_BYTES * 8 - 1));

    interrupt_bit = scause_cause | (1L << (XLEN_BYTES * 8 - 1));
    interrupt_bit >>= (XLEN_BYTES * 8 - 1);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause SUPERVISOR SOFTWARE INTERRUPT", SIE_SSIE_OFF, cause);
    TEST_COMPARE("check scause interrupt bit is set", 1, interrupt_bit);

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // clear fields
    csr_set_field(vsie, VSIE_SSIE_OFF, VSIE_SSIE_LEN, 0);
    csr_set_field(vsip, VSIP_SSIP_OFF, VSIP_SSIP_LEN, 0);
    csr_set_field(vsstatus, VSSTATUS_SIE_OFF, VSSTATUS_SIE_LEN, 0);

    CSRW(hideleg, 0L);

    TEST_END();
}
