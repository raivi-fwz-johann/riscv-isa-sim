
#include <test_utils.h>

void __attribute__((weak)) stvec_base_handler(){
    excpt.triggered = true;
}

bool __attribute__((weak)) stvec_base(){
    TEST_START();

    const reg_t mode_direct = 0;
    const reg_t mode_vectored = 1;

    reg_t base_old, base_new, mode;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // clear delegation register
    set_shandler(stvec_base_handler);                                                                                                                                                                             

    // set trap mode to direct
    csr_set_field(stvec, STVEC_MODE_OFF, STVEC_MODE_LEN, mode_direct);
    mode = csr_get_field(stvec, STVEC_MODE_OFF, STVEC_MODE_LEN);
    TEST_COMPARE("set and check that stvec mode is direct", mode_direct, mode);

    // call trap and check that it triggered
    excpt.triggered = false;
    excpt.for_testing = true;

    ecall(0,0);

    TEST_COMPARE("check that trap is triggered", true, excpt.triggered);

    // set new stvec base and check that it changed
    base_old = csr_get_field(stvec, STVEC_BASE_OFF, STVEC_BASE_LEN);

    asm volatile (
        "la t0, other_shandler_entry \n\t"
        "csrw stvec, t0 \n\t"
    );

    base_new = csr_get_field(stvec, STVEC_BASE_OFF, STVEC_BASE_LEN);
    TEST_ASSERT("check that stvec value is changed", base_old != base_new, "Error! New and old stvec.base are same!");

    // call trap with new stvec.base and check that it triggered
    excpt.triggered = false;
    excpt.for_testing = true;

    ecall(0,0);

    TEST_COMPARE("check that trap with new stvec.base is triggered", true, excpt.triggered);

    // set stvec.base back to old value
    asm volatile (
        "la t0, shandler_entry \n\t"
        "csrw stvec, t0 \n\t"
    );
    base_new = csr_get_field(stvec, STVEC_BASE_OFF, STVEC_BASE_LEN);
    TEST_COMPARE("set stvec.base back to old value", base_old, base_new);

    // call trap with restored stvec.base and check that it triggered
    excpt.triggered = false;
    excpt.for_testing = true;

    ecall(0,0);

    TEST_COMPARE("check that trap with restored stvec.base is triggered", true, excpt.triggered);


    TEST_END();
}
