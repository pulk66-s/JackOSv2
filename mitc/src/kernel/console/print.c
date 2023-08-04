/**
 * @file    print.c
 * @brief   Print functions
 * 
 * @details
 * This file contains all the functions that print on the kernel console
*/

#include <include/console.h>
#include <include/clib/string.h>

static inline void check_newline(void) {
    struct console *console = get_console();

    if (console->x >= console->width) {
        console->x = 0;
        console->y++;
    }
}

/**
 * @brief       Print a character on the screen
 * @param   c   The character to print
*/
void kcons_printc(char c) {
    struct console *console = get_console();

    console->interface.putc(c, console->x, console->y, console->color);
    console->x++;
    check_newline();
}

/**
 * @brief       Print a string on the screen
 * @param   str The string to print
*/
void kcons_prints(const char *str) {
    struct console *console = get_console();

    console->interface.puts(str, console->x, console->y, console->color);
    console->x += strlen(str);
    check_newline();
}

/**
 * @brief       Print a number on the screen
 * @param   n   The number to print
*/
void kcons_printn(int n) {
    struct console *console = get_console();
    size_t len = 0;

    console->interface.putn(n, console->x, console->y, console->color);
    while (n != 0) {
        n /= 10;
        len++;
    }
    console->x += len;
    check_newline();
}