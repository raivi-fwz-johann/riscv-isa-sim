
#include <test_utils.h>

static reg_t hstatus_hu_cause = 0;

void __attribute__((weak)) hstatus_hu_handler(){
    excpt.triggered = true;
    hstatus_hu_cause = CSRR(scause);
}

bool __attribute__((weak)) hstatus_hu(){
    TEST_START();

    reg_t hstatus_hu_reg;

    set_shandler(hstatus_hu_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   


    // check that handler not triggered in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        ".balign 4 \n\t"
        "hstatus_hu_load_addr: \n\t"
        "la t0, hstatus_hu_load_addr\n\t"
        "hlv.w x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that handler is not triggered", false, excpt.triggered);

    
    // check that handler triggered in U mode when HU is clear
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(hstatus, HSTATUS_HU_OFF, HSTATUS_HU_LEN, 0);
    hstatus_hu_reg = csr_get_field(hstatus, HSTATUS_HU_OFF, HSTATUS_HU_LEN);
    TEST_COMPARE("check hstatus.hu is clear", 0, hstatus_hu_reg);

    switch_mode_supervisor(MODE_U);
    TEST_COMPARE("check that currunt mode is U", MODE_U, current_mode);                                                   

    asm volatile (
        "la t0, hstatus_hu_load_addr\n\t"
        "hlv.w x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that handler is triggered", true, excpt.triggered);

    switch_mode_supervisor(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    
    // check that handler not triggered in U mode when HU is set
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(hstatus, HSTATUS_HU_OFF, HSTATUS_HU_LEN, 1);
    hstatus_hu_reg = csr_get_field(hstatus, HSTATUS_HU_OFF, HSTATUS_HU_LEN);
    TEST_COMPARE("check hstatus.hu is set", 1, hstatus_hu_reg);

    switch_mode_supervisor(MODE_U);
    TEST_COMPARE("check that currunt mode is U", MODE_U, current_mode);                                                   

    asm volatile (
        "la t0, hstatus_hu_load_addr\n\t"
        "hlv.w x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that handler is not triggered", false, excpt.triggered);

    switch_mode_supervisor(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // clear test
    csr_set_field(hstatus, HSTATUS_HU_OFF, HSTATUS_HU_LEN, 0);
    hstatus_hu_reg = csr_get_field(hstatus, HSTATUS_HU_OFF, HSTATUS_HU_LEN);
    TEST_COMPARE("check hstatus.hu is clear", 0, hstatus_hu_reg);

    TEST_END();
}
