#include <drivers/vga.h>
#include <lib/string.h>

/**
 * @brief       This function print a char on the screen.
 * @param   c   The char to print.
*/
void vga_putc(struct vga *core, char c)
{
    switch (c) {
    case '\n':
        core->x = 0;
        core->y++;
        break;
    default:
        core->buffer[core->y * VGA_WIDTH * 2 + core->x * 2] = c;
        core->buffer[core->y * VGA_WIDTH * 2 + core->x * 2 + 1] = core->color;
        core->x++;
        break;
    }
}

/**
 * @brief       This function print a string on the screen.
 * @param   s   The string to print.
*/
void vga_print(struct vga *core, const char *s)
{
    for (size_t i = 0; s[i]; i++) {
        vga_putc(core, s[i]);
    }
}

/**
 * @brief       This function print a string on the screen and add a new line.
 * @param   s   The string to print.
*/
void vga_println(struct vga *core, const char *s)
{
    vga_print(core, s);
    vga_putc(core, '\n');
}

/**
 * @brief       This function print a number on the screen.
 * @param   n   The number to print.
*/
void vga_printn(struct vga *core, int n)
{
    char buf[32] = {0};

    itoa(n, buf);
    vga_print(core, buf);
}

