
#include <test_utils.h>

static reg_t mstatus_gva = 0;

extern reg_t mstatus_gva_access_fault_handler_return_addr;

static void mstatus_gva_mhandler(){
    excpt.triggered = true;
    mstatus_gva = csr_get_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN);
    reg_t reg = CSRR(mstatus);

    CSRW(mepc, (reg_t)(&mstatus_gva_access_fault_handler_return_addr));
}

bool __attribute__((weak)) mstatus_gva_instruction_access_fault(){
    TEST_START();

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mstatus_gva_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN, 0L);
    reg_t reg = csr_get_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN);
    TEST_COMPARE("check mstatus.gva is clear", 0, mstatus_gva);

    switch_mode_and_vmode(MODE_S, ON);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    // access to 0x7FFFFFFF is restricted by pmp in boot.S
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "jr t0 \n\t"

        ".globl mstatus_gva_access_fault_handler_return_addr\n\t"
        "mstatus_gva_access_fault_handler_return_addr: \n\t"
        "nop \n\t"
    );
    
    switch_mode_and_vmode(MODE_M, OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check mstatus.gva is set under INSTRUCTION_ACCESS_FAULT exception", 1, mstatus_gva);
    
    // clear changes
    csr_set_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN, 0L);

    TEST_END();
}
