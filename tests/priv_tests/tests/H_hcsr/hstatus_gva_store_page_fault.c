
#include <test_utils.h>

static reg_t hstatus_gva = 0;

static void hstatus_gva_shandler(){
    excpt.triggered = true;
    hstatus_gva = csr_get_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN);
    CSRW(vsatp, 0LL);
}

bool __attribute__((weak)) hstatus_gva_store_page_fault(){
    TEST_START();

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(hstatus_gva_shandler);                                                                                                                                                                             

    // setup test page table
    test_pagetable[0] = PTE_V |           PTE_AD | 0x00000000 >> 2;
    test_pagetable[1] = PTE_V |           PTE_AD | 0x40000000 >> 2;
    test_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    test_pagetable[3] = PTE_V |           PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.vvma \n\t");

    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN, 0);
    reg_t reg = csr_get_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN);
    TEST_COMPARE("check hstatus.gva is clear", 0, reg);

    set_virtial_mode_host(ON);

    // set satp register
    reg_t satp_value;
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);

    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "sb x0, 0(t0) \n\t"
    );

    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    TEST_COMPARE("check hstatus.gva is set under STORE_PAGE_FAULT exception", 1, hstatus_gva);

    // clear changes
    csr_set_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN, 0);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    TEST_END();
}
