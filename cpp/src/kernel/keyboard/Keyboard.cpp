#include "kernel/keyboard/Keyboard.hpp"
#include "kernel/IDT/Handler/handlers.hpp"

void Keyboard::init(IDT *idt)
{
    idt->enableEntry(33);
}
