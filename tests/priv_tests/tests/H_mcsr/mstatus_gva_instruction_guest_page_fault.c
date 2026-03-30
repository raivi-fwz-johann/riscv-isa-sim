
#include <test_utils.h>

static reg_t mstatus_gva = 0;

static pte_t guest_test_pagetable[4] __attribute__((aligned(PAGE_SIZE*4)));

extern reg_t mstatus_gva_guest_page_fault_handler_return_addr;

static void mstatus_gva_mhandler(){
    excpt.triggered = true;
    mstatus_gva = csr_get_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN);
    reg_t reg = CSRR(mstatus);

    CSRW(hgatp, 0LL);
    CSRW(mepc, (reg_t)(&mstatus_gva_guest_page_fault_handler_return_addr));
}

bool __attribute__((weak)) mstatus_gva_instruction_guest_page_fault(){
    TEST_START();

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mstatus_gva_mhandler);                                                                                                                                                                             

    guest_test_pagetable[0] = PTE_V |                   PTE_AD | 0x00000000 >> 2;
    guest_test_pagetable[1] = PTE_V |                   PTE_AD | 0x40000000 >> 2;
    guest_test_pagetable[2] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    guest_test_pagetable[3] = PTE_V |                   PTE_AD | 0xC0000000 >> 2;
    asm volatile ("hfence.gvma \n\t");

    excpt.triggered = false;
    excpt.for_testing = true;

    csr_set_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN, 0L);
    reg_t reg = csr_get_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN);
    TEST_COMPARE("check mstatus.gva is clear", 0, mstatus_gva);

    // set hgatp register
    reg_t hgatp_value;
    hgatp_value = get_ppn( (reg_t)(guest_test_pagetable) );
    hgatp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(hgatp, hgatp_value);

    switch_mode_and_vmode(MODE_S, ON);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    asm volatile (
        "la t0, 0x7FFFFFFF \n\t"
        "jr t0 \n\t"

        ".globl mstatus_gva_guest_page_fault_handler_return_addr\n\t"
        "mstatus_gva_guest_page_fault_handler_return_addr: \n\t"
        "nop \n\t"
    );
    
    switch_mode_and_vmode(MODE_M, OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check mstatus.gva is set under INSTRUCTION_GUEST_PAGE_FAULT exception", 1, mstatus_gva);
    
    // clear changes
    csr_set_field(mstatus, MSTATUS_GVA_OFF, MSTATUS_GVA_LEN, 0L);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        guest_test_pagetable[i] = 0UL;
    }

    TEST_END();
}
