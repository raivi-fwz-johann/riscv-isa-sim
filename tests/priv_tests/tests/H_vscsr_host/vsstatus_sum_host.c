
#include <test_utils.h>

static reg_t sstatus_sum_cause = 32;

static void scause_shandler(){
    excpt.triggered = true;
    sstatus_sum_cause = CSRR(scause);
}

bool __attribute__((weak)) vsstatus_sum_host(){
    TEST_START();

    reg_t satp_value, temp, sum;
    reg_t fault_addr = 0xC0000000;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(scause_shandler);                                                                                                                                                                             


    // setup test page table
    test_pagetable[0] = PTE_V |           PTE_AD | 0x00000000 >> 2;
    test_pagetable[1] = PTE_V |           PTE_AD | 0x40000000 >> 2;
    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    test_pagetable[3] = PTE_V | PTE_RWX | PTE_U | PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.vvma \n\t");

    // set satp register
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(vsatp, satp_value);

    // check that when SUM is 0 load from Uset Page Table Entry cause trap
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(vsstatus, VSSTATUS_SUM_OFF, VSSTATUS_SUM_LEN, 0);
    sum = csr_get_field(vsstatus, VSSTATUS_SUM_OFF, VSSTATUS_SUM_LEN);
    TEST_COMPARE("check vsstatus.sum is 0", 0, sum);

    set_virtial_mode_host(ON);
    temp = *((reg_t*)fault_addr);
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, sstatus_sum_cause);

    // check that when SUM is 1 load from Uset Page Table Entry not cause trap
    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(vsstatus, VSSTATUS_SUM_OFF, VSSTATUS_SUM_LEN, 1);
    sum = csr_get_field(vsstatus, VSSTATUS_SUM_OFF, VSSTATUS_SUM_LEN);
    TEST_COMPARE("check vsstatus.sum is 1", 1, sum);

    set_virtial_mode_host(ON);
    temp = *((reg_t*)fault_addr);
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    // clear state
    CSRW(vsatp, 0UL);
    
    csr_set_field(vsstatus, VSSTATUS_SUM_OFF, VSSTATUS_SUM_LEN, 0);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    TEST_END();
}
