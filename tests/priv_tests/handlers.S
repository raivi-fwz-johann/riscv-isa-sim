#include <defines.h>

#if XLEN_BYTES == 8
    #define LOAD ld
    #define STORE sd
    #define REGLEN (8)
#else
    #define LOAD lw
    #define STORE sw
    #define REGLEN (4)
#endif

#ifndef HANDLER_ALIGN
    #define HANDLER_ALIGN 0x4
#endif

.macro SAVE_CONTEXT

    add sp, sp, -(REGLEN*31)

    STORE   x1, 0*REGLEN(sp)
    STORE   x3, 2*REGLEN(sp)
    STORE   x4, 3*REGLEN(sp)
    STORE   x5, 4*REGLEN(sp)
    STORE   x6, 5*REGLEN(sp)
    STORE   x7, 6*REGLEN(sp)
    STORE   x8, 7*REGLEN(sp)
    STORE   x9, 8*REGLEN(sp)
    STORE   x10, 9*REGLEN(sp)
    STORE   x11, 10*REGLEN(sp)
    STORE   x12, 11*REGLEN(sp)
    STORE   x13, 12*REGLEN(sp)
    STORE   x14, 13*REGLEN(sp)
    STORE   x15, 14*REGLEN(sp)
    STORE   x16, 15*REGLEN(sp)
    STORE   x17, 16*REGLEN(sp)
    STORE   x18, 17*REGLEN(sp)
    STORE   x19, 18*REGLEN(sp)
    STORE   x20, 19*REGLEN(sp)
    STORE   x21, 20*REGLEN(sp)
    STORE   x22, 21*REGLEN(sp)
    STORE   x23, 22*REGLEN(sp)
    STORE   x24, 23*REGLEN(sp)
    STORE   x25, 24*REGLEN(sp)
    STORE   x26, 25*REGLEN(sp)
    STORE   x27, 26*REGLEN(sp)
    STORE   x28, 27*REGLEN(sp)
    STORE   x29, 28*REGLEN(sp)
    STORE   x30, 29*REGLEN(sp)
    STORE   x31, 29*REGLEN(sp)
.endm

.macro RESTORE_CONTEXT
    LOAD   x1, 0*REGLEN(sp)
    LOAD   x3, 2*REGLEN(sp)
    LOAD   x4, 3*REGLEN(sp)
    LOAD   x5, 4*REGLEN(sp)
    LOAD   x6, 5*REGLEN(sp)
    LOAD   x7, 6*REGLEN(sp)
    LOAD   x8, 7*REGLEN(sp)
    LOAD   x9, 8*REGLEN(sp)
    LOAD   x10, 9*REGLEN(sp)
    LOAD   x11, 10*REGLEN(sp)
    LOAD   x12, 11*REGLEN(sp)
    LOAD   x13, 12*REGLEN(sp)
    LOAD   x14, 13*REGLEN(sp)
    LOAD   x15, 14*REGLEN(sp)
    LOAD   x16, 15*REGLEN(sp)
    LOAD   x17, 16*REGLEN(sp)
    LOAD   x18, 17*REGLEN(sp)
    LOAD   x19, 18*REGLEN(sp)
    LOAD   x20, 19*REGLEN(sp)
    LOAD   x21, 20*REGLEN(sp)
    LOAD   x22, 21*REGLEN(sp)
    LOAD   x23, 22*REGLEN(sp)
    LOAD   x24, 23*REGLEN(sp)
    LOAD   x25, 24*REGLEN(sp)
    LOAD   x26, 25*REGLEN(sp)
    LOAD   x27, 26*REGLEN(sp)
    LOAD   x28, 27*REGLEN(sp)
    LOAD   x29, 28*REGLEN(sp)
    LOAD   x30, 29*REGLEN(sp) 
    LOAD   x31, 30*REGLEN(sp) 

    add sp, sp, (REGLEN*31) 
.endm

.balign HANDLER_ALIGN
.global mhandler_entry
mhandler_entry:
    SAVE_CONTEXT
    jal mhandler_trampoline
    RESTORE_CONTEXT
    mret 


.balign HANDLER_ALIGN
.global shandler_entry
shandler_entry:
    SAVE_CONTEXT
    jal shandler_trampoline
    RESTORE_CONTEXT
    sret 


.balign HANDLER_ALIGN
.global vshandler_entry
vshandler_entry:
    SAVE_CONTEXT
    jal vshandler_trampoline
    RESTORE_CONTEXT
    sret 


.balign HANDLER_ALIGN
.global other_mhandler_entry
other_mhandler_entry:
    j mhandler_entry


.balign HANDLER_ALIGN
.global other_shandler_entry
other_shandler_entry:
    j shandler_entry


.balign HANDLER_ALIGN
.global other_vshandler_entry
other_vshandler_entry:
    j vshandler_entry



