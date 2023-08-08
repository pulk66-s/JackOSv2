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
#include "types.h"

/**
 * @brief   Initiate the memory management
*/
void mem_init(void);

#endif