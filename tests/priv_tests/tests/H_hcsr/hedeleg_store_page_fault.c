
#include <test_utils.h>

static reg_t hedeleg_v_mode = 0;
static reg_t hedeleg_cause = 32;

static void hedeleg_shandler(){
    excpt.triggered = true;
    hedeleg_v_mode = OFF;
    hedeleg_cause = CSRR(scause);
}

static void hedeleg_vshandler(){
    excpt.triggered = true;
    hedeleg_v_mode = ON;
    hedeleg_cause = CSRR(scause);
}

bool __attribute__((weak)) hedeleg_store_page_fault(){
    TEST_START();

    reg_t hedeleg_reg;
    reg_t temp;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    set_shandler(hedeleg_shandler);                                                                                                                                                                             
    set_vshandler(hedeleg_vshandler);                                                                                                                                                                             

    // setup test page table
    test_pagetable[0] = PTE_V |           PTE_AD | 0x00000000 >> 2;
    test_pagetable[1] = PTE_V |           PTE_AD | 0x40000000 >> 2;
    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    test_pagetable[3] = PTE_V |           PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.vvma \n\t");

    // set satp register
    reg_t satp_value;
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(vsatp, satp_value);

    // check that trap without delegation is handled in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(hedeleg, 0);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 0. Delegation is OFF", 0, hedeleg_reg);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "sb x0, 0(t0) \n\t"
    );

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in S mode", OFF, hedeleg_v_mode);


    // check that trap with delegation is handled in S mode
    excpt.triggered = false;
    excpt.for_testing = true;

    CSRW(hedeleg, 1 << CAUSE_STORE_PAGE_FAULT);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 1. Delegation is ON", 1 << CAUSE_STORE_PAGE_FAULT, hedeleg_reg);

    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "sb x0, 0(t0) \n\t"
    );

    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap handled in VS mode", ON, hedeleg_v_mode);
    TEST_COMPARE("check trap cause", CAUSE_STORE_PAGE_FAULT, hedeleg_cause);

    //clear state
    CSRW(hedeleg, 0);
    hedeleg_reg = CSRR(hedeleg);
    TEST_COMPARE("clear and check that hedeleg bit is 0. Delegation is OFF", 0, hedeleg_reg);

    CSRW(vsatp, 0LL);
    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }
    TEST_END();
}
