
#include <test_utils.h>

static reg_t sstatus_mxr_cause = 32;

static void scause_shandler(){
    excpt.triggered = true;
    sstatus_mxr_cause = CSRR(scause);
}

bool __attribute__((weak)) sstatus_mxr(){
    TEST_START();

    reg_t satp_value, temp, mxr;
    reg_t execute_only_addr = 0xC0000000;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(scause_shandler);                                                                                                                                                                             

    // setup test page table
    test_pagetable[0] = PTE_V |           PTE_AD | 0x00000000 >> 2;
    test_pagetable[1] = PTE_V |           PTE_AD | 0x40000000 >> 2;
    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    test_pagetable[3] = PTE_V | PTE_X   | PTE_AD | 0xC0000000 >> 2;
    asm volatile ("sfence.vma \n\t");

    // set satp register
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    // check that when MXR is 0 load from Execute Page Table Entry cause trap
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_MXR_OFF, SSTATUS_MXR_LEN, 0);
    mxr = csr_get_field(sstatus, SSTATUS_MXR_OFF, SSTATUS_MXR_LEN);
    TEST_COMPARE("check sstatus.mxr is 0", 0, mxr);

    temp = *((reg_t*)execute_only_addr);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, sstatus_mxr_cause);

    // check that when MXR is 1 load from Execute Page Table Entry not cause trap
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(sstatus, SSTATUS_MXR_OFF, SSTATUS_MXR_LEN, 1);
    mxr = csr_get_field(sstatus, SSTATUS_MXR_OFF, SSTATUS_MXR_LEN);
    TEST_COMPARE("check sstatus.mxr is 1", 1, mxr);

    temp = *((reg_t*)execute_only_addr);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    // clear state
    CSRW(satp, 0UL);
    
    csr_set_field(sstatus, SSTATUS_MXR_OFF, SSTATUS_MXR_LEN, 0);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    TEST_END();
}
