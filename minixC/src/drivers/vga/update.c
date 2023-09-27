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
