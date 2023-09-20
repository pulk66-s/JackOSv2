/**
 * @file    boot.c
 * @brief   Memory management boot
 * 
 * @details
 * This file contains the memory management boot code. This code is used to
 * use the memory before the implementation of the paging system.
*/

#include <include/mem.h>
#include <include/console.h>
#include <include/mmu.h>
#include <include/types.h>

/**
 * @brief           Allocate size bytes of physical memory, returning a pointer
 *                  to the memory. The memory is rounded up to a multiple of PGSIZE.
 * @param   size    The size of the memory to allocate, if size == 0, then it
 *                  return the current address of the last allocated memory,
 *                  otherwise it returns the address of the next free memory
 *                  rounded up to a multiple of PAGE_SIZE.
 * @return          A pointer to the allocated memory
 * 
 * @warning
 * ! This must be used only before the paging system is implemented. Once the
 * ! paging system is implemented, you must use the "page_alloc" function.
*/
void *boot_alloc(size_t size) {
	static char *nextfree;	// virtual address of next byte of free memory
	char *result;

	if (!nextfree) {
		extern char end[];
		nextfree = ROUNDUP((char *) end, PAGE_SIZE);
	}
	if ((uint32_t)nextfree + size >= KERNEL_BASE + 0xFc00000) {
		panic("boot_alloc: out of memory\n");
	}
	result = nextfree;
	nextfree += ROUNDUP(size, PAGE_SIZE);
	return result;
}
