#include <lib/mem.h>

/**
 * @brief       This function set n bytes of memory to a value.
 * @param dest  The destination.
 * @param val   The value.
 * @param n     The number of bytes to set.
*/
void memset(void *dest, int val, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        ((char *)dest)[i] = val;
    }
}
