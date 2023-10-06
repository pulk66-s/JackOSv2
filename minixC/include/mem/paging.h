/**
 * @file    include/mem/paging.h
 * @brief   Paging functions for the kernel
*/

/**
 * @details
 * 
 * The paging system is a way to map virtual addresses to physical addresses.
 * In the JOS kernel, we are using a two-level paging system. The first level
 * is a page directory, which contains 1024 page directory entries (PDEs). Each
 * PDE points to a page table, which contains 1024 page table entries (PTEs).
 * So in total, we have 1024 * 1024 = 1048576 virtual addresses (1048577 but the
 * first one is reserved as the parent directory) and 1048576 physical pages.
 * 
*/

#ifndef __INC_MEM_PAGING_H__
#define __INC_MEM_PAGING_H__

#include "paging/data.h"

/**
 * @brief   Initialize the paging system
 * @return  1 if the paging system is initialized successfully, 0 otherwise
*/
int paging_init(void);

/**
 * @brief               Get the page directory entry from a virtual address and a page directory
 * @param   page_dir    The page directory to get the entry from
 * @param   vaddr       The virtual address to get the entry from
 * @return              The page directory entry
*/
pde_t *get_pde(struct page_directory *page_dir, virtual_address vaddr);

/**
 * @brief               Get the page table entry from a virtual address and a page table
 * @param   page_table  The page table to get the entry from
 * @param   vaddr       The virtual address to get the entry from
 * @return              The page table entry
*/
pte_t *get_pte(struct page_table *page_table, virtual_address vaddr);

/**
 * @brief           Allocate a page of memory
 * @param   page    The page table entry to allocate
 * @return          The physical address of the allocated page
*/
void *alloc_page(pte_t *page);

/**
 * @brief           Free a page of memory
 * @param   page    The page table entry to free
*/
void free_page(pte_t *page);


/**
 * @brief       Set the current page directory
 * @param pd    The page directory to set
 * @return      1 if the page directory is set successfully, 0 otherwise
*/
int set_page_directory(struct page_directory *pd);

/**
 * @brief       Map a virtual address to a physical address
 * @param   pa  The physical address to map
 * @param   va  The virtual address to map
 * @return      1 if the virtual address is mapped successfully, 0 otherwise
*/
int map_page(physical_address pa, virtual_address va);

#endif
