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
    tty->display = display;
    tty->x = 0;
    tty->y = 0;
    tty->color = 0x0F;
    for (size_t i = 0; i < TTY_MAX_PROMPT_SIZE; tty->prompt[i++] = '\0');
    tty->prompt[0] = '$';
    tty->prompt[1] = '>';
    tty->prompt[2] = ' ';
    tty->prompt[3] = '\0';
    for (size_t i = 0; i < TTY_MAX_BUFF_SIZE; tty->buff[i++] = '\0');
}

/**
 * @brief           Launch the tty
 * @param   tty     The tty to launch
*/
void launch_tty(struct tty *tty)
{
    tty->display.clear();
    tty_putstr(tty, tty->prompt);
    for (;;) {
        char buff[TTY_MAX_BUFF_SIZE] = {0};

        tty_readline(tty, buff);
        tty_launch_command(tty, buff);
        tty_newline(tty, 1);
    }
}
