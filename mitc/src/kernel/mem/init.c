/**
 * @file    init.c
 * @brief   Memory management initialization
 * 
 * @details
 * This file contains the memory management initialization code.
*/

#include <include/mem.h>
#include <include/mmu.h>
#include <include/memlayout.h>
#include <include/console.h>
#include <include/pmap.h>
#include <include/clib/memory.h>
#include <include/x86.h>

static pde_t *kern_page_dir;
static size_t nb_pages;
extern char bootstacktop[], bootstack[];

void check_page_free_list(int only_low_memory);

/**
 * @brief   Initiate the memory management
*/
void mem_init(void) {
	uint32_t cr0;

	// We need to check the number of pages in the nvram
	nvram_init();
	nb_pages = get_nvram_nbpages();

	// Create the first kernel page directory using boot_alloc
	kern_page_dir = boot_alloc(PAGE_SIZE);
	memset(kern_page_dir, 0, PAGE_SIZE);

	//////////////////////////////////////////////////////////////////////
	// Recursively insert PD in itself as a page table, to form
	// a virtual page table at virtual address UVPT.
	// (For now, you don't have understand the greater purpose of the
	// following line.)

	// Permissions: kernel R, user R
	// TODO: Why do we need to do this ?
	kern_page_dir[PAGE_DIR_INDEX(USER_VIRT_PAGE_ADDR)] = PHYS_ADDR(kern_page_dir) | PTE_P | PTE_W;

	// Init the pagination system
	pagination_init(get_nvram_nbpages());

	check_page_free_list(1);
	// check_page_alloc();
	// check_page();

	/**
	 * Map different memory regions
	 * /////////////////////////////////////////////
	 * [UPAGES, UPAGES + PAGE_TABLE_SIZE -> [PADDR(pages), PADDR(pages) + PAGE_TABLE_SIZE]
	 * Permissions:
	 * - kernel R, user R
	 * - pages: kernel RW, user NONE
	*/
	page_map_region(kern_page_dir, UPAGES, PAGE_TABLE_SIZE, PHYS_ADDR(get_all_pages()), PTE_P | PTE_U);
	page_map_region(kern_page_dir, KSTACKTOP - KSTKSIZE, KSTKSIZE, PHYS_ADDR(bootstack), PTE_W | PTE_P);
	page_map_region(kern_page_dir, KERNEL_BASE, 0xffffffff - KERNEL_BASE, 0, PTE_W | PTE_P);
	lcr3(PHYS_ADDR(kern_page_dir));

	cr0 = rcr0();
	cr0 |= CR0_PE | CR0_PG | CR0_AM | CR0_WP | CR0_NE | CR0_MP;
	cr0 &= ~(CR0_TS | CR0_EM);
	lcr0(cr0);
}
