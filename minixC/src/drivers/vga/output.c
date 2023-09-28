#include <drivers/vga.h>
#include <lib/string.h>

/**
 * @brief       This function print a char on the screen.
 * @param   x   The x position.
 * @param   y   The y position.
 * @param   cl  The color.
 * @param   c   The char to print.
*/
void vga_putc(uint8_t x, uint8_t y, uint8_t cl, char c)
{
    uint8_t *buffer = (uint8_t *)VGA_BUFFER;
    size_t offset = (VGA_WIDTH * y + x) * 2;

    buffer[offset] = c;
    buffer[offset + 1] = cl;
    x++;
}

/**
 * @brief       This function print a string on the screen.
 * @param   x   The x position.
 * @param   y   The y position.
 * @param   cl
 * @param   s   The string to print.
*/
void vga_print(uint8_t x, uint8_t y, uint8_t cl, const char *s)
{
    for (size_t i = 0; s[i]; i++) {
        vga_putc(x + i % VGA_WIDTH, y + (x + i) / VGA_WIDTH, cl, s[i]);
    }
}

/**
 * @brief       This function print a string on the screen and add a new line.
 * @param   x   The x position.
 * @param   y   The y position.
 * @param   cl
 * @param   s   The string to print.
*/
void vga_println(uint8_t x, uint8_t y, uint8_t cl, const char *s)
{
    vga_print(x, y, cl, s);
    vga_putc(x, y, cl, '\n');
}

/**
 * @brief       This function print a number on the screen.
 * @param   x   The x position.
 * @param   y   The y position.
 * @param   cl
 * @param   n   The number to print.
*/
void vga_printn(uint8_t x, uint8_t y, uint8_t cl, int n)
{
    char buf[32] = {0};

    itoa(n, buf, 10);
    vga_print(x, y, cl, buf);
}
