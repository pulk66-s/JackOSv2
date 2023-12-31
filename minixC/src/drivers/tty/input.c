#include <drivers/tty.h>
#include <drivers/ps2/keyboard.h>
#include <lib/string.h>

/**
 * @brief           Read a line from the keyboard.
 * @param   tty     The tty to read from.
 * @return          The line read.
*/
void tty_readline(struct tty *tty, char *buff)
{
    size_t save_x = tty->x, save_y = tty->y;
    char c = 0;
    size_t prompt_len = strlen(tty->prompt);

    while (1) {
        c = keyboard_read();
        switch (c) {
        case '\b':
            if (tty->x > prompt_len) {
                tty->x--;
                tty->display.display_char(tty->x, tty->y, tty->color, ' ');
            }
            break;
        case '\n':
            for (size_t i = prompt_len; i < tty->x; i++) {
                buff[i - prompt_len] = tty->display.get_char(i, tty->y);
            }
            tty_newline(tty, 0);
            return;
        default:
            tty_putc(tty, c);
            break;
        }
    }
}
