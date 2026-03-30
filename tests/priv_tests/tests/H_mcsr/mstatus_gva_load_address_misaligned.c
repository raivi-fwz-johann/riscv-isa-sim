
#include <test_utils.h>

static reg_t mstatus_gva = 0;

static void mstatus_gva_mhandler(){
    excpt.triggered = true;
    mstatus_gva = csr_get_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN);
    reg_t reg = CSRR(mstatus);
}

bool __attribute__((weak)) mstatus_gva_load_address_misaligned(){
    TEST_START();

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mstatus_gva_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN, 0L);
    reg_t reg = csr_get_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN);
    TEST_COMPARE("check mstatus.gva is clear", 0, mstatus_gva);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_virtial_mode_machine(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    asm volatile (
        ".balign 4 \n\t"
        "mcause_misaligned_addr: \n\t"
        "la t0, mcause_misaligned_addr \n\t"
        "lw x0, 1(t0) \n\t"
    );
    
    set_virtial_mode_machine(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check mstatus.gva is set under MISALIGNED_LOAD exception", 1, mstatus_gva);
    
    // clear changes
    csr_set_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN, 0L);

    TEST_END();
}
