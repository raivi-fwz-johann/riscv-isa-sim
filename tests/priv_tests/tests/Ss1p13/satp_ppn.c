
#include <test_utils.h>

static reg_t satp_ppn_cause = 32;

static pte_t other_test_pagetable[TEST_PAGETABLE_SIZE] __attribute__((section(".bss2"),aligned(PAGE_SIZE)));

static void satp_ppn_shandler(){
    excpt.triggered = true;
    satp_ppn_cause = CSRR(scause);
}

bool __attribute__((weak)) satp_ppn(){
    TEST_START();

    reg_t satp_value, temp, satp_ppn, satp_ppn_gold;
    reg_t test_addr = 0xC0000000;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        other_test_pagetable[i] = 0UL;
    }

    set_shandler(satp_ppn_shandler);                                                                                                                                                                             

    // config to page table, one with RWX and other is not
    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    test_pagetable[3] = PTE_V | PTE_RWX | PTE_AD | 0xC0000000 >> 2;

    other_test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    other_test_pagetable[3] = PTE_V |           PTE_AD | 0xC0000000 >> 2;

    // check that when MODE is SV39, config ppn so that it not trigger PAGE FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;
    asm volatile ("sfence.vma \n\t");

    satp_ppn_gold = get_ppn( (reg_t)(test_pagetable) );
    satp_value = satp_ppn_gold | SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    satp_ppn = csr_get_field(satp, SATP_PPN_OFF, SATP_PPN_LEN);
    TEST_COMPARE("check satp.ppn is set", satp_ppn_gold, satp_ppn);
    
    temp = *((reg_t*)test_addr);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    CSRW(satp, 0);

    // check that when MODE is SV39, config ppn so that it trigger PAGE FAULT exception
    excpt.triggered = false;
    excpt.for_testing = true;
    asm volatile ("sfence.vma \n\t");

    satp_ppn_gold = get_ppn( (reg_t)(other_test_pagetable) );
    satp_value = satp_ppn_gold | SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    satp_ppn = csr_get_field(satp, SATP_PPN_OFF, SATP_PPN_LEN);
    TEST_COMPARE("check satp.ppn is set", satp_ppn_gold, satp_ppn);
    
    temp = *((reg_t*)test_addr);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, satp_ppn_cause);

    CSRW(satp, 0);

    // clear tables
    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        other_test_pagetable[i] = 0UL;
    }
    TEST_END();
}
