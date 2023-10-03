#ifndef __JOS_INC_DRIVERS_TTY_INPUT_H__
#define __JOS_INC_DRIVERS_TTY_INPUT_H__

/**
 * @brief       Read a line from the keyboard.
 * @param   tty The tty to read from.
 * @return      The line read.
*/
void tty_readline(struct tty *tty, char *buff);

#endif
