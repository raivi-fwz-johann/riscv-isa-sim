#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <platform.h>
#include <csrs.h>

#define PAGE_SIZE 4096

#define PTE_VALID (1ULL << 0)
#define PTE_READ (1ULL << 1)
#define PTE_WRITE (1ULL << 2)
#define PTE_EXECUTE (1ULL << 3)
#define PTE_USER (1ULL << 4)
#define PTE_GLOBAL (1ULL << 5)
#define PTE_ACCESS (1ULL << 6)
#define PTE_DIRTY (1ULL << 7)

#define PTE_V PTE_VALID
#define PTE_AD (PTE_ACCESS | PTE_DIRTY)
#define PTE_A PTE_ACCESS
#define PTE_D PTE_DIRTY
#define PTE_U PTE_USER
#define PTE_R (PTE_READ)
#define PTE_RW (PTE_READ | PTE_WRITE)
#define PTE_X (PTE_EXECUTE)
#define PTE_RX (PTE_READ | PTE_EXECUTE)
#define PTE_RWX (PTE_READ | PTE_WRITE | PTE_EXECUTE)

#define PTE_N (1ULL << (XLEN_BYTES*8 - 1))

#define SATP_BARE 0ULL
#define SATP_SV32 1ULL
#define SATP_SV39 8ULL
#define SATP_SV48 9ULL
#define SATP_SV57 10ULL

enum test_page { 
    VSRWX_GURWX,
    VSRWX_GURW,
    VSRWX_GURX,
    VSRWX_GUR,
    VSRWX_GUX,
    VSRW_GURWX,
    VSRW_GURW,
    VSRW_GURX,
    VSRW_GUR,
    VSRW_GUX,
    VSRX_GURWX,
    VSRX_GURW,
    VSRX_GURX,
    VSRX_GUR,
    VSRX_GUX,
    VSR_GURWX,
    VSR_GURW,
    VSR_GURX,
    VSR_GUR,
    VSR_GUX,
    VSX_GURWX,
    VSX_GURW,
    VSX_GURX,
    VSX_GUR,
    VSX_GUX,
    VSURWX_GRWX,
    VSURWX_GRW,
    VSURWX_GRX,
    VSURWX_GR,
    VSURWX_GX,
    VSURW_GRWX,
    VSURW_GRW,
    VSURW_GRX,
    VSURW_GR,
    VSURW_GX,
    VSURX_GRWX,
    VSURX_GRW,
    VSURX_GRX,
    VSURX_GR,
    VSURX_GX,
    VSUR_GRWX,
    VSUR_GRW,
    VSUR_GRX,
    VSUR_GR,
    VSUR_GX,
    VSUX_GRWX,
    VSUX_GRW,
    VSUX_GRX,
    VSUX_GR,
    VSUX_GX,
    VSURWX_GURWX,
    VSURWX_GURW,
    VSURWX_GURX,
    VSURWX_GUR,
    VSURWX_GUX,
    VSURW_GURWX,
    VSURW_GURW,
    VSURW_GURX,
    VSURW_GUR,
    VSURW_GUX,
    VSURX_GURWX,
    VSURX_GURW,
    VSURX_GURX,
    VSURX_GUR,
    VSURX_GUX,
    VSUR_GURWX,
    VSUR_GURW,
    VSUR_GURX,
    VSUR_GUR,
    VSUR_GUX,
    VSUX_GURWX,
    VSUX_GURW,
    VSUX_GURX,
    VSUX_GUR,
    VSUX_GUX,
    VSRWX_GRWX,
    VSRWX_GRW,
    VSRWX_GRX,
    VSRWX_GR,
    VSRWX_GX,
    VSRW_GRWX,
    VSRW_GRW,
    VSRW_GRX,
    VSRW_GR,
    VSRW_GX,
    VSRX_GRWX,
    VSRX_GRW,
    VSRX_GRX,
    VSRX_GR,
    VSRX_GX,
    VSR_GRWX,
    VSR_GRW,
    VSR_GRX,
    VSR_GR,
    VSR_GX,
    VSX_GRWX,
    VSX_GRW,
    VSX_GRX,
    VSX_GR,
    VSX_GX,
    VSI_GI,
    VSRWX_GI,
    VSRW_GI,
    VSI_GURWX,
    VSI_GUX,
    VSI_GUR,
    VSI_GURW,
    SCRATCHPAD,
    SWITCH1,
    SWITCH2,
    TOP = 511,
    TEST_PAGE_MAX
};

typedef reg_t pte_t;

// use page table with for entries, so that for Sv39 we can cover first 4 GiB
#define TEST_PAGETABLE_SIZE 4
extern pte_t test_pagetable[TEST_PAGETABLE_SIZE];

reg_t get_ppn(reg_t addr);
reg_t get_test_superpage_address();
reg_t get_test_superpage_ppn();

#endif
