
#include <test_utils.h>

static reg_t mideleg_sti_mode = 0;
extern reg_t mideleg_sti_return_address;

void __attribute__((weak)) mideleg_sti_mhandler(){
    reg_t mcause_cause = CSRR(mcause);

    if (mcause_cause == CAUSE_SUPERVISOR_ECALL){
        csr_set_field(mie, MIE_STIE_OFF, MIE_STIE_LEN, 1);
    }
    else {
        excpt.triggered = true;
        csr_set_field(mie, MIE_STIE_OFF, MIE_STIE_LEN, 0);
        mideleg_sti_mode = MODE_M;
    }
    CSRW(mepc, (reg_t)&mideleg_sti_return_address);
}

void __attribute__((weak)) mideleg_sti_shandler(){
    excpt.triggered = true;
    csr_set_field(sie, SIE_STIE_OFF, SIE_STIE_LEN, 0);
    mideleg_sti_mode = MODE_S;
}

bool __attribute__((weak)) mideleg_sti(){
    TEST_START();

    reg_t mideleg_sti;
    reg_t temp;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mideleg_sti_mhandler);                                                                                                                                                                             
    set_shandler(mideleg_sti_shandler);                                                                                                                                                                             
    
    // enable supervisor software interrupt
    csr_set_field(mip, MIP_STIP_OFF, MIP_STIP_LEN, 1);

    csr_set_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN, 0);
    temp = csr_get_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN);
    TEST_COMPARE("enable SSI. mstatus.sie is 0", 0, temp);

    csr_set_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN, 1);
    temp = csr_get_field(sstatus, SSTATUS_SIE_OFF, SSTATUS_SIE_LEN);
    TEST_COMPARE("check sstatus.sie is set", 1, temp);


    // check that trap without delegation is handled in M mode
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mideleg, MIDELEG_STI_OFF, MIDELEG_STI_LEN, 0);
    mideleg_sti = csr_get_field(mideleg, MIDELEG_STI_OFF, MIDELEG_STI_LEN);
    TEST_COMPARE("clear and check that mideleg STI is 0. Delegation is OFF", 0, mideleg_sti);

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
        ".globl mideleg_sti_return_address \n"
        "mideleg_sti_return_address: \n"
        "nop \n"
    );


    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in M mode", MODE_M, mideleg_sti_mode);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   


    // check that trap with delegation is handled in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mideleg, MIDELEG_STI_OFF, MIDELEG_STI_LEN, 1);
    mideleg_sti = csr_get_field(mideleg, MIDELEG_STI_OFF, MIDELEG_STI_LEN);
    TEST_COMPARE("clear and check that mideleg STI is 1. Delegation is ON", 1, mideleg_sti);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // now mideleg.sti is 1 and interrupt is fired in S mode
    csr_set_field(sie, SIE_STIE_OFF, SIE_STIE_LEN, 1);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in S mode", MODE_S, mideleg_sti_mode);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear state
    csr_set_field(mideleg, MIDELEG_STI_OFF, MIDELEG_STI_LEN, 0);
    mideleg_sti = csr_get_field(mideleg, MIDELEG_STI_OFF, MIDELEG_STI_LEN);
    TEST_COMPARE("clear and check that mideleg STI is 0. Delegation is OFF", 0, mideleg_sti);

    csr_set_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN, 0);
    temp = csr_get_field(mstatus, MSTATUS_SIE_OFF, MSTATUS_SIE_LEN);
    TEST_COMPARE("disable STI. mstatus.sie is 0", 0, temp);

    csr_set_field(sie, SIE_STIE_OFF, SIE_STIE_LEN, 0);
    temp = csr_get_field(sie, SIE_STIE_OFF, SIE_STIE_LEN);
    TEST_COMPARE("disable STI. sie.stie is 0", 0, temp);

    TEST_END();
}
