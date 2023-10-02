#ifndef __JOS_INTERRUPTS_DATA_H__
#define __JOS_INTERRUPTS_DATA_H__

#include <lib/types.h>

#define IDT_ENTRIES 48
#define MAX_CALLBAC_PER_ENTRY 10

/**
 * @brief       The interrupt descriptor table entry
*/
struct idt_entry {
    uint16_t isr_low;   // The lower 16 bits of the ISR's address
    uint16_t kernel_cs; // The GDT segment selector that the CPU will load into CS before calling the ISR
    uint8_t reserved;   // Set to zero
    uint8_t attributes; // Type and attributes; see the IDT page
    uint16_t isr_high;  // The higher 16 bits of the ISR's address
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#endif
