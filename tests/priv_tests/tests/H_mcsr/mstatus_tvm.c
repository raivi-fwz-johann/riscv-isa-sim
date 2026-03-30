
#include <test_utils.h>

static reg_t mstatus_tvm_cause = 0;

void __attribute__((weak)) mstatus_tvm_handler(){
    mstatus_tvm_cause = CSRR(mcause);   
    excpt.triggered = true;
}

bool __attribute__((weak)) mstatus_tvm(){
    TEST_START();

    reg_t tvm;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear delegation register
    CSRW(medeleg, 0);
    set_mhandler(mstatus_tvm_handler);                                                                                                                                                                             

    // check TVM == 0, don't cause illigal instruction traps
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(mstatus, MSTATUS_TVM_OFF, MSTATUS_TVM_LEN, 0);
    tvm = csr_get_field(mstatus, MSTATUS_TVM_OFF, MSTATUS_TVM_LEN);
    TEST_COMPARE("clear and check that mstatus.tvm is 0", 0, tvm);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    CSRR(satp);
    TEST_COMPARE("read satp and check that exception is not triggered", false, excpt.triggered);

    CSRR(hgatp);
    TEST_COMPARE("read hgatp and check that exception is not triggered", false, excpt.triggered);

    CSRR(vsatp);
    TEST_COMPARE("read vsatp and check that exception is not triggered", false, excpt.triggered);

    asm volatile ("sfence.vma \n\t");
    TEST_COMPARE("run sfence.vma and check that exception is not triggered", false, excpt.triggered);
    
    asm volatile ("hfence.gvma \n\t");
    TEST_COMPARE("run hfence.gvma and check that exception is not triggered", false, excpt.triggered);

    asm volatile ("hfence.vvma \n\t");
    TEST_COMPARE("run hfence.vvma and check that exception is not triggered", false, excpt.triggered);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   


    // check TVM == 1, cause illigal instruction traps
    csr_set_field(mstatus, MSTATUS_TVM_OFF, MSTATUS_TVM_LEN, 1);
    tvm = csr_get_field(mstatus, MSTATUS_TVM_OFF, MSTATUS_TVM_LEN);
    TEST_COMPARE("set and check that mstatus.tvm is 1", 1, tvm);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = true;
    mstatus_tvm_cause = 0;
    CSRR(satp);
    TEST_COMPARE("read satp and check that exception is triggered", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, mstatus_tvm_cause);

    excpt.triggered = false;
    excpt.for_testing = true;
    mstatus_tvm_cause = 0;
    CSRR(hgatp);
    TEST_COMPARE("read hgatp and check that exception is triggered", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, mstatus_tvm_cause);

    excpt.triggered = false;
    excpt.for_testing = true;
    mstatus_tvm_cause = 0;
    CSRR(vsatp);
    TEST_COMPARE("read vsatp and check that exception is not triggered", false, excpt.triggered);

    excpt.triggered = false;
    excpt.for_testing = true;
    mstatus_tvm_cause = 0;
    asm volatile ("sfence.vma \n\t");
    TEST_COMPARE("run sfence.vma and check that exception is triggered", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, mstatus_tvm_cause);

    excpt.triggered = false;
    excpt.for_testing = true;
    mstatus_tvm_cause = 0;
    asm volatile ("hfence.gvma \n\t");
    TEST_COMPARE("run hfence.gvma and check that exception is triggered", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, mstatus_tvm_cause);

    excpt.triggered = false;
    excpt.for_testing = true;
    mstatus_tvm_cause = 0;
    asm volatile ("hfence.vvma \n\t");
    TEST_COMPARE("run hfence.vvma and check that exception is not triggered", false, excpt.triggered);


    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    
    // clear states
    csr_set_field(mstatus, MSTATUS_TVM_OFF, MSTATUS_TVM_LEN, 0);
    tvm = csr_get_field(mstatus, MSTATUS_TVM_OFF, MSTATUS_TVM_LEN);
    TEST_COMPARE("clear and check that mstatus.tvm is 0", 0, tvm);

    TEST_END();
}
