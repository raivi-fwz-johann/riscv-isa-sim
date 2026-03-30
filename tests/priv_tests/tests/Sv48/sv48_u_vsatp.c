
#include <test_utils.h>

static reg_t exception_cause;
static reg_t exception_address = 0xC0000000;

static void exception_shandler(){
    excpt.triggered = true;
    exception_cause = CSRR(scause);
}

// page tables
static pte_t L3_pagetable[4] __attribute__((aligned(PAGE_SIZE)));
static pte_t L2_pagetable[4] __attribute__((aligned(PAGE_SIZE)));
static pte_t L1_pagetable[4] __attribute__((aligned(PAGE_SIZE)));
static pte_t L0_pagetable[4] __attribute__((aligned(PAGE_SIZE)));

bool __attribute__((weak)) sv48_u_vsatp(){
    TEST_START();

    reg_t reg;


    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(exception_shandler);                                                                                                                                                                             


    // check that page with U flag equal 0 in vsatp not cause page fault exception in VS mode
    excpt.triggered = false;
    excpt.for_testing = true;

    L3_pagetable[0] = PTE_V |                    ( (reg_t)L2_pagetable ) >> 2;

    L2_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    L2_pagetable[3] = PTE_V | PTE_RWX | PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.vvma \n\t");

    CSRW( vsatp, (SATP_SV48<< SATP_MODE_OFF |  get_ppn((reg_t)L3_pagetable)) );

    set_virtial_mode_host(ON);
    reg = *((reg_t*)exception_address);
    set_virtial_mode_host(OFF);
    
    CSRW(vsatp, 0);

    TEST_COMPARE("check that interrupt is not triggered when U is 0", false, excpt.triggered);


    // check that page with U flag equal 1 in vsatp cause page fault exception in VS mode
    excpt.triggered = false;
    excpt.for_testing = true;

    L3_pagetable[0] = PTE_V |                    ( (reg_t)L2_pagetable ) >> 2;

    L2_pagetable[2] = PTE_V |        PTE_RWX | PTE_AD | 0x80000000 >> 2;
    L2_pagetable[3] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.vvma \n\t");

    CSRW( vsatp, (SATP_SV48<< SATP_MODE_OFF |  get_ppn((reg_t)L3_pagetable)) );

    set_virtial_mode_host(ON);
    reg = *((reg_t*)exception_address);
    set_virtial_mode_host(OFF);

    CSRW(vsatp, 0);

    TEST_COMPARE("check that interrupt is triggered when U is 1", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, exception_cause);


    // clear tables
    for (int i = 0; i < 4; i++) {
        L3_pagetable[i] = 0UL;
        L2_pagetable[i] = 0UL;
        L1_pagetable[i] = 0UL;
        L0_pagetable[i] = 0UL;
    }

    TEST_END();
}
