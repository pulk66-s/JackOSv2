#ifndef __JOS_INC_DRIVERS_TTY_CMD_H__
#define __JOS_INC_DRIVERS_TTY_CMD_H__

#include <drivers/tty/data.h>

#define NB_COMMANDS 0   // Number of existing commands

typedef int (*tty_cmd_func_t)(struct tty *tty, const char *cmd);

/**
 * @brief           Launch a tty command
 * @param   tty     The tty to launch the command on
 * @param   cmd     The command to launch
 * @return          status code
*/
int tty_launch_command(struct tty *tty, const char *cmd);

#endif
