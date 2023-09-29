#ifndef __JOS_INC_DRIVERS_TTY_OUTPUT_H__
#define __JOS_INC_DRIVERS_TTY_OUTPUT_H__

#include <drivers/tty/data.h>

/**
 * @brief       Output a character on the screen with the tty
 * @param   tty The tty to use
 * @param   c   The character to output
*/
void tty_putc(struct tty *tty, char c);

/**
 * @brief       Output a string on the screen with the tty
 * @param   tty The tty to use
 * @param   str The string to output
*/
void tty_putstr(struct tty *tty, const char *str);

/**
 * @brief       Output a number on the screen with the tty
 * @param   tty The tty to use
 * @param   nb  The number to output
*/
void tty_putnb(struct tty *tty, int nb);

#endif
