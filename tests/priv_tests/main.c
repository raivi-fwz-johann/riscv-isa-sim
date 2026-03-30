
#include <test_utils.h>

extern size_t test_table_size;
extern test_func_t* test_table;

#ifdef TEST_NAME
bool TEST_NAME ();
#endif

void main(){
    bool run_passed = true;

    #ifdef TEST_NAME
        init();
        run_passed &= TEST_NAME ();
    #else 
        for (int i = 0; i < test_table_size; i++) {
            run_passed &= test_table[i]();
        }
    #endif
    exit(!run_passed);
}
