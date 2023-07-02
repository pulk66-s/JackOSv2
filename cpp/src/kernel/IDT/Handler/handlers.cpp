#include "kernel/IDT/Handler/handlers.hpp"

// static ISRHandler isrHandler;
// static IRQHandler irqHandler;

namespace JO::Kernel::IDT::Handler {
    ISRHandler *getISRHandler()
    {
        return nullptr;
        // return &isrHandler;
    }

    IRQHandler *getIRQHandler()
    {
        return nullptr;
        // return &irqHandler;
    }
}