/**
 * @file    revstr.c
 * @brief   revstr function implementation
 * 
 * @details
 * The revstr() function reverses the string pointed to by str.
*/

#include <include/clib/string.h>

/**
 * @brief       Reverse a string
 * @param str   The string to reverse
*/
void revstr(char *str) {
    size_t len = strlen(str);
    char tmp;

    for (size_t i = 0; i < len / 2; i++) {
        tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}
