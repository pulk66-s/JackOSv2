#ifndef __JACKOS_KERNEL_IDT_IDT_HPP__
#define __JACKOS_KERNEL_IDT_IDT_HPP__

#include "kernel/IDT/types.hpp"
#include "kernel/PIC/PIC.hpp"

class IDT
{
public:
    void init();
    void enableAllEntries();
    inline void disableEntry(uint8_t index);
    void enableEntry(uint8_t index);
    inline void sti();
    inline void lidt();

private:
    struct idt_entry idt[IDT_SIZE];
    struct idt_descriptor idt_descriptor;
    Pic pic;

    void fillEntries();
    inline void createIdtEntry(uint8_t index, void (*call)(), uint16_t segment, uint8_t flags);
};

#endif