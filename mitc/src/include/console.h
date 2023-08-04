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

struct console_interface {
    void (*init)(void);
    void (*putc)(char c, uint8_t x, uint8_t y, uint8_t color);
    void (*puts)(const char *str, uint8_t x, uint8_t y, uint8_t color);
    void (*putn)(int n, uint8_t x, uint8_t y, uint8_t color);
    void (*clear)(void);
};

struct console {
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    uint8_t color;
    struct console_interface interface;
};

/**
 * @brief           Init the console
 * @param   console The console to init types to init, if NULL, the CGA is used
*/
void console_init(struct console *console);

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

#endif