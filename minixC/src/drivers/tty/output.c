#include <drivers/tty/output.h>
#include <lib/string.h>

/**
 * @brief       Output a character on the screen with the tty
 * @param   tty The tty to use
 * @param   c   The character to output
*/
void tty_putc(struct tty *tty, char c)
{
    tty->display.display_char(tty->x, tty->y, tty->color, c);
    tty->x++;
}

/**
 * @brief       Output a string on the screen with the tty
 * @param   tty The tty to use
 * @param   str The string to output
*/
void tty_putstr(struct tty *tty, const char *str)
{
    tty->display.display_string(tty->x, tty->y, tty->color, str);
    tty->x += strlen(str);
}

/**
 * @brief       Output a number on the screen with the tty
 * @param   tty The tty to use
 * @param   nb  The number to output
*/
void tty_putnb(struct tty *tty, int nb)
{
    char str[11] = {0};

    itoa(nb, str, 10);
    tty_putstr(tty, str);
}

/**
 * @brief       Output a newline on the screen with the tty
 * @param   tty The tty to use
 * @param   nb  The number to output
*/
void tty_newline(struct tty *tty)
{
    tty->x = 0;
    tty->y++;
    tty_putstr(tty, tty->prompt);
}
