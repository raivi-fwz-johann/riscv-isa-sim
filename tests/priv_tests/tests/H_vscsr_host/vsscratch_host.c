
#include <test_utils.h>

bool __attribute__((weak)) vsscratch_host(){
    TEST_START();

    reg_t reg_old; 
    reg_t reg_new; 
    reg_t reg_inverted;

    reg_old = CSRR(vsscratch); 
    reg_inverted = ~reg_old;

    CSRW(vsscratch, reg_inverted);
    reg_new = CSRR(vsscratch); 
    TEST_COMPARE("vsscratch host RW access", reg_inverted, reg_new);
    CSRW(vsscratch, reg_old);
    reg_new = CSRR(vsscratch); 
    TEST_COMPARE("vsscratch host restore value", reg_old, reg_new);

    
    CSRW(vsscratch, reg_inverted);
    set_virtial_mode_host(ON);
    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   
    reg_new = CSRR(sscratch); 
    TEST_COMPARE("vsscratch host W, guest R access", reg_inverted, reg_new);
    CSRW(sscratch, reg_old);
    reg_new = CSRR(sscratch); 
    TEST_COMPARE("vsscratch guest restore value", reg_old, reg_new);


    CSRW(sscratch, reg_inverted);
    set_virtial_mode_host(OFF);
    TEST_COMPARE("check that virtualization is OFF", OFF, v_mode);                                                   
    reg_new = CSRR(vsscratch); 
    TEST_COMPARE("vsscratch guest W, host R access", reg_inverted, reg_new);
    CSRW(vsscratch, reg_old);
    reg_new = CSRR(vsscratch); 
    TEST_COMPARE("vsscratch host restore value", reg_old, reg_new);


    TEST_END();
}
