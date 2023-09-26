#include <drivers/tty.h>

/**
 * @brief       Print a character on the screen to test the boot process
 * @param   c   The character to print
*/
static void print_char(char c, int x, int y)
{
    unsigned char *video = (unsigned char *)0xb8000;
    int offset = (y * 80 + x) * 2;

    video[offset] = c;
    video[offset + 1] = 0x0F;
}

static void print_string(char *str, int x, int y)
{
    int i = 0;

    while (str[i] != '\0') {
        print_char(str[i], x + i, y);
        i++;
    }
}

void kernel_main(void)
{
    print_char('H', 10, 0);
}
