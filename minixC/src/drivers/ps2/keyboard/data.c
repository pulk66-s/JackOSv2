#include <drivers/ps2/keyboard.h>
#include <lib/types.h>
#include <drivers/vga.h>

static char buff[MAX_KEYS_BUFFER] = {0};
static uint8_t buff_idx = 0;

/**
 * @brief       Add a key to the linked list.
 * @param   c   The character to add.
*/
void keyboard_keys_list_add(char c)
{
    buff[buff_idx++] = c;
}

/**
 * @brief       Get the first key in the linked list.
 * @return      The first key in the linked list.
*/
inline char keyboard_keys_list_get(void)
{
    char c = buff[buff_idx];

    buff[buff_idx] = '\0';
    if (buff_idx > 0) {
        buff_idx--;
    }
    return c;
}
