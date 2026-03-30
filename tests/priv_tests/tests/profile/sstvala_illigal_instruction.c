
#include <test_utils.h>

static reg_t stval_tval = 0;
static reg_t stval_epc = 0;

static void stval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
    stval_epc = CSRR(sepc);
}

bool __attribute__((weak)) sstvala_illigal_instruction(){
    TEST_START();

    uint32_t instr, instr_h;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    CSRW(medeleg, 1 << CAUSE_ILLEGAL_INSTRUCTION);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   


    set_shandler(stval_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile ("unimp \n\t");

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    instr = *((uint16_t*)stval_epc);
    instr_h = *((uint16_t*)stval_epc + 1);
    instr = instr + (instr_h << 16);
    
    // compressed instruction 
    if ( (instr & 0b11) == 0b11 ) {
        instr &= 0xFFFF;
    }
    
    // compressed unimp instruction
    if ( (instr & 0xFFFF) == 0x0000 ) {
        instr &= 0xFFFF;
    }

    TEST_COMPARE("check ILLIGAL INSTRUCTION tval value", instr, stval_tval);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    CSRW(medeleg, 0);

    TEST_END();
}
