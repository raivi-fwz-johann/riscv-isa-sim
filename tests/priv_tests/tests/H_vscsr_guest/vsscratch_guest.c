
#include <test_utils.h>

bool __attribute__((weak)) vsscratch_guest(){
    TEST_START();

    reg_t reg_old; 
    reg_t reg_new; 
    reg_t reg_inverted;

    TEST_COMPARE("check that virtualization is ON", ON, v_mode);                                                   

    reg_old = CSRR(sscratch); 

    reg_inverted = ~reg_old;
    CSRW(sscratch, reg_inverted);
    
    reg_new = CSRR(sscratch); 
    TEST_COMPARE("vsscratch RW access", reg_inverted, reg_new);

    CSRW(sscratch, reg_old);
    reg_new = CSRR(sscratch); 
    TEST_COMPARE("vsscratch restore value", reg_old, reg_new);

    TEST_END();
}
