#ifndef __JOS_INC_DRIVERS_VGA_DATA_H__
#define __JOS_INC_DRIVERS_VGA_DATA_H__

#include <lib/types.h>

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_BUFFER  0xB8000

#define VGA_COLOR(fg, bg)   ((bg << 4) | fg)

enum vga_color {
    VGA_COLOR_BLACK         = 0,
    VGA_COLOR_BLUE          = 1,
    VGA_COLOR_GREEN         = 2,
    VGA_COLOR_CYAN          = 3,
    VGA_COLOR_RED           = 4,
    VGA_COLOR_MAGENTA       = 5,
    VGA_COLOR_BROWN         = 6,
    VGA_COLOR_LIGHT_GREY    = 7,
    VGA_COLOR_DARK_GREY     = 8,
    VGA_COLOR_LIGHT_BLUE    = 9,
    VGA_COLOR_LIGHT_GREEN   = 10,
    VGA_COLOR_LIGHT_CYAN    = 11,
    VGA_COLOR_LIGHT_RED     = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN   = 14,
    VGA_COLOR_WHITE         = 15,
};

void init_vga(void);

#endif
