/**
 * @file    string.h
 * @brief   String functions
 * 
 * @details
 * This file contains the definition of the string functions
 *
*/

#ifndef __JOS_CLIB_STRING_H__
#define __JOS_CLIB_STRING_H__

#include "../types.h"

#define MAX_INT_SIZE 11

/**
 * @brief       Get the length of a string
 * @param str   The string to get the length of
 * @return      The length of the string
*/
size_t strlen(const char *str);

/**
 * @brief       convert an int to a string
 * @param num   The number to convert
 * @param buff  The buffer to store the string in. It must be at least 
 *              MAX_INT_SIZE + 1 bytes long to store the string and the null terminator.
 *              It will be filled with 0s.
 * @return      The string representation of the number
*/
void itoa(int num, char *buff);

/**
 * @brief       Reverse a string
 * @param str   The string to reverse
*/
void revstr(char *str);

#endif
