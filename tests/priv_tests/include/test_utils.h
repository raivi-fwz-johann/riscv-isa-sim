#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <csrs.h>
#include <encoding.h>
#include <instructions.h>
#include <logging.h>
#include <platform.h>
#include <handler_utils.h>
#include <page_table.h>

extern struct exception excpt;

typedef bool (*test_func_t)();
extern test_func_t* test_table;
extern size_t test_table_size;

bool check_ro_csr_field(size_t addr, size_t offset, size_t len, reg_t gold);

bool init();

#define TEST_REGISTER(test)\
    bool test();\
    static test_func_t test ## func __attribute__((section(".test_table"), used)) = test;

#define TEST_RO_REGISTER(test, gold)\
    bool test() {\
        TEST_START();\
        test_status = check_ro_csr(test, gold);\
        TEST_END();\
    }\
    static test_func_t test ## func __attribute__((section(".test_table"), used)) = test;

#define TEST_R_REGISTER(test, gold)\
    bool test() {\
        TEST_START();\
        test_status = check_r_csr(test, gold);\
        TEST_END();\
    }\
    static test_func_t test ## func __attribute__((section(".test_table"), used)) = test;

#define TEST_RO_FIELD_REGISTER(test, csr, offset, len, gold)\
    bool test() {\
        TEST_START();\
        test_status = check_ro_csr_field(csr, offset, len, gold);\
        TEST_END();\
    }\
    static test_func_t test ## func __attribute__((section(".test_table"), used)) = test;

#define TEST_RW_FIELD_REGISTER(test, csr, offset, len)\
    bool test() {\
        TEST_START();\
        test_status = check_rw_csr_field(csr, offset, len);\
        TEST_END();\
    }\
    static test_func_t test ## func __attribute__((section(".test_table"), used)) = test;

#define TEST_R_FIELD_REGISTER(test, csr, offset, len, gold)\
    bool test() {\
        TEST_START();\
        test_status = check_r_csr_field(csr, offset, len, gold);\
        TEST_END();\
    }\
    static test_func_t test ## func __attribute__((section(".test_table"), used)) = test;


#define TEST_START()\
    const char* __test_name = __func__;\
    bool test_status = true;\
    if(LOG_LEVEL >= LOG_INFO) printf(CBLU "%-85s" CDFLT, __test_name);\
    if(LOG_LEVEL >= LOG_DETAIL) printf("\n");

#define TEST_ASSERT(test, cond, ...) {\
    if(LOG_LEVEL >= LOG_DETAIL){\
        size_t line_size = 80;\
        size_t size = strlen(test);\
        printf(CBLU "\t%-85.*s" CDFLT, line_size, test);\
        for(int i = line_size; i < size; i+=line_size)\
            printf(CBLU "\n\t%-85.*s" CDFLT, line_size, &test[i]);\
        printf("%s" CDFLT, (cond) ? CGRN "PASSED" : CRED "FAILED");\
        if(!(cond)) { printf("\n\t("); printf(""__VA_ARGS__); printf(")"); }\
        printf("\n");\
    }\
    test_status = test_status && cond;\
    if(!test_status) goto failed; \
}

#define TEST_COMPARE(test, gold, actual) \
    TEST_ASSERT(test , gold == actual, "Mismatch! Gold: %lx. Actual: %lx", gold, actual);

#define TEST_SETUP_EXCEPT() {\
    __sync_synchronize();\
    excpt.testing = true;\
    excpt.triggered = false;\
    excpt.fault_inst = 0;\
    __sync_synchronize();\
    DEBUG("setting up exception test");\
}


#define TEST_EXEC_EXCEPT(addr) {\
    asm volatile(\
        "la t0, 1f\n\t"\
        "sd t0, %1\n\t"\
        "1:\n\t"\
        "jr  %0\n\t"\
        :: "r"(addr), "m"(excpt.fault_inst) : "t0", "memory"\
    );\
}

#define TEST_EXEC_SRET() {\
    asm volatile(\
        "la t0, 1f\n\t"\
        "csrw sepc, t0\n\t"\
        "sret\n\t"\
        "1:\n\t"\
        ::: "t0", "memory"\
    );\
}


#define TEST_END(test) {\
failed:\
    if(LOG_LEVEL >= LOG_INFO && LOG_LEVEL < LOG_VERBOSE){\
         printf("%s\n" CDFLT, (test_status) ? CGRN "PASSED" CDFLT : CRED "FAILED" CDFLT);\
    }\
    return (test_status);\
}


#define csr_get_field(csr, offset, len)     \
    ({                                      \
        reg_t reg;                          \
        reg = CSRR(csr);                    \
        reg >>= offset;                     \
        reg &= ( (1L << len) - 1 );         \
        reg;                                \
    })

#define csr_set_field(csr, offset, len, value)      \
    ({                                              \
        reg_t reg;                                  \
        reg_t mask = ( (1L << len) - 1 ) << offset; \
        reg = CSRR(csr);                            \
        reg &= (~mask);                             \
        reg |= (value << offset);                   \
        CSRW(csr, reg);                             \
    })

#define csr_invert_field(csr, offset, len)  \
    {                                       \
        reg_t reg = CSRR(csr);              \
        reg_t mask = ( (1L << len) - 1 );   \
        mask <<= offset;                    \
        reg ^= mask;                        \
        CSRW(csr, reg);                     \
    }                                       


#define check_ro_csr_field(csr, offset, len, gold)                                                      \
({                                                                                                      \
    reg_t reg;                                                                                          \
    bool test_status = true;                                                                            \
    reg = csr_get_field(csr, offset, len);                                                              \
    TEST_ASSERT("check read value", reg == gold, "Mismatch! Gold: %lx. Actual: %lx", gold, reg);        \
    csr_invert_field(csr, offset, len);                                                                 \
    reg = csr_get_field(csr, offset, len);                                                              \
    TEST_ASSERT("check value after write", reg == gold, "Mismatch! Gold: %lx. Actual: %lx", gold, reg); \
    test_status;                                                                                        \
})


#define check_rw_csr_field(csr, offset, len)                                                            \
({                                                                                                      \
    reg_t reg, reg_old, reg_inv;                                                                        \
    bool test_status = true;                                                                            \
    reg_old = csr_get_field(csr, offset, len);                                                          \
    reg_inv = ~reg_old & ((1 << len) - 1);                                                              \
    csr_invert_field(csr, offset, len);                                                                 \
    reg = csr_get_field(csr, offset, len);                                                              \
    TEST_ASSERT("invert value and check field value", reg == reg_inv, "Mismatch! Gold: %lx. Actual: %lx", reg_inv, reg);      \
    csr_invert_field(csr, offset, len);                                                                 \
    reg = csr_get_field(csr, offset, len);                                                              \
    TEST_ASSERT("invert back and check field value", reg == reg_old, "Mismatch! Gold: %lx. Actual: %lx", reg_old, reg);          \
    test_status;                                                                                        \
})


#define check_r_csr_field(csr, offset, len, gold)                                                       \
({                                                                                                      \
    reg_t reg;                                                                                          \
    bool test_status = true;                                                                            \
    reg = csr_get_field(csr, offset, len);                                                              \
    TEST_ASSERT("check read value", reg == gold, "Mismatch! Gold: %lx. Actual: %lx", gold, reg);        \
    test_status;                                                                                        \
})


#define check_ro_csr(csr, gold)                                                                         \
({                                                                                                      \
    reg_t reg;                                                                                          \
    bool test_status = true;                                                                            \
    reg = CSRR(csr);                                                                                    \
    TEST_ASSERT("check read value", reg == gold, "Mismatch! Gold: %lx. Actual: %lx", gold, reg);        \
    reg = ~reg;                                                                                         \
    CSRW(csr, reg);                                                                                     \
    reg = CSRR(csr);                                                                                    \
    TEST_ASSERT("check value after write", reg == gold, "Mismatch! Gold: %lx. Actual: %lx", gold, reg); \
    test_status;                                                                                        \
})


#define check_r_csr(csr, gold)                                                                          \
({                                                                                                      \
    reg_t reg;                                                                                          \
    bool test_status = true;                                                                            \
    reg = CSRR(csr);                                                                                    \
    TEST_ASSERT("check read value", reg == gold, "Mismatch! Gold: %lx. Actual: %lx", gold, reg);        \
    test_status;                                                                                        \
})

#endif
