
#include <test_utils.h>

static reg_t sstatus_vs_cause = 0;

void __attribute__((weak)) sstatus_vs_handler(){
    sstatus_vs_cause = CSRR(scause);
    excpt.triggered = true;
}

bool __attribute__((weak)) sstatus_vs(){
    TEST_START();

    const reg_t vs_off = 0b00;
    const reg_t vs_initial = 0b01;
    const reg_t vs_clean = 0b10;
    const reg_t vs_dirty = 0b11;

    reg_t vs;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    set_shandler(sstatus_vs_handler);                                                                                                                                                                             

    // check vs == OFF cause illigal instruction
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN, vs_off);
    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("set and check that sstatus.vs is in OFF state", vs_off, vs);

    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");

    TEST_COMPARE("check that exception is triggered", true, excpt.triggered);
    TEST_COMPARE("check that scause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, sstatus_vs_cause);
    
    excpt.triggered = false;
    excpt.for_testing = false;

    // set fs to Initial State
    csr_set_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN, vs_initial);
    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("set and check that sstatus.vs is in INITIAL state", vs_initial, vs);

    // perform vector operaion and check that state is Dirty
    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");
    asm volatile ("vmv.v.x v0, x0 \n\t");

    TEST_COMPARE("check that exception is not triggered", false, excpt.triggered);

    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("check that sstatus.vs is in DIRTY state", vs_dirty, vs);

    // clear state and perform vector operation again
    csr_set_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN, vs_clean);
    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("set and check that sstatus.vs is in CLEAN state", vs_clean, vs);

    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");
    asm volatile ("vmv.v.x v0, x0 \n\t");

    TEST_COMPARE("check that exception is not triggered", false, excpt.triggered);

    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("check that sstatus.vs is in DIRTY state", vs_dirty, vs);

    // set state back to off
    csr_set_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN, vs_off);
    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("set and check that sstatus.vs is in OFF state", vs_off, vs);

    TEST_END();
}
