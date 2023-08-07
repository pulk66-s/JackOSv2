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
        .output_interface = {
            [0] = (struct console_interface) {
                .init = cga_init,
                .clear = cga_clear,
                .putc = cga_putc,
                .puts = cga_puts,
                .putn = cga_putn,
                .printf = cga_printf,
            }
        },
        .input_interface = {
            .getc = NULL,
        }
    };
}

/**
 * @brief       Init the console
*/
void console_init(struct console_interface *choosed) {
    init_cga_console();
    if (choosed) {
        console.output_interface[0] = *choosed;
    }
    console.nb_interface++;
    console.output_interface[0].init();
}

/**
 * @brief   Get the console
 * @return  The console
*/
struct console *get_console(void) {
    return &console;
}

/**
 * @brief           Add a console interface to the console
 * @param   inter   The console interface to add
*/
void console_add_output_interface(struct console_interface *inter) {
    console.output_interface[console.nb_interface++] = *inter;
}

/**
 * @brief           Set the input interface of the console
 * @param   inter   The input interface to set
*/
void console_set_input_interface(struct console_input_interface *inter) {
    console.input_interface = *inter;
}