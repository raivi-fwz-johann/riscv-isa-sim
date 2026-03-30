
#include <test_utils.h>

static reg_t mstatus_tw_cause = 0;

void __attribute__((weak)) mstatus_tw_handler(){
    mstatus_tw_cause = CSRR(mcause);   
    excpt.triggered = true;
}

bool __attribute__((weak)) mstatus_tw(){
    TEST_START();

    reg_t tw;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear delegation register
    CSRW(medeleg, 0);
    set_mhandler(mstatus_tw_handler);                                                                                                                                                                             


    // set TW to 1
    csr_set_field(mstatus, MSTATUS_TW_OFF, MSTATUS_TW_LEN, 1);
    tw = csr_get_field(mstatus, MSTATUS_TW_OFF, MSTATUS_TW_LEN);
    TEST_COMPARE("set and check that mstatus.tw is 1", 1, tw);


    // check that wfi in S mode cause illigal instruction traps
    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = true;
    mstatus_tw_cause = 0;
    asm volatile ("wfi \n\t");
    TEST_COMPARE("run wfi and check that exception is triggeredin S mode", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, mstatus_tw_cause);

    
    // check that wfi in U mode cause illigal instruction traps
    switch_mode(MODE_U);
    TEST_COMPARE("check that currunt mode is S", MODE_U, current_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = true;
    mstatus_tw_cause = 0;
    asm volatile ("wfi \n\t");
    TEST_COMPARE("run wfi and check that exception is triggeredin U mode", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, mstatus_tw_cause);


    // clear states
    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    csr_set_field(mstatus, MSTATUS_TW_OFF, MSTATUS_TW_LEN, 0);
    tw = csr_get_field(mstatus, MSTATUS_TW_OFF, MSTATUS_TW_LEN);
    TEST_COMPARE("clear and check that mstatus.tw is 0", 0, tw);

    TEST_END();
}
