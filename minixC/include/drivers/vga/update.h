#ifndef __JOS_INC_DRIVERS_VGA_UPDATE_H__
#define __JOS_INC_DRIVERS_VGA_UPDATE_H__

#include <lib/types.h>

/**
 * @brief       This function clean the screen.
*/
void vga_clear(void);

/**
 * @brief       Get a character at the given position.
 * @param   x   The x position
 * @param   y   The y position
 * @return      The character at the given position.
*/
char vga_get_char(uint8_t x, uint8_t y);

#endif
