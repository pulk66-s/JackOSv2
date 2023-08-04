/**
 * @file    init.c
 * @brief   Initialize the kernel console
 * 
 * @details
 * This file contains all the function that initialize the kernel console
*/

#include <include/console.h>
#include <include/graphics/CGA.h>

static struct console console;

/**
 * @brief       Init the default CGA console
*/
static inline void init_cga_console(void) {
    console = (struct console) {
        .x = 0,
        .y = 0,
        .width = CGA_WIDTH,
        .height = CGA_HEIGHT,
        .color = CGA_COLOR(CGA_COLOR_WHITE, CGA_COLOR_BLACK),
        .interface = (struct console_interface) {
            .init = cga_init,
            .clear = cga_clear,
            .putc = cga_putc,
            .puts = cga_puts,
            .putn = cga_putn,
        }
    };
}

/**
 * @brief       Init the console
*/
void console_init(struct console *choosed) {
    if (choosed == NULL) {
        init_cga_console();
    } else {
        console = *choosed;
    }
    console.interface.init();
}

/**
 * @brief   Get the console
 * @return  The console
*/
struct console *get_console(void) {
    return &console;
}
