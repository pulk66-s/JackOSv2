#include "kernel/GDT/GDT.hpp"
#include <stddef.h>

void GDT::init()
{
    for (size_t i = 0; i < NO_GDT_DESCRIPTORS; i++) {
        this->gdt[i] = (struct gdt_entry) {
            .segment_limit = 0,
            .base_low = 0,
            .base_middle = 0,
            .access = 0,
            .granularity = 0,
            .base_high = 0
        };
    }
    this->gdtr = (struct gdt_descriptor) {
        .limit = sizeof(struct gdt_entry) * NO_GDT_DESCRIPTORS - 1,
        .gdt = (struct gdt_entry *)&this->gdt
    };

    this->setEntry(0, (struct base){0, 0, 0}, 0, 0, 0);                   // null segment
    this->setEntry(1, (struct base){0, 0, 0}, 0xffffffff, 0x9a, 0xcf);    // code segment
    this->setEntry(2, (struct base){0, 0, 0}, 0xffffffff, 0x92, 0xcf);    // data segment
    this->setEntry(3, (struct base){0, 0, 0}, 0xffffffff, 0xfa, 0xcf);    // user code segment
    this->setEntry(4, (struct base){0, 0, 0}, 0xffffffff, 0xf2, 0xcf);    // user data segment
    this->load();                                                         // load the GDT (global descriptor table
}

inline void GDT::load()
{
    asm volatile("lgdt (%0)" : : "r" (&this->gdtr));
}

void GDT::setEntry(uint8_t index, struct base base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    this->gdt[index] = {
        .segment_limit = limit & 0xFFFF,
        .base_low = base.low & 0xFFFF,
        .base_middle = base.middle,
        .access = access,
        .granularity = granularity,
        .base_high = base.high
    };
}