
.section .boot, "ax" 
.globl _boot
_boot:
    bnez a0, .
    csrwi    sscratch, 0xf
    /* Initialize stack pointer */
    la sp, __stack_top

    /* Clear bss */ 
    la a0, __bss_start
    la a1, __bss_end
    bgeu a0, a1, 2f
1:
    sw zero, (a0)
    addi a0, a0, 4
    bltu a0, a1, 1b
2:

    /* set mtvec*/
    la t0, mhandler_entry
    csrw mtvec, t0
    
    /* set stvec*/
    la t0, shandler_entry
    csrw stvec, t0

    /* set vstvec*/
    la t0, vshandler_entry
    csrw vstvec, t0

    /* init pmp*/
    // set lower 2 GiB memory to not RWX
    // set upper then 4 GiB memory to not RWX
    // lock pmp so that we can get access fault in M mode
    li t0, (0x80000000 >> 2) 
    csrw pmpaddr0, t0
    li t0, (0x100000000 >> 2)
    csrw pmpaddr1, t0
    li t0, (0x180000000 >> 2)
    csrw pmpaddr2, t0
    li t0, ( (0b10001000 << 16) | (0b10001111 << 8) | 0b10001000 )
    csrw pmpcfg0, t0

    call main
    li a0, 0
    call exit
    j .

.section ".tohost","aw",@progbits
.align 6
.globl tohost
tohost: .dword 0
.align 6
.globl fromhost
fromhost: .dword 0
