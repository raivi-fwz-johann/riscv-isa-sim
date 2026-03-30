
#include <test_utils.h>

static reg_t mideleg_sei_mode = 0;
extern reg_t mideleg_sei_return_address;

void __attribute__((weak)) mideleg_sei_mhandler(){
    reg_t mcause_cause = CSRR(mcause);

    if (mcause_cause == CAUSE_SUPERVISOR_ECALL){
        csr_set_field(mie, MIE_SEIE_OFF, MIE_SEIE_LEN, 1);
    }
    else {
        excpt.triggered = true;
        csr_set_field(mie, MIE_SEIE_OFF, MIE_SEIE_LEN, 0);
        mideleg_sei_mode = MODE_M;
    }
    CSRW(mepc, (reg_t)&mideleg_sei_return_address);
}

void __attribute__((weak)) mideleg_sei_shandler(){
    excpt.triggered = true;
    csr_set_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN, 0);
    mideleg_sei_mode = MODE_S;
}

bool __attribute__((weak)) mideleg_sei(){
    TEST_START();

    reg_t mideleg_sei;
    reg_t temp;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mideleg_sei_mhandler);                                                                                                                                                                             
    set_shandler(mideleg_sei_shandler);                                                                                                                                                                             
    
    // enable supervisor software interrupt
    csr_set_field(mip, MIP_SEIP_OFF, MIP_SEIP_LEN, 1);

    csr_set_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN, 0);
    temp = csr_get_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN);
    TEST_COMPARE("enable SSI. mstatus.sie is 0", 0, temp);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    temp = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, temp);


    // check that trap without delegation is handled in M mode
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mideleg, MIDELEG_SEI_OFF, MIDELEG_SEI_LEN, 0);
    mideleg_sei = csr_get_field(mideleg, MIDELEG_SEI_OFF, MIDELEG_SEI_LEN);
    TEST_COMPARE("clear and check that mideleg SEI is 0. Delegation is OFF", 0, mideleg_sei);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // we can't enable software interrupt from S-mode because it does not delegated
    // and we can't enable software interupt before because we need handler to switch between modes
    // so we use ecall trap for that
    // next one more interrupt is fired if MIE STIE is one
    // mstatus.sie == 1 when we enter in S mode
    // sstatus.sie == 1 we set before
    asm volatile (
        "ecall \n"
        ".globl mideleg_sei_return_address \n"
        "mideleg_sei_return_address: \n"
        "nop \n"
    );


    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in M mode", MODE_M, mideleg_sei_mode);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   


    // check that trap with delegation is handled in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mideleg, MIDELEG_SEI_OFF, MIDELEG_SEI_LEN, 1);
    mideleg_sei = csr_get_field(mideleg, MIDELEG_SEI_OFF, MIDELEG_SEI_LEN);
    TEST_COMPARE("clear and check that mideleg SEI is 1. Delegation is ON", 1, mideleg_sei);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // now mideleg.sei is 1 and interrupt is fired in S mode
    csr_set_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN, 1);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in S mode", MODE_S, mideleg_sei_mode);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear state
    csr_set_field(mideleg, MIDELEG_SEI_OFF, MIDELEG_SEI_LEN, 0);
    mideleg_sei = csr_get_field(mideleg, MIDELEG_SEI_OFF, MIDELEG_SEI_LEN);
    TEST_COMPARE("clear and check that mideleg SEI is 0. Delegation is OFF", 0, mideleg_sei);

    csr_set_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN, 0);
    temp = csr_get_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN);
    TEST_COMPARE("disable SEI. mstatus.sie is 0", 0, temp);

    csr_set_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN, 0);
    temp = csr_get_field(sie, SIE_SEIE_OFF, SIE_SEIE_LEN);
    TEST_COMPARE("disable SEI. sie.seie is 0", 0, temp);

    TEST_END();
}
