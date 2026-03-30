
#include <test_utils.h>

static reg_t hstatus_vtvm_cause = 0;

void __attribute__((weak)) hstatus_vtvm_handler(){
    hstatus_vtvm_cause = CSRR(scause);   
    excpt.triggered = true;
}

bool __attribute__((weak)) hstatus_vtvm(){
    TEST_START();

    reg_t vtvm;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(hstatus_vtvm_handler);                                                                                                                                                                             

    // check VTVM == 0, don't cause illigal instruction traps
    excpt.triggered = false;
    excpt.for_testing = false;

    csr_set_field(hstatus, HSTATUS_VTVM_OFF, HSTATUS_VTVM_LEN, 0);
    vtvm = csr_get_field(hstatus, HSTATUS_VTVM_OFF, HSTATUS_VTVM_LEN);
    TEST_COMPARE("clear and check that hstatus.vtvm is 0", 0, vtvm);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    CSRR(satp);
    TEST_COMPARE("read satp and check that exception is not triggered", false, excpt.triggered);

    asm volatile ("sfence.vma \n\t");
    TEST_COMPARE("run sfence.vma and check that exception is not triggered", false, excpt.triggered);
    
    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   


    // check TVM == 1, cause illigal instruction traps
    csr_set_field(hstatus, HSTATUS_VTVM_OFF, HSTATUS_VTVM_LEN, 1);
    vtvm = csr_get_field(hstatus, HSTATUS_VTVM_OFF, HSTATUS_VTVM_LEN);
    TEST_COMPARE("set and check that hstatus.vtvm is 1", 1, vtvm);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = true;
    hstatus_vtvm_cause = 0;

    CSRR(satp);
    TEST_COMPARE("read satp and check that exception is triggered", true, excpt.triggered);
    TEST_COMPARE("check that cause is illigal instruction", CAUSE_VIRTUAL_INSTRUCTION, hstatus_vtvm_cause);

    excpt.triggered = false;
    excpt.for_testing = true;
    hstatus_vtvm_cause = 0;
    asm volatile ("sfence.vma \n\t");
    TEST_COMPARE("run sfence.vma and check that exception is triggered", true, excpt.triggered);
    TEST_COMPARE("check that cause is illigal instruction", CAUSE_VIRTUAL_INSTRUCTION, hstatus_vtvm_cause);
    
    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // clear states
    csr_set_field(hstatus, HSTATUS_VTVM_OFF, HSTATUS_VTVM_LEN, 0);
    vtvm = csr_get_field(hstatus, HSTATUS_VTVM_OFF, HSTATUS_VTVM_LEN);
    TEST_COMPARE("clear and check that hstatus.vtvm is 0", 0, vtvm);

    TEST_END();
}
