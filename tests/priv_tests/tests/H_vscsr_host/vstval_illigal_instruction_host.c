
#include <test_utils.h>

static reg_t stval_tval = 0;
static reg_t stval_epc = 0;

static void vstval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(vstval);
    stval_epc = CSRR(vsepc);
}

static void vstval_vshandler(){
    // run ecall to jump to Host hamdler and read VS register
    ecall(0,0);
}

bool __attribute__((weak)) vstval_illigal_instruction_host(){
    TEST_START();

    uint32_t instr;

    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_shandler(vstval_shandler);                                                                                                                                                                             
    set_vshandler(vstval_vshandler);                                                                                                                                                                             

    CSRW(hedeleg, ~0L);

    excpt.triggered = false;
    excpt.for_testing = true;

    set_virtial_mode_host(ON);
    asm volatile ("unimp \n\t");
    set_virtial_mode_host(OFF);

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    instr = *((uint32_t*)stval_epc);
    
    // compressed instruction 
    if ( (instr & 0b11) == 0b11 ) {
        instr &= 0xFFFF;
    }
    
    // compressed unimp instruction
    if ( (instr & 0xFFFF) == 0x0000 ) {
        instr &= 0xFFFF;
    }

    TEST_COMPARE("check ILLIGAL INSTRUCTION tval value", instr, stval_tval);

    CSRW(hedeleg, 0L);

    TEST_END();
}
