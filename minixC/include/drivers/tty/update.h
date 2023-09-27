#ifndef __JOS_INC_DRIVERS_TTY_UPDATE_H__
#define __JOS_INC_DRIVERS_TTY_UPDATE_H__

#include <drivers/tty/data.h>

/**
 * @brief           Init the tty
 * @param   tty     The tty to init
 * @param   display The display interface
*/
void init_tty(struct tty *tty, struct tty_print_interface display);

/**
 * @brief           Launch the tty
 * @param   tty     The tty to launch
*/
void launch_tty(struct tty *tty);

#endif
