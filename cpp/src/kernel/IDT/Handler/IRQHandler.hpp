#ifndef __JACKOS_KERNEL_IDT_HANDLER_IRQHANDLER_HPP__
    #define __JACKOS_KERNEL_IDT_HANDLER_IRQHANDLER_HPP__

    #include "kernel/IDT/Handler/IHandler.hpp"
    #include <kernel/PIC.hpp>
    #include <kernel/PIC/PICNamespace.hpp>

    #define IRQ_MAX_CALLBACKS 256

namespace JO::Kernel::IDT::Handler
{
    class IRQHandler: public IHandler {
    public:
        IRQHandler();
        void handle(struct registers *regs);
        void addCallback(int irq, handler callback);

    private:
        PIC::Pic pic;
        handler callbacks[IRQ_SIZE][IRQ_MAX_CALLBACKS];
    };
}

#endif