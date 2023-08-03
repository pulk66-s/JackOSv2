/**
 * @file mmu.h
 * @brief Memory management unit
 * @details
 * Memory management unit is responsible for managing the memory of the system.
 * It includes every memory related operations
 */

#ifndef __JOS_INCLUDE_MMU_h__
#define __JOS_INCLUDE_MMU_h__

/*
 * This is GDT Definition and macros
 */

#ifdef __ASSEMBLER__			// Check if we are in GAS
#define SEG_NULL \
    .word 0, 0;  \
    .byte 0, 0, 0, 0
#define SEG(type, base, lim)                        \
    .word(((lim) >> 12) & 0xffff), ((base)&0xffff); \
    .byte(((base) >> 16) & 0xff), (0x90 | (type)),  \
        (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)
#endif

/**
 * @brief   Segment Descriptor for GDT
*/

#define SEG_EXECUTABLE  0x8		// Executable segment
#define SEG_WRITABLE    0x2		// Writable segment (non-executable segment)
#define SEG_READABLE    0x2    	// Readable segment (executable segment)

/**
 * @brief   Memory paging informations
*/

// Control Register flags
#define CR0_PE                              0x00000001	// Protection Enable
#define CR0_PG                              0x80000000	// Paging
#define CR0_WP                              0x00010000	// Write Protect

// bytes mapped by a page
#define PAGE_SIZE		                    4096
#define PAGE_SHIFT	                        12		// log2(PGSIZE)
#define NB_TABLE_ENTRIES_PER_PAGE           1024	// page table entries per page table
#define NB_PAGE_DIRECTORY_ENTRIES_PER_PAGE	1024	// page directory entries per page directory

// size of a kernel stack
#define KERNEL_STACK_SIZE	                (8 * 32768)

#define PDXSHIFT	                        22      // offset of PDX in a linear address

// Page table/directory entry flags.
#define PTE_P                               0x001   // Present
#define PTE_W                       		0x002	// Writeable

#endif
