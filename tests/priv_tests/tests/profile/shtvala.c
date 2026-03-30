
#include <test_utils.h>

static reg_t htval_tval = 32;
static reg_t htval_cause = 32;

static pte_t guest_test_pagetable[4] __attribute__((aligned(PAGE_SIZE*4)));

static void htval_shandler(){
    excpt.triggered = true;
    htval_tval = CSRR(htval);
    htval_cause = CSRR(scause);
}

bool __attribute__((weak)) shtvala(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    CSRW(medeleg, 1 << CAUSE_LOAD_GUEST_PAGE_FAULT);

    reg_t hgatp_value, vsatp_value;
    reg_t none_rwx_addr = 0xC0000000;

    set_shandler(htval_shandler);                                                                                                                                                                             

    // setup guest test page table
    guest_test_pagetable[2] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    guest_test_pagetable[3] = PTE_V | PTE_U |           PTE_AD | 0xC00000000 >> 2;
    asm volatile ("hfence.gvma \n\t");

    // set hgatp register
    hgatp_value = get_ppn( (reg_t)(guest_test_pagetable) );
    hgatp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(hgatp, hgatp_value);

    switch_mode_and_vmode(MODE_S, ON);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    excpt.triggered = false;
    excpt.for_testing = true;

    reg_t temp = *((reg_t*)none_rwx_addr);
    
    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_GUEST_PAGE_FAULT", CAUSE_LOAD_GUEST_PAGE_FAULT, htval_cause);
    TEST_COMPARE("check GUEST PAGE FAULT tval value", 0xC0000000 >> 2, htval_tval);
    

    switch_mode_and_vmode(MODE_M, OFF);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    CSRW(hgatp, 0UL);
    CSRW(medeleg, 0);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        guest_test_pagetable[i] = 0UL;
    }

    TEST_END();
}
