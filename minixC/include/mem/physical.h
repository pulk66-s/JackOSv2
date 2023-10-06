/**
 * @brief   This file contains all the physical memory management functions,
 * It manages the physical memory using blocks
*/

#ifndef __JOS_INC_MEM_PHYSICAL_H__
#define __JOS_INC_MEM_PHYSICAL_H__

#include <lib/types.h>

/**
 * @brief           The physical memory management block structure
 * @param   start   The start address of the block
 * @param   size    The size of the block
*/
void init_physical_memory(phys_addr start, size_t size);

/**
 * @brief           Allocate a block of physical memory
 * @param   size    The size of the block
 * @return          The start address of the block
*/
phys_addr *alloc_physical_block(size_t size);

/**
 * @brief           Free a block of physical memory
 * @param   block   The start address of the block
 * @param   size    The size of the block
*/
void free_physical_block(phys_addr *block, size_t size);

#endif
