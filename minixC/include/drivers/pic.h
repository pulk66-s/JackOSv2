/**
 * @file    This file provides functions to manage the PIC
 */

#ifndef __JL_DRIVERS_PIC_H__
#define __JL_DRIVERS_PIC_H__

#include <lib.h>

/**
 * @brief           Read a byte from the PIC
 * @param   port    The port to read from
 * @return          The byte read
 */
static inline uint8_t pic_read(uint16_t port)
{
    uint8_t ret;

    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/**
 * @brief           Write a byte to the PIC
 * @param   port    The port to write to
 * @param   data    The byte to write
*/
static inline void pic_write(uint16_t port, uint8_t data)
{
    asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

/**
 * @brief           This function read a number of bytes from the given port and
 *                  store them in the given address.
 * @param   port    The port to read from
 * @param   addr    The address where to store the bytes
 * @param   size    The number of bytes to read
*/
static inline void pic_read_bytes(uint16_t port, void *addr, size_t size)
{
    asm volatile("cld\n\trepne\n\tinsl"
        : "=D"(addr), "=c"(size)
        : "d"(port), "0"(addr), "1"(size)
        : "memory", "cc"
    );
}

#endif
