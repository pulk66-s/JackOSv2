#ifndef __JACKOS_KERNEL_KERNEL_HPP__
    #define __JACKOS_KERNEL_KERNEL_HPP__

    #include "VGA/VGA.hpp"
    #include "IDT/IDT.hpp"

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

public:
    void run();
};

#endif