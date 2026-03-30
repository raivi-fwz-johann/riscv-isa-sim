#include <defines.h>

ENTRY(_boot)

STACK_SIZE = 1M;

MEMORY {
    RAM (rwx)    : ORIGIN = MEM_BASE, LENGTH = MEM_SIZE    
}

SECTIONS {

	.boot : {
		*(.boot)
	} 

 	.text :  {
 		*(.text)
 	} 
 
 	.rodata :  {
 		*(.rodata)
 	}
 
    .test_table :  {
        _test_table = .;
        *(.test_table)
        _test_table_end = .;
    }
    _test_table_size = (_test_table_end - _test_table) / XLEN_BYTES;
 	
 	.data : {
 		*(.data)
 	}
 
 	.tohost ALIGN(0x1000) :  {
 		*(.tohost)
 	}
 
 	.bss ALIGN(0x1000) (NOLOAD) :  {
 		__bss_start = .;
 		*(.bss) 
 		*(.sbss) 
 		*(COMMON)	
 		__bss_end = .;
 	} 
 
 	.pmp_check ALIGN(0x1000) (NOLOAD) :  {
 		__pmp_access_fault_addr = .;
 	} 

 	. = MEM_BASE + 0x1ff000;
     
     . = ALIGN(16) + STACK_SIZE;
     __stack_top = .;
     _end = .;
}
