/**
 * @brief   This file containss everything related to interrupts
 * and interrupt handlers.
*/

#ifndef __JOS_INTERRUPTS_H__
#define __JOS_INTERRUPTS_H__

#include <lib/types.h>
#include <interrupts/data.h>
#include <interrupts/isr.h>
#include <arch/x86.h>

/**
 * @brief       This file handles the interrupt.
 * @param   nb  The number of the interrupt.
*/
extern void isr_handler(struct registers *regs);

/**
 * @brief       This file handles the interrupt request.
 * @param   nb  The number of the interrupt.
*/
extern void irq_handler(struct registers *regs);

/**
 * @brief       Setup the interrupt descriptor table.
*/
void idt_setup();

/**
 * @brief   Enable an interrupt.
 * @param   nb  The number of the interrupt.
*/
void enable_interrupt(uint8_t nb);

/**
 * @brief   Add a callback to an interrupt.
*/
void set_callback(int nb, isr_callback cb);

#endif
