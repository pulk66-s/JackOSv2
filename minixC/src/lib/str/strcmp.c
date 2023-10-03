#include <lib/string.h>

/**
 * @brief           Compare two strings
 * @param   s1      The first string
 * @param   s2      The second string
 * @return          0 if the strings are equal, a negative number if s1 is less than s2, a positive number otherwise
 */
int strcmp(const char *s1, const char *s2)
{
    size_t i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i]) {
        i++;
    }
    return s1[i] - s2[i];
}
