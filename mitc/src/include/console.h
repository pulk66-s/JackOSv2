/**
 * @file    console.h
 * @brief   All the kernel console functions are here
 * 
 * @details
 * This file contains all the functions that are used to print to the screen.
 * It's a kernel console used and only used by the kernel
*/

#ifndef __JOS_INCLUDE_CONSOLE_H__
#define __JOS_INCLUDE_CONSOLE_H__

#include "types.h"

#define MAX_CONSOLE_INTERFACE 10
#define NB_COMMANDS 2

struct console_interface {
    void (*init)(void);
    void (*putc)(char c, uint8_t x, uint8_t y, uint8_t color);
    void (*puts)(const char *str, uint8_t x, uint8_t y, uint8_t color);
    void (*putn)(int n, uint8_t x, uint8_t y, uint8_t color);
    void (*clear)(void);
    void (*printf)(const char *fmt, uint8_t x, uint8_t y, uint8_t color, ...);
};

struct console_input_interface {
    char (*getc)(void);
};

struct console {
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    uint8_t color;
    uint8_t nb_interface;
    struct console_interface output_interface[MAX_CONSOLE_INTERFACE];
    struct console_input_interface input_interface;
};

struct Command {
    const char *name;
    const char *description;
    void (*func)(char **argv);
};

/**
 * @brief           Init the console
 * @param   console The console to init types to init, if NULL, the CGA is used
*/
void console_init(struct console_interface *console);

/**
 * @brief   Get the console
 * @return  The console
*/
struct console *get_console(void);

/**
 * @brief       Print a character on the screen
 * @param   c   The character to print
*/
void kcons_printc(char c);

/**
 * @brief       Print a string on the screen
 * @param   str The string to print
*/
void kcons_prints(const char *str);

/**
 * @brief       Print a number on the screen
 * @param   n   The number to print
*/
void kcons_printn(int n);

/**
 * @brief           Change the color of the console
 * @param   color   The new color
*/
void kcons_set_color(uint8_t color);

/**
 * @brief       printf implementation for the kernel console
 * @param   fmt The format string
 * @param   ... The arguments
*/
void kcons_printf(const char *fmt, ...);

/**
 * @brief       Panic function, it print a message and then halt the system
 * @param   str The message to print
*/
void panic(const char *str);

/**
 * @brief           Add a console interface to the console
 * @param   inter   The console interface to add
*/
void console_add_output_interface(struct console_interface *inter);

/**
 * @brief           Set the input interface of the console
 * @param   inter   The input interface to set
*/
void console_set_input_interface(struct console_input_interface *inter);

/**
 * @brief           Run the command given by the user
*/
void runcmd(void);

/**
 * @brief           Display the help
 * @param   argv    The arguments
*/
void help_cmd(char **argv);

/**
 * @brief           Display the NVRAM
 * @param   argv    The arguments
*/
void nvram_cmd(char **argv);

/**
 * @brief           Get all the commands informations
 * @return          all the commands
*/
struct Command *get_commands(void);

#endif