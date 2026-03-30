#include <test_utils.h>

#define SHCOUNTERENW_CHECK_HPM_W(mask, idx) \
{                                           \
    CSRW(mhpmcounter##idx, -1L);             \
    reg_t temp = CSRR(mhpmcounter##idx);     \
    CSRW(mhpmcounter##idx, 0);               \
    if (temp != 0)                          \
        mask |= (1 << idx);                 \
}


bool __attribute__((weak)) shcounterenw(){
    TEST_START();

    reg_t hpm_writable_mask = 0;
    reg_t hcounteren_reg; 
    
    // get writable hmpcounteren bits
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 3);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 4);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 5);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 6);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 7);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 8);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 9);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 10);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 11);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 12);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 13);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 14);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 15);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 16);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 17);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 18);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 19);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 20);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 21);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 22);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 23);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 24);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 25);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 26);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 27);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 28);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 29);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 30);
    SHCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 31);

    // try to write all ones to hcounteren
    CSRW(hcounteren, -1L);
    hcounteren_reg = CSRR(hcounteren);
    
    // compare hmp writable mask and scounteren bits 
    TEST_COMPARE("compare hmp writable mask and hcounteren bits", (reg_t)(hpm_writable_mask & 0xFFFFFFFF), (reg_t)(hcounteren_reg & (~0b111) & 0xFFFFFFFF) );

    // clear state
    CSRW(hcounteren, 0L);

    TEST_END();
}
