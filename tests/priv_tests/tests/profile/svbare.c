
#include <test_utils.h>


static void svbare_mhandler(){
    excpt.triggered = true;
}

bool __attribute__((weak)) svbare(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    set_mhandler(svbare_mhandler);                                                                                                                                                                             

    excpt.triggered = false;
    excpt.for_testing = true;

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    CSRW(satp, 0L);
    reg_t satp_reg = CSRR(satp);
    TEST_COMPARE("check satp is in bare mode", 0, satp_reg);
    
    TEST_COMPARE("check that exception is not triggered", false, excpt.triggered);

    switch_mode(MODE_M);
    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    TEST_END();
}
