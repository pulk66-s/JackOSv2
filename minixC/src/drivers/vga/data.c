#include <drivers/vga.h>

void init_vga(struct vga *vga)
{
    vga->buffer = (uint8_t *) VGA_BUFFER;
    vga->color = VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga->x = 0;
    vga->y = 0;
}
