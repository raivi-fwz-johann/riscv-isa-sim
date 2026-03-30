
#include <test_utils.h>

void __attribute__((weak)) vstvec_base_handler(){
    excpt.triggered = true;
}

bool __attribute__((weak)) vstvec_base_host(){
    TEST_START();

    const reg_t mode_direct = 0;
    const reg_t mode_vectored = 1;

    reg_t base_old, base_new, mode, hedeleg_reg;

    set_vshandler(vstvec_base_handler);                                                                                                                                                                             

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    CSRW(hedeleg, 1 << CAUSE_ILLEGAL_INSTRUCTION);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 1. Delegation is ON", 1 << CAUSE_ILLEGAL_INSTRUCTION, hedeleg_reg);
    
    // set trap mode to direct
    csr_set_field(vstvec, VSTVEC_MODE_OFF, VSTVEC_MODE_LEN, mode_direct);
    mode = csr_get_field(vstvec, VSTVEC_MODE_OFF, VSTVEC_MODE_LEN);
    TEST_COMPARE("set and check that vstvec mode is direct", mode_direct, mode);

    // call trap and check that it triggered
    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_host(ON);
    asm volatile ("unimp \n\t");
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that trap is triggered", true, excpt.triggered);

    // set new stvec base and check that it changed
    base_old = csr_get_field(vstvec, VSTVEC_BASE_OFF, VSTVEC_BASE_LEN);

    asm volatile (
        "la t0, other_vshandler_entry \n\t"
        "csrw vstvec, t0 \n\t"
    );

    base_new = csr_get_field(vstvec, VSTVEC_BASE_OFF, VSTVEC_BASE_LEN);
    TEST_ASSERT("check that vstvec value is changed", base_old != base_new, "Error! New and old vstvec.base are same!");

    // call trap with new vstvec.base and check that it triggered
    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_host(ON);
    asm volatile ("unimp \n\t");
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that trap with new vstvec.base is triggered", true, excpt.triggered);

    // set vstvec.base back to old value
    asm volatile (
        "la t0, vshandler_entry \n\t"
        "csrw vstvec, t0 \n\t"
    );
    base_new = csr_get_field(vstvec, VSTVEC_BASE_OFF, VSTVEC_BASE_LEN);
    TEST_COMPARE("set vstvec.base back to old value", base_old, base_new);

    // call trap with restored vstvec.base and check that it triggered
    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_host(ON);
    asm volatile ("unimp \n\t");
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that trap with restored vstvec.base is triggered", true, excpt.triggered);


    TEST_END();
}
