
#include <test_utils.h>

static reg_t mstatus_sum_cause = 32;

static void mcause_mhandler(){
    excpt.triggered = true;
    mstatus_sum_cause = CSRR(mcause);
}

bool __attribute__((weak)) mstatus_sum(){
    TEST_START();

    reg_t satp_value, temp, sum;
    reg_t fault_addr = 0xC0000000;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mcause_mhandler);                                                                                                                                                                             


    // setup test page table
    test_pagetable[0] = PTE_V |           PTE_AD | 0x00000000 >> 2;
    test_pagetable[1] = PTE_V |           PTE_AD | 0x40000000 >> 2;
    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    test_pagetable[3] = PTE_V | PTE_RWX | PTE_U | PTE_AD | 0xC0000000 >> 2;
    asm volatile ("sfence.vma \n\t");

    // set satp register
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    // check that when SUM is 0 load from Uset Page Table Entry cause trap
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_SUM_OFF, MSTATUS_SUM_LEN, 0);
    sum = csr_get_field(mstatus, MSTATUS_SUM_OFF, MSTATUS_SUM_LEN);
    TEST_COMPARE("check mstatus.sum is 0", 0, sum);

    switch_mode(MODE_S);
    temp = *((reg_t*)fault_addr);
    switch_mode(MODE_M);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, mstatus_sum_cause);

    // check that when SUM is 1 load from Uset Page Table Entry not cause trap
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_SUM_OFF, MSTATUS_SUM_LEN, 1);
    sum = csr_get_field(mstatus, MSTATUS_SUM_OFF, MSTATUS_SUM_LEN);
    TEST_COMPARE("check mstatus.sum is 1", 1, sum);

    switch_mode(MODE_S);
    temp = *((reg_t*)fault_addr);
    switch_mode(MODE_M);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    // clear state
    CSRW(satp, 0UL);
    
    csr_set_field(mstatus, MSTATUS_SUM_OFF, MSTATUS_SUM_LEN, 0);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    TEST_END();
}
