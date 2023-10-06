/**
 * @file    include/mem/paging/data.h
 * @brief   This file contains all the paging informations
*/

#ifndef __JOS_INC_MEM_PAGING_DATA_H__
#define __JOS_INC_MEM_PAGING_DATA_H__

#include <lib/types.h>

/**
 * @brief       Page table descriptions
*/

// Size of a page in bytes (4KB)
#define PAGE_SIZE       4096

// Number of page table entries per page table
#define PTE_PER_PT      1024

// Page Table Entry
typedef uint32_t pte_t;

// Flags for page table, not every flags are here
typedef enum {
    // Present bit in a page table,
    // Check if the page is present in physical memory
    PTE_PRESENT     = 1 << 0,

    // Read/Write bit in a page table,
    // 0 = read-only, 1 = read/write
    PTE_READ_WRITE  = 1 << 1,

    // User/Supervisor bit in a page table,
    // 0 = supervisor, 1 = user
    PTE_USER        = 1 << 2,
} PAGE_TABLE_FLAGS;

// A page table, can handle PTE_PER_PT * PAGE_SIZE bytes (4MB for now)
struct page_table {
    pte_t entries[PTE_PER_PT];
};

// A page directory, can handle PTE_PER_PT pages (4GB for now)

/**
 * @brief       Page Directory Descriptions
*/

/**
 * A page directory entry (PDE) is 32 bits, and is structured as follows (for 4KB pages):
 * 31      22 21    12 11      9         8       7         6         1
 * +---------+---------+--------+---------+-------+---------+---------+
 * | PT Addr | PD Addr | OS AVL | Ignored | Psize | Ignored | Present |
 * +---------+---------+--------+---------+-------+---------+---------+
 * - Bits 31-22:    Page table base address
 * - Bits 22-12:    Page directory base address
 * - Bits 11-9:     Available for OS use (JOS doesn't use them)
 * - Bit 8:         Ignored
 * - Bit 7:         Page size (0 = 4KB, 1 = 4MB)
 * - Bit 6-1:       Ignored (Usefull but not used in JOS)
 * - Bit 0:         Present (1 = present, 0 = not present)
*/

// Offset of the Page directory entry in the page directory
#define PDE_OFFSET      22
// Mask to limit the page directory entry to the max nb of bits (1023)
#define PDE_MASK        0x3FF

// Offset of the Page table entry in the page table
#define PTE_OFFSET      12

// Number of page tables per page directory
#define PTE_PER_PD      1024

// Page Directory Entry
typedef uint32_t pde_t;

// Flags for page directory, not every flags are here
typedef enum {
    // Present bit in a page table,
    // Check if the page is present in physical memory
    PDE_PRESENT     = 1 << 0,

    // Read/Write bit in a page table,
    // 0 = read-only, 1 = read/write
    PDE_READ_WRITE  = 1 << 1,

    // User/Supervisor bit in a page table,
    // 0 = supervisor, 1 = user
    PDE_USER        = 1 << 2,

    // Page size bit in a page table,
    // 0 = 4KB, 1 = 4MB
    PDE_PAGE_SIZE   = 1 << 7,
} PAGE_DIR_FLAGS;

// A page directory, can handle PTE_PER_PT pages (4GB for now)
struct page_directory {
    pde_t entries[PTE_PER_PD];
};

/**
 * @brief       Memory management and conversions
*/

// Set a flag in a page table entry
#define SET_FLAG(entry, flag)   (*entry |= flag)

// Unset a flag in a page table entry
#define UNSET_FLAG(entry, flag) (*entry &= ~flag)
 
// Test a flag
#define TEST_FLAG(entry, flag)  (*entry & flag)

// Convert a virtual address into a page directory index
#define VADDR_TO_PDX(vaddr) (vaddr >> PDE_OFFSET)

// convert a virtual address into a page table index
#define VADDR_TO_PTX(vaddr) (vaddr >> PTE_OFFSET & PDE_MASK)

// Convert a table entry into a physical address
// ~0xFFF is used to remove the bits 11-0 of the address
// And get only the bits 31-12 which are the PTE addr
#define PTE_TO_ADDR(pde)    ((*pde) & ~0xFFF)

// Set an address to a page directory entry 
#define SET_PTE_ADDR(entry, addr) (*entry = (*entry & ~0x7FFFF000) | addr)

// Type to be clear that the curr addr is a physical one
typedef uint32_t physical_address;

// Type to be clear that the curr addr is a virtual one
typedef uint32_t virtual_address;

#endif
