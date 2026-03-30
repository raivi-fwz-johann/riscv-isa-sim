#ifndef MISA_H
#define MISA_H

#include <test_utils.h>

void misa_handler();

#define TEST_MISA_CREATE(extention, instruction)                                                        \
bool __attribute__((weak)) misa_ ## extention (){                                                       \
    TEST_START();                                                                                       \
                                                                                                        \
    reg_t isa_bit;                                                                                      \
    set_mhandler(misa_handler);                                                                         \
                                                                                                        \
    isa_bit = csr_get_field(misa, MISA_ ## extention ## _OFF, MISA_ ## extention ## _LEN);                                              \
    TEST_COMPARE("check isa bit is set", 1, isa_bit);                                                   \
                                                                                                        \
    excpt.for_testing = false;                                                                          \
    asm volatile (instruction);                                                                         \
    TEST_ASSERT("check that exception not triggered", !excpt.triggered);                                \
                                                                                                        \
    csr_set_field(misa, MISA_ ## extention ## _OFF, MISA_B_LEN, 0);                                     \
    isa_bit = csr_get_field(misa, MISA_ ## extention ## _OFF, MISA_ ## extention ## _LEN);              \
    TEST_COMPARE("check that isa bit is unset", 0, isa_bit);                                            \
                                                                                                        \
    excpt.for_testing = true;                                                                           \
    asm volatile (instruction);                                                                         \
    TEST_ASSERT("check that exception triggered and passed", excpt.triggered && excpt.testing_pass);    \
                                                                                                        \
    csr_set_field(misa, MISA_ ## extention ## _OFF, MISA_ ## extention ## _LEN, 1);                     \
    isa_bit = csr_get_field(misa, MISA_ ## extention ## _OFF, MISA_ ## extention ## _LEN);              \
    TEST_COMPARE("check that isa bit is set again", 1, isa_bit);                                        \
                                                                                                        \
    TEST_END();                                                                                         \
}

#endif
