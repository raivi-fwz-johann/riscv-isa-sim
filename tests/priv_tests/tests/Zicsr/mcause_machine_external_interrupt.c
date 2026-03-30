
#include <test_utils.h>

static reg_t mcause_cause = 32;

static void mcause_mhandler(){
    excpt.triggered = true;
    mcause_cause = CSRR(mcause);
    csr_set_field(mstatus, MSTATUS_MPIE_OFF, MSTATUS_MPIE_LEN, 0);
}

bool __attribute__((weak)) mcause_machine_external_interrupt(){
    TEST_START();

    reg_t meie, meip, mie;

    reg_t cause, interrupt_bit;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mcause_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 1);
    mie = csr_get_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN);
    TEST_COMPARE("check mstatus.mie is set", 1, mie);

    csr_set_field(mip, MIP_MEIP_OFF, MIP_MEIP_LEN, 1);
    meip = csr_get_field(mip, MIP_MEIP_OFF, MIP_MEIP_LEN);
    TEST_COMPARE("check mip.meip is set", 1, meip);

    csr_set_field(mie, MIE_MEIE_OFF, MIE_MEIE_LEN, 1);
    
    meie = csr_get_field(mie, MIE_MEIE_OFF, MIE_MEIE_LEN);
    TEST_COMPARE("check mie.meie is set", 1, meie);

    cause = mcause_cause & ~(1L << (XLEN_BYTES * 8 - 1));

    interrupt_bit = mcause_cause & (1L << (XLEN_BYTES * 8 - 1));
    interrupt_bit >>= (XLEN_BYTES * 8 - 1);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause MACHINE EXTERNAL INTERRUPT", MIE_MEIE_OFF, cause);
    TEST_COMPARE("check mcause interrupt bit is set", 1, interrupt_bit);

    // clear fields
    csr_set_field(mie, MIE_MEIE_OFF, MIE_MEIE_LEN, 0);
    csr_set_field(mip, MIP_MEIP_OFF, MIP_MEIP_LEN, 0);
    csr_set_field(mstatus, MSTATUS_MIE_OFF, MSTATUS_MIE_LEN, 0);

    TEST_END();
}
