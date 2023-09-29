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
    for (size_t i = 0; i < TTY_MAX_PROMPT_SIZE; tty->prompt[i++] = '\0');
    tty->prompt[0] = '$';
    tty->prompt[1] = '>';
    tty->prompt[2] = ' ';
    tty->prompt[3] = '\0';
}

/**
 * @brief           Launch the tty
 * @param   tty     The tty to launch
*/
void launch_tty(struct tty *tty)
{
    tty_putstr(tty, tty->prompt);
    for (;;) {
        
    }
}
