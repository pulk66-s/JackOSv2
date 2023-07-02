#ifndef __JACKOS_KERNEL_KERNEL_HPP__
    #define __JACKOS_KERNEL_KERNEL_HPP__

    #include <kernel/VGA.hpp>
    #include <kernel/IDT.hpp>
    #include <kernel/GDT.hpp>
    #include <kernel/Keyboard.hpp>

/**
 * @brief      The kernel class
 * It's the main class of the kernel.
 * It's the first class to be instantiated.
 * It's the first class to be executed.
 * This is where the kernel starts.
*/
class Kernel {

    struct Context {
        VGA *vga;
        IDT *idt;
        GDT *gdt;
        Keyboard *keyboard;
    };

private:
    VGA vga;
    IDT idt;
    GDT gdt;
    Keyboard keyboard;

public:
    void run();
    Context getContext();
    static Kernel *getKernel();
};

#endif