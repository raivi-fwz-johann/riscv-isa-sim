
#include <test_utils.h>
#include <misa.h>

void __attribute__((weak)) misa_handler(){
    reg_t cause = CSRR(mcause);

    excpt.triggered = true;

    if (cause == CAUSE_ILLEGAL_INSTRUCTION){
        excpt.testing_pass = true;
    } else {
        excpt.testing_pass = false;
    }

}

