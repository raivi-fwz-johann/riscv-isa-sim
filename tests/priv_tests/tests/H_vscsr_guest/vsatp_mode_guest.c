
#include <test_utils.h>

static reg_t satp_mode_cause = 32;

static void satp_mode_shandler(){
    excpt.triggered = true;
    satp_mode_cause = CSRR(scause);
}

bool __attribute__((weak)) vsatp_mode_guest(){
    TEST_START();

    reg_t satp_value, temp, satp_mode;
    reg_t none_valid_addr = ~(0xF); // all ones, but less for bits are zero 

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(satp_mode_shandler);                                                                                                                                                                             

    // check that when MODE is BARE, load from page with no RWX trigger ACCESS FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;

    satp_value = 0;
    satp_value |= SATP_BARE<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    satp_mode = csr_get_field(satp, SATP_MODE_OFF, SATP_MODE_LEN);
    TEST_COMPARE("check satp.mode is BARE", SATP_BARE, satp_mode);
    
    temp = *((reg_t*)none_valid_addr);

    TEST_COMPARE("check that when mode is BARE interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_ACCESS", CAUSE_LOAD_ACCESS, satp_mode_cause);

    // check that when MODE is SV39, load from page with no RWX trigger PAGE FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;

    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    asm volatile ("sfence.vma \n\t");

    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    satp_mode = csr_get_field(satp, SATP_MODE_OFF, SATP_MODE_LEN);
    TEST_COMPARE("check satp.mode is SV39", SATP_SV39, satp_mode);
    
    temp = *((reg_t*)none_valid_addr);

    TEST_COMPARE("check that when mode is SV39 interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, satp_mode_cause);

    CSRW(satp, 0);
    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    // check that when MODE is SV48, load from page with no RWX trigger PAGE FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;

    test_pagetable[0] = PTE_V | PTE_RWX | PTE_AD | 0 >> 2;
    asm volatile ("sfence.vma \n\t");
    
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV48<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    satp_mode = csr_get_field(satp, SATP_MODE_OFF, SATP_MODE_LEN);
    TEST_COMPARE("check satp.mode is SV48", SATP_SV48, satp_mode);
    
    temp = *((reg_t*)none_valid_addr);

    TEST_COMPARE("check that when mode is SV48 interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, satp_mode_cause);

    CSRW(satp, 0);
    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    // check that when MODE is SV57, load from page with no RWX trigger PAGE FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;

    test_pagetable[0] = PTE_V | PTE_RWX | PTE_AD | 0 >> 2;
    asm volatile ("sfence.vma \n\t");
    
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV57<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    satp_mode = csr_get_field(satp, SATP_MODE_OFF, SATP_MODE_LEN);
    TEST_COMPARE("check satp.mode is SV57", SATP_SV57, satp_mode);
    
    temp = *((reg_t*)none_valid_addr);

    TEST_COMPARE("check that when mode is SV57 interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, satp_mode_cause);

    CSRW(satp, 0);
    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    TEST_END();
}
