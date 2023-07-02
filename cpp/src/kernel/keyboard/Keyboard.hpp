#ifndef __JACKOS_KERNEL_KEYBOARD_KEYBOARD_HPP__
    #define __JACKOS_KERNEL_KEYBOARD_KEYBOARD_HPP__

    #include "kernel/IDT/IDT.hpp"

class Keyboard {
public:
    void init(IDT *idt);
    void handleInput(uint8_t scancode);
};

#endif