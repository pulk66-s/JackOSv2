/**
 * @file    CGA.h
 * @brief   CGA graphics mode
 * 
 * @details This file contains the definition of the CGA graphics mode.
*/

#ifndef __JOS_INCLUDE_GRAPHICS_CGA_H__
#define __JOS_INCLUDE_GRAPHICS_CGA_H__

#include <include/types.h>
#include <include/memlayout.h>

// CGA Buffer Address, we are adding KERNEL_BASE because we hare using a
// virtual memory system
#define CGA_BASE        (uint8_t *)(0xB8000 + KERNEL_BASE)
#define CGA_WIDTH       80
#define CGA_HEIGHT      25

// All CGA colors
enum CGA_COLOR {
    CGA_COLOR_BLACK         = 0,
    CGA_COLOR_BLUE          = 1,
    CGA_COLOR_GREEN         = 2,
    CGA_COLOR_CYAN          = 3,
    CGA_COLOR_RED           = 4,
    CGA_COLOR_MAGENTA       = 5,
    CGA_COLOR_BROWN         = 6,
    CGA_COLOR_LIGHT_GREY    = 7,
    CGA_COLOR_DARK_GREY     = 8,
    CGA_COLOR_LIGHT_BLUE    = 9,
    CGA_COLOR_LIGHT_GREEN   = 10,
    CGA_COLOR_LIGHT_CYAN    = 11,
    CGA_COLOR_LIGHT_RED     = 12,
    CGA_COLOR_LIGHT_MAGENTA = 13,
    CGA_COLOR_LIGHT_BROWN   = 14,
    CGA_COLOR_WHITE         = 15,
};

// Macro to create a CGA color with a foreground and background color
#define CGA_COLOR(fg, bg) ((bg << 4) | fg)

// Type to represents a CGA color
typedef uint8_t cga_color_t;

/**
 * @brief           Print a character on the screen
 * @param   c       The character to print
 * @param   x       The x position of the character
 * @param   y       The y position of the character
 * @param   color   The color of the character
*/
void cga_putc(char c, uint8_t x, uint8_t y, cga_color_t color);

/**
 * @brief           Print a string on the screen
 * @param   str     The string to print
 * @param   x       The x position of the string
 * @param   y       The y position of the string
 * @param   color   The color of the string
*/
void cga_puts(const char *str, uint8_t x, uint8_t y, cga_color_t color);

/**
 * @brief           Print a number on the screen
 * @param   num     The number to print
 * @param   x       The x position of the number
 * @param   y       The y position of the number
 * @param   color   The color of the number
*/
void cga_putn(int num, uint8_t x, uint8_t y, cga_color_t color);

/**
 * @brief   Init the CGA driver
*/
void cga_init();

/**
 * @brief   Clear the screen
*/
void cga_clear();

#endif