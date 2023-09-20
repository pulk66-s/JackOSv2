/**
 * @file        paging.h
 * @brief       Pagination include file
 * 
 * @details
 * This file contains all the memory pagination files
*/

#ifndef __JOS_INCLUDE_MEM_PAGING_H__
#define __JOS_INCLUDE_MEM_PAGING_H__

#include "../types.h"
#include "../memlayout.h"
#include "../mmu.h"
#include "../console.h"

/**
 * @brief       Allocation flags
*/
enum allocation_flags {
    ALLOC_ZERO = 1
};

extern size_t nb_total_pages;

typedef uint32_t pte_t; // Page table entry type
typedef uint32_t pde_t; // Page directory entry type

/* This macro takes a physical address and returns the corresponding kernel
 * virtual address.  It panics if you pass an invalid physical address. */
#define KERNEL_ADDR(pa) _kaddr(pa)

static inline void* _kaddr(physaddr_t pa)
{
	if (PAGE_NUMBER(pa) >= nb_total_pages)
		panic("KADDR called with invalid pa");
	return (void *)(pa + KERNEL_BASE);
}

/**
 * @brief   Linked list that represents the page table
*/
struct page_info {
    struct page_info *link; // Next page on the free list
    size_t ref;             // Number of references to this page
};

/**
 * @brief               Initialize the pagination system
 * @param    nb_pages   Number of pages to allocate
 * @return              0 on success, -1 on error
*/
void pagination_init(size_t nb_pages);

/**
 * @brief           Map a virtual paged region to a physical region
 * @param   pgdir   Page directory to map the region
 * @param   va      Virtual starting address
 * @param   size    Size of the region
 * @param   pa      Physical starting address
 * @param   perm    Permissions of the region
*/
void page_map_region(pde_t *pgdir, uintptr_t va, size_t size, physaddr_t pa, int perm);

/**
 * @brief           Allocate a page with the flags
 * @param   flags   Flags of the page
 * @return          struct page_info that describe the page, NULL on error
*/
struct page_info *page_alloc(int flags);

/**
 * @brief           Free the given page
 * @param   pp      Page to free
*/
void page_free(struct page_info *pp);

/**
 * @brief           Decrement the amount of ref of the page. If ref == 0, free the page
 * @param   pp      Page to decrement the ref
*/
void page_decref(struct page_info *pp);

/**
 * @brief       Return the physical address of the page
 * @param   pp  Page to get the physical address
 * @return      Physical address of the page
*/
physaddr_t page_to_phys_addr(struct page_info *pp);

/**
 * @brief       Return the page info of the physical address
 * @param   pa  Physical address
 * @return      Page info of the physical address
*/
struct page_info *phys_addr_to_page(physaddr_t pa);

/**
 * @brief       Return kernel virtual address of a page info
 * @param   pp  Page info to get the kernel virtual address
 * @return      A pointer to the kernel virtual address of the page info
*/
void *page_to_kernel_vaddr(struct page_info *pp);

/**
 * @brief           Return the corresponding page table entry of the virtual address
 * @param   pgdir   Page directory to get the page table entry
 * @param   va      Virtual address to get the page table entry
 * @param   create  If create == 1, create the page table entry if it doesn't exist
 * @return          The corresponding page table entry of the virtual address
*/
pte_t *pgdir_walk(pde_t *pgdir, const void *va, int create);

/**
 * @brief           Map the region [va, va + size) to physical address [pa, pa + size)
 *                  of the given page directory
 * @param   va      Virtual starting address
 * @param   size    Size of the region
 * @param   pa      Physical starting address
 * @param   perm    Permissions of the region
*/
void page_map_region(pde_t *pgdir, uintptr_t va, size_t size, physaddr_t pa, int perm);

/**
 * @brief       Return all the pages
 * @return      All the pages
*/
struct page_info *get_all_pages(void);

#endif