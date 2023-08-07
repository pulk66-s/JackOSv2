/**
 * @file    serial.h
 * @brief   Serial port driver
 * 
 * @details
 * This file contains all the serial graphics driver functions.
 * It contains all the function that are needed to initialize and use the serial port.
*/

#ifndef __JOS_INCLUDE_SERIAL_H__
#define __JOS_INCLUDE_SERIAL_H__

#include <include/types.h>

/***** Serial I/O code *****/

#define COM1		0x3F8

#define COM_RX		0   	    // In:	Receive buffer (DLAB=0)
#define COM_TX		0   	    // Out: Transmit buffer (DLAB=0)
#define COM_DLL		0   	    // Out: Divisor Latch Low (DLAB=1)
#define COM_DLM		1   	    // Out: Divisor Latch High (DLAB=1)

#define COM_IER     1	        // Out: Interrupt Enable Register
#define   COM_IER_RDI	0x01	//   Enable receiver data interrupt

#define COM_IIR		2	        // In:	Interrupt ID Register
#define COM_FCR		2	        // Out: FIFO Control Register

#define COM_LCR		3	        // Out: Line Control Register
#define	  COM_LCR_DLAB	0x80	//   Divisor latch access bit
#define	  COM_LCR_WLEN8	0x03	//   Wordlength: 8 bits

#define COM_MCR		4	        // Out: Modem Control Register
#define	  COM_MCR_RTS	0x02	// RTS complement
#define	  COM_MCR_DTR	0x01	// DTR complement
#define	  COM_MCR_OUT2	0x08	// Out2 complement

#define COM_LSR		5	        // In:	Line Status Register
#define   COM_LSR_DATA	0x01	//   Data available
#define   COM_LSR_TXRDY	0x20	//   Transmit buffer avail
#define   COM_LSR_TSRE	0x40	//   Transmitter off

/**
 * @brief   Initialize the serial port
*/
int serial_init();

typedef uint8_t serial_color_t;

/**
 * @brief       Print a char on the serial port
 * @param c     The char to print
 * ! params x, y and color are not used but are here to be compatible with the 
 * ! kernel console interface
*/
void serial_putc(
    char c,
    __attribute__((unused)) uint8_t x,
    __attribute__((unused)) uint8_t y,
    __attribute__((unused)) serial_color_t color
);

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
);

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
);

/**
 * @brief   Clear the serial port
 * ! Do nothing, only here to be compatible with the kernel console interface
*/
void serial_clear();

/**
 * @brief       printf implementation for the serial port
 * @param   fmt The format string
 * @param   ... The arguments
 * ! params x, y and color are not used but are here to be compatible with the
 * ! kernel console interface
*/
void serial_printf(
    const char *fmt,
    __attribute__((unused)) uint8_t x,
    __attribute__((unused)) uint8_t y,
    __attribute__((unused)) serial_color_t color,
    ...
);

/**
 * @brief   Get a char from the serial port
 * @return  The char
*/
char serial_getc();

#endif