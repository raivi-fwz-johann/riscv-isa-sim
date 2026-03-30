
#include <test_utils.h>

static reg_t test_data = 0;

bool __attribute__((weak)) za64rs(){
    TEST_START();

    reg_t sc_rd; 
    
    // read test data using LR, then try to SC to test data address plus 64 byte
    // SC should fail, because reservation set size is 64B maximum

    asm volatile (
        /* read using load reserved */
        "la t0, test_data \n"
        "lr.w t2, (t0) \n"

        /* increment address by 64 bytes */
        "addi t0, t0, 64 \n"

        /* try to run store conditional */
        "sc.w %0, t1, (t0) \n"
        
        : "=r" (test_data)
        : /*no input data*/
        : "t0", "t1", "t2"
    );

    TEST_ASSERT("store conditional with 64 byte offset failed" , test_data != 0, "Mismatch! SC fould fail with offset more then 64B");

    TEST_END();
}
