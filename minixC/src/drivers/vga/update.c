#include <drivers/vga.h>

/**
 * @brief       This function clean the screen.
*/
void vga_clear(struct vga *vga)
{
    uint8_t *buff = vga->buffer;

    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        buff[i * 2] = ' ';
        buff[i * 2 + 1] = 0x00;
    }
}
