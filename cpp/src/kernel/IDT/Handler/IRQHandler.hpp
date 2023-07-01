#ifndef __JACKOS_KERNEL_IDT_HANDLER_IRQHANDLER_HPP__
    #define __JACKOS_KERNEL_IDT_HANDLER_IRQHANDLER_HPP__

    #include "kernel/IDT/Handler/IHandler.hpp"
    #include "kernel/PIC/PIC.hpp"

    #define IRQ_MAX_CALLBACKS 256

class IRQHandler: public IHandler {
public:
    IRQHandler();
    void handle(struct registers *regs);
    void addCallback(int irq, handler callback);

private:
    Pic pic;
    handler callbacks[IRQ_SIZE][IRQ_MAX_CALLBACKS];
};

#endif