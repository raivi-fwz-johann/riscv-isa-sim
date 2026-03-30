
#include <test_utils.h>

static reg_t stval_tval = 0;
static reg_t stval_epc = 0;

static void vstval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
    stval_epc = CSRR(sepc);
}

bool __attribute__((weak)) vstval_illigal_instruction_guest(){
    TEST_START();

    uint32_t instr;

    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_vshandler(vstval_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile ("unimp \n\t");

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

    TEST_END();
}
