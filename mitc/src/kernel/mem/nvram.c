/**
 * @file    nvram.c
 * @brief   Non-volatile RAM management
 * 
 * @details
 * This file contains the non-volatile RAM management code.
*/

#include <include/mem/nvram.h>
#include <include/x86.h>

/**
 * @brief           Read from the non-volatile RAM
 * @param    reg    The register to read from
 * @return          The value of the register
 * ?? What is mc146818?
 *  * mc146818 is a chip that is used to read from the non-volatile RAM
*/
uint32_t mc146818_read(uint32_t reg)
{
    outb(IO_RTC, reg);
    return inb(IO_RTC + 1);
}


/**
 * @brief           Read from the non-volatile RAM
 * @param    reg    The register to read from
 * @return          The value of the register
*/
uint32_t nvram_read(uint32_t reg) {
	return mc146818_read(reg) | (mc146818_read(reg + 1) << 8);
}