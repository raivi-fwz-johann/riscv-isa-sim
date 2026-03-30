
#include <test_utils.h>

bool __attribute__((weak)) mscratch(){
    TEST_START();

    reg_t reg_old; 
    reg_t reg_new; 
    reg_t reg_inverted;

    reg_old = CSRR(mscratch); 

    reg_inverted = ~reg_old;
    CSRW(mscratch, reg_inverted);
    
    reg_new = CSRR(mscratch); 
    TEST_COMPARE("mscratch RW access", reg_inverted, reg_new);

    CSRW(mscratch, reg_old);
    reg_new = CSRR(mscratch); 
    TEST_COMPARE("mscratch restore value", reg_old, reg_new);

    TEST_END();
}
