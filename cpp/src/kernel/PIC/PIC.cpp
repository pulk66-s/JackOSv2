#include "kernel/PIC/PIC.hpp"

namespace JO::Kernel::PIC
{
    void Pic::remap()
    {
        this->outb(0x20, 0x11);
        this->outb(0xA0, 0x11);
        this->outb(0x21, 0x20);
        this->outb(0xA1, 0x28);
        this->outb(0x21, 0x04);
        this->outb(0xA1, 0x02);
        this->outb(0x21, 0x01);
        this->outb(0xA1, 0x01);
        this->outb(0x21, 0x0);
        this->outb(0xA1, 0x0);
    }

    uint8_t Pic::inb(uint16_t port)
    {
        uint8_t result = 0;

        asm volatile("in %%dx, %%al" : "=a" (result) : "d" (port));
        return (result);
    }

    void Pic::outb(uint16_t port, uint8_t data)
    {
        asm volatile("out %%al, %%dx" : : "a" (data), "d" (port));
    }
}