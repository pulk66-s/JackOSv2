#ifndef __JOS_INC_DRIVERS_VGA_OUTPUT_H__
#define __JOS_INC_DRIVERS_VGA_OUTPUT_H__

#include <lib/types.h>
#include <drivers/vga/data.h>

/**
 * @brief       This function print a char on the screen.
 * @param   c   The char to print.
*/
void vga_putc(struct vga *core, char c);

/**
 * @brief       This function print a string on the screen.
 * @param   s   The string to print.
*/
void vga_print(struct vga *core, const char *s);

/**
 * @brief       This function print a string on the screen and add a new line.
 * @param   s   The string to print.
*/
void vga_println(struct vga *core, const char *s);

/**
 * @brief       This function print a number on the screen.
 * @param   n   The number to print.
*/
void vga_printn(struct vga *core, int n);

#endif
