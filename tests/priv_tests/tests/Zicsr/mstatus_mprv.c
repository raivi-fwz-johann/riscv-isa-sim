
#include <test_utils.h>

static reg_t mcause_cause = 32;

static void mcause_mhandler(){
    excpt.triggered = true;
    mcause_cause = CSRR(mcause);
    csr_set_field(mstatus, MSTATUS_MPRV_OFF, MSTATUS_MPRV_LEN, 0);
}

bool __attribute__((weak)) mstatus_mprv(){
    TEST_START();

    reg_t satp_value, mpp;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mcause_mhandler);                                                                                                                                                                             

    
    // set satp register
    satp_value = get_test_superpage_ppn();
    satp_value |= SATP_SV39<< SATP_MODE_OFF;
    CSRW(satp, satp_value);
    
    // check that when MPRV is 0 and MPP is MODE_S, translation is not used  
    csr_set_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN, MODE_S);
    mpp = csr_get_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN);
    TEST_COMPARE("check mstatus.mpp is MODE_S", MODE_S, mpp);

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        // mstatus bit 17 is MPRV 
        "li t0, (1 << 17) \n\t"
        "csrc mstatus, t0 \n\t"
        
        "load_addr_1: \n\t"
        "la t0, load_addr_1 \n\t"
        "lb x0, 0(t0) \n\t"
    );

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);

    // check that when MPRV is 1 and MPP is MODE_M, translation is not used  
    csr_set_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN, MODE_M);
    mpp = csr_get_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN);
    TEST_COMPARE("check mstatus.mpp is MODE_M", MODE_M, mpp);

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        // mstatus bit 17 is MPRV 
        "li t0, (1 << 17) \n\t"
        "csrs mstatus, t0 \n\t"

        "load_addr_2: \n\t"
        "la t0, load_addr_2 \n\t"
        "lb x0, 0(t0) \n\t"
        
        "li t0, (1 << 17) \n\t"
        "csrc mstatus, t0 \n\t"
    );

    TEST_COMPARE("check that interrupt is not triggered", false, excpt.triggered);
    
    // check that when MPRV is 1 and MPP is MODE_S, translation is used
    // because we not initialize page table we expect trap
    csr_set_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN, MODE_S);
    mpp = csr_get_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN);
    TEST_COMPARE("check mstatus.mpp is MODE_S", MODE_S, mpp);

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile (
        // mstatus bit 17 is MPRV 
        "li t0, (1 << 17) \n\t"
        "csrs mstatus, t0 \n\t"

        "load_addr_3: \n\t"
        "la t0, load_addr_3 \n\t"
        "lb x0, 0(t0) \n\t"
        
        "li t0, (1 << 17) \n\t"
        "csrc mstatus, t0 \n\t"
    );

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    TEST_COMPARE("check trap cause CAUSE_LOAD_PAGE_FAULT", CAUSE_LOAD_PAGE_FAULT, mcause_cause);

    // clear state
    CSRW(satp, 0Ul);
    csr_set_field(mstatus, MSTATUS_MPP_OFF, MSTATUS_MPP_LEN, MODE_M);
    csr_set_field(mstatus, MSTATUS_MPRV_OFF, MSTATUS_MPRV_LEN, 0);

    for (int i = 0; i < TEST_PAGETABLE_SIZE; i++) {
        test_pagetable[i] = 0UL;
    }

    TEST_END();
}
