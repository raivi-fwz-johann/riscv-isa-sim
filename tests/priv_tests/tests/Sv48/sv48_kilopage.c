
#include <test_utils.h>

// page tables
static pte_t L3_pagetable[5] __attribute__((aligned(PAGE_SIZE)));
static pte_t L2_pagetable[5] __attribute__((aligned(PAGE_SIZE)));
static pte_t L1_pagetable[5] __attribute__((aligned(PAGE_SIZE)));
static pte_t L0_pagetable[5] __attribute__((aligned(PAGE_SIZE)));

bool __attribute__((weak)) sv48_kilopage(){
    TEST_START();

    const reg_t page_addr_lower = 0xC0000000;
    const reg_t page_addr_upper = 0xC0001000;

    reg_t read_data_lower;
    reg_t read_data_upper;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // setup page table, to pages point to the same physical address
    L3_pagetable[0] = PTE_V |                    ( (reg_t)L2_pagetable ) >> 2;

    L2_pagetable[2] = PTE_V | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    L2_pagetable[3] = PTE_V |                    ( (reg_t)L1_pagetable ) >> 2;

    L1_pagetable[0] = PTE_V |                    ( (reg_t)L0_pagetable ) >> 2;

    L0_pagetable[0] = PTE_V | PTE_RWX | PTE_AD | page_addr_lower >> 2;
    L0_pagetable[1] = PTE_V | PTE_RWX | PTE_AD | page_addr_lower >> 2;
    asm volatile ("sfence.vma \n\t");

    // enable address translation
    CSRW( satp, (SATP_SV48<< SATP_MODE_OFF |  get_ppn((reg_t)L3_pagetable)) );



    // set data by lower page, then read and check by upper
    read_data_lower = 0xAAAA;
    *( (reg_t*)page_addr_lower ) = read_data_lower;

    read_data_upper = *( (reg_t*)page_addr_upper );
    TEST_COMPARE("Write by lower page, read by upper", read_data_lower, read_data_upper);



    // set data by upper page, then read and check by lower
    read_data_upper = 0x5555;
    *( (reg_t*)page_addr_upper ) = read_data_upper;

    read_data_lower = *( (reg_t*)page_addr_lower );
    TEST_COMPARE("Write by upper page, read by lower", read_data_lower, read_data_upper);



    // disable address translation
    CSRW(satp, 0);

    // clear tables
    for (int i = 0; i < 5; i++) {
        L3_pagetable[i] = 0UL;
        L2_pagetable[i] = 0UL;
        L1_pagetable[i] = 0UL;
        L0_pagetable[i] = 0UL;
    }

    TEST_END();
}
