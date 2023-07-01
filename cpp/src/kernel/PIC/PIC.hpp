#ifndef __JACKOS_KERNEL_PIC_PIC_HPP__
    #define __JACKOS_KERNEL_PIC_PIC_HPP__

    #include <stdint.h>

class Pic {
public:
    void remap();

    uint8_t inb(uint16_t port);
    void outb(uint16_t port, uint8_t data);
};

#endif