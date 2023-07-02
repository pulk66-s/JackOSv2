#include "kernel/keyboard/Keyboard.hpp"
#include "kernel/IDT/Handler/handlers.hpp"
#include <kernel/VGA.hpp>

void Keyboard::init(IDT *idt)
{
    idt->enableEntry(33);
}

void Keyboard::handleInput(uint8_t scancode)
{
    VGA vga;

    vga.clear();
    vga.puts("Keyboard: ");
    vga.puti(scancode);
}