#include <test_utils.h>

extern test_func_t _test_table, _test_table_size;
test_func_t* test_table = &_test_table;
size_t test_table_size = (size_t) &_test_table_size;
