
#include <test_utils.h>

bool __attribute__((weak)) sscratch(){
    TEST_START();

    reg_t reg_old; 
    reg_t reg_new; 
    reg_t reg_inverted;

    reg_old = CSRR(sscratch); 

    reg_inverted = ~reg_old;
    CSRW(sscratch, reg_inverted);
    
    reg_new = CSRR(sscratch); 
    TEST_COMPARE("sscratch RW access", reg_inverted, reg_new);

    CSRW(sscratch, reg_old);
    reg_new = CSRR(sscratch); 
    TEST_COMPARE("sscratch restore value", reg_old, reg_new);

    TEST_END();
}
