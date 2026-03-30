
#include <test_utils.h>

extern reg_t sv48_hgatp_return_addr;

static reg_t exception_cause;
static reg_t exception_address = 0xC0000000;

static void exception_execute();

static void exception_shandler(){
    excpt.triggered = true;
    exception_cause = CSRR(scause);
    CSRW(sepc, (reg_t)(&sv48_hgatp_return_addr));
}

// page tables
static pte_t L3_pagetable[4] __attribute__((aligned(PAGE_SIZE*4)));
static pte_t L2_pagetable[4] __attribute__((aligned(PAGE_SIZE)));
static pte_t L1_pagetable[4] __attribute__((aligned(PAGE_SIZE)));
static pte_t L0_pagetable[4] __attribute__((aligned(PAGE_SIZE)));

bool __attribute__((weak)) sv48_x_hgatp(){
    TEST_START();

    reg_t reg;


    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(exception_shandler);                                                                                                                                                                             

    // set exception address to illigal instruction
    *((reg_t*)exception_address) = 0;

    // check that page with X flag equal 0 cause page fault exception
    excpt.triggered = false;
    excpt.for_testing = true;

    L3_pagetable[0] = PTE_V |                    ( (reg_t)L2_pagetable ) >> 2;

    L2_pagetable[2] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    L2_pagetable[3] = PTE_V | PTE_U |           PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.gvma \n\t");

    CSRW( hgatp, (SATP_SV48<< SATP_MODE_OFF |  get_ppn((reg_t)L3_pagetable)) );

    set_virtial_mode_host(ON);
    exception_execute();
    set_virtial_mode_host(OFF);
    
    CSRW(hgatp, 0);

    TEST_COMPARE("check that interrupt is triggered when X is 0", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_FETCH_GUEST_PAGE_FAULT", CAUSE_FETCH_GUEST_PAGE_FAULT, exception_cause);


    // check that page with X flag equal 1 not cause page fault exception
    excpt.triggered = false;
    excpt.for_testing = true;

    L3_pagetable[0] = PTE_V |                    ( (reg_t)L2_pagetable ) >> 2;

    L2_pagetable[2] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    L2_pagetable[3] = PTE_V | PTE_U | PTE_X   | PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.gvma \n\t");

    CSRW( hgatp, (SATP_SV48<< SATP_MODE_OFF |  get_ppn((reg_t)L3_pagetable)) );

    set_virtial_mode_host(ON);
    exception_execute();
    set_virtial_mode_host(OFF);

    CSRW(hgatp, 0);

    TEST_COMPARE("check that interrupt is triggered when X is 1", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_ILLIGAL_INSTRUCTION", CAUSE_ILLEGAL_INSTRUCTION, exception_cause);

    // clear tables
    for (int i = 0; i < 4; i++) {
        L3_pagetable[i] = 0UL;
        L2_pagetable[i] = 0UL;
        L1_pagetable[i] = 0UL;
        L0_pagetable[i] = 0UL;
    }

    TEST_END();
}

static void exception_execute() {
    asm volatile (
        "li t0, 0xC0000000 \n\t"
        "jr 0(t0) \n\t"

        ".globl sv48_hgatp_return_addr\n\t"
        "sv48_hgatp_return_addr: \n\t"
        "nop \n\t"
    );
}
