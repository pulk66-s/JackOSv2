#ifndef __JACKOS_KERNEL_GDT_GDT_HPP__
    #define __JACKOS_KERNEL_GDT_GDT_HPP__

    #include "kernel/GDT/types.hpp"

class GDT {
public:
    void init();
    void load();
    void setEntry(uint8_t index, struct base base, uint32_t limit, uint8_t access, uint8_t granularity);

private:
    struct gdt_entry gdt[NO_GDT_DESCRIPTORS];
    struct gdt_descriptor gdtr;
};

#endif