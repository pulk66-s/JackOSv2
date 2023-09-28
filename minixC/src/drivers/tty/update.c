#include <drivers/tty.h>
#include <lib/string.h>

/**
 * @brief           Init the tty
 * @param   tty     The tty to init
 * @param   display The display interface
*/
void init_tty(struct tty *tty, struct tty_print_interface display)
{
    tty->display = display;
    char res[32] = {0};
    char res2[32] = {0};
    char res3[32] = {0};
    itoa((uint64_t)vga_clear, res, 16);
    for (size_t x = 0; res[x]; x++) {
        vga_putc(x, 1, 0x0F, res[x]);
    }

    itoa((uint64_t)(tty->display.clear), res2, 16);
    for (size_t x = 0; res2[x]; x++) {
        vga_putc(x, 2, 0x0F, res2[x]);
    }

    tty->display.clear = tty->display.clear - 0xF0000000;

    itoa((uint64_t)(tty->display.clear), res3, 16);
    for (size_t x = 0; res3[x]; x++) {
        vga_putc(x, 3, 0x0F, res3[x]);
    }

    // vga_clear();
    tty->display.clear();

    vga_putc(0, 4, 0x0F, 'a');
    tty->x = 0;
    tty->y = 0;
}

/**
 * @brief           Launch the tty
 * @param   tty     The tty to launch
*/
void launch_tty(struct tty *tty)
{
    char prompt[] = "JOS> ";

    tty->display.clear();
    tty->display.display_string(0, 0, VGA_COLOR(VGA_COLOR_RED, VGA_COLOR_BLUE), prompt);
    for (;;) {
        
    }
}
