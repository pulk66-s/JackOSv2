#include <drivers/tty.h>
#include <lib/string.h>

static char *command_names[NB_COMMANDS] = {

};
static tty_cmd_func_t command_funcs[NB_COMMANDS] = {

};

/**
 * @brief           Launch the unknown command message
 * @param   tty     The tty to launch the message on
 * @return          status code
*/
static int tty_launch_unknown_command(struct tty *tty)
{
    tty->display.display_string(tty->x, tty->y, tty->color, "Unknown command");
    return 1;
}

/**
 * @brief           Launch a tty command
 * @param   tty     The tty to launch the command on
 * @param   cmd     The command to launch
 * @return          status code
*/
int tty_launch_command(struct tty *tty, const char *cmd)
{
    for (size_t i = 0; i < NB_COMMANDS; i++) {
        if (!strcmp(cmd, command_names[i])) {
            return command_funcs[i](tty, cmd);
        }
    }
    return tty_launch_unknown_command(tty);
}
