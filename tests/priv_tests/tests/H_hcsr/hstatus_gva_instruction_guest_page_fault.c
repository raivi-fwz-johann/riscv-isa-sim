
#include <test_utils.h>

static reg_t hstatus_gva = 0;

static pte_t guest_test_pagetable[4] __attribute__((aligned(PAGE_SIZE*4)));

extern reg_t hstatus_gva_guest_page_fault_handler_return_addr;

static void hstatus_gva_shandler(){
    excpt.triggered = true;
    hstatus_gva = csr_get_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN);

    CSRW(hgatp, 0LL);
    CSRW(sepc, (reg_t)(&hstatus_gva_guest_page_fault_handler_return_addr));
}

bool __attribute__((weak)) hstatus_gva_instruction_guest_page_fault(){
    TEST_START();

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(hstatus_gva_shandler);                                                                                                                                                                             

    // setup test page table
    guest_test_pagetable[0] = PTE_V |                   PTE_AD | 0x00000000 >> 2;
    guest_test_pagetable[1] = PTE_V |                   PTE_AD | 0x40000000 >> 2;
    guest_test_pagetable[2] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    guest_test_pagetable[3] = PTE_V |                   PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.gvma \n\t");

    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN, 0);
    reg_t reg = csr_get_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN);
    TEST_COMPARE("check hstatus.gva is clear", 0, reg);

    // set hgatp register
    reg_t hgatp_value;
    hgatp_value = get_ppn( (reg_t)(guest_test_pagetable) );
    hgatp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(hgatp, hgatp_value);

    set_virtial_mode_host(ON);

    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "jr t0 \n\t"

        ".globl hstatus_gva_guest_page_fault_handler_return_addr\n\t"
        "hstatus_gva_guest_page_fault_handler_return_addr: \n\t"
        "nop \n\t"
    );
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);

    TEST_COMPARE("check hstatus.gva is set under INSTRUCTION_GUEST_PAGE_FAULT exception", 1, hstatus_gva);

    // clear changes
    csr_set_field(hstatus, HSTATUS_GVA_OFF, HSTATUS_GVA_LEN, 0);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        guest_test_pagetable[i] = 0UL;
    }

    TEST_END();
}
