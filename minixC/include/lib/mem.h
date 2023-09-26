/**
 * @file    This file contains the memory management functions.
*/

#ifndef __JOS_INCLUDE_MEM_H__
#define __JOS_INCLUDE_MEM_H__

#include <lib/types.h>

/**
 * @brief       This function copy n bytes of memory from a source to a destination.
*/
void *memcpy(void *dest, const void *src, size_t n);

#endif
