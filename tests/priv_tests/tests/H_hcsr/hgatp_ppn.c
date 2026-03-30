
#include <test_utils.h>

static reg_t hgatp_ppn_cause = 32;

static pte_t guest_test_pagetable[TEST_PAGETABLE_SIZE] __attribute__((section(".bss2"),aligned(PAGE_SIZE*4)));
static pte_t other_guest_test_pagetable[TEST_PAGETABLE_SIZE] __attribute__((section(".bss2"),aligned(PAGE_SIZE*4)));

static void hgatp_ppn_shandler(){
    excpt.triggered = true;
    hgatp_ppn_cause = CSRR(scause);
}

bool __attribute__((weak)) hgatp_ppn(){
    TEST_START();

    reg_t hgatp_value, temp, hgatp_ppn, hgatp_ppn_gold;
    reg_t test_addr = 0xC0000000;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        guest_test_pagetable[i] = 0UL;
        other_guest_test_pagetable[i] = 0UL;
    }

    set_shandler(hgatp_ppn_shandler);                                                                                                                                                                             

    // config to page table, one with RWX and other is not
    guest_test_pagetable[2] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    guest_test_pagetable[3] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0xC0000000 >> 2;

    other_guest_test_pagetable[2] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    other_guest_test_pagetable[3] = PTE_V | PTE_U |           PTE_AD | 0xC0000000 >> 2;

    asm volatile ("hfence.gvma \n\t");


    // check that when MODE is SV39, config ppn so that it not trigger PAGE FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;

    hgatp_ppn_gold = get_ppn( (reg_t)(guest_test_pagetable) );
    hgatp_value = hgatp_ppn_gold | SATP_SV39<< SATP_MODE_OFF;
    CSRW(hgatp, hgatp_value);

    hgatp_ppn = csr_get_field(hgatp, SATP_PPN_OFF, SATP_PPN_LEN);
    TEST_COMPARE("check hgatp.ppn is set", hgatp_ppn_gold, hgatp_ppn);
    
    set_virtial_mode_host(ON);
    temp = *((reg_t*)test_addr);
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    CSRW(hgatp, 0);

    // check that when MODE is SV39, config ppn so that it trigger PAGE FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;
    asm volatile ("hfence.gvma \n\t");

    hgatp_ppn_gold = get_ppn( (reg_t)(other_guest_test_pagetable) );
    hgatp_value = hgatp_ppn_gold | SATP_SV39<< SATP_MODE_OFF;
    CSRW(hgatp, hgatp_value);

    hgatp_ppn = csr_get_field(hgatp, SATP_PPN_OFF, SATP_PPN_LEN);
    TEST_COMPARE("check hgatp.ppn is set", hgatp_ppn_gold, hgatp_ppn);
    
    set_virtial_mode_host(ON);
    temp = *((reg_t*)test_addr);
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_GUEST_PAGE_FAULT", CAUSE_LOAD_GUEST_PAGE_FAULT, hgatp_ppn_cause);

    CSRW(hgatp, 0);

    // clear tables
    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        guest_test_pagetable[i] = 0UL;
    }

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        other_guest_test_pagetable[i] = 0UL;
    }
    TEST_END();
}
