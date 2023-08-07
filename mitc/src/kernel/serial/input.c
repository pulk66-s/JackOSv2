/**
 * @file    input.c
 * @brief   Input functions
 * 
 * @details
 * This file contains all the functions that handle the input on the kernel
*/

#include <include/graphics/serial.h>
#include <include/x86.h>

/**
 * @brief   Get a char from the serial port
 * @return  The char
*/
char serial_getc() {
    while (!(inb(COM1 + 5) & 1));
    return inb(COM1);
}
