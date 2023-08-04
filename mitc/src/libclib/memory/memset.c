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
void memset(void *ptr, uint8_t value, size_t size) {
    uint8_t *p = (uint8_t *)ptr;

    for (size_t i = 0; i < size; i++)
        p[i] = value;
}