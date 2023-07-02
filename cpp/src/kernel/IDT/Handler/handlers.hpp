#ifndef __JACKOS_KERNEL_IDT_HANDLER_HANDLERS_HPP__
    #define __JACKOS_KERNEL_IDT_HANDLER_HANDLERS_HPP__

    #include "kernel/IDT/Handler/IRQHandler.hpp"
    #include "kernel/IDT/Handler/ISRHandler.hpp"

namespace JO::Kernel::IDT::Handler {
    ISRHandler *getISRHandler();
    IRQHandler *getIRQHandler();
}

#endif