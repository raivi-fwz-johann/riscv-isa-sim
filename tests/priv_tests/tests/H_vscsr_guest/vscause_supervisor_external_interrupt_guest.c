
#include <test_utils.h>

static reg_t scause_cause = 32;

static void vscause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(scause);
    csr_set_field(sstatus, SSTATUS_SPIE_OFF, SSTATUS_SPIE_LEN, 0);
}

bool __attribute__((weak)) vscause_supervisor_external_interrupt_guest(){
    TEST_START();

    reg_t temp;
    reg_t cause, interrupt_bit;

    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(vscause_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    temp = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, temp);

    // set pending in init
    temp = csr_get_field(sip, SIP_SEIP_OFF, SIP_SEIP_LEN);
    TEST_COMPARE("check sip.seip is set", 1, temp);

    csr_set_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN, 1);
    temp = csr_get_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN);
    TEST_COMPARE("check sie.seie is set", 1, temp);

    cause = scause_cause & ~(1L << (XLEN_BYTES * 8 - 1));

    interrupt_bit = scause_cause | (1L << (XLEN_BYTES * 8 - 1));
    interrupt_bit >>= (XLEN_BYTES * 8 - 1);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause SUPERVISOR EXTERNAL INTERRUPT", SIE_SEIE_OFF, cause);
    TEST_COMPARE("check scause interrupt bit is set", 1, interrupt_bit);

    // clear fields
    csr_set_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN, 0);
    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 0);

    TEST_END();
}
