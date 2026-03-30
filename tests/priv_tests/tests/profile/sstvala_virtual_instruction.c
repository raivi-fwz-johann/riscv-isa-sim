
#include <test_utils.h>

static reg_t stval_tval = 0;
static reg_t stval_epc = 0;

static void stval_shandler(){
    excpt.triggered = true;
    stval_tval = CSRR(stval);
    stval_epc = CSRR(sepc);
}

bool __attribute__((weak)) sstvala_virtual_instruction(){
    TEST_START();

    uint32_t instr, instr_h;

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   
    CSRW(medeleg, 1 << CAUSE_VIRTUAL_INSTRUCTION);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    set_virtial_mode_machine(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    set_shandler(stval_shandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    asm volatile ("hlv.w x0, (x0) \n");

    TEST_COMPARE("check that interrupt is triggered", true, excpt.triggered);
    
    instr = *((uint16_t*)stval_epc);
    instr_h = *((uint16_t*)stval_epc + 1);
    instr = instr + (instr_h << 16);

    TEST_COMPARE("check VIRTUAL INSTRUCTION tval value", instr, stval_tval);


    set_virtial_mode_machine(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    CSRW(medeleg, 0);

    TEST_END();
}
