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
    char c = keyboard_read();
    size_t prompt_len = strlen(tty->prompt);

    if (c == '\n') {
        for (size_t i = prompt_len; i < tty->x; i++) {
            buff[i - prompt_len] = vga_get_char(i, tty->y);
        }
        tty_newline(tty);
    } else {
        tty_putc(tty, c);
    }
}
