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
    // first address after kernel loaded from ELF file. It's a symbol given by the linker
    extern char end[];

    static char *last_addr = end;
    char *res;

    size = ROUNDUP(size, PAGE_SIZE);
    res = last_addr;
    last_addr += size;
    return res;
}
