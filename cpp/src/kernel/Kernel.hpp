#ifndef __JACKOS_KERNEL_KERNEL_HPP__
    #define __JACKOS_KERNEL_KERNEL_HPP__

    #include <kernel/VGA.hpp>
    #include <kernel/IDT.hpp>
    #include <kernel/GDT.hpp>
    #include <kernel/PS2.hpp>
    #include <kernel/KernelNamespace.hpp>

namespace JO::Kernel
{
    /**
     * @brief      The kernel class
     * It's the main class of the kernel.
     * It's the first class to be instantiated.
     * It's the first class to be executed.
     * This is where the kernel starts.
    */
    class Kernel {

        struct Context {
            VGA::VGA *vga;
            IDT::IDT *idt;
            GDT::GDT *gdt;
            PS2::Keyboard *keyboard;
        };

    private:
        VGA::VGA vga;
        IDT::IDT idt;
        GDT::GDT gdt;
        PS2::Keyboard keyboard;

    public:
        void run();
        Context getContext();
        static Kernel *getKernel();
    };
}

#endif