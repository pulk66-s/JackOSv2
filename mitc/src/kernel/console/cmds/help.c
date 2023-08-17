/**
 * @file    help.c
 * @brief   Display the help
 *
 * @details
 * This file contains the help command implementation
 * ! This command works only on the kernel console
*/

#include <include/console.h>

/**
 * @brief   Display the help
 * @param   argv    The arguments
*/
void help_cmd(__attribute__((unused)) char **argv) {
    struct command *cmds = get_commands();

    kcons_prints("Available commands:\n");
    for (size_t i = 0; i < NB_COMMANDS; i++) {
        kcons_prints(cmds[i].name);
        kcons_prints("\t\t");
        kcons_prints(cmds[i].description);
        kcons_prints("\n");
    }
}