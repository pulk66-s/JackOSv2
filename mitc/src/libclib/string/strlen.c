/**
 * @file    strlen.c
 * @brief   strlen function implementation
 *
 * @details
 * The strlen() function calculates the length of the string pointed to by s,
*/

#include <include/clib/string.h>

size_t strlen(const char *s)
{
    size_t len = 0;

    while (s[len])
        len++;
    return len;
}
