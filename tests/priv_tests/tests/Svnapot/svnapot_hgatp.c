
#include <test_utils.h>

// page tables
static pte_t L2_pagetable[5] __attribute__((aligned(PAGE_SIZE*4)));
static pte_t L1_pagetable[5] __attribute__((aligned(PAGE_SIZE)));
static pte_t L0_pagetable[17] __attribute__((aligned(PAGE_SIZE)));



static void exception_shandler(){
    excpt.triggered = true;
}

bool __attribute__((weak)) svnapot_hgatp(){
    TEST_START();

    const reg_t page_addr_lower = 0xC0000000;
    const reg_t page_addr_upper = 0xC0010000; 

    // address inside pte 1, fetched from TLB, because of NAPOT
    const reg_t napot_test_addr = 0xC0001000;

    reg_t read_data_lower;
    reg_t read_data_upper;
    reg_t read_data_temp;

    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    // setup page table, to pages point to the same physical address
    L2_pagetable[2] = PTE_V | PTE_U | PTE_RWX | PTE_AD | 0x80000000 >> 2;
    L2_pagetable[3] = PTE_V |                            ( (reg_t)L1_pagetable ) >> 2;

    L1_pagetable[0] = PTE_V |                            ( (reg_t)L0_pagetable ) >> 2;

    L0_pagetable[0]  = PTE_N | PTE_V | PTE_U | PTE_RWX | PTE_AD | page_addr_lower >> 2 | 0b1000 << 10;
    L0_pagetable[16] = PTE_N | PTE_V | PTE_U | PTE_RWX | PTE_AD | page_addr_lower >> 2 | 0b1000 << 10;
    asm volatile ("hfence.gvma \n\t");

    // enable address translation
    CSRW( hgatp, (SATP_SV39<< SATP_MODE_OFF |  get_ppn((reg_t)L2_pagetable)) );


    set_virtial_mode_host(ON);

    // set data by lower page, then read and check by upper
    read_data_lower = 0xAAAA;
    *( (reg_t*)page_addr_lower + 4 ) = read_data_lower;

    read_data_upper = *( (reg_t*)page_addr_upper + 4 );
    TEST_COMPARE("Write by lower page, read by upper", read_data_lower, read_data_upper);



    // set data by upper page, then read and check by lower
    read_data_upper = 0x5555;
    *( (reg_t*)page_addr_upper + 8 ) = read_data_upper;

    read_data_lower = *( (reg_t*)page_addr_lower + 8 );
    TEST_COMPARE("Write by upper page, read by lower", read_data_lower, read_data_upper);


    // check that read from pte 1 don't cause exception, because this address in TLB
    read_data_temp = *( (reg_t*)napot_test_addr );
    TEST_COMPARE("Check that read from NAPOT test address not trigger exception", false, excpt.triggered);

    set_virtial_mode_host(OFF);


    // disable address translation
    CSRW(hgatp, 0);

    // clear tables
    for (int i = 0; i < 5; i++) {
        L2_pagetable[i] = 0UL;
        L1_pagetable[i] = 0UL;
    }

    for (int i = 0; i < 17; i++) {
        L0_pagetable[i] = 0UL;
    }

    TEST_END();
}
