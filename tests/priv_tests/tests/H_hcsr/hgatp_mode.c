
#include <test_utils.h>

static reg_t hgatp_mode_cause = 32;

static pte_t guest_test_pagetable[4] __attribute__((aligned(PAGE_SIZE*4)));

static void hgatp_mode_shandler(){
    excpt.triggered = true;
    hgatp_mode_cause = CSRR(scause);
}

bool __attribute__((weak)) hgatp_mode(){
    TEST_START();

    reg_t hgatp_value, temp, hgatp_mode;
    reg_t none_valid_addr = ~(0xF); // all ones, but less for bits are zero 

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(hgatp_mode_shandler);                                                                                                                                                                             

    // check that when MODE is BARE, load from page with no RWX trigger ACCESS FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;

    hgatp_value = 0;
    hgatp_value |= SATP_BARE<< SATP_MODE_OFF;
    CSRW(hgatp, hgatp_value);

    hgatp_mode = csr_get_field(hgatp, SATP_MODE_OFF, SATP_MODE_LEN);
    TEST_COMPARE("check hgatp.mode is BARE", SATP_BARE, hgatp_mode);
    
    set_virtial_mode_host(ON);
    temp = *((reg_t*)none_valid_addr);
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that when mode is BARE interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_ACCESS", CAUSE_LOAD_ACCESS, hgatp_mode_cause);

    // check that when MODE is SV39, load from page with no RWX trigger PAGE FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;

    guest_test_pagetable[2] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    asm volatile ("hfence.gvma \n\t");

    hgatp_value = get_ppn( (reg_t)(guest_test_pagetable) );
    hgatp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(hgatp, hgatp_value);

    hgatp_mode = csr_get_field(hgatp, SATP_MODE_OFF, SATP_MODE_LEN);
    TEST_COMPARE("check hgatp.mode is SV39", SATP_SV39, hgatp_mode);
    
    set_virtial_mode_host(ON);
    temp = *((reg_t*)none_valid_addr);
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that when mode is SV39 interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_GUEST_PAGE_FAULT", CAUSE_LOAD_GUEST_PAGE_FAULT, hgatp_mode_cause);

    CSRW(hgatp, 0);
    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        guest_test_pagetable[i] = 0UL;
    }

    // check that when MODE is SV48, load from page with no RWX trigger PAGE FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;

    guest_test_pagetable[0] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0 >> 2;
    asm volatile ("hfence.gvma \n\t");
    
    hgatp_value = get_ppn( (reg_t)(guest_test_pagetable) );
    hgatp_value |= SATP_SV48<< SATP_MODE_OFF;
    CSRW(hgatp, hgatp_value);

    hgatp_mode = csr_get_field(hgatp, SATP_MODE_OFF, SATP_MODE_LEN);
    TEST_COMPARE("check hgatp.mode is SV48", SATP_SV48, hgatp_mode);
    
    set_virtial_mode_host(ON);
    temp = *((reg_t*)none_valid_addr);
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that when mode is SV48 interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_GUEST_PAGE_FAULT", CAUSE_LOAD_GUEST_PAGE_FAULT, hgatp_mode_cause);

    CSRW(hgatp, 0);
    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        guest_test_pagetable[i] = 0UL;
    }

    TEST_END();
}
