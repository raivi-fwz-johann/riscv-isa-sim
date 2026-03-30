
#include <test_utils.h>

static reg_t exception_cause;
static reg_t exception_address = 0xC0000000;

static void exception_mhandler(){
    excpt.triggered = true;
    exception_cause = CSRR(mcause);
}

// page tables
static pte_t L2_pagetable[4] __attribute__((aligned(PAGE_SIZE)));
static pte_t L1_pagetable[4] __attribute__((aligned(PAGE_SIZE)));
static pte_t L0_pagetable[4] __attribute__((aligned(PAGE_SIZE)));

bool __attribute__((weak)) svade_a_vsatp(){
    TEST_START();

    reg_t reg;


    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(exception_mhandler);                                                                                                                                                                             


    // check that page with A flag equal 0 cause page fault exception
    excpt.triggered = false;
    excpt.for_testing = true;

    L2_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    L2_pagetable[3] = PTE_V | PTE_RWX | PTE_D  | 0xC0000000 >> 2;
    asm volatile ("hfence.vvma \n\t");

    CSRW( vsatp, (SATP_SV39<< SATP_MODE_OFF |  get_ppn((reg_t)L2_pagetable)) );

    switch_mode_and_vmode(MODE_S, ON);
    reg = *((reg_t*)exception_address);
    switch_mode_and_vmode(MODE_M, OFF);
    
    CSRW(vsatp, 0);

    TEST_COMPARE("check that interrupt is triggered when A is 0", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, exception_cause);


    // check that page with A flag equal 1 not cause page fault exception
    excpt.triggered = false;
    excpt.for_testing = true;

    L2_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    L2_pagetable[3] = PTE_V | PTE_RWX | PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.vvma \n\t");

    CSRW( vsatp, (SATP_SV39<< SATP_MODE_OFF |  get_ppn((reg_t)L2_pagetable)) );

    switch_mode_and_vmode(MODE_S, ON);
    reg = *((reg_t*)exception_address);
    switch_mode_and_vmode(MODE_M, OFF);

    CSRW(vsatp, 0);

    TEST_COMPARE("check that interrupt is not triggered when A is 1", false, excpt.triggered);


    // clear tables
    for (int i = 0; i < 4; i++) {
        L2_pagetable[i] = 0UL;
        L1_pagetable[i] = 0UL;
        L0_pagetable[i] = 0UL;
    }

    TEST_END();
}
