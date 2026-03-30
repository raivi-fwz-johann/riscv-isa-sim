
#include <test_utils.h>


bool __attribute__((weak)) sstvecd(){
    TEST_START();

    const reg_t mode_direct = 0;
    const reg_t mode_vectored = 1;

    reg_t mode, base, old_stvec;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // store old stvec value
    old_stvec = CSRR(stvec);

    // try to set stvec to direct mode
    csr_set_field(stvec, STVEC_MODE_OFF, STVEC_MODE_LEN, mode_direct);
    mode = csr_get_field(stvec, STVEC_MODE_OFF, STVEC_MODE_LEN);
    TEST_COMPARE("set and check that stvec mode is direct", mode_direct, mode);

    // try to set all base bits to one
    csr_set_field(stvec, STVEC_BASE_OFF, STVEC_BASE_LEN, -1L);
    base = csr_get_field(stvec, STVEC_BASE_OFF, STVEC_BASE_LEN);
    TEST_COMPARE("set base to all ones and check that all bits are writable", (reg_t)(-1L) >> 2, base);

    // restore old stvec value
    CSRW(stvec, old_stvec);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    TEST_END();
}
