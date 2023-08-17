/**
 * @file    mem.h
 * @brief   Memory management
 * 
 * @details
 * This file contains the memory management functions.
 * It's initiating paging and virtual memory
*/

#ifndef __JOS_INCLUDE_MEM_H__
#define __JOS_INCLUDE_MEM_H__

#include "./mem/nvram.h"
#include "./mem/paging.h"
#include "types.h"

/**
 * @brief   Initiate the memory management
*/
void mem_init(void);

/**
 * @brief           Allocate size bytes of physical memory, returning a pointer
 *                  to the memory. The memory is rounded up to a multiple of PGSIZE.
 * @param   size    The size of the memory to allocate
 * @return          A pointer to the allocated memory
 * ! This must be used only before the paging system is implemented. Once the
 * ! paging system is implemented, you must use the "page_alloc" function.
*/
void *boot_alloc(size_t size);

#endif