
#include <test_utils.h>

void __attribute__((weak)) mtvec_base_handler(){
    excpt.triggered = true;
}

bool __attribute__((weak)) mtvec_base(){
    TEST_START();

    const reg_t mode_direct = 0;
    const reg_t mode_vectored = 1;

    reg_t base_old, base_new, mode;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear delegation register
    set_mhandler(mtvec_base_handler);                                                                                                                                                                             

    // set trap mode to direct
    csr_set_field(mtvec, MTVEC_MODE_OFF, MTVEC_MODE_LEN, mode_direct);
    mode = csr_get_field(mtvec, MTVEC_MODE_OFF, MTVEC_MODE_LEN);
    TEST_COMPARE("set and check that mtvec mode is direct", mode_direct, mode);

    // call trap and check that it triggered
    excpt.triggered = false;
    excpt.for_testing = true;

    ecall(0,0);

    TEST_COMPARE("check that trap is triggered", true, excpt.triggered);

    // set new mtvec base and check that it changed
    base_old = csr_get_field(mtvec, MTVEC_BASE_OFF, MTVEC_BASE_LEN);

    asm volatile (
        "la t0, other_mhandler_entry \n\t"
        "csrw mtvec, t0 \n\t"
    );

    base_new = csr_get_field(mtvec, MTVEC_BASE_OFF, MTVEC_BASE_LEN);
    TEST_ASSERT("check that mtvec value is changed", base_old != base_new, "Error! New and old mtvec.base are same!");

    // call trap with new mtvec.base and check that it triggered
    excpt.triggered = false;
    excpt.for_testing = true;

    ecall(0,0);

    TEST_COMPARE("check that trap with new mtvec.base is triggered", true, excpt.triggered);

    // set mtvec.base back to old value
    asm volatile (
        "la t0, mhandler_entry \n\t"
        "csrw mtvec, t0 \n\t"
    );
    base_new = csr_get_field(mtvec, MTVEC_BASE_OFF, MTVEC_BASE_LEN);
    TEST_COMPARE("set mtvec.base back to old value", base_old, base_new);

    // call trap with restored mtvec.base and check that it triggered
    excpt.triggered = false;
    excpt.for_testing = true;

    ecall(0,0);

    TEST_COMPARE("check that trap with restored mtvec.base is triggered", true, excpt.triggered);


    TEST_END();
}
