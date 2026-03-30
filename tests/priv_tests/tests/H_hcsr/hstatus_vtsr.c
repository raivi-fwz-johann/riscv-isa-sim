
#include <test_utils.h>

static reg_t hstatus_vtsr_cause = 0;

void __attribute__((weak)) hstatus_vtsr_handler(){
    hstatus_vtsr_cause = CSRR(scause);   
    excpt.triggered = true;
}

bool __attribute__((weak)) hstatus_vtsr(){
    TEST_START();

    reg_t vtsr;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(hstatus_vtsr_handler);                                                                                                                                                                             

    // set TSR to 1
    csr_set_field(hstatus, HSTATUS_VTSR_OFF, HSTATUS_VTSR_LEN, 1);
    vtsr = csr_get_field(hstatus, HSTATUS_VTSR_OFF, HSTATUS_VTSR_LEN);
    TEST_COMPARE("set and check that hstatus.vtsr is 1", 1, vtsr);


    // check that sret in VS mode cause illigal instruction traps
    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = true;
    hstatus_vtsr_cause = 0;
    asm volatile ("sret \n\t");
    TEST_COMPARE("run sret and check that exception is triggeredin S mode", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_VIRTUAL_INSTRUCTION, hstatus_vtsr_cause);

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // clear states
    csr_set_field(hstatus, HSTATUS_VTSR_OFF, HSTATUS_VTSR_LEN, 0);
    vtsr = csr_get_field(hstatus, HSTATUS_VTSR_OFF, HSTATUS_VTSR_LEN);
    TEST_COMPARE("clear and check that hstatus.vtsr is 0", 0, vtsr);

    TEST_END();
}
