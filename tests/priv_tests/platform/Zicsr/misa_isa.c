
#include <test_utils.h>
#include <misa.h>

#undef TEST_MISA_CREATE
#define TEST_MISA_CREATE(extention, instruction)                                                        \
bool __attribute__((weak)) misa_ ## extention (){                                                       \
    TEST_START();                                                                                       \
                                                                                                        \
    reg_t isa_bit;                                                                                      \
    set_mhandler(misa_handler);                                                                         \
                                                                                                        \
    isa_bit = csr_get_field(misa, MISA_ ## extention ## _OFF, MISA_ ## extention ## _LEN);              \
    TEST_COMPARE("check isa bit is set", 1, isa_bit);                                                   \
                                                                                                        \
    excpt.for_testing = false;                                                                          \
    asm volatile (instruction);                                                                         \
    TEST_ASSERT("check that exception not triggered", !excpt.triggered);                                \
                                                                                                        \
    TEST_END();                                                                                         \
}


TEST_MISA_CREATE(B, "andn x0, x0, x0 \n\t")
TEST_MISA_CREATE(C, "c.nop \n\t")
TEST_MISA_CREATE(H, "hfence.vvma \n\t")
TEST_MISA_CREATE(M, "mul x0, x0, x0 \n\t")
