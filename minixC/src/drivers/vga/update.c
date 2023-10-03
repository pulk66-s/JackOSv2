#include <drivers/vga.h>

/**
 * @brief       This function clean the screen.
*/
void vga_clear(void)
{
    uint8_t *buffer = (uint8_t *)VGA_BUFFER;

    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i++) {
        buffer[i] = 0;
    }
}

/**
 * @brief       Get a character at the given position.
 * @param   x   The x position
 * @param   y   The y position
 * @return      The character at the given position.
*/
char vga_get_char(uint8_t x, uint8_t y)
{
    uint8_t *buffer = (uint8_t *)VGA_BUFFER;

    return buffer[(y * VGA_WIDTH + x) * 2];
}
