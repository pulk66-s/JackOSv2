#include "kernel/PS2/keyboard/Keyboard.hpp"

#include <kernel/VGA.hpp>

namespace JO::Kernel::PS2
{
    void Keyboard::init(IDT::IDT *idt)
    {
        idt->enableEntry(33);
    }

    void Keyboard::handleInput(uint8_t scancode)
    {
        VGA::VGA vga;

        vga.clear();
        vga.puts("Keyboard: ");
        vga.puti(scancode);
    }
}