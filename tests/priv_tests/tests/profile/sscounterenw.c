#include <test_utils.h>

#define SSCOUNTERENW_CHECK_HPM_W(mask, idx) \
{                                           \
    CSRW(mhpmcounter##idx, -1L);             \
    reg_t temp = CSRR(mhpmcounter##idx);     \
    CSRW(mhpmcounter##idx, 0);               \
    if (temp != 0)                          \
        mask |= (1 << idx);                 \
}


bool __attribute__((weak)) sscounterenw(){
    TEST_START();

    reg_t hpm_writable_mask = 0;
    reg_t scounteren_reg; 
    
    // get writable hmpcounteren bits
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 3);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 4);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 5);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 6);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 7);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 8);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 9);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 10);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 11);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 12);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 13);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 14);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 15);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 16);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 17);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 18);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 19);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 20);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 21);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 22);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 23);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 24);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 25);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 26);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 27);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 28);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 29);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 30);
    SSCOUNTERENW_CHECK_HPM_W(hpm_writable_mask, 31);

    // try to write all ones to scounteren
    CSRW(scounteren, -1L);
    scounteren_reg = CSRR(scounteren);
    
    // compare hmp writable mask and scounteren bits 
    TEST_COMPARE("compare hmp writable mask and scounteren bits", (reg_t)(hpm_writable_mask & 0xFFFFFFFF), (reg_t)(scounteren_reg & (~0b111) & 0xFFFFFFFF) );

    // clear state
    CSRW(scounteren, 0L);

    TEST_END();
}
