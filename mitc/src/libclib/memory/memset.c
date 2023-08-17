/**
 * @file    memset.c
 * @brief   Memory set
 * 
 * @details This file contains the implementation of the memory set function.
 * It's used to set a block of memory to a specific value.
*/

#include <include/clib/memory.h>

/**
 * @brief           Set a block of memory to a specific value
 * @param   ptr     The pointer to the block of memory
 * @param   value   The value to set
 * @param   size    The size of the block of memory
*/
void *
memset(void *v, int c, size_t n)
{
	char *p;
	int m;

	p = v;
	m = n;
	while (--m >= 0)
		*p++ = c;

	return v;
}
