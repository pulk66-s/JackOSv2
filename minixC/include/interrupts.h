/**
 * @brief   This file containss everything related to interrupts
 * and interrupt handlers.
*/

#ifndef __JOS_INTERRUPTS_H__
#define __JOS_INTERRUPTS_H__

#include <lib/types.h>
#include <interrupts/data.h>
#include <interrupts/isr.h>

/**
 * @brief       This file handles the interrupt request.
 * @param   nb  The number of the interrupt.
*/
extern void exception_handler(uint8_t nb);

/**
 * @brief       Setup the interrupt descriptor table.
*/
void idt_setup();

#endif
