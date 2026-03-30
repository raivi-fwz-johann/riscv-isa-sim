
#include <test_utils.h>

static reg_t mtval_tval = 0;
static reg_t mtval_epc = 0;

static void mtval_mhandler(){
    excpt.triggered = true;
    mtval_tval = CSRR(mtval);
    mtval_epc = CSRR(mepc);
}

bool __attribute__((weak)) mtval_illigal_instruction(){
    TEST_START();

    reg_t medeleg_reg;
    uint32_t instr;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(mtval_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile ("unimp \n\t");

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    instr = *((uint32_t*)mtval_epc);
    
    // compressed instruction 
    if ( (instr & 0b11) == 0b11 ) {
        instr &= 0xFFFF;
    }
    
    // compressed unimp instruction
    if ( (instr & 0xFFFF) == 0x0000 ) {
        instr &= 0xFFFF;
    }

    TEST_COMPARE("check ILLIGAL INSTRUCTION tval value", instr, mtval_tval);

    TEST_END();
}
