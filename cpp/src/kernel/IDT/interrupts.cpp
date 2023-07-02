#include "kernel/IDT/interrupts.hpp"
#include "kernel/IDT/Handler/ISRHandler.hpp"
#include "kernel/IDT/Handler/IRQHandler.hpp"

#include <kernel/GDT.hpp>
#include <kernel/Kernel.hpp>

namespace JO::Kernel::IDT {

    extern "C" {
        void isr_handler(struct registers *regs) {
            VGA::VGA vga;
            vga.puts("ISR: ");
        }

        void irq_handler(struct registers *regs) {
            PIC::Pic pic;

            if (regs->interrupt >= 40) {
                pic.outb(0xA0, 0x20);
            }
            pic.outb(0x20, 0x20);
            if (regs->interrupt == 33) {
                uint8_t scancode = pic.inb(0x60);
                PS2::Keyboard *keyboard = JO::Kernel::Kernel::getKernel()->getContext().keyboard;

                keyboard->handleInput(scancode);
            }
        }
    }
}