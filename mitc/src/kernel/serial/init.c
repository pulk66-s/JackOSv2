/**
 * @file    init.c
 * @brief   Serial driver initialization
 * 
 * @details
 * This file contains all the procedure to initialize the serial port
*/

#include <include/graphics/serial.h>
#include <include/x86.h>
#include <include/types.h>

/**
 * @brief   Initialize the serial port
*/
int serial_init() {
    int serial_exists = 0;

    // Turn off the FIFO
    outb(COM1 + COM_FCR, 0);
    // Set speed; requires DLAB latch
    outb(COM1 + COM_LCR, COM_LCR_DLAB);
    outb(COM1 + COM_DLL, (uint8_t) (115200 / 9600));
    outb(COM1 + COM_DLM, 0);
    // 8 data bits, 1 stop bit, parity off; turn off DLAB latch
    outb(COM1 + COM_LCR, COM_LCR_WLEN8 & ~COM_LCR_DLAB);
    // No modem controls
    outb(COM1 + COM_MCR, 0);
    // Enable rcv interrupts
    outb(COM1 + COM_IER, COM_IER_RDI);
    // Clear any preexisting overrun indications and interrupts
    // Serial port doesn't exist if COM_LSR returns 0xFF
    serial_exists = (inb(COM1 + COM_LSR) != 0xFF);
    (void) inb(COM1 + COM_IIR);
    (void) inb(COM1 + COM_RX);

    return serial_exists;
}
