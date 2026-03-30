
#include <test_utils.h>

static reg_t mtval_tval = 0;

static void mtval_mhandler(){
    excpt.triggered = true;
    mtval_tval = CSRR(mtval);
    CSRW(satp, 0UL);
}

bool __attribute__((weak)) mtval_page_fault(){
    TEST_START();

    reg_t satp_value;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mtval_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    // setup test page table
    test_pagetable[0] = PTE_V |           PTE_AD | 0x00000000 >> 2;
    test_pagetable[1] = PTE_V |           PTE_AD | 0x40000000 >> 2;
    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    test_pagetable[3] = PTE_V |           PTE_AD | 0xC0000000 >> 2;
    asm volatile ("sfence.vma \n\t");

    switch_mode(MODE_S);
    TEST_COMPARE("switch to S mode and check that currunt mode is S", MODE_S, current_mode);  
    
    // set satp register
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "lb x0, 0(t0) \n\t"
    );

    switch_mode(MODE_M);
    TEST_COMPARE("switch to M mode and check that currunt mode is M", MODE_M, current_mode);  

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check PAGE FAULT tval value", 0x7FFFFFFF, mtval_tval);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    TEST_END();
}
