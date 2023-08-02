/**
 * @file x86.h
 * @brief The x86 interface.
 *
 * @details
 * This file contains the x86 interface. It contains the x86 specific functions.
 */

#ifndef __JOS_INCLUDE_X86_h__
#define __JOS_INCLUDE_X86_h__

#include "types.h"

/**
 * @brief   This function read the port 'port' of the PIC and return the data.
 * @param port The port to read.
 * @return The data read from the port.
 */
static inline uint8_t inb(int port)
{
    uint8_t data;

    asm volatile("inb %w1,%0"
                 : "=a"(data)
                 : "d"(port));
    return data;
}

/**
 * @brief   This function write the data 'data' to the port 'port' of the PIC.
 * @param port The port to write.
 * @param data The data to write.
 */
static inline void outb(int port, uint8_t data)
{
    asm volatile("outb %0,%w1"
                 :
                 : "a"(data), "d"(port));
}

/**
 * @brief   This function read 'cnt' bytes from the port 'port' and write it to
 * the address 'addr'.
 */
static inline void insl(int port, void *addr, int cnt)
{
    asm volatile("cld\n\trepne\n\tinsl"
                 : "=D"(addr), "=c"(cnt)
                 : "d"(port), "0"(addr), "1"(cnt)
                 : "memory", "cc");
}

#endif