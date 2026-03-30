
#include <test_utils.h>

static reg_t hstatus_vtw_cause = 0;

void __attribute__((weak)) hstatus_vtw_handler(){
    hstatus_vtw_cause = CSRR(scause);   
    excpt.triggered = true;
}

bool __attribute__((weak)) hstatus_vtw(){
    TEST_START();

    reg_t vtw;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(hstatus_vtw_handler);                                                                                                                                                                             

    // set TW to 1
    csr_set_field(hstatus, HSTATUS_VTW_OFF, HSTATUS_VTW_LEN, 1);
    vtw = csr_get_field(hstatus, HSTATUS_VTW_OFF, HSTATUS_VTW_LEN);
    TEST_COMPARE("set and check that hstatus.vtw is 1", 1, vtw);


    // check that wfi in VS mode cause illigal instruction traps
    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = true;
    hstatus_vtw_cause = 0;
    asm volatile ("wfi \n\t");
    TEST_COMPARE("run wfi and check that exception is triggeredin VS mode", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_VIRTUAL_INSTRUCTION, hstatus_vtw_cause);

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    // clear states
    csr_set_field(hstatus, HSTATUS_VTW_OFF, HSTATUS_VTW_LEN, 0);
    vtw = csr_get_field(hstatus, HSTATUS_VTW_OFF, HSTATUS_VTW_LEN);
    TEST_COMPARE("clear and check that hstatus.vtw is 0", 0, vtw);

    TEST_END();
}
