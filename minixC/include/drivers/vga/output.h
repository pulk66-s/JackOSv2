#ifndef __JOS_INC_DRIVERS_VGA_OUTPUT_H__
#define __JOS_INC_DRIVERS_VGA_OUTPUT_H__

#include <lib/types.h>
#include <drivers/vga/data.h>

/**
 * @brief       This function print a char on the screen.
 * @param   x   The x position.
 * @param   y   The y position.
 * @param   cl  The color.
 * @param   c   The char to print.
*/
void vga_putc(uint8_t x, uint8_t y, uint8_t cl, char c);

/**
 * @brief       This function print a string on the screen.
 * @param   x   The x position.
 * @param   y   The y position.
 * @param   cl  The color.
 * @param   s   The string to print.
*/
void vga_print(uint8_t x, uint8_t y, uint8_t cl, const char *s);

/**
 * @brief       This function print a string on the screen and add a new line.
 * @param   x   The x position.
 * @param   y   The y position.
 * @param   cl  The color.
 * @param   s   The string to print.
*/
void vga_println(uint8_t x, uint8_t y, uint8_t cl, const char *s);

/**
 * @brief       This function print a number on the screen.
 * @param   x   The x position.
 * @param   y   The y position.
 * @param   cl  The color.
 * @param   n   The number to print.
*/
void vga_printn(uint8_t x, uint8_t y, uint8_t cl, int n);

#endif
