
#include <test_utils.h>

static reg_t exception_cause;
static reg_t exception_address = 0xC0000000;

static void exception_shandler(){
    excpt.triggered = true;
    exception_cause = CSRR(scause);
}

// page tables
static pte_t L4_pagetable[4] __attribute__((section(".bss2"),aligned(PAGE_SIZE)));
static pte_t L3_pagetable[4] __attribute__((section(".bss2"),aligned(PAGE_SIZE)));
static pte_t L2_pagetable[4] __attribute__((section(".bss2"),aligned(PAGE_SIZE)));
static pte_t L1_pagetable[4] __attribute__((section(".bss2"),aligned(PAGE_SIZE)));
static pte_t L0_pagetable[4] __attribute__((section(".bss2"),aligned(PAGE_SIZE)));

bool __attribute__((weak)) sv57_v(){
    TEST_START();

    reg_t reg;



    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // clear tables
    for (int i = 0; i < 4; i++) {
        L4_pagetable[i] = 0UL;
        L3_pagetable[i] = 0UL;
        L2_pagetable[i] = 0UL;
        L1_pagetable[i] = 0UL;
        L0_pagetable[i] = 0UL;
    }

    set_shandler(exception_shandler);                                                                                                                                                                         


    // check that page with V flag equal 0 cause page fault exception
    excpt.triggered = false;
    excpt.for_testing = true;

    L4_pagetable[0] = PTE_V |                    ( (reg_t)L3_pagetable ) >> 2;
    L3_pagetable[0] = PTE_V |                    ( (reg_t)L2_pagetable ) >> 2;
    
    L2_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    L2_pagetable[3] =         PTE_RWX | PTE_AD | 0xC0000000 >> 2;
    asm volatile ("sfence.vma \n\t");

    CSRW( satp, (SATP_SV57<< SATP_MODE_OFF |  get_ppn((reg_t)L4_pagetable)) );
    reg = *((reg_t*)exception_address);
    CSRW(satp, 0);

    TEST_COMPARE("check that interrupt is triggered when V is 0", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, exception_cause);


    // check that page with V flag equal 1 not cause page fault exception
    excpt.triggered = false;
    excpt.for_testing = true;

    L4_pagetable[0] = PTE_V |                    ( (reg_t)L3_pagetable ) >> 2;
    L3_pagetable[0] = PTE_V |                    ( (reg_t)L2_pagetable ) >> 2;

    L2_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    L2_pagetable[3] = PTE_V | PTE_RWX | PTE_AD | 0xC0000000 >> 2;
    asm volatile ("sfence.vma \n\t");

    CSRW( satp, (SATP_SV57<< SATP_MODE_OFF |  get_ppn((reg_t)L4_pagetable)) );
    reg = *((reg_t*)exception_address);
    CSRW(satp, 0);

    TEST_COMPARE("check that interrupt is not triggered when V is 1", false, excpt.triggered);


    // clear tables
    for (int i = 0; i < 4; i++) {
        L4_pagetable[i] = 0UL;
        L3_pagetable[i] = 0UL;
        L2_pagetable[i] = 0UL;
        L1_pagetable[i] = 0UL;
        L0_pagetable[i] = 0UL;
    }

    TEST_END();
}
