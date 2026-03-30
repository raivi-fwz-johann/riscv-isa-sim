#include <page_table.h>

pte_t test_pagetable[TEST_PAGETABLE_SIZE] __attribute__((aligned(PAGE_SIZE)));


reg_t get_ppn(reg_t addr) {
    reg_t mask = (1ULL << SATP_PPN_LEN) - 1;
    return (addr / PAGE_SIZE) & mask;
}


reg_t get_test_superpage_address() {
    return (reg_t)(test_pagetable);
}


reg_t get_test_superpage_ppn() {
    reg_t test_superpage_addr = get_test_superpage_address();
    return get_ppn(test_superpage_addr);
}
