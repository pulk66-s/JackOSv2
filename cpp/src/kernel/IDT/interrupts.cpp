#include "kernel/IDT/interrupts.hpp"
#include "kernel/IDT/Handler/ISRHandler.hpp"
#include "kernel/IDT/Handler/IRQHandler.hpp"
#include "kernel/VGA/VGA.hpp"

extern "C" {
    void isr_handler(struct registers *regs) {
        VGA vga;
        vga.puts("ISR: ");
    }

    void irq_handler(struct registers *regs) {
        Pic pic;

        if (regs->interrupt >= 40) {
            pic.outb(0xA0, 0x20);
        }
        pic.outb(0x20, 0x20);
        if (regs->interrupt == 33) {
            VGA vga;
            vga.puts("IRQ: ");
        }
    }
}