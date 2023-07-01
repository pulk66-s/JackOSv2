#ifndef __JACKOS_KERNEL_IDT_HANDLER_HPP__
    #define __JACKOS_KERNEL_IDT_HANDLER_HPP__

    #include "kernel/IDT/types.hpp"

class ISRHandler {
public:
    void handle();
};

#endif