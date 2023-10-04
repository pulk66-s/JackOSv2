/**
 * @file    include/mem/kernel.h
 * @brief   This file contains the memory management before the kernel has setup
 *          the memory management system.
*/

#ifndef __INC_MEM_KERNEL_H__
#define __INC_MEM_KERNEL_H__

#include <lib/types.h>

/**
 * @brief           This function allocate a memory block of given size
 * @param   size    The size of the memory block to allocate
 * @return          The address of the allocated memory block
 * !                This function will must be used before the kernel has setup
 * !                the memory management system.
 * !                This function will panic if there is no more memory available
*/
void *kmalloc(size_t size);

#endif