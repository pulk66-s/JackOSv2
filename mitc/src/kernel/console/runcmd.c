/**
 * @file    runcmd.c
 * @brief   Run the user command
*/

#include <include/console.h>
#include <include/graphics/CGA.h>
#include <include/clib/string.h>

#define MAX_BUFFER 1024
char buff[MAX_BUFFER];
char prompt[] = "KJOS> ";

void help_cmd(char **argv);

static struct Command cmds[NB_COMMANDS] = {
    { "help", "Display this list of commands",  help_cmd},
    { "nvram", "Display the NVRAM informations",  nvram_cmd},
};

/**
 * @brief           Get all the commands informations
 * @return          all the commands
*/
struct Command *get_commands(void) {
    return cmds;
}


/**
 * @brief           Get the line from the user
 * @param   console The console
*/
static void getline(struct console *console) {
    char c;
    size_t i = 0;

    while ((c = console->input_interface.getc()) != '\r') {
        if (c == 127) {
            if (i > 0) {
                buff[--i] = 0;
                kcons_printc(c);
            }
        } else {
            buff[i++] = c;
            kcons_printc(c);
        }
    }
}

/**
 * @brief       Parse a command
 * @param   cmd The command to parse
*/
static void parsecmd(char *cmd) {
    for (size_t i = 0; i < NB_COMMANDS; i++) {
        if (strcmp(cmd, cmds[i].name) == 0) {
            cmds[i].func(NULL);
            return;
        }
    }
    kcons_prints(cmd);
    kcons_prints(": Command not found\n");
}

/**
 * @brief       Run the command given by the user
*/
void runcmd(void) {
    struct console *console = get_console();
    char c;

    if (!console->input_interface.getc) {
        panic("No input interface");
    }
    while (1) {
        kcons_prints(prompt);
        for (int i = 0; i < MAX_BUFFER; i++) {
            buff[i] = 0;
        }
        getline(console);
        kcons_prints("\n");
        parsecmd(buff);
    }
    kcons_prints("Command not found\n");
}
