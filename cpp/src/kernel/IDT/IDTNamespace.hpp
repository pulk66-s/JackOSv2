#ifndef __JACKOS_KERNEL_IDT_IDTNAMESPACE_HPP__
    #define __JACKOS_KERNEL_IDT_IDTNAMESPACE_HPP__

namespace JO::Kerne::IDT
{
    class IDT;
    namespace Handler
    {
        class IHandler;
        class ISRHandler;
        class IRQHandler;
    }
}

#endif