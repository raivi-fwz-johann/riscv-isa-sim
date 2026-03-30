
#include <test_utils.h>

static reg_t hstatus_gva = 0;

extern reg_t hstatus_gva_access_fault_handler_return_addr;

static void hstatus_gva_shandler(){
    excpt.triggered = true;
    hstatus_gva = csr_get_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN);

    CSRW(sepc, (reg_t)(&hstatus_gva_access_fault_handler_return_addr));
}

bool __attribute__((weak)) hstatus_gva_instruction_access_fault(){
    TEST_START();

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(hstatus_gva_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN, 0);
    reg_t reg = csr_get_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN);
    TEST_COMPARE("check hstatus.gva is clear", 0, reg);

    set_virtial_mode_host(ON);

    // access to 0x7FFFFFFF is restricted by pmp in boot.S
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "jr t0 \n\t"

        ".globl hstatus_gva_access_fault_handler_return_addr\n\t"
        "hstatus_gva_access_fault_handler_return_addr: \n\t"
        "nop \n\t"
    );
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    TEST_COMPARE("check hstatus.gva is set under INSTRUCTION_ACCESS_FAULT exception", 1, hstatus_gva);

    // clear changes
    csr_set_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN, 0);

    TEST_END();
}
