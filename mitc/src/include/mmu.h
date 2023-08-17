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

// A linear address 'la' has a three-part structure as follows:
//
// +--------10------+-------10-------+---------12----------+
// | Page Directory |   Page Table   | Offset within Page  |
// |      Index     |      Index     |                     |
// +----------------+----------------+---------------------+
//  \--- PDX(la) --/ \--- PTX(la) --/ \---- PGOFF(la) ----/
//  \---------- PGNUM(la) ----------/
//
// The PDX, PTX, PGOFF, and PGNUM macros decompose linear addresses as shown.
// To construct a linear address la from PDX(la), PTX(la), and PGOFF(la),
// use PGADDR(PDX(la), PTX(la), PGOFF(la)).

// page number field of address (PGNUM)
#define PAGE_NUMBER(la)                     (((uintptr_t) (la)) >> PAGE_TABLE_INDEX_SHIFT)

// Page directory index
#define PAGE_DIR_INDEX(la)                  ((((uintptr_t) (la)) >> PAGE_DIRECTORY_INDEX_SHIFT) & 0x3FF)

// Page table index
#define PAGE_TABLE_INDEX(la)                ((((uintptr_t) (la)) >> PAGE_TABLE_INDEX_SHIFT) & 0x3FF)

#define PAGE_DIRECTORY_INDEX_SHIFT          22      // offset of PDX in a linear address
#define PAGE_TABLE_INDEX_SHIFT              12      // offset of PTX in a linear address

// Address in page table or page directory entry
#define PTE_ADDR(pte)	                    ((physaddr_t) (pte) & ~0xFFF)

// Control Register flags
#define CR0_PE		0x00000001	// Protection Enable
#define CR0_MP		0x00000002	// Monitor coProcessor
#define CR0_EM		0x00000004	// Emulation
#define CR0_TS		0x00000008	// Task Switched
#define CR0_ET		0x00000010	// Extension Type
#define CR0_NE		0x00000020	// Numeric Errror
#define CR0_WP		0x00010000	// Write Protect
#define CR0_AM		0x00040000	// Alignment Mask
#define CR0_NW		0x20000000	// Not Writethrough
#define CR0_CD		0x40000000	// Cache Disable
#define CR0_PG		0x80000000	// Paging

// bytes mapped by a page
#define PAGE_SIZE		                    4096
#define PAGE_SHIFT	                        12		// log2(PGSIZE)
#define PAGE_TABLE_SIZE                     (PAGE_SIZE * NB_TABLE_ENTRIES_PER_PAGE)
#define NB_TABLE_ENTRIES_PER_PAGE           1024	// page table entries per page table
#define NB_PAGE_DIRECTORY_ENTRIES_PER_PAGE	1024	// page directory entries per page directory

// size of a kernel stack
#define KERNEL_STACK_SIZE	                (8 * 32768)

// Page table/directory entry flags.
#define PTE_P                               0x001   // Page Table Entry Present
#define PTE_W                       		0x002	// Page Table Entry Writeable
#define PTE_U                               0x004   // Page Table Entry User

#endif
