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
#include "stdarg.h"

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

/**
 * @brief       Format a string in printf style
 * @param fmt   The format string
 * @param args  The arguments to the format string
 * @return      The formatted string
*/
char *format_string(const char *fmt, va_list args);

/**
 * @brief       Concatenate two strings
 * @param dest  The destination string
 * @param src   The source string
 * @return      The destination string
*/
char *strcat(char *dest, const char *src);

/**
 * @brief       Compare two strings
 * @param str1  The first string
 * @param str2  The second string
 * @return      0 if the strings are equal, a negative number if str1 < str2, a positive number if str1 > str2
*/
int strcmp(const char *str1, const char *str2);

#endif
