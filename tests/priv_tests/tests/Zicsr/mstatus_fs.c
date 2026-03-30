
#include <test_utils.h>

static reg_t mstatus_fs_cause = 0;

void __attribute__((weak)) mstatus_fs_handler(){
    mstatus_fs_cause = CSRR(mcause);
    excpt.triggered = true;
}

bool __attribute__((weak)) mstatus_fs(){
    TEST_START();

    const reg_t fs_off = 0b00;
    const reg_t fs_initial = 0b01;
    const reg_t fs_clean = 0b10;
    const reg_t fs_dirty = 0b11;

    reg_t fs;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // clear delegation register
    CSRW(medeleg, 0);
    set_mhandler(mstatus_fs_handler);                                                                                                                                                                             


    // check fs == OFF cause illigal instruction
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN, fs_off);
    fs = csr_get_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN);
    TEST_COMPARE("set and check that mstatus.fs is in OFF state", fs_off, fs);

    asm volatile ("fmv.w.x f0, x0 \n\t");

    TEST_COMPARE("check that exception is triggered", true, excpt.triggered);
    TEST_COMPARE("check that mcause is illigal instruction", CAUSE_ILLEGAL_INSTRUCTION, mstatus_fs_cause);
    
    excpt.triggered = false;
    excpt.for_testing = false;

    // set fs to Initial State
    csr_set_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN, fs_initial);
    fs = csr_get_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN);
    TEST_COMPARE("set and check that mstatus.fs is in INITIAL state", fs_initial, fs);

    // perform FP operaion and check that state is Dirty
    asm volatile ("fmv.w.x f0, x0 \n\t");

    TEST_COMPARE("check that exception is not triggered", false, excpt.triggered);

    fs = csr_get_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN);
    TEST_COMPARE("check that mstatus.fs is in DIRTY state", fs_dirty, fs);

    // clear state and perform FP operation again
    csr_set_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN, fs_clean);
    fs = csr_get_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN);
    TEST_COMPARE("set and check that mstatus.fs is in CLEAN state", fs_clean, fs);

    asm volatile ("fmv.w.x f0, x0 \n\t");

    TEST_COMPARE("check that exception is not triggered", false, excpt.triggered);

    fs = csr_get_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN);
    TEST_COMPARE("check that mstatus.fs is in DIRTY state", fs_dirty, fs);

    // set state back to off
    csr_set_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN, fs_off);
    fs = csr_get_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN);
    TEST_COMPARE("set and check that mstatus.fs is in OFF state", fs_off, fs);

    TEST_END();
}
