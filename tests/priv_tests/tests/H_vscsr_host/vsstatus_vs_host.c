
#include <test_utils.h>

static reg_t sstatus_vs_cause = 0;

void __attribute__((weak)) vsstatus_vs_handler(){
    sstatus_vs_cause = CSRR(scause);
    excpt.triggered = true;
}

bool __attribute__((weak)) vsstatus_vs_host(){
    TEST_START();

    const reg_t vs_off = 0b00;
    const reg_t vs_initial = 0b01;
    const reg_t vs_clean = 0b10;
    const reg_t vs_dirty = 0b11;

    reg_t vs;

    set_shandler(vsstatus_vs_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // init VS reg in Host
    csr_set_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN, vs_initial);
    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("set and check that sstatus.vs is in INITIAL state", vs_initial, vs);


    // check vs == OFF cause illigal instruction
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN, vs_off);
    vs = csr_get_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN);
    TEST_COMPARE("set and check that vsstatus.vs is in OFF state", vs_off, vs);

    set_virtial_mode_host(ON);
    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that exception is triggered", true, excpt.triggered);
    TEST_COMPARE("check that scause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, sstatus_vs_cause);
    
    // set fs to Initial State
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN, vs_initial);
    vs = csr_get_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN);
    TEST_COMPARE("set and check that vsstatus.vs is in INITIAL state", vs_initial, vs);

    // perform vector operaion and check that state is Dirty
    set_virtial_mode_host(ON);
    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");
    asm volatile ("vmv.v.x v0, x0 \n\t");
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that exception is not triggered", false, excpt.triggered);

    vs = csr_get_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN);
    TEST_COMPARE("check that vsstatus.vs is in DIRTY state", vs_dirty, vs);

    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("check that sstatus.vs is in DIRTY state", vs_dirty, vs);

    // clear state and perform vector operation again
    csr_set_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN, vs_clean);

    vs = csr_get_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN);
    TEST_COMPARE("set and check that vsstatus.vs is in CLEAN state", vs_clean, vs);

    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("set and check that sstatus.vs is in DIRTY state", vs_dirty, vs);

    set_virtial_mode_host(ON);
    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");
    asm volatile ("vmv.v.x v0, x0 \n\t");
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that exception is not triggered", false, excpt.triggered);

    vs = csr_get_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN);
    TEST_COMPARE("check that vsstatus.vs is in DIRTY state", vs_dirty, vs);

    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("check that sstatus.vs is in DIRTY state", vs_dirty, vs);
    
    // set state back to off
    csr_set_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN, vs_off);
    vs = csr_get_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN);
    TEST_COMPARE("set and check that vsstatus.vs is in OFF state", vs_off, vs);

    csr_set_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN, vs_off);
    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("set and check that sstatus.vs is in OFF state", vs_off, vs);

    TEST_END();
}
