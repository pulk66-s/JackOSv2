#ifndef __JACKOS_KERNEL_KERNEL_HPP__
    #define __JACKOS_KERNEL_KERNEL_HPP__

    #include "kernel/VGA/VGA.hpp"
    #include "kernel/IDT/IDT.hpp"
    #include "kernel/GDT/GDT.hpp"
    #include "kernel/keyboard/Keyboard.hpp"

/**
 * @brief      The kernel class
 * It's the main class of the kernel.
 * It's the first class to be instantiated.
 * It's the first class to be executed.
 * This is where the kernel starts.
*/
class Kernel {

private:
    // To display basic information on the screen
    VGA vga;
    IDT idt;
    GDT gdt;
    Keyboard keyboard;

public:
    void run();
};

#endif