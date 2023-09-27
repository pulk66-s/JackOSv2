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
    itoa(vga_clear, res, 16);
    for (size_t x = 0; res[x]; x++) {
        vga_putc(x, 1, 0x0F, res[x]);
    }

    res[0] = 0;
    void (*clear)(void) = tty->display.clear;

    clear();
    itoa(clear, res, 16);
    for (size_t x = 0; res[x]; x++) {
        vga_putc(x, 2, 0x0F, res[x]);
    }
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
