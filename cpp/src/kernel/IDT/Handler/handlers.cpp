#include "kernel/IDT/Handler/handlers.hpp"

// static ISRHandler isrHandler;
// static IRQHandler irqHandler;

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