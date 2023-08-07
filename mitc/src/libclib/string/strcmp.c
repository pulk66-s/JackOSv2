/**
 * @file        strcmp.c
 * @brief       Compare two strings
 * 
 * @details
 * This file contains the implementation of the strcmp function
*/

#include <include/clib/string.h>

/**
 * @brief       Compare two strings
 * @param str1  The first string
 * @param str2  The second string
 * @return      0 if the strings are equal, a negative number if str1 < str2, a positive number if str1 > str2
*/
int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}