
#include <test_utils.h>

static reg_t mstatus_tsr_cause = 0;

void __attribute__((weak)) mstatus_tsr_handler(){
    mstatus_tsr_cause = CSRR(mcause);   
    excpt.triggered = true;
}

bool __attribute__((weak)) mstatus_tsr(){
    TEST_START();

    reg_t tsr;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear delegation register
    CSRW(medeleg, 0);
    set_mhandler(mstatus_tsr_handler);                                                                                                                                                                             


    // set TSR to 1
    csr_set_field(mstatus, MSTATUS_TSR_OFF, MSTATUS_TSR_LEN, 1);
    tsr = csr_get_field(mstatus, MSTATUS_TSR_OFF, MSTATUS_TSR_LEN);
    TEST_COMPARE("set and check that mstatus.tsr is 1", 1, tsr);


    // check that sret in S mode cause illigal instruction traps
    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = true;
    mstatus_tsr_cause = 0;
    asm volatile ("sret \n\t");
    TEST_COMPARE("run sret and check that exception is triggeredin S mode", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, mstatus_tsr_cause);

    // check that sret in VS mode not cause illigal instruction traps
    set_virtial_mode_machine(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = false;
    mstatus_tsr_cause = 0;
    
    asm volatile (
        "la t0, 1f     \n\t"
        "csrw sepc, t0 \n\t"
        "sret          \n\t"
        "1:            \n\t"
    );

    TEST_COMPARE("run sret and check that exception is not  triggered in VS mode", false, excpt.triggered);
    
    set_virtial_mode_machine(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   


    // clear states
    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    csr_set_field(mstatus, MSTATUS_TSR_OFF, MSTATUS_TSR_LEN, 0);
    tsr = csr_get_field(mstatus, MSTATUS_TSR_OFF, MSTATUS_TSR_LEN);
    TEST_COMPARE("clear and check that mstatus.tsr is 0", 0, tsr);

    TEST_END();
}
