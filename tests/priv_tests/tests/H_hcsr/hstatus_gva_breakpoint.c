
#include <test_utils.h>

static reg_t hstatus_gva = 0;

static void hstatus_gva_shandler(){
    excpt.triggered = true;
    hstatus_gva = csr_get_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN);
}

bool __attribute__((weak)) hstatus_gva_breakpoint(){
    TEST_START();

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(hstatus_gva_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN, 0);
    reg_t reg = csr_get_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN);
    TEST_COMPARE("check hstatus.gva is clear", 0, hstatus_gva);

    set_virtial_mode_host(ON);
    asm volatile (
        ".globl stval_break_addr\n\t"
        "stval_break_addr: \n\t"
        "ebreak \n\t"
    );
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    TEST_COMPARE("check hstatus.gva is set under BREAKPOINT exception", 1, hstatus_gva);

    // clear changes
    csr_set_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN, 0);

    TEST_END();
}
