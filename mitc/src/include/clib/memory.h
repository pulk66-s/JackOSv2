/**
 * @file    memory.h
 * @brief   Memory management functions
 * 
 * @details
 * This file contains the memory management functions.
*/

#ifndef __JOS_INCLUDE_MEMORY_H__
#define __JOS_INCLUDE_MEMORY_H__

#include "../types.h"

/**
 * @brief           Set a block of memory to a specific value
 * @param   ptr     The pointer to the block of memory
 * @param   value   The value to set
 * @param   size    The size of the block of memory
*/
void memset(void *ptr, uint8_t value, size_t size);

#endif