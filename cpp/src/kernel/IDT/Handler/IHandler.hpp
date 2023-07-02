#ifndef __JACKOS_KERNEL_IDT_HANDLER_IHANDLER_HPP__
    #define __JACKOS_KERNEL_IDT_HANDLER_IHANDLER_HPP__

    #include "kernel/IDT/types.hpp"

namespace JO::Kernel::IDT::Handler {
    class IHandler {
        virtual void handle(struct registers *regs) = 0;
    };
}

#endif