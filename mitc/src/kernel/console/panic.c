/**
 * @file    panic.c
 * @brief   Panic function
 * 
 * @details
 * This file handle the panic function. It's a function that will be called
 * when the kernel encounter a fatal error. It will print the error message
 * and then halt the system.
*/

#include <include/console.h>
#include <include/graphics/CGA.h>

/**
 * @brief       Panic function, it print a message and then halt the system
 * @param   str The message to print
*/
void panic(const char *str) {
    kcons_set_color(CGA_COLOR(CGA_COLOR_BLACK, CGA_COLOR_RED));
    kcons_prints("PANIC: ");
    kcons_prints(str);
    asm volatile("cli");
    asm volatile("hlt");
    for (;;);
}
