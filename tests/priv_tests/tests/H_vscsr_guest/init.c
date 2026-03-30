
#include <test_utils.h>

bool __attribute__((weak)) init(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // delegate all exceptions and interrupts to S mode
    CSRW(medeleg, ~0L);
    CSRW(mideleg, ~0L);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // delegate all exceptions and interrupts to VS mode
    CSRW(hedeleg, ~0L);
    CSRW(hideleg, ~0L);

    // init FS and VS, so that in VS mode we can use float and vector instructions
    csr_set_field(sstatus, SSTATUS_FS_OFF, SSTATUS_FS_LEN, 0b01);
    csr_set_field(sstatus, SSTATUS_VS_OFF, SSTATUS_VS_LEN, 0b01);

    // always pending
    csr_set_field(hvip, HVIP_VSTIP_OFF, HVIP_VSTIP_LEN, 1);
    csr_set_field(hvip, HVIP_VSEIP_OFF, HVIP_VSEIP_LEN, 1);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    TEST_END();
}
