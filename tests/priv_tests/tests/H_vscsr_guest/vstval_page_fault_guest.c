
#include <test_utils.h>

static reg_t stval_tval = 0;

static void stval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
    CSRW(satp, 0UL);
}

bool __attribute__((weak)) vstval_page_fault_guest(){
    TEST_START();

    reg_t satp_value;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(stval_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    // setup test page table
    test_pagetable[0] = PTE_V |           PTE_AD | 0x00000000 >> 2;
    test_pagetable[1] = PTE_V |           PTE_AD | 0x40000000 >> 2;
    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    test_pagetable[3] = PTE_V |           PTE_AD | 0xC0000000 >> 2;
    asm volatile ("sfence.vma \n\t");
    
    // set satp register
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "lb x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check PAGE FAULT tval value", 0x7FFFFFFF, stval_tval);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    TEST_END();
}
