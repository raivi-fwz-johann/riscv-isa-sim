
#include <test_utils.h>

static reg_t scause_cause = 32;

static void scause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(scause);
}

bool __attribute__((weak)) scause_illigal_instruction(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(scause_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile ("unimp \n\t");

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_ILLEGAL_INSTRUCTION", CAUSE_ILLEGAL_INSTRUCTION, scause_cause);

    TEST_END();
}
