
#include <test_utils.h>

static reg_t mstatus_vs_cause = 0;

void __attribute__((weak)) mstatus_vs_handler(){
    mstatus_vs_cause = CSRR(mcause);
    excpt.triggered = true;
}

bool __attribute__((weak)) mstatus_vs(){
    TEST_START();

    const reg_t vs_off = 0b00;
    const reg_t vs_initial = 0b01;
    const reg_t vs_clean = 0b10;
    const reg_t vs_dirty = 0b11;

    reg_t vs;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear delegation register
    CSRW(medeleg, 0);
    set_mhandler(mstatus_vs_handler);                                                                                                                                                                             


    // check vs == OFF cause illigal instruction
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN, vs_off);
    vs = csr_get_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN);
    TEST_COMPARE("set and check that mstatus.vs is in OFF state", vs_off, vs);

    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");

    TEST_COMPARE("check that exception is triggered", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, mstatus_vs_cause);
    
    excpt.triggered = false;
    excpt.for_testing = false;

    // set fs to Initial State
    csr_set_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN, vs_initial);
    vs = csr_get_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN);
    TEST_COMPARE("set and check that mstatus.vs is in INITIAL state", vs_initial, vs);

    // perform vector operaion and check that state is Dirty
    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");
    asm volatile ("vmv.v.x v0, x0 \n\t");

    TEST_COMPARE("check that exception is not triggered", false, excpt.triggered);

    vs = csr_get_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN);
    TEST_COMPARE("check that mstatus.vs is in DIRTY state", vs_dirty, vs);

    // clear state and perform vector operation again
    csr_set_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN, vs_clean);
    vs = csr_get_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN);
    TEST_COMPARE("set and check that mstatus.vs is in CLEAN state", vs_clean, vs);

    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");
    asm volatile ("vmv.v.x v0, x0 \n\t");

    TEST_COMPARE("check that exception is not triggered", false, excpt.triggered);

    vs = csr_get_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN);
    TEST_COMPARE("check that mstatus.vs is in DIRTY state", vs_dirty, vs);

    // set state back to off
    csr_set_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN, vs_off);
    vs = csr_get_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN);
    TEST_COMPARE("set and check that mstatus.vs is in OFF state", vs_off, vs);

    TEST_END();
}
