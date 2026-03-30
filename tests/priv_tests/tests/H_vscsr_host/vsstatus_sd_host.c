
#include <test_utils.h>


bool __attribute__((weak)) vsstatus_sd_host(){
    TEST_START();

    const reg_t state_off = 0b00;
    const reg_t state_initial = 0b01;
    const reg_t state_dirty = 0b11;

    reg_t sd, fs, vs;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // check that sd is set when FS is dirty
    sd = csr_get_field(vsstatus, VSSTATUS_SD_OFF, VSSTATUS_SD_LEN);
    TEST_COMPARE("check that vsstatus.sd is clear", 0, sd);

    csr_set_field(sstatus, SSTATUS_FS_OFF, SSTATUS_FS_LEN, state_initial);
    fs = csr_get_field(sstatus, SSTATUS_FS_OFF, SSTATUS_FS_LEN);
    TEST_COMPARE("set and check that sstatus.fs is in INITIAL state", state_initial, fs);

    csr_set_field(vsstatus, VSSTATUS_FS_OFF, VSSTATUS_FS_LEN, state_initial);
    fs = csr_get_field(vsstatus, VSSTATUS_FS_OFF, VSSTATUS_FS_LEN);
    TEST_COMPARE("set and check that vsstatus.fs is in INITIAL state", state_initial, fs);

    set_virtial_mode_host(ON);
    asm volatile ("fmv.w.x f0, x0 \n\t");
    set_virtial_mode_host(OFF);

    fs = csr_get_field(vsstatus, VSSTATUS_FS_OFF, VSSTATUS_FS_LEN);
    TEST_COMPARE("check that vsstatus.fs is in DIRTY state", state_dirty, fs);

    sd = csr_get_field(vsstatus, VSSTATUS_SD_OFF, VSSTATUS_SD_LEN);
    TEST_COMPARE("check that vsstatus.sd is set", 1, sd);
    
    csr_set_field(vsstatus, VSSTATUS_FS_OFF, VSSTATUS_FS_LEN, state_off);
    fs = csr_get_field(vsstatus, VSSTATUS_FS_OFF, VSSTATUS_FS_LEN);
    TEST_COMPARE("set and check that vsstatus.fs is in OFF state", state_off, fs);

    sd = csr_get_field(vsstatus, VSSTATUS_SD_OFF, VSSTATUS_SD_LEN);
    TEST_COMPARE("check that vsstatus.sd is clear", 0, sd);

    csr_set_field(sstatus, SSTATUS_FS_OFF, SSTATUS_FS_LEN, state_off);
    fs = csr_get_field(sstatus, SSTATUS_FS_OFF, SSTATUS_FS_LEN);
    TEST_COMPARE("set and check that sstatus.fs is in OFF state", state_off, fs);


    // check that sd is set when VS is dirty
    sd = csr_get_field(vsstatus, VSSTATUS_SD_OFF, VSSTATUS_SD_LEN);
    TEST_COMPARE("check that vsstatus.sd is clear", 0, sd);

    csr_set_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN, state_initial);
    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("set and check that sstatus.vs is in INITIAL state", state_initial, vs);

    csr_set_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN, state_initial);
    vs = csr_get_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN);
    TEST_COMPARE("set and check that vsstatus.vs is in INITIAL state", state_initial, vs);

    set_virtial_mode_host(ON);
    asm volatile ("vsetvli x0, x0, e8,m8,tu,mu \n\t");
    asm volatile ("vmv.v.x v0, x0 \n\t");
    set_virtial_mode_host(OFF);

    vs = csr_get_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN);
    TEST_COMPARE("check that vsstatus.vs is in DIRTY state", state_dirty, vs);

    sd = csr_get_field(vsstatus, VSSTATUS_SD_OFF, VSSTATUS_SD_LEN);
    TEST_COMPARE("check that vsstatus.sd is set", 1, sd);
    
    csr_set_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN, state_off);
    vs = csr_get_field(vsstatus, VSSTATUS_VS_OFF, VSSTATUS_VS_LEN);
    TEST_COMPARE("set and check that vsstatus.vs is in OFF state", state_off, vs);

    sd = csr_get_field(vsstatus, VSSTATUS_SD_OFF, VSSTATUS_SD_LEN);
    TEST_COMPARE("check that vsstatus.sd is clear", 0, sd);

    csr_set_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN, state_off);
    vs = csr_get_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN);
    TEST_COMPARE("set and check that sstatus.vs is in OFF state", state_off, vs);

    TEST_END();
}
