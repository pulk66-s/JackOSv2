#include <drivers/tty.h>
#include <mem.h>
#include <lib/string.h>

/**
 * @brief           Init the tty
 * @param   tty     The tty to init
 * @param   display The display interface
*/
void init_tty(struct tty *tty, struct tty_print_interface display)
{
    tty->display = (struct tty_print_interface) {
        .clear          = RELOC_KERNEL(display.clear),
        .display_char   = RELOC_KERNEL(display.display_char),
        .display_int    = RELOC_KERNEL(display.display_int),
        .display_string = RELOC_KERNEL(display.display_string),
    };
    tty->x = 0;
    tty->y = 0;
    tty->color = VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    tty->display.clear();
}

/**
 * @brief           Launch the tty
 * @param   tty     The tty to launch
*/
void launch_tty(struct tty *tty)
{
    char prompt[] = "JOS> ";

    tty->display.display_string(0, 0, tty->color, prompt);
    for (;;) {
        
    }
}
