#ifndef __JACKOS_KERNEL_KERNEL_HPP__
    #define __JACKOS_KERNEL_KERNEL_HPP__

    #include "VGA/VGA.hpp"

class Kernel {

private:
    VGA vga;

public:
    void run();
};

#endif