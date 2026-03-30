#ifndef PLATFORM_H
#define PLATFORM_H

#include <defines.h>
#include <stdint.h>

#if XLEN_BYTES == 8
    typedef uint64_t reg_t;
#else
    typedef uint32_t reg_t;
#endif
/*
 * Flush from cache data to main memory 
 */
void synchronize_memory();

/*
 * System call handler 
 */
uintptr_t syscall(uintptr_t which, uint64_t arg0, uint64_t arg1, uint64_t arg2);

#endif
