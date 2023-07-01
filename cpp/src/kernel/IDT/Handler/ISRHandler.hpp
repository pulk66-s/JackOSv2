#ifndef __JACKOS_KERNEL_IDT_ISRHANDLER_HPP__
    #define __JACKOS_KERNEL_IDT_ISRHANDLER_HPP__

    #include "kernel/IDT/types.hpp"
    #include "kernel/IDT/Handler/IHandler.hpp"

    #define ISR_MAX_CALLBACKS 256

class ISRHandler: public IHandler {
public:
    ISRHandler();
    void handle(struct registers *regs);
    void addCallback(int isr, handler callback);

private:
    handler callbacks[ISR_SIZE][ISR_MAX_CALLBACKS];
};

#endif