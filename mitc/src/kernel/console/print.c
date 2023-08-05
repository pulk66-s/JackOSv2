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
        // for (;;);
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

    switch (c) {
        case '\n':
            console->x = 0;
            console->y++;
            break;
        case '\r':
            console->x = 0;
            break;
        case '\t':
            for (;;);
            console->x += 4;
            break;
        default:
            for (int i = 0; i < console->nb_interface; i++) {
                console->interface[i].putc(c, console->x, console->y, console->color);
            }
            console->x++;
            break;
    }
    check_newline();
}

/**
 * @brief       Print a string on the screen
 * @param   str The string to print
*/
void kcons_prints(const char *str) {
    struct console *console = get_console();

    for (int i = 0; str[i]; i++) {
        kcons_printc(str[i]);
    }
}

/**
 * @brief       Print a number on the screen
 * @param   n   The number to print
*/
void kcons_printn(int n) {
    struct console *console = get_console();
    size_t len = 0;

    for (int i = 0; i < console->nb_interface; i++) {
        console->interface[i].putn(n, console->x, console->y, console->color);
    }
    while (n != 0) {
        n /= 10;
        len++;
    }
    console->x += len;
    check_newline();
}

/**
 * @brief       Change the color of the console
 * @param   color   The new color
*/
void kcons_set_color(uint8_t color) {
    struct console *console = get_console();

    console->color = color;
}

/**
 * @brief       printf implementation for the kernel console
 * @param   fmt The format string
 * @param   ... The arguments
*/
void kcons_printf(const char *fmt, ...) {
    struct console *console = get_console();

    for (int i = 0; i < console->nb_interface; i++) {
        console->interface[i].printf(fmt, console->x, console->y, console->color);
    }
}