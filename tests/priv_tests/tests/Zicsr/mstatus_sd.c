
#include <test_utils.h>


bool __attribute__((weak)) mstatus_sd(){
    TEST_START();

    const reg_t state_off = 0b00;
    const reg_t state_initial = 0b01;
    const reg_t state_dirty = 0b11;

    reg_t sd, fs, vs;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // check that sd is set when FS is dirty
    sd = csr_get_field(mstatus, MSTATUS_SD_OFF, MSTATUS_SD_LEN);
    TEST_COMPARE("check that mstatus.sd is clear", 0, sd);

    csr_set_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN, state_initial);
    fs = csr_get_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN);
    TEST_COMPARE("set and check that mstatus.fs is in INITIAL state", state_initial, fs);

    asm volatile ("fmv.w.x f0, x0 \n\t");

    fs = csr_get_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN);
    TEST_COMPARE("check that mstatus.fs is in DIRTY state", state_dirty, fs);

    sd = csr_get_field(mstatus, MSTATUS_SD_OFF, MSTATUS_SD_LEN);
    TEST_COMPARE("check that mstatus.sd is set", 1, sd);
    
    csr_set_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN, state_off);
    fs = csr_get_field(mstatus, MSTATUS_FS_OFF, MSTATUS_FS_LEN);
    TEST_COMPARE("set and check that mstatus.fs is in OFF state", state_off, fs);

    sd = csr_get_field(mstatus, MSTATUS_SD_OFF, MSTATUS_SD_LEN);
    TEST_COMPARE("check that mstatus.sd is clear", 0, sd);

    // check that sd is set when VS is dirty
    sd = csr_get_field(mstatus, MSTATUS_SD_OFF, MSTATUS_SD_LEN);
    TEST_COMPARE("check that mstatus.sd is clear", 0, sd);

    csr_set_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN, state_initial);
    vs = csr_get_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN);
    TEST_COMPARE("set and check that mstatus.vs is in INITIAL state", state_initial, vs);

    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");
    asm volatile ("vmv.v.x v0, x0 \n\t");

    vs = csr_get_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN);
    TEST_COMPARE("check that mstatus.vs is in DIRTY state", state_dirty, vs);

    sd = csr_get_field(mstatus, MSTATUS_SD_OFF, MSTATUS_SD_LEN);
    TEST_COMPARE("check that mstatus.sd is set", 1, sd);
    
    csr_set_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN, state_off);
    vs = csr_get_field(mstatus, MSTATUS_VS_OFF, MSTATUS_VS_LEN);
    TEST_COMPARE("set and check that mstatus.vs is in OFF state", state_off, vs);

    sd = csr_get_field(mstatus, MSTATUS_SD_OFF, MSTATUS_SD_LEN);
    TEST_COMPARE("check that mstatus.sd is clear", 0, sd);


    TEST_END();
}
