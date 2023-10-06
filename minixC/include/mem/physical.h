#ifndef __JOS_INC_MEM_PHYSICAL_H__
#define __JOS_INC_MEM_PHYSICAL_H__

#include <lib/types.h>

// Starting of the physical address for the physical memory
#define PHYSICAL_MEMORY_START   0x30000

// Maximum physical memory size
#define PHYSICAL_MEMORY_MAX     0x40000000

/**
 * @brief       Initialize the physical memory management
 * @param sa    The start address of the physical memory
 * @param size  The size of the physical memory
*/
void physical_mem_init(uint32_t sa, uint32_t size);

/**
 * @brief           Allocate a given numbers of blocks of physical memory
 * @param nb_blocks The numbers of blocks to allocate
 * @return          The start address of the allocated physical memory
*/
uint32_t *physical_mem_alloc(uint32_t nb_blocks);

/**
 * @brief           Free a given numbers of blocks of physical memory
 * @param address   The start address of the physical memory to free
 * @param nb_blocks The numbers of blocks to free
*/
void free_blocks(const uint32_t *address, const uint32_t num_blocks);

/**
 * @brief       Unmap a virtual address
 * @param   va  The virtual address to unmap
*/
void unmap_page(void *virt_address);

#endif
