/**
 * @file    print.c
 * @brief   CGA print functions
 * 
 * @details
 * This file handle all the print functions for the CGA driver.
*/

#include <include/graphics/CGA.h>
#include <include/clib/string.h>

// CGA buffer
static uint8_t *cga_buffer = NULL;

static inline void put_char_in_buffer(char c, uint8_t x, uint8_t y, uint8_t color) {
    cga_buffer[(y * CGA_WIDTH * 2) + x] = c;
    cga_buffer[(y * CGA_WIDTH * 2) + x + 1] = color;
}

/**
 * @brief           Print a character on the screen
 * @param   c       The character to print
 * @param   x       The x position of the character
 * @param   y       The y position of the character
 * @param   color   The color of the character
*/
void cga_putc(char c, uint8_t x, uint8_t y, uint8_t color) {
    if (!cga_buffer)
        return;
    switch (c) {
        case '\t':
        case '\r':
        case '\n':
        case 127:
            put_char_in_buffer(' ', x * 2, y, color);
            break;
        default:
            put_char_in_buffer(c, x * 2, y, color);
            break;
    }
}

/**
 * @brief           Print a string on the screen
 * @param   str     The string to print
 * @param   x       The x position of the string
 * @param   y       The y position of the string
 * @param   color   The color of the string
*/
void cga_puts(const char *str, uint8_t x, uint8_t y, uint8_t color) {
    if (!cga_buffer)
        return;
    for (size_t i = 0; str[i] != '\0'; i++) {
        put_char_in_buffer(str[i], x * 2 + i * 2, y, color);
    }
}

/**
 * @brief           Print a number on the screen
 * @param   num     The number to print
 * @param   x       The x position of the number
 * @param   y       The y position of the number
 * @param   color   The color of the number
*/
void cga_putn(int num, uint8_t x, uint8_t y, uint8_t color) {
    char buffer[MAX_INT_SIZE] = {0};

    if (!cga_buffer)
        return;
    itoa(num, buffer);
    cga_puts(buffer, x, y, color);
}

/**
 * @brief   Init the CGA driver
*/
void cga_init() {
    cga_buffer = (uint8_t *)CGA_BASE;
    cga_clear();
}

/**
 * @brief   Clear the screen
*/
void cga_clear() {
    if (!cga_buffer)
        return;
    for (size_t i = 0; i < CGA_WIDTH * CGA_HEIGHT; i++)
        cga_buffer[i] = 0;
}

/**
 * @brief   printf implementation for the CGA driver
 * @param   fmt     The format string
 * @param   x       The x position of the string
 * @param   y       The y position of the string
 * @param   color   The color of the string
 * @param   ...     The arguments
 * 
 * ! This function is not implemented yet, waiting for format_string function
 * ! implementation
*/
void cga_printf(const char *fmt, uint8_t x, uint8_t y, uint8_t color, ...) {
    va_list args;
    va_start(args, color);
    // const char *buff = format_string(fmt, args);

    // cga_puts(buff, x, y, color);
    va_end(args);
}