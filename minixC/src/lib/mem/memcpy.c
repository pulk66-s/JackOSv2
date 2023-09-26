#include <lib/mem.h>

/**
 * @brief       This function copy n bytes of memory from a source to a destination.
*/
void *memcpy(void *dest, const void *src, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return dest;
}
