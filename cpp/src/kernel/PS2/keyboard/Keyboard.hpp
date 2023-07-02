#ifndef __JACKOS_KERNEL_PS2_KEYBOARD_KEYBOARD_HPP__
    #define __JACKOS_KERNEL_PS2_KEYBOARD_KEYBOARD_HPP__

    #include <kernel/IDT.hpp>
    #include <kernel/PS2/PS2Namespace.hpp>

namespace JO::Kernel::PS2
{
    class Keyboard {
    public:
        void init(IDT::IDT *idt);
        void handleInput(uint8_t scancode);
    };
}

#endif