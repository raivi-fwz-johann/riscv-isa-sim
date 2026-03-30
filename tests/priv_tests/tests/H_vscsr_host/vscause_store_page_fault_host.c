
#include <test_utils.h>

static reg_t scause_cause = 32;

static void vscause_shandler(){
    excpt.triggered = true;
    scause_cause = CSRR(vscause);
}

static void vscause_vshandler(){
    // run ecall to jump to Host hamdler and read VS register
    ecall(0,0);
    CSRW(satp, 0LL);
}

bool __attribute__((weak)) vscause_store_page_fault_host(){
    TEST_START();

    reg_t satp_value;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(vscause_vshandler);                                                                                                                                                                             
    set_shandler(vscause_shandler);                                                                                                                                                                             

    CSRW(hedeleg, ~0L);

    excpt.triggered = false;
    excpt.for_testing = true;

    // setup test page table
    test_pagetable[0] = PTE_V |           PTE_AD | 0x00000000 >> 2;
    test_pagetable[1] = PTE_V |           PTE_AD | 0x40000000 >> 2;
    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    test_pagetable[3] = PTE_V |           PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.vvma \n\t");

    set_virtial_mode_host(ON);

    // set satp register
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);
    
    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "sb x0, 0(t0) \n\t"
    );

    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_STORE_PAGE_FAULT", CAUSE_STORE_PAGE_FAULT, scause_cause);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    CSRW(hedeleg, 0L);

    TEST_END();
}
