/**
 * @file    print.c
 * @brief   CGA print functions
 * 
 * @details
 * This file handle all the print functions for the CGA driver.
*/

#include <include/graphics/CGA.h>
#include <include/memlayout.h>
#include <include/clib/string.h>

// CGA buffer
static uint8_t *cga_buffer = NULL;

static inline void put_char_in_buffer(char c, uint8_t x, uint8_t y, cga_color_t color) {
    cga_buffer[(y * CGA_WIDTH) + x] = c;
    cga_buffer[(y * CGA_WIDTH) + x + 1] = color;
}

/**
 * @brief           Print a character on the screen
 * @param   c       The character to print
 * @param   x       The x position of the character
 * @param   y       The y position of the character
 * @param   color   The color of the character
*/
void cga_putc(char c, uint8_t x, uint8_t y, cga_color_t color) {
    if (!cga_buffer)
        return;
    put_char_in_buffer(c, x * 2, y, color);
}

/**
 * @brief           Print a string on the screen
 * @param   str     The string to print
 * @param   x       The x position of the string
 * @param   y       The y position of the string
 * @param   color   The color of the string
*/
void cga_puts(char *str, uint8_t x, uint8_t y, cga_color_t color) {
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
void cga_putn(int num, uint8_t x, uint8_t y, cga_color_t color) {
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
    if (!cga_buffer)
        return;
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
