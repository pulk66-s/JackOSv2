/**
 * @file    print.c
 * @brief   Serial driver print
 * 
 * @details
 * This file contains all the procedure to print on the serial port
*/

#include <include/graphics/serial.h>
#include <include/x86.h>
#include <include/clib/string.h>

/**
 * @brief       Print a char on the serial port
 * @param c     The char to print
 * @param color The color of the char
*/
void serial_putc(
    char c,
    __attribute__((unused)) uint8_t x,
    __attribute__((unused)) uint8_t y,
    __attribute__((unused)) serial_color_t color
) {
    for (int i = 0; i < 10000 && !(inb(COM1 + COM_LSR) & COM_LSR_TXRDY); i++);
    outb(COM1 + COM_TX, c);
}

/**
 * @brief       Print a string on the serial port
 * @param str   The string to print
 * ! params x, y and color are not used but are here to be compatible with the 
 * ! kernel console interface
*/
void serial_puts(
    const char *str,
    __attribute__((unused)) uint8_t x,
    __attribute__((unused)) uint8_t y,
    __attribute__((unused)) serial_color_t color
) {
    for (int i = 0; str[i] != '\0'; i++) {
        serial_putc(str[i], 0, 0, 0);
    }
}

/**
 * @brief       Print a number on the serial port
 * @param n     The number to print
 * ! params x, y and color are not used but are here to be compatible with the 
 * ! kernel console interface
*/
void serial_putn(
    int n,
    __attribute__((unused)) uint8_t x,
    __attribute__((unused)) uint8_t y,
    __attribute__((unused)) serial_color_t color
) {
    char str[MAX_INT_SIZE] = {0};

    itoa(n, str);
    serial_puts(str, 0, 0, 0);
}

/**
 * @brief   Clear the serial port
 * ! Do nothing, only here to be compatible with the kernel console interface
*/
void serial_clear() {

}

/**
 * @brief       printf implementation for the serial port
 * @param   fmt The format string
 * @param   ... The arguments
 * ! params x, y and color are not used but are here to be compatible with the
 * ! kernel console interface
 * TODO: Implement the printf function for the serial port
*/
void serial_printf(
    __attribute__((unused)) const char *fmt,
    __attribute__((unused)) uint8_t x,
    __attribute__((unused)) uint8_t y,
    __attribute__((unused)) serial_color_t color,
    ...
) {}