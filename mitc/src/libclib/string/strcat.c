/**
 * @file    strcat.c
 * @brief   This file contains the strcat function
 * 
 * @details
 * The strcat function appends a copy of the source string to the destination string.
*/

#include <include/clib/string.h>

/**
 * @brief       Concatenate two strings
 * @param dest  The destination string
 * @param src   The source string
 * @return      The destination string
*/
char *strcat(char *dest, const char *src) {
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';
    return dest;
}