
#include <test_utils.h>

extern reg_t medeleg_page_fault_handler_return_addr_1;
extern reg_t medeleg_page_fault_handler_return_addr_2;

static reg_t medeleg_mode = 0;
static reg_t medeleg_cause = 32;

static void medeleg_mhandler(){
    excpt.triggered = true;
    medeleg_mode = MODE_M;
    medeleg_cause = CSRR(mcause);

    CSRW(satp, 0LL);
    CSRW(mepc, (reg_t)(&medeleg_page_fault_handler_return_addr_1));
}

static void medeleg_shandler(){
    excpt.triggered = true;
    medeleg_mode = MODE_S;
    medeleg_cause = CSRR(scause);

    CSRW(satp, 0LL);
    CSRW(sepc, (reg_t)(&medeleg_page_fault_handler_return_addr_2));
}

bool __attribute__((weak)) medeleg_instruction_page_fault(){
    TEST_START();

    reg_t satp_value;
    reg_t medeleg_reg;
    reg_t temp;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(medeleg_mhandler);                                                                                                                                                                             
    set_shandler(medeleg_shandler);                                                                                                                                                                             

    // setup test page table
    test_pagetable[0] = PTE_V |           PTE_AD | 0x00000000 >> 2;
    test_pagetable[1] = PTE_V |           PTE_AD | 0x40000000 >> 2;
    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    test_pagetable[3] = PTE_V |           PTE_AD | 0xC0000000 >> 2;
    asm volatile ("sfence.vma \n\t");

    // check that trap without delegation is handled in M mode
    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(medeleg, 0);
    medeleg_reg = CSRR(medeleg);
    TEST_COMPARE("clear and check that medeleg bit is 0. Delegation is OFF", 0, medeleg_reg);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   


    // set satp register
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);
    
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "jr t0 \n\t"

        ".globl medeleg_page_fault_handler_return_addr_1\n\t"
        "medeleg_page_fault_handler_return_addr_1: \n\t"
        "nop \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in M mode", MODE_M, medeleg_mode);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   


    // check that trap with delegation is handled in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(medeleg, 1 << CAUSE_FETCH_PAGE_FAULT);
    medeleg_reg = CSRR(medeleg);
    TEST_COMPARE("clear and check that medeleg bit is 1. Delegation is ON", 1 << CAUSE_FETCH_PAGE_FAULT, medeleg_reg);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // set satp register
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);
    
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "jr t0 \n\t"

        ".globl medeleg_page_fault_handler_return_addr_2\n\t"
        "medeleg_page_fault_handler_return_addr_2: \n\t"
        "nop \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in S mode", MODE_S, medeleg_mode);
    TEST_COMPARE("check trap cause",CAUSE_FETCH_PAGE_FAULT , medeleg_cause);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    TEST_END();
}
