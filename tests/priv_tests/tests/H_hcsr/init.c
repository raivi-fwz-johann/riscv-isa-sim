
#include <test_utils.h>

bool __attribute__((weak)) init(){
    TEST_START();

    TEST_COMPARE("check that currunt mode is M", MODE_M, current_mode);                                                   

    // delegate all exceptions and interrupts to S mode
    CSRW(medeleg, ~0L);
    CSRW(mideleg, ~0L);

    switch_mode(MODE_S);
    TEST_COMPARE("check that currunt mode is S", MODE_S, current_mode);                                                   

    TEST_END();
}
