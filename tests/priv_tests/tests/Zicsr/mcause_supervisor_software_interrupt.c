
#include <test_utils.h>

static reg_t mcause_cause = 32;
extern reg_t mcause_return_address_ssip;

static void mcause_mhandler(){
    mcause_cause = CSRR(mcause);

    if (mcause_cause == CAUSE_SUPERVISOR_ECALL){
        csr_set_field(mie, MIE_SSIE_OFF, MIE_SSIE_LEN, 1);
    }
    else {
        excpt.triggered = true;
        csr_set_field(mie, MIE_SSIE_OFF, MIE_SSIE_LEN, 0);
    }
    CSRW(mepc, (reg_t)&mcause_return_address_ssip);
}

bool __attribute__((weak)) mcause_supervisor_software_interrupt(){
    TEST_START();

    reg_t temp;
    reg_t cause, interrupt_bit;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    CSRW(mideleg, 0);
    set_mhandler(mcause_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(mip, 1 << MIP_SSIP_OFF);
    
    switch_mode(MODE_S);
    TEST_COMPARE("switch to S mode and check that currunt mode is S", MODE_S, current_mode);  

    // we can't enable sofware interrupt from S-mode because it does not delegated
    // so we use ecall trap for that
    // next one more interrupt is fired if MIE SSIE is one
    asm volatile (
        "ecall \n"
        ".globl mcause_return_address_ssip \n"
        "mcause_return_address_ssip: \n"
        "nop \n"
    );

    cause = mcause_cause & ~(1L << (XLEN_BYTES * 8 - 1));

    interrupt_bit = mcause_cause & (1L << (XLEN_BYTES * 8 - 1));
    interrupt_bit >>= (XLEN_BYTES * 8 - 1);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause SUPERVISOR SOFTWARE INTERRUPT", SIE_SSIE_OFF, cause);
    TEST_COMPARE("check mcause interrupt bit is set", 1, interrupt_bit);

    switch_mode(MODE_M);
    TEST_COMPARE("switch to M mode and check that currunt mode is M", MODE_M, current_mode);  

    // clear fields
    CSRW(mip, 0);

    TEST_END();
}
